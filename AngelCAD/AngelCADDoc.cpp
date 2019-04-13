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
   
#include "AngelCADDoc.h"
#include "ConfigEnums.h"
#include "wx/stdpaths.h"

AngelCADDoc* AngelCADDoc::m_self;

AngelCADDoc::AngelCADDoc()
{
   m_self = this;

   // default file output formats
   m_formats["amf"] = false;
   m_formats["stl"] = true;
   m_formats["csg"] = false;
   m_formats["dxf"] = true;
   m_formats["svg"] = true;
   m_formats["obj"] = false;
   m_formats["off"] = false;

   // default file paths
   wxFileName exec_path(wxStandardPaths::Get().GetExecutablePath());
   m_file_paths[ConfigEnums::AS_CSG]     = wxFileName(exec_path.GetPath(),"as_csg",exec_path.GetExt());
   m_file_paths[ConfigEnums::AS_OUTSUB]  = "xcsg";
   m_file_paths[ConfigEnums::XCSG]       = wxFileName(exec_path.GetPath(),"xcsg",exec_path.GetExt());
   m_file_paths[ConfigEnums::OPENSCAD]   = ConfigSaveRestore::DefaultOpenScadPath();
   m_file_paths[ConfigEnums::STLAMFVIEW] = wxFileName(exec_path.GetPath(),"angelview",exec_path.GetExt());
   m_file_paths[ConfigEnums::DXFVIEW]    = ConfigSaveRestore::DefaultDxfViewerPath();

   m_docurl = ConfigSaveRestore::DefaultDocUrl();
}

AngelCADDoc::~AngelCADDoc()
{
   //dtor
}

wxFileName AngelCADDoc::GetOutSubDir()
{
   return m_file_paths[ConfigEnums::AS_OUTSUB];
}

wxFileName AngelCADDoc::GetXcsgFileName(const wxFileName& source_file)
{
   // the template path is the input source file
   wxFileName xcsg_path(source_file);

   // outsub contains a directory path but no file name
   // AppendDir does not allow adding a full subpath, each must be added sequentially
   // GetDirs interprets the last component as a file name, so dirs will not contain the final leaf
   // We handle that using GetName at the end
   wxFileName outsub = GetOutSubDir();

   // if the spec is just a dot, it means no subdirectory
   if(outsub.GetFullPath() != ".") {
      wxArrayString dirs = outsub.GetDirs();
      for(size_t i=0; i<dirs.GetCount(); i++) {
         xcsg_path.AppendDir(dirs[i]);
      }
      xcsg_path.AppendDir(outsub.GetName());
   }

   // set the file extension as the finel step
   xcsg_path.SetExt("xcsg");

   return xcsg_path;
}

wxFileName AngelCADDoc::GetConfigFilePath(ConfigEnums::ExtFile file)
{
   return m_file_paths[file];
}

void AngelCADDoc::SetConfigFilePath(ConfigEnums::ExtFile file, const wxFileName& fname)
{
   if(fname.GetFullPath().length() > 0) {
      m_file_paths[file] = fname;
   }
}

bool AngelCADDoc::GetFileFormatFlag(wxString format)
{
   auto i = m_formats.find(format);
   if(i!=m_formats.end())return i->second;
   return false;
}

void AngelCADDoc::SetFileFormatFlag(wxString format, bool enabled)
{
   m_formats[format] = enabled;
}

void AngelCADDoc::RestoreConfig(ConfigSaveRestore& config_helper)
{
   bool save = false;
   config_helper.SaveRestoreWindowSize(save);
   config_helper.SaveRestoreExternalFiles(m_file_paths,save);
   config_helper.SaveRestoreFormats(m_formats,save);
   config_helper.SaveRestoreSaveDir(m_savedir,save);
   config_helper.SaveRestoreDocURL(m_docurl,save);
   int i = 0;
}

void AngelCADDoc::SaveConfig(ConfigSaveRestore& config_helper)
{
   bool save = true;
   config_helper.SaveRestoreWindowSize(save);
   config_helper.SaveRestoreExternalFiles(m_file_paths,save);
   config_helper.SaveRestoreFormats(m_formats,save);
   config_helper.SaveRestoreSaveDir(m_savedir,save);
   config_helper.SaveRestoreDocURL(m_docurl,save);
}

wxString AngelCADDoc::GetXcsgFormatOptionString()
{
   wxString options;
   for(auto p : m_formats) {
      if(p.second) options += " --"+p.first;
   }
   options += " --fullpath";
   return options;
}

void AngelCADDoc::SetSaveDir(wxString savedir)
{
   m_savedir = savedir;
}

wxString AngelCADDoc::GetSaveDir() const
{
   return m_savedir;
}

void AngelCADDoc::SetDocUrl(wxString url)
{
   m_docurl = url;
}

wxString AngelCADDoc::GetDocUrl() const
{
   return m_docurl;
}

