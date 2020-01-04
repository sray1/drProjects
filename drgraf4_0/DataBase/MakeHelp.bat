@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DATABASE.HPJ. >"hlp\database.hm"
echo. >>"hlp\database.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\database.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\database.hm"
echo. >>"hlp\database.hm"
echo // Prompts (IDP_*) >>"hlp\database.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\database.hm"
echo. >>"hlp\database.hm"
echo // Resources (IDR_*) >>"hlp\database.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\database.hm"
echo. >>"hlp\database.hm"
echo // Dialogs (IDD_*) >>"hlp\database.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\database.hm"
echo. >>"hlp\database.hm"
echo // Frame Controls (IDW_*) >>"hlp\database.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\database.hm"
REM -- Make help for Project DATABASE


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\database.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\database.hlp" goto :Error
if not exist "hlp\database.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\database.hlp" Debug
if exist Debug\nul copy "hlp\database.cnt" Debug
if exist Release\nul copy "hlp\database.hlp" Release
if exist Release\nul copy "hlp\database.cnt" Release
echo.
goto :done

:Error
echo hlp\database.hpj(1) : error: Problem encountered creating help file

:done
echo.
