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
   
#include "as_reftype.h"
#include "as_factory.h"

map<string,string>      as_reftype::decl_types;
multimap<string,string> as_reftype::decl_constructors;
set<string>             as_reftype::decl_methods;

void as_reftype::DeclareTypeEx(const std::string& type_name, asIScriptEngine* engine, const std::string& description)
{
   if(decl_types.find(type_name) != decl_types.end()) return;
   int r = engine->RegisterObjectType(type_name.c_str(), 0, asOBJ_REF); as_assert( r >= 0 );
   DeclareRefCount(type_name,engine);
   decl_types.insert(make_pair(type_name,description));
}

int as_reftype::DeclareConstructor(asIScriptEngine* engine, const std::string& type_name, const std::string& declaration, const asSFuncPtr& funcPointer)
{
   decl_constructors.insert(make_pair(type_name,declaration));
   return engine->RegisterObjectBehaviour(type_name.c_str(), asBEHAVE_FACTORY, declaration.c_str(),funcPointer, asCALL_CDECL);
}

void as_reftype::DeclareMethodsEx(const std::string& type_name, asIScriptEngine* engine)
{
   int r = 0;
   r = DeclareMethod(engine,type_name,"string Type() const", asMETHOD(as_reftype,Type));    as_assert( r >= 0 );
   r = DeclareMethod(engine,type_name,"int Refcount() const",       asMETHOD(as_reftype,Refcount)); as_assert( r >= 0 );
}


int as_reftype::DeclareMethod(asIScriptEngine* engine, const std::string& type_name, const std::string& declaration, const asSFuncPtr& funcPointer, asDWORD callConv)
{
   string sig = type_name +"::"+declaration;
   if(decl_methods.find(sig) != decl_methods.end()) {
      return 0;
   }
   decl_methods.insert(sig);
   return engine->RegisterObjectMethod(type_name.c_str(),declaration.c_str(),funcPointer, callConv);
}

int as_reftype::DeclareProperty(asIScriptEngine* engine,  const std::string& type_name, const std::string& declaration, int byteOffset)
{
   return engine->RegisterObjectProperty(type_name.c_str(), declaration.c_str(), byteOffset);
}

// Declare the class refcount behaviour. This must be called for all levels in the hierarchy
// Notice that all Addref()/Release() calls maps to the as_reftype implementation for all derived types!!
void as_reftype::DeclareRefCount( std::string type_name, asIScriptEngine* engine)
{
   // Register the addref/release behaviours
   int r = 0;
   r = engine->RegisterObjectBehaviour(type_name.c_str(), asBEHAVE_ADDREF,  "void Addref()",  asMETHOD(as_reftype,Addref),  asCALL_THISCALL); as_assert( r >= 0 );
   r = engine->RegisterObjectBehaviour(type_name.c_str(), asBEHAVE_RELEASE, "void Release()", asMETHOD(as_reftype,Release), asCALL_THISCALL); as_assert( r >= 0 );
}

void as_reftype::InstallType(asIScriptEngine* engine)
{
   DeclareType<as_reftype>(engine);
}

as_reftype::as_reftype(const as_reftype& other)
: m_type(other.m_type)
, m_refcount(0)
{
   as_factory* factory = asF();
   factory->IncrementInstanceCount(m_type);
   factory->ObjectConstructed(this);
   if(factory->GetEchoRef()) factory->EchoRef(m_type,"ctor_c",this,m_refcount);
   Addref();
}


as_reftype::as_reftype(const std::string type)
: m_type(type)
, m_refcount(0)
{
   as_factory* factory = asF();
   factory->IncrementInstanceCount(m_type);
   factory->ObjectConstructed(this);
   if(factory->GetEchoRef()) factory->EchoRef(m_type,"ctor",this,m_refcount);
   Addref();
}

as_reftype::~as_reftype()
{
   as_factory* factory = asF();
   factory->DecrementInstanceCount(m_type);
   factory->ObjectDestructed(this);
   if(factory->GetEchoRef()) factory->EchoRef(m_type,"~dtor",this,m_refcount);
}


void as_reftype::Addref()
{
   // Increase the reference counter
   m_refcount++;
   as_factory* factory = asF();
   if(factory->GetEchoRef()) factory->EchoRef(m_type,"Addref",this,m_refcount);
}

void as_reftype::Release()
{
   as_factory* factory = asF();
   // Decrease ref count and delete if it reaches 0
   if(m_refcount > 0) {
      if(--m_refcount==0) {
         if(factory->GetEchoRef()) factory->EchoRef(m_type,"Release",this,0);
         delete this;
         return;
      }
      else if(factory->GetEchoRef()) factory->EchoRef(m_type,"Release",this,m_refcount);
   }
  // if(factory->GetEchoRef()) factory->EchoRef("<naked>","Release",this,m_refcount);
}


void as_reftype::decl_get_constructors(const std::string& type_name, set<string>& constr)
{
   auto it_pair = decl_constructors.equal_range(type_name);
   for(auto it=it_pair.first; it!=it_pair.second; it++) {
      string decl = it->second;
      size_t space = decl.find(' ')+1;
      decl = decl.substr(space);
      size_t pls = decl.find('+');
      while(pls != string::npos) {
         decl.replace(pls,1,"");
         pls = decl.find('+');
      }

      constr.insert(decl);
   }
}

string as_reftype::decl_get_description(const std::string& type_name)
{
   auto i = decl_types.find(type_name);
   if(i == decl_types.end())return "";
   return i->second;
}
