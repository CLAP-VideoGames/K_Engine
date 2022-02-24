@echo off

:: Batch variables
set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set CEGUI_BUILD_SOL=.\build\cegui.sln

set CMAKE_EXEC=..\cmake\bin\cmake.exe

:: Make the build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %CEGUI_BUILD_SOL% goto done

:: Generate the build
echo Generating CEGUI build...

%CMAKE_EXEC% -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -S %SRC_DIR% -B %BUILD_DIR%

echo CEGUI build succesfully generated

:: Build OGRE library
echo Compiling CEGUI library...

msbuild %CEGUI_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug
msbuild %CEGUI_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release 

echo CEGUI library compiled

goto end

:done

:: Confirmation message
echo CEGUI already built and compiled

:end