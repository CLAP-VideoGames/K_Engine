@echo off

title Engine_Build_Reset

:: Directory variables
set CURRENT_DIR=%cd%
set EXE_DIR=.\exe\

set OGRE_BUILD_DIR=.\dependencies\ogre\
set BULLET_BUILD_DIR=.\dependencies\bullet\
set CEGUI_BUILD_DIR=.\dependencies\cegui\

:: Remove build OGRE and SDL2 library
cd %OGRE_BUILD_DIR%
call build_reset.bat
cd %CURRENT_DIR%

:: Remove OGRE dlls
del .\exe\OgreMain_d.dll 1>NUL
del .\exe\OgreMain.dll 1>NUL
del .\exe\zlib.dll 1>NUL
del .\exe\RenderSystem_GL_d.dll 1>NUL
del .\exe\RenderSystem_GL.dll 1>NUL
del .\exe\Codec_STBI.dll 1>NUL
del .\exe\Codec_STBI_d.dll 1>NUL

:: Remove OGRE dlls
del .\exe\SDL2d.dll 1>NUL
del .\exe\SDL2.dll 1>NUL