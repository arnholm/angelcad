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
   
#include "wxGLUICanvas.h"
#include "wxGLUIContext.h"
#include <wx/dcclient.h>

#include "spacemath/vec3d.h"

static const double pi = 4.0*atan(1.0);

wxBEGIN_EVENT_TABLE(wxGLUICanvas, wxGLCanvas)
   EVT_PAINT(wxGLUICanvas::OnPaint)

	EVT_ENTER_WINDOW(wxGLUICanvas::OnEnterWindow)
	EVT_LEAVE_WINDOW(wxGLUICanvas::OnLeaveWindow)

   EVT_LEFT_DOWN(wxGLUICanvas::OnMouseLeftDown)
   EVT_LEFT_UP(wxGLUICanvas::OnMouseLeftUp)

   EVT_RIGHT_DOWN(wxGLUICanvas::OnMouseRightDown)
   EVT_RIGHT_UP(wxGLUICanvas::OnMouseRightUp)

   EVT_MOTION(wxGLUICanvas::OnMouseMove)
   EVT_MOUSEWHEEL(wxGLUICanvas::OnMouseWheel)

   EVT_SIZE(wxGLUICanvas::OnSize)
wxEND_EVENT_TABLE()

wxGLUICanvas::wxGLUICanvas(wxWindow *parent,
                                 wxWindowID id,
                                 const int* attribList,
                                 const wxPoint& pos,
                                 const wxSize& size,
                                 long style,
                                 const wxString& name)
    // With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
    // flag should always be set, because even making the canvas smaller should
    // be followed by a paint event that updates the entire canvas with new
    // viewport settings.
: wxGLCanvas(parent, wxID_ANY, attribList, wxDefaultPosition, size, wxFULL_REPAINT_ON_RESIZE)
, m_lmb_tracking(false)
, m_rmb_tracking(false)
, m_is_shown(false)
, m_rmb_is_rotate(false)
{}

wxGLUICanvas::~wxGLUICanvas()
{
   //dtor
}

void wxGLUICanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
   // This is required even though dc is not used otherwise.
   wxPaintDC dc(this);

   // Set the OpenGL viewport according to the client size of this canvas.
   // This is done here rather than in a wxSizeEvent handler because our
   // OpenGL rendering context (and thus viewport setting) is used with
   // multiple canvases: If we updated the viewport in the wxSizeEvent
   // handler, changing the size of one canvas causes a viewport setting that
   // is wrong when next another canvas is repainted.

   const wxSize ClientSize = GetClientSize();
   glViewport(0, 0, ClientSize.x, ClientSize.y);

   GetCurrentContext()->DoSceneDraw();

   // wxGLCanvas has SwapBuffers():
   // "Swaps the double-buffer of this window, making the back-buffer
   // the front-buffer and vice versa, so that the output of the previous
   // OpenGL commands is displayed on the window. "
   SwapBuffers();

   // record that this window has been painted
   m_is_shown = true;
}

void wxGLUICanvas::OnMouseLeftDown(wxMouseEvent& event)
{
   m_lmb_down = event.GetPosition();
   m_lmb_up   = m_lmb_down;
   m_lmb_tracking = true;
}

void wxGLUICanvas::OnMouseLeftUp(wxMouseEvent& event)
{
   m_lmb_up = event.GetPosition();
   if(m_lmb_tracking) {
      if(m_lmb_up != m_lmb_down) {
         ApplyMouseAction(false,m_lmb_down,m_lmb_up);
         m_lmb_down = m_lmb_up;
      }
   }
   m_lmb_tracking = false;
}

void wxGLUICanvas::OnMouseRightDown(wxMouseEvent& event)
{
   m_rmb_down = event.GetPosition();
   m_rmb_up   = m_rmb_down;
   m_rmb_tracking = true;
}

void wxGLUICanvas::OnMouseRightUp(wxMouseEvent& event)
{
   m_rmb_up = event.GetPosition();
   if(m_rmb_tracking) {
      if(m_rmb_up != m_rmb_down){
         ApplyMouseAction(true,m_rmb_down,m_rmb_up);
         m_rmb_down = m_rmb_up;
      }
   }
   m_rmb_tracking = false;
}

void wxGLUICanvas::OnMouseMove(wxMouseEvent& event)
{
   if(m_rmb_tracking) {
      m_rmb_up = event.GetPosition();
      if(m_rmb_up != m_rmb_down){
         ApplyMouseAction(true,m_rmb_down,m_rmb_up);
         m_rmb_down = m_rmb_up;
      }
   }
   if(m_lmb_tracking) {
      m_lmb_up = event.GetPosition();
      if(m_lmb_up != m_lmb_down) {
         ApplyMouseAction(false,m_lmb_down,m_lmb_up);
         m_lmb_down = m_lmb_up;
      }
   }
}

void wxGLUICanvas::ApplyMouseAction(bool rmb, wxPoint mouse_down,  wxPoint mouse_up)
{
   if(rmb) {
      if(m_rmb_is_rotate) ApplyMouseRotation(mouse_down,mouse_up);
      else                ApplyMousePan(mouse_down,mouse_up);
   }
   else {
      if(m_rmb_is_rotate) ApplyMousePan(mouse_down,mouse_up);
      else                ApplyMouseRotation(mouse_down,mouse_up);
   }
}

void wxGLUICanvas::ApplyMousePan(wxPoint mouse_down,  wxPoint mouse_up)
{
   wxCoord width,height;
   GetSize(&width,&height);

   double dx = double(mouse_up.x - mouse_down.x)/width;
   double dy = -1*double(mouse_up.y - mouse_down.y)/height;

   GetCurrentContext()->PanApply(dx,dy);
   Refresh(false);
}

void wxGLUICanvas::ApplyMouseRotation(wxPoint mouse_down,  wxPoint mouse_up)
{
   wxCoord width,height;
   GetSize(&width,&height);

   wxGLUIContext* context = GetCurrentContext();

   // compute distance to centre of view
   double dist_x = mouse_up.x - width/2;
   double dist_y = mouse_up.y - height/2;
   double dist   = sqrt(dist_x*dist_x + dist_y*dist_y);
   if(dist > height/2) {

      // we are in the corner somewhere
      // compute the position angle of each mouse position.
      // Compute against a reference vector to maintain proper sign

      pos3d centre(0.5*width,0.5*height,0.0);
      pos3d p1(mouse_down.x,mouse_down.y,0.0);
      pos3d p2(mouse_up.x,mouse_up.y,0.0);
      vec3d vref(width,0,0);
      vec3d v1(centre,p1);
      vec3d v2(centre,p2);

      // The signed angle is the difference between these angles,
      // but the sign is opposite in the lower corners!
      double ang1  = vref.angle(v1);
      double ang2  = vref.angle(v2);
      double z_rad = (dist_y < 0)? ang1-ang2 : ang2-ang1;
      context->RotateZV(z_rad);
   }
   else {
      double dx = mouse_up.x - mouse_down.x;
      double dy = mouse_up.y - mouse_down.y;
      double y_rad  = -pi*(dy/height);
      double x_rad  =  pi*(dx/width);
      context->RotateXV(y_rad);
      context->RotateYV(x_rad);
   }
   context->RotateApply();
   Refresh(false);
}

void wxGLUICanvas::OnEnterWindow(wxMouseEvent&  event)
{
   m_rmb_tracking = false;
   m_lmb_tracking = false;
   SetFocus();
   event.Skip();
}

void wxGLUICanvas::OnLeaveWindow(wxMouseEvent&  event)
{
   m_rmb_tracking = false;
   m_lmb_tracking = false;
   GetParent()->SetFocus();
   event.Skip();
}

void wxGLUICanvas::OnMouseWheel(wxMouseEvent& event)
{
   int rot = event.GetWheelRotation()/event.GetWheelDelta();
   if(rot != 0){
      wxPoint mpos = event.GetPosition();

      wxCoord width,height;
      GetSize(&width,&height);

      // prevent zoom if mouse cursor is outside window borders
      int x = mpos.x;
      if(x<0 || x>(width-1))return;

      int y = mpos.y;
      if(y<0 || y>(height-1))return;

      GetCurrentContext()->ZoomApply(rot);
      Refresh(false);
   }
}

void wxGLUICanvas::OnSize(wxSizeEvent& event)
{
   if(m_is_shown) {
      // we may access the context
      // only after a paint event has happened.
      GetCurrentContext()->SetSceneProjection();
      Refresh(false);
   }
}
