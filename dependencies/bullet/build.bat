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
             -S %SRC_DIR% -B %BUILD_DIR%

echo Bullet build succesfully generated

:: Build OGRE library
echo Compiling Bullet library...

msbuild %BULLET_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug
msbuild %BULLET_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release 

echo Bullet library compiled

goto end

:done

:: Confirmation message
echo Bullet already built and compiled

:end