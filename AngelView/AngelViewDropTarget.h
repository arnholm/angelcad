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

#ifndef ANGELVIEWDROPTARGET_H
#define ANGELVIEWDROPTARGET_H

#include <wx/dnd.h>


class AngelViewDropTarget : public wxFileDropTarget {
public:
   AngelViewDropTarget();
   virtual ~AngelViewDropTarget();
   bool OnDropFiles(wxCoord x, wxCoord y,  const wxArrayString& filenames);

};

#endif // ANGELVIEWDROPTARGET_H
