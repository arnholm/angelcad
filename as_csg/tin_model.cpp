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
   
#include "tin_model.h"
#include <sstream>
#include "ce_angelscript_ex/as_vector.h"
#include "pos3.h"
#include "spacemath/pos3d.h"

void tin_model::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted tin_model type
   DeclareType<tin_model>(engine,"tin_model, vertices in CCW order");

   // Declare allowed type conversion between tin_model(=derived) and solid(=base)
   DeclareCast<tin_model,solid>(engine);
   DeclareCast<tin_model,shape>(engine);

   // Declare the tin_model constructors
   DeclareConstructors(engine);
   // Inherit any methods + declare the unique tin_model methods
   tin_model::DeclareMethods<tin_model>(engine);
}

solid* tin_model::clone_solid() const
{
   return new tin_model(*this);
}

tin_model::tin_model(const CScriptArray* points)
: solid(as_typeid<tin_model>())
{
   as_vector<pos3*> other(points);
   if(other.size() < 3) {
      string message = "tin_model exception: A tin_model must be specified with at least 3 points";
      throw logic_error(message);
   }
   for(size_t i=0; i<other.size(); i++) {
      pos3* pnt = other[i];
      m_vert.push_back(pos3d(pnt->x(),pnt->y(),pnt->z()));
   }
}

tin_model::~tin_model()
{}

size_t tin_model::size() const
{
   return m_vert.size();
}

string tin_model::openscad_csg() const
{
   ostringstream out;
   out << "tin_model( points=[";
   for(size_t i=0; i<m_vert.size(); i++) {
      const pos3d& p = m_vert[i];
      if(i>0) out << ',';
      out << setprecision(12) << '[' << p.x() << ',' << p.y() << ',' << p.z()  << ']';
   }
   out << "] );";
   return out.str();
}

spaceio::xml_node tin_model::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   // vertices
   {
      spaceio::xml_node xml_vertices = xml_this.add_child("vertices");
      for(size_t ivert=0; ivert<m_vert.size(); ivert++) {
         const pos3d& p = m_vert[ivert];
         spaceio::xml_node xml_vertex = xml_vertices.add_child("vertex");
         xml_vertex.add_property("x",p.x());
         xml_vertex.add_property("y",p.y());
         xml_vertex.add_property("z",p.z());
      }
   }
   return xml_this;
}


bbox3d tin_model::get_box() const
{
   bbox3d box;
   for(size_t ivert=0; ivert<m_vert.size(); ivert++) {
      const pos3d& p = m_vert[ivert];
      box.enclose(pos3d(p.x(),p.y(),p.z()));
   }
   return get_transform()*box;
}
