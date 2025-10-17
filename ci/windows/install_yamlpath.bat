@echo off

:: Install yamlpath.
:: https://github.com/wwkimball/yamlpath
:: https://pypi.org/project/yamlpath/

:: Search for py.exe
:: NOTE: THIS STEP IS WINDOWS ONLY. Linux does not have a python launcher.
echo Validate if python launcher is installed
where py.exe >NUL 2>NUL
if errorlevel 1 (
  echo Command failed. Please install python and python launcher to continue.
  exit /B %errorlevel%
)
echo Found python launcher.
echo.

:: Search for python.exe
echo Validate if python is installed
where python.exe >NUL 2>NUL
echo Found python interpreter
python --version
echo.

:: Search for pip.exe
echo Validate if pip is installed
where pip.exe >NUL 2>NUL
if errorlevel 1 (
  echo Command failed. Please install pip ^(Package Installer Python^) to continue.
  exit /B %errorlevel%
)
echo.

:: Installing yamlpath.
echo Proceeding with instaling yamlpath...
pip install yamlpath
if errorlevel 1 (
  echo Command failed. An error was found while installing yamlpath.
  exit /B %errorlevel%
)
echo.

echo yamlpath was installed on the system without error.
echo.
