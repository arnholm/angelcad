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

#include "square.h"
#include <sstream>

void square::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted square type
   DeclareType<square>(engine,"square, by default located in 1st quadrant touching origin");

   // Declare allowed type conversion between square(=derived) and shape2d(=base)
   DeclareCast<square,shape2d>(engine);
   DeclareCast<square,shape>(engine);

   // Declare the square constructors
   DeclareConstructors(engine);
   // Inherit any methods + declare the unique square methods
   square::DeclareMethods<square>(engine);
}

shape2d* square::clone_shape2d() const
{
   return new square(*this);
}

square::square(double size, bool center)
: shape2d(as_typeid<square>())
, m_size(size)
, m_center(center)
{}

square::~square()
{}

double square::size() const
{
   return m_size;
}

string square::openscad_csg() const
{
   ostringstream out;
   out << setprecision(12) << "square( size=["  << m_size << ", " << m_size << "] , center=" << ((m_center)? "true":"false") << ");";
   return out.str();
}


spaceio::xml_node square::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);
   xml_this.add_property("size",m_size);
   xml_this.add_property("center",((m_center)? "true":"false") );
   return xml_this;
}


bbox3d square::get_box() const
{
   double dmin = (m_center)? -m_size*0.5 : 0.0;
   double dmax = (m_center)? +m_size*0.5 : m_size;

   return get_transform()*bbox3d(pos3d(dmin,dmin,0),pos3d(dmax,dmax,0));
}
