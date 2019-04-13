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
   
#include "shape2d_vector.h"
#include "shape2d.h"
#include "ce_angelscript_ex/as_vector.h"

shape2d_vector::shape2d_vector()
{}

shape2d_vector::shape2d_vector(const shape2d* shape)
{
   if(shape)m_shapes.push_back(shape->clone_shape2d());
}

shape2d_vector::shape2d_vector(const CScriptArray* arr)
{
   // the as_vector serves as our adapter to interpret the script array
   as_vector<shape2d*> other(arr);
   m_shapes.reserve(other.size());
   for(size_t i=0;i<other.size();i++) {
      shape2d* orig = other[i];
      if(orig) {
         shape2d* cloned = orig->clone_shape2d();
         // the clone should now have reference count = 1
         m_shapes.push_back(cloned);
      }
   }
}

shape2d_vector::shape2d_vector(const shape2d_vector& other)
{
   m_shapes.reserve(other.size());
   for(size_t i=0;i<other.size();i++) {
      const shape2d* orig = other[i];
      if(orig) {
         shape2d* cloned = orig->clone_shape2d();
         // the clone should now have reference count = 1
         m_shapes.push_back(cloned);
      }
   }
}

shape2d_vector::~shape2d_vector()
{
   clear();
}

void shape2d_vector::clear()
{
   // the shape2ds contained are unique in this context,
   // so we can simply Release them here, and they will die immediately
   for(size_t i=0;i<m_shapes.size();i++) {
      shape2d* shape2d = m_shapes[i];
      shape2d->Release();
   }
   m_shapes.clear();
}

size_t shape2d_vector::size() const
{
   return m_shapes.size();
}


void shape2d_vector::reserve(size_t sz)
{
   clear();
   m_shapes.reserve(sz);
}


const shape2d* shape2d_vector::operator[](size_t index) const
{
   return m_shapes[index];
}

shape2d* shape2d_vector::operator[](size_t index)
{
   return m_shapes[index];
}

void shape2d_vector::push_back(const shape2d* shape)
{
   if(shape)m_shapes.push_back(shape->clone_shape2d());
}
