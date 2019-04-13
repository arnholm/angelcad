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
   
#ifndef ROTATE_Z_H
#define ROTATE_Z_H

#include "tmatrix.h"
#include <cmath>

/// rotate_z generates a rotate transformation around z
class rotate_z : public tmatrix {
public:

   rotate_z(double rx);
   virtual ~rotate_z();

   // return rotation angle in radians
   double rad() const { return m_angle; }

   // return rotation angle in degrees
   double deg() const { return tmatrix::to_degree(m_angle); }

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

protected:
   /// \privatesection (hidden in documentation)


   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static rotate_z* ctor_r(double deg, double rad) {  return new rotate_z(tmatrix::to_radian(deg,rad)); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<rotate_z>(),"rotate_z@ rotate_z(double deg=0x7fc00000, double rad=0x7fc00000)",asFUNCTION(rotate_z::ctor_r)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      tmatrix::DeclareMethods<tmatrix>(engine);
      tmatrix::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
      int r = DeclareMethod(engine,type_name,"double rad() const", asMETHOD(rotate_z,rad)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"double deg() const", asMETHOD(rotate_z,deg)); as_assert( r >= 0 );
   }

private:
   double m_angle;
};

#endif // ROTATE_Z_H
