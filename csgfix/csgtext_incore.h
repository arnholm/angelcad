#ifndef CSGTEXT_INCORE_H
#define CSGTEXT_INCORE_H

#include <memory>
#include <string>
class font_info;

class csgtext_incore {
public:
   csgtext_incore();
   virtual ~csgtext_incore();

   // parse the openscad text() statement
   bool parse(const std::string& line, std::string& text, std::string& font, size_t& tsize);

   std::string code(size_t ilevel, const std::string& text, const std::string& font, size_t tsize = 10);

private:
   std::shared_ptr<font_info> m_fonts;  // font info in case text() is encountered
};

#endif // CSGTEXT_INCORE_H
