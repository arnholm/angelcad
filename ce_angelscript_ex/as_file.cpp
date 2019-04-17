#include "as_file.h"
#include <sys/stat.h>

bool as_file::file_exists(const std::string& path)
{
   struct stat fileStat;
   if(stat(path.c_str(), &fileStat) )return false;
   if(!S_ISREG(fileStat.st_mode)) return false;

   return true;
}

bool as_file::dir_exists(const std::string& path)
{
   struct stat fileStat;
   if(stat(path.c_str(), &fileStat) )return false;
   if(!S_ISDIR(fileStat.st_mode)) return false;

   return true;
}
