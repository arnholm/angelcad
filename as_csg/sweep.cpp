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

#include "sweep.h"
#include "xcsg_vector.h"
#include "spline_path.h"

static const double pi=4.0*atan(1.0);

void sweep::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<sweep>(engine,"Sweep 2d shape along path curve to create 3d solid");

    // Declare allowed type conversion between csg_sphere(=derived) and solid(=base)
   DeclareCast<sweep,solid>(engine);
   DeclareCast<sweep,::shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);

   // Inherit any methods
   sweep::DeclareMethods<sweep>(engine);
}

solid* sweep::clone_solid() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new sweep(*this);
}

sweep::sweep(const shape2d* shape, const spline_path* path)
: solid(as_typeid<sweep>())
, m_shapes(shape)
{
   m_p = path->p();
   m_v = path->v();
}

sweep::~sweep()
{}

string sweep::openscad_csg() const
{
   ostringstream out;
   out << setprecision(12) << "sweep( )";

   return out.str();
}

spaceio::xml_node sweep::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xcsg_vector<shape2d_vector> vec(m_shapes);
   vec.to_xcsg(xml_this);

   size_t np = m_p.size();
   spaceio::xml_node xml_spline_path = xml_this.add_child("spline_path");
   for(size_t ip=0; ip<np; ip++) {
      const pos3d& p = m_p[ip];
      const vec3d& v = m_v[ip];

      spaceio::xml_node xml_cpoint = xml_spline_path.add_child("cpoint");
      xml_cpoint.add_property("x",p.x());
      xml_cpoint.add_property("y",p.y());
      xml_cpoint.add_property("z",p.z());

      xml_cpoint.add_property("vx",v.x());
      xml_cpoint.add_property("vy",v.y());
      xml_cpoint.add_property("vz",v.z());
   }

   return xml_this;
}


bbox3d sweep::get_box() const
{
   bbox3d box;
   return get_transform()*box;
}
