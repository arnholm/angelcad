#ifndef CSGFIX_H
#define CSGFIX_H

#include <wx/filename.h>
#include <unordered_map>
#include "spacemath/polyhedron3d.h"

class csgfix {
public:
   csgfix( std::ostream& out
         , const wxFileName& scad
         , const wxFileName& csg
         , size_t maxiter
         , double dist_tol
         , double area_tol
         );
   virtual ~csgfix();

   // run the filtering with feedback to console
   void run();

protected:
   std::string poly_string(std::shared_ptr<ph3d_vector> poly);

private:
   typedef std::unordered_map<std::string,std::string> FileMap;

   std::ostream& m_out;
   wxFileName    m_scad;   // original .scad file
   wxFileName    m_csg;    // .csg file generated by openscad

   size_t        m_maxiter;
   double        m_dist_tol;
   double        m_area_tol;

   size_t        m_line_number;
   FileMap       m_files;
   wxString      m_working_dir;  // current working directory of caller
};

#endif // CSGFIX_H
