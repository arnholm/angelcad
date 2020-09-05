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

#ifndef POLYHEDRONGL_H
#define POLYHEDRONGL_H

#include "spacemath/bbox3d.h"
#include "spacemath/polyhedron3d.h"
#include <wx/glcanvas.h>
#include <wx/filename.h>

using namespace spacemath;

class PolyhedronGL {
public:
   PolyhedronGL();
   virtual ~PolyhedronGL();

   time_t read_time() const { return m_read_time; }
   const bbox3d& bounding_box() const { return m_bbox; }

   bool read(const wxFileName& path);


   void set_changed(bool changed = true) { bool m_is_changed = changed; }
   bool is_changed() { return m_is_changed; }

   void set_axes(bool axes_on,bool markers_on) {m_axes = axes_on; m_markers=markers_on; set_changed(); }
   void set_filled(bool filled) { m_filled = filled; set_changed(); }
   void set_wireframe(bool wireframe) { m_wireframe = wireframe; set_changed(); }
   void set_highlight_backside(bool highlight_backside) { m_highlight_backside = highlight_backside; set_changed(); }
   void set_init_projection(bool init_projection) { m_init_projection = init_projection; set_changed(); }
   void set_background_dark(bool background_dark) { m_background_dark = background_dark; set_changed(); }
   void set_rmb_is_rotate(bool rmb_is_rotate)     { m_rmb_is_rotate = rmb_is_rotate; set_changed(); }
   void set_draw_center(bool center) { m_center = center;  set_changed(); }

   bool get_filled() { return m_filled; }
   bool get_wireframe() { return m_wireframe; }
   bool get_highlight_backside() { return m_highlight_backside; }
   bool get_init_projection() { return m_init_projection; }
   bool get_draw_axes() { return m_axes; }
   bool get_draw_markers() { return m_markers; }
   bool get_background_dark() { return m_background_dark; }
   bool get_rmb_is_rotate() { return m_rmb_is_rotate; }
   bool get_draw_center() { return m_center; }

   void draw();

   GLint nv() const { return   m_nvert; }

protected:
   void clear();

   void ConvertModelDirect(std::shared_ptr<ph3d_vector> polyset);
   void ConvertModelVertexArray(std::shared_ptr<ph3d_vector> polyset);


protected:
   GLint    m_nvert; // number of vertices
   GLint    m_nface; // number of faces

   GLfloat* m_vert;  // vertex coordinates
   GLfloat* m_norm;  // normal vectors
   GLuint*  m_face;  // face indices

private:
   bool     m_is_changed;

   bool     m_filled;
   bool     m_wireframe;
   bool     m_axes;
   bool     m_markers;
   bool     m_highlight_backside;
   bool     m_init_projection;
   bool     m_background_dark;
   bool     m_rmb_is_rotate;
   bool     m_center;

   time_t   m_read_time;
   bbox3d   m_bbox;
};

#endif // POLYHEDRONGL_H
