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

#include "as_include_callback.h"
#include "as_file.h"
#include <string>
using namespace std;

#include "ce_angelscript/ce_angelscript.h"
#include "ce_angelscript/add_on/scriptbuilder/scriptbuilder.h"

// This callback will be called for each #include directive encountered by the
// builder. The callback should call the AddSectionFromFile or AddSectionFromMemory
// to add the included section to the script. If the include cannot be resolved
// then the function should return a negative value to abort the compilation.

int as_include_callback(const char* c_include, const char* c_from_section, CScriptBuilder* builder, void* userParam)
{
   // Determine the path of the current script so that we can resolve relative paths for includes
   string path = c_from_section;
   size_t posOfSlash = path.find_last_of("/\\");
   if( posOfSlash != string::npos )
      path.resize(posOfSlash+1);
   else
      path = "";

   // c_include is the contents of the #include "c_include"
   string include(c_include);

   // we start by assuming this is the full path
   string full_path = include;

   // classify the type of include path
   // =================================
   // explicit_absolute: starts with '/' or '\\'   :  /this/is/an/explicit/absolute/path  C:\this\is\an\explicit\absolute\path
   // explicit_relative: starts with '.'           :  ./this/is/an/explicit/relative/path
   // implicit_relative: neither of the above      :  this/is/an/implicit/relative/path

   // implicit_relative can be relative to the current script path or
   // or relative to the library path possibly passed as "userParam"

   bool path_explicit_absolute = (include.find_first_of("/\\") == 0)           // linux path or Windows network path \\server\folder
                              || (include.find_first_of(":") != string::npos); // Windows native path style "C:"
   bool path_explicit_relative = include.find_first_of(".") == 0;
   bool path_implicit_relative = (!path_explicit_absolute) && (!path_explicit_relative);

   // If the include path is not absolute,
   // then try prepending the path of the originating script
   if(!path_explicit_absolute)  {
      // either explicit or implicit relative
      full_path = path + include;
   }

   // if the file is found, we can try to compile it.
   // At this point it can be any of explicit_absolute, explicit_relative or implicit_relative
   // if not found, we silently ignore it at this stage
   if(as_file::file_exists(full_path)) {
      int r = builder->AddSectionFromFile(full_path.c_str());
      if(r < 0)return r;
      return 0;
   }

   // if we get here it means the file was not found above
   if(userParam && path_implicit_relative ) {

      // the specfied include was implicit relative
      // and we have a specified library include path

      // the user parameter is the include path
      string include_path = *((string*)userParam);
      full_path = include_path + include;
   }

   // we don't pre-check for file existence here,
   // as we want a script error message if the file really does not exist
   int r = builder->AddSectionFromFile(full_path.c_str());
   if(r < 0)return r;
   return 0;

}
