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

#ifndef TRANSFORM_EXTRUDE_H
#define TRANSFORM_EXTRUDE_H

#include "solid.h"
#include "shape2d.h"
#include "shape2d_vector.h"

/// transform_extrude transforms between 2d shapes
class transform_extrude : public solid {
public:
   virtual ~transform_extrude();

   // constructors
   transform_extrude(const shape2d* bottom, const shape2d* top);

   /// \privatesection (hidden in documentation)

   const shape2d* shape() const;

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

   virtual void populate_tree(node_csg* node) ;

   static transform_extrude* ctor_h(const shape2d* bottom, const shape2d* top) { return new transform_extrude(bottom,top); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<transform_extrude>(), "transform_extrude@ transform_extrude(const shape2d@+ bottom, const shape2d@+ top)",asFUNCTION(transform_extrude::ctor_h)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      solid::DeclareMethods<solid>(engine);
      solid::DeclareMethods<T>(engine);

      std::string type_name = as_typeid<T>();
     // int r = DeclareMethod(engine,type_name,"double height() const", asMETHOD(transform_extrude,height)); as_assert( r >= 0 );
   }


private:
  shape2d_vector  m_shapes; // we use a vector here because it knows how to manage references/cloning
};

#endif // UNION3D_H
