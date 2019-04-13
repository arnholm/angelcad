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
   
#ifndef SOLID_VECTOR_H
#define SOLID_VECTOR_H


class CScriptArray;
#include <vector>
using namespace std;
class solid;

// the purpose of solid_vector is to be a class member of
// union, intersection, difference etc., i.e. any object holding a collection of solids
//
// The main idea is to construct solid_vector by cloning every input solid(s)
// so that all objects contained here always have reference count=1, i.e. uniqe ownership.
// Observe the copy constructor which has an important role when copying union etc.

class solid_vector {
public:
   /// \privatesection (hidden in documentation)

   solid_vector();
   solid_vector(const solid* solid);
   solid_vector(const CScriptArray* arr);
   solid_vector(const solid_vector& other);

   virtual ~solid_vector();

   // clear
   void clear();

   // return size
   size_t size() const;

   // reserve size
   void reserve(size_t sz);

   // read only operator
   const solid* operator[](size_t index) const;

   // non-const access
   solid* operator[](size_t index);

   // insert a value at the end
   void push_back(const solid* solid);

private:
   vector<solid*> m_solids;
};

#endif // SOLID_VECTOR_H
