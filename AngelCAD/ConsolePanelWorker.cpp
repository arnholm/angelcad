// BeginLicense:
// Part of: angelcad - script based 3D solid modeller
// Copyright (C) 2017-2020 Carsten Arnholm
// All rights reserved
//
// This file may be used under the terms of either the GNU General
// Public License version 2 or 3 (at your option) as published by the
// Free Software Foundation and appearing in the files LICENSE.GPL2
// and LICENSE.GPL3 included in the packaging of this file.
//
// This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
// INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE.
// EndLicense:

#include "ConsolePanelWorker.h"
#include <wx/textctrl.h>

ConsolePanelWorker::ConsolePanelWorker(wxWindow* parent,
                                       ts_queue<wxString>*    to_worker,     // messages to worker from application
                                       ts_queue<ConsoleText>* from_worker,   // messages to application from worker
                                       wxInputStream* std_out,
                                       wxInputStream* std_err
                                      )
: m_parent(parent)
, m_to_worker(to_worker)
, m_from_worker(from_worker)
, m_std_out(std_out)
, m_std_err(std_err)
{}

ConsolePanelWorker::~ConsolePanelWorker()
{}

void ConsolePanelWorker::operator()()
{
   run();
}

void ConsolePanelWorker::AppendText(const wxString& txt)
{
   if(txt.Find("asERR") != wxNOT_FOUND) {
      m_from_worker->enqueue(ConsoleText(2,txt));
   }
   else if(txt.Find("asWARN") != wxNOT_FOUND) {
      m_from_worker->enqueue(ConsoleText(1,txt));
   }
   else {
      m_from_worker->enqueue(ConsoleText(0,txt));
   }

   // signal to the gui that there is data on the message queue
   wxThreadEvent* event = new wxThreadEvent();
   event->SetInt(0); // 0 means "display text"
   wxQueueEvent(m_parent,event);
}

void ConsolePanelWorker::run()
{
   try{
      int retval = 1;  // "Start next Job"

      wxTextInputStream std_out(*m_std_out);
      while(!m_std_out->Eof()) {

         // check if there was a message from the application
         wxString msg_from_app;
         if(m_to_worker->try_dequeue(msg_from_app)) {

            if(msg_from_app == "END_PROCESS") {
               // empty the buffer
               while(!m_std_out->Eof()) {
                  wxString line = std_out.ReadLine();
                  AppendText(line);
               }
               break;
            }
         }

         // if we reached the end of the input, we exit in a different way
         if(m_std_out->Eof()) {
            break;
         }

         // read line by line and add to our text control
         wxString line = std_out.ReadLine();
         AppendText(line);
      }

      // if the subprocess wrote to std_err, we output those messages as well
      // and consider it an error situation
      wxTextInputStream std_err(*m_std_err);
      while(!m_std_err->Eof()) {
         if(m_std_err->Eof()) {
            break;
         }
         wxString line = std_err.ReadLine();
         if(line.length() > 0) {
            AppendText(line);
            // this is an error situation

            // However, OpenSCAD writes "ECHO:" to std_err, even if there is no error
            // so in this special case we cancel the error and continue
            if(line.find("ECHO:")       != static_cast<size_t>(wxNOT_FOUND))      retval =  1;  // no error
            else if(line.find("DEPRECATED:") != static_cast<size_t>(wxNOT_FOUND)) retval =  1;  // no error
            else                                                                  retval = -1;  // error
         }
      }

      // add a blank line for readability
      AppendText("  ");

      // signal to the gui that the worker thread is done.
      // Queue the event so the GUI can catch it
      wxThreadEvent* event = new wxThreadEvent();
      event->SetInt(retval);  // 1 means "start next job", -1 means TerminateJobs
      wxQueueEvent(m_parent,event);

   }
   catch(std::exception ex) {
      AppendText("Exception: " + wxString(ex.what()));

      // signal to the gui that the worker thread detected a fatal error
      wxThreadEvent* event = new wxThreadEvent();
      event->SetInt(-1);  // -1 means "terminate jobs"
      wxQueueEvent(m_parent,event);
   }
}
