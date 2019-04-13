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
   
#include "difference3d.h"
#include "xcsg_vector.h"

void difference3d::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<difference3d>(engine,"3d difference boolean operation");

    // Declare allowed type conversion between csg_sphere(=derived) and solid(=base)
   DeclareCast<difference3d,solid>(engine);
   DeclareCast<difference3d,shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);
   // Inherit any methods
   difference3d::DeclareMethods<difference3d>(engine);
}

solid* difference3d::clone_solid() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new difference3d(*this);
}

difference3d::~difference3d()
{}

difference3d::difference3d(const solid* incl, const solid*  excl)
: solid(as_typeid<difference3d>())
, m_incl(incl)
, m_excl(excl)
{}

void difference3d::populate_tree(node_csg* node)
{
   node_csg* this_node = new node_csg(this);
   node->push_back(this_node);

   for(size_t i=0;i<m_incl.size(); i++) {
      solid* solid = m_incl[i];
      if(solid)solid->populate_tree(this_node);
   }

   for(size_t i=0;i<m_excl.size(); i++) {
      solid* solid = m_excl[i];
      if(solid)solid->populate_tree(this_node);
   }
}

string difference3d::openscad_csg() const
{
   return "difference()";
}


spaceio::xml_node difference3d::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   xcsg_vector<solid_vector> inc(m_incl);
   inc.to_xcsg(xml_this);

   xcsg_vector<solid_vector> exc(m_excl);
   exc.to_xcsg(xml_this);

   return xml_this;
}

bbox3d difference3d::get_box() const
{
   bbox3d box1;
   for(size_t i=0;i<m_incl.size(); i++) {
      const solid* body = m_incl[i];
      bbox3d shape_box = body->get_box();
      box1.enclose(shape_box.p1());
      box1.enclose(shape_box.p2());
   }

   bbox3d box2;
   for(size_t i=0;i<m_excl.size(); i++) {
      const solid* body = m_excl[i];
      bbox3d shape_box = body->get_box();
      box2.enclose(shape_box.p1());
      box2.enclose(shape_box.p2());
   }
   return get_transform()*box1.difference(box2);
}
