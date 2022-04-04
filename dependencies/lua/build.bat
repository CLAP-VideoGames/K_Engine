@echo off

:: Batch variables
set LUA_BUILD_SOL=.\sol\lua.sln
set LUA_DLL_PATH =.\sol\bin\Release\lua.dll

:: Make the build directory
if exist %LUA_DLL_PATH% goto done

:: Build Lua
echo Compiling Lua...

msbuild %LUA_BUILD_SOL% /t:lua_prj /p:platform=x64 /p:configuration=Release 
if %RELEASE_ENGINE% == false msbuild %LUA_BUILD_SOL% /t:lua_prj /p:platform=x64 /p:configuration=Debug

echo Lua compiled

goto end

:done
:: Confirmation message
echo Lua already built and compiled

:end