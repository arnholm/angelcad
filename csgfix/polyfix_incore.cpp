#include "polyfix_incore.h"
#include "polyhealer/polyhealer.h"

polyfix_incore::polyfix_incore( std::ostream& out
                              , std::shared_ptr<ph3d_vector> polyset
                              , size_t maxiter
                              , double dist_tol
                              , double area_tol
                              )
: m_out(out)
, m_polyset(polyset)
, m_maxiter(maxiter)
, m_dist_tol(dist_tol)
, m_area_tol(area_tol)
{}

polyfix_incore::~polyfix_incore()
{}

bool polyfix_incore::run()
{
   bool verbose = false;

   try {

      std::vector<std::string> warning_summary(m_polyset->size());

      // used for offsetting output
      const std::string blanks = "             ";

      // traverse the polyhedra and remove unused vertices
      for(size_t ipoly=0; ipoly<m_polyset->size(); ipoly++) {

         std::shared_ptr<polyhedron3d> poly = (*m_polyset)[ipoly];
         polyhealer healer(poly,m_dist_tol,m_area_tol,verbose);

         m_out << std::endl << "polyhedron " << ipoly << " ================= volume="<<poly->volume() << ", dtol=" << m_dist_tol << ", atol=" << m_area_tol << ", maxiter="<< m_maxiter;

         warning_summary[ipoly] = healer.run_healing(m_maxiter,m_out);
      }

      m_out << std::endl << "Summary: ";
      for(size_t ipoly=0; ipoly<m_polyset->size(); ipoly++) {
         std::shared_ptr<polyhedron3d> poly = (*m_polyset)[ipoly];
         m_out << std::endl << blanks << "polyhedron " << ipoly <<": vertices=" << poly->vertex_size() << " faces="<<poly->face_size();
      }

      m_out << std::endl;
   }
   catch(std::exception& ex) {
      m_out << "Error: " << ex.what() << std::endl;
      return false;
   }


   return true;
}
