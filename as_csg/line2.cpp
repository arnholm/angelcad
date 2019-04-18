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

#include "line2.h"
#include <fstream>
#include <iostream>
using namespace std;

#include "pos2.h"

void line2::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   DeclareTypeEx("line2d",engine,"2d line");

   // declate constructors
   line2::DeclareConstructors(engine);

   // Declare the line2 methods
   line2::DeclareMethods<line2>(engine);
}

line2::line2(const pos2* p1, const pos2* p2)
: as_reftype("line2d")
, m_line(*p1,*p2)
{}

line2::line2(const spacemath::line2d& line)
: as_reftype("line2d")
, m_line(line)
{}

line2::~line2()
{}

as_reftype* line2::clone_scoped()
{
   return new line2(*this);
}


pos2* line2::end1() const
{
   return new pos2(m_line.end1());
}

pos2* line2::end2() const
{
   return new pos2(m_line.end2());
}

double  line2::length() const
{
   return m_line.length();
}

pos2* line2::interpolate(double par) const
{
   return new pos2(m_line.interpolate(par));
}

double line2::project(const pos2* point) const
{
   return m_line.project(*point);
}

