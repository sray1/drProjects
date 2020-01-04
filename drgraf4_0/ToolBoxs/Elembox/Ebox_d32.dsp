# Microsoft Developer Studio Project File - Name="Ebox_d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Ebox_d - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ebox_d32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ebox_d32.mak" CFG="Ebox_d - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ebox_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Ebox_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W4 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MD /W4 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
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

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /Fd"E_BOX.PDB" /c
# ADD CPP /nologo /MDd /W4 /GX /ZI /Od /D "_AFXEXT" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFX_EXT" /YX"stdafx.h" /Fd".\E_BOX.PDB" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ldllcew.lib oldnames.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib /nologo /subsystem:windows /dll /incremental:no /map:"c:\drgraf4_0\toolboxs\elembox\Debug\Ebox_d32.map" /debug /machine:IX86 /def:".\Ebox_d.def" /out:"c:\drgraf4_0\applic\Debug\Ebox_d32.dll" /implib:"c:\drgraf4_0\applic\Debug\Ebox_d32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Ebox_d - Win32 Release"
# Name "Ebox_d - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Ebox.rc
# End Source File
# Begin Source File

SOURCE=.\Ebox_d.def

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Eboxdll.cpp
# End Source File
# Begin Source File

SOURCE=.\EoxWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\EoxWnd.h
# End Source File
# Begin Source File

SOURCE=.\Hexbar.cpp
# End Source File
# Begin Source File

SOURCE=.\HexBar.h
# End Source File
# Begin Source File

SOURCE=.\Hexbox.cpp
# End Source File
# Begin Source File

SOURCE=.\Hexbox.h
# End Source File
# Begin Source File

SOURCE=.\MeshBar0.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshBar0.h
# End Source File
# Begin Source File

SOURCE=.\MeshBar1.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshBar1.h
# End Source File
# Begin Source File

SOURCE=.\MeshBar2.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshBar2.h
# End Source File
# Begin Source File

SOURCE=.\MeshBar3.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshBar3.h
# End Source File
# Begin Source File

SOURCE=.\MeshBox0.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshBox0.h
# End Source File
# Begin Source File

SOURCE=.\MeshBox1.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshBox1.h
# End Source File
# Begin Source File

SOURCE=.\MeshBox2.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshBox2.h
# End Source File
# Begin Source File

SOURCE=.\MeshBox3.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshBox3.h
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

SOURCE=.\Penbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Penbar.h
# End Source File
# Begin Source File

SOURCE=.\Penbox.cpp
# End Source File
# Begin Source File

SOURCE=.\Penbox.h
# End Source File
# Begin Source File

SOURCE=.\Pipebar.cpp
# End Source File
# Begin Source File

SOURCE=.\Pipebar.h
# End Source File
# Begin Source File

SOURCE=.\PipeBox.cpp
# End Source File
# Begin Source File

SOURCE=.\PipeBox.h
# End Source File
# Begin Source File

SOURCE=.\Quadbar.cpp
# End Source File
# Begin Source File

SOURCE=.\QuadBar.h
# End Source File
# Begin Source File

SOURCE=.\Quadbox.cpp
# End Source File
# Begin Source File

SOURCE=.\Quadbox.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\Tetbar.cpp
# End Source File
# Begin Source File

SOURCE=.\TETBar.h
# End Source File
# Begin Source File

SOURCE=.\Tetbox.cpp
# End Source File
# Begin Source File

SOURCE=.\TETbox.h
# End Source File
# Begin Source File

SOURCE=.\Tribar.cpp
# End Source File
# Begin Source File

SOURCE=.\Tribar.h
# End Source File
# Begin Source File

SOURCE=.\Tribox.cpp
# End Source File
# Begin Source File

SOURCE=.\Tribox.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\EBoxDll.h
# End Source File
# Begin Source File

SOURCE=.\EoxBMPID.h
# End Source File
# Begin Source File

SOURCE=.\EoxWndID.h
# End Source File
# Begin Source File

SOURCE=.\HEXbutt.h
# End Source File
# Begin Source File

SOURCE=.\Meshbut0.h
# End Source File
# Begin Source File

SOURCE=.\Meshbut1.h
# End Source File
# Begin Source File

SOURCE=.\Meshbut2.h
# End Source File
# Begin Source File

SOURCE=.\Meshbut3.h
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

SOURCE=.\PENbutt.h
# End Source File
# Begin Source File

SOURCE=.\PIPEbutt.h
# End Source File
# Begin Source File

SOURCE=.\Quadbutt.h
# End Source File
# Begin Source File

SOURCE=.\TETbutt.h
# End Source File
# Begin Source File

SOURCE=.\TRIbutt.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\brickbox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Button.cur
# End Source File
# Begin Source File

SOURCE=.\Res\hexbox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\MeshBox0.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\MeshBox1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\MeshBox2.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\MeshBox3.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\penbox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pipebox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\quadbox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\tetBox.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\tribox.bmp
# End Source File
# End Group
# End Target
# End Project
