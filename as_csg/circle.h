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

#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape2d.h"
class pos2;

/// circle generates a 2d circle
class circle : public shape2d {
public:
   // construct circle with given radius
   circle();
   circle(double r);
   circle(const pos2* p1, const pos2* p2, const pos2* p3);
   virtual ~circle();

   // return radius
   double radius() const;

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // clone this object onto a new shape2d
   virtual shape2d* clone_shape2d() const;

   string openscad_csg() const;

   spaceio::xml_node to_xcsg(spaceio::xml_node& xml_parent);

   // return bounding box
   virtual bbox3d get_box() const;

protected:
   /// \privatesection (hidden in documentation)

   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static circle* ctor_r(double r) { return new circle(r); }
   static circle* ctor_p3(const pos2* p1, const pos2* p2, const pos2* p3) { return new circle(p1,p2,p3); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<circle>(),"circle@ circle(double r)",asFUNCTION(circle::ctor_r)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,as_typeid<circle>(),"circle@ circle(const pos2d@+ p1, const pos2d@+ p2, const pos2d@+ p3 )",asFUNCTION(circle::ctor_p3)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      shape2d::DeclareMethods<shape2d>(engine);
      shape2d::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
      int r = DeclareMethod(engine,type_name,"double radius() const", asMETHOD(circle,radius)); as_assert( r >= 0 );

      // short form
      r = DeclareMethod(engine,type_name,"double r() const", asMETHOD(circle,radius)); as_assert( r >= 0 );
   }

private:
   double m_radius;
};

#endif // SPHERE_H
