#ifndef WXPROCESSSYNC_H
#define WXPROCESSSYNC_H

#include <wx/utils.h>
#include <wx/string.h>
#include "ConsolePanel.h"

// synchronous running of external command
class wxProcessSync {
public:
   wxProcessSync();
   virtual ~wxProcessSync();

   long Execute(ConsolePanel* console, const wxString& cmd, const wxString& cwd);
};

#endif // WXPROCESSSYNC_H
