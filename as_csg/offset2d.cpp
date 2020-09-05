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

#include "offset2d.h"
#include <iostream>
#include "xcsg_vector.h"

void offset2d::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<offset2d>(engine,"2d profile offset");

    // Declare allowed type conversion between csg_sphere(=derived) and shape2d(=base)
   DeclareCast<offset2d,shape2d>(engine);
   DeclareCast<offset2d,shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);

   // Inherit any methods
   offset2d::DeclareMethods<offset2d>(engine);
}

shape2d* offset2d::clone_shape2d() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new offset2d(*this);
}

offset2d::offset2d(const CScriptArray* arr, double r, double delta, bool chamfer)
: shape2d(as_typeid<offset2d>())
, m_incl(arr)
, m_delta(0.0)
, m_round(true)
, m_chamfer(chamfer)
{
   std::pair<double,bool> p = interpret_offset(r,delta);
   m_delta = p.first;
   m_round = p.second;
}

offset2d::offset2d(const shape2d* s1, double r, double delta, bool chamfer)
: shape2d(as_typeid<offset2d>())
, m_delta(0.0)
, m_round(true)
, m_chamfer(chamfer)
{
   std::pair<double,bool> p = interpret_offset(r,delta);
   m_delta = p.first;
   m_round = p.second;

   // push_back will check for zero pointer and clone
   m_incl.push_back(s1);
}


void offset2d::populate_tree(node_csg* node)
{
   node_csg* this_node = new node_csg(this);
   node->push_back(this_node);

   for(size_t i=0;i<m_incl.size(); i++) {
      shape2d* shape2d = m_incl[i];
      if(shape2d)shape2d->populate_tree(this_node);
   }
}

std::pair<double,bool> offset2d::interpret_offset(double r, double delta)
{
   bool NaN_r     = (r==0x7fc00000);
   bool NaN_delta = (delta==0x7fc00000);

   if( ( NaN_r) && ( NaN_delta) ) { throw std::logic_error("offset2d: One of r or delta must be specified"); }
   if( (!NaN_r) && (!NaN_delta))  { throw std::logic_error("offset2d: Cannot specify both r and delta"); }

   return (NaN_delta)? std::make_pair(r,true) : std::make_pair(delta,false);
}

offset2d::~offset2d()
{}

string offset2d::openscad_csg() const
{
   ostringstream out;
   if(m_round) {
      out << setprecision(12) << "offset( r=" << m_delta << ")";
   }
   else {
      out << setprecision(12) << "offset( delta=" << m_delta << ", chamfer="<< ((m_chamfer)? "true":"false") <<")";
   }
   return out.str();
}

spaceio::xml_node offset2d::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   xml_this.add_property("delta",m_delta);
   xml_this.add_property("round",((m_round)? "true" : "false"));
   xml_this.add_property("chamfer",((m_chamfer)? "true" : "false"));
   xcsg_vector<shape2d_vector> vec(m_incl);
   vec.to_xcsg(xml_this);
   return xml_this;
}


bbox3d offset2d::get_box() const
{
   // compute the 2d box
   bbox3d box;
   for(size_t i=0;i<m_incl.size(); i++) {
      const shape2d* body = m_incl[i];
      bbox3d shape_box = body->get_box();
      box.enclose(shape_box.p1());
      box.enclose(shape_box.p2());
   }

   pos3d p1 = box.p1();
   pos3d p2 = box.p2();

   return get_transform()*bbox3d(pos3d(p1.x()-m_delta,p1.y()-m_delta,0),pos3d(p1.x()+m_delta,p1.y()+m_delta,0));
}
