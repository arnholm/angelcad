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

#include "wxConfigBooleans.h"

wxConfigBooleans::wxConfigBooleans()
{}

wxConfigBooleans::~wxConfigBooleans()
{}


void wxConfigBooleans::SetFlag(wxString name, bool value)
{
   m_flags[name] = value;
}

bool wxConfigBooleans::GetFlag(wxString name)
{
   auto i = m_flags.find(name);
   if(i != m_flags.end()) return i->second;

   return false;
}
