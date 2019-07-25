#ifndef PROJECTION2D_H
#define PROJECTION2D_H

#include "shape2d.h"
#include "solid_vector.h"


class projection2d : public shape2d {
public:
   projection2d(const solid* s);
   virtual ~projection2d();

   /// \privatesection (hidden in documentation)

   // RegisterType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // clone this object onto a new shape2d
   virtual shape2d* clone_shape2d() const;

   string openscad_csg() const;

   spaceio::xml_node to_xcsg(spaceio::xml_node& xml_parent);

   // return bounding box
   virtual bbox3d get_box() const;

protected:
   /// \privatesection (hidden in documentation)

   virtual void populate_tree(node_csg* node) ;

   static projection2d* ctor_s(const solid* s) { return new projection2d(s); }

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      const std::string type_name = as_typeid<projection2d>();
      int r = DeclareConstructor(engine,type_name, "projection2d@ projection2d(const solid@+ s)",asFUNCTION(projection2d::ctor_s)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      shape2d::DeclareMethods<shape2d>(engine);
      shape2d::DeclareMethods<T>(engine);

      std::string type_name = as_typeid<T>();
    //  int r = 0;
    //  r = DeclareMethod(engine,type_name,"double height() const", asMETHOD(cylinder,height)); as_assert( r >= 0 );
   }

private:
   solid_vector  m_shapes; // we use a vector here because it knows how to manage references/cloning
};

#endif // PROJECTION2D_H
