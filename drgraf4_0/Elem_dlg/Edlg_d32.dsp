# Microsoft Developer Studio Project File - Name="Edlg_d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Edlg_d - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Edlg_d32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Edlg_d32.mak" CFG="Edlg_d - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Edlg_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Edlg_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:".\FULL" /machine:IX86

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W4 /GX /ZI /Od /D "_WINDLL" /D "_AFXEXT" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFX_EXT" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Spec_D.lib OMgr_D.lib Elem_D.lib Draw_D.lib Dr3D_D.lib oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Spec_D32.lib Elem_D32.lib OMgr_D32.lib Draw_D32.lib Dr3D_D32.lib /nologo /subsystem:windows /dll /incremental:no /map:".\Debug\Edlg_d32..map" /debug /machine:IX86 /def:".\Edlg_d.def" /out:"c:\drgraf4_0\applic\Debug\Edlg_d32.dll" /implib:"c:\drgraf4_0\applic\Debug\Edlg_d32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Edlg_d - Win32 Release"
# Name "Edlg_d - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\dlg_fe0i.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_FE0i.h
# End Source File
# Begin Source File

SOURCE=.\dlg_FE1i.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_fe1i.h
# End Source File
# Begin Source File

SOURCE=.\dlg_fe2i.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_fe2i.h
# End Source File
# Begin Source File

SOURCE=.\Edlg_d.def

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Edlgdll.cpp
# End Source File
# Begin Source File

SOURCE=.\Edlgdll.h
# End Source File
# Begin Source File

SOURCE=.\Edlgmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\Edlgmgr.h
# End Source File
# Begin Source File

SOURCE=.\edlgrsrc.h
# End Source File
# Begin Source File

SOURCE=.\Elem_dlg.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\edlgrsrc.hm
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\Applic\Res\Ico_pipe.ico
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Image1d.bmp
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Image1f.bmp
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Image1u.bmp
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Image2d.bmp
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Image2f.bmp
# End Source File
# Begin Source File

SOURCE=..\Applic\Res\Image2u.bmp
# End Source File
# End Group
# End Target
# End Project
