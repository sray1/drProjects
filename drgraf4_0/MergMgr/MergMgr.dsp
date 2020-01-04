# Microsoft Developer Studio Project File - Name="MergMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MergMgr - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MergMgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MergMgr.mak" CFG="MergMgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MergMgr - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MergMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MergMgr - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "MergMgr - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MergMgr - Win32 Release"
# Name "MergMgr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CurMerg.cpp
# End Source File
# Begin Source File

SOURCE=.\DbMerg.cpp
# End Source File
# Begin Source File

SOURCE=.\DLDMerg.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_enoA.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_ENod.cpp
# End Source File
# Begin Source File

SOURCE=.\ElMerg.cpp
# End Source File
# Begin Source File

SOURCE=.\MergDlgM.cpp
# End Source File
# Begin Source File

SOURCE=.\MergDll.cpp
# End Source File
# Begin Source File

SOURCE=.\MergMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\MergMgr.def
# End Source File
# Begin Source File

SOURCE=.\MergMgr.rc
# End Source File
# Begin Source File

SOURCE=.\MergRsrc.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MNodMerg.cpp
# End Source File
# Begin Source File

SOURCE=.\NodMerg.cpp
# End Source File
# Begin Source File

SOURCE=.\PatMerg.cpp
# End Source File
# Begin Source File

SOURCE=.\Regen1D.cpp
# End Source File
# Begin Source File

SOURCE=.\Regen2D.cpp
# End Source File
# Begin Source File

SOURCE=.\Regen3D.cpp
# End Source File
# Begin Source File

SOURCE=.\RegenCur.cpp
# End Source File
# Begin Source File

SOURCE=.\RegenPat.cpp
# End Source File
# Begin Source File

SOURCE=.\RegenSol.cpp
# End Source File
# Begin Source File

SOURCE=.\SLDMerg.cpp
# End Source File
# Begin Source File

SOURCE=.\SLMCur.cpp
# End Source File
# Begin Source File

SOURCE=.\SLMNod.cpp
# End Source File
# Begin Source File

SOURCE=.\SLMPat.cpp
# End Source File
# Begin Source File

SOURCE=.\SolMerg.cpp
# End Source File
# Begin Source File

SOURCE=.\SpLMerg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SupMerg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CurMerg.h
# End Source File
# Begin Source File

SOURCE=.\DbMerg.h
# End Source File
# Begin Source File

SOURCE=.\DLdMerg.h
# End Source File
# Begin Source File

SOURCE=.\dlg_enoA.h
# End Source File
# Begin Source File

SOURCE=.\dlg_enod.h
# End Source File
# Begin Source File

SOURCE=.\MergDlgM.h
# End Source File
# Begin Source File

SOURCE=.\MergDll.h
# End Source File
# Begin Source File

SOURCE=.\MergMgr.h
# End Source File
# Begin Source File

SOURCE=.\MergRsrc.h
# End Source File
# Begin Source File

SOURCE=.\MmgrRsrc.h
# End Source File
# Begin Source File

SOURCE=.\MNodMerg.h
# End Source File
# Begin Source File

SOURCE=.\NodMerg.h
# End Source File
# Begin Source File

SOURCE=.\PatMerg.h
# End Source File
# Begin Source File

SOURCE=.\Regen1D.h
# End Source File
# Begin Source File

SOURCE=.\Regen2D.h
# End Source File
# Begin Source File

SOURCE=.\Regen3D.h
# End Source File
# Begin Source File

SOURCE=.\RegenCur.h
# End Source File
# Begin Source File

SOURCE=.\RegenPat.h
# End Source File
# Begin Source File

SOURCE=.\RegenSol.h
# End Source File
# Begin Source File

SOURCE=.\SLDMerg.h
# End Source File
# Begin Source File

SOURCE=.\SLMCur.h
# End Source File
# Begin Source File

SOURCE=.\SLMNod.h
# End Source File
# Begin Source File

SOURCE=.\SLMPat.h
# End Source File
# Begin Source File

SOURCE=.\SolMerg.h
# End Source File
# Begin Source File

SOURCE=.\SpLMerg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SupMerg.h
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
# Begin Source File

SOURCE=..\Applic\Res\Ico_pipe.ico
# End Source File
# Begin Source File

SOURCE=.\res\MergMgr.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
