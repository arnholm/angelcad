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

#include "intersection2d.h"
#include "xcsg_vector.h"

void intersection2d::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<intersection2d>(engine,"2d intersection boolean operation");

    // Declare allowed type conversion between csg_sphere(=derived) and shape2d(=base)
   DeclareCast<intersection2d,shape2d>(engine);
   DeclareCast<intersection2d,shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);
   // Inherit any methods
   intersection2d::DeclareMethods<intersection2d>(engine);
}

shape2d* intersection2d::clone_shape2d() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new intersection2d(*this);
}

intersection2d::~intersection2d()
{}


intersection2d::intersection2d(const CScriptArray* arr)
: shape2d(as_typeid<intersection2d>())
, m_incl(arr)
{}

intersection2d::intersection2d(const shape2d* s1, const shape2d* s2, const shape2d* s3, const shape2d* s4, const shape2d* s5)
: shape2d(as_typeid<intersection2d>())
{
   // push_back will check for zero pointers, so just push them all (they will be cloned)
   m_incl.push_back(s1);
   m_incl.push_back(s2);
   m_incl.push_back(s3);
   m_incl.push_back(s4);
   m_incl.push_back(s5);
}

void intersection2d::populate_tree(node_csg* node)
{
   node_csg* this_node = new node_csg(this);
   node->push_back(this_node);

   for(size_t i=0;i<m_incl.size(); i++) {
      shape2d* shape2d = m_incl[i];
      if(shape2d)shape2d->populate_tree(this_node);
   }
}

string intersection2d::openscad_csg() const
{
   return "intersection()";
}

spaceio::xml_node intersection2d::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   xcsg_vector<shape2d_vector> inc(m_incl);
   inc.to_xcsg(xml_this);

   return xml_this;
}


bbox3d intersection2d::get_box() const
{
   bbox3d box1;
   for(size_t i=0;i<m_incl.size(); i++) {
      const shape2d* shape2d = m_incl[i];
      bbox3d shape_box = shape2d->get_box();
      if(i == 0) {
         box1.enclose(shape_box.p1());
         box1.enclose(shape_box.p2());
      }
      else {
         box1 = box1.intersection(shape_box);
      }
   }

   return get_transform()*box1;
}
