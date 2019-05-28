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

#include "vec2.h"
#include "pos2.h"
#include <fstream>
#include <iostream>
using namespace std;
#include "tmatrix.h"

void vec2::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   DeclareTypeEx("vec2d",engine,"2d direction vector");

   // declate constructors
   vec2::DeclareConstructors(engine);

   // Declare the vec2 methods
   vec2::DeclareMethods<vec2>(engine);
}

vec2::vec2(double x, double y)
: as_reftype("vec2d")
, m_vec(x,y)
{}

vec2::vec2(const as_initializer_vector<double>& v)
: as_reftype("vec2d")
, m_vec(v[0],v[1])
{
   // cout << "vec2 Initlist " << this << " " << m_vec.x() << " " << m_vec.y() << endl;
}

vec2::vec2(const pos2* p1, const pos2* p2)
: as_reftype("vec2d")
, m_vec(*p1,*p2)
{}

vec2::vec2(const vec2d& vec)
: as_reftype("vec2d")
, m_vec(vec)
{}


double vec2::x() const
{
   return m_vec.x();
}

double vec2::y() const
{
   return m_vec.y();
}

vec2::~vec2()
{}

as_reftype* vec2::clone_scoped()
{
   return new vec2(*this);
}

double vec2::length() const
{
   return m_vec.length();
}

double vec2::cross(const vec2* v2) const
{
   return m_vec.cross(*v2);
}

double vec2::dot(const vec2* v2) const
{
   return m_vec.dot(*v2);
}

double vec2::angle(const vec2* v2) const
{
   return m_vec.angle(*v2);
}

void  vec2::normalise()
{
   m_vec.normalise();
}

vec2* vec2::opAddVec(const vec2* v1)
{
   return new vec2(m_vec+v1->vec());
}

vec2* vec2::opSubVec(const vec2* v1)
{
   return new vec2(m_vec-v1->vec());
}

vec2* vec2::opMulFact(double fact)
{
   return new vec2(m_vec*fact);
}

