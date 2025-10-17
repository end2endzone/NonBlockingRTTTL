@echo off

:: Set PRODUCT_SOURCE_DIR root directory
setlocal enabledelayedexpansion
if "%PRODUCT_SOURCE_DIR%"=="" (
  :: Delayed expansion is required within parentheses https://superuser.com/questions/78496/variables-in-batch-file-not-being-set-when-inside-if
  cd /d "%~dp0"
  cd ..\..
  set PRODUCT_SOURCE_DIR=!CD!
  cd ..\..
  echo PRODUCT_SOURCE_DIR set to '!PRODUCT_SOURCE_DIR!'.
)
endlocal & set PRODUCT_SOURCE_DIR=%PRODUCT_SOURCE_DIR%
echo.

:: Create libraries folder for current user
mkdir %USERPROFILE%\Documents\Arduino\libraries >NUL 2>NUL

:: Navigate to root directory of repository
cd /d %~dp0
cd ..\..

setlocal

:: Copy properties as environment variables
FOR /F "tokens=1,2 delims==" %%G IN (library.properties) DO (set %%G=%%H) 
echo Installing %name%-%version% for current user

:: Cleanup
set installdir=%USERPROFILE%\Documents\Arduino\libraries\%name%-%version%
IF EXIST %installdir% (
  rmdir /S /Q %installdir%
)

:: Copy
xcopy /S /Y %cd% %installdir%\

::Cleanup
IF EXIST %installdir%\build (
  rmdir /S /Q %installdir%\build
)
IF EXIST %installdir%\third_parties (
  rmdir /S /Q %installdir%\third_parties
)

endlocal
