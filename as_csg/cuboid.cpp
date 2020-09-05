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

#include "cuboid.h"
#include <sstream>

void cuboid::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted cuboid type
   DeclareType<cuboid>(engine,"cuboid, by default in 1st octant with one corner toucing origin");

   // Declare allowed type conversion between cuboid(=derived) and solid(=base)
   DeclareCast<cuboid,solid>(engine);
   DeclareCast<cuboid,shape>(engine);

   // Declare the cuboid constructors
   DeclareConstructors(engine);
   // Inherit any methods + declare the unique cuboid methods
   cuboid::DeclareMethods<cuboid>(engine);
}

solid* cuboid::clone_solid() const
{
   return new cuboid(*this);
}

cuboid::cuboid(double dx, double dy, double dz, bool center)
: solid(as_typeid<cuboid>())
, m_dx(dx)
, m_dy(dy)
, m_dz(dz)
, m_center(center)
{}

cuboid::~cuboid()
{}

double cuboid::dx() const
{
   return m_dx;
}

double cuboid::dy() const
{
   return m_dy;
}

double cuboid::dz() const
{
   return m_dz;
}

string cuboid::openscad_csg() const
{
   ostringstream out;
   out << setprecision(12) << "cube( size=["  << m_dx << ", " << m_dy << ", " << m_dz << "] "<< ", center="<< ((m_center)? "true":"false") <<  " );";
   return out.str();
}

spaceio::xml_node cuboid::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xml_this.add_property("dx",m_dx);
   xml_this.add_property("dy",m_dy);
   xml_this.add_property("dz",m_dz);
   xml_this.add_property("center",((m_center)? "true":"false") );

   return xml_this;
}


bbox3d cuboid::get_box() const
{
   double xmin = (m_center)? -m_dx*0.5 : 0.0;
   double ymin = (m_center)? -m_dy*0.5 : 0.0;
   double zmin = (m_center)? -m_dz*0.5 : 0.0;

   double xmax = (m_center)? +m_dx*0.5 : m_dx;
   double ymax = (m_center)? +m_dy*0.5 : m_dy;
   double zmax = (m_center)? +m_dz*0.5 : m_dz;

   return get_transform()*bbox3d(pos3d(xmin,ymin,zmin),pos3d(xmax,ymax,zmax));
}
