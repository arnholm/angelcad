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

#ifndef CONSOLEPANELWORKER_H
#define CONSOLEPANELWORKER_H

#include "threads/ts_queue.h"
#include <wx/string.h>
#include <wx/txtstrm.h>
#include <wx/window.h>
#include "ConsoleText.h"
class wxTextCtrl;

// The console panel worker is a helper class running in a separate thread
// it monitors the redirected output from an external process, the output is
// read from "wxInputStream* msg". The class sends text data to the GUI using "from_worker"
// and receives messages from the GUI thread in "to_worker".

class ConsolePanelWorker {
public:
   ConsolePanelWorker(wxWindow* parent,                     // the parent wiondow starting the worker
                      ts_queue<wxString>* to_worker,        // messages to worker from application
                      ts_queue<ConsoleText>* from_worker,   // messages to application from worker
                      wxInputStream* std_out,                //
                      wxInputStream* std_err                 //
                      );
   virtual ~ConsolePanelWorker();

   // used when running as boost:thread
   void operator()();

   // used when running without thread
   void run();

protected:
   void AppendText(const wxString& txt);

private:
   wxWindow*              m_parent;
   ts_queue<wxString>*    m_to_worker;
   ts_queue<ConsoleText>* m_from_worker;
   wxInputStream*         m_std_out;     // stream corresponding to the standard output stream of the subprocess.
   wxInputStream*         m_std_err;     // stream corresponding to the standard error output stream of the subprocess.
};

#endif // CONSOLEPANELWORKER_H
