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

#include "ConsolePanel.h"
#include "ConsolePanelWorker.h"
#include "AngelCADEditor.h"
#include <boost/thread.hpp>
#include <wx/msgdlg.h>

//(*InternalHeaders(ConsolePanel)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(ConsolePanel)
const long ConsolePanel::ID_TEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ConsolePanel,wxPanel)
	//(*EventTable(ConsolePanel)
	//*)
END_EVENT_TABLE()

ConsolePanel::ConsolePanel(wxWindow* parent,wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: m_page(0)
, m_is_busy(false)
, m_error_count(0)
, m_prev_status(-1)
{
	//(*Initialize(ConsolePanel)
	wxBoxSizer* BoxSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	m_txtctrl = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	wxFont m_txtctrlFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
	m_txtctrl->SetFont(m_txtctrlFont);
	BoxSizer1->Add(m_txtctrl, 1, wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)

   // connect the thread event handler to the thread event ID
   Bind(wxEVT_THREAD, &ConsolePanel::OnThreadUpdate, this);

   // receive end process events in this console
	Connect(id,wxEVT_END_PROCESS,(wxObjectEventFunction)&ConsolePanel::OnEndProcess);
}

ConsolePanel::~ConsolePanel()
{
	//(*Destroy(ConsolePanel)
	//*)
}

void ConsolePanel::Clear()
{
   m_txtctrl->Clear();
}

void ConsolePanel::AppendText(const wxString& text, int status)
{
   if(status != m_prev_status) {
      switch(status) {
         case 0:  { m_txtctrl->SetDefaultStyle(wxTextAttr(*wxBLACK)); break; }
         case 1:  { m_txtctrl->SetDefaultStyle(wxTextAttr(*wxBLUE)); break; }
         case 2:  { m_txtctrl->SetDefaultStyle(wxTextAttr(*wxRED)); m_error_count++; break; }
         default: { m_txtctrl->SetDefaultStyle(wxTextAttr(*wxBLACK)); }
      };
      m_prev_status = status;
   }
   m_txtctrl->AppendText(text+'\n');
}

void ConsolePanel::Execute(const std::list<JobPair>& jobs, bool clear_console)
{
   if(clear_console)Clear();

   // establish the list of jobs, and start executing the first job
   m_jobs = jobs;
   if(m_jobs.size() > 0) {
      m_error_count = 0;

      m_is_busy = true;
      // pull the job from the list, start it, and remove from list
      JobPair& job = *m_jobs.begin();
      Execute(job.first,job.second);
      m_jobs.erase(m_jobs.begin());
   }
}

void ConsolePanel::KillJobs()
{
   long pid1 = m_process.GetPid();
   if(pid1 > 0) {
      AppendText(wxString::Format("Stopping process %ld",pid1));
      m_jobs.clear();
      long pid2 = m_process.KillJob();
      if(pid1 == pid2) AppendText(wxString::Format("Process %ld stopped OK",pid2));
      else             AppendText(wxString::Format("Process %ld could not be stopped: %ld",pid1,pid2));
   }
   else {
      AppendText("No running process, nothing to stop.");
   }
}

void ConsolePanel::Execute(const wxString& cmd, AngelCADEditor* page)
{
   if(page)page->DeleteErrorMarkers();

   // create the process with redirection and start executing
   if(long pid = m_process.Execute(this,GetId(),cmd)) {

      AppendText(wxString::Format("%ld > ",pid)+ cmd);

      m_page        = page;
      m_prev_status = -1;

      // process started
      // get the input stream from redirection
      wxInputStream* std_out = m_process.GetInputStream();
      wxInputStream* std_err = m_process.GetErrorStream();

      // empty the queues
      ConsoleText from_txt;
      wxString txt;
      while(m_from_worker.try_dequeue(from_txt)) {}
      while(m_to_worker.try_dequeue(txt)) {}

      // start a thread to display the progress,
      // just let it run until this console panel receives the wxEVT_END_PROCESS event
      // in which case a message will be sent to the thread to tell it to exit
      // and a wxTrheadEvent will be issued in return to signal it did complete, see OnThreadUpdate below

      boost::thread(ConsolePanelWorker(this,&m_to_worker,&m_from_worker,std_out,std_err));

   }
   else {
      m_page = 0;
      AppendText("Error m_process->Execute(cmd)");
   }
}

void ConsolePanel::OnEndProcess(wxProcessEvent& event)
{
   // the external process ended. Send message to the worker thread
   m_to_worker.enqueue("END_PROCESS");
}

void ConsolePanel::DisplayTextFromWorker()
{
   ConsoleText msg;
   while(m_from_worker.try_dequeue(msg)) {

      const wxString& line = msg.txt();
      AppendText(line,msg.status());

      // if an error is detected, highlight it in the source code
      // we do this only at first error found
      if(line.Find("asERR") != wxNOT_FOUND) {
         if(m_page && m_error_count==0) {

            // this speculates on the format of the error output
            int ipos = line.Find(": (line");
            if(ipos != wxNOT_FOUND) {

               // lno_source is a line number in the script source
               int lno_source = 0;

               // get the relevant substring from the error message and read the line number
               wxString buf = line.Mid(ipos+7,10);
               std::istringstream in(buf.ToStdString());
               in >> lno_source;
               if(lno_source > 0) {
                  // add the error marker in the margin of the editor and make sure the line is visible
                  m_page->InsertErrorMarker(lno_source);
                  m_page->SetFirstVisibleLine(m_page->MarkerNext(0,0x1)-5);

                  // check to see if we can highlight the column as well
                  int col_pos = line.Find(", col");
                  if(col_pos != wxNOT_FOUND) {

                     int icol = 0;
                     wxString buf = line.Mid(col_pos+5,10);
                     std::istringstream in(buf.ToStdString());
                     in >> icol;

                     // get position at the start of the line. For some reason we must subtract one here
                     int line_pos = m_page->PositionFromLine(lno_source-1);

                     // set anchor point at the column where the error was found
                     // we use SetSelection with same from and to position, just to get the caret in the right place
                     int from = line_pos+icol-1;
                     int to   = from;
                     m_page->SetSelection(from,to);
                  }
               }
            }
         }
         m_error_count++;
      }
   }
}

void ConsolePanel::StartNextJob()
{
   // if errors detected, do not start next job
   if(m_error_count == 0) {

      // display any remaining messages
      DisplayTextFromWorker();

      // Start the next job on the list
      if(m_jobs.size() > 0) {
         // pull the job from the list, start it, and remove from list
         auto i = m_jobs.begin();
         Execute(i->first,i->second);
         m_jobs.erase(i);
      }
      else {
         // no more jobs
         m_is_busy = false;
         m_process.ClearPid();

         AppendText("Build completed! Press F7 to view.",0);
      }
   }
   else {
      TerminateJobs();
   }
}

void ConsolePanel::TerminateJobs()
{
   DisplayTextFromWorker();
   m_jobs.clear();
   m_is_busy = false;
   m_process.ClearPid();
}

void ConsolePanel::OnThreadUpdate(wxThreadEvent& evt)
{
   int retval = evt.GetInt();
   switch(retval) {
      case -1:  { TerminateJobs();
                  m_error_count++;
                  AppendText("ERRORS found: Build stopped. Please correct and try again.",2);
                  break; }
      case  0:  { DisplayTextFromWorker(); break; }
      case  1:  { StartNextJob(); break; }
      default:  { TerminateJobs();  }
   };
}
