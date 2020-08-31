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

#include "rotate_extrude.h"
#include "xcsg_vector.h"

static const double pi=4.0*atan(1.0);

void rotate_extrude::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<rotate_extrude>(engine,"Extrude 2d shape CCW in XZ plane into 3d solid");

    // Declare allowed type conversion between csg_sphere(=derived) and solid(=base)
   DeclareCast<rotate_extrude,solid>(engine);
   DeclareCast<rotate_extrude,::shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);

   // Inherit any methods
   rotate_extrude::DeclareMethods<rotate_extrude>(engine);
}

solid* rotate_extrude::clone_solid() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new rotate_extrude(*this);
}

rotate_extrude::rotate_extrude(const shape2d* shape, double angle, double pitch)
: solid(as_typeid<rotate_extrude>())
, m_shapes(shape)
, m_angle(angle)
, m_pitch(pitch)
{}

const shape2d* rotate_extrude::shape() const
{
   return m_shapes[0];  // clone?
}


void rotate_extrude::populate_tree(node_csg* node)
{
   node_csg* this_node = new node_csg(this);
   node->push_back(this_node);

   m_shapes[0]->populate_tree(this_node);
}

rotate_extrude::~rotate_extrude()
{}

string rotate_extrude::openscad_csg() const
{
   ostringstream out;
   out << setprecision(12) << "multmatrix([[1,0,0,0],[0,0,-1,0],[0,-1,0,0],[0,0,0,1]]) rotate_extrude( angle=" << -180.*m_angle/pi << ", pitch="<< m_pitch <<")";

   return out.str();
}

spaceio::xml_node rotate_extrude::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xml_this.add_property("angle",m_angle);
   xml_this.add_property("pitch",m_pitch);

   xcsg_vector<shape2d_vector> vec(m_shapes);
   vec.to_xcsg(xml_this);
   return xml_this;
}


bbox3d rotate_extrude::get_box() const
{
   bbox3d box;
   for(size_t i=0;i<m_shapes.size(); i++) {
      const shape2d* body = m_shapes[i];
      bbox3d shape_box = body->get_box();
      box.enclose(shape_box.p1());
      box.enclose(shape_box.p2());
   }

   pos3d p1base = box.p1();
   pos3d p2base = box.p2();

   double revs = fabs(m_angle)/(2*pi);

   // we have to iterate here
   double angle = 0.0;
   double dang  = -0.5*pi;  // rotate around  y, but CCW
   bool iterate = true;
   while(iterate) {

      if(fabs(angle) > fabs(m_angle)) {
         angle   = -m_angle;
         iterate = false;
      }

      // translate in y
      HTmatrix translate;
      translate(0,3) = 0.0;
      translate(1,3) = -(angle/m_angle)*revs*m_pitch;
      translate(2,3) = 0.0;

      // rotate around  y, but CCW
      double sinang = sin(angle);
      double cosang = cos(angle);

      HTmatrix rot;
      rot(0,0) = cosang;  rot(2,0) = -sinang;
      rot(0,2) = sinang;  rot(2,2) =  cosang;

      HTmatrix transf = rot*translate;

      pos3d p1 = transf * p1base;
      pos3d p2 = transf * p2base;

      box.enclose(p1);
      box.enclose(p2);

      angle += dang;
   }
   return get_transform()*box;
}
