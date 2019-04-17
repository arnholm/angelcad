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

#ifndef as_factory_H
#define as_factory_H

#include "ce_angelscript/ce_angelscript.h"
#include <string>
#include <map>
#include <set>
using namespace std;

class as_factory {
public:
   typedef map<string,int> InstanceCountMap;
   typedef set<void*>      ObjectSet;

   // factory management
   static as_factory* singleton();
   static void        ReleaseSingleton();

   // access to script engine
   asIScriptEngine*  engine();

   // set the path to the root library folder, set empty path if no library folder to be used
   void SetLibraryIncludePath(const string& path);

   // Load and run a complete script from file. Call in try/catch block
   bool RunScriptFile(const string& path, const string& outsubdir, const string& module_name);

public:
   void ClearInstanceCount();
   void IncrementInstanceCount(const string& class_name);
   void DecrementInstanceCount(const string& class_name);
   int  GetInstanceCount(const string& class_name);
   bool CheckInstanceCount();

   void ObjectConstructed(void* object);
   void ObjectDestructed(void* object);

   int  GetLineNumber();
   int  GetColNumber();
   void SetLineNumber(int line_number, int col_number);

   // Echoref controls debug report tracking flag for reference counting
   inline void SetEchoRef(bool echo_ref) { m_echo_ref = echo_ref; }
   inline bool GetEchoRef()              { return m_echo_ref;     }
   void EchoRef(const string& type, const string& func, void* ptr, long refcount);

   static string GetInputFullPath();                   // returns the full file path of the input script
   static string GetInputFullPathNoExt();              // returns the full file path of the input script, without the file extension
   static string GetOutputFullPath(const string& ext); // returns the full file path of the output file with given extension
   static string GetOutSubDir();                       // returns output subdirectory specification

private:
   as_factory();
   virtual ~as_factory();

   string             m_library_path; // path to library folder or empty string of none
   string             m_script_path;  // path to current script file
   string             m_outsubdir;    // path to script output subdirectory (may be empty)

   InstanceCountMap   m_instance_count;
   bool               m_echo_ref;
   ObjectSet          m_objects;  // anything in this set is constructed but not destructed

   asIScriptEngine*   m_engine;
   int                m_line_number;  // line number from LineCallback
   int                m_col_number;   // column number from LineCallback
private:
   static as_factory*  m_singleton;
};

inline as_factory* asF() { return as_factory::singleton(); }

#endif // as_factory_H
