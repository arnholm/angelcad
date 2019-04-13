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
   
#ifndef localsystem3D_H
#define localsystem3D_H

#include "ce_angelscript_ex/as_reftype.h"
#include "spacemath/locsys3d.h"
using spacemath::locsys3d;

// script classes
class vec3;

/// localsystem3d is a utility class used with 3d primitives, the script class name is "locsys3d"
class localsystem3d : public as_reftype {
public:
   // constructor
   localsystem3d(const vec3* xvec, const vec3* zvec);
   localsystem3d(const locsys3d& sys);
   virtual ~localsystem3d();

   vec3* x() const;
   vec3* y() const;
   vec3* z() const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

   operator locsys3d() const { return m_sys; }

protected:
   /// \privatesection (hidden in documentation)

   static localsystem3d* ctor_v2(const vec3* xvec, const vec3* zvec) { return new localsystem3d(xvec,zvec); }

   // ==== SCRIPTING INTERFACE
   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,"locsys3d","locsys3d@ locsys3d(const vec3d@+ xvec, const vec3d@+ zvec)",asFUNCTION(localsystem3d::ctor_v2)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      const std::string type_name = "locsys3d";
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = 0;
      r = DeclareMethod(engine,type_name,"vec3d@ x() const", asMETHOD(localsystem3d,x)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec3d@ y() const", asMETHOD(localsystem3d,y)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec3d@ z() const", asMETHOD(localsystem3d,z)); as_assert( r >= 0 );
   }
private:
   locsys3d m_sys;
};

#endif // SHAPE3D_H
