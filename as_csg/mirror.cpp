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
   
#include "mirror.h"
#include "pos3.h"
#include "vec3.h"

void mirror::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<mirror>(engine,"Mirror transformation around given point");

    // Declare allowed type conversions
   DeclareCast<mirror,tmatrix>(engine);

   // Declare the constructors
   DeclareConstructors(engine);
   // Inherit any methods from base in this class + declare the added local methods

   mirror::DeclareMethods<mirror>(engine);
}

mirror::mirror(double dx, double dy, double dz)
: tmatrix(as_typeid<mirror>())
, m_normal(dx,dy,dz)
, m_point(0,0,0)
{
   // the point we are mirroring about, we set it to origin here because OpenSCAD does not know better
   apply_mirror(m_point,m_normal);
}

mirror::mirror(vec3* normal, pos3* point)
: tmatrix(as_typeid<mirror>())
, m_normal(*normal)
, m_point(*point)
{
   point->Release();
   normal->Release();

   apply_mirror(m_point,m_normal);
}


void mirror::apply_mirror(const pos3d& point, const vec3d& axis)
{
   // access the raw matrix
   HTmatrix& trans = matrix();
   // set the mirror terms

   // first compute the plane equation for the plane with normal dx,dy,dz
   vec3d n(axis);
   n.normalise();

   // the point we are mirroring about
   pos3d p(point);

   // plane equation parameters: A*x + B*y + C*z = D
   double ABCD[4];
   ABCD[0] = n.x();
   ABCD[1] = n.y();
   ABCD[2] = n.z();
   ABCD[3] = ABCD[0]*p.x()+ABCD[1]*p.y()+ABCD[2]*p.z();

   double nx =  ABCD[0];
   double ny =  ABCD[1];
   double nz =  ABCD[2];
   double k  =  -ABCD[3];


   trans(0,0) = 1.0 - 2.0*nx*nx;
   trans(1,0) =     - 2.0*ny*nx;
   trans(2,0) =     - 2.0*nz*nx;
   trans(3,0) =       0.0;

   trans(0,1) =     - 2.0*nx*ny;
   trans(1,1) = 1.0 - 2.0*ny*ny;
   trans(2,1) =     - 2.0*nz*ny;
   trans(3,1) =       0.0;

   trans(0,2) =     - 2.0*nx*nz;
   trans(1,2) =     - 2.0*ny*nz;
   trans(2,2) = 1.0 - 2.0*nz*nz;
   trans(3,2) =       0.0;

   trans(0,3) =     - 2.0*nx*k;
   trans(1,3) =     - 2.0*ny*k;
   trans(2,3) =     - 2.0*nz*k;
   trans(3,3) =       1.0;
}

mirror::~mirror()
{}

double mirror::dx() const
{
   return m_normal.x();
}

double mirror::dy() const
{
   return m_normal.y();
}

double mirror::dz() const
{
   return m_normal.z();
}
