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
   
#include "as_doc_type_doxy.h"

as_doc_type_doxy::as_doc_type_doxy()
{
   //ctor
}

as_doc_type_doxy::~as_doc_type_doxy()
{
   //dtor
}

void as_doc_type_doxy::insert_doc(const string& sig, const list<string>& doxy)
{
   m_func_doxy[sig] = doxy;
}

void as_doc_type_doxy::insert_classdoc(const list<string>& doxy)
{
   m_classdoc = doxy;
}

bool  as_doc_type_doxy::write_classdoc(ostream& out)
{
   for(auto& s : m_classdoc) {
      out << s << endl;
   }
   return true;
}

bool as_doc_type_doxy::write_doc(const string& sig, ostream& out)
{
   auto i = m_func_doxy.find(sig);
   if(i != m_func_doxy.end()) {
      const list<string>& doxy = i->second;
      for(auto& line : doxy) {
         out << "   " << line << endl;
      }
      return true;
   }
   return false;
}
