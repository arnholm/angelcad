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

#include "cube.h"
#include <sstream>

void cube::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted cube type
   DeclareType<cube>(engine,"cube, by default in 1st octant with one corner toucing origin");

   // Declare allowed type conversion between cube(=derived) and solid(=base)
   DeclareCast<cube,solid>(engine);
   DeclareCast<cube,shape>(engine);

   // Declare the cube constructors
   DeclareConstructors(engine);
   // Inherit any methods + declare the unique cube methods
   cube::DeclareMethods<cube>(engine);
}

solid* cube::clone_solid() const
{
   return new cube(*this);
}

cube::cube(double size, bool center)
: solid(as_typeid<cube>())
, m_size(size)
, m_center(center)
{}

cube::~cube()
{}

double cube::size() const
{
   return m_size;
}

string cube::openscad_csg() const
{
   ostringstream out;
   out << setprecision(12) << "cube( size=["  << m_size << ", " << m_size << ", " << m_size << "]"<< ", center="<< ((m_center)? "true":"false") <<" );";
   return out.str();
}

spaceio::xml_node cube::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xml_this.add_property("size",m_size);
   xml_this.add_property("center",((m_center)? "true":"false") );
   return xml_this;
}


bbox3d cube::get_box() const
{
   double dmin = (m_center)? -m_size*0.5 : 0.0;
   double dmax = (m_center)? +m_size*0.5 : m_size;

   return get_transform()*bbox3d(pos3d(dmin,dmin,dmin),pos3d(dmax,dmax,dmax));
}
