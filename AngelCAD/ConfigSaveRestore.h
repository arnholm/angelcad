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

#ifndef CONFIGSAVERESTORE_H
#define CONFIGSAVERESTORE_H

#include <map>
#include <wx/config.h>
#include <wx/string.h>
#include <wx/filename.h>
#include <wx/frame.h>

#include "ConfigEnums.h"

class ConfigSaveRestore {
public:
   ConfigSaveRestore(wxFrame* window, wxConfig* config);
   virtual ~ConfigSaveRestore();

   void SaveRestoreWindowSize(bool save);
   void SaveRestoreExternalFiles(std::map<ConfigEnums::ExtFile,wxFileName>& file_paths, bool save);
   void SaveRestoreFormats(std::map<wxString,bool>& formats, bool save);
   void SaveRestoreSaveDir(wxString& savedir, bool save);
   void SaveRestoreDocURL(wxString& url, bool save);
   void SaveRestoreArguments(wxString& args, bool save);

   static wxFileName DefaultOpenScadPath();
   static wxFileName DefaultDxfViewerPath();
   static wxString   DefaultDocUrl();
private:
   wxFrame*  m_window;
   wxConfig* m_config;
};

#endif // CONFIGSAVERESTORE_H
