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
   
#ifndef AS_DOC_TYPE_H
#define AS_DOC_TYPE_H

#include <ostream>
#include <string>
#include <set>
using namespace std;
class as_document;

#include "ce_angelscript/ce_angelscript.h"

class as_doc_type {
   friend class as_document;

public:
   as_doc_type(asITypeInfo* type);
   virtual ~as_doc_type();

   void write_doc(as_document* doc, const string& type_name, ostream& out);

protected:
   // returns true when given type is listed as a base
   bool has_unique_base_type(const string& type);

   // returns true if number of bases < 2
   bool resolve_base(as_document* doc);

private:
   string       m_descr;  // descriptive text of this tyoe
   set<string>  m_base;   // <type_name>    // these are the candidate base types (defined via opImplCast)
   set<string>  m_constr; // <constr_decl>  // constructor declarations
   set<string>  m_func;   // <func_decl>    // member function declarations
};

#endif // AS_DOC_TYPE_H
