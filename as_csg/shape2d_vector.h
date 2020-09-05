// BeginLicense:
// Part of: angelcad - script based 3D solid modeller
// Copyright (C) 2017-2020 Carsten Arnholm
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

#ifndef SHAPE2D_VECTOR_H
#define SHAPE2D_VECTOR_H


class CScriptArray;
#include <vector>
using namespace std;
class shape2d;

// the purpose of shape2d_vector is to be a class member of
// union2d, intersection2d, difference2d etc., i.e. any object holding a collection of shapes
//
// The main idea is to construct shape2d_vector by cloning every input shape(s)
// so that all objects contained here always have reference count=1, i.e. uniqe ownership.
// Observe the copy constructor which has an important role when copying union etc.

class shape2d_vector {
public:
   /// \privatesection (hidden in documentation)

   shape2d_vector();
   shape2d_vector(const shape2d* shape);
   shape2d_vector(const CScriptArray* arr);
   shape2d_vector(const shape2d_vector& other);

   virtual ~shape2d_vector();

   // clear
   void clear();

   // return size
   size_t size() const;

   // reserve size
   void reserve(size_t sz);

   // read only operator
   const shape2d* operator[](size_t index) const;

   // non-const access
   shape2d* operator[](size_t index);

   // insert a value at the end
   void push_back(const shape2d* shape);

private:
   vector<shape2d*> m_shapes;
};

#endif // SHAPE2D_VECTOR_H
