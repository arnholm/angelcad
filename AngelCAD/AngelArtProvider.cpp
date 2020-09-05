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

#include "AngelArtProvider.h"

#include "images/std/wxSTD_NEW.xpm"
#include "images/std/wxSTD_FILE_OPEN.xpm"
#include "images/std/wxSTD_FILE_SAVE.xpm"
#include "images/std/wxSTD_FILE_SAVE_AS.xpm"
#include "images/std/wxSTD_FLOPPY.xpm"
#include "images/std/wxSTD_GO_FORWARD.xpm"
#include "images/std/wxSTD_KILL.xpm"
#include "images/std/wxSTD_CUBE.xpm"

#include "images/std/wxSTD_ERROR.xpm"

AngelArtProvider::AngelArtProvider()
{}

AngelArtProvider::~AngelArtProvider()
{
   //dtor
}

wxBitmap AngelArtProvider::CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size)
{
   if(id == "wxSTD_NEW")return wxBitmap(wxSTD_NEW_xpm);
   else if(id == "wxSTD_FILE_OPEN")return wxBitmap(wxSTD_FILE_OPEN_xpm);
   else if(id == "wxSTD_FILE_SAVE")return wxBitmap(wxSTD_FILE_SAVE_xpm);
   else if(id == "wxSTD_FILE_SAVE_AS")return wxBitmap(wxSTD_FILE_SAVE_AS_xpm);
   else if(id == "wxSTD_FLOPPY")return wxBitmap(wxSTD_FLOPPY_xpm);
   else if(id == "wxSTD_GO_FORWARD")return wxBitmap(wxSTD_GO_FORWARD_xpm);
   else if(id == "wxSTD_KILL")return wxBitmap(wxSTD_KILL_xpm);
   else if(id == "wxSTD_CUBE")return wxBitmap(wxSTD_CUBE_xpm);
   return wxBitmap(wxSTD_ERROR_xpm);
}
