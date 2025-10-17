@echo off

:: Set current directory to local script
cd /d %~dp0

:: Check Arduino CLI installation
echo Expecting Arduino CLI installed in directory: %ARDUINO_CLI_INSTALL_DIR%
echo Searching for arduino-cli executable...
set PATH=%PATH%;%ARDUINO_CLI_INSTALL_DIR%
where arduino-cli.exe
if %errorlevel% neq 0 exit /b %errorlevel%
echo.

echo Searching for yaml-merge executable...
where yaml-merge
if %errorlevel% neq 0 exit /b %errorlevel%
echo.

:: Set arduino-cli config file path
set ARDUINO_CONFIG_FILE_PATH=C:\Users\%USERNAME%\AppData\Local\Arduino15\arduino-cli.yaml
echo ARDUINO_CONFIG_FILE_PATH set to '%ARDUINO_CONFIG_FILE_PATH%'
type "%ARDUINO_CONFIG_FILE_PATH%"
echo.
echo.

set YAML_MERGE_FILE=..\arduinocli-core-esp8266.yaml
echo Adding %YAML_MERGE_FILE% to arduino-cli config...
yaml-merge --nostdin "%YAML_MERGE_FILE%" "%ARDUINO_CONFIG_FILE_PATH%" --overwrite="%ARDUINO_CONFIG_FILE_PATH%"
if %errorlevel% neq 0 exit /b %errorlevel%
type "%ARDUINO_CONFIG_FILE_PATH%"
echo.
echo.

set YAML_MERGE_FILE=..\arduinocli-core-esp32.yaml
echo Adding %YAML_MERGE_FILE% to arduino-cli config...
yaml-merge --nostdin "%YAML_MERGE_FILE%" "%ARDUINO_CONFIG_FILE_PATH%" --overwrite="%ARDUINO_CONFIG_FILE_PATH%"
if %errorlevel% neq 0 exit /b %errorlevel%
type "%ARDUINO_CONFIG_FILE_PATH%"
echo.
echo.

echo arduino update-index...
arduino-cli core update-index
if %errorlevel% neq 0 exit /b %errorlevel%
echo.
echo.

echo Installing arduino:avr core...
REM Use `--skip-post-install` on AppVeyor to skip UAC prompt which is blocking the build.
arduino-cli core install arduino:avr --skip-post-install
if %errorlevel% neq 0 exit /b %errorlevel%
echo.
echo.

echo Installing esp8266:esp8266 core...
arduino-cli core install esp8266:esp8266
if %errorlevel% neq 0 exit /b %errorlevel%
echo.
echo.

echo Installing esp32:esp32 core...
arduino-cli core install esp32:esp32
if %errorlevel% neq 0 exit /b %errorlevel%
echo.
echo.

echo Listing all installed cores...
arduino-cli core list
if %errorlevel% neq 0 exit /b %errorlevel%
echo.
echo.
