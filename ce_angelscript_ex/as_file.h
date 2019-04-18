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


#ifndef AS_FILE_H
#define AS_FILE_H

#include <string>

// as_file offers checks for file/directory existance without
// dependency on external libraries

class as_file {
public:
   static bool file_exists(const std::string& path);
   static bool dir_exists(const std::string& path);
};

#endif // AS_FILE_H
