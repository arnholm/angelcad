#include "poly2csg.h"
#include <sstream>
#include <iomanip>

poly2csg::poly2csg()
{}

poly2csg::~poly2csg()
{}

std::string poly2csg::render(int level, std::shared_ptr<font2poly> poly)
{
   std::ostringstream out;

   auto poly_pos = poly->poly_pos();
   auto poly_neg = poly->poly_neg();

   if(poly_neg.size() > 0) {
      std::string prefix(level*3,' ');
      out << prefix << "difference() {"<< std::endl;
      out << csg_union(level+1,poly_pos);
      out << csg_union(level+1,poly_neg);
      out << prefix << "}"<< std::endl;
   }
   else {
      out << csg_union(level,poly_pos);
   }
   return out.str();
}

std::string poly2csg::csg_union(int level, std::vector<font2poly::polygon> vpoly)
{
   std::string prefix(level*3,' ');
   std::ostringstream out;
   out << prefix << "union() {"<< std::endl;
   for(auto p : vpoly) out << polygon(level+1,p) << std::endl;
   out << prefix << "}"<< std::endl;
   return out.str();
}

std::string poly2csg::polygon(int level, font2poly::polygon poly)
{
   std::string prefix(level*3,' ');

   std::ostringstream out;
   out << prefix << "polygon( points=[";
   size_t icount = 0;
   for(auto p : *poly) {
      if(icount>0) out << ',';
      // we can manage with a little less precision than usual here
      out << std::setprecision(8) << '[' << p.x() << ',' << p.y() << ']';
      icount++;
   }
   out << "] );";
   return out.str();

}
