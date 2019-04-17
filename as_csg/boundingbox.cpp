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

#include "boundingbox.h"
#include <fstream>
#include <iostream>
using namespace std;

#include "pos3.h"

void boundingbox::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   DeclareType<boundingbox>(engine,"bounding box aligned with system axes");

   // declate constructors
   boundingbox::DeclareConstructors(engine);

   // Declare the boundingbox methods
   boundingbox::DeclareMethods<boundingbox>(engine);
}

boundingbox::boundingbox()
: as_reftype(as_typeid<boundingbox>())
, m_box(false)
{}

boundingbox::boundingbox(const spacemath::bbox3d& box)
: as_reftype(as_typeid<boundingbox>())
, m_box(box)
{}

void boundingbox::enclose(pos3* p)
{
   m_box.enclose(*p);
   p->Release();
}

pos3* boundingbox::p1() const
{
   return new pos3(m_box.p1());
}

pos3* boundingbox::p2() const
{
   return new pos3(m_box.p2());
}

boundingbox::~boundingbox()
{}

as_reftype* boundingbox::clone_scoped()
{
   return new boundingbox(*this);
}

pos3* boundingbox::center() const
{
   return new pos3(m_box.center());
}

double boundingbox::dx() const
{
   return m_box.dx();
}

double boundingbox::dy() const
{
   return m_box.dy();
}

double boundingbox::dz() const
{
   return m_box.dz();
}

double boundingbox::diagonal() const
{
   return m_box.diagonal();
}
