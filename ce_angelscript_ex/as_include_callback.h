#ifndef AS_INCLUDE_CALLBACK_H
#define AS_INCLUDE_CALLBACK_H
class  CScriptBuilder;
#include <string>

// #include handler callback to support libraries
//   ref https://www.angelcode.com/angelscript/sdk/docs/manual/doc_addon_build.html#doc_addon_build_1_1

int as_include_callback(const char* include, const char* from, CScriptBuilder* builder, void* userParam);

#endif // AS_INCLUDE_CALLBACK_H
