// font2geo.h - this file was heavily modified by Carsten Arholm,
// using Don Brights "font_to_svg.hpp" as a starting point
// ref. https://github.com/donbright/font_to_svg
// font2geo converts a single TrueType character glyph into a
// "glyph_contours" object.
// This code depends on FreeType - https://www.freetype.org/


// font_to_svg.hpp - Read Font in TrueType (R) format, write SVG
// Copyright Don Bright 2013 <hugh.m.bright@gmail.com>
/*

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  License based on zlib license, by Jean-loup Gailly and Mark Adler
*/

/*

This program reads a TTF (TrueType (R)) file and outputs an SVG path.

See these sites for more info.
Basic Terms: http://www.freetype.org/freetype2/docs/glyphs/glyphs-3.html
FType + outlines: http://www.freetype.org/freetype2/docs/reference/ft2-outline_processinhtml
FType + contours: http://www.freetype.org/freetype2/docs/glyphs/glyphs-6.html
TType contours: https://developer.apple.com/fonts/TTRefMan/RM01/Chap1.html
TType contours2: http://www.truetype-typography.com/ttoutln.htm
Non-zero winding rule: http://en.wikipedia.org/wiki/Nonzero-rule
SVG paths: http://www.w3schools.com/svg/svg_path.asp
SVG paths + nonzero: http://www.w3.org/TR/SVG/paintinhtml#FillProperties

TrueType is a trademark of Apple Inc. Use of this mark does not imply
endorsement.

*/

#ifndef __FONT2GEO_H__
#define __FONT2GEO_H__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <utility>
#include <string>
#include <limits>

namespace font2geo {

   class ttf_file {
   public:
      ttf_file()
      {}

      ttf_file( std::string fname )
      {
         filename = fname;
         error = FT_Init_FreeType( &library );

         // Load a typeface
         error = FT_New_Face( library, filename.c_str(), 0, &face );
         if (error) {
            std::cerr << "problem loading file " << filename << "\n";
            exit(1);
         }
      }

      std::pair<std::string,std::string> get_font_name()
      {
         std::pair<std::string,std::string> font_name;
         FT_UInt num = FT_Get_Sfnt_Name_Count(face );
         for(FT_UInt i=0; i<num; i++) {
            FT_SfntName name;
            FT_Get_Sfnt_Name(face,i,&name);

            if(name.encoding_id == 0) {
               switch(name.name_id) {
               case TT_NAME_ID_FONT_FAMILY:
                  { font_name.first = std::string((const char*)name.string,name.string_len); break; }
               case TT_NAME_ID_FONT_SUBFAMILY:
                  { font_name.second = std::string((const char*)name.string,name.string_len); break; }
               default: {}
               };
            }
         }
         return font_name;
      }

      void free()
      {
         error = FT_Done_Face( face );
         error = FT_Done_FreeType( library );
      }

      FT_Face face;

   private:
      std::string filename;
      FT_Library library;
      FT_Error error;
   };

   // A single, closed contour
   // The contur contains segments equivalent to items in an SVG path
   // The final coordinate is the same as the first, so all contours are closed
   class contour {
   public:
      using segment = std::pair<char,std::vector<int>>;
      contour() {}

      // Note: inversion of y sign in glyph::render_unicode)
      void MoveTo(int x, int y)                   { m_segments.push_back(segment('M',{x,y})); }
      void LineTo(int x, int y)                   { m_segments.push_back(segment('L',{x,y})); }
      void BezierTo(int cx, int cy, int x, int y) { m_segments.push_back(segment('Q',{cx,cy,x,y})); }

      const std::vector<segment>& get_segments() const { return m_segments; }
   private:
      std::vector<segment> m_segments;
   };

   // contours of a single glyph (i.e. character)
   class glyph_contours {
   public:
      using contour_vector = std::vector<std::shared_ptr<contour>>;
      using const_iterator = contour_vector::const_iterator;

      glyph_contours() {}
      void push_back(std::shared_ptr<contour> contour) { m_contours.push_back(contour); }
      size_t size() const { return m_contours.size(); }
      const_iterator begin() const { return m_contours.begin(); }
      const_iterator end() const   { return m_contours.end(); }
   private:
      contour_vector m_contours;
   };

   class glyph {
   public:

      glyph( std::string filename)
           : m_x(std::numeric_limits<int>::max(),-std::numeric_limits<int>::max())
           , m_y(std::numeric_limits<int>::max(),-std::numeric_limits<int>::max())
      {
         this->file = ttf_file(filename);
         file.get_font_name();
      }

      ~glyph()
      {
         file.free();
      }

      std::pair<std::string,std::string> get_font_name()
      {
         return file.get_font_name();
      }

      // render a single ASCII character
      void render(char c)
      {
         unsigned int code = static_cast<unsigned int>(c);
         std::ostringstream s;
         s << code;
         render_unicode(s.str());
      }

      // render a single unicode character into svg contours
      // To render the character "A", enter "65"
      void render_unicode( std::string unicode_s )
      {
         face = file.face;
         codepoint = strtol( unicode_s.c_str() , NULL, 0 );
         // Load the Glyph into the face's Glyph Slot + print details
         FT_UInt glyph_index = FT_Get_Char_Index( face, codepoint );
         error = FT_Load_Glyph( face, glyph_index, FT_LOAD_NO_SCALE );
         slot = face->glyph;
         ftoutline = slot->outline;
         char glyph_name[1024];
         FT_Get_Glyph_Name( face, glyph_index, glyph_name, 1024 );
         gm = slot->metrics;

         // Invert y coordinates (SVG = neg at top, TType = neg at bottom)
         ftpoints = ftoutline.points;
         for ( int i = 0 ; i < ftoutline.n_points ; i++ )
            ftpoints[i].y *= -1;

         bbheight = face->bbox.yMax - face->bbox.yMin;
         bbwidth  = face->bbox.xMax - face->bbox.xMin;
         tags = ftoutline.tags;
         contours = ftoutline.contours;

         compute_outline();
      }

      int width()  { return m_x.second - m_x.first; }
      int height() { return m_y.second - m_y.first; }
      int bb_height() { return bbheight; }

      std::string svg()
      {
         return  svgheader()
         + svgtransform()
         + svgoutline()
         + svgfooter();
      }

      std::string svgheader() {
         std::stringstream tmp;
         tmp << "<svg width='" << bbwidth << "px' height='" << bbheight << "px' xmlns='http://www.w3.org/2000/svg' version='1.1'>";
         return tmp.str();
      }

      std::string svgtransform() {
         // TrueType points are not in the range usually visible by SVG.
         // they often have negative numbers etc. So.. here we
         // 'transform' to make visible.
         //
         // note also that y coords of all points have been flipped during
         // init() so that SVG Y positive = Truetype Y positive
         std::stringstream tmp;
         int yadj = gm.horiBearingY + gm.vertBearingY + 100;
         int xadj = 100;
         tmp << "\n <g fill-rule='nonzero' transform='translate(" << xadj << " " << yadj << ")' >";
         return tmp.str();
      }

      void compute_outline()  {
         std::vector<FT_Vector> pointsv(ftpoints,ftpoints+ftoutline.n_points);
         std::vector<char>      tagsv(tags,tags+ftoutline.n_points);
         std::vector<short>     contoursv(contours,contours+ftoutline.n_contours);
         compute_contours(pointsv, tagsv, contoursv);
      }

      std::string svgfooter()  {
         std::stringstream tmp;
         tmp << "\n </g>\n</svg>\n";
         return tmp.str();
      }

      std::shared_ptr<glyph_contours>  get_contours() { return  m_glyph_contours; }

      std::string svgoutline()
      {
         if(!m_glyph_contours.get()) throw std::runtime_error("No contours in glyph");

         std::stringstream  svg;
         svg << std::endl << "   <path fill='black' stroke='black' fill-opacity='0.45' stroke-width='2' d='";

         for(auto& c : *m_glyph_contours) {
            svg << std::endl;
            for(auto& s : c->get_segments()) {
               svg << std::endl << "   " << s.first;
               auto& v = s.second;
               for(size_t i=0; i<v.size(); i++) {
                  svg << ( (i%2==1)? "," : " ") << v[i];
               }
            }
            svg << std::endl << "   Z";
         }

         svg << std::endl << "'/>";
         return svg.str();
      }

   private:

      /* Draw the outline of the font as svg.
      There are three main components.
      1. the points
      2. the 'tags' for the points
      3. the contour indexes (that define which points belong to which contour)
      */
      void compute_contours(std::vector<FT_Vector> points, std::vector<char> tags, std::vector<short> contours)
      {
         m_glyph_contours = std::make_shared<glyph_contours>();

         m_x = std::make_pair(std::numeric_limits<int>::max(),-std::numeric_limits<int>::max());
         m_y = std::make_pair(std::numeric_limits<int>::max(),-std::numeric_limits<int>::max());

         if (points.size()==0) return;
         if (contours.size()==0)return;

         /* tag bit 1 indicates whether its a control point on a bez curve
         or not. two consecutive control points imply another point halfway
         between them */

         // Step 1. move to starting point (M x-coord y-coord )
         // Step 2. decide whether to draw a line or a bezier curve or to move
         // Step 3. for bezier: Q control-point-x control-point-y, destination-x, destination-y
         //         for line:   L x-coord, y-coord
         //         for move:   M x-coord, y-coord

         int contour_starti = 0;
         int contour_endi = 0;
         for ( int i = 0 ; i < contours.size() ; i++ ) {

            // create the current contour
            auto svg_cont = std::make_shared<contour>();
            m_glyph_contours->push_back(svg_cont);

            contour_endi = contours.at(i);
            int offset = contour_starti;
            int npts = contour_endi - contour_starti + 1;

            // add to contour
            svg_cont->MoveTo(points[contour_starti].x,points[contour_starti].y);
            minmax(points[contour_starti].x,points[contour_starti].y);

            for ( int j = 0; j < npts; j++ ) {
               int thisi = j%npts + offset;
               int nexti = (j+1)%npts + offset;
               int nextnexti = (j+2)%npts + offset;
               int x = points[thisi].x;
               int y = points[thisi].y;
               int nx = points[nexti].x;
               int ny = points[nexti].y;
               int nnx = points[nextnexti].x;
               int nny = points[nextnexti].y;
               bool this_tagbit1 = (tags[ thisi ] & 1);
               bool next_tagbit1 = (tags[ nexti ] & 1);
               bool nextnext_tagbit1 = (tags[ nextnexti ] & 1);
               bool this_isctl = !this_tagbit1;
               bool next_isctl = !next_tagbit1;
               bool nextnext_isctl = !nextnext_tagbit1;

               if (this_isctl && next_isctl) {
                  x = (x + nx) / 2;
                  y = (y + ny) / 2;
                  this_isctl = false;
                  if (j==0) {
                     svg_cont->MoveTo(x,y);
                     minmax(x,y);
                  }
               }

               if (!this_isctl && next_isctl && !nextnext_isctl) {
                  svg_cont->BezierTo(nx,ny,nnx,nny);
                  minmax(nx,ny);
                  minmax(nnx,nny);
               } else if (!this_isctl && next_isctl && nextnext_isctl) {
                  nnx = (nx + nnx) / 2;
                  nny = (ny + nny) / 2;
                  svg_cont->BezierTo(nx,ny,nnx,nny);
                  minmax(nx,ny);
                  minmax(nnx,nny);
               } else if (!this_isctl && !next_isctl) {
                  svg_cont->LineTo(nx,ny);
                  minmax(nx,ny);
               } else if (this_isctl && !next_isctl) {
                  // debug << " this is ctrl pt. skipping to " << nx << "," << ny << "\n";
               }
            }
            contour_starti = contour_endi+1;
         }
      }

      void minmax(int x, int y)
      {
         m_x.first  = (x < m_x.first )? x : m_x.first;
         m_x.second = (x > m_x.second)? x : m_x.second;
         m_y.first  = (y < m_y.first )? y : m_y.first;
         m_y.second = (y > m_y.second)? y : m_y.second;
      }

   public:
      int              codepoint;
      FT_GlyphSlot     slot;
      FT_Error         error;
      FT_Outline       ftoutline;
      FT_Glyph_Metrics gm;
      FT_Face          face;
      ttf_file         file;

      FT_Vector* ftpoints;
      char*      tags;
      short*     contours;

      int bbwidth, bbheight;

      std::pair<int,int>   m_x;  // min,max for x
      std::pair<int,int>   m_y;  // min,max for y

      // svg-equivalent contours of a single character glyph
      std::shared_ptr<glyph_contours> m_glyph_contours;
   };

} // namespace

#endif

