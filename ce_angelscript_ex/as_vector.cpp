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
   
#include "as_vector.h"
#include "ce_angelscript_ex/as_factory.h"

CScriptArray* CreateScriptArrayEmpty(const std::string& type, size_t len)
{
   // Create the array object with proper length
   asIScriptEngine* engine    = asF()->engine();
   asITypeInfo* arrayType     = engine->GetTypeInfoById(engine->GetTypeIdByDecl(string("array<"+type+">").c_str()));
   CScriptArray* script_array = CScriptArray::Create(arrayType,(asUINT)len);
   script_array->AddRef();
   return script_array;
}
