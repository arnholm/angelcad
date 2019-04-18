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

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "ce_angelscript_ex/as_reftype.h"
#include "spacemath/vec3d.h"
#include "spacemath/pos3d.h"
using spacemath::vec3d;
using spacemath::pos3d;
class pos3;

/// vec3 is a utility class used with 3d primitives, the script class name is "vec3d"
class vec3 : public as_reftype {
   friend class as_csg;
public:
   // constructor
   vec3(double x, double y, double z);
   vec3(const pos3* p1, const pos3* p2);
   vec3(const vec3d& vec);
   virtual ~vec3();

   double x() const;
   double y() const;
   double z() const;

   double length() const;
   vec3* cross(const vec3* vec2) const;
   double    dot(const vec3* vec2) const;
   double    angle(const vec3* vec2) const;
   void      normalise();

   vec3* opAddVec(const vec3* v1);    // v + v1
   vec3* opSubVec(const vec3* v1);    // v - v1
   vec3* opMulFact(double fact);          // v*0.5

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

   operator spacemath::vec3d() const { return m_vec; }
   spacemath::vec3d vec() const { return m_vec; }

protected:
   /// \privatesection (hidden in documentation)

   static vec3* ctor_xyz(double x, double y, double z) { return new vec3(x,y,z); }
   static vec3* ctor_p2(const pos3* p1, const pos3* p2) { return new vec3(p1,p2); }
   static vec3* ctor_copy(const vec3* v) { return new vec3(v->m_vec); }

   // ==== SCRIPTING INTERFACE
   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,"vec3d","vec3d@ vec3d(double x,double y, double z)",asFUNCTION(vec3::ctor_xyz)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,"vec3d","vec3d@ vec3d(const pos3d@+ p1, const pos3d@+ p2)",asFUNCTION(vec3::ctor_p2)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,"vec3d","vec3d@ vec3d(const vec3d@+ other)",asFUNCTION(vec3::ctor_copy)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      const std::string type_name = "vec3d";
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = 0;
      r = DeclareMethod(engine,type_name,"double x() const", asMETHOD(vec3,x)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double y() const", asMETHOD(vec3,y)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double z() const", asMETHOD(vec3,z)); as_assert( r >= 0 );

      r = DeclareMethod(engine,type_name,"double length() const", asMETHOD(vec3,length)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec3d@ cross(const vec3d@+ other) const", asMETHOD(vec3,cross)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dot(const vec3d@+ other) const", asMETHOD(vec3,dot)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double angle(const vec3d@+ other) const", asMETHOD(vec3,angle)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"void normalise()", asMETHOD(vec3,normalise)); as_assert( r >= 0 );
   }

   static void DeclareOperators(asIScriptEngine* engine)
   {
      const std::string type_name = "vec3d";

      // local operators
      int r = 0;
      r = DeclareMethod(engine,type_name,"vec3d@ opAdd(vec3d@+ v1)",asMETHOD(vec3,opAddVec)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec3d@ opSub(vec3d@+ v1)",asMETHOD(vec3,opSubVec)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec3d@ opMul(double f1)",asMETHOD(vec3,opMulFact)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec3d@ opMul_r(double f1)",asMETHOD(vec3,opMulFact)); as_assert( r >= 0 );
   }
private:
   vec3d m_vec;
};

#endif // SHAPE3D_H
