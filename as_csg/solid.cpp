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
   
#include "solid.h"
#include <fstream>
#include <iostream>
using namespace std;
#include "tmatrix.h"
#include "union3d.h"
#include "difference3d.h"
#include "intersection3d.h"

void solid::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   // DeclareType<solid>(engine);

   // no constructors here, this is an abstract class
   DeclareCast<solid,shape>(engine);
   DeclareCast<solid,shape>(engine);

   // Declare the solid methods
   shape::DeclareMethods<solid>(engine);
   solid::DeclareMethods<solid>(engine);
}

solid::solid(const std::string& type)
: shape(type)
{}

solid::~solid()
{}

HTmatrix solid::get_transform() const
{
   return m_transform;
}

shape* solid::clone_shape() const
{
   return clone_solid();
}

solid* solid::clone_transform(const tmatrix* matrix) const
{
   return clone_solid()->transform(matrix);
}

solid* solid::transform(const tmatrix* matrix)
{
   if(matrix) m_transform = matrix->matrix() * m_transform;
   return this;
}

spaceio::xml_node& solid::transform(spaceio::xml_node& xml_parent)
{
   HTmatrix identity;

   // add transform if different from identity
   double sum = 0.0;
   for(size_t irow=0; irow<4; irow++) {
      for(size_t icol=0; icol<4; icol++) {
         sum += fabs(m_transform(irow,icol) - identity(irow,icol));
      }
   }

   if(sum > 0.0) {
      spaceio::xml_node xml_this = xml_parent.add_child(as_typeid<tmatrix>());
      for(size_t irow=0; irow<4; irow++) {
         spaceio::xml_node xml_row = xml_this.add_child("trow");
         for(size_t icol=0; icol<4; icol++) {
            ostringstream out;
            out << 'c' << icol;
            xml_row.add_property(out.str(),m_transform(irow,icol));
         }
      }
   }
   return xml_parent;
}

solid* solid::opAdd(const solid* b)
{
   return new union3d(this,b);
}

solid* solid::opSub(const solid* b)
{
   return new difference3d(this,b);
}

solid* solid::opAnd(const solid* b)
{
   return new intersection3d(this,b);
}
