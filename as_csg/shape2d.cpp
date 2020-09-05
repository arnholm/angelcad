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

#include "shape2d.h"
#include <fstream>
#include <iostream>
using namespace std;
#include "tmatrix.h"

#include "union2d.h"
#include "difference2d.h"
#include "intersection2d.h"

void shape2d::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   // DeclareType<shape2d>(engine);

   // Declare allowed type conversion between cone(=derived) and solid(=base)
   DeclareCast<shape2d,shape>(engine);

   // no constructors here, this is an abstract class

   // Declare the shape2d methods
   shape::DeclareMethods<shape2d>(engine);
   shape2d::DeclareMethods<shape2d>(engine);
}

shape2d::shape2d(const shape2d& other)
: shape(other.Type())
, m_transform(other.m_transform)
{}

shape2d::shape2d(const std::string& type)
: shape(type)
{}

shape2d::~shape2d()
{}

HTmatrix shape2d::get_transform() const
{
   return m_transform;
}

shape* shape2d::clone_shape() const
{
   return clone_shape2d();
}

shape2d* shape2d::clone_transform(const tmatrix* matrix) const
{
//   cout << "shape2d::clone_transform from " << this << endl;
   return clone_shape2d()->transform(matrix);
}

shape2d* shape2d::transform(const tmatrix* matrix)
{
   if(matrix) m_transform = m_transform * matrix->matrix();
   return this;
}

shape2d* shape2d::transform(const HTmatrix& matrix)
{
   m_transform = m_transform * matrix;
   return this;
}

void shape2d::populate_tree(node_csg* node)
{
   node->push_back(new node_csg(this));
}


spaceio::xml_node& shape2d::transform(spaceio::xml_node& xml_parent)
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


shape2d* shape2d::opAdd(const shape2d* b)
{
   return new union2d(this,b);
}

shape2d* shape2d::opSub(const shape2d* b)
{
   return new difference2d(this,b);
}

shape2d* shape2d::opAnd(const shape2d* b)
{
   return new intersection2d(this,b);
}
