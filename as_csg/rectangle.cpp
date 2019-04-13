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
   
#include "rectangle.h"
#include <sstream>

void rectangle::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted rectangle type
   DeclareType<rectangle>(engine,"rectangle, by default located in 1st quadrant touching origin");

   // Declare allowed type conversion between rectangle(=derived) and shape2d(=base)
   DeclareCast<rectangle,shape2d>(engine);
   DeclareCast<rectangle,shape>(engine);

   // Declare the rectangle constructors
   DeclareConstructors(engine);
   // Inherit any methods + declare the unique rectangle methods
   rectangle::DeclareMethods<rectangle>(engine);
}

shape2d* rectangle::clone_shape2d() const
{
   return new rectangle(*this);
}

rectangle::rectangle(double dx, double dy, bool center)
: shape2d(as_typeid<rectangle>())
, m_dx(dx)
, m_dy(dy)
, m_center(center)
{}

rectangle::~rectangle()
{}

double rectangle::dx() const
{
   return m_dx;
}

double rectangle::dy() const
{
   return m_dy;
}

string rectangle::openscad_csg() const
{
   ostringstream out;
   out << setprecision(12) << "square( size=["  << m_dx << ", " << m_dy <<"] , center=" << ((m_center)? "true":"false") << ");";
   return out.str();
}

spaceio::xml_node rectangle::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xml_this.add_property("dx",m_dx);
   xml_this.add_property("dy",m_dy);
   xml_this.add_property("center",((m_center)? "true":"false") );
   return xml_this;
}

bbox3d rectangle::get_box() const
{
   double xmin = (m_center)? -m_dx*0.5 : 0.0;
   double xmax = (m_center)? +m_dx*0.5 : m_dx;
   double ymin = (m_center)? -m_dy*0.5 : 0.0;
   double ymax = (m_center)? +m_dy*0.5 : m_dy;

   return get_transform()*bbox3d(pos3d(xmin,ymin,0),pos3d(xmax,ymax,0));
}
