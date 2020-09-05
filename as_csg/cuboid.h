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

#ifndef CUBOID_H
#define CUBOID_H

#include "solid.h"

/// cuboid generates a 3d cuboid
class cuboid : public solid {
public:

   // scripting interface
   cuboid(double dx, double dy, double dz, bool center);
   virtual ~cuboid();

   double dx() const;
   double dy() const;
   double dz() const;

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
   static cuboid* ctor_xyz(double dx, double dy, double dz, bool center) { return new cuboid(dx, dy, dz,center); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<cuboid>(), "cuboid@ cuboid(double dx, double dy, double dz, bool center=false)",asFUNCTION(cuboid::ctor_xyz)); as_assert( r >= 0 );
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
      r = DeclareMethod(engine,type_name,"double dx() const", asMETHOD(cuboid,dx)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dy() const", asMETHOD(cuboid,dy)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dz() const", asMETHOD(cuboid,dz)); as_assert( r >= 0 );

	  // archaic form
     //  r = DeclareMethod(engine,type_name,"double width() const", asMETHOD(cuboid,dx)); as_assert( r >= 0 );
     //  r = DeclareMethod(engine,type_name,"double depth() const", asMETHOD(cuboid,dy)); as_assert( r >= 0 );
     //  r = DeclareMethod(engine,type_name,"double height() const", asMETHOD(cuboid,dz)); as_assert( r >= 0 );
   }

private:
   double m_dx;
   double m_dy;
   double m_dz;
   bool   m_center;
};

#endif // CUBOID_H
