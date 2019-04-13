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
   
#ifndef WXCONFIGSAVERESTORE_H
#define WXCONFIGSAVERESTORE_H

#include <map>
#include <wx/config.h>
#include <wx/string.h>
#include <wx/filename.h>
#include <wx/frame.h>
#include "wxConfigBooleans.h"

class wxConfigSaveRestore {
public:
   wxConfigSaveRestore(wxFrame* window, wxConfig* config);
   virtual ~wxConfigSaveRestore();

   void SaveRestoreWindowSize(bool save);
   void SaveRestoreFlags(bool save, wxConfigBooleans& flags);

protected:

private:
   wxFrame*  m_window;
   wxConfig* m_config;
};

#endif // WXCONFIGSAVERESTORE_H
