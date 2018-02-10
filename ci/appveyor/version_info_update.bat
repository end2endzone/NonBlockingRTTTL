@echo off

echo =======================================================================
echo Finding root folder of repository
echo =======================================================================
cd /d %~dp0
cd ..\..
set REPOSITORY_ROOT=%cd%
echo REPOSITORY_ROOT=%REPOSITORY_ROOT%
echo done.
echo.

REM **************** version_info.bat ****************
set OUTPUTFILE=%REPOSITORY_ROOT%\version_info.bat
echo Updating %OUTPUTFILE%...
echo set PRODUCT_VERSION=%APPVEYOR_BUILD_VERSION%>%OUTPUTFILE%
set OUTPUTFILE=
echo done.
echo.
