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

#ifndef OFFSET2D_H
#define OFFSET2D_H

#include "shape2d.h"
#include "shape2d_vector.h"
#include <utility>

/// offset2d offsets a profile inwards or ou
class offset2d : public shape2d {
public:

   // constructors with script array
   offset2d(const CScriptArray* arr, double r, double delta, bool chamfer);
   offset2d(const shape2d* s1, double r, double delta, bool chamfer);
   virtual ~offset2d();

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

   static std::pair<double,bool> interpret_offset(double r, double delta);

   virtual void populate_tree(node_csg* node) ;

   static offset2d* ctor_arr(const CScriptArray* arr, double r, double delta, bool chamfer) { return new offset2d(arr,r,delta,chamfer); }
   static offset2d* ctor_sr(const shape2d* s1, double r, double delta, bool chamfer )       { return new offset2d(s1,r,delta,chamfer);  }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      const std::string type_name = as_typeid<offset2d>();
      int r = DeclareConstructor(engine,type_name, "offset2d@ offset2d(array<shape2d@>@+ arr, double r=0x7fc00000, double delta=0x7fc00000, bool chamfer=false)",asFUNCTION(offset2d::ctor_arr)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "offset2d@ offset2d(const shape2d@+ profile, double r=0x7fc00000, double delta=0x7fc00000, bool chamfer=false)",asFUNCTION(offset2d::ctor_sr)); as_assert( r >= 0 );

   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      shape2d::DeclareMethods<shape2d>(engine);
      shape2d::DeclareMethods<T>(engine);

      std::string type_name = as_typeid<T>();
    //  int r = 0;
    //  r = DeclareMethod(engine,type_name,"double height() const", asMETHOD(cylinder,height)); as_assert( r >= 0 );
   }


private:
   double m_delta;    // offset value
   bool   m_round;    // use rounded corners
   bool   m_chamfer;  // apply chamfer corners (ignored for m_round=true)
   shape2d_vector  m_incl;
};

#endif // UNION2D_H
