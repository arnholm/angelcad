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

#ifndef CONSOLEPANEL_H
#define CONSOLEPANEL_H

#include <wx/process.h>
#include "wxProcessExecute.h"
#include "ConsoleText.h"

#include "threads/ts_queue.h"
#include <list>

class AngelCADEditor;

//(*Headers(ConsolePanel)
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
//*)

class ConsolePanel: public wxPanel {
public:
   typedef std::pair<wxString,AngelCADEditor*> JobPair;

   ConsolePanel(wxWindow* parent,wxWindowID id=wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = "ConsolePanel");
   virtual ~ConsolePanel();

   // clear the console
   void Clear();

   // append a line of text to the console
   void AppendText(const wxString& text, int status = 0);

   // returs true if there are ongoing jobs
   bool is_busy() const { return m_is_busy; }

   // execute the list of jobs in sequence
   void Execute(const std::list<JobPair>& jobs);

   // kill running jobs
   void KillJobs();

   //(*Declarations(ConsolePanel)
   wxTextCtrl* m_txtctrl;
   //*)

protected:
   void DisplayTextFromWorker();
   void StartNextJob();
   void TerminateJobs();

   // execute the compilation of the code saved from the page
   void Execute(const wxString& cmd, AngelCADEditor* page);

   // event handler receiving messages from worker thread
   void OnThreadUpdate(wxThreadEvent& evt);

   //(*Identifiers(ConsolePanel)
   static const long ID_TEXTCTRL1;
   //*)

   // handler for wxEVT_END_PROCESS
   void OnEndProcess(wxProcessEvent& event);

private:

   //(*Handlers(ConsolePanel)
   //*)

   DECLARE_EVENT_TABLE()
private:
   wxProcessExecute           m_process;       // external process to manage
   ts_queue<wxString>    m_to_worker;     // queue for messages to the worker thread
   ts_queue<ConsoleText> m_from_worker;   // queue for messages from the worker thread
   AngelCADEditor*            m_page;          // the current source file page
   std::list<JobPair>         m_jobs;          // the list of external jobs to be executed
   bool                       m_is_busy;       // true if processes being executed
   size_t                     m_error_count;   // error count in this batch of jobs
   int                        m_prev_status;   // optimization used to avoid updating colour every time
};

#endif
