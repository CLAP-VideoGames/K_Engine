@echo off

set CURR_WORKING_DIR=%cd%

set OGRE_BUILD_DIR=.\ogre\
set BULLET_BUILD_DIR=.\bullet\
set SDL_MIXER_BUILD_DIR=.\sdl_mixer\
set LUA_BUILD_DIR=.\lua\

:: Build OGRE and SDL2 library
cd %OGRE_BUILD_DIR%
call build.bat
cd %CURR_WORKING_DIR%

:: Build Bullet library
cd %BULLET_BUILD_DIR%
call build.bat
cd %CURR_WORKING_DIR%

:: Build SDL_Mixer library
cd %SDL_MIXER_BUILD_DIR%
call build.bat
cd %CURR_WORKING_DIR%

:: Build LUA library
cd %LUA_BUILD_DIR%
call build.bat
cd %CURR_WORKING_DIR%

echo All dependencies succesfully built