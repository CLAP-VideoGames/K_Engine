@echo off

:: Directory variables
set BUILD_DIR=.\build\

if exist %BUILD_DIR% rmdir /S /Q %BUILD_DIR%