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
   
#include "transform_extrude.h"
#include "xcsg_vector.h"

void transform_extrude::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<transform_extrude>(engine,"Extrude from botton to top shapes using transform");

    // Declare allowed type conversion between csg_sphere(=derived) and solid(=base)
   DeclareCast<transform_extrude,solid>(engine);
   DeclareCast<transform_extrude,::shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);

   // Inherit any methods
   transform_extrude::DeclareMethods<transform_extrude>(engine);
}

solid* transform_extrude::clone_solid() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new transform_extrude(*this);
}

transform_extrude::transform_extrude(const shape2d* bottom, const shape2d* top)
: solid(as_typeid<transform_extrude>())
{
   m_shapes.reserve(2);
   m_shapes.push_back(bottom);
   m_shapes.push_back(top);
}

const shape2d* transform_extrude::shape() const
{
   return m_shapes[0];  // clone?
}

void transform_extrude::populate_tree(node_csg* node)
{
   node_csg* this_node = new node_csg(this,false);
   node->push_back(this_node);

   m_shapes[0]->populate_tree(this_node);
}

transform_extrude::~transform_extrude()
{}

string transform_extrude::openscad_csg() const
{
   // we have to approximate transform_extrude() with linear extrude here
   // and speculate in "height" being the difference in z translation
   HTmatrix t0 = m_shapes[0]->get_transform();
   HTmatrix t1 = m_shapes[1]->get_transform();

   ostringstream out;
   out << setprecision(12) << "linear_extrude(height="<<t1(2,3)-t0(2,3)<<") // *** transform_extrude()";

   return out.str();
}

spaceio::xml_node transform_extrude::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   xcsg_vector<shape2d_vector> vec(m_shapes);
   vec.to_xcsg(xml_this);
   return xml_this;
}


bbox3d transform_extrude::get_box() const
{
   bbox3d box1 = m_shapes[0]->get_box();
   bbox3d box2 = m_shapes[1]->get_box();
   box1.enclose(box2.p1());
   box1.enclose(box2.p2());
   return get_transform()*box1;
}
