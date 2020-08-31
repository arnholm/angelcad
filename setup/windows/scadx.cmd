@echo off
REM 
REM scadx.cmd 
REM =========
REM Create an STL file from OpenSCAD *.scad file REM Without using OpenSCAD boolean engine.
REM Use AngelCADs xcsg instead
REM Note: Some OpenSCAD commands not supported: import, surface, text
REM
REM Author: Carsten Arnholm, August 2020
REM
REM Dependencies
REM   - OpenSCAD must be installed https://www.openscad.org/
REM   - AngelCAD must be installed https://arnholm.github.io/angelcad-docs/
REM   - SVG viewer must be installed (Brave browser recommeded https://brave.com/ )
REM =====
set openscad="C:\Program Files\OpenSCAD\openscad.exe"
set xcsg="D:\cpde_usr\bin\xcsg.exe"
set angelview="D:\cpde_usr\bin\angelview.exe"
set svg_viewer="C:\Program Files (x86)\BraveSoftware\Brave-Browser\Application\brave.exe" 
REM =====
REM
REM Get the file name parameter: example.scad
set scad_file=%1%
for %%A in (%scad_file%) do (
    set Name=%%~nA
    set Ext=%%~xA
)
REM Echo %Name%
REM Echo %Ext%
set csg_file="%Name%.csg"
set xcsg_file="%Name%.xcsg"
set stl_file="%Name%.stl"
set svg_file="%Name%.svg"
Echo %csg_file%
REM goto finish
REM check input
if ".scad" == "%Ext%"  goto process 
echo Error: Input file has wrong type, must be: .scad
goto finish

:process 
echo.
echo.Running OpenSCAD --o %csg_file% %scad_file%
%openscad% --o %csg_file% %scad_file%
if %ERRORLEVEL% EQU 0 (
    echo.Running xcsg --stl --svg %csg_file%
    %xcsg% --stl --svg %csg_file%
    if %ERRORLEVEL% EQU 0 (
        set command="cmd /c echo Created file: @path @fdate @ftime Size=@fsize bytes"
        IF EXIST %stl_file% (
            forfiles /M %stl_file%   /c %command%
            rm -f %csg_file%
            rm -f %xcsg_file%
            start %angelview% %stl_file% 
        )
        IF EXIST %svg_file% (
            forfiles /M %svg_file%  /c %command%
            rm -f %csg_file%
            rm -f %xcsg_file%
            echo Starting SVG viewer...please wait
            start %svg_viewer% %svg_file% 
        )
    )
)  

:finish