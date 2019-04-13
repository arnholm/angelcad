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
   
#include "cylinder.h"
#include <sstream>
#include <iostream>

void cylinder::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted cylinder type
   DeclareType<cylinder>(engine,"cylinder with axis in z-direction, by default extending from origin");

   // Declare allowed type conversion between cylinder(=derived) and solid(=base)
   DeclareCast<cylinder,solid>(engine);
   DeclareCast<cylinder,shape>(engine);

   // Declare the cylinder constructors
   DeclareConstructors(engine);
   // Inherit any methods + declare the unique cylinder methods
   cylinder::DeclareMethods<cylinder>(engine);
}

solid* cylinder::clone_solid() const
{
   return new cylinder(*this);
}

cylinder::cylinder(double h, double r, bool center)
: solid(as_typeid<cylinder>())
, m_height(h)
, m_radius(r)
, m_center(center)
{}

cylinder::~cylinder()
{}

double cylinder::height() const
{
   return m_height;
}

double cylinder::radius() const
{
   return m_radius;
}

string cylinder::openscad_csg() const
{
   ostringstream out;
   out << "cylinder( r1=" << setprecision(12) << m_radius << ", r2=" <<m_radius << ", h=" << m_height  << ", center="<< ((m_center)? "true":"false") << " );";
   return out.str();
}


spaceio::xml_node cylinder::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xml_this.add_property("h",m_height);
   xml_this.add_property("r",m_radius);
   xml_this.add_property("center",((m_center)? "true":"false") );

   return xml_this;
}


bbox3d cylinder::get_box() const
{
   double zmin   = (m_center)? -m_height*0.5 : 0.0;
   double zmax   = (m_center)? +m_height*0.5 : m_height;

   return get_transform()*bbox3d(pos3d(-m_radius,-m_radius,zmin),pos3d(+m_radius,+m_radius,zmax));
}
