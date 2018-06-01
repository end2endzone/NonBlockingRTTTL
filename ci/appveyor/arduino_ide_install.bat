@echo off
REM 

@echo off
cd /d %~dp0

set ARDUINO_IDE_VERSION=1.8.4

:: Download
echo Downloading arduino-%ARDUINO_IDE_VERSION%-windows.zip...
curl -fsS -o %TEMP%\arduino-%ARDUINO_IDE_VERSION%-windows.zip "https://downloads.arduino.cc/arduino-%ARDUINO_IDE_VERSION%-windows.zip"

:: Installing
set ARDUINO_INSTALL_DIR=%USERPROFILE%\Desktop\arduino-%ARDUINO_IDE_VERSION%
echo Installing Arduino IDE to '%ARDUINO_INSTALL_DIR%'...
7z x %TEMP%\arduino-%ARDUINO_IDE_VERSION%-windows.zip "-o%USERPROFILE%\Desktop"

:: Add Arduino IDE to PATH
set PATH=%ARDUINO_INSTALL_DIR%;%PATH%

:: Create libraries folder for current user
mkdir %USERPROFILE%\Documents\Arduino\libraries >NUL 2>NUL
