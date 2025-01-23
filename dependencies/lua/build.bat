@echo off

:: Batch variables
set SRC_DIR=.\src\
set BUILD_DIR=.\build\

set LUA_BUILD_SOL=.\build\lua.sln

set CMAKE_EXEC=..\cmake\bin\cmake.exe

:: Make the build directory
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %LUA_BUILD_SOL% goto done

:: Generate the build
echo Generating Lua build...

%CMAKE_EXEC% -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -D LUA_BUILD_AS_CXX:BOOL="0" ^
             -D LUA_BUILD_BINARY:BOOL="0" ^
             -D LUA_BUILD_COMPILER:BOOL="0" ^
             -D LUA_ENABLE_SHARED:BOOL="1" ^
             -D LUA_ENABLE_TESTS:BOOL="0" ^
             -D LUA_SUPPORT_DL:BOOL="0" ^
             -S %SRC_DIR% -B %BUILD_DIR%

echo Lua build succesfully generated

:: Build Lua
echo Compiling Lua...

msbuild %LUA_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Release 
if %RELEASE_ENGINE% == false msbuild %LUA_BUILD_SOL% /t:ALL_BUILD /p:platform=x64 /p:configuration=Debug

echo Lua compiled

goto end

:done
:: Confirmation message
echo Lua already built and compiled

:end