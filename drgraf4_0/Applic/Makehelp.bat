@echo off
REM -- First make map file from App Studio generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DRGRAF.HPJ. >hlp\drgraf.hm
echo. >>hlp\drgraf.hm
echo // Commands (ID_* and IDM_*) >>hlp\drgraf.hm
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>hlp\drgraf.hm
echo. >>hlp\drgraf.hm
echo // Prompts (IDP_*) >>hlp\drgraf.hm
makehm IDP_,HIDP_,0x30000 resource.h >>hlp\drgraf.hm
echo. >>hlp\drgraf.hm
echo // Resources (IDR_*) >>hlp\drgraf.hm
makehm IDR_,HIDR_,0x20000 resource.h >>hlp\drgraf.hm
echo. >>hlp\drgraf.hm
echo // Dialogs (IDD_*) >>hlp\drgraf.hm
makehm IDD_,HIDD_,0x20000 resource.h >>hlp\drgraf.hm
echo. >>hlp\drgraf.hm
echo // Frame Controls (IDW_*) >>hlp\drgraf.hm
makehm IDW_,HIDW_,0x50000 resource.h >>hlp\drgraf.hm
REM -- Make help for Project DRGRAF
call hc31 drgraf.hpj
echo.
