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

#ifndef MINKOWSKI2D_H
#define MINKOWSKI2D_H

#include "shape2d.h"
#include "shape2d_vector.h"

/// minkowski2d computes the Minkowski sum for 2d shapes
class minkowski2d : public shape2d {
public:

   // constructors with script array
   minkowski2d(const shape2d* a, const shape2d* b);
   virtual ~minkowski2d();

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

   virtual void populate_tree(node_csg* node) ;

   static minkowski2d* ctor_s2(const shape2d* a, const shape2d* b ) { return new minkowski2d(a,b); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      const std::string type_name = as_typeid<minkowski2d>();
      int r = DeclareConstructor(engine,type_name, "minkowski2d@ minkowski2d(const shape2d@+ a, const shape2d@+ b )",asFUNCTION(minkowski2d::ctor_s2)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      shape2d::DeclareMethods<shape2d>(engine);
      shape2d::DeclareMethods<T>(engine);

      std::string type_name = as_typeid<T>();
   }


private:
   shape2d_vector  m_incl;
};

#endif // HULL2D_H
