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
   
#include "rotate_x.h"
#include <cmath>

void rotate_x::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<rotate_x>(engine,"Rotation around x");

    // Declare allowed type conversions
   DeclareCast<rotate_x,tmatrix>(engine);

   // Declare the constructors
   DeclareConstructors(engine);
   // Inherit any methods from base in this class + declare the added local methods

   rotate_x::DeclareMethods<rotate_x>(engine);
}

rotate_x::rotate_x(double rx)
: tmatrix(as_typeid<rotate_x>())
, m_angle(rx)
{
   // access the raw matrix
   HTmatrix& hmat = matrix();
   // set the rotation terms
   hmat(0,0) = 1.0;

   hmat(1,1) =  cos(rx);
   hmat(2,1) =  sin(rx);

   hmat(1,2) = -sin(rx);
   hmat(2,2) =  cos(rx);
}

rotate_x::~rotate_x()
{}
