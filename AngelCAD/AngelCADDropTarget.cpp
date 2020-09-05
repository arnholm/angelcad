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

#include "AngelCADDropTarget.h"
#include "AngelCADMain.h"
#include <wx/filename.h>

AngelCADDropTarget::AngelCADDropTarget()
{}

AngelCADDropTarget::~AngelCADDropTarget()
{}

bool AngelCADDropTarget::OnDropFiles(wxCoord x, wxCoord y,  const wxArrayString& filenames)
{
   AngelCADFrame* frame = AngelCADFrame::singleton();

   size_t ncount = 0;
   if(frame) {
      size_t nfiles = filenames.GetCount();
      for(size_t i=0;i<nfiles; i++) {
         wxFileName filename(filenames[i]);
         if(frame->DoSourceFileOpen(filename.GetFullPath())) ncount++;
      }
   }
   return (ncount>0);
}
