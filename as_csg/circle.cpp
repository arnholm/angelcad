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

#include "circle.h"
#include "pos2.h"
#include "spacemath/circle2d.h"

using namespace spacemath;

void circle::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted circle type
   DeclareType<circle>(engine,"circle, centered at origin");

    // Declare allowed type conversion between circle(=derived) and shape2d(=base)
   DeclareCast<circle,shape2d>(engine);
   DeclareCast<circle,shape>(engine);

   // Declare the circle constructors
   DeclareConstructors(engine);

   // Inherit any methods from in this class + declare the unique circle methods
   circle::DeclareMethods<circle>(engine);
}

shape2d* circle::clone_shape2d() const
{
   return new circle(*this);
}

circle::circle(double r)
: shape2d(as_typeid<circle>())
, m_radius(r)
{}

circle::circle(const pos2* p1, const pos2* p2, const pos2* p3)
: shape2d(as_typeid<circle>())
, m_radius(0.0)
{
   // compute center and radius
   pos2d center;
   circle2d::circle_3p(*p1,*p2,*p3,center,m_radius);

   if(!(m_radius > 0)) {
      string message = "circle exception: The circle radius is zero";
      throw logic_error(message);
   }

   // apply center as transformation
   HTmatrix T;
   T(0,3) = center.x();
   T(1,3) = center.y();
   T(2,3) = 0.0;
   transform(T);
}


circle::circle()
: shape2d(as_typeid<circle>())
, m_radius(0)
{}

circle::~circle()
{}

double circle::radius() const
{
   return m_radius;
}

string circle::openscad_csg() const
{
   ostringstream out;
   out << "circle( r=" << setprecision(12) << m_radius << " );";
   return out.str();
}

spaceio::xml_node circle::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xml_this.add_property("r",m_radius);
   return xml_this;
}

bbox3d circle::get_box() const
{
   return get_transform()*bbox3d(pos3d(-m_radius,-m_radius,0),pos3d(+m_radius,+m_radius,0));
}
