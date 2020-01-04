# Microsoft Developer Studio Project File - Name="CreOMMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CreOMMgr - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CreOMMgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CreOMMgr.mak" CFG="CreOMMgr - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CreOMMgr - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CreOMMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_d32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib MMgr_D32.lib PMgr_D32.lib MMs0_D32.lib MMs1_D32.lib MMs2_D32.lib MMs3_D32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:".\CreOM_d.def" /out:"c:\drgraf4_0\applic\Debug/CreM_D32.dll" /implib:"c:\drgraf4_0\applic\Debug/CreM_D32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "CreOMMgr - Win32 Release"
# Name "CreOMMgr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CreM.rc
# End Source File
# Begin Source File

SOURCE=.\CreMDlgM.cpp
# End Source File
# Begin Source File

SOURCE=.\CreMDll.cpp
# End Source File
# Begin Source File

SOURCE=.\CreOM_d.def

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CreOMMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\CurCreOM.cpp
# End Source File
# Begin Source File

SOURCE=.\MI_0SPN.cpp
# End Source File
# Begin Source File

SOURCE=.\MI_1SPN.cpp
# End Source File
# Begin Source File

SOURCE=.\MI_2SPN.cpp
# End Source File
# Begin Source File

SOURCE=.\MI_3SPN.cpp
# End Source File
# Begin Source File

SOURCE=.\MI_MSPN.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_croi.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_LALL.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_LSy3.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_LSym.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_LSyT.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_RotT.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_SpnC.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_SpnN.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_spnO.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_SpnP.cpp
# End Source File
# Begin Source File

SOURCE=.\Mlg_SpnS.cpp
# End Source File
# Begin Source File

SOURCE=.\NodCreOM.cpp
# End Source File
# Begin Source File

SOURCE=.\PatCreOM.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CreMDlgM.h
# End Source File
# Begin Source File

SOURCE=.\CreMDll.h
# End Source File
# Begin Source File

SOURCE=.\CreMRsrc.h
# End Source File
# Begin Source File

SOURCE=.\CreOMMgr.h
# End Source File
# Begin Source File

SOURCE=.\CurCreOM.h
# End Source File
# Begin Source File

SOURCE=.\Mi_3SPN.h
# End Source File
# Begin Source File

SOURCE=.\Mi_MSPN.h
# End Source File
# Begin Source File

SOURCE=.\NodCreOM.h
# End Source File
# Begin Source File

SOURCE=.\O3DCreOM.h
# End Source File
# Begin Source File

SOURCE=.\PatCreOM.h
# End Source File
# Begin Source File

SOURCE=.\SolCreOM.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE="..\Applic\Res\000%.cur"
# End Source File
# Begin Source File

SOURCE="..\Applic\Res\012%.cur"
# End Source File
# Begin Source File

SOURCE="..\Applic\Res\025%.cur"
# End Source File
# Begin Source File

SOURCE="..\Applic\Res\037%.cur"
# End Source File
# Begin Source File

SOURCE="..\Applic\Res\050%.cur"
# End Source File
# Begin Source File

SOURCE="..\Applic\Res\062%.cur"
# End Source File
# Begin Source File

SOURCE="..\Applic\Res\075%.cur"
# End Source File
# Begin Source File

SOURCE="..\Applic\Res\087%.cur"
# End Source File
# Begin Source File

SOURCE="..\Applic\Res\100%.cur"
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Cur_iso.cur
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Curh_12.cur
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Curh_23.cur
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Curh_31.cur
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Curtext.cur
# End Source File
# End Group
# End Target
# End Project
