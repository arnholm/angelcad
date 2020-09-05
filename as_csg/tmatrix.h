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

#ifndef TMATRIX_H
#define TMATRIX_H

#include "ce_angelscript_ex/as_reftype.h"
#include "spacemath/HTmatrix.h"
#include "pos3.h"
#include "pos2.h"
#include "vec3.h"
#include "solid.h"
#include "shape2d.h"
#include <string>
using namespace std;

/// tmatrix is an abstract tranformation from which concrete transformations derive
class tmatrix : public as_reftype {
public:

   void dump() const;

   vec3* xdir() const;
   vec3* ydir() const;
   vec3* zdir() const;
   pos3* origin() const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   tmatrix(const string& type);
   tmatrix(const string& type, const HTmatrix& matrix);
   virtual ~tmatrix();

   as_reftype* clone_scoped() { return new tmatrix(*this); }

   // create a clone of obj applying this transformation
   solid* clone_solid(solid* obj) const { return obj->clone_transform(this);}
   shape2d* clone_shape2d(shape2d* obj) const { return obj->clone_transform(this);}
   pos2* clone_pos2(pos2* obj) const { return obj->clone_transform(this);}
   pos3* clone_pos3(pos3* obj) const { return obj->clone_transform(this);}

   // provide read only access to body transform
   const HTmatrix& matrix() const;

   // special helper functions
   static double to_radian(double deg, double rad);
   static double to_radian(double deg);
   static double to_degree(double rad);

protected:
   /// \privatesection (hidden in documentation)

   HTmatrix& matrix();


protected:
   /// \privatesection (hidden in documentation)

   static tmatrix* multiply_tmatrix(const tmatrix* A, const tmatrix* B);

   // ==== SCRIPTING INTERFACE

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
      int r = DeclareMethod(engine,type_name,"tmatrix@ opMul(const tmatrix@+ B)",asFUNCTIONPR(multiply_tmatrix,(const tmatrix* A, const tmatrix* B),tmatrix* ),asCALL_CDECL_OBJLAST); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"vec3d@ xdir() const",asMETHOD(tmatrix,xdir)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"vec3d@ ydir() const",asMETHOD(tmatrix,ydir)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"vec3d@ zdir() const",asMETHOD(tmatrix,zdir)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"pos3d@ origin() const",asMETHOD(tmatrix,origin)); as_assert( r >= 0 );

          r = DeclareMethod(engine,type_name,"solid@ opMul(solid@+ obj)",asMETHOD(tmatrix,clone_solid)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"shape2d@ opMul(shape2d@+ obj)",asMETHOD(tmatrix,clone_shape2d)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"pos2d@ opMul(pos2d@+ obj)",asMETHOD(tmatrix,clone_pos2)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"pos3d@ opMul(pos3d@+ obj)",asMETHOD(tmatrix,clone_pos3)); as_assert( r >= 0 );

          r = DeclareMethod(engine,type_name,"void dump() const", asMETHOD(tmatrix,dump)); as_assert( r >= 0 );
    }
private:
   HTmatrix m_matrix;
};



#endif // TMATRIX_H
