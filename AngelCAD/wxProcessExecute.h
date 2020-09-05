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

#ifndef WXPROCESSEXECUTE_H
#define WXPROCESSEXECUTE_H

#include <wx/process.h>

// special wxProcess designed for executing external commands with output redirection

class wxProcessExecute : public wxProcess {
public:
   // the parent must handle wxEVT_END_PROCESS
   wxProcessExecute();
   virtual ~wxProcessExecute();

   // the return value is the process id and zero value indicates that the command could not be executed.
   long Execute(wxEvtHandler* parent, int id, const wxString cmd);

   long GetPid() { return m_pid; }

   // kill running job
   long KillJob();

   // ClearPid should be called after a running job has terminated
   void ClearPid() { m_pid = 0; }

private:
   long m_pid;   // process-id of any running process, or 0 if none
};

#endif // WXPROCESSEXECUTE_H
