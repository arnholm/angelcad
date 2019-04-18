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


#include "line3.h"
#include <fstream>
#include <iostream>
using namespace std;

#include "pos3.h"

void line3::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   DeclareTypeEx("line3d",engine,"3d line");

   // declate constructors
   line3::DeclareConstructors(engine);

   // Declare the line3 methods
   line3::DeclareMethods<line3>(engine);
}

line3::line3(const pos3* p1, const pos3* p2)
: as_reftype("line3d")
, m_line(*p1,*p2)
{}

line3::line3(const spacemath::line3d& line)
: as_reftype("line3d")
, m_line(line)
{}

line3::~line3()
{}

as_reftype* line3::clone_scoped()
{
   return new line3(*this);
}

pos3* line3::end1() const
{
   return new pos3(m_line.end1());
}

pos3* line3::end2() const
{
   return new pos3(m_line.end2());
}

double line3::length() const
{
   return m_line.length();
}


pos3* line3::interpolate(double par) const
{
   return new pos3(m_line.interpolate(par));
}

double line3::project(const pos3* point) const
{
   return m_line.project(*point);
}

