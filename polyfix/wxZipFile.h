#ifndef WXZIPFILE_H
#define WXZIPFILE_H

#include <wx/filename.h>
#include <wx/zipstrm.h>
#include <wx/wfstream.h>
// convenience wrapper around wxZipOutputStream

class wxZipFile {
public:
   wxZipFile(const wxFileName& zipname);
   virtual ~wxZipFile();

   // add an external file to the zip archive
   // full_path      : true if full path is stored in entry. Otherwise name only
   // remove_original: delete the input file if successful
   bool AddFileEntry(const wxString& file_path, bool full_path, bool remove_original);

   wxFileName FileName() const;

private:
   wxFileName           m_zipname;
   wxZipOutputStream*   m_zip;
};

#endif // WXZIPFILE_H
