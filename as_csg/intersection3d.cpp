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

#include "intersection3d.h"
#include "xcsg_vector.h"

void intersection3d::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<intersection3d>(engine,"3d intersection boolean operation");

    // Declare allowed type conversion between csg_sphere(=derived) and solid(=base)
   DeclareCast<intersection3d,solid>(engine);
   DeclareCast<intersection3d,shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);
   // Inherit any methods
   intersection3d::DeclareMethods<intersection3d>(engine);
}

solid* intersection3d::clone_solid() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new intersection3d(*this);
}

intersection3d::~intersection3d()
{}

intersection3d::intersection3d(const CScriptArray* arr)
: solid(as_typeid<intersection3d>())
, m_incl(arr)
{}

intersection3d::intersection3d(const solid* s1, const solid* s2, const solid* s3, const solid* s4, const solid* s5)
: solid(as_typeid<intersection3d>())
{
   // push_back will check for zero pointers, so just push them all (they will be cloned)
   m_incl.push_back(s1);
   m_incl.push_back(s2);
   m_incl.push_back(s3);
   m_incl.push_back(s4);
   m_incl.push_back(s5);
}

void intersection3d::populate_tree(node_csg* node)
{
   node_csg* this_node = new node_csg(this);
   node->push_back(this_node);

   for(size_t i=0;i<m_incl.size(); i++) {
      solid* solid = m_incl[i];
      if(solid)solid->populate_tree(this_node);
   }
}

string intersection3d::openscad_csg() const
{
   return "intersection()";
}

spaceio::xml_node intersection3d::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   xcsg_vector<solid_vector> inc(m_incl);
   inc.to_xcsg(xml_this);

   return xml_this;
}


bbox3d intersection3d::get_box() const
{
   bbox3d box1;
   for(size_t i=0;i<m_incl.size(); i++) {
      const solid* body = m_incl[i];
      bbox3d shape_box = body->get_box();
      if(i==0) {
         box1.enclose(shape_box.p1());
         box1.enclose(shape_box.p2());
      }
      else {
         box1 = box1.intersection(shape_box);
      }
   }

   return get_transform()*box1;
}
