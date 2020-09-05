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

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "tmatrix.h"
#include "vec3.h"

/// translate generates a translation transformation
class translate : public tmatrix {
public:
   translate(double dx, double dy, double dz);
   translate(const spacemath::vec3d& v);
   virtual ~translate();

   double dx() const;
   double dy() const;
   double dz() const;

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

protected:
   /// \privatesection (hidden in documentation)


   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static translate* ctor_xyz(double dx, double dy, double dz) { return new translate(dx,dy,dz); }
   static translate* ctor_vec(const vec3* v) { return new translate(v->vec()); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<translate>(),"translate@ translate(double dx, double dy, double dz=0.0)",asFUNCTION(translate::ctor_xyz)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,as_typeid<translate>(),"translate@ translate(const vec3d@+ v)",asFUNCTION(translate::ctor_vec)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      tmatrix::DeclareMethods<tmatrix>(engine);
      tmatrix::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
      int r = 0;
      r = DeclareMethod(engine,type_name,"double dx() const", asMETHOD(translate,dx)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dy() const", asMETHOD(translate,dy)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dz() const", asMETHOD(translate,dz)); as_assert( r >= 0 );
   }
private:
   double m_dx;
   double m_dy;
   double m_dz;
};

#endif // TRANSLATE_H
