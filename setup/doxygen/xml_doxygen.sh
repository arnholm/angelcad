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
html_dir="$CPDE_USR/doc/AngelCAD/html"
rpl  " *&#160;" "@&#160;" $html_dir/*.html
rpl   ">* " ">@ "  $html_dir/*.html
#
html_index="$html_dir/index.html"
echo "======================================="
echo "AngeCAD documentation complete         "
echo "   to open   : xdg-open $html_index    "
echo "   or run as : xml_doxygen.sh open     "
echo "======================================="
if [[ "$1" == "open" ]]
then
    xdg-open "$html_index"
fi
