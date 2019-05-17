@echo off
REM
REM Generate AngelCAD documentation
REM
REM Create/update angelcad_xmldoc.xml and angelcad.h
as_csg -xmldoc doc.as
REM
REM Run doxygen using angelcad.h as input
doxygen Doxyfile_AngelCAD
REM
REM Fix return types 
REM    from C++ pointer          : "pos2d * "
REM     to AngelScript reference : "pos2d@ "
REM
REM Using http://fart-it.sourceforge.net/
fart  %CPDE_USR%\doc\AngelCAD\html\*.html " *&#160;" "@&#160;" 
fart  %CPDE_USR%\doc\AngelCAD\html\*.html ">* " ">@ " 
REM 
REM Because of the replace, run hhc.exe again
echo Generating angelcad.chm (second run)
"C:/Program Files (x86)/HTML Help Workshop/hhc.exe"  %CPDE_USR%\doc\AngelCAD\html\index.hhp
echo ===============================
echo AngeCAD documentation complete.
echo ===============================
