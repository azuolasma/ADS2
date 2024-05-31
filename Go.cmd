@echo off
rem Check if the script is running on a faculty machine or a personal PC.
if .%USERDOMAIN% == .LINA goto savasPC

echo Setting up environment for MIF computer...
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make
goto toliau

:savasPC
echo Setting up environment for personal PC...
path C:\Program Files\CodeBlocks\MinGW\bin\;%path%
mingw32-make

:toliau
max_queens.exe > results.txt
echo Test results saved to results.txt.
mingw32-make clean
echo Cleanup completed.
pause
