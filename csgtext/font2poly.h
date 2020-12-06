#ifndef FONT2POLY_H
#define FONT2POLY_H
#include "csgtext_config.h"
#include <memory>
#include <string>
#include "spacemath/polygon2d.h"
#include "spacemath/bbox3d.h"

// font2poly converts a text string to polygons
class CSGTEXT_PUBLIC font2poly {
public:
   using polygon = std::shared_ptr<spacemath::polygon2d>;

   font2poly();
   virtual ~font2poly();

   // render the text as polygons
   // given the TrueType font file path and the text
   void render(const std::string& ttf_path
             , const std::string& text
             , size_t tsize
             , size_t spacing
             , const std::string& halign
             , const std::string& valign
             );

   // return polygons to be added
   std::vector<polygon> poly_pos() const { return m_poly_pos; }

   // return polygons to be subtracted
   std::vector<polygon> poly_neg() const { return m_poly_neg; }

   // compute bounding box of polygons (after rendering)
   spacemath::bbox3d box() const;

private:
   std::vector<polygon> m_poly_pos;  // polygons to be added
   std::vector<polygon> m_poly_neg;  // polygons to be subtracted
};

#endif //
