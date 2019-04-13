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
   
#ifndef DIFFERENCE3D_H
#define DIFFERENCE3D_H

#include "solid.h"
#include "solid_vector.h"

/// difference2d provides boolean difference for 3d objects
class difference3d : public solid {
public:
   // Difference allows single arguments only
   difference3d(const solid* incl, const solid*  excl);

   virtual ~difference3d();

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // clone this object onto a new solid
   virtual solid* clone_solid() const;

   string openscad_csg() const;

   spaceio::xml_node to_xcsg(spaceio::xml_node& xml_parent);

   // return bounding box
   virtual bbox3d get_box() const;

protected:
   /// \privatesection (hidden in documentation)

   virtual void populate_tree(node_csg* node) ;

   static difference3d* ctor_ss(const solid* incl,    const solid* excl)    { return new difference3d(incl,excl); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = DeclareConstructor(engine,as_typeid<difference3d>(), "difference3d@ difference3d(solid@+ incl, solid@+ excl)",asFUNCTION(difference3d::ctor_ss)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      solid::DeclareMethods<solid>(engine);
      solid::DeclareMethods<T>(engine);

      std::string type_name = as_typeid<T>();
    //  int r = 0;
    //  r = DeclareMethod(engine,type_name,"double height() const", asMETHOD(cylinder,height)); as_assert( r >= 0 );
   }


private:
   solid_vector m_incl;
   solid_vector m_excl;
};

#endif // CSG_DIFFERENCE_H
