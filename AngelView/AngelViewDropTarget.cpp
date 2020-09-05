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

#include "AngelViewDropTarget.h"
#include "AngelViewMain.h"
#include <wx/filename.h>

AngelViewDropTarget::AngelViewDropTarget()
{
   //ctor
}

AngelViewDropTarget::~AngelViewDropTarget()
{
   //dtor
}

bool AngelViewDropTarget::OnDropFiles(wxCoord x, wxCoord y,  const wxArrayString& filenames)
{
   AngelViewFrame* frame = AngelViewFrame::singleton();

   size_t nfiles = filenames.GetCount();
   for(size_t ifile=0; ifile<nfiles; ifile++) {

      wxFileName fname(filenames[ifile]);
      if(fname.GetExt()=="stl" || fname.GetExt()=="amf" || fname.GetExt()=="obj" || fname.GetExt()=="off" ) {
         frame->DoFileOpen(fname,true);
         return true;
      }
   }
   return false;
}
