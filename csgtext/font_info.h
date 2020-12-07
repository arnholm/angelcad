#ifndef FONT_INFO_H
#define FONT_INFO_H

#include <string>
#include <vector>
#include <map>
#include "csgtext_config.h"

// basic class to find available system TrueType fonts and associated *.ttf file names
// The application should create exactly one font_info object
class CSGTEXT_PUBLIC font_info {
public:
   using font_dirs = std::vector<std::string>;           // directory paths where ttf's are found
   using font_map  = std::map<std::string,std::string>;  // <"font:style","ttf-file">
   using const_iterator = font_map::const_iterator;

   font_info();
   virtual ~font_info();

   // add user defined font dir (call build_map() after to activate)
   void add_font_dir(const std::string& dir);

   // build map is called by default for default font locations
   // but must be called explicitely after calling add_font_dir(...)
   void build_map();

   // size returns number of fonts registered
   size_t size() const { return m_map.size(); }

   const_iterator begin() const { return m_map.begin(); }
   const_iterator end() const { return m_map.end(); }

   // look up a font file using <font_name>:<font_style> syntax (e.g. "Liberation Sans:Regular" )
   const_iterator find(const std::string& font_key) { return m_map.find(font_key); }

protected:
   void default_font_dirs();

private:
   font_dirs m_dirs;
   font_map  m_map;
};

#endif // FONT_INFO_H
