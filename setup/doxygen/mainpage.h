#ifndef MAINPAGE_H
#define MAINPAGE_H

/*!
\mainpage AngelCAD - script based 3D solid modeller

AngelCAD is an open source 3D solid modeller based on the <a href="https://en.wikipedia.org/wiki/Constructive_solid_geometry">Constructive Solid Geometry (CSG)</a> modelling technique, expressed in the <a href="http://www.angelcode.com/angelscript/sdk/docs/manual/doc_script.html">AngelScript language</a>. The software is used for creating 3D models in STL or other file formats.

\image html angelcad_ide.png


\section language_sec AngelCAD language extension to AngelScript

AngelCAD uses the <a href="http://www.angelcode.com/angelscript/sdk/docs/manual/doc_script.html">AngelScript</a> language to express 3D model designs. It is a powerful language based on the well known syntax of languages such as C++ or Java. It is a strongly typed language allowing the user  to declare variables for parametric modelling or to hold parts of the design. Standard constructs such as for-loops and if-statements are available, plus much more. See the <a href="http://www.angelcode.com/angelscript/sdk/docs/manual/doc_script.html">AngelScript language description</a> for details. 

The AngelCAD language extension adds 3D solid modelling features to the general purpose AngelScript language. This includes modelling primitives such as 'cube', 'sphere', 'polyhedron' and more, plus operators such as 'union3d' and 'hull3d'. For a full overview of the features, see the 'Classes' page of this manual. See also the AngelCAD sample scripts available from the <a href="https://github.com/arnholm/angelcad-samples/">angelcad-samples</a> repository.


\section License
AngelCAD is Copyright (c) 2015 - 2020 Carsten Arnholm. The software is distributed under the <a href="https://www.gnu.org/licenses/gpl.html">GNU General Public License version 3.</a> 


\section gettingstarted_sec Getting Started

To install the software, download the pre-built binaries from the Github releases section. Extract the downloaded ZIP-file and run the setup.exe (Windows) or setup.sh shell script (Linux). Then try some of the sample scripts from the <a href="https://github.com/arnholm/angelcad-samples">angelcad-samples</a> GitHub repository. One of the examples is "csg_wikipadia.as",shown below and in the image at the top of the page.
\code

shape@ main_shape()
{
   // intersection of cube and sphere
   cube@     cu = cube(size:45,center:true);
   sphere@   sp = sphere(r:30);
   solid@  cusp = cu & sp;                   // '&' : intersection

   // union of 3 cylinders
   cylinder@ cy = cylinder(r:17,h:50,center:true);
   solid@   cy2 = cy  + rotate_x(deg:90)*cy;
   solid@   cy3 = cy2 + rotate_y(deg:90)*cy; // '+' : union

   // difference of the 2 above
   return cusp - cy3;                        // '-' : difference
}

void main()
{
	shape@ obj = main_shape();
	obj.write_xcsg(GetInputFullPath(),secant_tolerance:0.01);
}

\endcode

Some rules
- You *must* have a "void main()" function. 
- It is recommended to use a "shape@ main_shape()" function that returns the final object created.
- The secant tolerance controls the density of the generated mesh
- You can use as many additional functions as you need.
- Note the use of handles such as shape@, cylinder@ etc. The use of the "@" character with most AngelCAD objects signifies a reference variable, you can think of it as a kind of smart pointer to an object as it manages itself automatically and does not require explicit deletion.


\section technology_sec Technology 
AngelCAD uses <a href="https://github.com/arnholm/xcsg">xcsg</a> for 3d computations. xcsg is based on the <a href="https://github.com/arnholm/carve">carve library</a> created by Tobias Sargeant. xcsg also uses qhull by C.B. Barber and libtess2 by Mikko Mononen. The AngelCAD language interpreter - as_csg - is based on the AngelScript language by Andreas Jönsson, as_csg extends the language with 3d modelling types and operations for constructive solid geometry. The AngelCAD IDE and Viewer applications use the <a href="https://wxwidgets.org/">wxWidgets</a> cross-platform GUI library to create native GUI for Windows and Linux.

*/


#endif
