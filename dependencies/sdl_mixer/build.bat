@echo off

:: Batch variables
:: why ;-;
cd ..
set DEPENDENCY_ABSOLUTE_PATH=%cd%

set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set SDL_MIXER_BUILD_SOL=.\build\SDL2_mixer.sln
set SDL_MIXER_DBG_BIN_SOL=.\build\Debug\

set CMAKE_EXEC=..\cmake\bin\cmake.exe

set SDL2_DEPENDENCY_PATH=%DEPENDENCY_ABSOLUTE_PATH%\ogre\build\Dependencies\cmake\

:: Make the build directory
cd .\sdl_mixer\
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %SDL_MIXER_BUILD_SOL% goto done

:: Generate the build
echo Generating SDL_mixer build...

%CMAKE_EXEC% -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -D SDL2_DIR:STRING=%SDL2_DEPENDENCY_PATH% ^
             -D SUPPORT_MP3_MPG123:BOOL="1" ^
             -D SUPPORT_OGG:BOOL="1" ^
             -D SUPPORT_WAV:BOOL="1" ^
             -S %SRC_DIR% -B %BUILD_DIR%

echo SDL_mixer build succesfully generated

:: Build OGRE library
echo Compiling SDL_mixer library...

msbuild %SDL_MIXER_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug
msbuild %SDL_MIXER_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release

:: Rename all debug files
set CURR_DIR=%cd%
cd %SDL_MIXER_DBG_BIN_SOL%
ren SDL2_mixer.* SDL2_mixer_d.*
cd %CURR_DIR%

echo SDL_mixer library compiled

goto end

:done
:: Confirmation message
echo SDL_mixer already built and compiled

:end