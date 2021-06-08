@if not "%MINGW_ROOT%" == "" (@set "PATH=%PATH%;%MINGW_ROOT%")

cd .

if "%1"=="" ("C:\PROGRA~1\MATLAB\R2019a\bin\win64\gmake"  -f W07_Neighborhood_cs.mk all) else ("C:\PROGRA~1\MATLAB\R2019a\bin\win64\gmake"  -f W07_Neighborhood_cs.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1
