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

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "ce_angelscript_ex/as_reftype.h"
#include "spacemath/bbox3d.h"
class pos3;

/// boundingbox is a utility class
class boundingbox : public as_reftype {
public:
   // constructor
   boundingbox();
   boundingbox(const spacemath::bbox3d& box);
   virtual ~boundingbox();

   void enclose(pos3* p);

   pos3* center() const;
   double dx() const;
   double dy() const;
   double dz() const;
   double diagonal() const;

   pos3* p1() const;
   pos3* p2() const;

   bool is_empty() const { return !m_box.initialised(); }

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

protected:
   /// \privatesection (hidden in documentation)

   static boundingbox* ctor() { return new boundingbox(); }

   // ==== SCRIPTING INTERFACE
   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<boundingbox>(),"boundingbox@ boundingbox()",asFUNCTION(boundingbox::ctor)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      std::string type_name = as_typeid<T>();
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethodsEx(type_name,engine);

      // local methods
      int r = 0;
      r = DeclareMethod(engine,type_name,"void enclose(pos3d@+ p)", asMETHOD(boundingbox,enclose)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos3d@ p1() const", asMETHOD(boundingbox,p1)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos3d@ p2() const", asMETHOD(boundingbox,p2)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos3d@ center() const", asMETHOD(boundingbox,center)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dx() const", asMETHOD(boundingbox,dx)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dy() const", asMETHOD(boundingbox,dy)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double dz() const", asMETHOD(boundingbox,dz)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double diagonal() const", asMETHOD(boundingbox,diagonal)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"bool is_empty() const", asMETHOD(boundingbox,is_empty)); as_assert( r >= 0 );
   }
private:
   spacemath::bbox3d m_box;
};

#endif // BOUNDINGBOX_H
