@echo off

title Engine_Build_Reset

:: Directory variables
set CURRENT_DIR=%cd%

set OGRE_BUILD_DIR=.\dependencies\ogre\build\
set BULLET_BUILD_DIR=.\dependencies\bullet\build\
set CEGUI_BUILD_DIR=.\dependencies\cegui\build\
set CEGUI_SRC_DEP_BUILD_DIR=.\dependencies\cegui\src\dependencies\
set CEGUI_DEP_BUILD_DIR=.\dependencies\cegui\dependencies\build\
set SDL_MIXER_BUILD_DIR=.\dependencies\cegui\build\
set LUA_BUILD_DIR=.\dependencies\lua\sol\bin\

:: Remove all dependencies' builds
echo Removing OGRE and SDL2 build...
if exist %OGRE_BUILD_DIR% rmdir /s /q %OGRE_BUILD_DIR%
echo OGRE and SDL2 build succesfully removed

echo Removing Bullet build...
if exist %BULLET_BUILD_DIR% rmdir /s /q %BULLET_BUILD_DIR%
echo Bullet build succesfully removed

echo Removing CEGUI build...
if exist %CEGUI_BUILD_DIR% rmdir /s /q %CEGUI_BUILD_DIR%
echo CEGUI build succesfully removed

echo Removing CEGUI dependencies build...
if exist %CEGUI_DEP_BUILD_DIR% rmdir /s /q %CEGUI_DEP_BUILD_DIR%
if exist %CEGUI_SRC_DEP_BUILD_DIR% rmdir /s /q %CEGUI_SRC_DEP_BUILD_DIR%
echo CEGUI dependencies build succesfully removed

echo Removing SDL_mixer build...
if exist %SDL_MIXER_BUILD_DIR% rmdir /s /q %SDL_MIXER_BUILD_DIR%
echo SDL_mixer build succesfully removed

echo Removing Lua build...
if exist %LUA_BUILD_DIR% rmdir /s /q %LUA_BUILD_DIR%
echo Lua build succesfully removed

:: Remove all dynamic libraries
echo Removing all dynamic libraries...
del /s ./exe/*.dll 1>nul
echo Dynamic libraries build succesfully removed