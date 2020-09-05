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

#ifndef NODE_CSG_H
#define NODE_CSG_H

#include "spacemath/HTmatrix.h"
class shape;
#include <vector>
#include <ostream>
#include <sstream>
#include <iomanip>
using namespace std;

using spacemath::HTmatrix;

/// node_csg is for internal use only
class node_csg {
public:

   /// \privatesection (hidden in documentation)

   node_csg(const shape* node_csg, bool enclose_children = true);
   virtual ~node_csg();

   void push_back(node_csg* child_node);

   // write openscad data for this node_csg
   void write_csg(ostream& out, int indent=0);

private:

   // return transformation as an openscad multmatrix string
   static string multmatrix(const HTmatrix& matrix);

   // write shape data
   void write_shape(ostream& out, int indent);

private:
   const shape*      m_node_csg;
   bool              m_enclose_children;  // true if children to be enclosed in parentheses
   vector<node_csg*> m_children;
};

#endif // NODE_H
