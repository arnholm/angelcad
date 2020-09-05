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

#include "node_csg.h"
#include "shape.h"
#include <sstream>
#include <iostream>

node_csg::node_csg(const shape* node_csg, bool enclose_children)
: m_node_csg(node_csg)
, m_enclose_children(enclose_children)
{}

node_csg::~node_csg()
{
   for(auto i=m_children.begin(); i!=m_children.end(); i++) {
      node_csg* child_node_csg = *i;
      delete child_node_csg;
   }
}

void node_csg::push_back(node_csg* child_node)
{
   m_children.push_back(child_node);
}

void node_csg::write_csg(ostream& out, int indent)
{
//   cout << "node_csg::write_csg " << m_node_csg << endl;

   // compute the tab indent for this level
   string tabs;
   for(int i=0;i<indent; i++)tabs+= '\t';

   if(m_node_csg) {
      // write shape with transformation
      out << tabs << multmatrix(m_node_csg->get_transform()) << " {" << endl;
      write_shape(out,indent+1);
      out << tabs << '}'  << endl;
   }
   else {
      // skip transformation when there is no node_csg
      write_shape(out,indent);
   }
}

void node_csg::write_shape(ostream& out, int indent)
{
   string type = "group()";
   if(m_node_csg) {
      type =  m_node_csg->openscad_csg();
   }

   // write this node_csg
   string tabs;
   for(int i=0;i<indent; i++)tabs+= '\t';
   out << tabs << type;

   if(m_children.size() > 0) {

      // write child node_csgs
      if(m_enclose_children) out << " {";
      out << endl;
      for(auto i=m_children.begin(); i!=m_children.end(); i++) {
         node_csg* child_node_csg = *i;
         if(m_enclose_children)child_node_csg->write_csg(out,indent+1);
         else                  child_node_csg->write_csg(out,indent);
      }
      if(m_enclose_children)out << tabs << '}'  << endl;
   }
   else {
      out << endl;
   }
}


string node_csg::multmatrix(const HTmatrix& matrix)
{
   ostringstream out;

   out << "multmatrix([";

   for(size_t irow=0;irow<4; irow++) {
      if(irow > 0) out << ',';
      out << '[';
      for(size_t icol=0;icol<4; icol++) {
         if(icol > 0) out << ',';
         out << setprecision(12) << matrix(irow,icol);
      }
      out << ']';
   }

   out << "])";

   return out.str();
}
