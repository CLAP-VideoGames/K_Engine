@echo on

:: Directory variables
set SRC_DIR=.\src\
set BUILD_DIR=.\build\
set BUILD_SOL=.\build\OGRE.sln
set CMAKE_EXEC=..\cmake\bin\cmake.exe

:: Make the build directory
@REM if exist %BUILD_DIR% goto done
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

:: Generate the build
%CMAKE_EXEC% -S %SRC_DIR% -B %BUILD_DIR%

:: Build library
msbuild %BUILD_SOL% /p:platform="x64" /p:configuration="Debug"
msbuild %BUILD_SOL% /p:platform="x64" /p:configuration="Release" 
goto end

:: Confirmation message
echo "OGRE compilado"

:done
echo "OGRE esta ya compilado"

:end
pause
@REM -CMAKE_CONFIGURATION_TYPES:STRING="Debug;Release" ^
@REM -OGRE_BUILD_COMPONENT_BITES:BOOL="0" ^
@REM -OGRE_BUILD_SAMPLES:BOOL="0" ^
@REM -OGRE_INSTALL_SAMPLES:BOOL="0" ^
@REM -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="1" ^
@REM -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="1" ^
@REM -OGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" ^

