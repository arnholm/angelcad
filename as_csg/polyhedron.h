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

#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include "solid.h"
#include "spacemath/polyhedron3d.h"
#include "pos3.h"
#include "vec3.h"
#include "polyhedron_face.h"

using spacemath::polyhedron3d;

/// polyhedron generates a 3d polyhedron
class polyhedron : public solid {
public:

   polyhedron();
   polyhedron(const CScriptArray* points);
   polyhedron(const CScriptArray* points, const CScriptArray* faces);
   polyhedron(const string& file, int id);
   virtual ~polyhedron();

   // number of vertices
   size_t nvert() const;

   // return vertex position
   pos3* vertex(size_t iv) const;

   // set vertex position
   void set_vertex(size_t iv, pos3* pos);

   // number of faces
   size_t nface() const;

   // return face definition
   polyhedron_face* face(size_t iface) const;

   // return face area
   double face_area(size_t iface) const;

   // return the computed volume of the polyhedron
   double volume() const;

   // flip given face
   void flip_face(size_t iface);

   // flip all faces
   void flip_faces();

   // verify polyhedron against common issues, throw error message for any error found
   void verify() const;

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


   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static polyhedron* ctor_p(const CScriptArray* points) { return new polyhedron(points); }
   static polyhedron* ctor_pf(const CScriptArray* points, const CScriptArray* faces) { return new polyhedron(points,faces); }
   static polyhedron* ctor_f(const string& filepath, int id) { return new polyhedron(filepath,id); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<polyhedron>(),"polyhedron@ polyhedron(array<pos3d@>@+ points, array<pface@>@+ faces)",asFUNCTION(polyhedron::ctor_pf)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,as_typeid<polyhedron>(),"polyhedron@ polyhedron(array<pos3d@>@+ points)",asFUNCTION(polyhedron::ctor_p)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,as_typeid<polyhedron>(),"polyhedron@ polyhedron(string file, int id=-1)",asFUNCTION(polyhedron::ctor_f)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      solid::DeclareMethods<solid>(engine);
      solid::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
    //  int r = DeclareMethod(engine,type_name,"boundingbox@ box() const", asMETHOD(polyhedron,box)); as_assert( r >= 0 );
      int r = DeclareMethod(engine,type_name,"uint nvert() const", asMETHOD(polyhedron,nvert)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"pos3d@ vertex(uint iv) const", asMETHOD(polyhedron,vertex)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"void set_vertex(uint iv, pos3d@+ pos)", asMETHOD(polyhedron,set_vertex)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"uint nface() const", asMETHOD(polyhedron,nface)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"pface@ face(uint iface) const", asMETHOD(polyhedron,face)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"double face_area(uint iface) const", asMETHOD(polyhedron,face_area)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"void flip_face(uint iface)", asMETHOD(polyhedron,flip_face)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"void flip_faces()", asMETHOD(polyhedron,flip_faces)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"double volume() const", asMETHOD(polyhedron,volume)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"void verify() const", asMETHOD(polyhedron,verify)); as_assert( r >= 0 );
   }

private:
   std::shared_ptr<spacemath::polyhedron3d> m_poly;
};

#endif // POLYHEDRON_H
