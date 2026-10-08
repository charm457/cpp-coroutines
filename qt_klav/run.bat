@echo off

rem Нужен PATH с Qt из MSYS2, иначе keyboard.exe не найдёт DLL
if exist C:\msys64\ucrt64\bin set PATH=C:\msys64\ucrt64\bin;%PATH%

rem Рабочая папка должна быть build_ninja, т.к. там лежит img\ со смайликом
cd /d %~dp0build_ninja

if not exist keyboard.exe (
	echo Сначала соберите проект: запустите build.bat
	pause
	exit /b 1
)

keyboard.exe
cd /d %~dp0