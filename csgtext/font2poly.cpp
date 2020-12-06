#include "font2poly.h"
#include "font2geo.h"
#include "spacemath/pos2d.h"
#include "spacemath/vec3d.h"
#include "spacemath/vec2d.h"
#include "spacemath/line2d.h"

using namespace font2geo;
using namespace spacemath;


font2poly::font2poly()
{}

font2poly::~font2poly()
{}

static void add_bezier(double f, std::vector<pos2d>& vec, const std::vector<int>& x)
{
   pos2d p1 = *vec.rbegin();
   pos2d p2(x[0]*f,-x[1]*f);
   pos2d p3(x[2]*f,-x[3]*f);

   line2d l1(p1,p2);
   line2d l2(p2,p3);

   // looks like 5 segments is reasonable
   size_t nseg = 5;
   double par  = 0.0;
   double dpar = 1.0/(nseg);

   std::vector<pos2d> bzr;
   bzr.reserve(nseg+1);
   for(size_t i=0; i<nseg+1; i++) {
      pos2d q1 = l1.interpolate(par);
      pos2d q2 = l2.interpolate(par);
      line2d ql(q1,q2);
      bzr.push_back(ql.interpolate(par));
      par += dpar;
   }

   // add possible curve optimisation here

   // add bzr points to vec (skip 1st point)
   for(size_t i=1; i<bzr.size(); i++) vec.push_back(bzr[i]);
}

void font2poly::render( const std::string& ttf_path
                      , const std::string& text
                      , size_t tsize
                      , size_t tspacing
                      , const std::string& halign
                      , const std::string& valign
                      )
{
   m_poly_pos.clear();
   m_poly_neg.clear();

   font2geo::glyph g(ttf_path);

   double dx = 0.0;
   double spacing = 150.0*tspacing;

   for(size_t i=0; i<text.length(); i++) {

      double f = 1.0;

      // process one character glyph
      char c = text[i];
      if(isspace(c)) {
         // we render a dummy, narrow character to get its width (see dx calculation)
         g.render('j');
         int height = g.bb_height();
         f = (1.9*tsize)/height;
      }
      else {

         // not whitespace
         g.render(c);
         int height = g.bb_height();
         f = (1.9*tsize)/height;

         // get the glyph contours
         std::shared_ptr<glyph_contours> contours = g.get_contours();

         // traverse the closed contours of this glyph
         for(std::shared_ptr<contour> contour : *contours) {

            // process the segment commands of this closed contour
            // and compute the vertices of of its polygon
            std::vector<pos2d> vec;
            vec.reserve(20);

            // switch sign of Y coordinate during conversion to pos2d
            // since it was flipped before due to SVG convention.
            // Here, we use same convention as TTF for pos2d (right hand system)
            // Also scale by f to user space coordinates

            const std::vector<contour::segment>& segments = contour->get_segments();
            for(auto& p : segments) {
               const std::vector<int>& x = p.second;
               switch(p.first) {
                  case 'M': { vec.push_back(pos2d(x[0]*f,-x[1]*f)); break; }
                  case 'L': { vec.push_back(pos2d(x[0]*f,-x[1]*f)); break; }
                  case 'Q': { add_bezier(f,vec,x); break; }
                  default: {  }
               };
            }

            // all contour points computed
            // erase last point (=duplicate of first)
            vec.resize(vec.size()-1);

            // shift the coordinates to the right by the current offset
            for(auto& p : vec) p += pos2d(dx,0);

            // create the polygon
            auto poly = std::make_shared<polygon2d>(vec);
            if(poly->signed_area() > 0) {
               m_poly_pos.push_back(poly);
            }
            else {
               // reverse polygon orientation, but remember it was originally negative
               poly->reverse();
               m_poly_neg.push_back(poly);
            }
         }
      }

      // update the character offset with current glyph width + spacing
      dx += f*(g.width() + spacing);
   }

   bool align_h = (halign=="center");
   bool align_v = (valign=="center");

   if(align_h || align_v) {
      auto bbox = box();
      spacemath::vec3d v3(bbox.p1(),bbox.p2());
      double dx = (align_h)? -v3.x()*0.5 : 0.0;
      double dy = (align_v)? -v3.y()*0.5 : 0.0;
      spacemath::vec2d v(dx,dy);

      // offset all polygon coordinates
      for(auto& poly : m_poly_pos) {
         for(auto& pos : *poly) {
            pos += v;
         }
      }
      for(auto& poly : m_poly_neg) {
         for(auto& pos : *poly) {
            pos += v;
         }
      }
   }
}

spacemath::bbox3d font2poly::box() const
{
   spacemath::bbox3d bbox;
   // we ignore negative polygons here, they are always contained
   for(auto& poly : m_poly_pos) {
      for(auto& pos : *poly) {
         bbox.enclose(pos3d(pos.x(),pos.y(),0.0));
      }
   }
   return bbox;
}
