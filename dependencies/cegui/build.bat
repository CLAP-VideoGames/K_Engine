@echo off

:: Batch variables
:: why x2 ;-;
cd ..
set DEPENDENCY_ABSOLUTE_PATH=%cd%
cd .\cegui\
set CURRENT_DIR=%cd%
set DEPENDENCIES_DIR=.\dependencies\
set DEPENDENCIES_LIB=.\dependencies\build\dependencies\*.*
set SRC_DEPENDENCIES_DIR=.\src\dependencies\

:: Generate dependencies
cd %DEPENDENCIES_DIR%
call build.bat
cd %CURRENT_DIR%
if not exist %SRC_DEPENDENCIES_DIR% mkdir %SRC_DEPENDENCIES_DIR%
copy /s /y %DEPENDENCIES_LIB% %SRC_DEPENDENCIES_DIR% 1>nul

set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set CEGUI_BUILD_SOL=.\build\cegui.sln

set CMAKE_EXE=..\cmake\bin\cmake.exe

:: Make the build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %CEGUI_BUILD_SOL% goto done

:: Generate the build
echo Generating CEGUI build...

%CMAKE_EXE% -S %SRC_DIR% -B %BUILD_DIR% ^
            -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
            -D OGRE_H_PATH:PATH=%DEPENDENCY_ABSOLUTE_PATH%\ogre\src\OgreMain\include\ ^
            -D OGRE_H_BUILD_SETTINGS_PATH:PATH=%DEPENDENCY_ABSOLUTE_PATH%\ogre\build\include\ ^
            -D OGRE_LIB:FILEPATH=%DEPENDENCY_ABSOLUTE_PATH%\ogre\build\lib\Release\OgreMain.lib ^
            -D OGRE_LIB_DBG:FILEPATH=%DEPENDENCY_ABSOLUTE_PATH%\ogre\build\lib\Debug\OgreMain_d.lib ^
            -D CEGUI_SAMPLES_ENABLED:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_COMMON_DIALOGUES_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_DEMO6:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_DRAGDROP_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_EDITBOX_VALIDATION_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_EFFECTS_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_FONT_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_GAMEMENU_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_HELLO_WORLD_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_HUD_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_INVENTORY_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_LOOKNFEELOVERVIEW_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_MINESWEEPER_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_SCROLLABLEPANE_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_TABCONTROL_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_TEXT_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_TREE_DEMO:BOOL=0 ^ 
            -D CEGUI_SAMPLES_ENABLE_WIDGET_DEMO:BOOL=0 ^ 
            -D CEGUI_BUILD_APPLICATION_TEMPLATES:BOOL=1 ^
            -D CEGUI_BUILD_IMAGECODEC_DEVIL:BOOL=1 ^ 
            -D CEGUI_BUILD_IMAGECODEC_SILLY:BOOL=1 ^ 
            -D CEGUI_BUILD_RENDERER_OGRE:BOOL=1 ^ 
            -D CEGUI_BUILD_RENDERER_OPENGL:BOOL=1 ^
            -D CEGUI_BUILD_RENDERER_OPENGL3:BOOL=1 ^ 
            -D CEGUI_BUILD_XMLPARSER_EXPAT:BOOL=1 ^ 
            -D CEGUI_HAS_DEFAULT_LOGGER:BOOL=1 ^ 
            -D CEGUI_HAS_FREETYPE:BOOL=1 ^
            -D CEGUI_HAS_PCRE_REGEX:BOOL=1

echo CEGUI build succesfully generated

:: POR ALGUNA RAZON OGRE::IMAGE NO TIENE BOX (CAMBIADO EN TEXTURE.H) Y FALTA INCLUDE SSTREAM EN OGRECOMMON
:: Change major, minar and patch on Config.h
powershell -command "(gc %CEGUI_CONFIG_PATH%) -replace 'define CEGUI_OGRE_VERSION_MAJOR 0', 'define CEGUI_OGRE_VERSION_MAJOR 1' | Out-File -encoding ASCII %CEGUI_CONFIG_PATH%"
powershell -command "(gc %CEGUI_CONFIG_PATH%) -replace 'define CEGUI_OGRE_VERSION_MINOR 0', 'define CEGUI_OGRE_VERSION_MINOR 12' | Out-File -encoding ASCII %CEGUI_CONFIG_PATH%"
powershell -command "(gc %CEGUI_CONFIG_PATH%) -replace 'define CEGUI_OGRE_VERSION_PATCH 0', 'define CEGUI_OGRE_VERSION_PATCH 11' | Out-File -encoding ASCII %CEGUI_CONFIG_PATH%"

:: Build CEGUI library
echo Compiling CEGUI library...

msbuild %CEGUI_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug
msbuild %CEGUI_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release 

echo CEGUI library compiled

goto end

:done

:: Confirmation message
echo CEGUI already built and compiled

:end

@REM "D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\build\cegui.sln" (ALL_BUILD target) (1) ->
@REM "D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\build\ALL_BUILD.vcxproj.metaproj" (default target) (2) ->

@REM "D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\build\cegui\src\RendererModules\Ogre\CEGUIOgreRenderer-0.
@REM vcxproj.metaproj" (default target) (14) ->

@REM "D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\build\cegui\src\RendererModules\Ogre\CEGUIOgreRenderer-0.
@REM vcxproj" (default target) (15) ->

@REM (ClCompile target) ->

@REM   D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\src\cegui\src\RendererModules\Ogre\Texture.cpp(246,18):
@REM error C2039: 'Box': is not a member of 'Ogre::Image' [D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\buil
@REM d\cegui\src\RendererModules\Ogre\CEGUIOgreRenderer-0.vcxproj]

@REM   D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\src\cegui\src\RendererModules\Ogre\Texture.cpp(246,22):
@REM error C2065: 'Box': undeclared identifier [D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\build\cegui\src
@REM \RendererModules\Ogre\CEGUIOgreRenderer-0.vcxproj]

@REM   D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\src\cegui\src\RendererModules\Ogre\Texture.cpp(246,22):
@REM error C2146: syntax error: missing ';' before identifier 'box' [D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\
@REM cegui\build\cegui\src\RendererModules\Ogre\CEGUIOgreRenderer-0.vcxproj]

@REM   D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\src\cegui\src\RendererModules\Ogre\Texture.cpp(246,22):
@REM error C3861: 'box': identifier not found [D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\build\cegui\src\
@REM RendererModules\Ogre\CEGUIOgreRenderer-0.vcxproj]

@REM   D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\src\cegui\src\RendererModules\Ogre\Texture.cpp(247,48):
@REM error C2065: 'box': undeclared identifier [D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\build\cegui\src
@REM \RendererModules\Ogre\CEGUIOgreRenderer-0.vcxproj]

@REM   D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\src\cegui\src\RendererModules\Ogre\Texture.cpp(280,28):
@REM error C2079: 'strstream' uses undefined class 'std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>' [D:\Game_Dev
@REM \Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\build\cegui\src\RendererModules\Ogre\CEGUIOgreRenderer-0.vcxproj]

@REM   D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\dependencies\cegui\src\cegui\src\RendererModules\Ogre\Texture.cpp(281,37):
@REM error C2297: '<<': illegal, right operand has type 'const char [13]' [D:\Game_Dev\Projects\VS-VSC\C++\P3\Repositories\K_Engine\depende
@REM ncies\cegui\build\cegui\src\RendererModules\Ogre\CEGUIOgreRenderer-0.vcxproj]