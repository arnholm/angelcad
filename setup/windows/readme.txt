AngelCAD install instructions - Windows
---------------------------------------

Please note that AngelCAD is a 64bit application
and will not run under 32bit Windows.

If you have 64bit windows and still having problems 
starting AngelCAD, you may be missing a runtime 
redistributable on your computer. If so, download 
and run  vc_redist.x64.exe from

"The latest supported Visual C++ downloads"
https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads
i.e. https://aka.ms/vs/16/release/vc_redist.x64.exe

It only needs to be run once per computer.

To uninstall AngelCAD, use the uninstall icon in the 
Windows Start Menu, in the AngeCAD group.

Please observe that AngelCAD comes with a couple of
programs that must be configured properly in the AngelCAD editor:

as_csg.exe 	  : AngelCAD language compiler
AngelView.exe : AngelCAD 3d file viewer
xcsg.exe	  : AngelCAD boolean engine
dxfread.exe   : AngelCAD DXF reader
polyfix.exe   : AngelCAD mesh repair utility

These programs are found in the AngelCAD installation folder, 
If you install in the default folder: C:\Program Files\AngelCAD

