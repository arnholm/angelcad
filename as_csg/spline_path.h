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

#ifndef SPLINE_PATH_H
#define SPLINE_PATH_H

#include "ce_angelscript_ex/as_reftype.h"
#include "pos3.h"
#include "vec3.h"
#include <vector>
class CScriptArray;

/// spline_path defines a 3d path for use in sweeping
class spline_path : public as_reftype {
public:

   spline_path(const CScriptArray* points, const CScriptArray* vectors);
   spline_path(const CScriptArray* points, const vec3* v);
   virtual ~spline_path();

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   const std::vector<pos3d>& p() const { return m_p; }
   const std::vector<vec3d>& v() const { return m_v; }


protected:
   /// \privatesection (hidden in documentation)


   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static spline_path* ctor_pv(const CScriptArray* p, const CScriptArray* v) { return new spline_path(p,v); }
   static spline_path* ctor_pv1(const CScriptArray* p, const vec3* v) { return new spline_path(p,v); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<spline_path>(),"spline_path@ spline_path(array<pos3d@>@+ p, array<vec3d@>@+ v)",asFUNCTION(spline_path::ctor_pv)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,as_typeid<spline_path>(),"spline_path@ spline_path(array<pos3d@>@+ p, vec3d@+ v)"        ,asFUNCTION(spline_path::ctor_pv1)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
    //  int r = DeclareMethod(engine,type_name,"boundingbox@ box() const", asMETHOD(spline_path,box)); as_assert( r >= 0 );
   }

private:
   std::vector<pos3d> m_p;  // spline points
   std::vector<vec3d> m_v;  // orientation vectors
};

#endif // SPLINE_PATH_H
