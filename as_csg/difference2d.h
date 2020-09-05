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

#ifndef DIFFERENCE2D_H
#define DIFFERENCE2D_H

#include "shape2d.h"
#include "shape2d_vector.h"

/// difference2d provides boolean difference for 2d objects
class difference2d : public shape2d {
public:
   // Difference allows single arguments only
   difference2d(const shape2d* incl, const shape2d*  excl);

   virtual ~difference2d();


   /// \privatesection (hidden in documentation)

   // clone this object onto a new shape2d
   virtual shape2d* clone_shape2d() const;

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   string openscad_csg() const;

   spaceio::xml_node to_xcsg(spaceio::xml_node& xml_parent);

   // return bounding box
   virtual bbox3d get_box() const;

protected:
   /// \privatesection (hidden in documentation)

   virtual void populate_tree(node_csg* node) ;

   static difference2d* ctor_ss(const shape2d* incl,    const shape2d* excl)    { return new difference2d(incl,excl); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<difference2d>(), "difference2d@ difference2d(shape2d@+ incl, shape2d@+ excl)",asFUNCTION(difference2d::ctor_ss)); as_assert( r >= 0 );
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
   shape2d_vector m_incl;
   shape2d_vector m_excl;
};

#endif // CSG_DIFFERENCE_H
