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
   
#ifndef ANGELARTPROVIDER_H
#define ANGELARTPROVIDER_H

#include <wx/artprov.h>
#include <set>
using namespace std;

class AngelArtProvider : public wxArtProvider {
public:
   AngelArtProvider();
   virtual ~AngelArtProvider();

protected:
   virtual wxBitmap CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size);
private:
   set<wxArtID> m_ids;
};

#endif // ANGELARTPROVIDER_H
