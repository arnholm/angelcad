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

#ifndef MIRROR_H
#define MIRROR_H

#include "tmatrix.h"

#include "spacemath/pos3d.h"
#include "spacemath/vec3d.h"
class pos3;
class vec3;

using spacemath::vec3d;
using spacemath::pos3d;

/// mirror generates a mirror transformation around given point
class mirror : public tmatrix {
public:

   // this constructor specifies the normal of a mirror plane through the origin
   mirror(double dx, double dy, double dz);

   // this constructor specifies the normal of a mirror plane through the given point
   mirror(vec3* normal, pos3* point);
   virtual ~mirror();

   // return components of the mirroring plane normal
   double dx() const;
   double dy() const;
   double dz() const;

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

protected:
   /// \privatesection (hidden in documentation)

   void apply_mirror(const pos3d& point, const vec3d& axis);


   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static mirror* ctor_xyz(double dx, double dy, double dz) { return new mirror(dx,dy,dz); }
   static mirror* ctor_vp(vec3* normal, pos3* point) { return new mirror(normal,point); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<mirror>(),"mirror@ mirror(double dx, double dy, double dz)",asFUNCTION(mirror::ctor_xyz)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,as_typeid<mirror>(),"mirror@ mirror(vec3d@+ normal, pos3d@+ point = pos3d(0,0,0) )",asFUNCTION(mirror::ctor_vp)); as_assert( r >= 0 );
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
      int r = 0;
      r = DeclareMethod(engine,type_name,"double dx() const", asMETHOD(mirror,dx)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dy() const", asMETHOD(mirror,dy)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dz() const", asMETHOD(mirror,dz)); as_assert( r >= 0 );
   }
private:
   vec3d  m_normal;   // mirror plane normal
   pos3d  m_point;    // point in mirror plane
};

#endif // MIRROR_H
