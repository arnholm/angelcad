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

#ifndef SPHERE_H
#define SPHERE_H

#include "solid.h"

/// sphere generates a 3d sphere
class sphere : public solid {
public:

   // construct sphere with given radius
   sphere();
   sphere(double r);
   virtual ~sphere();

   // return radius
   double radius() const;

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // clone this object onto a new solid
   virtual solid* clone_solid() const;

   string openscad_csg() const;

   spaceio::xml_node to_xcsg(spaceio::xml_node& xml_parent);

   // return bounding box
   virtual bbox3d get_box() const;

protected:
   /// \privatesection (hidden in documentation)


   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static sphere* ctor_r(double r) { return new sphere(r); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<sphere>(),"sphere@ sphere(double r)",asFUNCTION(sphere::ctor_r)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      solid::DeclareMethods<solid>(engine);
      solid::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
      int r = DeclareMethod(engine,type_name,"double radius() const", asMETHOD(sphere,radius)); as_assert( r >= 0 );

      // short form
      r = DeclareMethod(engine,type_name,"double r() const", asMETHOD(sphere,radius)); as_assert( r >= 0 );
   }

private:
   double m_radius;
};

#endif // SPHERE_H
