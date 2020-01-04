@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by RUNDLL.HPJ. >"hlp\rundll.hm"
echo. >>"hlp\rundll.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\rundll.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\rundll.hm"
echo. >>"hlp\rundll.hm"
echo // Prompts (IDP_*) >>"hlp\rundll.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\rundll.hm"
echo. >>"hlp\rundll.hm"
echo // Resources (IDR_*) >>"hlp\rundll.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\rundll.hm"
echo. >>"hlp\rundll.hm"
echo // Dialogs (IDD_*) >>"hlp\rundll.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\rundll.hm"
echo. >>"hlp\rundll.hm"
echo // Frame Controls (IDW_*) >>"hlp\rundll.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\rundll.hm"
REM -- Make help for Project RUNDLL


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\rundll.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\rundll.hlp" goto :Error
if not exist "hlp\rundll.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\rundll.hlp" Debug
if exist Debug\nul copy "hlp\rundll.cnt" Debug
if exist Release\nul copy "hlp\rundll.hlp" Release
if exist Release\nul copy "hlp\rundll.cnt" Release
echo.
goto :done

:Error
echo hlp\rundll.hpj(1) : error: Problem encountered creating help file

:done
echo.
