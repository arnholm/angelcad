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
   
#ifndef MINKOWSKI3D_H
#define MINKOWSKI3D_H

#include "solid.h"
#include "solid_vector.h"

/// minkowski3d computes the Minkowski sum for 3d solids (NOT supported in .xcsg)
class minkowski3d : public solid {
public:
   minkowski3d(const solid* a, const solid* b);
   virtual ~minkowski3d();

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // clone this object onto a new solid
   virtual solid* clone_solid() const;

   string openscad_csg() const;

   // return bounding box
   virtual bbox3d get_box() const;

   spaceio::xml_node to_xcsg(spaceio::xml_node& xml_parent);

protected:
   /// \privatesection (hidden in documentation)

   virtual void populate_tree(node_csg* node) ;

   static minkowski3d* ctor_s2(const solid* a, const solid* b) { return new minkowski3d(a,b);          }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      const std::string type_name = as_typeid<minkowski3d>();
      int r = DeclareConstructor(engine,type_name, "minkowski3d@ minkowski3d(const solid@+ a, const solid@+ b )",asFUNCTION(minkowski3d::ctor_s2)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      solid::DeclareMethods<solid>(engine);
      solid::DeclareMethods<T>(engine);

      std::string type_name = as_typeid<T>();
   }


private:
   solid_vector  m_incl;
};

#endif // UNION3D_H
