#include "projection2d.h"
#include "solid.h"
#include "xcsg_vector.h"

projection2d::projection2d(const solid* s)
: shape2d(as_typeid<projection2d>())
, m_shapes(s)
{}

projection2d::~projection2d()
{
   //dtor
}


void projection2d::InstallType(asIScriptEngine* engine)
{
   // Declare the reference counted type
   DeclareType<projection2d>(engine,"Project from 3d to 2d");

    // Declare allowed type conversion between csg_sphere(=derived) and shape2d(=base)
   DeclareCast<projection2d,shape2d>(engine);
   DeclareCast<projection2d,shape>(engine);

   // Declare the csg_sphere constructors
   DeclareConstructors(engine);

   // Inherit any methods
   projection2d::DeclareMethods<projection2d>(engine);
}

shape2d* projection2d::clone_shape2d() const
{
   // we use default copy contructor, relying on copy constructor of members & base
   return new projection2d(*this);
}

bbox3d projection2d::get_box() const
{
   bbox3d box;
   for(size_t i=0;i<m_shapes.size(); i++) {
      const solid* body = m_shapes[i];
      bbox3d shape_box = body->get_box();
      box.enclose(shape_box.p1());
      box.enclose(shape_box.p2());
   }
   return get_transform()*box;
}

string projection2d::openscad_csg() const
{
   return "projection()";
}


spaceio::xml_node projection2d::to_xcsg(spaceio::xml_node& xml_parent)
{
   spaceio::xml_node xml_this = xml_parent.add_child(as_typeid(this));
   transform(xml_this);

   xcsg_vector<solid_vector> vec(m_shapes);
   vec.to_xcsg(xml_this);

   return xml_this;
}
