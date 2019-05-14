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

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>

#include <wx/image.h>

#include <wx/string.h>   // wxString
#include <wx/filefn.h>   // File Functions
#include <wx/filename.h> // wxFileName
#include <wx/cmdline.h>  // command line parser
typedef map<wxString,wxString> CmdLineMap;    // CmdLineMap

#include "as_csg.h"
#include "version.h"
#include "as_document.h"
#include "ce_angelscript_ex/as_reftype.h"
#include "ce_angelscript_ex/as_xml.h"

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
  //   kind            shortName           longName                description                                    parameterType          flag(s)
  { wxCMD_LINE_PARAM,  wxT_2("input_file"),  wxT_2("input_file"),  wxT_2("<input_filename>"),                     wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY },
  { wxCMD_LINE_OPTION, wxT_2("include"),     wxT_2("include"),     wxT_2("optional library include path"),        wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_OPTION, wxT_2("outsub"),      wxT_2("outsub"),      wxT_2("optional output subdirectory"),         wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_SWITCH, wxT_2("r"),           wxT_2("refcount"),    wxT_2("Reference count logging"),              wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_SWITCH, wxT_2("doc"),         wxT_2("doc"),         wxT_2("Write 'angelcad.h'"),                   wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_OPTION, wxT_2("doxy"),        wxT_2("doxy"),        wxT_2("Write 'angelcad.h' with doxygen info"), wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_SWITCH, wxT_2("xmldoc"),      wxT_2("xmldoc"),      wxT_2("Create/update XML documentation"),      wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_SWITCH, wxT_2("h"),           wxT_2("help"),        wxT_2("Command line help"),                    wxCMD_LINE_VAL_NONE,   wxCMD_LINE_OPTION_HELP    },
  { wxCMD_LINE_SWITCH, wxT_2("v"),           wxT_2("version"),     wxT_2("Show version number only"),             wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_NONE,   wxT_2(""),            wxT_2(""),            wxT_2(""),                                     wxCMD_LINE_VAL_NONE  , wxCMD_LINE_PARAM_OPTIONAL }
};


void ParserToMap(wxCmdLineParser& parser, CmdLineMap& cmdMap)
{
   size_t pcount = sizeof(cmdLineDesc)/sizeof(wxCmdLineEntryDesc) - 1;
   size_t iparam=0;
   for(size_t i=0; i<pcount; i++) {
      wxString pname = cmdLineDesc[i].longName;
      if(cmdLineDesc[i].kind == wxCMD_LINE_PARAM) {
         if(iparam < parser.GetParamCount()) {
            cmdMap.insert(make_pair(pname,parser.GetParam(iparam++)));
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

int main(int argc, char **argv)
{
   // detect if -v option is provided before asking wxWidgets to parse, as this is a special case
   for(int i=1; i<argc; i++) {
      string arg(argv[i]);
      std::transform(arg.begin(),arg.end(),arg.begin(),::tolower);
      if(arg == "-v" || arg=="--version") {
         string version(AS_CSG_version);
         cout << version.substr(1) << endl;
         return 0;
      }
   }

   // initialise wxWidgets library
   wxInitializer initializer(argc,argv);;

   // parse command line
   wxCmdLineParser parser(cmdLineDesc);
   parser.DisableLongOptions();
   parser.SetSwitchChars(wxT("-"));
   parser.SetCmdLine(argc,argv);
   bool giveUsage = false;  // do not allow Parse to show the Usage string
   if(parser.Parse(giveUsage) != 0) {
      // command line parameter error
      cout << "asERR: command line parameter error. If file path contains blanks, use quotes."<< endl;
      cout << parser.GetUsageString().ToStdString();
      cout << "as_csg " << AS_CSG_version << endl;
      return 1;
   }
   // wxInitAllImageHandlers is required due to image2d
   wxInitAllImageHandlers();

   // convert parameters to map
   CmdLineMap cmdMap;
   ParserToMap(parser,cmdMap);
   bool has_input_file  = cmdMap.find("input_file")  != cmdMap.end();
   bool has_include     = cmdMap.find("include")  != cmdMap.end();
   bool has_outsub      = cmdMap.find("outsub") != cmdMap.end();
   bool has_refcount    = cmdMap.find("refcount") != cmdMap.end();
   bool has_doc         = cmdMap.find("doc") != cmdMap.end();
   bool has_doxy        = cmdMap.find("doxy") != cmdMap.end();
   bool has_xmldoc      = cmdMap.find("xmldoc") != cmdMap.end();
   bool has_version     = cmdMap.find("version") != cmdMap.end();
   if(has_doxy)has_doc = true;

   string include_path = "";
   if(has_include) {
      include_path = cmdMap["include"].ToStdString();
   }

   wxDateTime time_begin = wxDateTime::UNow();
   cout << "as_csg started." << endl;

   // set the default output precision, this will affect AngelScript cout as well
   cout.precision(12);

   int exit_status = 0;

   as_csg parser_csg;
   if(parser_csg.register_types()) {

      if(has_doc) {
         as_document doc(asF()->engine());

         if(has_doxy) {
            doc.read_doxy(cmdMap["doxy"].ToStdString());
         }

         string docfile = "angelcad.h";
         ofstream doc_out(docfile);
         doc.write_doc(doc_out);
         cout << "Created documentation file: " << docfile << endl;
      }
      else if(has_xmldoc) {

         // generate or opdate XML documentation

         wxFileName xmlFile("angelcad_xmldoc.xml");
         string xmlpath = xmlFile.GetFullPath().ToStdString();
         as_xml xml_doc("angelcad");
         if(xmlFile.Exists()) {
            // file already exists so readi it in
            ifstream in(xmlpath);
            xml_doc.read_xml(in);
            xml_doc.unverify();
         }

         // update or create XML doc from script engine data
         xml_doc.from_script_engine(asF()->engine());

         // export the updated XML file
         ofstream out(xmlpath);
         xml_doc.write_xml(out);
         cout << "Created xml file: " << xmlpath << endl;

         ofstream hfile(xml_doc.appnam()+".h");
         xml_doc.write_header(hfile);

      }

      as_reftype::decl_end();

      if(has_input_file) {

         asF()->SetEchoRef(has_refcount);

         string input_file = cmdMap[wxT("input_file")].ToStdString();
         string outsub     = (has_outsub)? cmdMap[wxT("outsub")].ToStdString() : "";

         // set current working directory so that file references behave as expected
         wxFileName fname(input_file);
         if(fname.GetPath().Length() == 0) {
            fname.SetPath(fname.GetCwd());
         }
         wxSetWorkingDirectory(fname.GetPath());
         input_file = fname.GetFullName().ToStdString();

         exit_status = parser_csg.run_script(input_file,include_path,outsub);
      }
   }
   // write any errors to console
   for(auto i = parser_csg.message_begin(); i != parser_csg.message_end(); i++) {
      cout << *i << endl;
   }

   wxDateTime time_end  = wxDateTime::UNow();
   wxTimeSpan time_used = time_end.Subtract(time_begin);

   cout << endl;
   cout << "as_csg " << AS_CSG_version << " finished, time used: " << time_used.Format(wxT("%Dd %Hh %Mm %S.%ls")) << endl;

   return exit_status;
}
