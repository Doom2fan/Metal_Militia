@ECHO OFF
SETLOCAL

REM ACS Stuff
ECHO Cleaning ACS library files (.bin, .ir, .o, etc. files)
MAKE cleanall
ECHO Compiling ACS libraries
MAKE all

REM 7z stuff
SET MAIN_7Z=%CD%
SET PROG_7Z="%CD%/Tools/7z/7z"
SET PK7SOURCE="%CD%/PK7_Source"

IF EXIST "%MAIN_7Z%/D-Master_Exploder/" (
    RMDIR D-Master_Exploder /S /Q
)
IF EXIST "%MAIN_7Z%/D-Master_Exploder.PK7" (
    DEL "%MAIN_7Z%/D-Master_Exploder.PK7"
)

ECHO Creating temporary directories
MKDIR D-Master_Exploder
MKDIR D-Master_Exploder\README
MKDIR D-Master_Exploder\D-Master_Exploder-Licenses

ECHO Compiling D-Master_Exploder.PK7
CD %PK7SOURCE%
%PROG_7Z% a -tzip "%MAIN_7Z%/D-Master_Exploder.PK7" "*" -mx0 -r -x!*.DB -X!*.DBS -X!*.WAD.BACKUP* -X!*.TMP*
CD %MAIN_7Z%

DEL D-Master_Exploder.7Z /Q
ECHO Creating D-Master_Exploder-Licenses.ZIP
ECHO F | XCOPY LICENSE "%MAIN_7Z%/D-Master_Exploder/D-Master_Exploder-Licenses/Assets.txt" /Q /Y
ECHO F | XCOPY C_Source\LICENSE.md "%MAIN_7Z%/D-Master_Exploder/D-Master_Exploder-Licenses/C code-ACS library source.txt" /Q /Y
%PROG_7Z% A -t7z "%MAIN_7Z%/D-Master_Exploder/README/D-Master_Exploder-Licenses.ZIP" -m0=Deflate -mx0 -ms=off "%MAIN_7Z%/D-Master_Exploder/D-Master_Exploder-Licenses/*"
RMDIR D-Master_Exploder\D-Master_Exploder-Licenses /S /Q

ECHO Creating D-Master_Exploder-README.ZIP
XCOPY D-Master_Exploder-Bugs.TXT "%MAIN_7Z%/D-Master_Exploder/README"
XCOPY D-Master_Exploder-TODO.TXT "%MAIN_7Z%/D-Master_Exploder/README"
XCOPY D-Master_Exploder-README.TXT "%MAIN_7Z%/D-Master_Exploder/README"
%PROG_7Z% A -t7z "%MAIN_7Z%/D-Master_Exploder/D-Master_Exploder-README.ZIP" -m0=Deflate -mx0 -ms=off "%MAIN_7Z%/D-Master_Exploder/README/*"
RMDIR D-Master_Exploder\README /S /Q

ECHO Creating D-Master_Exploder.7Z
XCOPY D-Master_Exploder.PK7 "%MAIN_7Z%/D-Master_Exploder" /Q /Y
%PROG_7Z% A -t7z "%MAIN_7Z%/D-Master_Exploder.7Z" -m0=LZMA2 -mx9 -ms=off "%MAIN_7Z%/D-Master_Exploder/*"

ECHO Erasing temporary files and directories
RMDIR D-Master_Exploder /S /Q
DEL "%MAIN_7Z%\D-Master_Exploder.PK7" /Q