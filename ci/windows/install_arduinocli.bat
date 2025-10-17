@echo off
cd /d %~dp0

:: Set download filename
set ARDUINO_CLI_FILENAME=arduino-cli_latest_Windows_64bit.zip

:: Download
echo Downloading file https://downloads.arduino.cc/arduino-cli/%ARDUINO_CLI_FILENAME%
curl -fsSL -o "%TEMP%\%ARDUINO_CLI_FILENAME%" "https://downloads.arduino.cc/arduino-cli/%ARDUINO_CLI_FILENAME%"
if %errorlevel% neq 0 exit /b %errorlevel%
echo.
echo.

:: Installing
set ARDUINO_CLI_INSTALL_DIR=%USERPROFILE%\Desktop\arduino-cli
echo Installing Arduino CLI to directory: %ARDUINO_CLI_INSTALL_DIR%
7z x -y "%TEMP%\%ARDUINO_CLI_FILENAME%" "-o%ARDUINO_CLI_INSTALL_DIR%"
if %errorlevel% neq 0 exit /b %errorlevel%
echo.
echo.

:: Verify
echo Searching for arduino cli executable...
set PATH=%ARDUINO_CLI_INSTALL_DIR%;%PATH%
where arduino-cli.exe
if %errorlevel% neq 0 exit /b %errorlevel%
arduino-cli version
echo.
echo.

echo Initialize configuration file...
REM Expecting something like:  Config file written to: C:\Users\%USERNAME%\AppData\Local\Arduino15\arduino-cli.yaml
arduino-cli config init --overwrite
if %errorlevel% neq 0 exit /b %errorlevel%
echo.
echo.
