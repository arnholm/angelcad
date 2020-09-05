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

#ifndef CYLINDER_H
#define CYLINDER_H

#include "solid.h"

/// cylinder generates a 3d cylinder
class cylinder : public solid {
public:

   // scripting interface
   cylinder(double h, double r, bool center);
   virtual ~cylinder();

   double height() const;
   double radius() const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
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
   static cylinder* ctor_hrc(double h, double r, bool center) { return new cylinder(h,r,center); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      std::string type_name = as_typeid<cylinder>();
      int r = DeclareConstructor(engine,type_name, "cylinder@ cylinder(double h, double r, bool center=false)",asFUNCTION(cylinder::ctor_hrc)); as_assert( r >= 0 );
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
      int r = 0;
      r = DeclareMethod(engine,type_name,"double height() const", asMETHOD(cylinder,height)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double radius() const", asMETHOD(cylinder,radius)); as_assert( r >= 0 );

      // short form
      r = DeclareMethod(engine,type_name,"double h() const", asMETHOD(cylinder,height)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double r() const", asMETHOD(cylinder,radius)); as_assert( r >= 0 );
   }

private:
   double m_height;
   double m_radius;
   bool   m_center;
};

#endif // CYLINDER_H
