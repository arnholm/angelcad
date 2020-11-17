#include "wxProcessSync.h"
#include <wx/filename.h>

wxProcessSync::wxProcessSync()
{}

wxProcessSync::~wxProcessSync()
{}

long wxProcessSync::Execute(ConsolePanel* console, const wxString& cmd, const wxString& cwd )
{
   wxString working_dir = wxFileName::GetCwd();

   // run polyfix synchronously to create OFF
   console->AppendText(" ",0);
   console->AppendText("sync > " + cmd,0);
   console->AppendText("... please wait",0);
   console->DisplayTextFromWorker();

   // capture the output in an array
   wxSetWorkingDirectory(cwd);
   wxArrayString output;
   wxArrayString error;
   long status = wxExecute(cmd, output,error );
   wxSetWorkingDirectory(working_dir);

   // flush the output to console
   for(size_t i=0; i<output.GetCount(); i++) {
      console->AppendText(output[i],0);
   }

   for(size_t i=0; i<error.GetCount(); i++) {
      console->AppendText("stderr: "+ error[i],0);
   }

   return status;
}
