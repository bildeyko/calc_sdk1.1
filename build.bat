@echo off
rem set path=

set CDIR=D:\dev\Keil_v5\C51
set UTILS=%CD%\UTILS

set c51inc=%CDIR%\inc
set c51lib=%CDIR%\lib

set inc=..\include_c51

set path=%WINDIR%\COMMAND;%CDIR%\bin;%UTILS%;%path%

call clean.bat

If Not Exist .\bin (
	MD bin
)
copy .\load.m3p bin\load.m3p

cd src

for %%f in (*.c) do C51 %%f   CODE LARGE WL(0) INCDIR(%inc%) DEBUG OE NOINTVECTOR
if errorlevel 1 goto ERROR
for %%f in (*.a51) do A51 %%f
if errorlevel 1 goto ERROR

move /Y START_AD.obj ..\bin

echo START_AD.obj > ..\bin\command.lk
for %%f in (*.obj) do echo ,%%f >> ..\bin\command.lk
echo to calk CODE(2100H) XDATA(04000H) >> ..\bin\command.lk

move /Y *.lst ..\lst
move /Y *.obj ..\bin
cd ..\bin

BL51 @command.lk

OH51 calk
if errorlevel 1 goto ERROR

m3p.exe hb166 calk.hex  calk.bin bye
m3p.exe lfile load.m3p
goto OK


:ERROR
echo ------------- ERROR ----------------


:OK

cd ..
