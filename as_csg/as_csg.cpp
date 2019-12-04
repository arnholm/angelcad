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

#include "as_csg.h"
#include "ce_angelscript_ex/as_factory.h"

// basic utilities
#include "pos2.h"
#include "pos3.h"
#include "vec3.h"
#include "vec2.h"
#include "line2.h"
#include "line3.h"
#include "localsystem3d.h"
#include "boundingbox.h"
#include "spline2.h"
#include "spline3.h"
#include "spline_path.h"
//#include "loft3d.h"
#include "polyhedron_face.h"
//#include "image2d.h"
#include "pointcloud.h"

// 2d primitives
#include "circle.h"
#include "square.h"
#include "rectangle.h"
#include "polygon.h"

// 2d booleans
#include "difference2d.h"
#include "union2d.h"
#include "intersection2d.h"
#include "hull2d.h"
#include "fill2d.h"
#include "offset2d.h"
#include "minkowski2d.h"
#include "projection2d.h"

// 3d primitives
#include "cone.h"
#include "cylinder.h"
#include "cube.h"
#include "cuboid.h"
#include "sphere.h"
#include "polyhedron.h"
//#include "tin_model.h"

// 3d booleans
#include "difference3d.h"
#include "union3d.h"
#include "intersection3d.h"
#include "hull3d.h"
#include "sweep.h"
#include "minkowski3d.h"

#include "linear_extrude.h"
#include "rotate_extrude.h"
#include "transform_extrude.h"

//transforms
#include "tmatrix.h"
#include "translate.h"
#include "rotate_x.h"
#include "rotate_y.h"
#include "rotate_z.h"
#include "scale.h"
#include "mirror.h"
#include "hmatrix.h"

as_csg::as_csg()
{}

as_csg::~as_csg()
{}

bool  as_csg::register_types()
{
   m_message_list.clear();

   try {
      asIScriptEngine* engine = asF()->engine();

      as_reftype::decl_begin();

      // abstract types must be pre-declared
      as_reftype::DeclareType<as_reftype>(engine,"Astract reference counted type");
      shape::DeclareType<shape>(engine,"Abstract base for all primitives and booleans");
      shape2d::DeclareType<shape2d>(engine,"Abstract base for 2d primitives and booleans");
      solid::DeclareType<solid>(engine,"Abstract base for 3d primitives and booleans");
      tmatrix::DeclareType<tmatrix>(engine,"Abstract base matrix for transformations");

      // 2d and 3d utilities
      pos2::InstallType(engine);
      vec2::InstallType(engine);

      // pos2 and vec2 operators require both types to be declared first
      // then the operators can ve declared
      pos2::DeclareOperators(engine);
      vec2::DeclareOperators(engine);

      pos3::InstallType(engine);
      vec3::InstallType(engine);

      // pos3 and vec3 operators require both types to be declared first
      // then the operators can ve declared
      pos3::DeclareOperators(engine);
      vec3::DeclareOperators(engine);

      line2::InstallType(engine);
      line3::InstallType(engine);

      localsystem3d::InstallType(engine);
      boundingbox::InstallType(engine);
      ::spline2::InstallType(engine);
      ::spline3::InstallType(engine);
      spline_path::InstallType(engine);
//      image2d::InstallType(engine);  // image used by loft3d and must be installed first
//      loft3d::InstallType(engine);
      polyhedron_face::InstallType(engine);
      pointcloud::InstallType(engine);

      // 2d primitives
      shape2d::InstallType(engine);
      circle::InstallType(engine);
      square::InstallType(engine);
      rectangle::InstallType(engine);
      polygon::InstallType(engine);

      // 3d primitives
      solid::InstallType(engine);
      cylinder::InstallType(engine);
      cone::InstallType(engine);
      sphere::InstallType(engine);
      cube::InstallType(engine);
      cuboid::InstallType(engine);
      polyhedron::InstallType(engine);
  //    tin_model::InstallType(engine);

      // concrete transformations
      translate::InstallType(engine);
      rotate_x::InstallType(engine);
      rotate_y::InstallType(engine);
      rotate_z::InstallType(engine);
      scale::InstallType(engine);
      mirror::InstallType(engine);
      hmatrix::InstallType(engine);

      // 2d boolean operations
      union2d::InstallType(engine);
      difference2d::InstallType(engine);
      intersection2d::InstallType(engine);
      hull2d::InstallType(engine);
      fill2d::InstallType(engine);
      sweep::InstallType(engine);
      offset2d::InstallType(engine);
      minkowski2d::InstallType(engine);
      projection2d::InstallType(engine);

      // 3d boolean operations
      union3d::InstallType(engine);
      difference3d::InstallType(engine);
      intersection3d::InstallType(engine);
      hull3d::InstallType(engine);
      minkowski3d::InstallType(engine);

      linear_extrude::InstallType(engine);
      rotate_extrude::InstallType(engine);
      transform_extrude::InstallType(engine);

      // don't do this yet, in case of documentation generation
     // as_reftype::decl_end();
   }
   catch(std::exception& ex) {
      m_message_list.push_back(ex.what());
   }

   return (m_message_list.size() == 0);
}


size_t as_csg::run_script(const string& input_file, const string& include_path, const string& outdir)
{
   m_message_list.clear();
   try {
      asF()->SetLibraryIncludePath(include_path);
      if(!asF()->RunScriptFile(input_file,outdir,"as_csg")) {
         ostringstream out;
         out << " asINFO: (line 0 , col 0 ) : Script execution failed.";
         m_message_list.push_back(out.str());
      }
      as_factory::ReleaseSingleton();
   }
   catch(std::exception& ex) {
      ostringstream out;
      out << " asERR : (line " << asF()->GetLineNumber() << ", col "<< asF()->GetColNumber() << ") : " << ex.what();
      m_message_list.push_back(out.str());
   }

   return m_message_list.size();
}


