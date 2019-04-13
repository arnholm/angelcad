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
   
#include "as_typeid.h"


#ifndef  _MSC_VER
    /// GCC implements the Itanium C++ ABI, specified here:
    /// http://www.codesourcery.com/public/cxx-abi/abi.html
    #include <cxxabi.h>
#endif

std::string as_class_name(const std::type_info& type)
{
   std::string name = type.name();

#ifdef _MSC_VER
   /// For MSVC we can demangle by simply erasing the initial "class " part of the raw name when the type is a class
   /// for non-classes we do nothing
   if(name.find_first_of("class ")==0) {
      name.erase(0,6);
   }
#else
   /// Linux GNU g++
   /// Using demangler API of the Itanium C++ ABI
   /// Example in http://groups.google.com/group/gnu.g++.help/browse_thread/thread/ff412fbab4fb4eca
   size_t len=0;
   int s=0;
   char* p = abi::__cxa_demangle(name.c_str(),0,&len,&s);
   name = p;
#endif
   return name;
}
