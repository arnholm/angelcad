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
 * Name:      AngelViewApp.cpp
 * Purpose:   Code for Application Class
 * Author:    cpde template ()
 * Created:   2012-07-19
 * Copyright: cpde template ()
 * License:
 **************************************************************/

#include "AngelViewApp.h"
#include "AngelGLUIContext.h"
#include "wxGLUICanvas.h"

//(*AppHeaders
#include "AngelViewMain.h"
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




IMPLEMENT_APP(AngelViewApp);

bool AngelViewApp::OnInit()
{
   m_context = 0;

   // must call OnInit to trigger command line
   if (!wxApp::OnInit()) return false;

   // set input file, if any
   auto i = m_CmdMap.find("input_file");
   if(i != m_CmdMap.end()) {
      m_filename = i->second;
   }

   //(*AppInitialize
   bool wxsOK = true;
   wxInitAllImageHandlers();
   if ( wxsOK )
   {
   	AngelViewFrame* Frame = new AngelViewFrame(0);
   	Frame->Show();
   	SetTopWindow(Frame);
   }
   //*)

   return wxsOK;
}


AngelGLUIContext* AngelViewApp::GetContext(wxGLUICanvas* canvas)
{
   if (!m_context ) {
      // Create the OpenGL context for the first window which needs it:
      // subsequently created windows will all share the same context.
      m_context = new AngelGLUIContext(canvas);
   }
   m_context->SetCurrent(*canvas);
   return m_context;
}



void AngelViewApp::OnInitCmdLine(wxCmdLineParser& parser)
{
   parser.SetDesc (cmdLineDesc);
   // must refuse '/' as parameter starter or cannot use "/path" style paths
   parser.SetSwitchChars (wxT("-"));
}

bool AngelViewApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
   ParserToMap(parser,m_CmdMap);
   return true;
}
