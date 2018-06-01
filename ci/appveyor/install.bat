@echo off

set ARDUINO_LIBRARY_NAME=NonBlockingRtttl

echo Installing %ARDUINO_LIBRARY_NAME% for current user

:: Navigate to root directory of repository
cd /d %~dp0
cd ..\..

:: Copy
xcopy /S /Y %cd% %USERPROFILE%\Documents\Arduino\libraries\%ARDUINO_LIBRARY_NAME%\
