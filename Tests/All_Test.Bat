@echo off
if %1. == . goto noparm
if exist %1.res del %1.res
echo Task: День 5, Задача 3 : Главные дороги >%1.res
echo Program to test: %1 >>%1.res
echo ................ >>%1.res 
for %%i in (01,02,03,04,05,06,07,08,09,10,11) do call test.bat %%i %1
if exist bridges.in del bridges.in>Nul
if exist bridges.out del bridges.out>Nul
exit
:noparm
@echo Usage: test_all filename
@echo filename must be without extension!
