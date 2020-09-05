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

#ifndef WXGLUICONTEXT_H
#define WXGLUICONTEXT_H

#include <vector>
#include <wx/glcanvas.h>
#include <wx/image.h>
#include "spacemath/pos3d.h"
#include "spacemath/vec3d.h"
#include "spacemath/bbox3d.h"
#include "spacemath/HTmatrix.h"
class wxGLUICanvas;
using namespace spacemath;

class wxGLUIContext : public wxGLContext {
public:

   wxGLUIContext(wxGLUICanvas* canvas);
   virtual ~wxGLUIContext();

   // set light sources and related parameters
   virtual void SetSceneLight();

   // DoSceneInit must be called once before any drawing or rotation
   // It will call SetSceneProjection() if init_projection=true
   virtual void DoSceneInit(const bbox3d& box, bool init_projection);

   // (Re)set the GL_PROJECTION according to current window aspect
   virtual void SetSceneProjection();

   // draws the current scene
   virtual void DoSceneDraw() = 0;

   // return the bounding box
   const bbox3d& bounding_box() const { return m_box; }

   // Rotate around X viewport axis
   void RotateXV(double rad);

   // Rotate around Y viewport axis
   void RotateYV(double rad);

   // Rotate around Z viewport axis
   void RotateZV(double rad);

   // Apply rotations to OpenGL
   void RotateApply();

   // Apply zoom to OpenGL. Positive value=zoom out
   void ZoomApply(int zoom);

   // Apply pan to OpenGL, dx and dy are in normalised screen coordinates,
   // indicating amount and direction of pan
   void PanApply(double dx, double dy);

   // set specified view direction
   void SetViewFrom(const vec3d& fromvec, const vec3d& upvec);

   // set default view, eyepoint and center
   void SetViewDefault(bool realise_now);

   // Grab a snapshot of the current screen display
   bool GetScreenImage(wxImage& image);

   // set dark or bright background
   void SetBackgroundDark(bool black);

   // clear background according to dark/bright setting
   void ContextClearColor();

   // Set foreground colour (typically for lines) corresponding to dark/bright setting
   void ContextColorForeground();

protected:

   void CheckGL();

   inline const pos3d& center() const { return m_center; }
   inline const pos3d& eye() const { return m_eye; }
   inline const vec3d& up() const { return m_up; }

private:
   wxGLUICanvas*        m_canvas;     // the one and only canvas for this context, used for getting window size etc
   pos3d                m_center;     // the position the eye is looking towards. Initially geometric center of model
   pos3d                m_eye;        // the eyepoint we are viewing from. Modified with call to zoom_apply(...)
   vec3d                m_up;         // camera up-vector in model space
   bbox3d               m_box;        // application specified model bounding box
   double               m_diam;       // scene diameter computed from the bounding box
   HTmatrix             m_transform;  // computed viewing transformation, mostly rotations. Reset with call to RotateApply()
   HTmatrix             m_zrot;       // accumulated ZV rotation to keep consistent UP vector on screen

   std::vector<GLfloat> m_bg;         // background colour (4 values)
   std::vector<GLfloat> m_fg;         // foreground colour (4 values)
   bool                 m_light_ok;   // true when light has been initialised
};

#endif // WXGLUICONTEXT_H
