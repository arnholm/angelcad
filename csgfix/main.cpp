#include <iostream>
using namespace std;

#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>

#include <wx/string.h>   // wxString
#include <wx/filefn.h>   // File Functions
#include <wx/filename.h> // wxFileName
#include <wx/cmdline.h>  // command line parser
#include "as_csg/version.h"

#include <map>
using namespace std;
typedef map<wxString,wxString> CmdLineMap;    // CmdLineMap

#include "csgfix.h"

/*
   switch 	  This is a boolean option which can be given or not, but which doesn't have any value.
              We use the word switch to distinguish such boolean options from more generic options
              like those described below. For example, -v might be a switch meaning "enable verbose mode".

   option 	  Option for us here is something which comes with a value unlike a switch.
              For example, -o:filename might be an option which allows to specify the name of the output file.

   parameter  This is a required program argument.

   More info at: http://docs.wxwidgets.org/2.8/wx_wxcmdlineparser.html#wxcmdlineparser

*/

double dist_tol    = 1.0E-2;  // coordinate tolerance in mm
double area_tol    = 1.0E-6;  // area tolerance in mm^2
size_t maxiter     = 10;      // max iterations

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
  //   kind           shortName         longName          description                               parameterType          flag(s)
  { wxCMD_LINE_OPTION, wxT_2("scad"),   wxT_2("scad"),    wxT_2("<scad_file>"),                     wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },
  { wxCMD_LINE_OPTION, wxT_2("csg"),    wxT_2("csg"),     wxT_2("<csg_file>"),                      wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },

  { wxCMD_LINE_OPTION, wxT_2("maxiter"),wxT_2("maxiter"), wxT_2("Max iterations (def=10)"),         wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_OPTION, wxT_2("dtol"),   wxT_2("dtol"),    wxT_2("Distance tolerance (def=1.0E-2)"), wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_OPTION, wxT_2("atol"),   wxT_2("atol"),    wxT_2("Area tolerance (def=1.0E-6)"),     wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("v"),      wxT_2("version"), wxT_2("Show version number only"),        wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL },

  { wxCMD_LINE_NONE,   wxT_2(""),       wxT_2(""),        wxT_2(""),                                wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  }
};


// sample command line params: --project=cpde_export  --target=W32_Debug --tdir=w32\bin\Debug\

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
   wxInitializer initializer(argc,argv);

   // parse command line
   wxCmdLineParser parser(cmdLineDesc);
   parser.SetSwitchChars(wxT("-"));
   parser.DisableLongOptions();
   parser.SetCmdLine(argc,argv);
   if(parser.Parse() != 0) {
      // command line parameter error
      return 1;
   }

   // parser success
   // convert parameters to map
   CmdLineMap cmdMap;
   ParserToMap(parser,cmdMap);
   wxDateTime time_begin = wxDateTime::Now();
   size_t error_count = 0;

   wxFileName scad(cmdMap["scad"]);
   if(!scad.Exists()) {
      cout << scad.GetFullPath() << " does not exist" << endl;
      error_count++;
   }

   wxFileName csg(cmdMap["csg"]);
   if(!csg.Exists()) {
      cout << csg.GetFullPath() << " does not exist" << endl;
      error_count++;
   }

   auto it_dtol = cmdMap.find("dtol");
   if(it_dtol != cmdMap.end()) {
      wxString stol = it_dtol->second;
      stol.ToCDouble(&dist_tol);
   }

   auto it_atol = cmdMap.find("atol");
   if(it_atol != cmdMap.end()) {
      wxString stol = it_atol->second;
      stol.ToCDouble(&area_tol);
   }

   auto it_maxiter = cmdMap.find("maxiter");
   if(it_maxiter != cmdMap.end()) {
      wxString stol = it_maxiter->second;
      long mxiter=maxiter;
      stol.ToLong(&mxiter);
      maxiter =  mxiter;
   }

   if(error_count> 0) return 1;

   csgfix fix(cout,scad,csg,maxiter,dist_tol,area_tol);
   fix.run();

   wxDateTime time_end  = wxDateTime::Now();
   wxTimeSpan time_used = time_end.Subtract(time_begin);

   cout << endl << "... csgfix finished, time used: " << time_used.Format(wxT("%Dd %Hh %Mm %Ss")).ToStdString() << endl;

   return 0;
}


