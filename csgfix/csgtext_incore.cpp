#include "csgtext_incore.h"
#include "csgtext/font_info.h"
#include "csgtext/font2poly.h"
#include "csgtext/poly2csg.h"
#include <sstream>
#include <vector>
#include <functional>

static void tokenize(const std::string& input,
                     const std::string& delimiters,
                     std::vector<std::string>& tokens)
{
   using namespace std;
   string::size_type last_pos = 0;
   string::size_type pos = 0;
   while(true) {
      pos = input.find_first_of(delimiters, last_pos);
      if( pos == string::npos ) {
         if(input.length()-last_pos > 0)tokens.push_back(input.substr(last_pos));
         break;
      }
      else {
         if(pos-last_pos > 0)tokens.push_back(input.substr(last_pos, pos - last_pos));
         last_pos = pos + 1;
      }
   }
}

// trim from start (in place)
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}


csgtext_incore::csgtext_incore(std::ostream& out)
: m_out(&out)
, m_fonts(std::make_shared<font_info>())
{}

csgtext_incore::~csgtext_incore()
{}

bool csgtext_incore::parse(const std::string& line, text_params& params)
{
   bool retval = false;
   size_t itxt = line.find("text(text");

   if(itxt != std::string::npos) {

      size_t l1 = line.find("(")+1;
      size_t l2 = line.rfind(")");
      std::string pstring = line.substr(l1,l2-l1);

      // Remove the quote signs
      for(auto& c : pstring) c = (c == '\"')? ' ':c;

      std::vector<std::string> tokens;
      tokenize(pstring,",",tokens);
      for(auto& token : tokens) {
         trim(token);

         // we simplify the font specification here
         //    OpenSCAD  :  Carlito:style=Bold Italic
         //    Simplified:  Carlito:Bold Italic
         // The map contains the simplified style

         size_t istyle = token.find("style=");
         if(istyle != std::string::npos) {
            token = token.substr(0,istyle) + token.substr(istyle+6);
         }

         std::vector<std::string> tspec;
         tokenize(token,"=",tspec);
         if(tspec.size() == 2) {
            trim(tspec[0]);
            trim(tspec[1]);
            params[tspec[0]] = tspec[1];
         }
      }
      retval = true;
   }

   return retval;
}

template <typename T>
bool get_value(const std::string& name, csgtext_incore::text_params& params, T& value)
{
   auto i = params.find(name);
   if(i == params.end()) return false;
   std::istringstream in(i->second);
   in >> value;
   return true;
}

template <>
bool get_value(const std::string& name, csgtext_incore::text_params& params, std::string& value)
{
   auto i = params.find(name);
   if(i == params.end()) return false;
   value = i->second;
   return true;
}

std::string get_font(csgtext_incore::text_params& params)
{
   std::string font = "Arial:Regular";
   std::string test_font = font;
   if(get_value("font",params,test_font)) {
      trim(test_font);
      if(test_font.length() > 0) {
         font = test_font;
      }
   }
   return font;
}

std::string csgtext_incore::code(size_t ilevel, text_params& params)
{
   std::string code;

   std::string text;
   if(get_value("text",params,text)) {

      auto it = m_fonts->find(get_font(params));
      if(it != m_fonts->end()) {
         std::string fontfile = it->second;

         // look up some values that may or may not be specified
         size_t      tsize=10;
         size_t      spacing=1;
         std::string halign="left";
         std::string valign="baseline";

         get_value("size",params,tsize);
         get_value("spacing",params,spacing);
         get_value("halign",params,halign);
         get_value("valign",params,valign);

         auto poly2d = std::make_shared<font2poly>();
         poly2d->render(fontfile,text,tsize,spacing,halign,valign);
         auto csg = std::make_shared<poly2csg>();
         code = csg->render(0,poly2d);
      }
   }

   return code;
}
