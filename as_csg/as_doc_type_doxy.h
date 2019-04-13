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
   
#ifndef AS_DOC_TYPE_DOXY_H
#define AS_DOC_TYPE_DOXY_H

#include <ostream>
#include <string>
#include <map>
#include <list>
using namespace std;

// helper class to contain & write doxygen style documentation for a script class
class as_doc_type_doxy {
public:
   as_doc_type_doxy();
   virtual ~as_doc_type_doxy();

   void insert_classdoc(const list<string>& doxy);
   bool write_classdoc(ostream& out);

   void insert_doc(const string& sig, const list<string>& doxy);
   bool write_doc(const string& sig, ostream& out);

protected:

private:
   list<string>              m_classdoc;    // documentation for the whole class
   map<string,list<string>>  m_func_doxy;   // <signature,doxy_text>
};

#endif // AS_DOC_TYPE_DOXY_H
