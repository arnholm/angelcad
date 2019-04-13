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
   
#include "union3d.h"
#include <iostream>
#include "xcsg_vector.h"

void union3d::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<union3d>(engine,"3d union boolean operation");

    // Declare allowed type conversion between csg_sphere(=derived) and solid(=base)
   DeclareCast<union3d,solid>(engine);
   DeclareCast<union3d,shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);

   // Inherit any methods
   union3d::DeclareMethods<union3d>(engine);
}

solid* union3d::clone_solid() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new union3d(*this);
}

union3d::union3d(const CScriptArray* arr)
: solid(as_typeid<union3d>())
, m_incl(arr)
{}

union3d::union3d(const solid* s1, const solid* s2, const solid* s3, const solid* s4, const solid* s5)
: solid(as_typeid<union3d>())
{
   // push_back will check for zero pointers, so just push them all (they will be cloned)
   m_incl.push_back(s1);
   m_incl.push_back(s2);
   m_incl.push_back(s3);
   m_incl.push_back(s4);
   m_incl.push_back(s5);
}

void union3d::populate_tree(node_csg* node)
{
 //  cout << "union3d::populate_tree this=" << this << endl;

   node_csg* this_node = new node_csg(this);
   node->push_back(this_node);

   for(size_t i=0;i<m_incl.size(); i++) {
      solid* solid = m_incl[i];
 //      cout << "union3d::populate_tree incl=" << solid << endl;
      if(solid)solid->populate_tree(this_node);
   }
}

union3d::~union3d()
{}

string union3d::openscad_csg() const
{
   return "union()";
}

spaceio::xml_node union3d::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   xcsg_vector<solid_vector> vec(m_incl);
   vec.to_xcsg(xml_this);

   return xml_this;
}


bbox3d union3d::get_box() const
{
   bbox3d box;
   for(size_t i=0;i<m_incl.size(); i++) {
      const solid* body = m_incl[i];
      bbox3d shape_box = body->get_box();
      box.enclose(shape_box.p1());
      box.enclose(shape_box.p2());
   }
   return get_transform()*box;
}
