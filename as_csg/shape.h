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
   
#ifndef CSG_SHAPE_H
#define CSG_SHAPE_H

#include "ce_angelscript_ex/as_reftype.h"
class tmatrix;
#include "spacemath/HTmatrix.h"
#include "spacemath/bbox3d.h"
#include "node_csg.h"
#include "spaceio/xml_node.h"
class boundingbox;

using spacemath::bbox3d;
using spacemath::pos3d;

/// shape is an abstract application class from which concrete 3d or 2d primitives derive
class shape : public as_reftype {
public:
   virtual ~shape();

   // export csg tree
   void write_csg(const string& path);

   // export xcsg tree
   void write_xcsg(const string& path, double secant_tolerance);

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

   // clone this object into a new shape
   virtual shape* clone_shape() const = 0;

   // return transformation matrix
   tmatrix* transform() const;
   virtual HTmatrix get_transform() const = 0;

   // return bounding box
   boundingbox* box() const;
   virtual bbox3d get_box() const = 0;

   // populate tree may be overridden
   virtual void populate_tree(node_csg* node);

   // get the openscad csg string for this type
   virtual string openscad_csg() const = 0;

   void export_csg(ostream& out);

   virtual spaceio::xml_node to_xcsg(spaceio::xml_node& xml_parent);

protected:
   /// \privatesection (hidden in documentation)

   // application is not allowed to construct shapes directly
   shape(const std::string& type);

protected:
   /// \privatesection (hidden in documentation)
   void add_metadata(spaceio::xml_node& xml_parent, const string& model_name);


   // ==== SCRIPTING INTERFACE

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
      int r = DeclareMethod(engine,type_name,"tmatrix@ transform() const", asMETHOD(shape,transform)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"boundingbox@ box() const", asMETHOD(shape,box)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"void write_csg(string path)", asMETHOD(shape,write_csg)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"void write_xcsg(string path, double secant_tolerance=-1.0)", asMETHOD(shape,write_xcsg)); as_assert( r >= 0 );
   }

};

#endif // SHAPE2D_H
