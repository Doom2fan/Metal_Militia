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

IF EXIST "%MAIN_7Z%/CO-Metal_Militia/" (
    RMDIR CO-Metal_Militia /S /Q
)
IF EXIST "%MAIN_7Z%/CO-Metal_Militia.PK7" (
    DEL "%MAIN_7Z%/CO-Metal_Militia.PK7"
)

ECHO Creating temporary directories
MKDIR CO-Metal_Militia
MKDIR CO-Metal_Militia\README
MKDIR CO-Metal_Militia\CO-Metal_Militia-Licenses

ECHO Compiling CO-Metal_Militia.PK7
CD %PK7SOURCE%
%PROG_7Z% a -tzip "%MAIN_7Z%/CO-Metal_Militia.PK7" "*" -mx0 -r -x!*.DB -X!*.DBS -X!*.WAD.BACKUP* -X!*.TMP*
CD %MAIN_7Z%

DEL CO-Metal_Militia.7Z /Q
ECHO Creating CO-Metal_Militia-Licenses.ZIP
ECHO F | XCOPY LICENSE "%MAIN_7Z%/CO-Metal_Militia/CO-Metal_Militia-Licenses/Assets.txt" /Q /Y
ECHO F | XCOPY C_Source\LICENSE.md "%MAIN_7Z%/CO-Metal_Militia/CO-Metal_Militia-Licenses/C code-ACS library source.txt" /Q /Y
%PROG_7Z% A -t7z "%MAIN_7Z%/CO-Metal_Militia/README/CO-Metal_Militia-Licenses.ZIP" -m0=Deflate -mx0 -ms=off "%MAIN_7Z%/CO-Metal_Militia/CO-Metal_Militia-Licenses/*"
RMDIR CO-Metal_Militia\CO-Metal_Militia-Licenses /S /Q

ECHO Creating CO-Metal_Militia-README.ZIP
XCOPY CO-Metal_Militia-Bugs.TXT "%MAIN_7Z%/CO-Metal_Militia/README"
XCOPY CO-Metal_Militia-TODO.TXT "%MAIN_7Z%/CO-Metal_Militia/README"
XCOPY CO-Metal_Militia-README.TXT "%MAIN_7Z%/CO-Metal_Militia/README"
%PROG_7Z% A -t7z "%MAIN_7Z%/CO-Metal_Militia/CO-Metal_Militia-README.ZIP" -m0=Deflate -mx0 -ms=off "%MAIN_7Z%/CO-Metal_Militia/README/*"
RMDIR CO-Metal_Militia\README /S /Q

ECHO Creating CO-Metal_Militia.7Z
XCOPY CO-Metal_Militia.PK7 "%MAIN_7Z%/CO-Metal_Militia" /Q /Y
%PROG_7Z% A -t7z "%MAIN_7Z%/CO-Metal_Militia.7Z" -m0=LZMA2 -mx9 -ms=off "%MAIN_7Z%/CO-Metal_Militia/*"

ECHO Erasing temporary files and directories
RMDIR CO-Metal_Militia /S /Q
DEL "%MAIN_7Z%\CO-Metal_Militia.PK7" /Q