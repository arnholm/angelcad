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

#ifndef PFACE_H
#define PFACE_H

#include "ce_angelscript_ex/as_reftype.h"
#include <vector>
using namespace std;
class CScriptArray;

/// polyhedron_face is a plane polyhedron face, usually a triangle
class polyhedron_face : public as_reftype {
public:
    // scripting interface
   polyhedron_face(const CScriptArray* nodes);
   polyhedron_face(int n1, int n2, int n3, int n4=-1, int n5=-1, int n6=-1, int n7=-1, int n8=-1, int n9=-1);
   polyhedron_face(const vector<size_t>& face);
   virtual ~polyhedron_face();

   // number of vertices
   size_t nvert() const;

   // return vertex index
   size_t vindex(size_t iv) const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

   const vector<size_t>& nodes() const;

protected:
   /// \privatesection (hidden in documentation)

   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static polyhedron_face* ctor_n3(int n1, int n2, int n3 )                                                 { return new polyhedron_face(n1,n2,n3); }
   static polyhedron_face* ctor_n4(int n1, int n2, int n3, int n4 )                                         { return new polyhedron_face(n1,n2,n3,n4); }
   static polyhedron_face* ctor_n5(int n1, int n2, int n3, int n4 ,int n5 )                                 { return new polyhedron_face(n1,n2,n3,n4,n5); }
   static polyhedron_face* ctor_n6(int n1, int n2, int n3, int n4 ,int n5, int n6 )                         { return new polyhedron_face(n1,n2,n3,n4,n5,n6); }
   static polyhedron_face* ctor_n7(int n1, int n2, int n3, int n4 ,int n5, int n6, int n7 )                 { return new polyhedron_face(n1,n2,n3,n4,n5,n6,n7); }
   static polyhedron_face* ctor_n8(int n1, int n2, int n3, int n4 ,int n5, int n6, int n7, int n8 )         { return new polyhedron_face(n1,n2,n3,n4,n5,n6,n7,n8); }
   static polyhedron_face* ctor_n9(int n1, int n2, int n3, int n4 ,int n5, int n6, int n7, int n8 ,int n9 ) { return new polyhedron_face(n1,n2,n3,n4,n5,n6,n7,n8,n9); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      const std::string type_name = "pface";
      int r = DeclareConstructor(engine,type_name, "pface@ pface(uint iv1, uint iv2, uint iv3 )",asFUNCTION(polyhedron_face::ctor_n3)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "pface@ pface(uint iv1, uint iv2, uint iv3, uint iv4 )",asFUNCTION(polyhedron_face::ctor_n4)); as_assert( r >= 0 );

      // cannot call polyhedron::volume() for more than 4 vertices
      //    r = DeclareConstructor(engine,type_name, "pface@ pface(uint iv1, uint iv2, uint iv3, uint iv4, uint iv5)",asFUNCTION(polyhedron_face::ctor_n5)); as_assert( r >= 0 );
      //    r = DeclareConstructor(engine,type_name, "pface@ pface(uint iv1, uint iv2, uint iv3, uint iv4, uint iv5, uint iv6)",asFUNCTION(polyhedron_face::ctor_n6)); as_assert( r >= 0 );
      //    r = DeclareConstructor(engine,type_name, "pface@ pface(uint iv1, uint iv2, uint iv3, uint iv4, uint iv5, uint iv6, uint iv7)",asFUNCTION(polyhedron_face::ctor_n7)); as_assert( r >= 0 );
      //    r = DeclareConstructor(engine,type_name, "pface@ pface(uint iv1, uint iv2, uint iv3, uint iv4, uint iv5, uint iv6, uint iv7, uint iv8)",asFUNCTION(polyhedron_face::ctor_n8)); as_assert( r >= 0 );
      //    r = DeclareConstructor(engine,type_name, "pface@ pface(uint iv1, uint iv2, uint iv3, uint iv4, uint iv5, uint iv6, uint iv7, uint iv8, uint iv9)",asFUNCTION(polyhedron_face::ctor_n9)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      const std::string type_name = "pface";
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = DeclareMethod(engine,type_name,"uint nvert() const", asMETHOD(polyhedron_face,nvert)); as_assert( r >= 0 );
          r = DeclareMethod(engine,type_name,"uint vindex(uint iv) const", asMETHOD(polyhedron_face,vindex)); as_assert( r >= 0 );
   }

private:
   vector<size_t> m_nodes;
};

#endif // SQUARE_H
