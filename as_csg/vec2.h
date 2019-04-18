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

#ifndef vec2_H
#define vec2_H

#include "ce_angelscript_ex/as_reftype.h"
#include "spacemath/vec2d.h"
#include "spacemath/pos2d.h"
using spacemath::vec2d;
using spacemath::pos2d;
class pos2;

/// vec2 is a utility class used with 2d primitives, the script class name is "vec2d"
class vec2 : public as_reftype {
   friend class as_csg;
public:
   // constructor
   vec2(double x, double y);
   vec2(const pos2* p1, const pos2* p2);
   vec2(const vec2d& vec);
   virtual ~vec2();

   double x() const;
   double y() const;

   double length() const;
   double cross(const vec2* v2) const;
   double dot(const vec2* v2) const;
   double angle(const vec2* v2) const;
   void   normalise();

   vec2* opAddVec(const vec2* v1);    // v + v1
   vec2* opSubVec(const vec2* v1);    // v - v1
   vec2* opMulFact(double fact);          // v*0.5

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

   operator spacemath::vec2d() const { return m_vec; }
   spacemath::vec2d vec() const { return m_vec; }

protected:
   /// \privatesection (hidden in documentation)

   static vec2* ctor_xy(double x, double y) { return new vec2(x,y); }
   static vec2* ctor_p2(const pos2* p1, const pos2* p2) { return new vec2(p1,p2); }
   static vec2* ctor_copy(const vec2* v) { return new vec2(v->m_vec); }

   // ==== SCRIPTING INTERFACE
   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,"vec2d","vec2d@ vec2d(double x,double y)",asFUNCTION(vec2::ctor_xy)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,"vec2d","vec2d@ vec2d(const pos2d@+ p1, const pos2d@+ p2)",asFUNCTION(vec2::ctor_p2)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,"vec2d","vec2d@ vec2d(const vec2d@+ other)",asFUNCTION(vec2::ctor_copy)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      const std::string type_name = "vec2d";
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = 0;
      r = DeclareMethod(engine,type_name,"double x() const", asMETHOD(vec2,x)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double y() const", asMETHOD(vec2,y)); as_assert( r >= 0 );

      r = DeclareMethod(engine,type_name,"double length() const", asMETHOD(vec2,length)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double cross(const vec2d@+ other) const", asMETHOD(vec2,cross)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dot(const vec2d@+ other) const", asMETHOD(vec2,dot)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double angle(const vec2d@+ other) const", asMETHOD(vec2,angle)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"void normalise()", asMETHOD(vec2,normalise)); as_assert( r >= 0 );
   }

   static void DeclareOperators(asIScriptEngine* engine)
   {
      const std::string type_name = "vec2d";

      // local operators
      int r = 0;
      r = DeclareMethod(engine,type_name,"vec2d@ opAdd(vec2d@+ v1)",asMETHOD(vec2,opAddVec)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec2d@ opSub(vec2d@+ v1)",asMETHOD(vec2,opSubVec)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec2d@ opMul(double f1)",asMETHOD(vec2,opMulFact)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec2d@ opMul_r(double f1)",asMETHOD(vec2,opMulFact)); as_assert( r >= 0 );

   }
private:
   vec2d m_vec;
};

#endif // SHAPE2d_H
