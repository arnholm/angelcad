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
   
#ifndef ANGELGLUICONTEXT_H
#define ANGELGLUICONTEXT_H

#include "wxGLUIContext.h"
class wxGLUICanvas;

class AngelGLUIContext : public wxGLUIContext {
public:
   AngelGLUIContext(wxGLUICanvas* canvas);
   virtual ~AngelGLUIContext();

   // draws the current scene
   virtual void DoSceneDraw();

protected:

   void draw_camera(const pos3d& center, const vec3d& up);
   void draw_axes(bool markers);
   void draw_axis_label(const pos3d& pos, size_t iaxis, double val, double scale);
   void draw_digit(char ch, double scale);

private:
   time_t  m_time_init;   // time of last model initialisation
};

#endif // ANGELGLUICONTEXT_H
