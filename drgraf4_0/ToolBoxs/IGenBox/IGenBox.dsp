# Microsoft Developer Studio Project File - Name="IGenBox" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=IGenBox - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IGenBox.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IGenBox.mak" CFG="IGenBox - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IGenBox - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IGenBox - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IGenBox - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

# PROP BASE Use_MFC 0
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
# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFX_EXT" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib Stal_D32.lib Supp_D32.lib EBox_D32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /def:".\IGenBox_d.def" /out:"c:\DrGraf4_0\Applic\Debug/IGBx_D32.dll" /implib:"c:\DrGraf4_0\Applic\Debug/IGBx_D32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "IGenBox - Win32 Release"
# Name "IGenBox - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BoxWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Cboxbutt.h
# End Source File
# Begin Source File

SOURCE=.\CNTLbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Cntlbox.cpp
# End Source File
# Begin Source File

SOURCE=.\Cntlbutt.h
# End Source File
# Begin Source File

SOURCE=.\COpbar.cpp
# End Source File
# Begin Source File

SOURCE=.\COpbar.h
# End Source File
# Begin Source File

SOURCE=.\COpbox.cpp
# End Source File
# Begin Source File

SOURCE=.\COpbox.h
# End Source File
# Begin Source File

SOURCE=.\COpbutt.h
# End Source File
# Begin Source File

SOURCE=.\Curvebar.cpp
# End Source File
# Begin Source File

SOURCE=.\Curvebox.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_LSyT.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_MovT.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_RotT.cpp
# End Source File
# Begin Source File

SOURCE=.\DynLbar.cpp
# End Source File
# Begin Source File

SOURCE=.\DynLbox.cpp
# End Source File
# Begin Source File

SOURCE=.\DynLbutt.h
# End Source File
# Begin Source File

SOURCE=.\EDimBar.cpp
# End Source File
# Begin Source File

SOURCE=.\EDimBox.cpp
# End Source File
# Begin Source File

SOURCE=.\EDimButt.h
# End Source File
# Begin Source File

SOURCE=.\GOpbar.cpp
# End Source File
# Begin Source File

SOURCE=.\GOpbox.cpp
# End Source File
# Begin Source File

SOURCE=.\GOpbutt.h
# End Source File
# Begin Source File

SOURCE=.\IGenbar.cpp
# End Source File
# Begin Source File

SOURCE=.\IGenbox.cpp
# End Source File
# Begin Source File

SOURCE=.\IGenbox.rc
# End Source File
# Begin Source File

SOURCE=.\IGenBox_d.def

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\IGenButt.h
# End Source File
# Begin Source File

SOURCE=.\IGendll.cpp
# End Source File
# Begin Source File

SOURCE=.\IGenMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\IGenRsrc.h
# End Source File
# Begin Source File

SOURCE=.\MainBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Mainbox.cpp
# End Source File
# Begin Source File

SOURCE=.\MainButt.h
# End Source File
# Begin Source File

SOURCE=.\MCNodbar.cpp
# End Source File
# Begin Source File

SOURCE=.\MCNodbox.cpp
# End Source File
# Begin Source File

SOURCE=.\MGenbox.cpp
# End Source File
# Begin Source File

SOURCE=.\MNodbar.cpp
# End Source File
# Begin Source File

SOURCE=.\MNodbox.cpp
# End Source File
# Begin Source File

SOURCE=.\Nboxbutt.h
# End Source File
# Begin Source File

SOURCE=.\Nodebar.cpp
# End Source File
# Begin Source File

SOURCE=.\Nodebox.cpp
# End Source File
# Begin Source File

SOURCE=.\OldGlob.cpp
# End Source File
# Begin Source File

SOURCE=.\OldTool.cpp
# End Source File
# Begin Source File

SOURCE=.\Palette.cpp
# End Source File
# Begin Source File

SOURCE=.\Patchbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Patchbox.cpp
# End Source File
# Begin Source File

SOURCE=.\Pboxbutt.h
# End Source File
# Begin Source File

SOURCE=.\Sboxbutt.h
# End Source File
# Begin Source File

SOURCE=.\Solidbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Solidbox.cpp
# End Source File
# Begin Source File

SOURCE=.\SpeLbar.cpp
# End Source File
# Begin Source File

SOURCE=.\SpeLbox.cpp
# End Source File
# Begin Source File

SOURCE=.\SpeLbutt.h
# End Source File
# Begin Source File

SOURCE=.\StaLbar.cpp
# End Source File
# Begin Source File

SOURCE=.\StaLbox.cpp
# End Source File
# Begin Source File

SOURCE=.\StaLbutt.h
# End Source File
# Begin Source File

SOURCE=.\Suppbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Suppbox.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\BoxBMPID.h
# End Source File
# Begin Source File

SOURCE=.\BoxWnd.h
# End Source File
# Begin Source File

SOURCE=.\BoxWndID.h
# End Source File
# Begin Source File

SOURCE=.\CNTLbar.h
# End Source File
# Begin Source File

SOURCE=.\CntlBox.h
# End Source File
# Begin Source File

SOURCE=.\Curvebar.h
# End Source File
# Begin Source File

SOURCE=.\Curvebox.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_LSyT.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_MovT.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_RotT.h
# End Source File
# Begin Source File

SOURCE=.\DynLbar.h
# End Source File
# Begin Source File

SOURCE=.\DynLbox.h
# End Source File
# Begin Source File

SOURCE=.\DynLRsrc.h
# End Source File
# Begin Source File

SOURCE=.\EDimBar.h
# End Source File
# Begin Source File

SOURCE=.\EDimBox.h
# End Source File
# Begin Source File

SOURCE=.\GOpbar.h
# End Source File
# Begin Source File

SOURCE=.\GOpbox.h
# End Source File
# Begin Source File

SOURCE=.\IGenBar.h
# End Source File
# Begin Source File

SOURCE=.\IGenbox.h
# End Source File
# Begin Source File

SOURCE=.\IGendll.h
# End Source File
# Begin Source File

SOURCE=.\MainBar.h
# End Source File
# Begin Source File

SOURCE=.\Mainbox.h
# End Source File
# Begin Source File

SOURCE=.\MGenbox.h
# End Source File
# Begin Source File

SOURCE=.\MNBxbutt.h
# End Source File
# Begin Source File

SOURCE=.\MNodbar.h
# End Source File
# Begin Source File

SOURCE=.\MNodbox.h
# End Source File
# Begin Source File

SOURCE=.\Nodebar.h
# End Source File
# Begin Source File

SOURCE=.\Nodebox.h
# End Source File
# Begin Source File

SOURCE=.\OldGlob.h
# End Source File
# Begin Source File

SOURCE=.\OldTool.h
# End Source File
# Begin Source File

SOURCE=.\Palette.h
# End Source File
# Begin Source File

SOURCE=.\Patchbar.h
# End Source File
# Begin Source File

SOURCE=.\Patchbox.h
# End Source File
# Begin Source File

SOURCE=.\Solidbar.h
# End Source File
# Begin Source File

SOURCE=.\Solidbox.h
# End Source File
# Begin Source File

SOURCE=.\SpeLbar.h
# End Source File
# Begin Source File

SOURCE=.\SpeLbox.h
# End Source File
# Begin Source File

SOURCE=.\SpeLRsrc.h
# End Source File
# Begin Source File

SOURCE=.\StaLbar.h
# End Source File
# Begin Source File

SOURCE=.\StaLbox.h
# End Source File
# Begin Source File

SOURCE=.\StaLRsrc.h
# End Source File
# Begin Source File

SOURCE=.\Suppbar.h
# End Source File
# Begin Source File

SOURCE=.\Suppbox.h
# End Source File
# Begin Source File

SOURCE=.\Suppbutt.h
# End Source File
# Begin Source File

SOURCE=.\SuppRsrc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\Button.cur
# End Source File
# Begin Source File

SOURCE=.\Res\CntlBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\COpbox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\CurveBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\DynLBar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\EDimbox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\GOpbox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\IGenBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\MainBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\MCNodBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\MGenBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\MNodBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\NodeBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\PatchBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\solidbox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\SpelBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\StaLBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Suppbox.bmp
# End Source File
# End Group
# End Target
# End Project
