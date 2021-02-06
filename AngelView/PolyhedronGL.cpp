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

#include "PolyhedronGL.h"
#include "spaceio/stl_io.h"
#include "spaceio/amf_io.h"
#include "spaceio/obj_io.h"
#include "spaceio/off_io.h"
#include <ctime>
#include <sstream>
#include <GL/glu.h>

static const bool USE_VERTEX_ARRAY = true;


PolyhedronGL::PolyhedronGL()
: m_is_changed(true)
, m_read_time(0)
, m_nvert(0)
, m_nface(0)
, m_vert(0)
, m_norm(0)
, m_face(0)
, m_filled(true)
, m_wireframe(false)
, m_axes(false)
, m_markers(false)
, m_highlight_backside(true)
, m_init_projection(true)
, m_background_dark(true)
, m_rmb_is_rotate(false)
, m_center(false)
{}

PolyhedronGL::~PolyhedronGL()
{
   clear();
}

void PolyhedronGL::clear()
{
   delete[] m_vert;
   delete[] m_norm;
   delete[] m_face;

   m_nvert = 0;
   m_nface = 0;
   m_vert  = 0;
   m_norm  = 0;
   m_face  = 0;
}

bool PolyhedronGL::read(const wxFileName& path)
{
   clear();

   m_polyset = std::make_shared<ph3d_vector>();

   std::string file_path = path.GetFullPath().ToStdString();

   if(spaceio::stl_io::is_stl(file_path)) {
      m_polyset = spaceio::stl_io::read(file_path);
   }
   else if(spaceio::amf_io::is_amf(file_path)) {
      m_polyset = spaceio::amf_io::read(file_path);
   }
   else if(spaceio::obj_io::is_obj(file_path)) {
      m_polyset = spaceio::obj_io::read(file_path);
   }
   else if(spaceio::off_io::is_off(file_path)) {
      m_polyset = spaceio::off_io::read(file_path);
   }
   else {
      return false;
   }

   bool ret = RenderModel();

   time(&m_read_time);
   m_init_projection = true;

   return ret;
}

bool PolyhedronGL::RenderModel(HTmatrix& T)
{
   clear();
   m_bbox = bbox3d();

   if(m_polyset.get()) {

      size_t npoly = m_polyset->size();
      for(size_t ipoly=0; ipoly<npoly; ipoly++) {
         std::shared_ptr<polyhedron3d> poly = (*m_polyset)[ipoly];
         size_t nv = poly->vertex_size();
         for(size_t iv=0; iv<nv; iv++) {
            m_bbox.enclose(poly->vertex(iv));
         }

         m_nvert += poly->vertex_size();
         m_nface += poly->face_size();

      }
      if(m_nvert==0 || m_nface==0)return false;
      if(USE_VERTEX_ARRAY)  ConvertModelVertexArray(m_polyset,T);
      else                  ConvertModelDirect(m_polyset,T);

   }

   m_init_projection = false;

   return true;
}

void PolyhedronGL::ConvertModelVertexArray(std::shared_ptr<ph3d_vector> polyset, HTmatrix& T)
{

   if(polyset.get() && (m_nvert>0) && (m_nface>0) ) {
      size_t npoly = polyset->size();

      m_vert = new GLfloat[m_nface*3*3];  // 3x3 coordinates per face (vertices)
      m_norm = new GLfloat[m_nface*3*3];  // 3x3 coordinates per face (normals)

      size_t ivcount = 0;
      size_t incount = 0;

      for(size_t ipoly=0; ipoly<npoly; ipoly++) {
         std::shared_ptr<polyhedron3d> poly = (*polyset)[ipoly];

         // temporary copy of the polyhedron with transformation
         std::shared_ptr<polyhedron3d> poly_t = poly->transform_copy(T);

         // convert faces and vertices from the transformed copy
         size_t nface = poly_t->face_size();
         for(size_t iface=0; iface<nface; iface++) {

            vec3d normal = poly_t->face_normal(iface);
            normal.normalise();

            // face vertex indices
            const pface& face = poly_t->face(iface);
            for(size_t iv=0; iv<3; iv++) {

               const pos3d& pos = poly_t->vertex(face[iv]);

               m_vert[ivcount++] = static_cast<GLfloat>(pos.x());
               m_vert[ivcount++] = static_cast<GLfloat>(pos.y());
               m_vert[ivcount++] = static_cast<GLfloat>(pos.z());

               m_norm[incount++] = static_cast<GLfloat>(normal.x());
               m_norm[incount++] = static_cast<GLfloat>(normal.y());
               m_norm[incount++] = static_cast<GLfloat>(normal.z());
            }

         }
      }
   }
}


void PolyhedronGL::ConvertModelDirect(std::shared_ptr<ph3d_vector> polyset, HTmatrix& T)
{

   if(polyset.get() && (m_nvert>0) && (m_nface>0) ) {
      size_t npoly = polyset->size();

      m_vert = new GLfloat[m_nvert*3];  // 3 coordinates per vertex
      m_norm = new GLfloat[m_nface*3];  // 3 coordinates per normal, one per face
      m_face = new GLuint[m_nface*3];   // 3 indices per face

      size_t ivcount = 0;
      size_t incount = 0;
      size_t ifcount = 0;

      // iv_offset is an offset to the first vertex of the current polyhedron
      size_t iv_offset = 0;

      for(size_t ipoly=0; ipoly<npoly; ipoly++) {
         std::shared_ptr<polyhedron3d> poly = (*polyset)[ipoly];

         // temporary copy of the polyhedron with transformation
         std::shared_ptr<polyhedron3d> poly_t = poly->transform_copy(T);

         // convert vertices
         size_t nvert = poly_t->vertex_size();
         for(size_t ivert=0; ivert<nvert; ivert++) {
            const pos3d& p = poly_t->vertex(ivert);
            m_vert[ivcount++] = static_cast<GLfloat>(p.x());
            m_vert[ivcount++] = static_cast<GLfloat>(p.y());
            m_vert[ivcount++] = static_cast<GLfloat>(p.z());
         }

         // convert faces
         size_t nface = poly_t->face_size();
         for(size_t iface=0; iface<nface; iface++) {

            vec3d normal = poly_t->face_normal(iface);
            normal.normalise();

            // face normal
            m_norm[incount++] = static_cast<GLfloat>(normal.x());
            m_norm[incount++] = static_cast<GLfloat>(normal.y());
            m_norm[incount++] = static_cast<GLfloat>(normal.z());

            // face vertex indices
            size_t ifoff = iface*3;
            const pface& face = poly_t->face(iface);
            for(size_t iv=0; iv<3; iv++) {
               // for multi-polyhedron models we must remember to offset the vertex indices
               m_face[ifcount++] = iv_offset + face[iv];
            }

         }

         // increment the vertex offset by the number of vertices in this polyhedron
         iv_offset += nvert;
      }
   }
}


void PolyhedronGL::draw()
{
   if( (m_nvert>0) && (m_nface>0) ) {

      if(USE_VERTEX_ARRAY) {

         // Draw using vertex arrays
         glEnableClientState(GL_VERTEX_ARRAY);
         glEnableClientState(GL_NORMAL_ARRAY);

            glVertexPointer(3, GL_FLOAT, 0, m_vert);
            glNormalPointer(GL_FLOAT, 0, m_norm);
            glDrawArrays(GL_TRIANGLES,0,m_nface*3);

         glDisableClientState(GL_VERTEX_ARRAY);
         glDisableClientState(GL_NORMAL_ARRAY);
      }
      else {

         // direct mode

         glBegin(GL_TRIANGLES);

         // traverse all faces
         for(auto iface=0; iface<m_nface; iface++) {

            // offset to normal vector of current face
            size_t ioff_face = iface*3;
            glNormal3f(m_norm[ioff_face+0],m_norm[ioff_face+1],m_norm[ioff_face+2]);

            // vertices of current face. ioff_face can be re-used since
            // a triangle has 3 vertices, same as 3 coordinates in a vertex
            for(size_t iv=0;iv<3; iv++) {

               // get the vertex number
               size_t ivert = m_face[ioff_face+iv];

               // offset to vertex coordinate
               size_t ivoff = ivert*3;
               glVertex3f(m_vert[ivoff+0],m_vert[ivoff+1],m_vert[ivoff+2]);
            }
         }
         glEnd();
      }

   }
}

