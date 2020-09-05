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

#ifndef CONE_H
#define CONE_H

#include "solid.h"

/// cone generates a 3d cone
class cone : public solid {
public:

   // scripting interface
   cone(double h, double r1, double r2, bool center);
   virtual ~cone();

   double height() const;
   double radius1() const;
   double radius2() const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // clone this object onto a new solid
   virtual solid* clone_solid() const;

   string openscad_csg() const ;

   spaceio::xml_node to_xcsg(spaceio::xml_node& xml_parent);

   // return bounding box
   virtual bbox3d get_box() const;

protected:
   /// \privatesection (hidden in documentation)

   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static cone* ctor_hrrc(double h, double r1, double r2, bool center) { return new cone(h,r1,r2,center); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<cone>(), "cone@ cone(double h, double r1, double r2, bool center=false)",asFUNCTION(cone::ctor_hrrc)); as_assert( r >= 0 );
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
      r = DeclareMethod(engine,type_name,"double height() const", asMETHOD(cone,height)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double radius1() const", asMETHOD(cone,radius1)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double radius2() const", asMETHOD(cone,radius2)); as_assert( r >= 0 );

	  // short form
      r = DeclareMethod(engine,type_name,"double h() const", asMETHOD(cone,height)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double r1() const", asMETHOD(cone,radius1)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double r2() const", asMETHOD(cone,radius2)); as_assert( r >= 0 );
   }

private:
   double m_height;
   double m_radius1;
   double m_radius2;
   bool   m_center;
};

#endif // CONE_H
