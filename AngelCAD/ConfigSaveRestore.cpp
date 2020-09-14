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

#include "ConfigSaveRestore.h"
#include "wxConfigPath.h"
#include "wx/stdpaths.h"
#include <algorithm>

ConfigSaveRestore::ConfigSaveRestore(wxFrame* window, wxConfig* config)
: m_window(window)
, m_config(config)
{}

ConfigSaveRestore::~ConfigSaveRestore()
{}

void ConfigSaveRestore::SaveRestoreWindowSize(bool save)
{
   wxConfigPath path(m_config,"/MainFrame");
   if(save) {
      // position
      int PosX(0),PosY(0);
      m_window->GetScreenPosition(&PosX,&PosY);
      if(PosX > -1 && PosY > -1) {
         m_config->Write("PosX",PosX);
         m_config->Write("PosY",PosY);
      }

      // size
      int SizX(0),SizY(0);
      m_window->GetSize(&SizX,&SizY);
      if(SizX > 100 && SizY > 100) {
         m_config->Write("SizX",SizX);
         m_config->Write("SizY",SizY);
      }
   }
   else {

      bool pos_ok(false),size_ok(false);

      // position
      int PosX=0,PosY=0;
      if(m_config->Read("PosX",&PosX)
      && m_config->Read("PosY",&PosY)) {
         if(PosX > -1 && PosY > -1) {
            pos_ok = true;
         }
      }

      // size
      int SizX(0),SizY(0);
      if(m_config->Read("SizX",&SizX)
      && m_config->Read("SizY",&SizY)) {
         if(SizX > 100 && SizY > 100) {
            size_ok = true;
         }
      }

      if(pos_ok && size_ok) {
         m_window->SetSize(PosX,PosY,SizX,SizY);
      }
   }
}


void ConfigSaveRestore::SaveRestoreFormats(std::map<wxString,bool>& formats, bool save)
{
    wxConfigPath path(m_config,"/Formats");
    if(save) {
       for(auto fp : formats) {
          m_config->Write(fp.first,fp.second);
       }
    }
    else {
      // restore from config
       for(auto fp : formats) {
          bool value = fp.second;
          m_config->Read(fp.first,&value,fp.second);
          formats[fp.first] = value;
       }
    }
}

void ConfigSaveRestore::SaveRestoreExportDir(std::pair<bool,wxString>& dir, bool save)
{
   wxConfigPath path(m_config,"/Formats");
   if(save) {
      m_config->Write("enable_export_dir",dir.first);
      m_config->Write("export_dir",dir.second);
   }
   else {
      bool enable = dir.first;
      if(m_config->Read("enable_export_dir",&enable,dir.first)) dir.first = enable;

      wxString config_string = dir.second;
      if(m_config->Read("export_dir",&config_string,dir.second)) dir.second = config_string;
   }
}

void ConfigSaveRestore::SaveRestoreExternalFiles(std::map<ConfigEnums::ExtFile,wxFileName>& file_paths,bool save)
{
   wxConfigPath path(m_config,"/External");
   if(save) {
      m_config->Write("AS_CSG",     file_paths[ConfigEnums::AS_CSG].GetFullPath());
      m_config->Write("AS_OUTSUB",  file_paths[ConfigEnums::AS_OUTSUB].GetFullPath());
      m_config->Write("XCSG",       file_paths[ConfigEnums::XCSG].GetFullPath());
      m_config->Write("OPENSCAD",   file_paths[ConfigEnums::OPENSCAD].GetFullPath());
      m_config->Write("STLAMFVIEW", file_paths[ConfigEnums::STLAMFVIEW].GetFullPath());
      m_config->Write("DXFVIEW",    file_paths[ConfigEnums::DXFVIEW].GetFullPath());
      m_config->Write("DXFREADER",  file_paths[ConfigEnums::DXFREADER].GetFullPath());
   }
   else {

      // restore from config, possibly overriding program defaults

      wxString config_string;
      if(m_config->Read("AS_CSG",&config_string))     file_paths[ConfigEnums::AS_CSG] = config_string;
      if(m_config->Read("AS_OUTSUB",&config_string))  file_paths[ConfigEnums::AS_OUTSUB] = config_string;
      if(m_config->Read("XCSG",&config_string))       file_paths[ConfigEnums::XCSG] = config_string;
      if(m_config->Read("OPENSCAD",&config_string))   file_paths[ConfigEnums::OPENSCAD] = config_string;
      if(m_config->Read("STLAMFVIEW",&config_string)) file_paths[ConfigEnums::STLAMFVIEW] = config_string;
      if(m_config->Read("DXFVIEW",&config_string))    file_paths[ConfigEnums::DXFVIEW] = config_string;
      if(m_config->Read("DXFREADER",&config_string))  file_paths[ConfigEnums::DXFREADER] = config_string;
    }
}

void ConfigSaveRestore::SaveRestoreDocURL(wxString& url, bool save)
{
    wxConfigPath path(m_config,"/External");
    if(save) {
       m_config->Write("DOCURL",url);
    }
    else {
       wxString config_string;
       if(m_config->Read("DOCURL",&config_string,url)){
         url = config_string;
       }
    }
}

void ConfigSaveRestore::SaveRestoreFiles(std::vector<wxFileName>& files_open, size_t& index, bool save)
{
   const size_t max_files = 10;
   wxConfigPath path(m_config,"/OpenFiles");
   if(save) {
      size_t nfiles  = std::min(files_open.size(),max_files);
      size_t index_f = std::min(index,max_files-1);
      for(size_t i=0; i<max_files; i++) {
         wxString file_key = wxString::Format("OpenFile%d",(int)i);
         wxString file_path = (i<nfiles)? files_open[i].GetFullPath() : "";
         m_config->Write(file_key,file_path);
      }
      m_config->Write("ActiveFile",(long)index_f);
   }
   else {
      for(size_t i=0; i<max_files; i++) {
         wxString file_key = wxString::Format("OpenFile%d",(int)i);
         wxString config_string;
         if(m_config->Read(file_key,&config_string,"")) {
           if(config_string.Length() > 0) {
              files_open.push_back(wxFileName(config_string));
           }
         }
      }
      long config_index = 0;
      m_config->Read("ActiveFile",&config_index,config_index);
      index = config_index;
      if(index >= files_open.size()) index = 0;
   }

}

void ConfigSaveRestore::SaveRestoreSaveDir(wxString& savedir, bool save)
{
    wxConfigPath path(m_config,"/External");
    if(save) {
       m_config->Write("SAVEDIR",savedir);
    }
    else {
       wxString config_string;
       if(m_config->Read("SAVEDIR",&config_string,savedir)) savedir = config_string;
    }
}

void ConfigSaveRestore::SaveRestoreArguments(wxString& args, bool save)
{
    wxConfigPath path(m_config,"/External");
    if(save) {
       m_config->Write("ARGUMENTS",args);
    }
    else {
       wxString config_string;
       if(m_config->Read("ARGUMENTS",&config_string,args)) args = config_string;
    }
}

wxFileName ConfigSaveRestore::DefaultOpenScadPath()
{
   #if defined(__WXMSW__)
      return wxFileName("C:\\Program Files\\OpenSCAD\\openscad.exe");
   #else
      return wxFileName("/usr/bin/openscad");
   #endif
}

wxFileName ConfigSaveRestore::DefaultDxfViewerPath()
{
   #if defined(__WXMSW__)
      return wxFileName("C:\\Program Files (x86)\\LibreCAD\\librecad.exe");
   #else
      return wxFileName("/usr/bin/librecad");
   #endif
}

wxString ConfigSaveRestore::DefaultDocUrl()
{
  return wxString("https://arnholm.github.io/angelcad-docs/");
}



