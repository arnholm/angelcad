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
   
#ifndef AS_VECTOR_H
#define AS_VECTOR_H

#include "ce_angelscript/ce_angelscript.h"
#include "ce_angelscript/add_on/scriptarray/scriptarray.h"

// as_vector is a minimal STL-like read-only adapter around CScriptArray when it is used as input parameter
// as_vector does NOT copy or own any data, it just provides a different and simplified "view" on the existing array.
// as_vector must therefore only be used as a temporary stack variable in functions taking CScriptArray* parameters
// The main goals are
// - provide easy vector-like read access using size() and operator[]
// - hide implementation details on how CScriptArray handles things like pointers to pointers etc
// - provide easy conversion to std::vector<T>
//
// Inverse functionality is creating CScriptArray from an STL vector.
// This is done using the CreateScriptArray template function, typically when returning data to scripts
// example:
//
// CScriptArray* func()
// {
//    vector<double> vec = { 0.0, 2.0, -3.0 };
//    return CreateScriptArray<double>(vec);
// }
//

#include "as_typeid.h"
#include <vector>

template <class T>
class as_vector {
public:

   // construct by taking a shallow copy of the CScriptArray
   as_vector(const CScriptArray* arr);
   virtual ~as_vector();

   // return size
   size_t size() const;

   // read only operator
   const T operator[](size_t index) const;

   // create std::vector<T> copy
   std::vector<T> std_vector() const;

private:
   const CScriptArray* m_arr;
};

template <class T>
as_vector<T>::as_vector(const CScriptArray* arr)
: m_arr(arr)
{}

template <class T>
as_vector<T>::~as_vector()
{}

template <class T>
size_t as_vector<T>::size() const
{
   return (size_t)m_arr->GetSize();
}

template <class T>
const T as_vector<T>::operator[](size_t index) const
{
   asUINT i = (asUINT)index;
   const void* p = m_arr->At(i);
   const T object = *(const T*)p ;
   return object;
}


template <class T>
std::vector<T> as_vector<T>::std_vector() const
{
   std::vector<T> v(size());
   for(size_t i=0;i<size();i++) v[i] = (*this)[i];
   return std::move(v);
}

// ==== helper functions for creating script arrays in C++

CScriptArray* CreateScriptArrayEmpty(const std::string& type, size_t len);

template <class T>
CScriptArray* CreateScriptArray(const std::vector<T>& vec)
{
   // 2-step construction, first create empty typed array, then assign values
   CScriptArray* arr = CreateScriptArrayEmpty(as_typeid<T>(),vec.size());
   for(size_t i=0; i<vec.size(); i++) arr->SetValue((asUINT)i,const_cast<T*>(&vec[i]));
   return arr;
}

#endif // AS_VECTOR_H
