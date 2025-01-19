@echo off

:: Batch variables
set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set SDL2_BUILD_SOL=.\build\SDL2.sln

set CMAKE_EXEC=..\cmake\bin\cmake.exe

:: Make the build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %OGRE_BUILD_SOL% goto done

:: Generate the build
echo Generating SDL2 build...

%CMAKE_EXEC% -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -D SDL_DIRECTX:BOOL=0 ^
             -D SDL_OPENGL:BOOL=1 ^
             -D SDL_OPENGLES:BOOL=0 ^
             -D SDL_RENDER_D3D:BOOL=0 ^
             -D SDL_STATIC:BOOL=0 ^
             -D SDL_SHARED:BOOL=1 ^
             -D SDL_VULKAN:BOOL=0 ^
             -S %SRC_DIR% -B %BUILD_DIR%

echo SDL2 build succesfully generated

:: Build SDL2 library
echo Compiling SDL2 library...

msbuild %SDL2_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release 
if %RELEASE_ENGINE% == false msbuild %SDL2_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug

echo SDL2 library compiled

goto end

:done
:: Confirmation message
echo SDL2 already built and compiled

:end