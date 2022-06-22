@echo off

:: Batch variables
set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set BULLET_BUILD_SOL=.\build\BULLET_PHYSICS.sln

set CMAKE_EXEC=..\cmake\bin\cmake.exe

:: Make the build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %BULLET_BUILD_SOL% goto done

:: Generate the build
echo Generating Bullet build...

%CMAKE_EXEC% -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -D BUILD_BULLET2_DEMOS:BOOL="1" ^
             -D BUILD_CPU_DEMOS:BOOL="0" ^
             -D BUILD_OPENGL3_DEMOS:BOOL="1" ^
             -D USE_MSVC_RUNTIME_LIBRARY_DLL:BOOL="1" ^
             -S %SRC_DIR% -B %BUILD_DIR%

echo Bullet build succesfully generated

:: Build Bullet library
echo Compiling Bullet library...

msbuild %BULLET_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release 
if %RELEASE_ENGINE% == false msbuild %BULLET_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug

echo Bullet library compiled

goto end

:done
:: Confirmation message
echo Bullet already built and compiled

:end