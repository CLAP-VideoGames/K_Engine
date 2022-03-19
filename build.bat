@echo off

title Engine_Build

:: Directory variables
set CURRENT_WORKING_DIR=%cd%
set EXE_DIR=.\exe\

set OGRE_BUILD_DIR=.\dependencies\ogre\
set BULLET_BUILD_DIR=.\dependencies\bullet\
set CEGUI_BUILD_DIR=.\dependencies\cegui\
set SDL_MIXER_BUILD_DIR=.\dependencies\sdl_mixer\
set LUA_BUILD_DIR=.\dependencies\lua\

:: Build OGRE and SDL2 library
cd %OGRE_BUILD_DIR%
call build.bat
cd %CURRENT_WORKING_DIR%

cd %BULLET_BUILD_DIR%
call build.bat
cd %CURRENT_WORKING_DIR%

cd %CEGUI_BUILD_DIR%
call build.bat
cd %CURRENT_WORKING_DIR%

cd %SDL_MIXER_BUILD_DIR%
call build.bat
cd %CURRENT_WORKING_DIR%

cd %LUA_BUILD_DIR%
call build.bat
cd %CURRENT_WORKING_DIR%

:: Move OGRE .dlls
echo Copying OGRE .dlls...

copy .\dependencies\ogre\build\bin\release\OgreMain.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\debug\OgreMain_d.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\release\RenderSystem_GL.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\debug\RenderSystem_GL_d.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\release\Codec_STBI.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\debug\Codec_STBI_d.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\bin\release\zlib.dll %EXE_DIR% 1>nul

echo OGRE .dlls succesfully copied to engine

:: Move SDL2 .dlls
echo Copying SDL2 .dlls...

copy .\dependencies\ogre\build\SDL-build\Release\SDL2.dll %EXE_DIR% 1>nul
copy .\dependencies\ogre\build\SDL-build\Debug\SDL2d.dll %EXE_DIR% 1>nul

echo SDL2 .dlls succesfully copied to engine

:: Move CEGUI .dlls
echo Copying CEGUI .dlls...

copy .\dependencies\CEGUI\src\dependencies\bin\freetype.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\src\dependencies\bin\freetype_d.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\src\dependencies\bin\libexpat.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\src\dependencies\bin\libexpat_d.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\src\dependencies\bin\pcre.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\src\dependencies\bin\pcre_d.dll %EXE_DIR% 1>NUL

copy .\dependencies\CEGUI\build\bin\CEGUIBase-0.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\build\bin\CEGUIBase-0_d.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\build\bin\CEGUIOgreRenderer-0.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\build\bin\CEGUIOgreRenderer-0_d.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\build\bin\CEGUICoreWindowRendererSet.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\build\bin\CEGUICoreWindowRendererSet_d.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\build\bin\CEGUIExpatParser.dll %EXE_DIR% 1>NUL
copy .\dependencies\CEGUI\build\bin\CEGUIExpatParser_d.dll %EXE_DIR% 1>NUL

echo CEGUI .dlls succesfully copied to engine

:: Move SDL_Mixer .dlls
echo Copying SDL_Mixer .dlls...

copy .\dependencies\sdl_mixer\build\Debug\SDL2_mixer_d.dll %EXE_DIR% 1>nul
copy .\dependencies\sdl_mixer\build\Release\SDL2_mixer.dll %EXE_DIR% 1>nul

echo SDL_Mixer .dlls succesfully copied to engine

:: Move FMOD .dlls
echo Copying FMOD .dlls...

copy .\dependencies\fmod\build\dll\fmod.dll %EXE_DIR% 1>nul
copy .\dependencies\fmod\build\dll\fmodL.dll %EXE_DIR% 1>nul

echo FMOD .dlls succesfully copied to engine

:: Move Lua .dlls
echo Copying Lua .dlls...

copy .\dependencies\lua\sol\bin\Debug\lua_d.dll %EXE_DIR% 1>nul
copy .\dependencies\lua\sol\bin\Release\lua.dll %EXE_DIR% 1>nul

echo Lua .dlls succesfully copied to engine