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
   
#include "hmatrix.h"
#include "vec3.h"
#include "spacemath/vec3d.h"
using namespace spacemath;

void hmatrix::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<hmatrix>(engine,"Homogeneous transformation matrix");

    // Declare allowed type conversions
   DeclareCast<hmatrix,tmatrix>(engine);

   // Declare the constructors
   DeclareConstructors(engine);
   // Inherit any methods from base in this class + declare the added local methods

   hmatrix::DeclareMethods<hmatrix>(engine);
}

hmatrix::hmatrix(const vec3* xvec, const vec3* yvec, const vec3* zvec, const pos3* pos)
: tmatrix(as_typeid<hmatrix>())
{
   // access the raw matrix
   HTmatrix& hmat = matrix();

   // x-vector
   hmat(0,0) = xvec->x();
   hmat(1,0) = xvec->y();
   hmat(2,0) = xvec->z();

   // y-vector
   hmat(0,1) = yvec->x();
   hmat(1,1) = yvec->y();
   hmat(2,1) = yvec->z();

   // z-vector
   hmat(0,2) = zvec->x();
   hmat(1,2) = zvec->y();
   hmat(2,2) = zvec->z();

   // set the translational terms
   hmat(0,3) = pos->x();
   hmat(1,3) = pos->y();
   hmat(2,3) = pos->z();
}

hmatrix::hmatrix(const vec3* xvec, const vec3* yvec, const pos3* pos)
: tmatrix(as_typeid<hmatrix>())
{
   // construct normalised, orthogonal vectors
   vec3d xv = xvec->vec();
   vec3d yv = yvec->vec();
   xv.normalise();
   yv.normalise();
   vec3d zv = xv.cross(yv);
   zv.normalise();
   yv = zv.cross(xv);

   // access the raw matrix
   HTmatrix& hmat = matrix();

   // x-vector
   hmat(0,0) = xv.x();
   hmat(1,0) = xv.y();
   hmat(2,0) = xv.z();

   // y-vector
   hmat(0,1) = yv.x();
   hmat(1,1) = yv.y();
   hmat(2,1) = yv.z();

   // z-vector
   hmat(0,2) = zv.x();
   hmat(1,2) = zv.y();
   hmat(2,2) = zv.z();

   // set the translational terms
   hmat(0,3) = pos->x();
   hmat(1,3) = pos->y();
   hmat(2,3) = pos->z();
}

hmatrix::~hmatrix()
{}


