@echo off

:: Batch variables
set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set OGRE_BUILD_SOL=.\build\OGRE.sln
set SDL2_BUILD_SOL=.\build\SDL2-build\SDL2.sln

set CMAKE_EXEC=..\cmake\bin\cmake.exe

:: Make the build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %OGRE_BUILD_SOL% goto done

:: Generate the build
echo Generating OGRE & SDL2 build...

%CMAKE_EXEC% -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -D DCMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -D OGRE_BUILD_COMPONENT_BITES:BOOL=0 ^
             -D OGRE_BUILD_PLUGIN_DOT_SCENE:BOOL=0 ^
             -D OGRE_BUILD_RENDERSYSTEM_D3D11:BOOL=0 ^
             -D OGRE_BUILD_RENDERSYSTEM_D3D9:BOOL=0 ^
             -D OGRE_BUILD_RENDERSYSTEM_TINY:BOOL=0 ^
             -D OGRE_BUILD_RENDERSYSTEM_VULKAN:BOOL=0 ^
             -D OGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL=1 ^
             -D OGRE_BUILD_SAMPLES:BOOL=0 ^
             -D OGRE_INSTALL_SAMPLES:BOOL=0 ^
             -S %SRC_DIR% -B %BUILD_DIR%

echo OGRE & SDL2 build succesfully generated

:: Build OGRE library
echo Compiling OGRE library...

msbuild %OGRE_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug
msbuild %OGRE_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release 

echo OGRE library compiled

:: Build SDL2 library
echo Compiling SDL2 library...

msbuild %SDL2_BUILD_SOL% /p:platform=x64 /p:configuration=Debug
msbuild %SDL2_BUILD_SOL% /p:platform=x64 /p:configuration=Release 

echo SDL2 library compiled

goto end

:done

:: Confirmation message
echo OGRE & SDL2 already built and compiled

:end