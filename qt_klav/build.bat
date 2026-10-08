@echo off

rem Работаем всегда из папки скрипта, независимо от того, откуда запустили
cd /d %~dp0

rem Берём gcc, cmake, ninja и Qt из MSYS2 (ucrt64), если он установлен туда
if exist C:\msys64\ucrt64\bin set PATH=C:\msys64\ucrt64\bin;%PATH%

set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set IMG_FOLDER=img

if not exist %~dp0%BUILD_FOLDER% mkdir %~dp0%BUILD_FOLDER%

cmake -G %BUILD_TYPE% -S %~dp0 -B %~dp0%BUILD_FOLDER%
cmake --build %~dp0%BUILD_FOLDER%

if not exist %~dp0%BUILD_FOLDER%\%IMG_FOLDER% mkdir %~dp0%BUILD_FOLDER%\%IMG_FOLDER%
copy /Y %~dp0%IMG_FOLDER%\grustnii-smail.png %~dp0%BUILD_FOLDER%\%IMG_FOLDER%\
