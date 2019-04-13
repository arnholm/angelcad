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
   
#ifndef SWEEP_H
#define SWEEP_H

#include "solid.h"
#include "shape2d.h"
#include "shape2d_vector.h"
#include "tmatrix.h"
#include <vector>
#include "spacemath/pos3d.h"
#include "spacemath/vec3d.h"

using spacemath::pos3d;
using spacemath::vec3d;

class spline_path;

/// sweep provides spline curve extrusion from 2d shapes to 3d objects
class sweep : public solid {
public:
   virtual ~sweep();

   // constructors
   sweep(const shape2d* shape, const spline_path* path);

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

   static sweep* ctor_sp(const shape2d* shape, const spline_path* path) { return new sweep(shape,path); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<sweep>(), "sweep@ sweep(const shape2d@+ shape,const spline_path@+ path)",asFUNCTION(sweep::ctor_sp)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      solid::DeclareMethods<solid>(engine);
      solid::DeclareMethods<T>(engine);

//      std::string type_name = as_typeid<T>();
//      int r = DeclareMethod(engine,type_name,"double rad() const", asMETHOD(sweep,rad)); as_assert( r >= 0 );
   }


private:
  shape2d_vector  m_shapes; // we use a vector here because it knows how to manage references/cloning
  std::vector<pos3d> m_p;   // spline points
  std::vector<vec3d> m_v;   // orientation vectors
};

#endif // SWEEP_H
