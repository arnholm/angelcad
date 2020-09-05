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

#ifndef WXBITMAPLIBRARY_H
#define WXBITMAPLIBRARY_H

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <map>

// wxBitmapLibrary allows for storing a collection of named bitmaps
// and returing each as either wxBitmap or wxIcon.
// By ingeriting from this class and including XPM files, a custom
// library can be established with a single place for the XPM file #includes

class wxBitmapLibrary {
public:
   wxBitmapLibrary();
   virtual ~wxBitmapLibrary();

   virtual void LoadBitmaps() = 0;

   void  AddBitmap(const wxString& name, const wxBitmap& bm);

   // return a named bitmap
   const wxBitmap& GetBitmap(const wxString& name) const;

   // return a bitmap as an icon copy
   wxIcon GetIcon(const wxString& name) const;

   // call clear to release memory when no more bitmaps are required
   void clear();

private:
   std::map<wxString,wxBitmap> m_bitmaps;
};

#endif // WXBITMAPLIBRARY_H
