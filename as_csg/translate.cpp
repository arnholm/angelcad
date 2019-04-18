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

#include "translate.h"

void translate::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<translate>(engine,"Translation in x, y and z");

    // Declare allowed type conversions
   DeclareCast<translate,tmatrix>(engine);

   // Declare the constructors
   DeclareConstructors(engine);
   // Inherit any methods from base in this class + declare the added local methods

   translate::DeclareMethods<translate>(engine);
}

translate::translate(double dx, double dy, double dz)
: tmatrix(as_typeid<translate>())
, m_dx(dx)
, m_dy(dy)
, m_dz(dz)
{
   // access the raw matrix
   HTmatrix& hmat = matrix();
   // set the translational terms
   hmat(0,3) = m_dx;
   hmat(1,3) = m_dy;
   hmat(2,3) = m_dz;
}

translate::translate(const spacemath::vec3d& v)
: tmatrix(as_typeid<translate>())
, m_dx(v.x())
, m_dy(v.y())
, m_dz(v.z())
{
   // access the raw matrix
   HTmatrix& hmat = matrix();
   // set the translational terms
   hmat(0,3) = m_dx;
   hmat(1,3) = m_dy;
   hmat(2,3) = m_dz;
}

translate::~translate()
{}

double translate::dx() const
{
   return m_dx;
}

double translate::dy() const
{
   return m_dy;
}

double translate::dz() const
{
   return m_dz;
}
