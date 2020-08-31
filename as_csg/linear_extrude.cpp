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

#include "linear_extrude.h"
#include "xcsg_vector.h"

void linear_extrude::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<linear_extrude>(engine,"Extrude 2d shape in z direction into 3d solid");

    // Declare allowed type conversion between csg_sphere(=derived) and solid(=base)
   DeclareCast<linear_extrude,solid>(engine);
   DeclareCast<linear_extrude,::shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);

   // Inherit any methods
   linear_extrude::DeclareMethods<linear_extrude>(engine);
}

solid* linear_extrude::clone_solid() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new linear_extrude(*this);
}

linear_extrude::linear_extrude(const shape2d* shape, double height)
: solid(as_typeid<linear_extrude>())
, m_shapes(shape)
, m_height(height)
{}

const shape2d* linear_extrude::shape() const
{
   return m_shapes[0];  // clone?
}

double linear_extrude::height() const
{
   return m_height;
}

void linear_extrude::populate_tree(node_csg* node)
{
   node_csg* this_node = new node_csg(this);
   node->push_back(this_node);

   m_shapes[0]->populate_tree(this_node);
}

linear_extrude::~linear_extrude()
{}

string linear_extrude::openscad_csg() const
{
   ostringstream out;
   out << setprecision(12) << "linear_extrude( height=" << m_height << ")";

   return out.str();
}

spaceio::xml_node linear_extrude::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xml_this.add_property("dz",m_height);

   xcsg_vector<shape2d_vector> vec(m_shapes);
   vec.to_xcsg(xml_this);

   return xml_this;
}

bbox3d linear_extrude::get_box() const
{
   // compute the 2d box
   bbox3d box;
   for(size_t i=0;i<m_shapes.size(); i++) {
      const shape2d* body = m_shapes[i];
      bbox3d shape_box = body->get_box();
      box.enclose(shape_box.p1());
      box.enclose(shape_box.p2());
   }

   // add the 3rd dimension
   pos3d p = box.p2();
   box.enclose(pos3d(p.x(),p.y(),m_height));

   return get_transform()*box;
}
