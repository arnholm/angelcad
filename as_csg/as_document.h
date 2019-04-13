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
   
#ifndef AS_DOCUMENT_H
#define AS_DOCUMENT_H

#include "as_doc_type.h"
#include "as_doc_type_doxy.h"
#include "ce_angelscript/ce_angelscript.h"
#include <ostream>
#include <map>

class as_document {
   friend class as_doc_type;

public:
   as_document(asIScriptEngine* engine);
   virtual ~as_document();

   void read_doxy(const string& path);
   void write_doc(ostream& out);

   as_doc_type_doxy* get_doxy(const string& type_name);

protected:
   as_doc_type* get_type(const string& type_name);
   void document_types(asIScriptEngine* engine);

   void resolve_base_types();

private:

   map<string,as_doc_type> m_types;
   map<string,as_doc_type_doxy> m_types_doxy;  // doxygen style documentation on member functions
};

#endif // AS_DOCUMENT_H
