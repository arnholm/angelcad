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
   
#include "localsystem3d.h"
#include "pos3.h"
#include "vec3.h"
#include <fstream>
#include <iostream>
using namespace std;
#include "tmatrix.h"

void localsystem3d::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   DeclareTypeEx("locsys3d",engine,"3d localsystem");

   // declate constructors
   localsystem3d::DeclareConstructors(engine);

   // Declare the localsystem3d methods
   localsystem3d::DeclareMethods<localsystem3d>(engine);
}

localsystem3d::localsystem3d(const vec3* xvec, const vec3* zvec)
: as_reftype("locsys3d")
, m_sys(*xvec,*zvec)
{}

localsystem3d::localsystem3d(const locsys3d& vec)
: as_reftype("locsys3d")
, m_sys(vec)
{}

vec3* localsystem3d::x() const
{
   return new vec3(m_sys.x());
}

vec3* localsystem3d::y() const
{
   return new vec3(m_sys.y());
}

vec3* localsystem3d::z() const
{
   return new vec3(m_sys.z());
}

localsystem3d::~localsystem3d()
{}

as_reftype* localsystem3d::clone_scoped()
{
   return new localsystem3d(*this);
}

