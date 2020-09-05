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

#include "minkowski3d.h"
#include <iostream>
#include "xcsg_vector.h"

void minkowski3d::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<minkowski3d>(engine,"3d Minkowski sum operation");

    // Declare allowed type conversion between csg_sphere(=derived) and solid(=base)
   DeclareCast<minkowski3d,solid>(engine);
   DeclareCast<minkowski3d,shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);

   // Inherit any methods
   minkowski3d::DeclareMethods<minkowski3d>(engine);
}

solid* minkowski3d::clone_solid() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new minkowski3d(*this);
}

minkowski3d::minkowski3d(const solid* a, const solid* b)
: solid(as_typeid<minkowski3d>())
{
   if(a == 0)throw logic_error("minkowski3d: parameter a cannot be null");
   if(b == 0)throw logic_error("minkowski3d: parameter b cannot be null");

   // push_back will check for zero pointers
   m_incl.push_back(a);
   m_incl.push_back(b);
}


void minkowski3d::populate_tree(node_csg* node)
{
   node_csg* this_node = new node_csg(this);
   node->push_back(this_node);

   for(size_t i=0;i<m_incl.size(); i++) {
      solid* solid = m_incl[i];
      if(solid)solid->populate_tree(this_node);
   }
}

minkowski3d::~minkowski3d()
{}

string minkowski3d::openscad_csg() const
{
   return "minkowski()";
}


bbox3d minkowski3d::get_box() const
{
   const solid* a = m_incl[0];
   const solid* b = m_incl[1];

   // compute minkowski sum of bounding boxes
   bbox3d a_box = a->get_box();
   bbox3d b_box = b->get_box();

   bbox3d box;
   box.enclose(a_box.p1()+b_box.p1());
   box.enclose(a_box.p1()+b_box.p2());
   box.enclose(a_box.p2()+b_box.p1());
   box.enclose(a_box.p2()+b_box.p2());

   return get_transform()*box;
}

spaceio::xml_node minkowski3d::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   xcsg_vector<solid_vector> vec(m_incl);
   vec.to_xcsg(xml_this);

   return xml_this;
}
