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
   
#include "cone.h"
#include <sstream>

void cone::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted cone type
   DeclareType<cone>(engine,"cone with axis in z-direction, by default extending from origin");

   // Declare allowed type conversion between cone(=derived) and solid(=base)
   DeclareCast<cone,solid>(engine);
   DeclareCast<cone,shape>(engine);

   // Declare the cone constructors
   DeclareConstructors(engine);
   // Inherit any methods + declare the unique cone methods
   cone::DeclareMethods<cone>(engine);
}

solid* cone::clone_solid() const
{
   return new cone(*this);
}

cone::cone(double h, double r1, double r2, bool center)
: solid(as_typeid<cone>())
, m_height(h)
, m_radius1(r1)
, m_radius2(r2)
, m_center(center)
{}

cone::~cone()
{}

/*
void cone::populate_tree(node_csg* node)
{
   node->push_back(new node_csg(this));
}
*/

double cone::height() const
{
   return m_height;
}

double cone::radius1() const
{
   return m_radius1;
}

double cone::radius2() const
{
   return m_radius2;
}


string cone::openscad_csg() const
{
   ostringstream out;
   out << "cylinder( r1=" << setprecision(12) << m_radius1 << ", r2=" <<m_radius2 << ", h=" << m_height << ", center="<< ((m_center)? "true":"false") << " );";
   return out.str();
}

spaceio::xml_node cone::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xml_this.add_property("h",m_height);
   xml_this.add_property("r1",m_radius1);
   xml_this.add_property("r2",m_radius2);
   xml_this.add_property("center",((m_center)? "true":"false") );
   return xml_this;
}


bbox3d cone::get_box() const
{
   double radius = std::max(m_radius1,m_radius2);
   double zmin   = (m_center)? -m_height*0.5 : 0.0;
   double zmax   = (m_center)? +m_height*0.5 : m_height;

   return get_transform()*bbox3d(pos3d(-radius,-radius,zmin),pos3d(+radius,+radius,zmax));
}
