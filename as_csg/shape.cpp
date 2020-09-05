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

#include "shape.h"
#include <fstream>
#include <iostream>
using namespace std;
#include "tmatrix.h"
#include "version.h"
#include "spaceio/xml_tree.h"

#include "ce_angelscript_ex/as_factory.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/convenience.hpp>

#include "boundingbox.h"

void shape::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   // DeclareType<shape>(engine);

   // no constructors here, this is an abstract class

   // Declare the shape methods
   as_reftype::DeclareMethods<shape>(engine);
   shape::DeclareMethods<shape>(engine);
}

shape::shape(const std::string& type)
: as_reftype(type)
{}

shape::~shape()
{}

as_reftype* shape::clone_scoped()
{
   return clone_shape();
}

void shape::populate_tree(node_csg* node)
{
   node->push_back(new node_csg(this));
}

void shape::write_csg(const string& file_path)
{
   string outsubdir = asF()->GetOutSubDir();

   boost::filesystem::path fullpath(file_path);
   boost::filesystem::path boost_path;
   if(outsubdir.length() > 0) boost_path = fullpath.parent_path() / outsubdir / fullpath.stem();
   else                       boost_path = fullpath.parent_path() / fullpath.stem();
   boost::filesystem::create_directories(boost_path.parent_path());
   std::string path = boost_path.string() + ".csg";

   ofstream out(path);
   out << "// This file was created using AngelCAD (as_csg) " << AS_CSG_version << endl;
   out << "// Copyright(C) 2015-2020 Carsten Arnholm, http://arnholm.org/ " << endl;
   out << "// Open it with OpenSCAD for display or further processing " << endl;
   out << "$fn = 60;" << endl;
   out << "$fa = 6.0;" << endl;
   out << "$fs = 1.0;" << endl;
   export_csg(out);

   cout << endl << "Created OpenSCAD file: " << path;
}

void shape::export_csg(ostream& out)
{
   // the root node has no parent
   node_csg root(0);
   populate_tree(&root);
   root.write_csg(out);
}

void shape::write_xcsg(const string& file_path, double secant_tolerance)
{
   boost::system::error_code ec;
   string outsubdir = asF()->GetOutSubDir();

   boost::filesystem::path fullpath(file_path);
   boost::filesystem::path boost_path;
   if(outsubdir.length() > 0) boost_path = fullpath.parent_path() / outsubdir / fullpath.stem();
   else                       boost_path = fullpath.parent_path() / fullpath.stem();

   if(!boost_path.parent_path().empty()) {
      boost::filesystem::create_directories(boost_path.parent_path());
   }
   std::string path = boost_path.string() + ".xcsg";

   spaceio::xml_tree tree;
   if(tree.create_root("xcsg")) {
      spaceio::xml_node root;
      if(tree.get_root(root)) {
         root.add_property("version","1.0");
         if(secant_tolerance > 0.0) {
            root.add_property("secant_tolerance",secant_tolerance);
         }
         add_metadata(root,boost_path.stem().string());

         this->to_xcsg(root);

         tree.write_xml(path);
         if(!boost::filesystem::exists(path,ec)) throw std::runtime_error("Failed creating XCSG file: " + path + '\n' + ec.message());
         cout << endl << "Created XCSG file: " << path;
      }
   }
}

void shape::add_metadata(spaceio::xml_node& xml_parent, const string& model_name)
{
   // ISO8601 date and time string of current time
   time_t now = time(0);
   const size_t blen = 80;
   char buffer[blen];
   strftime(buffer,blen,"%Y-%m-%dT%H:%M:%S",gmtime(&now));
   string iso8601(buffer);

   // add some metadata
   spaceio::xml_node xml_meta = xml_parent.add_child("metadata");

   spaceio::xml_node software = xml_meta.add_child("software");
   software.add_property("name","angelcad");
   software.add_property("version",AS_CSG_version);

   spaceio::xml_node model = xml_meta.add_child("model");
   model.add_property("name",model_name);
   model.add_property("created",iso8601);
}

spaceio::xml_node shape::to_xcsg(spaceio::xml_node& xml_parent)
{
   // default implementation just adds an empty tag
   spaceio::xml_node xml_this  = xml_parent.add_child(as_typeid(this));
   xml_this.add_property("message","xcsg-unsupported");
   return xml_this;
}

tmatrix* shape::transform() const
{
   return new tmatrix(as_typeid<tmatrix>(),get_transform());
}

boundingbox* shape::box() const
{
   return new boundingbox(get_box());
}
