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

#ifndef POLYGON_H
#define POLYGON_H

#include "shape2d.h"
#include "spacemath/pos2d.h"
#include "spline2.h"
class pos2;
#include <vector>
using namespace std;
class CScriptArray;

using spacemath::pos2d;

/// polygon generates a 2d polygon
class polygon : public shape2d {
public:
    // scripting interface
   polygon(const CScriptArray* points, bool check);
   polygon(const pos2* p1, const pos2* p2, const pos2* p3, const pos2* p4=0, const pos2* p5=0);
   polygon(const ::spline2* spline, int nseg);
   polygon(double r, size_t np);
   virtual ~polygon();

   size_t size() const;

   // return vertex position
   pos2* vertex(size_t iv) const;

   // compute the area of the polygon
   double area() const;

   // compute the signed area of the polygon
   double signed_area() const;

   /// \privatesection (hidden in documentation)

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // clone this object onto a new shape2d
   virtual shape2d* clone_shape2d() const;

   string openscad_csg() const;

   spaceio::xml_node to_xcsg(spaceio::xml_node& xml_parent);

   // return bounding box
   virtual bbox3d get_box() const;

protected:
   /// \privatesection (hidden in documentation)

   // ==== SCRIPTING INTERFACE

   // static functions used with scripting constructors
   static polygon* ctor_arr(const CScriptArray* points, bool check) { return new polygon(points,check); }
   static polygon* ctor_p3(const pos2* p1, const pos2* p2, const pos2* p3                                            ) { return new polygon(p1,p2,p3); }
   static polygon* ctor_p4(const pos2* p1, const pos2* p2, const pos2* p3, const pos2* p4                      ) { return new polygon(p1,p2,p3,p4); }
   static polygon* ctor_p5(const pos2* p1, const pos2* p2, const pos2* p3, const pos2* p4, const pos2* p5) { return new polygon(p1,p2,p3,p4,p5); }
   static polygon* ctor_s1(const ::spline2* spline, int nseg) { return new polygon(spline,nseg); }
   static polygon* ctor_rp(double r, size_t np) { return new polygon(r,np); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      std::string type_name = as_typeid<polygon>();
      int r = DeclareConstructor(engine,type_name, "polygon@ polygon(array<pos2d@>@+ points, bool check=true)",asFUNCTION(polygon::ctor_arr)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "polygon@ polygon(const pos2d@+ p1, const pos2d@+ p2, const pos2d@+ p3 )",asFUNCTION(polygon::ctor_p3)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "polygon@ polygon(const pos2d@+ p1, const pos2d@+ p2, const pos2d@+ p3, const pos2d@+ p4 )",asFUNCTION(polygon::ctor_p4)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "polygon@ polygon(const pos2d@+ p1, const pos2d@+ p2, const pos2d@+ p3, const pos2d@+ p4, const pos2d@+ p5 )",asFUNCTION(polygon::ctor_p5)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "polygon@ polygon(const spline2d@+ spline, uint nseg=30)",asFUNCTION(polygon::ctor_s1)); as_assert( r >= 0 );
          r = DeclareConstructor(engine,type_name, "polygon@ polygon(double r, uint np)",asFUNCTION(polygon::ctor_rp)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      shape2d::DeclareMethods<shape2d>(engine);
      shape2d::DeclareMethods<T>(engine);

      // local methods
      std::string type_name = as_typeid<T>();
      int r = 0;
      r = DeclareMethod(engine,type_name,"uint size() const", asMETHOD(polygon,size)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"pos2d@ vertex(uint iv) const", asMETHOD(polygon,vertex)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double area() const", asMETHOD(polygon,area)); as_assert( r >= 0 );
      r = DeclareMethod(engine,type_name,"double signed_area() const", asMETHOD(polygon,signed_area)); as_assert( r >= 0 );
   }

private:
   vector<pos2d> m_vert;
};

#endif // SQUARE_H
