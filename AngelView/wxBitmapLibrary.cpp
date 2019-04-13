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
   
#include "wxBitmapLibrary.h"

wxBitmapLibrary::wxBitmapLibrary()
{}

wxBitmapLibrary::~wxBitmapLibrary()
{
   clear();
}

void wxBitmapLibrary::AddBitmap(const wxString& name, const wxBitmap& bm)
{
   if(m_bitmaps.find(name) != m_bitmaps.end()) throw std::logic_error("wxBitmapLibrary, Bitmap already exists: " + name.ToStdString());
   m_bitmaps.insert(std::make_pair(name,bm));
}

const wxBitmap& wxBitmapLibrary::GetBitmap(const wxString& name) const
{
   auto i = m_bitmaps.find(name);
   if(i == m_bitmaps.end()) throw std::logic_error("wxBitmapLibrary, Bitmap does not exist: " + name.ToStdString());
   return i->second;
}

wxIcon wxBitmapLibrary::GetIcon(const wxString& name) const
{
   wxIcon icon;
   icon.CopyFromBitmap(GetBitmap(name));
   return icon;
}

void wxBitmapLibrary::clear()
{
   m_bitmaps.clear();
}
