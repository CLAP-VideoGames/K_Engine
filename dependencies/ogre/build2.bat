set BUILD_SOL=".\build\Ogre.sln"

:: Build library
where msbuild
msbuild %BUILD_SOL% /t:ALL_BUILD /p:platform="x64" /p:configuration="Debug"
msbuild %BUILD_SOL% /t:ALL_BUILD /p:platform="x64" /p:configuration="Release"

pause