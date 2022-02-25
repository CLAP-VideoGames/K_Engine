@echo off

:: Batch variables
set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set SDL_MIXER_BUILD_SOL=.\build\SDL_mixer.sln

set CMAKE_EXEC=..\cmake\bin\cmake.exe
set SDL2_DEPENDENCY=..\ogre\build\Dependencies\cmake\

:: Make the build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %SDL_MIXER_BUILD_SOL% goto done

:: Generate the build
echo Generating SDL_mixer build...

%CMAKE_EXEC% -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -D SDL2_DIR:STRING=%SDL2_DEPENDENCY% ^
             -S %SRC_DIR% -B %BUILD_DIR%

echo SDL_mixer build succesfully generated

:: Build OGRE library
echo Compiling SDL_mixer library...

msbuild %SDL_MIXER_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug
msbuild %SDL_MIXER_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release 

echo SDL_mixer library compiled

goto end

:done

:: Confirmation message
echo SDL_mixer already built and compiled

:end