#include "as_file.h"
#ifdef _WIN32
   #include "Shlwapi.h"
#else
   #include <sys/stat.h>
#endif

bool as_file::file_exists(const std::string& path)
{
   #ifdef _WIN32
      return (TRUE == PathFileExists(path.c_str()));
   #else
      struct stat fileStat;
      if(stat(path.c_str(), &fileStat) )return false;
      if(!S_ISREG(fileStat.st_mode)) return false;
      return true;
   #endif
}

bool as_file::dir_exists(const std::string& path)
{
   #ifdef _WIN32
      DWORD ftyp = GetFileAttributesA(path.c_str());
      if (ftyp == INVALID_FILE_ATTRIBUTES) return false;  //something is wrong with your path!
      if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;   // this is a directory!
      return false;
   #else
      struct stat fileStat;
      if(stat(path.c_str(), &fileStat) )return false;
      if(!S_ISDIR(fileStat.st_mode)) return false;
      return true;
   #endif
}



