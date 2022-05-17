@echo off
@echo Test %1
@echo Test %1 >>%2.res
if exist bridges.in del bridges.in>Nul
if exist bridges.out del bridges.out>Nul
copy %1 bridges.in >nul
ConsoleApplication4.exe
Timer %2.exe 2000 65536 >>%2.res
if exist bridges.out goto next
@echo No output file! >>%2.res
goto end
:next
Check.exe %1 bridges.out %1.a >>%2.res
:end