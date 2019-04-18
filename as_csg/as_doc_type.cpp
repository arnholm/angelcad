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

#include "as_doc_type.h"
#include "as_document.h"
#include "ce_angelscript_ex/as_reftype.h"
#include <iostream>

static set<string> func_filter = {  "opImplCast", "opCast", "Refcount" };
static set<string> func_decl_filter = { "shape2d@ opMul(tmatrix@)", "solid@ opMul(tmatrix@)" };

as_doc_type::as_doc_type(asITypeInfo* type)
{
   // constructors

   // our types are mostly as_reftype....
   as_reftype::decl_get_constructors(type->GetName(),m_constr);
   m_descr = as_reftype::decl_get_description(type->GetName());

   // but if not...fall back to native recovery of constructor declarations if above did not return anything
   if(m_constr.size() == 0) {
      asUINT ncons = type->GetFactoryCount();
      for(asUINT icons=0; icons<ncons; icons++) {
        if(asIScriptFunction* func = type->GetFactoryByIndex(icons)) {
           string func_name = func->GetName();
           if(func_filter.find(func_name) == func_filter.end()) {
              bool includeObjectName=false;
              bool includeNamespace=false;
              bool includeParamNames=true;

              // get the full declaration with parameter names
              // Unfortunately, it looks like "includeParamNames" has no effect on constructor parameter names
              string func_decl = func->GetDeclaration(includeObjectName,includeNamespace,includeParamNames);
              m_constr.insert(func_decl);
           }
        }
      }
   }

   // methods
   asUINT nfunc = type->GetMethodCount();
   for(asUINT ifunc=0; ifunc<nfunc; ifunc++) {
     if(asIScriptFunction* func = type->GetMethodByIndex(ifunc)) {
        string func_name = func->GetName();

        // If we can implicitly cast to a type, we understand as a base class, either directly or indirectly.
        // We save all the candidates hare for resolution later
        if("opImplCast" == func_name) {
           string func_decl = func->GetDeclaration(false);
           size_t ipos = func_decl.find_first_of('@');
           if(ipos != string::npos) {
              string base_type =  func_decl.substr(0,ipos);
              m_base.insert(base_type);
           }
        }

        if(func_filter.find(func_name) == func_filter.end()) {
           string func_decl = func->GetDeclaration(false);

           if(func_decl_filter.find(func_decl) == func_decl_filter.end()) {
              bool includeObjectName=false;
              bool includeNamespace=false;
              bool includeParamNames=true;

              // get the full declaration with parameter names
              func_decl = func->GetDeclaration(includeObjectName,includeNamespace,includeParamNames);
              m_func.insert(func_decl);
           }
        }
     }
   }
}

bool as_doc_type::has_unique_base_type(const string& type)
{
   return ((m_base.size()==1) && (m_base.find(type) != m_base.end()) );
}

bool as_doc_type::resolve_base(as_document* doc)
{
   for(auto i=m_base.begin(); i!=m_base.end(); i++) {
      const string& base_type = *i;

      if(as_doc_type* base_candidate = doc->get_type(base_type)) {

         for(auto j=m_base.begin(); j!=m_base.end(); j++) {
            const string& base_type_other = *j;
            if(base_candidate->has_unique_base_type(base_type_other)) {
               m_base.erase(j);
               j=m_base.begin();
            }
         }
      }
   }

   return (m_base.size() < 2);
}

as_doc_type::~as_doc_type()
{
   //dtor
}


void as_doc_type::write_doc(as_document* doc, const string& type_name, ostream& out)
{
   as_doc_type_doxy* doxy = doc->get_doxy(type_name);
   if(!doxy) {
      cout << "** Missing doxy info for class " << type_name << endl;
   }

   if(m_descr.length() > 0) {
      out << endl << "/// " << m_descr;
   }
   out << endl;
   if(doxy) doxy->write_classdoc(out);
   out << "class " << type_name;
   for(auto i=m_base.begin(); i!=m_base.end(); i++) {
      out << " : public " << *i;
   }
   out << endl <<"{ " << endl;
   out << "public: " << endl;
   if(m_constr.size() > 0) {
    //  if(m_constr.size() == 1) out << "   // constructor " << endl;
    //  else out << "   // constructors " << endl;
      for(auto i=m_constr.begin(); i!=m_constr.end(); i++) {
         if(doxy)doxy->write_doc(*i,out);
         else cout << "**   " <<type_name<<"::"<<*i<< endl;
         out << "   " << *i << ';' << endl;
      }
   }

   if(m_func.size() > 0) {
      if(m_constr.size() > 0) out << endl;
    //  if(m_func.size() == 1) out << "   // method " << endl;
    //  else out << "   // methods " << endl;
      for(auto i=m_func.begin(); i!=m_func.end(); i++) {
         string sig = *i;
         bool op_boolean = (sig.find("opAdd")!=string::npos) || (sig.find("opSub")!=string::npos) || (sig.find("opAnd")!=string::npos)
                        || (sig.find("write_csg")!=string::npos) || (sig.find("write_xcsg")!=string::npos) ;
         bool skip = (op_boolean &&  ((type_name!="shape") && (type_name!="solid") && (type_name!="shape2d")
                                      && (type_name!="pos2d") && (type_name!="vec2d") && (type_name!="pos3d") && (type_name!="vec3d")
                                     )
                      );
         if(!skip) {
            if(doxy)doxy->write_doc(sig,out);
            else cout << "**   " <<type_name<<"::"<<*i<< endl;
            out << "   " << sig << ';' << endl;
         }
      }
   }
   out << "}; " << endl;
}
