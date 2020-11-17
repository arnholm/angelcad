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
#include <wx/filefn.h>   // File Functions
#include "spaceio/off_io.h"
#include "wxProcessSync.h"
#include "AngelCADDoc.h"

CsgFilter::CsgFilter(ConsolePanel* console, const wxFileName& csg)
: m_console(console)
, m_csg(csg)
, m_line_number(0)
, m_working_dir(wxFileName::GetCwd())
{}

CsgFilter::~CsgFilter()
{
   // reset working directory to what it was prior to call
   wxSetWorkingDirectory(m_working_dir);
}


void CsgFilter::run(AngelCADEditor* page )
{
   wxFileName pfix = DOC()->GetConfigFilePath(ConfigEnums::POLYFIX);
   bool have_pfix = pfix.Exists();

   // temporary files we create here are recorded and erased at the end
   std::set<wxString> tmp_files;

   // temporary file name of filtered output csg
   wxFileName out_csg(m_csg);
   out_csg.SetName(m_csg.GetName()+"_filtered");

   // line number in input csg
   m_line_number = 0;

   std::ifstream in(m_csg.GetFullPath().ToStdString());
   if(in.is_open()) {

      try {
         // open the output (filtered) csg
         std::ofstream out(out_csg.GetFullPath().ToStdString());

         // read the input csg line by line
         std::string line;
         while(std::getline(in,line)) {

            // increment the input line number (useful in error reporting)
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

                  // change the current working directory so that relative paths may work
                  wxSetWorkingDirectory(scad_path.GetPath());

                  // check if the ferenced file actually exists
                  wxFileName fname(filename);
                  fname.Normalize();

                  if(fname.Exists()) {

                     wxString ext = fname.GetExt().MakeLower();
                     if(have_pfix && ext == "stl") {

                        // run polyfix, overwriting any existing file with same name
                        wxString cmd = "\"" + pfix.GetFullPath() + "\"  \"" + fname.GetFullPath();
                        fname.SetExt("off");
                        cmd += "\" -overwrite -out=\""+fname.GetFullPath() + "\"";

                        // run polyfix synchronously to create OFF
                        wxProcessSync polyfix;
                        polyfix.Execute(m_console,cmd,scad_path.GetPath());

                        // read the file and put it in the tmp_files set
                        pvec = spaceio::off_io::read(fname.GetFullPath().ToStdString());
                        tmp_files.insert(fname.GetFullPath());
                     }
                     else if(ext == "off" ) {
                        pvec = spaceio::off_io::read(fname.GetFullPath().ToStdString());
                     }

                     if(pvec.get()) {
                        it = m_files.insert(std::make_pair(filename,poly_string(pvec))).first;
                     }
                  }
               }

               if(it != m_files.end()) {
                  // output the substitute statement
                  out << line.substr(0,imp) << ' ' << it->second << std::endl;
               }
               else {
                  // we could not resolve the file, so we just copy the input line
                  out << line << std::endl;
               }
            }
            else {
               // not an import statement
               out << line << std::endl;
            }
         }
      }
      catch(std::exception& ex) {
         // something bad happened here,
         // we just clear the files buffer and give up silently
         // so that we use the original .csg input file instead
         std::string msg = ex.what();
         m_files.clear();
      }
   }

   // close input file so that file copy can work
   in.close();

   if(m_files.size() > 0 && out_csg.Exists()) {
      // we did find import statements, so we use the filtered .csg
      wxRenameFile(out_csg.GetFullPath(),m_csg.GetFullPath(),true);
   }
   else {
      if(out_csg.Exists())wxRemoveFile(out_csg.GetFullPath());
   }

   // flush messages
   m_console->DisplayTextFromWorker();

   // reset original working directory
   wxSetWorkingDirectory(m_working_dir);

   // delete any temporary files we created
   for(auto f : tmp_files)  wxRemoveFile(f);
}


std::string CsgFilter::poly_string(std::shared_ptr<ph3d_vector> pvec)
{
   using namespace spacemath;
   std::string retval;

   if(pvec && pvec->size()>0) {
      std::shared_ptr<polyhedron3d> poly = (*pvec)[0];

      int prec = 9;

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

            // OpenSCAD uses reverse face vertex ordering, so we reverse it here
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

      retval = out.str();
   }
   return retval;
}
