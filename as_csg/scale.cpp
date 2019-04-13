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
   
#include "scale.h"

void scale::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<scale>(engine,"Scaling transformation");

    // Declare allowed type conversions
   DeclareCast<scale,tmatrix>(engine);

   // Declare the constructors
   DeclareConstructors(engine);
   // Inherit any methods from base in this class + declare the added local methods

   scale::DeclareMethods<scale>(engine);
}

scale::scale(double sx, double sy, double sz)
: tmatrix(as_typeid<scale>())
, m_sx(sx)
, m_sy(sy)
, m_sz(sz)
{
   // access the raw matrix
   HTmatrix& hmat = matrix();
   // set the translational terms
   hmat(0,0) = m_sx;
   hmat(1,1) = m_sy;
   hmat(2,2) = m_sz;
}

scale::~scale()
{}

double scale::sx() const
{
   return m_sx;
}

double scale::sy() const
{
   return m_sy;
}

double scale::sz() const
{
   return m_sz;
}
