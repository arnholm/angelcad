// BeginLicense:
// Part of: angelcad - script based 3D solid modeller
// Copyright (C) 2017 Carsten Arnholm
// All rights reserved
//
// This file may be used under the terms of either the GNU General
// Public License version 2 or 3 (at your option) as published by the
// Free Software Foundation and appearing in the files LICENSE.GPL2
// and LICENSE.GPL3 included in the packaging of this file.
//
// This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
// INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE.
// EndLicense:


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



