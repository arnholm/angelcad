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

#include "spline3.h"
#include <sstream>
#include "ce_angelscript_ex/as_vector.h"
#include "pos3.h"
#include "vec3.h"
#include <iostream>

void spline3::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted spline3 type
   DeclareTypeEx("spline3d",engine,"3d cubic spline curve");

   // Declare the spline3 constructors
   DeclareConstructors(engine);

   // Inherit any methods + declare the unique spline3 methods
   DeclareMethods<spline3>(engine);
}

as_reftype* spline3::clone_scoped()
{
   return new spline3(*this);
}

spline3::spline3(const CScriptArray* points)
: as_reftype("spline3d")
{
   vector<pos3d> nodes;
   as_vector<pos3*> other(points);
   if(other.size() < 2) {
      string message = "spline3 exception: A spline3 must be specified with at least 2 points";
      cout << message << endl;
      throw logic_error(message);
   }
   for(size_t i=0; i<other.size(); i++) {
      pos3* pnt = other[i];
      nodes.push_back(*pnt);
   }

   m_spline.compute_spline(nodes);
}

spline3::spline3(const pos3* p1, const pos3* p2, const pos3* p3, const pos3* p4, const pos3* p5)
: as_reftype("spline3d")
{
   vector<pos3d> nodes;

   nodes.push_back(*p1);
   nodes.push_back(*p2);
   if(p3)nodes.push_back(*p3);
   if(p4)nodes.push_back(*p4);
   if(p5)nodes.push_back(*p5);

   m_spline.compute_spline(nodes);
}

spline3::~spline3()
{}

pos3* spline3::pos(double t) const
{
   pos3d p = m_spline.pos(t);
   return new pos3(p);
}

vec3* spline3::dir(double t) const
{
   return new vec3(m_spline.deriv1(t));
}

pos3d spline3::pos_raw(double t) const
{
   return m_spline.pos(t);
}

vec3d spline3::vec_raw(double t) const
{
   return m_spline.deriv1(t);
}

const spacemath::spline3d& spline3::spline_raw() const
{
   return m_spline;
}
