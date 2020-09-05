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

#include "rotate_y.h"
#include <cmath>

void rotate_y::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<rotate_y>(engine,"Rotation around y");

    // Declare allowed type conversions
   DeclareCast<rotate_y,tmatrix>(engine);

   // Declare the constructors
   DeclareConstructors(engine);
   // Inherit any methods from base in this class + declare the added local methods

   rotate_y::DeclareMethods<rotate_y>(engine);
}

rotate_y::rotate_y(double rx)
: tmatrix(as_typeid<rotate_y>())
, m_angle(rx)
{
   // access the raw matrix
   HTmatrix& hmat = matrix();
   // set the rotation terms

   hmat(0,0) =  cos(rx);
   hmat(2,0) =  sin(rx);

   hmat(1,1) = 1.0;

   hmat(0,2) = -sin(rx);
   hmat(2,2) =  cos(rx);
}


rotate_y::~rotate_y()
{}
