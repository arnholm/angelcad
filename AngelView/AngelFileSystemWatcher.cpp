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

#include "AngelFileSystemWatcher.h"

AngelFileSystemWatcher::AngelFileSystemWatcher()
: m_owner(0)
, m_wx_watcher(0)
{}

AngelFileSystemWatcher::~AngelFileSystemWatcher()
{
    delete m_wx_watcher;
}

void AngelFileSystemWatcher::SetOwner(wxEvtHandler* owner)
{
    m_owner = owner;
}

void AngelFileSystemWatcher::DefineWatchFile(const wxFileName& filename)
{
   if(m_filename != filename) {
      m_filename = filename;
      if(m_wx_watcher) {
         m_wx_watcher->RemoveAll();
         if(m_filename.GetFullPath().Length() > 0) {
            m_wx_watcher->Add(m_filename.GetPath(),wxFSW_EVENT_MODIFY);
         }
      }
   }
}

bool AngelFileSystemWatcher::BeginWatch()
{
   if(!m_wx_watcher) {
      if(m_filename.GetFullPath().Length() > 0) {
         if(m_filename.Exists()) {
            m_wx_watcher = new wxFileSystemWatcher(m_filename.GetPath(),wxFSW_EVENT_MODIFY);
            m_wx_watcher->SetOwner(m_owner);
            return true;
         }
      }
   }
   return false;
}
