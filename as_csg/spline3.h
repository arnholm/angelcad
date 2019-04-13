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
   
#ifndef SPLINE3D_H
#define SPLINE3D_H

#include "ce_angelscript_ex/as_reftype.h"
#include "spacemath/pos3d.h"
#include "spacemath/spline3d.h"
class pos3;
class vec3;
#include <vector>
using namespace std;
class CScriptArray;

using spacemath::pos3d;
using spacemath::vec3d;

/// spline3 is a spline curve in 3d space
class spline3 : public as_reftype {
public:
    // scripting interface
   spline3(const CScriptArray* points);
   spline3(const pos3* p1, const pos3* p2, const pos3* p3=0, const pos3* p4=0, const pos3* p5=0);
   virtual ~spline3();

   pos3* pos(double t) const;
   vec3* dir(double t) const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

   // position interpolation
   pos3d pos_raw(double t) const;

   // direction interpolation
   vec3d vec_raw(double t) const;

   const spacemath::spline3d& spline_raw() const;

protected:
   /// \privatesection (hidden in documentation)

   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static spline3* ctor_arr(const CScriptArray* points) { return new spline3(points); }
   static spline3* ctor_p2(const pos3* p1, const pos3* p2                                                ) { return new spline3(p1,p2); }
   static spline3* ctor_p3(const pos3* p1, const pos3* p2, const pos3* p3                                ) { return new spline3(p1,p2,p3); }
   static spline3* ctor_p4(const pos3* p1, const pos3* p2, const pos3* p3, const pos3* p4                ) { return new spline3(p1,p2,p3,p4); }
   static spline3* ctor_p5(const pos3* p1, const pos3* p2, const pos3* p3, const pos3* p4, const pos3* p5) { return new spline3(p1,p2,p3,p4,p5); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      std::string type_name = "spline3d";
      int r = DeclareConstructor(engine,type_name, "spline3d@ spline3d(array<pos3d@>@+ points)",asFUNCTION(spline3::ctor_arr)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      std::string type_name = "spline3d";
      // inherit methods
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = 0;
      r = DeclareMethod(engine,type_name,"pos3d@ pos(double t) const", asMETHOD(spline3,pos)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec3d@ dir(double t) const", asMETHOD(spline3,dir)); as_assert( r >= 0 );
   }

private:
   spacemath::spline3d m_spline;
};

#endif // SQUARE_H
