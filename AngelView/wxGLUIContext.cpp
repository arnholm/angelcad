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
   
#include "wxGLUIContext.h"
#include "wxGLUICanvas.h"
#include <GL/glu.h>
#include <algorithm>
#include "spacemath/vec3d.h"

const double pi = 4.0*atan(1.0);

using namespace spacemath;

static void CheckGLError()
{
    GLenum errLast = GL_NO_ERROR;
    for ( ;; ) {
        GLenum err = glGetError();
        if ( err == GL_NO_ERROR )   return;

        // normally the error is reset by the call to glGetError() but if
        // glGetError() itself returns an error, we risk looping forever here
        // so check that we get a different error than the last time
        if ( err == errLast )  {
            wxLogError(wxT("OpenGL error state couldn't be reset."));
            return;
        }

        errLast = err;
        wxLogError(wxT("OpenGL error %d"), err);
    }
}

void wxGLUIContext::CheckGL()
{
   CheckGLError();
}

inline HTmatrix glGetMatrix(GLenum pname)
{
   HTmatrix gl_matrix;
   glGetDoublev(pname,gl_matrix.raw());
   return transpose(gl_matrix);
}

inline void glLoadMatrix(const HTmatrix& matrix)
{
   HTmatrix gl_matrix = transpose(matrix);
   glLoadMatrixd(gl_matrix.raw());
}

wxGLUIContext::wxGLUIContext(wxGLUICanvas* canvas)
: wxGLContext(canvas)
, m_canvas(canvas)
, m_center(0,0,0)
, m_eye(1,1,1)
, m_up(0,0,1)
, m_box(pos3d(-100,-100,-100),pos3d(100,100,100))
, m_diam(1.0)
, m_light_ok(false)
{
   SetBackgroundDark(true);
}

wxGLUIContext::~wxGLUIContext()
{}

void wxGLUIContext::SetBackgroundDark(bool black)
{
   m_bg.resize(4);
   m_fg.resize(4);

   if(black) {
      m_bg[0] = 0.0f;
      m_bg[1] = 0.0f;
      m_bg[2] = 0.0f;
      m_bg[3] = 1.0f;

      m_fg[0] = 1.0f;
      m_fg[1] = 1.0f;
      m_fg[2] = 1.0f;
      m_fg[3] = 1.0f;
   }
   else {
      m_bg[0] = 1.0f;
      m_bg[1] = 1.0f;
      m_bg[2] = 0.89f;
      m_bg[3] = 1.0f;

      m_fg[0] = 0.0f;
      m_fg[1] = 0.0f;
      m_fg[2] = 0.0f;
      m_fg[3] = 1.0f;
   }

}

void wxGLUIContext::ContextClearColor()
{
   glClearColor(m_bg[0],m_bg[1],m_bg[2],m_bg[3]);
}

void wxGLUIContext::ContextColorForeground()
{
   glColor3f(m_fg[0],m_fg[1],m_fg[2]);
}

void wxGLUIContext::SetSceneLight()
{
   if(m_light_ok)return;

   glEnable(GL_DEPTH_TEST);

   // add slightly more light, the default lighting is rather dark
   GLfloat ambient[] = { 0.5f, 0.0f, -3.0f, 1.0f };

   GLfloat light_diffuse0[]  = {1.1f, 0.9f, -0.8f, 1.0f};
   GLfloat light_position0[] = {-1.0, -1.0, +3.0, 0.0};

//   GLfloat light_diffuse1[]  = {1.1f, 0.9f, -0.8f, 1.0f};
   GLfloat light_diffuse1[]  = {1.0f, 0.8f, -0.7f, 1.0f};
   GLfloat light_position1[] = {+1.0, +1.0, -0.5, 0.0};

   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
   glEnable(GL_LIGHT0);

   glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
   glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
   glEnable(GL_LIGHT1);

   glEnable(GL_LIGHTING);
   glEnable(GL_NORMALIZE);

   CheckGLError();

   m_light_ok = true;
}

void wxGLUIContext::DoSceneInit(const bbox3d& box, bool init_projection)
{
   m_box = box;

   SetCurrent(*m_canvas);

   if(init_projection) {
      SetSceneLight();
      SetViewDefault(false);
      SetSceneProjection();
   }
}


void wxGLUIContext::SetSceneProjection()
{
   // Compute window aspect ratio, where aspect is relative
   // window width compared to height
   wxCoord width,height;
   m_canvas->GetSize(&width,&height);
   double aspect = double(width)/double(height);

   // near=2 and far=100 clipping planes seems to work ok
   GLdouble zNear = 2.0;
   GLdouble zFar = zNear + 100*m_diam;

      // set the projection transformation with built.in aspect ratio
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum( -1.0*aspect, 1.0*aspect, -1.0, 1.0, zNear, zFar);

   // set modelview using a dummy zoom
   ZoomApply(0);
}

void wxGLUIContext::RotateXV(double rad)
{
   double sinang = sin(rad);
   double cosang = cos(rad);

   HTmatrix rot;

   // rotate around screen x
   rot(1,1) = cosang;  rot(2,1) = -sinang;
   rot(1,2) = sinang;  rot(2,2) =  cosang;

   m_transform = rot*m_transform;
}

void wxGLUIContext::RotateYV(double rad)
{
   double sinang = sin(rad);
   double cosang = cos(rad);

   HTmatrix rot;

   // rotate around screen y
   rot(0,0) = cosang;  rot(2,0) = -sinang;
   rot(0,2) = sinang;  rot(2,2) =  cosang;

   m_transform = rot*m_transform;
}

void wxGLUIContext::RotateZV(double rad)
{
   double sinang = sin(rad);
   double cosang = cos(rad);

   HTmatrix rot;

   // rotate around screen z
   rot(0,0) = cosang;  rot(1,0) = -sinang;
   rot(0,1) = sinang;  rot(1,1) =  cosang;

   m_transform = rot*m_transform;

   // accumulate the ZV rotation
   m_zrot = rot*m_zrot;
}

void wxGLUIContext::RotateApply()
{
   glMatrixMode(GL_MODELVIEW);

   // start by moving the origin to model centre, using OpenGL
   // as we want to rotate around model origin always (a simplification... but good enough)
   glTranslated(+m_center.x(),+m_center.y(),+m_center.z());

   // read the OpenGL matrix
   HTmatrix gl_matrix;
   glGetDoublev(GL_MODELVIEW_MATRIX,gl_matrix.raw());
   gl_matrix = transpose(gl_matrix);

   // save the OpenGL origin as defined in the matrix
   double dx = gl_matrix(0,3);
   double dy = gl_matrix(1,3);
   double dz = gl_matrix(2,3);

   // zero the origin coordinates in the OpenGL matrix
   gl_matrix(0,3) = 0.0;
   gl_matrix(1,3) = 0.0;
   gl_matrix(2,3) = 0.0;

   // pre-multiply our local rotation, this ensures rotation around screen axes
   gl_matrix = m_transform*gl_matrix;

   // restore the original origin in the matrix, after pre-multiolying our rotations
   gl_matrix(0,3) = dx;
   gl_matrix(1,3) = dy;
   gl_matrix(2,3) = dz;

   // load the modified matrix back to OpenGL

   gl_matrix = transpose(gl_matrix);
   glLoadMatrixd(gl_matrix.raw());

   // finally move the origin back to where it was
   glTranslated(-m_center.x(),-m_center.y(),-m_center.z());

   // Compute a model coordinate vector normal to the screen
   // and with a length equal to the distance between eyepoint and center

   vec3d view(m_center,m_eye);
   double vlen = view.length();
   HTmatrix gl_matrix_inv = fast_inverse(gl_matrix);

   vec3d screen_normal = gl_matrix_inv*vec3d(0,0,1);
   screen_normal.normalise();
   screen_normal.scale(vlen);

   // we can now compute a new eye point
   m_eye = m_center + screen_normal;

   vec3d zdir(m_up);
   zdir.normalise();

   // compute a new up vector
   vec3d xdir(m_eye,m_center);
   xdir.normalise();
   vec3d ydir = zdir.cross(xdir);
   m_up  = xdir.cross(ydir);
   m_up.normalise();

   // set our transformation matrix to identity,
   // because the values are now incorporated into the OpenGL matrix
   m_transform = HTmatrix();

   // apply the rotation via dummy zoom
   ZoomApply(0);
}

void wxGLUIContext::ZoomApply(int zoom)
{
   // read the OpenGL matrix and estimate a model coordinate vector normal to screen
   HTmatrix gl_matrix;
   glGetDoublev(GL_MODELVIEW_MATRIX,gl_matrix.raw());

   HTmatrix gl_matrix_inv = fast_inverse(gl_matrix);
   vec3d zvec = gl_matrix_inv*vec3d(0,0,1);
   zvec.normalise();

   // zoom is realised by moving the eyepoint (i.e. fake zoom)
   if(zoom>0)      m_eye -= 0.15*m_diam*zvec;
   else if(zoom<0) m_eye += 0.15*m_diam*zvec;

   if(zoom != 0) {

      vec3d zdir(m_up);
      zdir.normalise();

      // compute a new up vector
      vec3d xdir(m_eye,m_center);
      xdir.normalise();
      vec3d ydir = zdir.cross(xdir);
      m_up  = xdir.cross(ydir);
      m_up.normalise();
   }

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // premultiply the accumulated ZV rotation to maintain the direction of the UP vector on the screen
   glGetDoublev(GL_MODELVIEW_MATRIX,gl_matrix.raw());
   gl_matrix = transpose(gl_matrix);

   gl_matrix = m_zrot*gl_matrix;

   gl_matrix = transpose(gl_matrix);
   glLoadMatrixd(gl_matrix.raw());

   // perform the zoom by modified "look at" parameters.
   // This will post-multiply the modelview matrix and thus maintain the ZV rotation
   gluLookAt(m_eye.x(),m_eye.y(),m_eye.z(), m_center.x(), m_center.y(), m_center.z(), m_up.x(),m_up.y(),m_up.z());

}

void wxGLUIContext::PanApply(double dx, double dy)
{
   // read the OpenGL matrix and estimate model coordinate vectors
   // corresponding to screen x and y

   HTmatrix gl_matrix;
   glGetDoublev(GL_MODELVIEW_MATRIX,gl_matrix.raw());

   HTmatrix gl_matrix_inv = fast_inverse(gl_matrix);
   vec3d xvec = gl_matrix_inv*vec3d(-1,0,0);
   xvec.normalise();

   vec3d yvec =  gl_matrix_inv*vec3d(0,-1,0);
   yvec.normalise();

   // 3d pan vector
   vec3d pan = 3.0*m_diam*(dx*xvec + dy*yvec);

   // Pan by moving eyepoint and center point
   m_center += pan;
   m_eye    += pan;

   // enforce via dummy zoom
   ZoomApply(0);
}

void wxGLUIContext::SetViewFrom(const vec3d& fromvec, const vec3d& upvec)
{
   // distance from eyepoint to center
   vec3d view(m_center,m_eye);
   double vlen = view.length();

   vec3d fvec(fromvec);
   fvec.normalise();

   // set the new eye-point
   m_eye = m_center + vlen*fvec;

   // set the specified up vector
   m_up = upvec;

   // set accumulated ZV rotation to identity
   m_zrot = HTmatrix();

   // update up vector to be orthogonal
   vec3d xdir(m_eye,m_center);
   xdir.normalise();
   vec3d ydir = m_up.cross(xdir);
   m_up  = xdir.cross(ydir);
   m_up.normalise();

   // enforce via dummy zoom
   ZoomApply(0);
}

void  wxGLUIContext::SetViewDefault(bool realise_now)
{
   const pos3d& p1 = m_box.p1();
   const pos3d& p2 = m_box.p2();
   vec3d diag(p1,p2);

   // default scene diameter
   m_diam   = diag.length();

   // initial center and eyepoint
   m_center = 0.5*(p1 + p2);
   m_eye    = pos3d(2*m_diam/3,-m_diam,0.75*m_diam);

   // default up vector
   m_up     = vec3d(0,0,1);

   // set accumulated ZV rotation to identity
   m_zrot = HTmatrix();

   // set modelview using a dummy zoom
   if(realise_now) ZoomApply(0);
}

bool wxGLUIContext::GetScreenImage(wxImage& image)
{
   wxCoord width,height;
   m_canvas->GetSize(&width,&height);

   // instead of forcing a window size truncation to 4 byte alignment,
   // we tell OpenGL to use 1-byte alignment (by default it is 4-byte alignment in glReadPixels)
   glPixelStorei(GL_PACK_ALIGNMENT,1);
   GLubyte* pixels = new GLubyte[3*width*height];
   glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

   // flip the image upside down, since OpenGL starts at bottom left, while wxImage starts at top left
   std::vector<GLubyte> tmp(width*3);
   for(int iy=0; iy<height/2; iy++) {

      // original and flipped row indices
      int iy1 = iy;
      int iy2 = height-iy-1;

      // corresponding byte offsets
      int i1 = 3*(iy1*width);
      int i2 = 3*(iy2*width);

      // do the flipping of rows
      memcpy(&tmp[0]    ,&pixels[i1],3*width);
      memcpy(&pixels[i1],&pixels[i2],3*width);
      memcpy(&pixels[i2],&tmp[0]    ,3*width);
   }

   // the wxImage takes ownership of the "pixels" array from here, no need to delete
   image.SetData(pixels,width,height);
   return true;
}
