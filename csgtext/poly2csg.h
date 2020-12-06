#ifndef POLY2CSG_H
#define POLY2CSG_H

#include "font2poly.h"
#include "csgtext_config.h"

// poly2csg converts a font2poly object to OpenSCAD csg
class CSGTEXT_PUBLIC poly2csg {
public:
   poly2csg();
   virtual ~poly2csg();

   // render to OpenSCAD .csg format
   std::string render(int level, std::shared_ptr<font2poly> poly);

protected:
   std::string csg_union(int level, std::vector<font2poly::polygon> vpoly);
   std::string polygon(int level, font2poly::polygon poly);
};

#endif // POLY2CSG_H
