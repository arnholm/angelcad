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

#include "polygon.h"
#include <sstream>
#include "ce_angelscript_ex/as_vector.h"
#include "pos2.h"
#include "spacemath/polygon2d.h"

static const double epspnt=1.0E-4,epspar=1.0E-3;
static const double pi = 4.0*atan(1.0);

void polygon::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted polygon type
   DeclareType<polygon>(engine,"polygon, vertices in CCW order");

   // Declare allowed type conversion between polygon(=derived) and shape2d(=base)
   DeclareCast<polygon,shape2d>(engine);
   DeclareCast<polygon,shape>(engine);

   // Declare the polygon constructors
   DeclareConstructors(engine);
   // Inherit any methods + declare the unique polygon methods
   polygon::DeclareMethods<polygon>(engine);
}

shape2d* polygon::clone_shape2d() const
{
   return new polygon(*this);
}

polygon::polygon(const CScriptArray* points, bool check)
: shape2d(as_typeid<polygon>())
{
   as_vector<pos2*> other(points);
   if(other.size() < 3) {
      string message = "polygon exception: A polygon must be specified with at least 3 points";
      throw logic_error(message);
   }
   for(size_t i=0; i<other.size(); i++) {
      pos2* pnt = other[i];
      if(!pnt) {
         string message = "polygon exception: NULL element detected in polygon points, index=" + std::to_string(i);
         throw logic_error(message);
      }
      m_vert.push_back(pos2d(pnt->x(),pnt->y()));
   }

   if(check) {
      spacemath::polygon2d poly2d(m_vert);
      if(!(poly2d.area() > 0)) {
         string message = "polygon exception: The polygon specified has zero area";
         throw logic_error(message);
      }

      if(poly2d.is_self_interesecting(epspnt,epspar)) {
         string message = "polygon exception: The polygon is self-intersecting";
         throw logic_error(message);
      }
   }
}

polygon::polygon(const ::spline2* spline, int nseg)
: shape2d(as_typeid<polygon>())
{
   if(nseg < 2) {
      string message = "polygon exception: A polygon defined from a spline2 must be specified with at least 2 segments";
      throw logic_error(message);
   }
   double dt = 1.0/nseg;
   size_t np = nseg+1;
   double t = 0.0;
   for(size_t ip=0; ip<np; ip++) {
      m_vert.push_back(spline->pos_raw(t));
      t += dt;
   }
   spacemath::polygon2d poly2d(m_vert);

   if(!(poly2d.area() > 0)) {
      string message = "polygon exception: The polygon specified has zero area";
      throw logic_error(message);
   }

   if(poly2d.is_self_interesecting(epspnt,epspar)) {
      string message = "polygon exception: The polygon is self-intersecting";
      throw logic_error(message);
   }
}

polygon::polygon(double r, size_t np)
: shape2d(as_typeid<polygon>())
{
   if(r <= 0.0) {
      string message = "polygon exception: A polygon defined from radius requires a radius > 0.0";
      throw logic_error(message);
   }

   if(np < 3) {
      string message = "polygon exception: A polygon defined from radius and number of points must have at least 3 points";
      throw logic_error(message);
   }

   double dang  = 2*pi/np;
   double angle = 0.0;
   for(size_t ip=0; ip<np; ip++) {
      double x = r*cos(angle);
      double y = r*sin(angle);
      m_vert.push_back(pos2d(x,y));
      angle += dang;
   }
}

polygon::polygon(const pos2* p1, const pos2* p2, const pos2* p3, const pos2* p4, const pos2* p5)
: shape2d(as_typeid<polygon>())
{
   m_vert.push_back(*p1);
   m_vert.push_back(*p2);
   m_vert.push_back(*p3);
   if(p4)m_vert.push_back(*p4);
   if(p5)m_vert.push_back(*p5);
   spacemath::polygon2d poly2d(m_vert);

   if(!(poly2d.area() > 0)) {
      string message = "polygon exception: The polygon specified has zero area";
      throw logic_error(message);
   }

   if(poly2d.is_self_interesecting(epspnt,epspar)) {
      string message = "polygon exception: The polygon is self-intersecting";
      throw logic_error(message);
   }
}

polygon::~polygon()
{}

size_t polygon::size() const
{
   return m_vert.size();
}

pos2* polygon::vertex(size_t iv) const
{
   if(iv >= m_vert.size()) throw std::logic_error("Vertex index out of range: " + std::to_string(iv));
   return new pos2(m_vert[iv]);
}

string polygon::openscad_csg() const
{
   ostringstream out;
   out << "polygon( points=[";
   for(size_t i=0; i<m_vert.size(); i++) {
      const pos2d& p = m_vert[i];
      if(i>0) out << ',';
      out << setprecision(12) << '[' << p.x() << ',' << p.y() << ']';
   }
   out << "] );";
   return out.str();
}

spaceio::xml_node polygon::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   // vertices
   {
      spaceio::xml_node xml_vertices = xml_this.add_child("vertices");
      for(size_t ivert=0; ivert<m_vert.size(); ivert++) {
         const pos2d& p = m_vert[ivert];
         spaceio::xml_node xml_vertex = xml_vertices.add_child("vertex");
         xml_vertex.add_property("x",p.x());
         xml_vertex.add_property("y",p.y());
      }
   }
   return xml_this;
}


double polygon::area() const
{
   spacemath::polygon2d poly2d(m_vert);
   return poly2d.area();
}

double polygon::signed_area() const
{
   spacemath::polygon2d poly2d(m_vert);
   return poly2d.signed_area();
}


bbox3d polygon::get_box() const
{
   bbox3d box;
   for(size_t ivert=0; ivert<m_vert.size(); ivert++) {
      const pos2d& p = m_vert[ivert];
      box.enclose(pos3d(p.x(),p.y(),0));
   }
   return get_transform()*box;
}
