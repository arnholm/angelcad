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

#include "pos2.h"
#include "vec2.h"
#include <fstream>
#include <iostream>
using namespace std;
#include "tmatrix.h"

using spacemath::pos2d;

void pos2::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   DeclareTypeEx("pos2d",engine,"2d position coordinates");

   // declate constructors
   pos2::DeclareConstructors(engine);

   // Declare the pos2 methods
   pos2::DeclareMethods<pos2>(engine);
}

pos2::pos2(double x, double y)
: as_reftype("pos2d")
, m_pos(x,y)
{}

pos2::pos2(const as_initializer_vector<double>& v)
: as_reftype("pos2d")
, m_pos(v[0],v[1])
{
   // cout << "pos2 Initlist " << this << " " << m_pos.x() << " " << m_pos.y() << endl;
}

pos2::pos2(const pos2d& pos)
: as_reftype("pos2d")
, m_pos(pos)
{}

double pos2::x() const
{
   return m_pos.x();
}

double pos2::y() const
{
   return m_pos.y();
}

pos2::~pos2()
{}

as_reftype* pos2::clone_scoped()
{
   return new pos2(*this);
}

double pos2::dist(const pos2* pos) const
{
   return m_pos.dist(*pos);
}

pos2* pos2::opAddPos(const pos2* p1)
{
   return new pos2(m_pos + p1->pos());
}

pos2* pos2::opAddVec(const vec2* v1)
{
   return new pos2(m_pos + v1->vec());
}

pos2* pos2::opSubVec(const vec2* v1)
{
   return new pos2(m_pos - v1->vec());
}

pos2* pos2::opMulFact(double fact)
{
   return new pos2(m_pos*fact);
}

pos2* pos2::clone_transform(const tmatrix* matrix) const
{
   const HTmatrix& t = matrix->matrix();
   pos3d p(m_pos.x(),m_pos.y(),0.0);
   pos3d tp = t*p;
   return new pos2(tp.x(),tp.y());
}

