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

#include "vec3.h"
#include "pos3.h"
#include <fstream>
#include <iostream>
using namespace std;
#include "tmatrix.h"

void vec3::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   DeclareTypeEx("vec3d",engine,"3d direction vector");

   // declate constructors
   vec3::DeclareConstructors(engine);

   // Declare the vec3 methods
   vec3::DeclareMethods<vec3>(engine);
}

vec3::vec3(double x, double y, double z)
: as_reftype("vec3d")
, m_vec(x,y,z)
{}

vec3::vec3(const as_initializer_vector<double>& v)
: as_reftype("vec3d")
, m_vec(v[0],v[1],v[2])
{
   // cout << "vec3 Initlist " << this << " " << m_vec.x() << " " << m_vec.y() << " " << m_vec.z() << endl;
}

vec3::vec3(const pos3* p1, const pos3* p2)
: as_reftype("vec3d")
, m_vec(*p1,*p2)
{}

vec3::vec3(const vec3d& vec)
: as_reftype("vec3d")
, m_vec(vec)
{}


double vec3::x() const
{
   return m_vec.x();
}

double vec3::y() const
{
   return m_vec.y();
}

double vec3::z() const
{
   return m_vec.z();
}

vec3::~vec3()
{}

as_reftype* vec3::clone_scoped()
{
   return new vec3(*this);
}

double vec3::length() const
{
   return m_vec.length();
}

vec3* vec3::cross(const vec3* vec2) const
{
   return new vec3(m_vec.cross(*vec2));
}

double vec3::dot(const vec3* vec2) const
{
   return m_vec.dot(*vec2);
}

double vec3::angle(const vec3* vec2) const
{
   return m_vec.angle(*vec2);
}

void  vec3::normalise()
{
   m_vec.normalise();
}

vec3* vec3::opAddVec(const vec3* v1)
{
   return new vec3(m_vec+v1->vec());
}

vec3* vec3::opSubVec(const vec3* v1)
{
   return new vec3(m_vec-v1->vec());
}

vec3* vec3::opMulFact(double fact)
{
   return new vec3(m_vec*fact);
}
