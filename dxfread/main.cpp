#include <iostream>
#include <fstream>
using namespace std;

#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>

#include <wx/string.h>   // wxString
#include <wx/filefn.h>   // File Functions
#include <wx/filename.h> // wxFileName
#include <wx/cmdline.h>  // command line parser
#include <wx/dir.h>
#include <wx/tokenzr.h>

#include "dxfdom/dxfroot.h"
#include "dxfdom/dxfprofile.h"
#include "dxfdom/dxfprofileexport.h"
#include "as_csg/version.h"

#include <map>
using namespace std;
typedef map<wxString,wxString> CmdLineMap;    // CmdLineMap


/*
   switch 	  This is a boolean option which can be given or not, but which doesn't have any value.
              We use the word switch to distinguish such boolean options from more generic options
              like those described below. For example, -v might be a switch meaning "enable verbose mode".

   option 	  Option for us here is something which comes with a value unlike a switch.
              For example, -o:filename might be an option which allows to specify the name of the output file.

   parameter  This is a required program argument.

   More info at: http://docs.wxwidgets.org/2.8/wx_wxcmdlineparser.html#wxcmdlineparser

*/

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
  //   kind           shortName      longName         description                                               parameterType          flag(s)
  { wxCMD_LINE_PARAM,   wxT_2("dxfpath"), wxT_2("dxfpath"),  wxT_2("[path to DXF file]"),                        wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },
  { wxCMD_LINE_SWITCH,  wxT_2("xml"),        wxT_2("xml"),        wxT_2("Export as XML, interpreted entities only"),  wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH,  wxT_2("xraw"),       wxT_2("xraw"),       wxT_2("Export as XML, interpreted + raw DXF data"), wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH,  wxT_2("as"),         wxT_2("as"),         wxT_2("Export as AngelCAD *.as"),                   wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH,  wxT_2("asfunc"),     wxT_2("asfunc"),     wxT_2("Export as AngelCAD *.as function only"),     wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH,  wxT_2("scad"),       wxT_2("scad"),       wxT_2("Export as OpenSCAD *.scad"),                 wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH,  wxT_2("p2d"),        wxT_2("p2d"),        wxT_2("Export as profile *.p2d"),                   wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH,  wxT_2("auto_close"), wxT_2("auto_close"), wxT_2("Auto-close open loops"),                     wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_OPTION,  wxT_2("scale"),      wxT_2("scale"),      wxT_2("Coordinate scale factor [1.0]"),             wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_OPTION,  wxT_2("sectol"),     wxT_2("sectol"),     wxT_2("Secant tolerance [0.1*scale]"),              wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_OPTION,  wxT_2("layers"),     wxT_2("layers"),     wxT_2("Select from given DXF layer(s) only, separated by commas"),   wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH,  wxT_2("v"),          wxT_2("version"),    wxT_2("Show version number only"),                  wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_NONE,    wxT_2(""),           wxT_2(""),           wxT_2(""),                                                           wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  }
};

// sample command line params: --project=cpde_export  --target=W32_Debug --tdir=w32\bin\Debug\

void ParserToMap(wxCmdLineParser& parser, CmdLineMap& cmdMap)
{
   size_t pcount = sizeof(cmdLineDesc)/sizeof(wxCmdLineEntryDesc) - 1;
   for(size_t i=0; i<pcount; i++) {
      wxString pname = cmdLineDesc[i].longName;
      if(cmdLineDesc[i].kind == wxCMD_LINE_PARAM) {
         if(parser.GetParamCount()>0) cmdMap.insert(make_pair(pname,parser.GetParam(0)));
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
   wxInitializer initializer(argc,argv);

   // parse command line
   wxCmdLineParser parser(cmdLineDesc);
   parser.DisableLongOptions();
   parser.SetSwitchChars(wxT("-"));
   parser.SetCmdLine(argc,argv);
   if(parser.Parse() != 0) {
      // command line parameter error
      return 1;
   }

   // parser success
   // convert parameters to map
   CmdLineMap cmdMap;
   ParserToMap(parser,cmdMap);

   cout << "parser OK" << endl;

   wxFileName dxf_mask = cmdMap["dxfpath"];
   wxString path = dxf_mask.GetPath();
   wxString mask = dxf_mask.GetFullName();
   if(path.length() == 0) {
      path = wxGetCwd();
   }

   wxArrayString dxf_files;
   wxDir::GetAllFiles(path,&dxf_files,mask,wxDIR_FILES);
   size_t nfiles = dxf_files.GetCount();
   if(nfiles == 0) {
      cout << "No such file(s): " <<  dxf_mask.GetFullPath().ToStdString() << endl;
      return 1;
   }

   double scale_factor = 1.0;
   if(cmdMap.find("scale") != cmdMap.end()) {
      cmdMap["scale"].ToCDouble(&scale_factor);
   }

   double sectol = 0.1*scale_factor;
   if(cmdMap.find("sectol") != cmdMap.end()) {
      cmdMap["sectol"].ToCDouble(&sectol);
   }

   std::set<string> layers;
   if(cmdMap.find("layers") != cmdMap.end()) {
      wxStringTokenizer tokenizer(cmdMap["layers"], ";,");
      while ( tokenizer.HasMoreTokens() ) {
         layers.insert(tokenizer.GetNextToken().ToStdString());
      }
   }

   bool include_raw = cmdMap.find("xraw")        != cmdMap.end();
   bool export_xml  = (cmdMap.find("xml")        != cmdMap.end()) || include_raw;
   bool export_as   = (cmdMap.find("as")         != cmdMap.end()) || (cmdMap.find("asfunc")   != cmdMap.end());
   bool func_only   = (cmdMap.find("asfunc")     != cmdMap.end());
   bool export_scad = (cmdMap.find("scad")       != cmdMap.end());
   bool export_p2d  = (cmdMap.find("p2d")        != cmdMap.end());
   bool auto_close  = (cmdMap.find("auto_close") != cmdMap.end());


   for(size_t i=0; i<nfiles; i++) {

      wxFileName dxfpath(dxf_files[i]);
      string path = dxfpath.GetFullPath().ToStdString();

      wxString ext = dxfpath.GetExt().Lower();
      if(ext != "dxf") {
         cout << "ignored (not dxf): " << path << endl;
         continue;
      }

      try {

         cout << "reading dxf: " << path << endl;

         double epspnt = 1.0E-3*scale_factor;
         bool keep_case = false;
         dxfxmloptions opt(include_raw,scale_factor,sectol,epspnt,layers,keep_case);
         opt.set_auto_close(auto_close);

         ifstream in(path);
         shared_ptr<dxfroot> root = make_shared<dxfroot>(in,opt);
         int nfiles=0;

         cout << "Layers: ";
         for(auto i=root->layer_begin(); i!=root->layer_end(); i++) cout << ' ' << *i;
         cout << endl;


         cout << " building xml " << endl;
         root->build_xml();

         if(export_xml) {
            wxFileName path(dxfpath);
            path.SetExt("xml");
            string out_path = path.GetFullPath().ToStdString();
            root->tree().write_xml(out_path);
            cout << " wrote: " << out_path << endl;
            nfiles++;
         }

         cout << " building profile loops " << endl;
         root->build_profile();
         shared_ptr<dxfprofile> prof = root->profile();

         if(prof->size() > 0) {
            dxfprofileexport exp;
            if(export_p2d) {
               wxFileName path(dxfpath);
               path.SetExt("p2d");
               exp.export_p2d(*prof,path.GetFullPath().ToStdString());
               cout << " wrote: " << path.GetFullPath().ToStdString() << endl;
               nfiles++;
            }
            if(export_as) {
               wxFileName path(dxfpath);
               path.SetExt("as");
               exp.export_as(*prof,path.GetFullPath().ToStdString(),func_only);
               cout << " wrote: " << path.GetFullPath().ToStdString() << " (AngelCAD)" << endl;
               nfiles++;
            }
            if(export_scad) {
               wxFileName path(dxfpath);
               path.SetExt("scad");
               exp.export_scad(*prof,path.GetFullPath().ToStdString());
               cout << " wrote: " << path.GetFullPath().ToStdString() << " (OpenSCAD)"<< endl;
               nfiles++;
            }
         }

         cout << " Wrote " << nfiles << " file(s)" << endl;
         if(prof->size() == 0) {
            cout << " Warning: Computed profile contains no loops, only XML can be exported. Check layer name if specified." << endl;
         }
      }
      catch(std::exception& ex) {
         cout << endl << "Error: " << ex.what() << endl;
         cout << "... skipping " << dxfpath.GetFullPath() << endl << endl;
      }
   }

   return 0;
}


