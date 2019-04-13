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
   
#ifndef CONSOLETEXT_H
#define CONSOLETEXT_H

#include <wx/string.h>
#include <wx/colour.h>

// console text is a helper class for transferring text messages from worker thread to GUI thread
// we cannot reliably write to text controls from other than GUI thread so this is required.
// The text carries with it an integer used for error classification and finally colour coding in the gui

class ConsoleText {
public:
   ConsoleText() : m_status(0)  {}
   ConsoleText(int status, const wxString& txt);
   virtual ~ConsoleText();

   inline int status() const { return m_status; }
   inline const wxString& txt() const { return m_txt; }

private:
   int      m_status;  // 0=normal, 1=warning, 2=error
   wxString m_txt;
};

#endif // CONSOLETEXT_H
