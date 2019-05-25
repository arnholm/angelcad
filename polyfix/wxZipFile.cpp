#include "wxZipFile.h"
#include <wx/wfstream.h>
#include <string>
using namespace std;

wxZipFile::wxZipFile(const wxFileName& zipname)
: m_zipname(zipname)
, m_zip(new wxZipOutputStream(new wxFFileOutputStream(zipname.GetFullPath())))
{}

wxZipFile::~wxZipFile()
{
  m_zip->Close();
  delete m_zip;
}


bool wxZipFile::AddFileEntry(const wxString& file_path, bool full_path, bool remove_original)
{
   // assume that this will fail
   bool retval = false;

   if(!m_zip)return retval;

   // check that the input file exists
   wxFileName  fname(file_path);
   if(!fname.Exists())return retval;

   std::string path = file_path.ToStdString();

   // open and read as binary data
   if(FILE* file = std::fopen(path.c_str(),"rb")) {

      // start a new entry
      wxString entry_name = (full_path)? file_path : fname.GetFullName();
      if(m_zip->PutNextEntry(entry_name)) {

         // read until no more data
         const size_t blen=1024;
         char buffer[blen];
         while(true) {
           size_t nbytes = std::fread(buffer,sizeof(char),blen,file);
           if(nbytes > 0) m_zip->Write(buffer,sizeof(char)*nbytes);
           else           break;
         }

         // all file data read, close the zip entry
         m_zip->CloseEntry();
         retval = true;
      }

      // close input file
      std::fclose(file);

      // we actually did it
      if(retval && remove_original) {
         wxRemoveFile(file_path);
      }
   }
   return retval;
}

wxFileName wxZipFile::FileName() const
{
   return m_zipname;
}
