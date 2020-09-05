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

#include "pos3.h"
#include "vec3.h"
#include <fstream>
#include <iostream>
using namespace std;
#include "tmatrix.h"

void pos3::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   DeclareTypeEx("pos3d",engine,"3d position coordinates");

   // declate constructors
   pos3::DeclareConstructors(engine);

   // Declare the pos3 methods
   pos3::DeclareMethods<pos3>(engine);
}

pos3::pos3(double x, double y, double z)
: as_reftype("pos3d")
, m_pos(x,y,z)
{}

pos3::pos3(const as_initializer_vector<double>& v)
: as_reftype("pos3d")
, m_pos(v[0],v[1],v[2])
{
   // cout << "pos3d Initlist " << this << " " << m_pos.x() << " " << m_pos.y() << " " << m_pos.z() << endl;
}

pos3::pos3(const pos3d& pos)
: as_reftype("pos3d")
, m_pos(pos)
{}


double pos3::x() const
{
   return m_pos.x();
}

double pos3::y() const
{
   return m_pos.y();
}

double pos3::z() const
{
   return m_pos.z();
}

pos3::~pos3()
{}

as_reftype* pos3::clone_scoped()
{
   return new pos3(*this);
}

pos3* pos3::clone_transform(const tmatrix* matrix) const
{
   const HTmatrix& t = matrix->matrix();
   return new pos3(t*m_pos);
}

double pos3::dist(const pos3* pos) const
{
   return m_pos.dist(*pos);
}

pos3* pos3::opAddPos(const pos3* p1)
{
   return new pos3(m_pos + p1->pos());
}

pos3* pos3::opAddVec(const vec3* v1)
{
   return new pos3(m_pos + v1->vec());
}

pos3* pos3::opSubVec(const vec3* v1)
{
   return new pos3(m_pos - v1->vec());
}

pos3* pos3::opMulFact(double fact)
{
   return new pos3(m_pos*fact);
}
