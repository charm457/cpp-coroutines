@echo off


set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

chcp 65001

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=sort

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
cmake --build .

set arr[0].file=power.sh
set arr[1].file=power2.sh

set arr[0].folder=SecondTask15_10_2025
set arr[1].folder=sortShell


for /L %%i in (0,1,9) do ( 
	if not exist .\!arr[%%i].folder!\!arr[%%i].file! (
		copy ..\%SOURCE_FOLDER%\!arr[%%i].folder!\!arr[%%i].file! .\!arr[%%i].folder!
	)
)

if not exist .\run_tests.sh copy ..\run_tests.sh .