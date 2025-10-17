@echo off

:: Validate GitHub CI's environment
if "%GITHUB_WORKSPACE%"=="" (
  echo Please define 'GITHUB_WORKSPACE' environment variable.
  exit /B 1
)

:: Call matching script for windows
call "%GITHUB_WORKSPACE%\ci\windows\%~n0.bat"
if %errorlevel% neq 0 exit /b %errorlevel%

:: Remember installation directory
echo Remember ARDUINO_CLI_INSTALL_DIR as %ARDUINO_CLI_INSTALL_DIR% in %GITHUB_ENV%
echo ARDUINO_CLI_INSTALL_DIR=%ARDUINO_CLI_INSTALL_DIR%>> %GITHUB_ENV%
