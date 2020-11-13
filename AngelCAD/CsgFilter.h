#ifndef CSGFILTER_H
#define CSGFILTER_H

#include <wx/filename.h>
#include "ConsolePanel.h"
#include "AngelCADEditor.h"
#include <unordered_map>
#include "spacemath/polyhedron3d.h"

class CsgFilter {
public:
   CsgFilter(ConsolePanel* console, const wxFileName& csg);
   virtual ~CsgFilter();

   // run the filtering with feedback to console
   void run(AngelCADEditor* page);

protected:
   std::string poly_string(std::shared_ptr<ph3d_vector> poly);

private:
   typedef std::unordered_map<std::string,std::string> FileMap;

   ConsolePanel* m_console;
   wxFileName    m_csg;
   size_t        m_line_number;
   FileMap       m_files;
   wxString      m_working_dir;  // current working directory of caller
};

#endif // CSGFILTER_H
