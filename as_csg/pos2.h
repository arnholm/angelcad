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

#ifndef POSITION2D_H
#define POSITION2D_H

#include "ce_angelscript_ex/as_reftype.h"
#include "ce_angelscript_ex/as_initializer_vector.h"
#include "spacemath/pos2d.h"
class vec2;
class tmatrix;

/// pos2 is a utility class used with 2d primitives, the script class name is "pos2d"
class pos2 : public as_reftype {
   friend class as_csg;
public:
   // constructor
   pos2(double x, double y);
   pos2(const as_initializer_vector<double>& v);
   pos2(const spacemath::pos2d& pos);
   virtual ~pos2();

   double dist(const pos2* pos) const;

   double x() const;
   double y() const;

   pos2* opAddPos(const pos2* p1);  // p + p1
   pos2* opAddVec(const vec2* v1);    // p + v1
   pos2* opSubVec(const vec2* v1);    // p - v1
   pos2* opMulFact(double fact);          // p*0.5

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // create a clone with given transformation
   virtual pos2* clone_transform(const tmatrix* matrix) const;

   // required by as_reftype
   as_reftype* clone_scoped();

   operator spacemath::pos2d() const { return m_pos; }
   spacemath::pos2d pos() const { return m_pos; }

protected:
   /// \privatesection (hidden in documentation)

   static pos2* ctor_xy(double x, double y) { return new pos2(x,y); }
   static pos2* ctor_copy(const pos2* p) { return new pos2(p->m_pos); }
   static pos2* ctor_initlist(void* initlist) { return new pos2(as_initializer_vector<double>(2,initlist)); };

   // ==== SCRIPTING INTERFACE
   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,"pos2d","pos2d@ pos2d(double x,double y)",asFUNCTION(pos2::ctor_xy)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,"pos2d","pos2d@ pos2d(const pos2d@+ other)",asFUNCTION(pos2::ctor_copy)); as_assert( r >= 0 );
          r = DeclareConstructorInitList(engine,"pos2d","pos2d@ pos2d(int &in list) {repeat double}",asFUNCTION(pos2::ctor_initlist)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      const std::string type_name = "pos2d";
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = 0;
      r = DeclareMethod(engine,type_name,"double x() const", asMETHOD(pos2,x)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double y() const", asMETHOD(pos2,y)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dist(const pos2d@+ pos) const", asMETHOD(pos2,dist)); as_assert( r >= 0 );
   }

   static void DeclareOperators(asIScriptEngine* engine)
   {
      const std::string type_name = "pos2d";

      // local operators
      int r = 0;
      r = DeclareMethod(engine,type_name,"pos2d@ opAdd(pos2d@+ p1)",asMETHOD(pos2,opAddPos)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos2d@ opAdd(vec2d@+ v1)",asMETHOD(pos2,opAddVec)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos2d@ opAdd_r(vec2d@+ v1)",asMETHOD(pos2,opAddVec)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos2d@ opSub(vec2d@+ v1)",asMETHOD(pos2,opSubVec)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos2d@ opMul(double f1)",asMETHOD(pos2,opMulFact)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos2d@ opMul_r(double f1)",asMETHOD(pos2,opMulFact)); as_assert( r >= 0 );
   }
private:
   spacemath::pos2d m_pos;
};

#endif // SHAPE2D_H
