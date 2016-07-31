@ECHO OFF
SETLOCAL

SET MAIN_7Z=%CD%
SET PROG_7Z="%CD%/Tools/7z/7z"
SET PK7SOURCE="%CD%/PK7_Source"

DEL "%MAIN_7Z%/D-Master_Exploder.PK7" 2>nul
DEL "%MAIN_7Z%/D-Master_Exploder_Zandro.PK7" 2>nul
CD %PK7SOURCE%
%PROG_7Z% a -tzip "%MAIN_7Z%/D-Master_Exploder.PK7" "*" -mx0 -r -x!*.DB -X!*.DBS -X!*.WAD.BACKUP* -X!*.TMP*