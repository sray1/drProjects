# Microsoft Developer Studio Project File - Name="MeshObj" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MeshObj - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MeshObj.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MeshObj.mak" CFG="MeshObj - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MeshObj - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MeshObj - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MeshObj - Win32 Release"

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

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "_AFXEXT" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFX_EXT" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib OGen_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /def:".\MeshObj.def" /out:"c:\drgraf4_0\applic\Debug/Mesh_D32.dll" /implib:"c:\drgraf4_0\applic\Debug/Mesh_D32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "MeshObj - Win32 Release"
# Name "MeshObj - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\DrEdge.cpp
# End Source File
# Begin Source File

SOURCE=.\DrFace.cpp
# End Source File
# Begin Source File

SOURCE=.\DrFE0D.cpp
# End Source File
# Begin Source File

SOURCE=.\DrFE1D.cpp
# End Source File
# Begin Source File

SOURCE=.\DrFE2D.cpp
# End Source File
# Begin Source File

SOURCE=.\DrFE3D.cpp
# End Source File
# Begin Source File

SOURCE=.\DrMesh1D.cpp
# End Source File
# Begin Source File

SOURCE=.\DrMesh2D.cpp
# End Source File
# Begin Source File

SOURCE=.\DrMesh3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Drprof_1.cpp
# End Source File
# Begin Source File

SOURCE=.\Drprof_2.cpp
# End Source File
# Begin Source File

SOURCE=.\EdgeInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\FaceInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Mesh_dll.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshObj.def

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MeshObj.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\DrEdge.h
# End Source File
# Begin Source File

SOURCE=.\DrFace.h
# End Source File
# Begin Source File

SOURCE=.\DrFE0D.h
# End Source File
# Begin Source File

SOURCE=.\DrFE1D.h
# End Source File
# Begin Source File

SOURCE=.\DrFE2D.h
# End Source File
# Begin Source File

SOURCE=.\DrFE3D.h
# End Source File
# Begin Source File

SOURCE=.\DrMbj3d.h
# End Source File
# Begin Source File

SOURCE=.\DrMesh1D.h
# End Source File
# Begin Source File

SOURCE=.\DrMesh2D.h
# End Source File
# Begin Source File

SOURCE=.\DrMesh3D.h
# End Source File
# Begin Source File

SOURCE=.\Drprof_1.h
# End Source File
# Begin Source File

SOURCE=.\Drprof_2.h
# End Source File
# Begin Source File

SOURCE=.\EdgeInfo.h
# End Source File
# Begin Source File

SOURCE=.\FaceInfo.h
# End Source File
# Begin Source File

SOURCE=.\Mesh_dll.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\MeshObj.rc2
# End Source File
# End Group
# End Target
# End Project
