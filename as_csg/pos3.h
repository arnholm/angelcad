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

#ifndef POSITION3D_H
#define POSITION3D_H

#include "ce_angelscript_ex/as_reftype.h"
#include "ce_angelscript_ex/as_initializer_vector.h"
#include "spacemath/pos3d.h"
class tmatrix;
class vec3;
using spacemath::pos3d;

/// pos3 is a utility class used with 3d primitives, the script class name is "pos3d"
class pos3 : public as_reftype {
   friend class as_csg;
public:
   // constructor
   pos3(double x, double y, double z);
   pos3(const as_initializer_vector<double>& v);
   pos3(const pos3d& pos);
   virtual ~pos3();

   double dist(const pos3* pos) const;

   double x() const;
   double y() const;
   double z() const;

   pos3* opAddPos(const pos3* p1);  // p + p1
   pos3* opAddVec(const vec3* v1);    // p + v1
   pos3* opSubVec(const vec3* v1);    // p - v1
   pos3* opMulFact(double fact);          // p*0.5

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // create a clone with given transformation
   virtual pos3* clone_transform(const tmatrix* matrix) const;

   // required by as_reftype
   as_reftype* clone_scoped();

   operator pos3d() const { return m_pos; }
   spacemath::pos3d pos() const { return m_pos; }

protected:
   /// \privatesection (hidden in documentation)

   static pos3* ctor_xyz(double x, double y, double z) { return new pos3(x,y,z); }
   static pos3* ctor_copy(const pos3* p) { return new pos3(p->m_pos); }
   static pos3* ctor_initlist(void* initlist) { return new pos3(as_initializer_vector<double>(3,initlist)); };

   // ==== SCRIPTING INTERFACE
   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,"pos3d","pos3d@ pos3d(double x,double y, double z)",asFUNCTION(pos3::ctor_xyz)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,"pos3d","pos3d@ pos3d(const pos3d@+ other)",asFUNCTION(pos3::ctor_copy)); as_assert( r >= 0 );
          r = DeclareConstructorInitList(engine,"pos3d","pos3d@ pos3d(int &in list) {repeat double}",asFUNCTION(pos3::ctor_initlist)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      const std::string type_name = "pos3d";
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = 0;
      r = DeclareMethod(engine,type_name,"double x() const", asMETHOD(pos3,x)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double y() const", asMETHOD(pos3,y)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double z() const", asMETHOD(pos3,z)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dist(const pos3d@+ pos) const", asMETHOD(pos3,dist)); as_assert( r >= 0 );
   }

   static void DeclareOperators(asIScriptEngine* engine)
   {
      const std::string type_name = "pos3d";

      // local operators
      int r = 0;
      r = DeclareMethod(engine,type_name,"pos3d@ opAdd(pos3d@+ p1)",asMETHOD(pos3,opAddPos)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos3d@ opAdd(vec3d@+ v1)",asMETHOD(pos3,opAddVec)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos3d@ opAdd_r(vec3d@+ v1)",asMETHOD(pos3,opAddVec)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos3d@ opSub(vec3d@+ v1)",asMETHOD(pos3,opSubVec)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos3d@ opMul(double f1)",asMETHOD(pos3,opMulFact)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos3d@ opMul_r(double f1)",asMETHOD(pos3,opMulFact)); as_assert( r >= 0 );
   }
private:
   pos3d m_pos;
};

#endif // SHAPE3D_H
