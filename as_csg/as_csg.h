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

#ifndef AS_CSG_H
#define AS_CSG_H

#include <string>
#include <list>
using namespace std;

#include "ce_angelscript_ex/as_factory.h"

// as_csg is the manager of the AngelCAD script engine
class as_csg {
public:
   typedef list<string> MessageList;
   typedef MessageList::const_iterator const_iterator;

   as_csg();
   virtual ~as_csg();

   // register the types supported by as_csg
   bool register_types();

   // run_script returns the number of error/warning messages in the message list
   size_t run_script(const string& input_file, const string& include_path, const string& outdir);

   const_iterator message_begin() const { return m_message_list.begin(); }
   const_iterator message_end() const   { return m_message_list.end(); }

private:
   MessageList m_message_list;
};

#endif // AS_H
