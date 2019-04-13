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
   
#include "wxConfigSaveRestore.h"
#include "wxConfigPath.h"

wxConfigSaveRestore::wxConfigSaveRestore(wxFrame* window, wxConfig* config)
: m_window(window)
, m_config(config)
{}

wxConfigSaveRestore::~wxConfigSaveRestore()
{}

void wxConfigSaveRestore::SaveRestoreWindowSize(bool save)
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


void wxConfigSaveRestore::SaveRestoreFlags(bool save, wxConfigBooleans& flags)
{
   wxConfigPath path(m_config,"/Settings");
   for(auto& p : flags) {
      if(save) {
          m_config->Write(p.first,((p.second)? 1 : 0));
      }
      else {
          m_config->Read(p.first,&p.second,p.second);
      }
   }
}
