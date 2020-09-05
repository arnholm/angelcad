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

#ifndef LINE3_H
#define LINE3_H

#include "ce_angelscript_ex/as_reftype.h"
#include "spacemath/line3d.h"
class pos3;

/// line3 is a utility class used with 3d primitives, the script class name is "line3d"
class line3 : public as_reftype {
public:
   // constructor
   line3(const pos3* p1, const pos3* p2);
   line3(const spacemath::line3d& vec);
   virtual ~line3();

   // return end points of line
   pos3* end1() const;
   pos3* end2() const;

   // length of line
   double length() const;

   // parameter in interval [0.0, 1.0], i.e. relative distance from end1
   pos3* interpolate(double par) const;

   // project point onto line and return parameter value (0.0 at end1 and 1.0 at end2)
   double project(const pos3* point) const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

   operator spacemath::line3d() const { return m_line; }

protected:
   /// \privatesection (hidden in documentation)

   static line3* ctor_p12(const pos3* p1, const pos3* p2) { return new line3(p1,p2); }

   // ==== SCRIPTING INTERFACE
   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,"line3d","line3d@ line3d(const pos3d@+ p1, const pos3d@+ p2)",asFUNCTION(line3::ctor_p12)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      const std::string type_name = "line3d";
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = 0;
      r = DeclareMethod(engine,type_name,"pos3d@ end1() const", asMETHOD(line3,end1)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos3d@ end2() const", asMETHOD(line3,end2)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double length() const", asMETHOD(line3,length)); as_assert( r >= 0 );

      r = DeclareMethod(engine,type_name,"pos3d@ interpolate(double par) const", asMETHOD(line3,interpolate)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double project(pos3d@+ point) const", asMETHOD(line3,project)); as_assert( r >= 0 );
   }
private:
   spacemath::line3d m_line;
};

#endif // SHAPE3D_H
