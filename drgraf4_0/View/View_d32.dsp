# Microsoft Developer Studio Project File - Name="View_d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=View_d - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "View_d32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "View_d32.mak" CFG="View_d - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "View_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "View_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "View_d - Win32 Release"

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

!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W4 /GR /GX /ZI /Od /D "_AFXEXT" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFX_EXT" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 OMgr_D.lib Spec_D.lib Draw_D.lib Dr3D_D.lib EBox_D.lib DBox_D.lib SDlg_D.lib oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib OMgr_d32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:IX86 /def:".\View_d.def" /out:"c:\drgraf4_0\applic\Debug\View_d32.dll" /implib:"c:\drgraf4_0\applic\Debug\View_d32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "View_d - Win32 Release"
# Name "View_d - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Ax_wire0.cpp
# End Source File
# Begin Source File

SOURCE=.\Axisdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\Colorpal.cpp
# End Source File
# Begin Source File

SOURCE=.\Draxis.cpp
# End Source File
# Begin Source File

SOURCE=.\Light.cpp
# End Source File
# Begin Source File

SOURCE=.\Render.cpp
# End Source File
# Begin Source File

SOURCE=.\Rn_wire0.cpp
# End Source File
# Begin Source File

SOURCE=.\Rn_wire0.h
# End Source File
# Begin Source File

SOURCE=.\Rn_wire1.cpp
# End Source File
# Begin Source File

SOURCE=.\Rn_wire1.h
# End Source File
# Begin Source File

SOURCE=.\Rn_wire2.cpp
# End Source File
# Begin Source File

SOURCE=.\Rn_wire2.h
# End Source File
# Begin Source File

SOURCE=.\Textures.cpp
# End Source File
# Begin Source File

SOURCE=.\View.rc
# End Source File
# Begin Source File

SOURCE=.\View_d.def

!IF  "$(CFG)" == "View_d - Win32 Release"

!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Viewdll.cpp
# End Source File
# Begin Source File

SOURCE=.\Viewinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Zbuffer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Ax_wire0.h
# End Source File
# Begin Source File

SOURCE=.\Axisdraw.h
# End Source File
# Begin Source File

SOURCE=.\ColorPal.h
# End Source File
# Begin Source File

SOURCE=.\Draxis.h
# End Source File
# Begin Source File

SOURCE=.\Light.h
# End Source File
# Begin Source File

SOURCE=.\Render.h
# End Source File
# Begin Source File

SOURCE=.\Textures.h
# End Source File
# Begin Source File

SOURCE=.\ViewDll.h
# End Source File
# Begin Source File

SOURCE=.\Viewinfo.h
# End Source File
# Begin Source File

SOURCE=.\Zbuffer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\applic\RES\CURVEBIT.BMP
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
