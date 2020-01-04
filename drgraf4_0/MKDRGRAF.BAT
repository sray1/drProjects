@echo off


echo.
echo DrGraf All DLLs and Application (batch build)
echo.
pause
REM set __DEBUG=1
REM if "%1"=="DEBUG" goto doit
REM if "%1"=="debug" goto doit

REM set __DEBUG=0

REM if "%1"=="RETAIL" goto doit
REM if "%1"=="retail" goto doit

REM if "%1"=="CLEAN" goto doit_clean
REM if "%1"=="clean" goto doit_clean

REM echo Please specify DEBUG or RETAIL or CLEAN on the command line.
REM echo.
REM echo     DEBUG will build executables with symbolic information,
REM echo         diagnostics, and no optimizations (large and slow).
REM echo     RETAIL will build ship quality executables that
REM echo         are fully optimized (small and fast).
REM echo     CLEAN will remove all compiler generated files (object
REM echo         files, executables, etc.)  Use this to switch between
REM echo         DEBUG and RETAIL.
REM echo.

REM goto end

REM :doit
REM shift

REM echo.
REM echo NOTE: Since this builds all the sample programs it could
REM echo take a little while.  Type Ctrl-C now if you wish
REM echo to build them later.  You can stop the build at
REM echo any time by typing Ctrl-C (several times) and
REM echo answer 'Y' to terminate.
REM echo.
REM pause

REM :doit_clean

REM if "%1"=="CLEAN" erase STDAFX??.PCH
REM if "%1"=="CLEAN" erase STDAFX??.OBJ

@echo on

cd D:\DRGRAF\SPECIALS
nmake SPEC_D.mak 
pause
IMPLIB_D
cd ..\DRAWOBJS
nmake DRAW_D.mak 
pause
IMPLIB_D

@echo off
REM echo Note: You must manually build the DLLTRACE sample
REM echo Note: You must manually build the MAKEHM tool
REM echo Note: You must manually build the TEMPLDEF tool

REM cd ..

REM :end
REM set __DEBUG=
@echo on
