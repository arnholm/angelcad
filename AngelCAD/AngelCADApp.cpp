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
 * Name:      AngelCADApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Carsten Arnholm
 * Created:   2016-12-25
 * Copyright: Carsten Arnholm
 * License:
 **************************************************************/

#include "AngelCADApp.h"
#include "AngelCADDoc.h"

//(*AppHeaders
#include "AngelCADMain.h"
#include <wx/image.h>
//*)

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
  //   kind            shortName      longName       description                 parameterType          flag(s)
  { wxCMD_LINE_PARAM,   wxT_2("input_file"),   wxT_2("input_file"),   wxT_2("<input_filename>"),       wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_NONE,    wxT_2(""),             wxT_2(""),             wxT_2(""),                       wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  }
};


void ParserToMap(wxCmdLineParser& parser, CmdLineMap& cmdMap)
{

   size_t pcount = sizeof(cmdLineDesc)/sizeof(wxCmdLineEntryDesc) - 1;
   for(size_t i=0; i<pcount; i++) {
      wxString pname = cmdLineDesc[i].longName;
      if(cmdLineDesc[i].kind == wxCMD_LINE_PARAM) {
         if(parser.GetParamCount()>0) {
            cmdMap.insert(make_pair(pname,parser.GetParam(0)));
         }
      }
      else {
         // switch or option, mush check if present
         if(parser.Found(pname)) {
            wxString pvalue;
            if(cmdLineDesc[i].type == wxCMD_LINE_VAL_STRING) {

               parser.Found(pname,&pvalue);
            }
            else if(cmdLineDesc[i].type == wxCMD_LINE_VAL_NUMBER) {
               long lvalue=0;
               parser.Found(pname,&lvalue);
               pvalue.Printf(wxT("%i"),lvalue);
            }
            cmdMap.insert(make_pair(pname,pvalue));
         }
      }
   }
}



IMPLEMENT_APP(AngelCADApp);

bool AngelCADApp::OnInit()
{
   m_doc = new AngelCADDoc();

   // must call OnInit to trigger command line
   if (!wxApp::OnInit()) return false;

   //(*AppInitialize
   bool wxsOK = true;
   wxInitAllImageHandlers();
   if ( wxsOK )
   {
   	AngelCADFrame* Frame = new AngelCADFrame(0);
   	Frame->Show();
   	SetTopWindow(Frame);
   }
   //*)

   // open database, if any
   auto i = m_CmdMap.find("input_file");
   if(i != m_CmdMap.end()) AngelCADFrame::singleton()->DoSourceFileOpen(i->second,true);

   return wxsOK;
}


AngelCADApp::~AngelCADApp()
{
   delete m_doc;
}

void AngelCADApp::OnInitCmdLine(wxCmdLineParser& parser)
{
   parser.SetDesc (cmdLineDesc);
   // must refuse '/' as parameter starter or cannot use "/path" style paths
   parser.SetSwitchChars (wxT("-"));
}

bool AngelCADApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
   ParserToMap(parser,m_CmdMap);
   return true;
}
