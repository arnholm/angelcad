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
   
#include "solid_vector.h"
#include "solid.h"
#include "ce_angelscript_ex/as_vector.h"

solid_vector::solid_vector()
{}

solid_vector::solid_vector(const solid* solid)
{
   if(solid)m_solids.push_back(solid->clone_solid());
}

solid_vector::solid_vector(const CScriptArray* arr)
{
   // the as_vector serves as our adapter to interpret the script array
   as_vector<solid*> other(arr);
   m_solids.reserve(other.size());
   for(size_t i=0;i<other.size();i++) {
      solid* orig = other[i];

      if(orig) {
         solid* cloned = orig->clone_solid();
         // the clone should now have reference count = 1
         m_solids.push_back(cloned);
      }
   }
}

solid_vector::solid_vector(const solid_vector& other)
{
   m_solids.reserve(other.size());
   for(size_t i=0;i<other.size();i++) {
      const solid* orig = other[i];

      if(orig) {
         solid* cloned = orig->clone_solid();
         // the clone should now have reference count = 1
         m_solids.push_back(cloned);
      }
   }
}

solid_vector::~solid_vector()
{
   clear();
}

void solid_vector::clear()
{
   // the solids contained are unique in this context,
   // so we can simply Release them here, and they will die immediately
   for(size_t i=0;i<m_solids.size();i++) {
      solid* solid = m_solids[i];
      solid->Release();
   }
   m_solids.clear();
}

size_t solid_vector::size() const
{
   return m_solids.size();
}


void solid_vector::reserve(size_t sz)
{
   clear();
   m_solids.reserve(sz);
}


const solid* solid_vector::operator[](size_t index) const
{
   return m_solids[index];
}

solid* solid_vector::operator[](size_t index)
{
   return m_solids[index];
}

void solid_vector::push_back(const solid* solid)
{
   if(solid)m_solids.push_back(solid->clone_solid());
}
