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
   
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape2d.h"

/// rectangle generates a 2d rectangle
class rectangle : public shape2d {
public:
   // scripting interface
   rectangle(double dx, double dy, bool center);
   double dx() const;
   double dy() const;
   virtual ~rectangle();

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
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
   static rectangle* ctor_xyc(double dx, double dy, bool center) { return new rectangle(dx, dy, center); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<rectangle>(), "rectangle@ rectangle(double dx, double dy, bool center=false)",asFUNCTION(rectangle::ctor_xyc)); as_assert( r >= 0 );
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
      int r = 0;
      r = DeclareMethod(engine,type_name,"double dx() const", asMETHOD(rectangle,dx)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dy() const", asMETHOD(rectangle,dy)); as_assert( r >= 0 );

	  // archaic form
    //  r = DeclareMethod(engine,type_name,"double width() const", asMETHOD(rectangle,dx)); as_assert( r >= 0 );
    //  r = DeclareMethod(engine,type_name,"double height() const", asMETHOD(rectangle,dy)); as_assert( r >= 0 );
   }

private:
   double m_dx;
   double m_dy;
   bool   m_center;
};

#endif // RECTANGLE_H
