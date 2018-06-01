@echo off
REM **************************************
echo Generate ZIP package
REM **************************************

REM Finding root folder of repository
cd /d %~dp0
cd ..\..
set REPOSITORY_ROOT=%cd%

mkdir %REPOSITORY_ROOT%\deploy >NUL 2>NUL

::Set product version
call %REPOSITORY_ROOT%\version_info.bat

set outfile="%REPOSITORY_ROOT%\deploy\NonBlockingRtttl v%PRODUCT_VERSION%.zip"

set infiles="%REPOSITORY_ROOT%"

echo Generating portable install %outfile%
echo using the following input files:
echo %infiles%
echo.
del %outfile% >NUL 2>NUL
call "C:\Program Files\7-Zip\7z.exe" a -bd %outfile% %infiles%

echo.
