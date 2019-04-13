To install the AngelScript CSG language syntax highlight 
definition file in Notepad++, please do as follows in Notepad++:

Language -> Define your language...

Press the "Import..." button and find the file "AngelScriptCSG_NPP.xml" and import it.
Exit and restart Notepad++, and open any *.as file (try the samples).

It is suggested to associate *.as files with Notepad++ so when you 
double click an *.as file it opens in Notepad++ with the syntax highlighting.

You can use the Run ... menu in Notepad++ to run as_csg or you can do it from the 
Windows command line:

> C:\path_to_your_installation\as_csg "filename".as

it generates "filename".csg which you can open in OpenSCAD.

