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
   
#ifndef SCALE_H
#define SCALE_H

#include "tmatrix.h"

/// scale generates a scaling transformation
class scale : public tmatrix {
public:
   scale(double sx, double sy, double sz);
   virtual ~scale();

   double sx() const;
   double sy() const;
   double sz() const;

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

protected:
   /// \privatesection (hidden in documentation)


   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static scale* ctor_xyz(double sx, double sy, double sz) { return new scale(sx,sy,sz); }
   static scale* ctor_s(double s) { return new scale(s,s,s); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<scale>(),"scale@ scale(double sx, double sy, double sz=1.0)",asFUNCTION(scale::ctor_xyz)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,as_typeid<scale>(),"scale@ scale(double s)",asFUNCTION(scale::ctor_s)); as_assert( r >= 0 );
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
      r = DeclareMethod(engine,type_name,"double sx() const", asMETHOD(scale,sx)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double sy() const", asMETHOD(scale,sy)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double sz() const", asMETHOD(scale,sz)); as_assert( r >= 0 );
   }
private:
   double m_sx;
   double m_sy;
   double m_sz;
};

#endif // SCALE_H
