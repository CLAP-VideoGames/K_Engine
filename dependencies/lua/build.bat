@echo off

:: Batch variables
set LUA_BUILD_SOL=.\sol\lua.sln
set LUA_DLL_PATH =.\sol\bin\Debug\lua.dll

:: Make the build directory
if exist %LUA_DLL_PATH% goto done

:: Build Lua
echo Compiling Lua...

msbuild %LUA_BUILD_SOL% /t:lua_prj /p:platform=x64 /p:configuration=Debug
msbuild %LUA_BUILD_SOL% /t:lua_prj /p:platform=x64 /p:configuration=Release 

echo Lua compiled

goto end

:done

:: Confirmation message
echo Lua already compiled

:end