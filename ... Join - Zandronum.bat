@ECHO OFF
SETLOCAL

SET PROG_ZANDRONUM="%DOOMDIR%\Zandronum\zandronum.EXE"

CALL %PROG_ZANDRONUM% -file "%CD%/PK7_Source" -connect %*