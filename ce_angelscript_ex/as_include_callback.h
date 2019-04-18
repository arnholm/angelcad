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

#ifndef AS_INCLUDE_CALLBACK_H
#define AS_INCLUDE_CALLBACK_H
class  CScriptBuilder;
#include <string>

// #include handler callback to support libraries
//   ref https://www.angelcode.com/angelscript/sdk/docs/manual/doc_addon_build.html#doc_addon_build_1_1

int as_include_callback(const char* include, const char* from, CScriptBuilder* builder, void* userParam);

#endif // AS_INCLUDE_CALLBACK_H
