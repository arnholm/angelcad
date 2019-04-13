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
   
#include "spline_path.h"
#include "ce_angelscript_ex/as_vector.h"
#include <vector>


void spline_path::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted spline_path type
   DeclareType<spline_path>(engine,"spline_path for sweep");

   // Declare the spline_path constructors
   DeclareConstructors(engine);

   // Inherit any methods from in this class + declare the unique spline_path methods
   spline_path::DeclareMethods<spline_path>(engine);
}

spline_path::spline_path(const CScriptArray* p, const CScriptArray* v)
: as_reftype(as_typeid<spline_path>())
{
   as_vector<pos3*>  points(p);
   as_vector<vec3*>    vectors(v);

   m_p.reserve(points.size());
   m_v.reserve(vectors.size());

   for(size_t ip=0;ip<points.size();ip++) {
      pos3* pos = points[ip];
      m_p.push_back(*pos);
   }

   for(size_t iv=0;iv<vectors.size();iv++) {
      vec3* vec = vectors[iv];
      m_v.push_back(*vec);
   }

   if(m_p.size() != m_v.size()) {
      string message = "spline_path: Number of points and vectors must be the same when usiing arrays.";
      throw logic_error(message);
   }
}

spline_path::spline_path(const CScriptArray* p, const vec3* v)
: as_reftype(as_typeid<spline_path>())
{
   as_vector<pos3*>  points(p);
   m_p.reserve(points.size());
   m_v.reserve(points.size());

   for(size_t ip=0;ip<points.size();ip++) {
      pos3* pos = points[ip];
      m_p.push_back(*pos);
      m_v.push_back(*v);
   }

}

spline_path::~spline_path()
{}


