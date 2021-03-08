@echo off
rem TESTPATH83 <quoted path> 
rem
rem Test existence and validity of a path
rem DISABLED in 8.3: Tries to convert path to 8.3 first where possible 
rem
rem (c)Copyright 2018 by TASS
rem All rights reserved.
rem
rem PreScan(r) has been developed at TASS BV.
 

rem (DISABLED in 8.3) set INSTALLPATH_OUT=%~s1
set INSTALLPATH_OUT=%~1

setlocal
set INSTALLPATH_OUT_LONG=%~1
set ERRORCODE=0

call :TEST_EXIST "%INSTALLPATH_OUT_LONG%" 
if %ERRORCODE%==1 goto :END

call :TEST_SPACES "%INSTALLPATH_OUT%" %INSTALLPATH_OUT% 
if %ERRORCODE%==1 goto :END

if "%INSTALLPATH_OUT%"=="%INSTALLPATH_OUT_LONG%" echo Path "%INSTALLPATH_OUT%" verified OK
if not "%INSTALLPATH_OUT%"=="%INSTALLPATH_OUT_LONG%" echo Path "%INSTALLPATH_OUT%" ("%INSTALLPATH_OUT_LONG%") verified OK
echo.

goto :END

:TEST_EXIST

rem TEST_EXIST <quoted path>
rem
rem Test for existence of path

if exist %1 goto :eof

echo ### ERROR ####
echo Path %1 does not exist
set ERRORCODE=1

goto :eof

:TEST_SPACES

rem TEST_SPACES <quoted path> <unquoted path>
rem
rem Test for spaces and other delimiters in path
rem If the path contains delimiters, the remainder will spill-over to %3 etc

if "X%3"=="X" goto :eof
echo ### ERROR ####
echo Path %1 contains spaces or other delimiters
rem (DISABLED in 8.3) echo while drive "%~d1" does not support conversion to 8.3 format
set ERRORCODE=1

goto :eof


:END
exit /B %ERRORCODE%
