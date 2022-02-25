@echo off

:: Batch variables
set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set SDL_MIXER_BUILD_SOL=.\build\SDL2_mixer.sln

set CMAKE_EXEC=..\cmake\bin\cmake.exe

:: why ;-;
cd ..
set ABSOLUTE_PATH=%cd%
cd .\sdl_mixer\
set SDL2_DEPENDENCY=%ABSOLUTE_PATH%\ogre\build\Dependencies\cmake\

:: Make the build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %SDL_MIXER_BUILD_SOL% goto done

:: Generate the build
echo Generating SDL_mixer build...

%CMAKE_EXEC% -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -D SDL2_DIR:STRING=%SDL2_DEPENDENCY% ^
             -D SUPPORT_MP3_MPG123:BOOL="1" ^
             -D SUPPORT_OGG:BOOL="1" ^
             -D SUPPORT_WAV:BOOL="1" ^
             -S %SRC_DIR% -B %BUILD_DIR%

echo SDL_mixer build succesfully generated

:: Build OGRE library
echo Compiling SDL_mixer library...

:: same dll ???
msbuild %SDL_MIXER_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug
@REM msbuild %SDL_MIXER_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release :: same dll

echo SDL_mixer library compiled

goto end

:done

:: Confirmation message
echo SDL_mixer already built and compiled

:end