@echo off

:: Directory variables
set BUILD_DIR=.\build\

if exist %BUILD_DIR% rmdir /s /q %BUILD_DIR%