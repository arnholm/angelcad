#ifndef DXFREAD_INCORE_H
#define DXFREAD_INCORE_H

// This class is a limited in-core variant of the dxfread application.
// It is designed to be used in prefiltering of .csg files

#include "dxfdom/dxfxmloptions.h"
#include "dxfdom/dxfroot.h"

class dxfread_incore {
public:
   dxfread_incore(std::ostream& out
                 ,std::shared_ptr<dxfroot> root
                 ,double dx
                 ,double dy
                 );
   virtual ~dxfread_incore();
   bool run(size_t ilevel);

   const std::string& code() const { return m_code; }

private:
   std::ostream&            m_out;
   std::shared_ptr<dxfroot> m_root;
   double                   m_dx; // amount to translate in x
   double                   m_dy; // amount to translate in y
   std::string              m_code;
};

#endif // DXFREAD_INCORE_H
