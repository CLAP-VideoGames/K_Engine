@echo off

title Engine_Build

:: Release compiling boolean
set RELEASE_ENGINE=false

:: Directory variables
set CURRENT_WORKING_DIR=%cd%
set SOL_DIR=.\K_Engine.sln
set EXE_DIR=.\exe\
set DEPENDENCIES_DIR=.\dependencies\

:: Build all dependencies
cd %DEPENDENCIES_DIR%
call build.bat
cd %CURRENT_WORKING_DIR%

:: Move OGRE .dlls
echo Copying OGRE .dlls...

copy .\dependencies\ogre\build\bin\release\OgreMain.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\release\OgreOverlay.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\release\Plugin_ParticleFX.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\release\RenderSystem_GL.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\release\Codec_STBI.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\release\Codec_Assimp.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\release\zlib.dll %EXE_DIR% 1>nul

if %RELEASE_ENGINE% == false (
    copy .\dependencies\ogre\build\bin\debug\OgreMain_d.dll %EXE_DIR% 1>nul
    copy .\dependencies\ogre\build\bin\debug\OgreOverlay_d.dll %EXE_DIR% 1>nul
    copy .\dependencies\ogre\build\bin\debug\Plugin_ParticleFX_d.dll %EXE_DIR% 1>nul
    copy .\dependencies\ogre\build\bin\debug\RenderSystem_GL_d.dll %EXE_DIR% 1>nul
    copy .\dependencies\ogre\build\bin\debug\Codec_STBI_d.dll %EXE_DIR% 1>nul
)

echo OGRE .dlls succesfully copied to engine

:: Move SDL2 .dlls
echo Copying SDL2 .dlls...

copy .\dependencies\ogre\build\SDL-build\Release\SDL2.dll %EXE_DIR% 1>nul

if %RELEASE_ENGINE% == false copy .\dependencies\ogre\build\SDL-build\Debug\SDL2d.dll %EXE_DIR% 1>nul

echo SDL2 .dlls succesfully copied to engine

:: Move SDL_Mixer .dlls
echo Copying SDL_Mixer .dlls...

copy .\dependencies\sdl_mixer\build\Release\SDL2_mixer.dll %EXE_DIR% 1>nul
if %RELEASE_ENGINE% == false copy .\dependencies\sdl_mixer\build\Debug\SDL2_mixer_d.dll %EXE_DIR% 1>nul

echo SDL_Mixer .dlls succesfully copied to engine

:: Move Lua .dlls
echo Copying Lua .dlls...

copy .\dependencies\lua\sol\bin\Release\lua.dll %EXE_DIR% 1>nul
if %RELEASE_ENGINE% == false copy .\dependencies\lua\sol\bin\Debug\lua_d.dll %EXE_DIR% 1>nul

echo Lua .dlls succesfully copied to engine

:: Change engine project properties

:: Build engine dll & exe
@REM msbuild %SOL_DIR% /t:engine_prj /p:platform=x64 /p:configuration=Release 
@REM if %RELEASE_ENGINE% == false msbuild %SOL_DIR% /t:engine_prj /p:platform=x64 /p:configuration=Debug