@echo off

set UTILS=%CD%\UTILS

set path=%WINDIR%\COMMAND;%CDIR%\bin;%UTILS%;%path%

IF EXIST Objects (
	copy %UTILS%\load.m3p Objects\load.m3p
	cd Objects
) ELSE (
	echo Objects dir not found
	goto ERROR
)

m3p.exe hb166 calk.hex calk.bin bye
m3p.exe lfile load.m3p
goto OK

:ERROR
echo ------------- ERROR ----------------

:OK

