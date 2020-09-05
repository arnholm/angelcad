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

#include "hull3d.h"
#include <iostream>
#include "xcsg_vector.h"

void hull3d::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<hull3d>(engine,"3d hull operation, enclosing the input solids");

    // Declare allowed type conversion between csg_sphere(=derived) and solid(=base)
   DeclareCast<hull3d,solid>(engine);
   DeclareCast<hull3d,shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);

   // Inherit any methods
   hull3d::DeclareMethods<hull3d>(engine);
}

solid* hull3d::clone_solid() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new hull3d(*this);
}

hull3d::hull3d(const CScriptArray* arr)
: solid(as_typeid<hull3d>())
, m_incl(arr)
{}

hull3d::hull3d(const solid* s1, const solid* s2, const solid* s3, const solid* s4, const solid* s5)
: solid(as_typeid<hull3d>())
{
   // push_back will check for zero pointers, so just push them all (they will be cloned)
   m_incl.push_back(s1);
   m_incl.push_back(s2);
   m_incl.push_back(s3);
   m_incl.push_back(s4);
   m_incl.push_back(s5);
}


void hull3d::populate_tree(node_csg* node)
{
   node_csg* this_node = new node_csg(this);
   node->push_back(this_node);

   for(size_t i=0;i<m_incl.size(); i++) {
      solid* solid = m_incl[i];
      if(solid)solid->populate_tree(this_node);
   }
}

hull3d::~hull3d()
{}

string hull3d::openscad_csg() const
{
   return "hull()";
}

spaceio::xml_node hull3d::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   xcsg_vector<solid_vector> vec(m_incl);
   vec.to_xcsg(xml_this);

   return xml_this;
}


bbox3d hull3d::get_box() const
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
