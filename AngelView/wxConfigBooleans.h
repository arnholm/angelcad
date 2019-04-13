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
   
#ifndef WXCONFIGBOOLEANS_H
#define WXCONFIGBOOLEANS_H

#include <wx/string.h>
#include <map>

class wxConfigBooleans {
public:
   wxConfigBooleans();
   virtual ~wxConfigBooleans();

   typedef std::map<wxString,bool> FlagMap;
   typedef FlagMap::iterator iterator;

   void SetFlag(wxString name, bool value);
   bool GetFlag(wxString name);

   iterator begin() { return m_flags.begin(); }
   iterator end()   { return m_flags.end(); }
protected:

private:
   FlagMap m_flags;
};

#endif // WXCONFIGBOOLEANS_H
