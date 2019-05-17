as_csg -xmldoc doc.as
doxygen Doxyfile_AngelCAD
#
# http://fart-it.sourceforge.net/
# this call to fart will replace return types written as C++ pointers
# into angelscript references
# example:
#  "pos2d * "  =>  "pos2d@ "
#
# fix return value
fart  %CPDE_USR%\doc\AngelCAD\html\*.html " *&#160;" "@&#160;" 
#
# fix arrays
#
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classshape.html\">shape</a> @[]@" "array&lt<a class=\"el\" href=\"classshape.html\">shape</a>@&gt@ " 
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classshape.html\">shape</a> @@[]" "array&lt<a class=\"el\" href=\"classshape.html\">shape</a>@&gt@ " 
#
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classshape2d.html\">shape2d</a> @[]@" "array&lt<a class=\"el\" href=\"classshape2d.html\">shape2d</a>@&gt@ " 
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classshape2d.html\">shape2d</a> @@[]" "array&lt<a class=\"el\" href=\"classshape2d.html\">shape2d</a>@&gt@ " 
#
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classsolid.html\">solid</a> @[]@" "array&lt<a class=\"el\" href=\"classsolid.html\">solid</a>@&gt@ " 
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classsolid.html\">solid</a> @@[]" "array&lt<a class=\"el\" href=\"classsolid.html\">solid</a>@&gt@ " 
#
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classpos2d.html\">pos2d</a> @[]@" "array&lt<a class=\"el\" href=\"classpos2d.html\">pos2d</a>@&gt@ "
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classpos2d.html\">pos2d</a> @@[]" "array&lt<a class=\"el\" href=\"classpos2d.html\">pos2d</a>@&gt@ "
# 
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classpos3d.html\">pos3d</a> @[]@" "array&lt<a class=\"el\" href=\"classpos3d.html\">pos3d</a>@&gt@ " 
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classpos3d.html\">pos3d</a> @@[]" "array&lt<a class=\"el\" href=\"classpos3d.html\">pos3d</a>@&gt@ " 
#
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classpface.html\">pface</a> @[]@" "array&lt<a class=\"el\" href=\"classpface.html\">pface</a>@&gt@ " 
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classpface.html\">pface</a> @@[]" "array&lt<a class=\"el\" href=\"classpface.html\">pface</a>@&gt@ " 
#
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classvec2d.html\">vec2d</a> @[]@" "array&lt<a class=\"el\" href=\"classvec2d.html\">vec2d</a>@&gt@ " 
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classvec2d.html\">vec2d</a> @@[]" "array&lt<a class=\"el\" href=\"classvec2d.html\">vec2d</a>@&gt@ " 
#
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classvec3d.html\">vec3d</a> @[]@" "array&lt<a class=\"el\" href=\"classvec3d.html\">vec3d</a>@&gt@ " 
fart  %CPDE_USR%\doc\AngelCAD\html\*.html "<a class=\"el\" href=\"classvec3d.html\">vec3d</a> @@[]" "array&lt<a class=\"el\" href=\"classvec3d.html\">vec3d</a>@&gt@ " 