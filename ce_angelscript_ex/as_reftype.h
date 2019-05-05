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

#ifndef AS_REFTYPE_H
#define AS_REFTYPE_H

#include <string>
#include "ce_angelscript/ce_angelscript.h"
#include "as_typeid.h"
#include "as_assert.h"
#include <set>
#include <map>
using namespace std;

// as_reftype is a base class that simplifies implementation of an AngelScript reference type
// see also http://www.angelcode.com/angelscript/sdk/docs/manual/doc_reg_basicref.html

class as_reftype {
public:
   as_reftype(const std::string type);
   as_reftype(const as_reftype& other);
   virtual ~as_reftype();

   /// \privatesection (hidden in documentation)

   static void InstallType(asIScriptEngine* engine);

   // fundamental Addref/Release used for
   // reference counting & garbage collection
   void Addref();
   void Release();

   // return the concrete type string for the object
   std::string Type() const { return m_type; }

   // return the current refcount
   int Refcount() const { return m_refcount; }

public:
   static void decl_begin() { decl_types.clear(); decl_methods.clear(); decl_constructors.clear(); }
   static void decl_end()   { decl_types.clear(); decl_methods.clear(); }
   static void decl_get_constructors(const std::string& type_name, set<string>& constr);
   static string decl_get_description(const std::string& type_name);

   // Declare the reference scripting class type. This must be called for all levels in the hierarchy
   template <class T> static void DeclareType(asIScriptEngine* engine, const std::string& description="") { DeclareTypeEx(as_typeid<T>(),engine,description); }

   // Use extended version only when C++ classes have other names than script classes
   static void DeclareTypeEx(const std::string& type_name, asIScriptEngine* engine, const std::string& description="");

protected:
   // Declare a scripting constructor. Use asFUNCTION(func) for funcPointer, static T::func is ok
   static int DeclareConstructor(asIScriptEngine* engine, const std::string& type_name, const std::string& declaration, const asSFuncPtr& funcPointer);

   // Declare initalization list construction
   static int DeclareConstructorInitList(asIScriptEngine* engine, const std::string& type_name, const std::string& declaration, const asSFuncPtr& funcPointer);

   // Declare a scripting member function. Use asMETHOD(T,func) for funcPointer.
   // for ordinary member functions, use asCALL_THISCALL, but for operators one must use one of asCALL_CDECL_OBJFIRST, asCALL_CDECL_OBJLAST
   // http://www.gamedev.net/topic/653793-math-conversion-problems/
   static int DeclareMethod(asIScriptEngine* engine, const std::string& type_name, const std::string& declaration, const asSFuncPtr& funcPointer, asDWORD callConv = asCALL_THISCALL);

   // Declare a scripting member property. Use offsetof(T,m_vaue) for byteoffset.
   static int DeclareProperty(asIScriptEngine* engine,  const std::string& type_name, const std::string& declaration, int byteOffset);

   // cast to B from A
   template<class B, class A>
   static B* refCast(A* a)
   {
       // If the handle already is a null handle, then just return the null handle
       if( !a ) return 0;
       // Now try to dynamically cast the pointer to the wanted type
       B* b = dynamic_cast<B*>(a);
       if( b != 0 ) {
           // Since the cast was made, we need to increase the ref counter for the returned handle
           b->Addref();
       }
       return b;
   }

   // Declare possible typecasts between Derived and Base scripting classes
   // ref http://www.angelcode.com/angelscript/sdk/docs/manual/doc_adv_class_hierarchy.html
   template <class Derived, class Base>
   static void DeclareCast(asIScriptEngine* engine)
   {
      std::string type_Derived = as_typeid<Derived>();
      std::string type_Base    = as_typeid<Base>();
      std::string to_Base      = type_Base+"@ opImplCast()";  // implicit cast from derived to base
      std::string to_Derived   = type_Derived+"@ opCast()";   // explicit cast from base to derived

      int r = 0;
      r = DeclareMethod(engine,type_Derived.c_str(), to_Base.c_str(),asFUNCTION((refCast<Base,Derived>)),asCALL_CDECL_OBJLAST); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_Base.c_str(), to_Derived.c_str(),asFUNCTION((refCast<Derived,Base>)),asCALL_CDECL_OBJLAST); as_assert( r >= 0 );
   }


   // Use template version when C++ classes have the same name as script classes
   template <class T> static void DeclareMethods(asIScriptEngine* engine)  { DeclareMethodsEx(as_typeid<T>(),engine);  }

   // Use extended version only when C++ classes have other names than script classes
   static void DeclareMethodsEx(const std::string& type_name, asIScriptEngine* engine);

private:
   static void DeclareRefCount( std::string type_name, asIScriptEngine* engine);

private:
   std::string  m_type;      // most concrete type
   int          m_refcount;  // reference count for this object instance

private:
   static map<string,string>      decl_types;
   static multimap<string,string> decl_constructors;
   static set<string>             decl_methods;
};

#endif // AS_REFTYPE_H
