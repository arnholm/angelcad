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
   
#ifndef AS_TYPEID_H
#define AS_TYPEID_H

#include <string>
#include <typeinfo>

/// return typeid string for any given class type_info
std::string as_class_name(const std::type_info& type);

/// return typeid string for any given class (template parameter)
template<class T> std::string as_typeid() { return as_class_name(typeid(T)); }
template<class T> std::string as_typeid(const T* object) { return as_class_name(typeid(*object)); }

#endif // AS_TYPEID_H
