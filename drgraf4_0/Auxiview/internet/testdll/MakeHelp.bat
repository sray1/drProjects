@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by TESTDLL.HPJ. >"hlp\testdll.hm"
echo. >>"hlp\testdll.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\testdll.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\testdll.hm"
echo. >>"hlp\testdll.hm"
echo // Prompts (IDP_*) >>"hlp\testdll.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\testdll.hm"
echo. >>"hlp\testdll.hm"
echo // Resources (IDR_*) >>"hlp\testdll.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\testdll.hm"
echo. >>"hlp\testdll.hm"
echo // Dialogs (IDD_*) >>"hlp\testdll.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\testdll.hm"
echo. >>"hlp\testdll.hm"
echo // Frame Controls (IDW_*) >>"hlp\testdll.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\testdll.hm"
REM -- Make help for Project TESTDLL


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\testdll.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\testdll.hlp" goto :Error
if not exist "hlp\testdll.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\testdll.hlp" Debug
if exist Debug\nul copy "hlp\testdll.cnt" Debug
if exist Release\nul copy "hlp\testdll.hlp" Release
if exist Release\nul copy "hlp\testdll.cnt" Release
echo.
goto :done

:Error
echo hlp\testdll.hpj(1) : error: Problem encountered creating help file

:done
echo.
