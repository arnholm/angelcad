#ifndef POLYFIX_INCORE_H
#define POLYFIX_INCORE_H

#include "spacemath/polyhedron3d.h"
#include <ostream>

// This class is a limited in-core variant of the polyfix application.
// It is designed to be used in prefiltering of .csg files
class polyfix_incore {
public:
   polyfix_incore( std::ostream& out
                 , std::shared_ptr<ph3d_vector> polyset
                 , size_t maxiter
                 , double dist_tol
                 , double area_tol
                 );
   virtual ~polyfix_incore();

   bool run();

private:
   std::ostream&                m_out;
   std::shared_ptr<ph3d_vector> m_polyset;
   size_t                       m_maxiter;
   double                       m_dist_tol;
   double                       m_area_tol;
};

#endif // POLYFIX_INCORE_H
