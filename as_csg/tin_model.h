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
   
#ifndef tin_model_H
#define tin_model_H

#include "solid.h"
#include "spacemath/pos3d.h"
class pos3;
#include <vector>
using namespace std;
class CScriptArray;

using spacemath::pos3d;

/// tin_model generates a 3d tin_model (Triangulated Irregular network)
class tin_model : public solid {
public:
    // scripting interface
   tin_model(const CScriptArray* points);
   virtual ~tin_model();

   size_t size() const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
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
   static tin_model* ctor_arr(const CScriptArray* points) { return new tin_model(points); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      std::string type_name = as_typeid<tin_model>();
      int r = DeclareConstructor(engine,type_name, "tin_model@ tin_model(array<pos3d@>@+ points)",asFUNCTION(tin_model::ctor_arr)); as_assert( r >= 0 );
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
      int r = 0;
      r = DeclareMethod(engine,type_name,"uint size() const", asMETHOD(tin_model,size)); as_assert( r >= 0 );
   }

private:
   vector<pos3d> m_vert;
};

#endif // SQUARE_H
