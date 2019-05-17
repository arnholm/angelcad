#!/bin/bash
#
# Generate AngelCAD documentation
#
# Create/update angelcad_xmldoc.xml and angelcad.h
as_csg -xmldoc doc.as
#
# Run doxygen using angelcad.h as input, 
# do not try generating  compiled HTML as there is no 
# compiler and it disables search in the basic HTML files
export ANGELCAD_VERSION="`${CPDE_USR}/bin/as_csg --version`"
export GENERATE_HTMLHELP=NO
doxygen Doxyfile_AngelCAD
#
# Fix return types 
#    from C++ pointer          : "pos2d * "
#     to AngelScript reference : "pos2d@ "
#
#
rpl  " *&#160;" "@&#160;" $CPDE_USR/doc/AngelCAD/html/*.html
rpl   ">* " ">@ "  $CPDE_USR/doc/AngelCAD/html/*.html
echo "==============================="
echo "AngeCAD documentation complete."
echo "==============================="