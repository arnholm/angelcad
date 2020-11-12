#include "CsgFilter.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <wx/string.h>
#include <wx/utils.h>
#include "spaceio/off_io.h"

#include "AngelCADDoc.h"


CsgFilter::CsgFilter(ConsolePanel* console, const wxFileName& csg)
: m_console(console)
, m_csg(csg)
, m_line_number(0)
{}

CsgFilter::~CsgFilter()
{}


void CsgFilter::run(AngelCADEditor* page )
{
   wxFileName pfix = DOC()->GetConfigFilePath(ConfigEnums::POLYFIX);
   bool have_pfix = pfix.Exists();

   std::set<wxString> tmp_files;

   // we have to make sure the csg file is closed
   wxMilliSleep(200);

   wxFileName out_csg(m_csg);
   out_csg.SetExt("csg2");

   m_line_number = 0;
   std::ifstream in(m_csg.GetFullPath().ToStdString());
   if(in.is_open()) {

      std::ofstream out(out_csg.GetFullPath().ToStdString());

      // read the file line by line
      std::string line;
      while(std::getline(in,line)) {

         // increment the line number (useful in error reporting)
         m_line_number++;

         size_t imp = line.find("import(file");
         if(imp != std::string::npos) {

            // this is an import statement

            // extract the filename of the file to be imported
            size_t left  = line.find("\"",imp) + 1;
            size_t right = line.find("\"",left);
            size_t len   = right-left;
            std::string filename = line.substr(left,len);

            // will convert the file to polyhedron
            std::shared_ptr<ph3d_vector> pvec;

            // check if this file has already been processed
            auto it=m_files.find(filename);
            if(it == m_files.end()) {

               // the imported file is relative to the scad path
               wxFileName scad_path=page->FileName();
               wxFileName fname(filename);
               fname.SetPath(scad_path.GetPath());

               wxString ext = fname.GetExt().MakeLower();
               if(have_pfix && ext == "stl") {

                  // run polyfix, overwriting any existing file with same name
                  wxString cmd = "\"" + pfix.GetFullPath() + "\"  \"" + fname.GetFullPath();
                  fname.SetExt("off");
                  cmd += "\" -overwrite -out=\""+fname.GetFullPath() + "\"";

                  // run polyfix to create OFF
                  std::list<ConsolePanel::JobPair> job;
                  job.push_back(std::make_pair(cmd,page));
                  m_console->Execute(job);

                  // make some time available for the OFF file to close
                  wxMilliSleep(200);

                  // read the file and put it in the tmp_files set
                  pvec = spaceio::off_io::read(fname.GetFullPath().ToStdString());
                  tmp_files.insert(fname.GetFullPath());
               }
               else if(ext == "off" ) {
                  pvec = spaceio::off_io::read(fname.GetFullPath().ToStdString());
               }

               it = m_files.insert(std::make_pair(filename,poly_string(pvec))).first;
            }

            // output the substitute statement
            out << line.substr(0,imp) << ' ' << it->second << std::endl;
         }
         else {
            // not an import statement
            out << line << std::endl;
         }
      }
   }

   in.close();


  if(m_files.size() > 0) {
      // we did find import statements
      wxMilliSleep(200);
//      wxRemoveFile(m_csg.GetFullPath());
      wxCopyFile(out_csg.GetFullPath(),m_csg.GetFullPath(),true);
      wxRemoveFile(out_csg.GetFullPath());
  }

   // delete any temporary files we created
   for(auto f : tmp_files)  wxRemoveFile(f);
}


std::string CsgFilter::poly_string(std::shared_ptr<ph3d_vector> pvec)
{
   using namespace spacemath;

   std::shared_ptr<polyhedron3d> poly = (*pvec)[0];

   int prec = 8;

   std::ostringstream out;
   size_t nvert = poly->vertex_size();
   size_t nface = poly->face_size();

   out << "polyhedron( "; // << endl;
   out << "points=[ ";
      for(size_t ivert=0; ivert<nvert; ivert++) {
         const pos3d& pos = poly->vertex(ivert);
         if(ivert > 0) out << ',';
         out << '[' << std::setprecision(prec) << pos.x() << ',' << std::setprecision(prec) << pos.y() << ',' << std::setprecision(prec) << pos.z() << ']';
      }
   out << " ], ";// << endl;
   out << "faces=[ ";
      for(size_t iface=0; iface<nface; iface++) {
         pface face = poly->face(iface);

         // OpenSCAD uses reverse face ordering, so we reverse it here
         std::reverse(face.begin(),face.end());

         size_t nv = face.size();
         if(iface > 0) out << ',';
         out << '[';
         for(size_t iv=0; iv<nv; iv++) {
            if(iv>0) out<<',';
            out << face[iv];
         }
         out << ']';
      }
   out << " ] "; // << endl;
   out << " );";

   return out.str();
}
