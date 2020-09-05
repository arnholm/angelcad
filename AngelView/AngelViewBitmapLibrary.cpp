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

#include "AngelViewBitmapLibrary.h"


#include "images/angelview_16x16.xpm"
#include "images/angelview_32x32.xpm"
//#include "images/angelview_48x48.xpm"
#include "images/angelview_64x64.xpm"

#include "images/view_xneg.xpm"
#include "images/view_xpos.xpm"
#include "images/view_yneg.xpm"
#include "images/view_ypos.xpm"
#include "images/view_zneg.xpm"
#include "images/view_zpos.xpm"
#include "images/view_reset.xpm"

#include "images/show_filled.xpm"
#include "images/show_edges.xpm"
#include "images/show_backside.xpm"

#include "images/show_axes.xpm"
#include "images/show_markers.xpm"

#include "images/show_center.xpm"
#include "images/background.xpm"

#include "images/rotate_rmb.xpm"

#include "images/wxSTD_FILE_OPEN.xpm"

AngelViewBitmapLibrary::AngelViewBitmapLibrary()
{}

AngelViewBitmapLibrary::~AngelViewBitmapLibrary()
{
   //dtor
}

void AngelViewBitmapLibrary::LoadBitmaps()
{
   AddBitmap("angelview_16x16",wxBitmap(angelview_16x16_xpm));
   AddBitmap("angelview_32x32",wxBitmap(angelview_32x32_xpm));
  // AddBitmap("angelview_48x48",wxBitmap(angelview_48x48_xpm));
   AddBitmap("angelview_64x64",wxBitmap(angelview_64x64_xpm));

   AddBitmap("view_xneg",wxBitmap(view_xneg_xpm));
   AddBitmap("view_xpos",wxBitmap(view_xpos_xpm));
   AddBitmap("view_yneg",wxBitmap(view_yneg_xpm));
   AddBitmap("view_ypos",wxBitmap(view_ypos_xpm));
   AddBitmap("view_zneg",wxBitmap(view_zneg_xpm));
   AddBitmap("view_zpos",wxBitmap(view_zpos_xpm));
   AddBitmap("view_reset",wxBitmap(view_reset_xpm));

   AddBitmap("show_filled",wxBitmap(show_filled_xpm));
   AddBitmap("show_edges",wxBitmap(show_edges_xpm));
   AddBitmap("show_backside",wxBitmap(show_backside_xpm));

   AddBitmap("show_axes",wxBitmap(show_axes_xpm));
   AddBitmap("show_markers",wxBitmap(show_markers_xpm));
   AddBitmap("show_center",wxBitmap(show_center_xpm));

   AddBitmap("background",wxBitmap(background_xpm));

   AddBitmap("rmb_is_rotate",wxBitmap(rotate_rmb_xpm));

   AddBitmap("wxSTD_FILE_OPEN",wxBitmap(wxSTD_FILE_OPEN_xpm));
}
