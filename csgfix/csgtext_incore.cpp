#include "csgtext_incore.h"
#include "csgtext/font_info.h"
#include "csgtext/font2poly.h"
#include "csgtext/poly2csg.h"
#include <sstream>

csgtext_incore::csgtext_incore()
: m_fonts(std::make_shared<font_info>())
{}

csgtext_incore::~csgtext_incore()
{}

bool csgtext_incore::parse(const std::string& line, std::string& text, std::string& font, size_t& tsize)
{
   bool retval = false;
   size_t itxt = line.find("text(text");

   if(itxt != std::string::npos) {

      // extract the text string to be rendered
      size_t left  = line.find("\"",itxt) + 1;
      size_t right = line.find("\"",left);
      size_t len   = right-left;
      text = line.substr(left,len);

      // get the specified font, use default if we can't decode it
      size_t ifont = line.find("font",0);
      if(ifont != std::string::npos) {
         left  = line.find("\"",ifont) + 1;
         right = line.find("\"",left);
         len   = right-left;
         std::string scad_font = line.substr(left,len);
         size_t i1 = scad_font.find(":",0)+1;
         if(i1 != std::string::npos) {
            size_t i2 = scad_font.find("=",i1);
            if(i2 != std::string::npos) {
               len  = i2-i1+1;
               scad_font.erase(i1,len);
               font = scad_font;
            }
         }
      }

      // get font size
      size_t isize = line.find("size",0);
      if(isize != std::string::npos) {
         left  = line.find("=",isize) + 1;
         right = line.find(",",left);
         size_t len   = right-left;
         std::string token = line.substr(left,len);
         std::istringstream in(token);
         in >> tsize;
      }

      return true;
   }

   return retval;
}

std::string csgtext_incore::code(size_t ilevel, const std::string& text, const std::string& font, size_t tsize)
{
   std::string code;

   auto it = m_fonts->find(font);
   if(it != m_fonts->end()) {
      std::string fontfile = it->second;

      auto poly2d = std::make_shared<font2poly>();
      poly2d->render(fontfile,text,tsize);
      auto csg = std::make_shared<poly2csg>();
      code = csg->render(0,poly2d);
   }

   return code;
}
