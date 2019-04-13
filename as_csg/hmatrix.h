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
   
#ifndef HMATRIX_H
#define HMATRIX_H

#include "tmatrix.h"

// script classes
class vec3;


/// hmatrix represents a homogeneous transformation
class hmatrix : public tmatrix {
public:
   hmatrix(const vec3* xvec, const vec3* yvec, const vec3* zvec, const pos3* pos);
   hmatrix(const vec3* xvec, const vec3* yvec, const pos3* pos);
   virtual ~hmatrix();

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

protected:
   /// \privatesection (hidden in documentation)


   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static hmatrix* ctor_vvvp(const vec3* xvec, const vec3* yvec, const vec3* zvec, const pos3* pos) { return new hmatrix(xvec,yvec,zvec,pos); }
   static hmatrix* ctor_vvp(const vec3* xvec, const vec3* yvec, const pos3* pos) { return new hmatrix(xvec,yvec,pos); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<hmatrix>(),"hmatrix@ hmatrix(const vec3d@+ xvec, const vec3d@+ yvec, const vec3d@+ zvec, const pos3d@+ pos = pos3d(0,0,0))",asFUNCTION(hmatrix::ctor_vvvp)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,as_typeid<hmatrix>(),"hmatrix@ hmatrix(const vec3d@+ xvec, const vec3d@+ yvec, const pos3d@+ pos = pos3d(0,0,0))",asFUNCTION(hmatrix::ctor_vvp)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      tmatrix::DeclareMethods<tmatrix>(engine);
      tmatrix::DeclareMethods<T>(engine);
   }
};

#endif // HMATRIX_H
