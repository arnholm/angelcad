as_csg -xmldoc doc.as
doxygen Doxyfile_AngelCAD
#
# http://fart-it.sourceforge.net/
# this call to fart will replace return types written as C++ pointers
# into angelscript references
# example:
#  "pos2d * "  =>  "pos2d@ "
#
fart  %CPDE_USR%\doc\AngelCAD\html\*.html " *&#160;" "@&#160;" 
