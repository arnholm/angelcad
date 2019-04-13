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
   
#ifndef UNION3D_H
#define UNION3D_H

#include "solid.h"
#include "solid_vector.h"

/// union3d provides boolean "union" operation for 3d objects
class union3d : public solid {
public:
   // constructors with script array
   union3d(const CScriptArray* arr);
   union3d(const solid* s1, const solid* s2, const solid* s3=0, const solid* s4=0, const solid* s5=0);

   virtual ~union3d();

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

   virtual void populate_tree(node_csg* node) ;

   static union3d* ctor_arr(const CScriptArray* arr) { return new union3d(arr); }
   static union3d* ctor_s2(const solid* s1, const solid* s2                                                   ) { return new union3d(s1,s2);          }
   static union3d* ctor_s3(const solid* s1, const solid* s2, const solid* s3                                  ) { return new union3d(s1,s2,s3);       }
   static union3d* ctor_s4(const solid* s1, const solid* s2, const solid* s3, const solid* s4                 ) { return new union3d(s1,s2,s3,s4);    }
   static union3d* ctor_s5(const solid* s1, const solid* s2, const solid* s3, const solid* s4, const solid* s5) { return new union3d(s1,s2,s3,s4,s5); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      const std::string type_name = as_typeid<union3d>();
      int r = DeclareConstructor(engine,type_name, "union3d@ union3d(array<solid@>@+ arr)",asFUNCTION(union3d::ctor_arr)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "union3d@ union3d(const solid@+ s1, const solid@+ s2 )",asFUNCTION(union3d::ctor_s2)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "union3d@ union3d(const solid@+ s1, const solid@+ s2, const solid@+ s3 )",asFUNCTION(union3d::ctor_s3)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "union3d@ union3d(const solid@+ s1, const solid@+ s2, const solid@+ s3, const solid@+ s4 )",asFUNCTION(union3d::ctor_s4)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "union3d@ union3d(const solid@+ s1, const solid@+ s2, const solid@+ s3, const solid@+ s4, const solid@+ s5 )",asFUNCTION(union3d::ctor_s5)); as_assert( r >= 0 );

   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      solid::DeclareMethods<solid>(engine);
      solid::DeclareMethods<T>(engine);

      const std::string type_name = as_typeid<T>();
    //  int r = 0;
    //  r = DeclareMethod(engine,type_name,"double height() const", asMETHOD(cylinder,height)); as_assert( r >= 0 );
   }


private:
  solid_vector  m_incl;
};

#endif // UNION3D_H
