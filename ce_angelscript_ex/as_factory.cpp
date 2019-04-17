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

#include "as_factory.h"
#include "ce_angelscript/add_on/scriptbuilder/scriptbuilder.h"
#include "ce_angelscript/add_on/scripthelper/scripthelper.h"
#include "ce_angelscript/add_on/scriptstdstring/scriptstdstring.h"
#include "ce_angelscript/add_on/scriptarray/scriptarray.h"
#include "ce_angelscript/add_on/scriptdictionary/scriptdictionary.h"
#include "ce_angelscript/add_on/scriptmath/scriptmath.h"
#include "ce_angelscript/add_on/scriptmath/scriptmathcomplex.h"
#include "ce_angelscript/add_on/aatc/aatc.hpp"
#include "ASOStream.h"
#include "ASIStream.h"
#include "ASStreams.h"
#include "as_assert.h"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>

#include <algorithm>
#include "as_include_callback.h"

static const double PI = 4.0*atan(1.0);
static const string endline = "\n";

static void MessageCallback(const asSMessageInfo* msg, void *param)
{
	const char *type = "asERR ";
	if( msg->type == asMSGTYPE_WARNING )
		type = "asWARN";
	else if( msg->type == asMSGTYPE_INFORMATION )
		type = "asINFO";

	printf(" %s: (line %d, col %d) : %-60s : asFILE=%s\n", type, msg->row, msg->col, msg->message, msg->section);
}


static void LineCallback(asIScriptContext *ctx, void *obj)
{
   int icol = 0;
   int iline = ctx->GetLineNumber(0,&icol);
   as_factory::singleton()->SetLineNumber(iline,icol);
}

static void MessageCallbackSilent(const asSMessageInfo* msg, void *param)
{
   // do nothing
}

as_factory* as_factory::m_singleton=0;
as_factory* as_factory::singleton()
{
   if(!m_singleton) {
      m_singleton = new as_factory;
   }
   return m_singleton;
}

void as_factory::ReleaseSingleton()
{
   delete m_singleton;
   m_singleton = 0;
}

as_factory::~as_factory()
{
   m_engine->Release();
   m_singleton = 0;
}

asIScriptEngine* as_factory::engine()
{
   return m_engine;
}

void as_factory::SetLineNumber(int line_number, int col_number)
{
   m_line_number = line_number;
   m_col_number  = col_number;
}

int as_factory::GetLineNumber()
{
   return m_line_number;
}

int  as_factory::GetColNumber()
{
   return m_col_number;
}

static void print_s(const string& str)
{
   printf("%s",str.c_str());
}

static void print_d(double value)
{
   printf("%g",value);
}

static void print_i(int value)
{
   printf("%d",value);
}


static void SetDebugEcho(bool echo)
{
   asF()->SetEchoRef(echo);
}

void as_factory::EchoRef(const string& type, const string& func, void* ptr, long refcount)
{
   string spec = type+"::"+func;
   string pointer = type+"* ";
   cout << "                  EchoRef: " << setw(25) << left << spec << "  " << setw(20) << pointer << ptr <<  "    Ref=" << setw(10) << refcount << " Objects=" << GetInstanceCount(type) << endl;
}

string as_factory::GetInputFullPath()
{
   return singleton()->m_script_path;
}

string as_factory::GetInputFullPathNoExt()
{
   string script_path = singleton()-> m_script_path;

   string out_base = script_path;
   size_t ipos = script_path.find_last_of('.');
   if(ipos != string::npos) {
      out_base = script_path.substr(0,ipos);
   }
   return out_base;
}

string as_factory::GetOutputFullPath(const string& ext)
{
   string outfile = GetInputFullPathNoExt();
   if(outfile.length() == 0) outfile = "ce_angelscript";
   if(ext.length()>0) {
      if('.' == ext[0]) outfile += ext;
      else              outfile += '.'+ext;
   }
   else {
      outfile += ".as_out";
   }
   return outfile;
}

string as_factory::GetOutSubDir()
{
   return singleton()->m_outsubdir;
}


as_factory::as_factory()
: m_echo_ref(false)
, m_line_number(0)
, m_col_number(0)
{
   // Create the script engine
   m_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

   // Set the message callback to receive information on errors in human readable form.
   int r = m_engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); assert( r >= 0 );

   // AngelScript doesn't have a built-in string type, as there is no definite standard
   // string type for C++ applications. Every developer is free to register it's own string type.
   // The SDK do however provide a standard add-on for registering a string type, so it's not
   // necessary to implement the registration yourself if you don't want to.
   RegisterStdString(m_engine);

   // http://www.angelcode.com/angelscript/sdk/docs/manual/doc_addon_array.html
   // The array type is a template object that allow the scripts to declare arrays of any type.
   // Since it is a generic class it is not the most performatic due to the need to determine
   // characteristics at runtime. For that reason it is recommended that the application registers
   // a template specialization for the array types that are most commonly used.
   //
   // Compile the add-on with the pre-processor define AS_USE_STLNAMES=1 to register the methods
   // with the same names as used by C++ STL where the methods have the same significance. Not all
   // methods from STL is implemented in the add-on, but many of the most frequent once are so a port
   // from script to C++ and vice versa might be easier if STL names are used.
   RegisterScriptArray(m_engine,true);

   // dictionary, a <string,"anything"> kind of map
   RegisterScriptDictionary(m_engine);

   // register math types
   RegisterScriptMath(m_engine);
 // Temporarily removed, crashes  RegisterScriptMathComplex(m_engine);

   RegisterStreams(m_engine);
   RegisterIStream(m_engine);
   RegisterOStream(m_engine);

   // register aatc container classes
//   aatc::RegisterAllContainers(m_engine);  // for the complete set

   // we select specific containers only
   aatc::Initializer aatcinit(m_engine);
   aatcinit.include_container[aatc::container::listing::MAP] = 1;
   aatcinit.include_container[aatc::container::listing::UNORDERED_MAP] = 1;
   aatcinit.Go();

   m_engine->RegisterGlobalProperty("const double PI",(void*)(&PI));
   m_engine->RegisterGlobalProperty("const string endl",(void*)(&endline));

   // Register a print function that the scripts may call
   m_engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print_s),      asCALL_CDECL); assert( r >= 0 );
   m_engine->RegisterGlobalFunction("void print(double value)",     asFUNCTION(print_d),      asCALL_CDECL); assert( r >= 0 );
   m_engine->RegisterGlobalFunction("void print(int value)",        asFUNCTION(print_i),      asCALL_CDECL); assert( r >= 0 );
   m_engine->RegisterGlobalFunction("void EchoRef(bool echo)",      asFUNCTION(SetDebugEcho), asCALL_CDECL); assert( r >= 0 );

   m_engine->RegisterGlobalFunction("string GetInputFullPath()",      asFUNCTION(GetInputFullPath), asCALL_CDECL); assert( r >= 0 );
   m_engine->RegisterGlobalFunction("string GetInputFullPathNoExt()", asFUNCTION(GetInputFullPathNoExt), asCALL_CDECL); assert( r >= 0 );
   m_engine->RegisterGlobalFunction("string GetOutputFullPath(const string &in ext)", asFUNCTION(GetOutputFullPath), asCALL_CDECL); assert( r >= 0 );
}

void as_factory::SetLibraryIncludePath(const string& path)
{
   m_library_path = path;
   const char c = m_library_path[m_library_path.length()-1];
   if(c != '/' && c != '\\') m_library_path += '/';

   std::replace(m_library_path.begin(),m_library_path.end(),'\\','/');
}

bool as_factory::RunScriptFile(const string& path, const string& outsubdir, const string& module_name)
{
   m_script_path = ""; // don't assign until successful

   ClearInstanceCount();

   // Set the message callback to receive information on errors in human readable form, in case it was switched off before
   int r = m_engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); assert( r >= 0 );


   // The CScriptBuilder helper is an add-on that loads the file,
   // performs a pre-processing pass if necessary, and then tells
   // the engine to build a script module.
   CScriptBuilder builder;
   if(m_library_path.length() > 0) {
      builder.SetIncludeCallback(as_include_callback,&m_library_path);
   }


   r = builder.StartNewModule(m_engine, module_name.c_str());
   if( r < 0 )
   {
     // If the code fails here it is usually because there
     // is no more memory to allocate the module
     printf(" asERR : Unrecoverable error while starting a new module.\n");
     return false;
   }
   r = builder.AddSectionFromFile(path.c_str());
   if( r < 0 )
   {
     // The builder wasn't able to load the file. Maybe the file
     // has been removed, or the wrong name was given, or some
     // preprocessing commands are incorrectly written.
     printf(" asERR : The builder wasn't able to load the file. Please correct the errors in the script and try again.\n");
     return false;
   }
   r = builder.BuildModule();
   if( r < 0 )
   {
     // An error occurred. Instruct the script writer to fix the
     // compilation errors that were listed in the output stream.
     printf(" asERR : Please correct the errors in the script and try again.\n");
     return false;
   }

   // Find the script function main() that is to be called.
   asIScriptModule*    mod = m_engine->GetModule(module_name.c_str());
   asIScriptFunction* func = mod->GetFunctionByDecl("void main()");
   if(!func)
   {
     // The function couldn't be found. Instruct the script writer
     // to include the expected function in the script.
     printf(" asERR : The script must have the function 'void main()'. Please add it and try again.\n");
     return false;
   }

   // actually run the script
   if(m_echo_ref)  cout << endl << "AngelScript running... " << endl;

   // compilation appears ok
   m_script_path = path;
   m_outsubdir = outsubdir;

   // Create our context, prepare it, and then execute
   asIScriptContext* ctx = m_engine->CreateContext();
   r = ctx->SetLineCallback(asFUNCTION(LineCallback), 0, asCALL_CDECL); assert( r >= 0 );
   ctx->Prepare(func);
   r = ctx->Execute();
   if( r != asEXECUTION_FINISHED )
   {
     // something went wrong, clear the path
     m_script_path = "";

     // The execution didn't complete as expected. Determine what happened.
     if( r == asEXECUTION_EXCEPTION )
     {
       // An exception occurred, let the script writer know what happened so it can be corrected.
       printf(" asERR : An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
     }
   }
   ctx->Release();


   return CheckInstanceCount();

}

void as_factory::ClearInstanceCount()
{
   m_instance_count.clear();
   m_objects.clear();
}

void as_factory::IncrementInstanceCount(const string& class_name)
{
   m_instance_count[class_name]++;
}

void as_factory::DecrementInstanceCount(const string& class_name)
{
   m_instance_count[class_name]--;
}

int as_factory::GetInstanceCount(const string& class_name)
{
   InstanceCountMap::iterator i=m_instance_count.find(class_name);
   if(i != m_instance_count.end()) {
      return i->second;
   }
   return 0;
}

bool as_factory::CheckInstanceCount()
{
   if(m_echo_ref)  cout << endl << "CheckInstanceCount: ";
   int err_count = 0;
   for(InstanceCountMap::iterator i=m_instance_count.begin(); i!=m_instance_count.end(); i++) {
      if(i->second != 0) {
         cout << "Error: memory leak detected for " << i->first << " Remaining object = " << i->second << endl;
         err_count++;
      }
   }

   for(auto i=m_objects.begin(); i!=m_objects.end(); i++) {
      cout << "Orphaned object = " << *i << endl;
   }

   if(err_count==0) {
      if(m_echo_ref)  cout << "OK :-)" << endl;

      // Set the message callback to NOT receive further information on errors
      int r = m_engine->SetMessageCallback(asFUNCTION(MessageCallbackSilent), 0, asCALL_CDECL); assert( r >= 0 );

      return true;
   }

   return false;
}

void as_factory::ObjectConstructed(void* object)
{
   m_objects.insert(object);
}

void as_factory::ObjectDestructed(void* object)
{
   m_objects.erase(object);
}
