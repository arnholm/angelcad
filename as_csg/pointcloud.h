// BeginLicense:
// Part of: angelcad - script based 3D solid modeller
// Copyright (C) 2017-2020 Carsten Arnholm
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

#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "ce_angelscript_ex/as_reftype.h"
#include "spacemath/pos3d.h"
#include "spacemath/bbox3d.h"
class pos3;
#include <vector>
using namespace std;
class CScriptArray;

using spacemath::pos3d;
using spacemath::bbox3d;

/// pointcloud represents a 3d pointcloud, possibly imported from file
class pointcloud : public as_reftype {
public:
    // scripting interface
   pointcloud(const CScriptArray* points);
   pointcloud(const string& file, int skip_lines, int xtok, int ytok, int ztok, const string& delimiters);
   virtual ~pointcloud();

   // return number of points in point cloud
   size_t size() const;

   // return points as array<pos3d@>
   CScriptArray* points_array() const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

   // return bounding box
   virtual bbox3d get_box() const;

protected:
   CScriptArray* create_array(const vector<pos3d>& pos);

   /// \privatesection (hidden in documentation)

   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static pointcloud* ctor_arr(const CScriptArray* points) { return new pointcloud(points); }
   static pointcloud* ctor_file1(const string& file, int skip_lines, int xtok, int ytok, int ztok, const string& delimiters) { return new pointcloud(file,skip_lines,xtok,ytok,ztok,delimiters); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      std::string type_name = as_typeid<pointcloud>();
      int r = 0;
      r = DeclareConstructor(engine,type_name, "pointcloud@ pointcloud(array<pos3d@>@+ points)",asFUNCTION(pointcloud::ctor_arr)); as_assert( r >= 0 );
      r = DeclareConstructor(engine,type_name, "pointcloud@ pointcloud(string file,int skip_lines=0,int xtok=0, int ytok=1, int ztok=2, string delimiters=' ,;\t\r')",asFUNCTION(pointcloud::ctor_file1)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      as_reftype::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
      int r = 0;
      r = DeclareMethod(engine,type_name,"uint size() const", asMETHOD(pointcloud,size)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"array<pos3d@>@ points_array() const", asMETHOD(pointcloud,points_array)); as_assert( r >= 0 );
   }

private:
   // by owning the script array here, we avoid orphaned objects
   CScriptArray* m_arr;  // array<pos3d@>
};

#endif // SQUARE_H
