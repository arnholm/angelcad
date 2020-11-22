#include "dxfread_incore.h"
#include <ostream>
#include <sstream>
#include "dxfdom/dxfprofileexport.h"

dxfread_incore::dxfread_incore(std::ostream& out
                              ,std::shared_ptr<dxfroot> root
                              ,double dx
                              ,double dy
                              )
: m_out(out)
, m_root(root)
, m_dx(dx)
, m_dy(dy)
{}

dxfread_incore::~dxfread_incore()
{}


bool dxfread_incore::run(size_t ilevel)
{
   bool status_ok = false;

   try  {

      m_out << " building profile loops " << std::endl;
      m_root->build_profile();
      if(shared_ptr<dxfprofile> prof = m_root->profile()) {

         // convert profile to a sorted list of loops.
         // the smallest area will be first in the list so loops need to
         // be popped from the back() to process the largest to smallest

         list<std::shared_ptr<dxfloop>> loop_list;
         size_t icount = 0;
         for(auto loop : *prof) {
            loop_list.push_front(loop);
         }

         if(loop_list.size() > 0) {
            dxfprofileexport exp;
            std::shared_ptr<dxfloop> loop = loop_list.front();
            loop_list.pop_front();
            m_code = exp.scad_booleans(ilevel+1,loop,loop_list);
            status_ok = m_code.length() > 0;

            std::ostringstream sout;
            for(size_t i=0; i<ilevel; i++) sout << "   ";
            sout << "multmatrix([[1, 0, 0, "<< m_dx << "], [0, 1, 0, " << m_dy << "], [0, 0, 1, 0], [0, 0, 0, 1]]) { "<< std::endl
                 << m_code;
            for(size_t i=0; i<ilevel; i++) sout << "   ";
            sout << "}";
            m_code = sout.str();
         }
      }
   }
   catch ( std::exception& ex) {
      m_out << "DXF error: " << ex.what() << std::endl;
   }

   return status_ok;
}
