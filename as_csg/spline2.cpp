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
   
#include "spline2.h"
#include <sstream>
#include "ce_angelscript_ex/as_vector.h"
#include "pos2.h"
#include "vec2.h"
#include <iostream>

using spacemath::pos2d;
using spacemath::vec2d;

void spline2::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted spline2d type
   DeclareTypeEx("spline2d",engine,"2d cubic spline curve");

   // Declare the spline2 constructors
   DeclareConstructors(engine);

   // Inherit any methods + declare the unique spline2 methods
   spline2::DeclareMethodsEx("spline2d",engine);
}

as_reftype* spline2::clone_scoped()
{
   return new spline2(*this);
}

spline2::spline2(const CScriptArray* points)
: as_reftype("spline2d")
{
   vector<pos2d> nodes;
   as_vector<pos2*> other(points);
   if(other.size() < 2) {
      string message = "spline2d exception: A spline2d must be specified with at least 2 points";
      cout << message << endl;
      throw logic_error(message);
   }
   for(size_t i=0; i<other.size(); i++) {
      pos2* pnt = other[i];
      nodes.push_back(*pnt);
   }

   m_spline.compute_spline(nodes);
}

spline2::spline2(const pos2* p1, const pos2* p2, const pos2* p3, const pos2* p4, const pos2* p5)
: as_reftype("spline2d")
{
   vector<pos2d> nodes;

   nodes.push_back(*p1);
   nodes.push_back(*p2);
   if(p3)nodes.push_back(*p3);
   if(p4)nodes.push_back(*p4);
   if(p5)nodes.push_back(*p5);

   m_spline.compute_spline(nodes);
}

spline2::~spline2()
{}

pos2* spline2::pos(double t) const
{
   pos2d p = m_spline.pos(t);
   return new pos2(p);
}

vec2* spline2::dir(double t) const
{
   return new vec2(m_spline.deriv1(t));
}

pos2d spline2::pos_raw(double t) const
{
   return m_spline.pos(t);
}

vec2d spline2::vec_raw(double t) const
{
   return m_spline.deriv1(t);
}

