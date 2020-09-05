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

#ifndef WXCONFIGPATH_H
#define WXCONFIGPATH_H

#include <wx/string.h>
#include <wx/config.h>

class wxConfigPath {
public:
   wxConfigPath(wxConfig* config,const wxString& newPath);
   virtual ~wxConfigPath();

   wxString OldPath() const;
   wxString GetPath() const;  // the current path
protected:
private:
   wxConfig* m_config;
   wxString  m_oldPath;
};

#endif // WXCONFIGPATH_H
