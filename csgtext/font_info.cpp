
#include "font_info.h"
#include <sstream>
#include "font2geo.h"
#include "recursive_file_search.h"
#include <stdlib.h>     /* getenv */

font_info::font_info()
{
   default_font_dirs();
   build_map();
}

void font_info::default_font_dirs()
{
#ifdef _MSC_VER
   std::string sysroot  = "C:\\Windows";
   if(char* path        = getenv ("SYSTEMROOT")) sysroot = path;
   std::string fonts    = "\\Fonts";
   std::string font_dir = sysroot + fonts;
   add_font_dir(font_dir);
#elif __GNUC__
   add_font_dir("/usr/share/fonts");
#else
  #error "Unknown compiler"
#endif
}

void font_info::add_font_dir(const std::string& dir)
{
   m_dirs.push_back(dir);
}

font_info::~font_info()
{}

void font_info::build_map()
{
   m_map.clear();

   // traverse directories
   for(auto& dir : m_dirs) {

      // find font files
      auto ttf_files = recursive_file_search(dir,"*.ttf",4);

      // traverse font files in directory
      for(auto& file : ttf_files) {

         // get the font signature
         font2geo::ttf_file font(file);
         auto p = font.get_font_name();

         // filter some 2-byte names with 0 characters
         std::string name;
         for(char c : p.first) if(c) name += c;
         std::string style;
         for(char c : p.second) if(c) style += c;

         if(name.length() > 0) {
            if(style.length()==0) style="Regular";
            std::ostringstream out;
            out << name << ":" << style;
            std::string signature = out.str();
            m_map[signature] = file;
         }
      }
   }
}
