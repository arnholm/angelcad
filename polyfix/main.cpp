#include <iostream>
#include <iomanip>
using namespace std;

#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>
#include "wxZipFile.h"

#include <wx/string.h>   // wxString
#include <wx/filefn.h>   // File Functions
#include <wx/filename.h> // wxFileName
#include <wx/cmdline.h>  // command line parser
#include <boost/lexical_cast.hpp>

#include "spaceio/amf_io.h"
#include "spaceio/stl_io.h"
#include "spaceio/off_io.h"
#include "spaceio/obj_io.h"
#include "polyhealer/polyhealer.h"
#include "polyhealer/polyremesh.h"


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

double dist_tol    = 1.0E-2;  // coordinate tolerance in mm
double area_tol    = 1.0E-6;  // area tolerance in mm^2
size_t maxiter     = 10;      // max iterations

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
  //   kind           shortName              longName              description                                                    parameterType          flag(s)
  { wxCMD_LINE_PARAM,  wxT_2("input_file"),  wxT_2("input_file"),  wxT_2("<input_filename>"),                                     wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },
  { wxCMD_LINE_PARAM,  wxT_2("output_file"), wxT_2("output_file"), wxT_2("<output_filename>"),                                    wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("astl"),        wxT_2("astl"),        wxT_2("Save to ASCII STL (def=binary)"),                       wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("verbose"),     wxT_2("verbose"),     wxT_2("Verbose messages"),                                     wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("zip"),         wxT_2("zip"),         wxT_2("Store output in compressed zip file"),                  wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },

  { wxCMD_LINE_OPTION, wxT_2("maxiter"),     wxT_2("maxiter"),     wxT_2("[heal]  \tMax iterations (def=10)"),                    wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_OPTION, wxT_2("dtol"),        wxT_2("dtol"),        wxT_2("[heal]  \tDistance tolerance (def=1.0E-2)"),            wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_OPTION, wxT_2("atol"),        wxT_2("atol"),        wxT_2("[heal]  \tArea tolerance (def=1.0E-6)"),                wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("lumps"),       wxT_2("lumps"),       wxT_2("[heal]  \tSplit into lumps (stored only in AMF)"),      wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("nflip"),       wxT_2("nflip"),       wxT_2("[heal]  \tFlip faces with inward normals"),             wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },

  { wxCMD_LINE_OPTION, wxT_2("remesh"),      wxT_2("remesh"),      wxT_2("[remesh]\tRemesh surfaces to given edge length (set dtol=~1.E-6)"),       wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("noaflip"),     wxT_2("noaflip"),     wxT_2("[remesh]\tDo not perform aspect ratio edge flipping"),  wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_NONE,   wxT_2(""),            wxT_2(""),            wxT_2(""),                                                     wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  }
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

   cout << endl << "Parameters:"<< endl;
   for(auto& p : cmdMap) {
      cout << setw(12) << p.first << " = " << p.second << endl;
   }
   cout << endl;


   try {


      string out_ext         = "stl";
      bool   stl_binary      = true;
      bool   remesh          = false;
      double remesh_edge_len = 40;

      wxFileName fname_in    = cmdMap[wxT("input_file")];

      if(cmdMap.find("astl") != cmdMap.end()) {
         out_ext    = "stl";
         stl_binary = false;
      }
      bool verbose       = (cmdMap.find("verbose") != cmdMap.end());
      bool lump_analysis = (cmdMap.find("lumps") != cmdMap.end());
      bool flip_faces    = (cmdMap.find("nflip") != cmdMap.end());
      if(flip_faces) {
         lump_analysis = true;
      }
      bool aspect_flip   = (cmdMap.find("noaflip") == cmdMap.end());
      bool zip_compress  = (cmdMap.find("zip") != cmdMap.end());

      // set the default output_file_name
      wxFileName fname_out   = fname_in;
      fname_out.SetName(fname_out.GetName()+"_polyfix");
      fname_out.SetExt(out_ext);
      auto it_out = cmdMap.find("output_file");
      if(it_out != cmdMap.end()) {
         fname_out = it_out->second;
      }

      // switch on compression if output file type is zip
      std::string ext = fname_out.GetExt().ToStdString();
      std::transform(ext.begin(),ext.end(),ext.begin(),::tolower);
      if(ext == "zip") {
         zip_compress = true;
         fname_out.SetExt("stl");
      }

      std::string input_file = fname_in.GetFullPath().ToStdString();
      auto it_dtol = cmdMap.find("dtol");
      if(it_dtol != cmdMap.end()) {
         std::string stol = (it_dtol->second).ToStdString();
         dist_tol =  boost::lexical_cast<double>(stol);
      }

      auto it_atol = cmdMap.find("atol");
      if(it_atol != cmdMap.end()) {
         std::string stol = (it_atol->second).ToStdString();
         area_tol =  boost::lexical_cast<double>(stol);
      }

      auto it_maxiter = cmdMap.find("maxiter");
      if(it_maxiter != cmdMap.end()) {
         std::string stol = (it_maxiter->second).ToStdString();
         maxiter =  boost::lexical_cast<size_t>(stol);
      }

      auto it = cmdMap.find("remesh");
      if(it != cmdMap.end()) {
         remesh = true;
         string sval = (it->second).ToStdString();
         try {
            if(sval.length()>0)remesh_edge_len =  boost::lexical_cast<double>(sval);
         }
         catch(std::exception& ex) {
            cout << "Error: "<< ex.what() << endl;
            cout << "Error: remesh parameter value is invalid: -remesh=" << sval << "  (use e.g. -remesh=40.0)" << endl;
            return 1;
         }
      }

      std::shared_ptr<ph3d_vector> lumps(new ph3d_vector);   // lumps used when splitting all into lumps
      std::shared_ptr<ph3d_vector> polyset;

           if(spaceio::amf_io::is_amf(input_file)) polyset = spaceio::amf_io::read(input_file);
      else if(spaceio::stl_io::is_stl(input_file)) polyset = spaceio::stl_io::read(input_file);
      else if(spaceio::off_io::is_off(input_file)) polyset = spaceio::off_io::read(input_file);
      else if(spaceio::obj_io::is_obj(input_file)) polyset = spaceio::obj_io::read(input_file);
      else throw logic_error("File type not supported: " + input_file);

      std::vector<std::string> warning_summary(polyset->size());

      // used for offsetting output
      const string blanks = "             ";

      // traverse the polyhedra and remove unused vertices
      for(size_t ipoly=0; ipoly<polyset->size(); ipoly++) {

         std::shared_ptr<polyhedron3d> poly = (*polyset)[ipoly];
         polyhealer healer(poly,dist_tol,area_tol,verbose);

         cout << endl << "polyhedron " << ipoly << " ================= volume="<<poly->volume() << ", dtol=" << dist_tol << ", atol=" << area_tol << ", maxiter="<< maxiter;

         warning_summary[ipoly] = healer.run_healing(maxiter,cout);

         // split objeck into lumps
         if(lump_analysis) {

            cout << endl << "Lump analysis: " << endl;
            std::shared_ptr<ph3d_vector> poly_lumps = healer.find_lumps(flip_faces);
            for(auto msg : healer) {
               cout << blanks << msg << endl;
            }

            // transfer to lumps vector
            for(auto lump : *poly_lumps) lumps->push_back(lump);
         }
      }

      // write the lumps if lump analysis requested
      if(lump_analysis) polyset = lumps;

      if(remesh) {
         for(size_t ipoly=0; ipoly<polyset->size(); ipoly++) {
            std::shared_ptr<polyhedron3d> poly = (*polyset)[ipoly];
            cout << blanks << "remeshing surface ... " << std::flush;
            polyremesh surf_mesh(poly,dist_tol,remesh_edge_len);
            surf_mesh.flip_split();
            if(aspect_flip)surf_mesh.aspect_ratio_flip();
            cout << poly->vertex_size() << " vertices, " <<  poly->face_size() << " faces" << std::endl;
         }
      }

      cout << endl << "Summary: ";
      for(size_t ipoly=0; ipoly<polyset->size(); ipoly++) {
         std::shared_ptr<polyhedron3d> poly = (*polyset)[ipoly];
         cout << endl << blanks << "polyhedron " << ipoly <<": vertices=" << poly->vertex_size() << " faces="<<poly->face_size();
         if(!lump_analysis) cout << " : " << warning_summary[ipoly];
      }

      cout << endl;
      cout << endl << "Writing: ";
      std::string target_file = fname_out.GetFullPath().ToStdString();
           if(spaceio::amf_io::is_amf(target_file)) target_file = spaceio::amf_io::write(polyset,fname_out.GetFullPath().ToStdString());
      else if(spaceio::off_io::is_off(target_file)) target_file = spaceio::off_io::write(polyset,fname_out.GetFullPath().ToStdString());
      else if(spaceio::obj_io::is_obj(target_file)) target_file = spaceio::obj_io::write(polyset,fname_out.GetFullPath().ToStdString());
      else                                          target_file = spaceio::stl_io::write(polyset,fname_out.GetFullPath().ToStdString(),stl_binary);

      if(zip_compress) {

         // create a zip file with just the single file
         wxFileName zipname(target_file);
         zipname.SetExt("zip");
         wxZipFile zipfile(zipname);

         bool remove_original = true;
         bool full_path = false;
         zipfile.AddFileEntry(target_file,full_path,remove_original);

         // set the new target name
         target_file = zipfile.FileName().GetFullPath().ToStdString();
      }
      cout << target_file;
      cout << endl;
   }
   catch(std::exception& ex) {
      cout << "Error: " << ex.what() << endl;
   }

   wxDateTime time_end  = wxDateTime::Now();
   wxTimeSpan time_used = time_end.Subtract(time_begin);

   cout << endl << "... abm_polyfix finished, time used: " << time_used.Format(wxT("%Dd %Hh %Mm %Ss")).ToStdString() << endl;

   return 0;
}


