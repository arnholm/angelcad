// BeginLicense:
// Part of: angelcad - script based 3D solid modeller
// Copyright (C) 2017 Carsten Arnholm
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

#include <stdexcept>

#include "wxProcessExecute.h"
#if defined(__WXMSW__)
      // wxSIGTERM fails on windows, must use wxSIGKILL http://trac.wxwidgets.org/ticket/15356
      const wxSignal SIGNAL_TERMINATE = wxSIGKILL;
#else
      // wxSIGTERM ok on linux
      const wxSignal SIGNAL_TERMINATE = wxSIGTERM;
#endif


wxProcessExecute::wxProcessExecute()
: wxProcess(wxPROCESS_DEFAULT)
, m_pid(0)
{
}

wxProcessExecute::~wxProcessExecute()
{}

long wxProcessExecute::Execute(wxEvtHandler* parent, int id, const wxString cmd)
{
   Init(parent,id,wxPROCESS_REDIRECT|wxEVT_END_PROCESS);
   m_pid = wxExecute(cmd, wxEXEC_ASYNC, this);
   if(m_pid == 0) {
      throw std::runtime_error("Failed to start process: " + cmd.ToStdString());
   }
   return m_pid;
}

long wxProcessExecute::KillJob()
{
   long retval = 0;
   if(m_pid > 0) {
      wxKillError status = wxProcess::Kill(m_pid,SIGNAL_TERMINATE);
      if( (status == wxKILL_OK) || (status == wxKILL_NO_PROCESS) ) {
         retval = m_pid;
         m_pid = 0;
      }
      else if(status == wxKILL_ACCESS_DENIED ) return -1;
      else if(status == wxKILL_ERROR  )        return -2;
   }
   return retval;
}

