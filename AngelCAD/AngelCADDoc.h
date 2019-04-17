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

#ifndef ANGELCADDOC_H
#define ANGELCADDOC_H

#include <map>
#include <wx/string.h>
#include <wx/filename.h>

#include "ConfigSaveRestore.h"

class AngelCADDoc {
   friend class AngelCADApp;
public:
   virtual ~AngelCADDoc();
   static AngelCADDoc* singleton() { return m_self; }

   void SaveConfig(ConfigSaveRestore& config_helper);
   void RestoreConfig(ConfigSaveRestore& config_helper);

   // GetOutSubDir() returns the relative path defined in the configuration
   wxFileName GetOutSubDir();

   // compute the absolute output XCSG file path, from the source file and subdir setting
   wxFileName GetXcsgFileName(const wxFileName& source_file);

   // get full path to file in configuration
   wxFileName GetConfigFilePath(ConfigEnums::ExtFile file);

   // set new path to file in configuration
   void SetConfigFilePath(ConfigEnums::ExtFile file, const wxFileName& fname);

   // get boolean for stl, amf etc
   bool GetFileFormatFlag(wxString format);

   // set boolean for stl, amf etc
   void SetFileFormatFlag(wxString format, bool enabled);

   // create options string for xcsg based on current settings
   wxString GetXcsgFormatOptionString();

   // define the save directory
   void SetSaveDir(wxString savedir);

   // return save directory
   wxString GetSaveDir() const;

   // define the HTML documentation URL
   void SetDocUrl(wxString url);

   // return he HTML documentation URL
   wxString GetDocUrl() const;

   // return URL of license info
   wxString GetLicenseUrl() const;

protected:
   AngelCADDoc();

private:
   std::map<ConfigEnums::ExtFile,wxFileName> m_file_paths; // <file_enum, path>
   std::map<wxString,bool>                   m_formats;    // <format,true>, XSCG save formats
   wxString                                  m_savedir;    // path to directory where last .as file was saved
   wxString                                  m_docurl;     // HTML documentation URL

private:
   static AngelCADDoc* m_self;
};

inline AngelCADDoc* DOC() { return AngelCADDoc::singleton(); }

#endif // ANGELCADDOC_H
