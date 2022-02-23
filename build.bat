@echo on

title Engine_Build

:: Directory variables
set CURRENT_DIR=%cd%
set EXE_DIR=.\exe\

set OGRE_BUILD_DIR=.\dependencies\ogre\
set BULLET_BUILD_DIR=.\dependencies\bullet\
set CEGUI_BUILD_DIR=.\dependencies\cegui\

:: Build OGRE and SDL2 library
cd %OGRE_BUILD_DIR%
call build.bat
cd %CURRENT_DIR%


:: Move OGRE dlls
copy .\dependencies\ogre\build\bin\debug\OgreMain_d.dll %EXE_DIR% 1>NUL
copy .\dependencies\ogre\build\bin\release\OgreMain.dll %EXE_DIR% 1>NUL
copy .\dependencies\ogre\build\bin\release\zlib.dll %EXE_DIR% 1>NUL
copy .\dependencies\ogre\build\bin\debug\RenderSystem_GL_d.dll %EXE_DIR% 1>NUL
copy .\dependencies\ogre\build\bin\release\RenderSystem_GL.dll %EXE_DIR% 1>NUL
copy .\dependencies\ogre\build\bin\release\Codec_STBI.dll %EXE_DIR% 1>NUL
copy .\dependencies\ogre\build\bin\debug\Codec_STBI_d.dll %EXE_DIR% 1>NUL

:: Move OGRE dlls
copy .\dependencies\Ogre\build\SDL2-build\Debug\SDL2d.dll %EXE_DIR% 1>NUL
copy .\dependencies\Ogre\build\SDL2-build\Release\SDL2.dll %EXE_DIR% 1>NUL