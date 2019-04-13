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
   
#ifndef WXGLUICANVAS_H
#define WXGLUICANVAS_H

#include <wx/glcanvas.h>
class wxGLUIContext;

class wxGLUICanvas : public wxGLCanvas {
public:
   wxGLUICanvas(wxWindow* parent,
                wxWindowID id=wxID_ANY,
                const int* attribList=NULL,
                const wxPoint& pos=wxDefaultPosition,
                const wxSize& size=wxDefaultSize,
                long style=wxTAB_TRAVERSAL,
                const wxString& name=wxPanelNameStr);

   virtual ~wxGLUICanvas();

   virtual wxGLUIContext* GetCurrentContext() = 0;

   bool GetRmbRotate()                    { return m_rmb_is_rotate; }
   void SetRmbRotate(bool rmb_is_rotate)  { m_rmb_is_rotate = rmb_is_rotate; }

protected:
   // event handlers

   void OnPaint(wxPaintEvent& event);

   void OnMouseLeftDown(wxMouseEvent& event);
   void OnMouseLeftUp(wxMouseEvent& event);

   void OnMouseRightDown(wxMouseEvent& event);
   void OnMouseRightUp(wxMouseEvent& event);

   void OnMouseMove(wxMouseEvent& event);

   void OnEnterWindow(wxMouseEvent&  event);
   void OnLeaveWindow(wxMouseEvent&  event);

   void OnMouseWheel(wxMouseEvent& event);

   void OnSize(wxSizeEvent& event);

protected:

   void ApplyMouseAction(bool rmb, wxPoint mouse_down,  wxPoint mouse_up);
   void ApplyMouseRotation(wxPoint mouse_down,  wxPoint mouse_up);
   void ApplyMousePan(wxPoint mouse_down,  wxPoint mouse_up);

   wxDECLARE_EVENT_TABLE();
private:
   wxPoint m_lmb_down;      // mouse position when LMB was pressed down
   wxPoint m_lmb_up;        // mouse position when LMB was released, or when mouse was moved during LMB tracking
   bool    m_lmb_tracking;  // indicates LMB is currently beeing pressed down

   wxPoint m_rmb_down;      // mouse position when RMB was pressed down
   wxPoint m_rmb_up;        // mouse position when RMB was released, or when mouse was moved during RMB tracking
   bool    m_rmb_tracking;  // indicates RMB is currently beeing pressed down

   bool    m_rmb_is_rotate; // true = mouse RMB controls rotation,LMB for pan.

   bool    m_is_shown;      // window has been shown, i.e. a paint event has been completed
};

#endif // WXGLUICANVAS_H
