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
   
#ifndef CUBE_H
#define CUBE_H

#include "solid.h"

/// cube generates a 3d cube
class cube : public solid {
public:

    // scripting interface
   cube(double size, bool center);
   virtual ~cube();

   double size() const;

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
   static cube* ctor_s(double size, bool center) { return new cube(size,center); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<cube>(), "cube@ cube(double size, bool center=false)",asFUNCTION(cube::ctor_s)); as_assert( r >= 0 );
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
      r = DeclareMethod(engine,type_name,"double size() const", asMETHOD(cube,size)); as_assert( r >= 0 );
   }

private:
   double m_size;
   bool   m_center;
};

#endif // CUBE_H
