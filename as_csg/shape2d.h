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
   
#ifndef SHAPE2D_H
#define SHAPE2D_H

#include "shape.h"

/// shape2d is an abstract application class from which concrete 2d primitives derive
class shape2d : public shape {
public:
   virtual ~shape2d();

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by shape
   shape* clone_shape() const;

   // clone this object into a new shape2d
   virtual shape2d* clone_shape2d() const = 0;

   // create a clone with given transformation
   virtual shape2d* clone_transform(const tmatrix* matrix) const;

   // return transformation matrix
   HTmatrix get_transform() const;

   virtual void populate_tree(node_csg* node);

   // get the openscad csg string for this type
   virtual string openscad_csg() const = 0;

protected:
   /// \privatesection (hidden in documentation)

   shape2d(const shape2d& other);

   // apply the transformation to this object
   shape2d* transform(const tmatrix* matrix);
   shape2d* transform(const HTmatrix& matrix);

   // application is not allowed to construct shape2ds directly
   shape2d(const std::string& type);

   // add transform to xml node and return same node
   spaceio::xml_node& transform(spaceio::xml_node& xml_parent);

   shape2d* opAdd(const shape2d* b);  // union2d
   shape2d* opSub(const shape2d* b);  // difference2d
   shape2d* opAnd(const shape2d* b);  // intersection2d

protected:

   // ==== SCRIPTING INTERFACE

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      shape::DeclareMethods<shape>(engine);
      shape::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
      int r = 0;
      r = DeclareMethod(engine,type_name,"shape2d@ opMul(tmatrix@+ matrix)",asMETHOD(shape2d,clone_transform)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"shape2d@ opAdd(shape2d@+ b)",asMETHOD(shape2d,opAdd)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"shape2d@ opSub(shape2d@+ b)",asMETHOD(shape2d,opSub)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"shape2d@ opAnd(shape2d@+ b)",asMETHOD(shape2d,opAnd)); as_assert( r >= 0 );
   }

private:
   HTmatrix m_transform;
};

#endif // SHAPE2D_H
