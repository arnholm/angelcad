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

#include "sphere.h"

void sphere::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted sphere type
   DeclareType<sphere>(engine,"sphere, centered at origin");

    // Declare allowed type conversion between sphere(=derived) and solid(=base)
   DeclareCast<sphere,solid>(engine);
   DeclareCast<sphere,shape>(engine);

   // Declare the sphere constructors
   DeclareConstructors(engine);

   // Inherit any methods from in this class + declare the unique sphere methods
   sphere::DeclareMethods<sphere>(engine);
}

solid* sphere::clone_solid() const
{
   return new sphere(*this);
}

sphere::sphere(double r)
: solid(as_typeid<sphere>())
, m_radius(r)
{}

sphere::sphere()
: solid(as_typeid<sphere>())
, m_radius(0)
{}

sphere::~sphere()
{}

double sphere::radius() const
{
   return m_radius;
}

string sphere::openscad_csg() const
{
   ostringstream out;
   out << "sphere( r=" << setprecision(12) << m_radius << " );";
   return out.str();
}


spaceio::xml_node sphere::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xml_this.add_property("r",m_radius);
   return xml_this;
}

bbox3d sphere::get_box() const
{
   return get_transform()*bbox3d(pos3d(-m_radius,-m_radius,-m_radius),pos3d(+m_radius,+m_radius,+m_radius));
}
