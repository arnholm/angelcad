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
   
#include "AngelGLUIContext.h"
#include "AngelGLUICanvas.h"
#include "AngelViewMain.h"
#include "AngelViewApp.h"
#include <GL/glu.h>
#include <sstream>

AngelGLUIContext::AngelGLUIContext(wxGLUICanvas* canvas)
: wxGLUIContext(canvas)
, m_time_init(0)
{
   PolyhedronGL& model = wxGetApp().GetModel();
   canvas->SetRmbRotate(model.get_rmb_is_rotate());
}

AngelGLUIContext::~AngelGLUIContext()
{
   //dtor
}

void AngelGLUIContext::DoSceneDraw()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   PolyhedronGL& model = wxGetApp().GetModel();
   SetBackgroundDark(model.get_background_dark());

   // define the background colour black or white
   ContextClearColor();

   if(m_time_init < model.read_time()) {

      // model has been updated since last draw
      DoSceneInit(model.bounding_box(),model.get_init_projection());
      m_time_init = model.read_time();
   }

    // perform the model drawing
   bool filled_on   = model.get_filled();
   bool edges_on    = model.get_wireframe();
   bool backside_on = model.get_highlight_backside();
   bool center_on   = model.get_draw_center();
   bool axes_on     = model.get_draw_axes();
   bool markers_on  = model.get_draw_markers();

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1.0,1.0);

   if(filled_on) {
      // draw the model filled and with light

      // draw only front facing polygon



      // standard options for filled surfaces
      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
      glEnable(GL_LIGHTING);
      glEnable(GL_NORMALIZE);

      if( backside_on ) {

         // enable removal of either front or back sides
         glEnable(GL_CULL_FACE);

         // draw first front faces with standard light and normalizing, but no backsides
         glCullFace(GL_BACK);
         model.draw();

         // Then draw only back faces, in red
         glCullFace(GL_FRONT);
         glDisable(GL_LIGHTING);
         glDisable(GL_NORMALIZE);
         glColor3f(0.5, 0.0 ,0.0);
         model.draw();

   		glDisable(GL_CULL_FACE);
      }
      else {

         // draw both sides at once, with normalising
         model.draw();
      }

      glDisable(GL_LIGHTING);
      glDisable(GL_NORMALIZE);
   }

   // must disable the polygon offset here, or else the edges become hardly visible
   glDisable(GL_POLYGON_OFFSET_FILL);

   if(edges_on) {

      // show wireframe display
      if(filled_on) {

         // in combination with filled, we just show plain white edges
         glDisable(GL_LIGHTING);
         glDisable(GL_NORMALIZE);
         ContextColorForeground();
      }
      else {
         // edges alone, so shaded edges
         glEnable(GL_LIGHTING);
         glEnable(GL_NORMALIZE);
      }
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      model.draw();
   }

   if(center_on) {
      draw_camera(center(),up());
   }

   if(axes_on && model.nv()>0) {
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      glDisable(GL_LIGHTING);
      glDisable(GL_NORMALIZE);
      draw_axes(markers_on);
   }

   glFlush();

   // check for errors
   CheckGL();
}

void AngelGLUIContext::draw_axes(bool markers)
{
   bbox3d box = bounding_box();
   const pos3d& p1 = box.p1();
   const pos3d& p2 = box.p2();
   double diam = p1.dist(p2);

   pos3d c = 0.5*(p1+p2);

   // compute the rounded up size of the model volume
   double lpow  = 1.0 + int(log10(diam));
   double size  = pow(10.0,lpow);
   double delta = size/10;

   // draw the axes in R,G,Cyan
   glLineWidth(1.0);
   glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);
      glVertex3d(-size, 0.0, 0.0);  glVertex3d(+size*1.1, 0.0, 0.0);
      glColor3f(0.0, 1.0, 0.0);
      glVertex3d(0.0, -size, 0.0);  glVertex3d(0.0, +size*1.1, 0.0);
      glColor3f(0.0, 0.5, 1.0);
      glVertex3d(0.0, 0.0, -size);  glVertex3d(0.0, 0.0, +size*1.1);
   glEnd();

   // draw arrowheads
   GLUquadric* quad = gluNewQuadric();
   gluQuadricOrientation(quad,GLU_OUTSIDE);
   glPushMatrix();
      glColor3f(1.0, 0.0, 0.0);
      glTranslated(+size*1.05, 0.0, 0.0);
      glRotated(90,0,1,0);
      gluCylinder(quad, delta/10, 0.0, delta/2, 4, 1);
   glPopMatrix();
   glPushMatrix();
      glColor3f(0.0, 1.0, 0.0);
      glTranslated(0.0, +size*1.05, 0.0);
      glRotated(-90,1,0,0);
      gluCylinder(quad, delta/10, 0.0, delta/2, 4, 1);
   glPopMatrix();
   glPushMatrix();
      glColor3f(0.0, 0.5, 1.0);
      glTranslated(0.0, 0.0, +size*1.05);
      gluCylinder(quad, delta/10, 0.0, delta/2, 4, 1);
   glPopMatrix();
   gluDeleteQuadric(quad);

   if(markers) {

      // markers in foreground colour
      ContextColorForeground();

      // very simple scheme for markers
      // we cover the whole range, here assuming the model is near origin
      double x = -delta*10;
      double y = -delta*10;
      double z = -delta*10;

      double markB = delta/6;
      double markS = delta/20;
      double scale = 0.06*delta;
      int icount = 0;

      while(x <= delta*10) {

         double mark = markS;
         if(icount%10 == 0){
            // big marker
            mark = markB;

            // draw the marker label
            draw_axis_label(pos3d(x,0,0),0, x, scale);
            draw_axis_label(pos3d(0,y,0),1, y, scale);
            draw_axis_label(pos3d(0,0,z),2, z, scale);
         }

         // draw the markers
         glBegin(GL_LINES);
         glVertex3d(     x, -mark, 0.0);  glVertex3d(     x, +mark, 0.0);
         glVertex3d(-mark,      y, 0.0);  glVertex3d(+mark,      y, 0.0);
         glVertex3d(-mark,     0.0,  z);  glVertex3d(+mark,   0.0,    z);
         glEnd();

         x += delta/10.0;
         y += delta/10.0;
         z += delta/10.0;
         icount++;
      }
   }
}

void AngelGLUIContext::draw_axis_label(const pos3d& pos, size_t iaxis, double val, double scale)
{
   // make a string from the number, it is (mostly) an integer
   std::stringstream out;

   // for small models you can end up with simething like 0.1234E-14 neear origin
   // to avoid that, we collapse to 0 for very small absolute values
   val = (fabs(val)<1.0E-5)? 0.0 : val;

   out << val;
   std::string label = out.str();

   // draw in a local coordinate system
   glPushMatrix();

      // start of label, bottom left is anchor point
      glTranslated(pos.x(),pos.y(),pos.z());

      // depending on which axis this relates to,
      // rotate to align the text along x or y. Z is drawn in XZ plane

      switch(iaxis) {
         case 1: { glRotatef(+90.0,0,0,1); break; }
         case 2: { glRotatef(+90.0,1,0,0); break; }
         default: {}
      };

      // offset a little from the given point
      glTranslated(scale*0.6,scale*0.6,0);

      // draw the characters
      for(size_t i=0; i<label.length(); i++) {
         draw_digit(label[i],scale);
      }

   // return to previous coordinate system
   glPopMatrix();
}

// simplification of line drawing
inline void glLine(const pos3d& a,const pos3d& b) { glVertex3d(a.x(),a.y(),a.z());  glVertex3d(b.x(),b.y(),b.z());  }

void AngelGLUIContext::draw_digit(char ch, double scale)
{

  // just an old style stroked 'font'

/*
       e o-------o f
         |       |
         |       |
       c o-------o d
         |       |
         |       |
       a o-------o b
*/
   const pos3d f(scale,  scale*2,    0);
   const pos3d e(    0,  scale*2,    0);

   const pos3d d(scale,    scale,    0);
   const pos3d c(    0,    scale,    0);

   const pos3d b(scale,        0,    0);
   const pos3d a(    0,        0,    0);

   // swicth on digits and minus, nothing else
   switch(ch) {
      case '-':
      {
         glBegin(GL_LINES);
         glLine(c,d);
         glEnd();
         break;
      }
      case '1':
      {
         glBegin(GL_LINES);
         glLine(e,c);
         glLine(c,a);
         glEnd();
         break;
      }
      case '2':
      {
         glBegin(GL_LINES);
         glLine(e,f);
         glLine(f,d);
         glLine(d,c);
         glLine(c,a);
         glLine(a,b);
         glEnd();
         break;
      }
      case '3':
      {
         glBegin(GL_LINES);
         glLine(e,f);
         glLine(c,d);
         glLine(a,b);
         glLine(b,f);
         glEnd();
         break;
      }
      case '4':
      {
         glBegin(GL_LINES);
         glLine(e,c);
         glLine(c,d);
         glLine(f,b);
         glEnd();
         break;
      }
      case '5':
      {
         glBegin(GL_LINES);
         glLine(f,e);
         glLine(e,c);
         glLine(c,d);
         glLine(d,b);
         glLine(b,a);
         glEnd();
         break;
      }
      case '6':
      {
         glBegin(GL_LINES);
         glLine(e,a);
         glLine(a,b);
         glLine(b,d);
         glLine(d,c);
         glEnd();
         break;
      }
      case '7':
      {
         glBegin(GL_LINES);
         glLine(e,f);
         glLine(f,b);
         glEnd();
         break;
      }
      case '8':
      {
         glBegin(GL_LINES);
         glLine(e,f);
         glLine(c,d);
         glLine(a,b);
         glLine(a,e);
         glLine(b,f);
         glEnd();
         break;
      }
      case '9':
      {
         glBegin(GL_LINES);
         glLine(e,f);
         glLine(c,d);
         glLine(c,e);
         glLine(f,b);
         glEnd();
         break;
      }
      case '0':
      {
         glBegin(GL_LINES);
         glLine(e,f);
         glLine(a,b);
         glLine(a,e);
         glLine(b,f);
         glEnd();
         break;
      }
      case '.':
      {
         glBegin(GL_LINES);
         glLine(a,b);
         glEnd();
         break;
      }
      case 'e':
      case 'E':
      {
         glBegin(GL_LINES);
         glLine(e,f);
         glLine(c,d);
         glLine(a,b);
         glLine(e,a);
         glEnd();
         break;
      }
      default: {}
   };

   // move to next character
   glTranslated(scale*1.5,0,0);
}


void AngelGLUIContext::draw_camera(const pos3d& center, const vec3d& up)
{
   glDisable(GL_LIGHTING);
   glDisable(GL_NORMALIZE);
   glPointSize(8.0 );
   glBegin(GL_POINTS);
   glColor3f(1,0,0);
   glVertex3d(center.x(),center.y(),center.z());
   glEnd();

   /*
   vec3d ups = up*10;
   glBegin(GL_LINES);
   glVertex3d(center.x(),center.y(),center.z());
   glVertex3d(center.x()+ups.x(),center.y()+ups.y(),center.z()+ups.z());
   glEnd();
   */
}
