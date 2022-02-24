@echo on

:: Batch variables
set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set OGRE_BUILD_SOL=.\build\OGRE.sln
set SDL2_BUILD_SOL=.\build\SDL2-build\SDL2.sln

set CMAKE_EXEC=..\cmake\bin\cmake.exe

:: Make the build directory
@REM if exist %BUILD_DIR% goto done
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

:: Generate the build
%CMAKE_EXEC% -D CMAKE_CONFIGURATION_TYPES:STRING="Debug;Release" ^
             -D OGRE_BUILD_COMPONENT_BITES:BOOL="0" ^
             -D OGRE_BUILD_SAMPLES:BOOL="0" ^
             -D OGRE_INSTALL_SAMPLES:BOOL="0" ^
             -D OGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="1" ^
             -D OGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="1" ^
             -D OGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" ^
             -S %SRC_DIR% -B %BUILD_DIR%

:: Build OGRE library
msbuild %OGRE_BUILD_SOL% /p:platform="x64" /p:configuration="Debug"
msbuild %OGRE_BUILD_SOL% /p:platform="x64" /p:configuration="Release" 

:: Confirmation message
echo "OGRE compilado"

:: Build SDL2 library
msbuild %SDL2_BUILD_SOL% /p:platform="x64" /p:configuration="Debug"
msbuild %SDL2_BUILD_SOL% /p:platform="x64" /p:configuration="Release" 

:: Confirmation message
echo "SDL2 compilado"

goto end

:done

:: Confirmation message
echo "OGRE y SDL2 ya compilado"

:end