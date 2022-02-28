@echo off

:: Batch variables
set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set CEGUI_DEPEN_DIR=..\src\dependecies\
set CEGUI_DEPEN_BUILD_SOL=.\build\CEGUI-DEPS.sln

set CMAKE_EXEC=..\..\cmake\bin\cmake.exe

set CEGUI_CONFIG_PATH=.\build\cegui\include\CEGUI\Config.h

:: Make the build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %CEGUI_DEPEN_BUILD_SOL% goto done

:: Generate the build
echo Generating CEGUI dependencies build...

%CMAKE_EXEC% -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -D CEGUI_BUILD_DEVIL:BOOL="1" ^
             -D CEGUI_BUILD_EXPAT:BOOL="1" ^
             -D CEGUI_BUILD_FREETYPE2:BOOL="1" ^
             -D CEGUI_BUILD_GLEW:BOOL="1" ^
             -D CEGUI_BUILD_GLFW:BOOL="1" ^
             -D CEGUI_BUILD_GLM:BOOL="1" ^
             -D CEGUI_BUILD_LUA:BOOL="0" ^
             -D CEGUI_BUILD_PCRE:BOOL="1" ^
             -D CEGUI_BUILD_SILLY:BOOL="1" ^
             -S %SRC_DIR% -B %BUILD_DIR%

echo CEGUI dependencies build succesfully generated

:: Build CEGUI dependencies
echo Compiling CEGUI dependencies...

msbuild %CEGUI_DEPEN_BUILD_SOL%  /p:platform=x64 /p:configuration=Debug
msbuild %CEGUI_DEPEN_BUILD_SOL%  /p:platform=x64 /p:configuration=Release 

echo CEGUI dependencies compiled

goto end

:done

:: Confirmation message
echo CEGUI dependencies already built and compiled

:end