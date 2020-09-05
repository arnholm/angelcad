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

#include "tmatrix.h"
#include <iostream>
using namespace std;

static const double pi = 4.0*atan(1.0);

void tmatrix::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   // DeclareType<tmatrix>(engine);

   // no constructors here, this is an abstract class

   // Declare the methods
   tmatrix::DeclareMethods<tmatrix>(engine);
}


tmatrix::tmatrix(const string& type)
: as_reftype(type)
{}

tmatrix::tmatrix(const string& type, const HTmatrix& matrix)
: as_reftype(type)
, m_matrix(matrix)
{}

tmatrix::~tmatrix()
{}

HTmatrix& tmatrix::matrix()
{
   return m_matrix;
}

const HTmatrix& tmatrix::matrix() const
{
   return m_matrix;
}

double tmatrix::to_radian(double deg, double rad)
{
   bool NaN_deg = (deg==0x7fc00000);
   bool NaN_rad = (rad==0x7fc00000);

   if( ( NaN_deg) && ( NaN_rad) ) { throw std::logic_error("One of deg or rad must be specified"); }
   if( (!NaN_deg) && (!NaN_rad))  { throw std::logic_error("Cannot specify both deg and rad"); }

   double angle = (NaN_deg)? rad : (pi*deg/180.0);
   return angle;
}

double tmatrix::to_radian(double deg)
{
   return (pi*deg/180.0);
}

double tmatrix::to_degree(double rad)
{
   return (180.0*rad/pi);
}

tmatrix* tmatrix::multiply_tmatrix(const tmatrix* A, const tmatrix* B)
{
/*
   cout << endl << "multiply_tmatrix";
   cout << endl << "A: ";
   A->dump();
   cout << endl << "B  ";
   B->dump();
*/

   const HTmatrix& a = A->m_matrix;
   const HTmatrix& b = B->m_matrix;
   tmatrix* res = new tmatrix(as_typeid<tmatrix>(),b*a);
/*
   cout << endl << "product ";
   res->dump();
*/
   return res;
}


vec3* tmatrix::xdir() const
{
   return new vec3( m_matrix(0,0), m_matrix(1,0), m_matrix(2,0));
}

vec3* tmatrix::ydir() const
{
   return new vec3( m_matrix(0,1), m_matrix(1,1), m_matrix(2,1));
}

vec3* tmatrix::zdir() const
{
   return new vec3( m_matrix(0,2), m_matrix(1,2), m_matrix(2,2));
}

pos3* tmatrix::origin() const
{
   return new pos3( m_matrix(0,3), m_matrix(1,3), m_matrix(2,3));
}

void tmatrix::dump() const
{
   cout << Type();
   for(size_t irow=0; irow<4; irow++) {
      cout << endl;
      for(size_t icol=0; icol<4; icol++) {
         cout << setw(5) << m_matrix(irow,icol) << ' ';
      }
   }
   cout << endl;
}
