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

#include "polyhedron.h"
#include "ce_angelscript_ex/as_vector.h"
#include <wx/filename.h>

#include <vector>
#include <fstream>
#include <sstream>

#include "spaceio/amf_io.h"
#include "spaceio/obj_io.h"
#include "spaceio/off_io.h"

void polyhedron::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted polyhedron type
   DeclareType<polyhedron>(engine,"Closed polyhedron volume defined by vertices and planar faces");

    // Declare allowed type conversion between polyhedron(=derived) and solid(=base)
   DeclareCast<polyhedron,solid>(engine);
   DeclareCast<polyhedron,shape>(engine);

   // Declare the polyhedron constructors
   DeclareConstructors(engine);

   // Inherit any methods from in this class + declare the unique polyhedron methods
   polyhedron::DeclareMethods<polyhedron>(engine);
}

solid* polyhedron::clone_solid() const
{
   return new polyhedron(*this);
}


polyhedron::polyhedron(const CScriptArray* points)
: solid(as_typeid<polyhedron>())
{
   as_vector<pos3*>       vertices(points);

   vtx_vec   vert;    vert.reserve(vertices.size());
   for(size_t ivert=0;ivert<vertices.size();ivert++) {
      pos3* pos = vertices[ivert];
      vert.push_back(*pos);
   }

   m_poly = std::make_shared<spacemath::polyhedron3d>(spacemath::polyhedron3d(vert));
}

polyhedron::polyhedron(const CScriptArray* points, const CScriptArray* faces)
: solid(as_typeid<polyhedron>())
{
   as_vector<pos3*>       vertices(points);
   as_vector<polyhedron_face*>  polyhedron_faces(faces);

   vtx_vec   vert;    vert.reserve(vertices.size());
   pface_vec pfaces;  pfaces.reserve(polyhedron_faces.size());

   for(size_t ivert=0;ivert<vertices.size();ivert++) {
      pos3* pos = vertices[ivert];
      if(!pos) {
         string message = "polyhedron exception: NULL element detected in polyhedron points, index=" + std::to_string(ivert);
         throw logic_error(message);
      }
      vert.push_back(*pos);
   }

   for(size_t iface=0;iface<polyhedron_faces.size();iface++) {
      polyhedron_face* face = polyhedron_faces[iface];
      if(!face) {
         string message = "polyhedron exception: NULL element detected in polyhedron faces, index=" + std::to_string(iface);
         throw logic_error(message);
      }
      pfaces.push_back(face->nodes());
   }

   m_poly = std::make_shared<spacemath::polyhedron3d>(spacemath::polyhedron3d(vert,pfaces));
}

polyhedron::polyhedron(const string& file, int id)
: solid(as_typeid<polyhedron>())
{
   wxFileName fname(file);

   wxString ext = fname.GetExt();
   ext.MakeLower();

   if( (ext!="amf") && (ext!="obj") && (ext!="off") ) {
      string message = "polyhedron exception: The file type '"+fname.GetExt().ToStdString()+"' is not supported. Supported: amf/obj/off ";
      throw logic_error(message);
   }

   if(!fname.Exists()) {
      string message = "polyhedron exception: The file does not exist: " + file;
      throw logic_error(message);
   }

   std::shared_ptr<ph3d_vector> polyset;
   if(ext == "amf") {
      polyset = spaceio::amf_io::read(file);
      if(id == -1) {
         // just put all lumps together
         m_poly = spaceio::amf_io::merge_lumps(polyset);
      }
      else {
         if(id >= (int)polyset->size())  throw logic_error("amf id index higher than number of polyhedrons returned");
         m_poly = (*polyset)[id];
      }
   }
   else if (ext == "obj") {
      polyset = spaceio::obj_io::read(file);
      m_poly = (*polyset)[0];
   }
   else if (ext == "off") {
      polyset = spaceio::off_io::read(file);
      m_poly = (*polyset)[0];
   }
}

polyhedron::polyhedron()
: solid(as_typeid<polyhedron>())
{}

polyhedron::~polyhedron()
{}


string polyhedron::openscad_csg() const
{
   ostringstream out;

   size_t nvert = m_poly->vertex_size();
   size_t nface = m_poly->face_size();

   out << "polyhedron( "; // << endl;
   out << "points=[ ";
      for(size_t ivert=0; ivert<nvert; ivert++) {
         const pos3d& pos = m_poly->vertex(ivert);
         if(ivert > 0) out << ',';
         out << '[' << setprecision(12) << pos.x() << ',' << setprecision(12) << pos.y() << ',' << setprecision(12) << pos.z() << ']';
      }
   out << " ], ";// << endl;
   out << "faces=[ ";
      for(size_t iface=0; iface<nface; iface++) {
         const pface& face = m_poly->face(iface);
         size_t nv = face.size();
         if(iface > 0) out << ',';
         out << '[';
         for(size_t iv=0; iv<nv; iv++) {
            if(iv>0) out<<',';
            out << face[iv];
         }
         out << ']';
      }
   out << " ] "; // << endl;
   out << " );";

   return out.str();
}


spaceio::xml_node polyhedron::to_xcsg(spaceio::xml_node& xml_parent)
{
   size_t nvert = m_poly->vertex_size();
   size_t nface = m_poly->face_size();

   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);;

   // vertices
   {
      spaceio::xml_node xml_vertices = xml_this.add_child("vertices");
      for(size_t ivert=0; ivert<nvert; ivert++) {
         const pos3d& pos = m_poly->vertex(ivert);
         spaceio::xml_node xml_vertex = xml_vertices.add_child("vertex");
         xml_vertex.add_property("x",pos.x());
         xml_vertex.add_property("y",pos.y());
         xml_vertex.add_property("z",pos.z());
      }
   }

   // faces
   if(nface > 0) {
      spaceio::xml_node xml_faces    = xml_this.add_child("faces");
      for(size_t iface=0; iface<nface; iface++) {

         const pface& face = m_poly->face(iface);
         size_t nv = face.size();
         spaceio::xml_node xml_face = xml_faces.add_child("face");
         for(size_t ifv=0; ifv<nv; ifv++) {
            spaceio::xml_node xml_fv   = xml_face.add_child("fv");
            xml_fv.add_property("index",face[ifv]);
         }
      }
   }

   return xml_this;
}


size_t polyhedron::nvert() const
{
   return m_poly->vertex_size();
}

size_t polyhedron::nface() const
{
    return m_poly->face_size();
}

pos3* polyhedron::vertex(size_t iv) const
{
   if(iv >= m_poly->vertex_size()) throw std::logic_error("Vertex index out of range: " + std::to_string(iv));
   return new pos3(m_poly->vertex(iv));
}

void  polyhedron::set_vertex(size_t iv, pos3* pos)
{
   pos3d p = *pos;
   pos->Release();

   if(iv >= m_poly->vertex_size()) throw std::logic_error("Vertex index out of range " + std::to_string(iv));
   m_poly->vertex(iv) = p;
}

polyhedron_face* polyhedron::face(size_t iface) const
{
   if(iface >= m_poly->face_size()) throw std::logic_error("Face index out of range: " + std::to_string(iface));
   const pface& face = m_poly->face(iface);
   return new polyhedron_face(face);
}

double polyhedron::face_area(size_t iface) const
{
   if(iface >= m_poly->face_size()) throw std::logic_error("Face index out of range: " + std::to_string(iface));
   return m_poly->face_normal(iface).length()*0.5;
}

double polyhedron::volume() const
{
   return m_poly->volume();
}

bbox3d polyhedron::get_box() const
{
   spacemath::bbox3d box;
   size_t nvert = m_poly->vertex_size();
   for(size_t ivert=0; ivert<nvert; ivert++) {
      box.enclose(m_poly->vertex(ivert));
   }
   return get_transform()*box;
}

void polyhedron::verify() const
{
   m_poly->verify_polyhedron();
}

void polyhedron::flip_face(size_t iface)
{
   m_poly->flip_face(iface);
}

void polyhedron::flip_faces()
{
   for(size_t iface=0; iface<m_poly->face_size(); iface++) {
      m_poly->flip_face(iface);
   }
}
