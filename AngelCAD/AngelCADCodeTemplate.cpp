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
   
#include "AngelCADCodeTemplate.h"

AngelCADCodeTemplate::AngelCADCodeTemplate()
{
   //ctor
}

AngelCADCodeTemplate::~AngelCADCodeTemplate()
{
   //dtor
}

/*
wxString AngelCADCodeTemplate::GetCSGText()
{
   wxString text;

   text += "// AngelCAD. Shift+F1 for help.\n";
   text += "\n";
   text += "shape@ main_shape()\n";
   text += "{\n";
   text += "   // Example code follows. This is where your model is built.\n";
   text += "   // Use your own helper functions if required.\n";
   text += "   // TODO: Remove or edit the lines below to do what you want.\n";
   text += "   \n";
   text += "   double height       = 200;\n";
   text += "   double radius       = 5;\n";
   text += "   double head_radius  = 20;\n";
   text += "   \n";
   text += "   // Notice the use of '@', indicating the variable is a reference.\n";
   text += "   // All 2d,3d objects + transformations require '@' as shown.\n";
   text += "   \n";
   text += "   cylinder@ stick = cylinder(height,radius);  // create a cylinder\n";
   text += "   solid@ head     = sphere(head_radius);      // create a sphere\n";
   text += "   translate@ tr   = translate(0,0,stick.h()); // create a transformation\n";
   text += "\n";
   text += "   // assemble, rotate and return the model for export\n";
   text += "   return rotate_y(deg:30) * union3d(stick, tr*head);\n";
   text += "}\n";
   text += "\n";
   text += "void main()\n";
   text += "{\n";
   text += "   shape@ obj = main_shape();\n";
   text += "   obj.write_xcsg(GetInputFullPath(),secant_tolerance:-1.0);\n";
   text += "}\n";

   return text;
}
*/

wxString AngelCADCodeTemplate::GetCSGText()
{
   wxString text;

   text += "// AngelCAD code.\n";
   text += "\n";
   text += "shape@ main_shape()\n";
   text += "{\n";
   text += "   // create cube & sphere in default positions\n";
   text += "   double d = 100;\n";
   text += "   solid@ mycub = cube(size:d);\n";
   text += "   solid@ mysph = sphere(r:d*0.8);\n";
   text += "\n";
   text += "   // move the sphere in z-direction and subtract from cube\n";
   text += "   return mycub - translate(0,0,d)*mysph;\n";
   text += "}\n";
   text += "\n";
   text += "void main()\n";
   text += "{\n";
   text += "   shape@ obj = main_shape();\n";
   text += "   obj.write_xcsg(GetInputFullPath(),secant_tolerance:-1.0);\n";
   text += "}\n";
   return text;
}
