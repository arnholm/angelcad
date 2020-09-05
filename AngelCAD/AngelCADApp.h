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

/***************************************************************
 * Name:      AngelCADApp.h
 * Purpose:   Defines Application Class
 * Author:    Carsten Arnholm
 * Created:   2016-12-25
 * Copyright: Carsten Arnholm
 * License:
 **************************************************************/

#ifndef ANGELCADAPP_H
#define ANGELCADAPP_H
#include <wx/cmdline.h>
#include <wx/app.h>
class AngelCADDoc;

#include <map>
using namespace std;
typedef map<wxString,wxString> CmdLineMap;

class AngelCADApp : public wxApp {
public:
   virtual ~AngelCADApp();
   virtual bool OnInit();

   virtual void OnInitCmdLine(wxCmdLineParser& parser);
   virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

private:
   AngelCADDoc* m_doc;
   CmdLineMap   m_CmdMap;
};

#endif // ANGELCADAPP_H
