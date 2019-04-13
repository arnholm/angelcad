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
   
#include "polyhedron_face.h"
#include "ce_angelscript_ex/as_vector.h"
#include <set>

void polyhedron_face::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted polyhedron_face type
   DeclareTypeEx("pface",engine,"Polyhedron face");

   // Declare the polyhedron_face constructors
   DeclareConstructors(engine);

   // Inherit any methods + declare the unique polyhedron_face methods
   polyhedron_face::DeclareMethods<polyhedron_face>(engine);
}

as_reftype* polyhedron_face::clone_scoped()
{
   return new polyhedron_face(*this);
}

static void check_insert(int node, std::set<int>& unique_nodes, vector<size_t>& m_nodes)
{
   if(node > -1) {
      if(unique_nodes.find(node) != unique_nodes.end()) {
         string message = "polyhedron_face exception: vertex index "+ std::to_string(node) + " was repeated in a face, indices must be unique." ;
         throw logic_error(message);
      }
      unique_nodes.insert(node);
      m_nodes.push_back((size_t)node);
   }
}

polyhedron_face::polyhedron_face(const CScriptArray* nodes)
: as_reftype(as_typeid<polyhedron_face>())
{
   std::set<int> unique_nodes;
   as_vector<int> other(nodes);
   for(size_t i=0; i<other.size(); i++) {
      int node = other[i];
      check_insert(node,unique_nodes,m_nodes);
   }
   if(m_nodes.size() < 3) {
      string message = "polyhedron_face exception: A polyhedron_face must be specified with at least 3 vertex indices different from -1";
      throw logic_error(message);
   }
}

polyhedron_face::polyhedron_face(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9)
: as_reftype(as_typeid<polyhedron_face>())
{
   std::set<int> unique_nodes;
   check_insert(n1,unique_nodes,m_nodes);
   check_insert(n2,unique_nodes,m_nodes);
   check_insert(n3,unique_nodes,m_nodes);
   check_insert(n4,unique_nodes,m_nodes);
   check_insert(n5,unique_nodes,m_nodes);
   check_insert(n6,unique_nodes,m_nodes);
   check_insert(n7,unique_nodes,m_nodes);
   check_insert(n8,unique_nodes,m_nodes);
   check_insert(n9,unique_nodes,m_nodes);
   if(m_nodes.size() < 3) {
      string message = "polyhedron_face exception: A polyhedron_face must be specified with at least 3 vertex indices  different from -1";
      throw logic_error(message);
   }
}

polyhedron_face::polyhedron_face(const vector<size_t>& face)
: as_reftype(as_typeid<polyhedron_face>())
, m_nodes(face)
{}

polyhedron_face::~polyhedron_face()
{}

const vector<size_t>& polyhedron_face::nodes() const
{
	return m_nodes;
}

size_t polyhedron_face::nvert() const
{
   return m_nodes.size();
}


size_t polyhedron_face::vindex(size_t iv) const
{
   return m_nodes[iv];
}
