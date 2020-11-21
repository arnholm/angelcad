#include "csgfix.h"
#include "spaceio/off_io.h"
#include "spaceio/stl_io.h"
#include "polyfix.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

csgfix::csgfix(std::ostream& out
              ,const wxFileName& scad
              ,const wxFileName& csg
              ,size_t maxiter
              ,double dist_tol
              ,double area_tol
              )
: m_out(out)
, m_scad(scad)
, m_csg(csg)
, m_maxiter(maxiter)
, m_dist_tol(dist_tol)
, m_area_tol(area_tol)
, m_line_number(0)
, m_working_dir(wxFileName::GetCwd())
{
   m_scad.Normalize();
   m_csg.Normalize();
}

csgfix::~csgfix()
{}

void csgfix::run()
{
   // temporary file name of filtered output csg
   wxFileName out_csg(m_csg);
   out_csg.SetName(m_csg.GetName()+"_filtered");
   out_csg.Normalize();

   // line number in input csg
   m_line_number = 0;

   std::ifstream in(m_csg.GetFullPath().ToStdString());
   if(in.is_open()) {

      try {
         // open the output (filtered) csg
         std::ofstream out(out_csg.GetFullPath().ToStdString());
         m_out << " " << std::endl;
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
                  // change the current working directory so that relative paths may work
                  wxSetWorkingDirectory(m_scad.GetPath());

                  // check if the ferenced file actually exists
                  wxFileName fname(filename);
                  fname.Normalize();

                  if(fname.Exists()) {

                     wxString ext = fname.GetExt().MakeLower();
                     if(ext == "stl") {

                        m_out << "csgfix processing " << fname.GetFullPath().ToStdString() << std::endl;

                        // read the file
                        pvec = spaceio::stl_io::read(fname.GetFullPath().ToStdString());

                        // run polyfix, it will modify pvec if possible
                        polyfix fix(m_out,pvec,m_maxiter,m_dist_tol,m_area_tol);
                        if(!fix.run()) {
                           m_out << std::endl << "WARNING: failed to heal " << fname.GetFullPath().ToStdString() << std::endl;
                        }
                     }
                     else if(ext == "off" ) {
                        pvec = spaceio::off_io::read(fname.GetFullPath().ToStdString());
                     }

                     if(pvec.get()) {
                        it = m_files.insert(std::make_pair(filename,poly_string(pvec))).first;
                     }
                  }


                  // reset working dir after processing file
                  wxSetWorkingDirectory(m_working_dir);
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

      m_out << std::endl << "csgfix modified " << m_csg.GetFullPath().ToStdString() << std::endl;
   }
   else {
      if(out_csg.Exists())wxRemoveFile(out_csg.GetFullPath());
   }

   wxSetWorkingDirectory(m_working_dir);
}


std::string csgfix::poly_string(std::shared_ptr<ph3d_vector> pvec)
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
