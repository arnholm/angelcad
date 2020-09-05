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

#ifndef ANGELFILESYSTEMWATCHER_H
#define ANGELFILESYSTEMWATCHER_H

#include <wx/fswatcher.h>

// AngelFileSystemWatcher a specialisation/adapter of wxFileSystemWatcher
// allowing a file to be defined for watching, but the actual start of the watch delayed.
// This is due to wxFileSystemWatcher requiring an event loop which may not be started
// when the file in question is a command line parameter.

// To solve this problem, the application can use a one-shot wxTimer at startup
// and call BeginWatch(); in the timer event handler, because then for sure there is an event loop.
// typically AngelFileSystemWatcher is a member of the Frame class

class AngelFileSystemWatcher {
public:
   AngelFileSystemWatcher();
   virtual ~AngelFileSystemWatcher();

   // call SetOwner() in application frame constructor
   void SetOwner(wxEvtHandler* owner);

   // call DefineWatchFile() when the file is opened, regardless of event loop
   void DefineWatchFile(const wxFileName& filename);

   // call BeginWatch() when the event loop is running, e.g. in a one-shot timer handler
   bool BeginWatch();

   // returns true if watch active
   bool IsWatching() { return (m_wx_watcher != 0); }

protected:

private:
   wxEvtHandler*         m_owner;
   wxFileName            m_filename;
   wxFileSystemWatcher*  m_wx_watcher;
};

#endif // ANGELFILESYSTEMWATCHER_H
