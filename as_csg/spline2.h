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

#ifndef SPLINE2D_H
#define SPLINE2D_H

#include "ce_angelscript_ex/as_reftype.h"
#include "spacemath/pos2d.h"
#include "spacemath/vec2d.h"
#include "spacemath/spline2d.h"

class pos2;
class vec2;

#include <vector>
using namespace std;
class CScriptArray;

/// spline2 is a spline curve in 2d space
class spline2 : public as_reftype {
public:
    // scripting interface
   spline2(const CScriptArray* points);
   spline2(const pos2* p1, const pos2* p2, const pos2* p3=0, const pos2* p4=0, const pos2* p5=0);
   virtual ~spline2();

   pos2* pos(double t) const;
   vec2* dir(double t) const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

   spacemath::pos2d pos_raw(double t) const;

   // direction interpolation
   spacemath::vec2d vec_raw(double t) const;

protected:
   /// \privatesection (hidden in documentation)

   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static spline2* ctor_arr(const CScriptArray* points) { return new spline2(points); }
   static spline2* ctor_p2(const pos2* p1, const pos2* p2                                                ) { return new spline2(p1,p2); }
   static spline2* ctor_p3(const pos2* p1, const pos2* p2, const pos2* p3                                ) { return new spline2(p1,p2,p3); }
   static spline2* ctor_p4(const pos2* p1, const pos2* p2, const pos2* p3, const pos2* p4                ) { return new spline2(p1,p2,p3,p4); }
   static spline2* ctor_p5(const pos2* p1, const pos2* p2, const pos2* p3, const pos2* p4, const pos2* p5) { return new spline2(p1,p2,p3,p4,p5); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      std::string type_name = "spline2d";
      int r = DeclareConstructor(engine,type_name, "spline2d@ spline2d(array<pos2d@>@+ points)",asFUNCTION(spline2::ctor_arr)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      std::string type_name = "spline2d";
      // inherit methods
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = 0;
      r = DeclareMethod(engine,type_name,"pos2d@ pos(double t) const", asMETHOD(spline2,pos)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"vec2d@ dir(double t) const", asMETHOD(spline2,dir)); as_assert( r >= 0 );
   }

private:
   spacemath::spline2d m_spline;
};

#endif // SQUARE_H
