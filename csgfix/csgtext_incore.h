#ifndef CSGTEXT_INCORE_H
#define CSGTEXT_INCORE_H

#include <memory>
#include <string>
#include <map>
class font_info;

// manage text() items in .csg files
class csgtext_incore {
public:
   using text_params = std::map<std::string,std::string>;

   csgtext_incore(std::ostream& out);
   virtual ~csgtext_incore();

   // parse the openscad text() statement into a map
   bool parse(const std::string& line, text_params& params);

   // generate the replacement code
   std::string code(size_t ilevel, text_params& params);

private:
   std::ostream*              m_out;
   std::shared_ptr<font_info> m_fonts;  // font info in case text() is encountered
};

#endif // CSGTEXT_INCORE_H
