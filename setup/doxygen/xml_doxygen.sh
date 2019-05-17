#!/bin/bash
as_csg -xmldoc doc.as
doxygen Doxyfile_AngelCAD
#
# this call to rpl will replace return types written as C++ pointers
# into angelscript references
# example:
#  "pos2d * "  =>  "pos2d@ "
#
rpl  " *&#160;" "@&#160;" $CPDE_USR/doc/AngelCAD/html/*.html
