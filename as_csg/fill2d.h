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

#ifndef FILL2D_H
#define FILL2D_H

#include "shape2d.h"
#include "shape2d_vector.h"

/// fill2d provides boolean "hull" operation for 2d objects (NOT supported in .xcsg)
class fill2d : public shape2d {
public:
   // constructors with script array
   fill2d(const CScriptArray* arr);
   fill2d(const shape2d* s1);

   virtual ~fill2d();

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

   static fill2d* ctor_arr(const CScriptArray* arr) { return new fill2d(arr); }
   static fill2d* ctor_s1(const shape2d* s1       ) { return new fill2d(s1);          }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
       const std::string type_name = as_typeid<fill2d>();
      int r = DeclareConstructor(engine,type_name, "fill2d@ fill2d(array<shape2d@>@+ arr)",asFUNCTION(fill2d::ctor_arr)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "fill2d@ fill2d(const shape2d@+ s1)"   ,asFUNCTION(fill2d::ctor_s1));  as_assert( r >= 0 );
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
   shape2d_vector  m_incl;
};

#endif // fill2d_H
