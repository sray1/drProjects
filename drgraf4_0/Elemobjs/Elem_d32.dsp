# Microsoft Developer Studio Project File - Name="Elem_d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Elem_d - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Elem_d32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Elem_d32.mak" CFG="Elem_d - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Elem_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Elem_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Elem_d - Win32 Release"

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

!ELSEIF  "$(CFG)" == "Elem_d - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MESSAGETRACE" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W4 /GX /ZI /Od /D "_MESSAGETRACE" /D "_AFXEXT" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFX_EXT" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Spec_D.lib Dr3D_D.lib oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib OGen_D32.lib Mesh_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:IX86 /def:".\Elem_d.def" /out:"c:\drgraf4_0\applic\Debug\Elem_d32.dll" /implib:"c:\drgraf4_0\applic\Debug\Elem_d32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Elem_d - Win32 Release"
# Name "Elem_d - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Dr_Qu_12.cpp
# End Source File
# Begin Source File

SOURCE=.\Dr_Qu_12.h
# End Source File
# Begin Source File

SOURCE=.\Dr_Qu_16.cpp
# End Source File
# Begin Source File

SOURCE=.\Dr_Qu_16.h
# End Source File
# Begin Source File

SOURCE=.\Dr_Qu_4.cpp
# End Source File
# Begin Source File

SOURCE=.\Dr_Qu_4.h
# End Source File
# Begin Source File

SOURCE=.\Dr_Qu_8.cpp
# End Source File
# Begin Source File

SOURCE=.\Dr_Qu_8.h
# End Source File
# Begin Source File

SOURCE=.\Dr_Qu_9.cpp
# End Source File
# Begin Source File

SOURCE=.\Dr_Qu_9.h
# End Source File
# Begin Source File

SOURCE=.\Dr_Tr_10.cpp
# End Source File
# Begin Source File

SOURCE=.\Dr_Tr_10.h
# End Source File
# Begin Source File

SOURCE=.\Dr_Tr_3.cpp
# End Source File
# Begin Source File

SOURCE=.\Dr_Tr_3.h
# End Source File
# Begin Source File

SOURCE=.\Dr_Tr_6.cpp
# End Source File
# Begin Source File

SOURCE=.\Dr_Tr_6.h
# End Source File
# Begin Source File

SOURCE=.\Dr_Tr_9.cpp
# End Source File
# Begin Source File

SOURCE=.\Dr_Tr_9.h
# End Source File
# Begin Source File

SOURCE=.\DrBeam.cpp
# End Source File
# Begin Source File

SOURCE=.\DrBeam.h
# End Source File
# Begin Source File

SOURCE=.\DrElbow.cpp
# End Source File
# Begin Source File

SOURCE=.\DrElbow.h
# End Source File
# Begin Source File

SOURCE=.\Drpipe.cpp
# End Source File
# Begin Source File

SOURCE=.\DrPipe.h
# End Source File
# Begin Source File

SOURCE=.\DrTruss.cpp
# End Source File
# Begin Source File

SOURCE=.\DrTruss.h
# End Source File
# Begin Source File

SOURCE=.\Elem_d.def

!IF  "$(CFG)" == "Elem_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Elem_d - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Elemdll.cpp
# End Source File
# Begin Source File

SOURCE=.\ElemInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ElemInfo.h
# End Source File
# Begin Source File

SOURCE=.\Mat_0D.cpp
# End Source File
# Begin Source File

SOURCE=.\Mat_0D.h
# End Source File
# Begin Source File

SOURCE=.\Mat_1D.cpp
# End Source File
# Begin Source File

SOURCE=.\Mat_1D.h
# End Source File
# Begin Source File

SOURCE=.\Mat_2D.cpp
# End Source File
# Begin Source File

SOURCE=.\Mat_2D.h
# End Source File
# Begin Source File

SOURCE=.\Pro_BEAM.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_BEAM.h
# End Source File
# Begin Source File

SOURCE=.\Pro_Pipe.cpp
# End Source File
# Begin Source File

SOURCE=.\Pro_Pipe.h
# End Source File
# Begin Source File

SOURCE=.\Property.cpp
# End Source File
# Begin Source File

SOURCE=.\Property.h
# End Source File
# Begin Source File

SOURCE=.\Release.cpp
# End Source File
# Begin Source File

SOURCE=.\Release.h
# End Source File
# Begin Source File

SOURCE=.\SIndex.cpp
# End Source File
# Begin Source File

SOURCE=.\SIndex.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Elemdll.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
