#include "csgfix.h"
#include "spaceio/off_io.h"
#include "spaceio/stl_io.h"
#include "polyfix_incore.h"
#include "dxfread_incore.h"
#include "csgtext_incore.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

static void tokenize(const std::string& input,
                     const std::string& delimiters,
                     std::vector<std::string>& tokens)
{
   using namespace std;
   string::size_type last_pos = 0;
   string::size_type pos = 0;
   while(true) {
      pos = input.find_first_of(delimiters, last_pos);
      if( pos == string::npos ) {
         if(input.length()-last_pos > 0)tokens.push_back(input.substr(last_pos));
         break;
      }
      else {
         if(pos-last_pos > 0)tokens.push_back(input.substr(last_pos, pos - last_pos));
         last_pos = pos + 1;
      }
   }
}


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

   // this variable is instanciated on first encounter of text() statement
   std::shared_ptr<csgtext_incore> csgtext;

   // line number in input csg
   m_line_number = 0;

   std::ifstream in(m_csg.GetFullPath().ToStdString());
   if(in.is_open()) {

      // open the output (filtered) csg
      std::ofstream out(out_csg.GetFullPath().ToStdString());
      m_out << " " << std::endl;
      // read the input csg line by line
      std::string line;
      while(std::getline(in,line)) {

         // increment the input line number (useful in error reporting)
         m_line_number++;

         size_t imp  = line.find("import(file");
         size_t itxt = line.find("text(text");
         if(imp != std::string::npos) {

            // this is an import statement
            std::string indent = line.substr(0,imp);

            // extract the filename of the file to be imported
            size_t left  = line.find("\"",imp) + 1;
            size_t right = line.find("\"",left);
            size_t len   = right-left;
            std::string filename = line.substr(left,len);

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
                     // STL file

                     m_out << "csgfix processing " << fname.GetFullPath().ToStdString() << std::endl;
                     auto pvec = spaceio::stl_io::read(fname.GetFullPath().ToStdString());

                     // run polyfix_incore, it will modify pvec if possible
                     polyfix_incore fix(m_out,pvec,m_maxiter,m_dist_tol,m_area_tol);
                     if(!fix.run()) {
                        m_out << std::endl << "WARNING: failed to heal " << fname.GetFullPath().ToStdString() << std::endl;
                     }
                     if(pvec.get()) it = m_files.insert(std::make_pair(filename,indent + poly_string(pvec))).first;

                  }
                  else if(ext == "off" ) {
                     // OFF file
                     m_out << "csgfix processing " << fname.GetFullPath().ToStdString() << std::endl;
                     auto pvec = spaceio::off_io::read(fname.GetFullPath().ToStdString());
                     if(pvec.get()) it = m_files.insert(std::make_pair(filename,indent + poly_string(pvec))).first;
                  }
                  else if(ext == "dxf" ) {

                     m_out << "csgfix processing " << fname.GetFullPath().ToStdString();

                     // extract layer info
                     std::set<string> layers;
                     size_t ilay  = line.find("layer");
                     std::string layer;
                     if(ilay != string::npos) {
                        size_t left  = line.find("\"",ilay) + 1;
                        size_t right = line.find("\"",left);
                        size_t len   = right-left;
                        layer        = line.substr(left,len);
                        if(len>0)layers.insert(layer);

                        m_out << ":" << layer;
                     }
                     m_out << std::endl;

                     if(layer != "undef") {

                        double dx = 0.0;
                        double dy = 0.0;
                        size_t iorg = line.find("origin");
                        if(iorg != string::npos) {
                           size_t left  = line.find("[",iorg) + 1;
                           size_t right = line.find("]",left);
                           size_t len   = right-left;
                           if(len > 0) {
                              std::vector<std::string> tokens;
                              tokenize(line.substr(left,len)," ,[]",tokens);
                              if(tokens.size()==2) {
                                 std::istringstream inx(tokens[0]),iny(tokens[1]);
                                 inx >> dx;
                                 iny >> dy;
                              }
                           }
                        }

                        // DXF files are keyed with layer
                        it=m_files.find(filename+layer);
                        if(it == m_files.end()) {

                           bool include_raw    = false;
                           double scale_factor = 1.0;
                           double sectol       = m_dist_tol;
                           double epspnt       = m_dist_tol;
                           bool   keep_case    = false;
                           dxfxmloptions opt(include_raw,scale_factor,sectol,epspnt,layers,keep_case);
                           opt.set_auto_close(true);
                           std::ifstream in(fname.GetFullPath().ToStdString());
                           if(in.is_open()) {
                              if(auto dxf_root = make_shared<dxfroot>(in,opt)) {
                                 dxfread_incore dxf(m_out,dxf_root,-dx,-dy);
                                 size_t ilevel = 2 + indent.length();
                                 if(dxf.run(ilevel)) {
                                    it = m_files.insert(std::make_pair(filename+layer,dxf.code())).first;
                                 }
                              }
                           }
                        }
                     }
                     else {
                        // mini square replaces DXF with "undef" layer
                        it = m_files.insert(std::make_pair(filename+layer,indent +"square(size = [0.05, 0.05], center = true);")).first;
                     }
                  }
               }
               else {
                  throw std::runtime_error("File does not exist: " + fname.GetFullPath().ToStdString());
               }

               // reset working dir after processing file
               wxSetWorkingDirectory(m_working_dir);
            }

            if(it != m_files.end()) {
               // output the substitute statement
               out << it->second << std::endl;
            }
            else {
               // we could not resolve the file, so we just copy the input line
               out << line << std::endl;
            }
         }
         else if(itxt != std::string::npos) {
            // this is a text statement
            size_t ilevel = itxt/3;

            if(!csgtext.get()) {
               csgtext = std::make_shared<csgtext_incore>(m_out);
            }
            // defaults
            csgtext_incore::text_params params;
            params["font"]    = "Liberation Sans:style=Regular";
            params["size"]    = "10";
            params["spacing"] = "1";
            params["halign"]  = "left";
            params["valign"]  = "baseline";

            std::string code;
            if(csgtext->parse(line,params)) {
               code = csgtext->code(ilevel,params);
            }

            if(code.length() > 0)  out <<  code << endl;
            else {
               out <<  line << endl;
               m_out << "Warning: could not translate : " << line << endl;
            }

         }
         else {
            // not a translated statement
            out << line << std::endl;
         }
      }
   }

   // close input file so that file copy can work
   in.close();

   if((csgtext.get() || m_files.size()>0) && out_csg.Exists()) {
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
