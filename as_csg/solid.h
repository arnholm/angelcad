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

#ifndef SOLID_H
#define SOLID_H

#include "shape.h"
class tmatrix;

/// solid is an abstract application class from which concrete solid primitives derive
class solid : public shape {
public:
   virtual ~solid();

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by shape
   shape* clone_shape() const;

   // clone this object into a new solid
   virtual solid* clone_solid() const = 0;

   // create a clone with given transformation
   virtual solid* clone_transform(const tmatrix* matrix) const;

   // return transformation matrix
   HTmatrix get_transform() const;

   // assign transformmation matrix directly
   void set_transform(const HTmatrix& matrix) { m_transform = matrix; }

   // get the openscad csg string for this type
   virtual string openscad_csg() const = 0;

protected:
   /// \privatesection (hidden in documentation)

   // apply the transformation to this object
   solid* transform(const tmatrix* matrix);

   solid* opAdd(const solid* b);  // union3d
   solid* opSub(const solid* b);  // difference3d
   solid* opAnd(const solid* b);  // intersection3d

   // application is not allowed to construct solids directly
   solid(const std::string& type);

   // add transform to xml node and return same node
   spaceio::xml_node& transform(spaceio::xml_node& xml_parent);

protected:
   /// \privatesection (hidden in documentation)


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
      r = DeclareMethod(engine,type_name,"solid@ opMul(tmatrix@+ matrix)",asMETHOD(solid,clone_transform)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"solid@ opAdd(solid@+ b)",asMETHOD(solid,opAdd)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"solid@ opSub(solid@+ b)",asMETHOD(solid,opSub)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"solid@ opAnd(solid@+ b)",asMETHOD(solid,opAnd)); as_assert( r >= 0 );
   }

private:
   HTmatrix m_transform;
};

#endif // SOLID_H
