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
   
/***************************************************************
 * Name:      AngelViewApp.h
 * Purpose:   Defines Application Class
 * Author:    cpde template ()
 * Created:   2012-07-19
 * Copyright: cpde template ()
 * License:
 **************************************************************/

#ifndef ANGELVIEWAPP_H
#define ANGELVIEWAPP_H

#include <wx/app.h>
#include <wx/cmdline.h>
#include "AngelGLUIContext.h"
#include "PolyhedronGL.h"
class wxGLUICanvas;

#include <map>
using namespace std;
typedef map<wxString,wxString> CmdLineMap;

class AngelViewApp : public wxApp{
public:
   virtual bool OnInit();

   AngelGLUIContext* GetContext(wxGLUICanvas* canvas);
   PolyhedronGL&     GetModel() { return m_model; }
   wxFileName        GetCmdLineFileName() { return m_filename; }

   virtual void OnInitCmdLine(wxCmdLineParser& parser);
   virtual bool OnCmdLineParsed(wxCmdLineParser& parser);

private:
   CmdLineMap              m_CmdMap;
   PolyhedronGL            m_model;
   AngelGLUIContext*       m_context;
   wxFileName              m_filename;  // command line specified filename
};

// the magic that will make wxGetApp work
DECLARE_APP(AngelViewApp);

#endif // ANGELVIEWAPP_H
