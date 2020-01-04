# Microsoft Developer Studio Project File - Name="GenObjs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GenObjs - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GenObjs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GenObjs.mak" CFG="GenObjs - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GenObjs - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GenObjs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GenObjs - Win32 Release"

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

!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "_AFXEXT" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFX_EXT" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /def:".\GenObj_d.def" /out:"c:\drgraf4_0\applic\Debug/OGen_D32.dll" /implib:"c:\drgraf4_0\applic\Debug/OGen_D32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "GenObjs - Win32 Release"
# Name "GenObjs - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Curve.cpp
# End Source File
# Begin Source File

SOURCE=.\Curve_1.cpp
# End Source File
# Begin Source File

SOURCE=.\Curve_2.cpp
# End Source File
# Begin Source File

SOURCE=.\Curve_3.cpp
# End Source File
# Begin Source File

SOURCE=.\Drcurve.cpp
# End Source File
# Begin Source File

SOURCE=.\Drnode.cpp
# End Source File
# Begin Source File

SOURCE=.\Drnode.h
# End Source File
# Begin Source File

SOURCE=.\Drobj3d.cpp
# End Source File
# Begin Source File

SOURCE=.\Drpatch.cpp
# End Source File
# Begin Source File

SOURCE=.\Drprof_c.cpp
# End Source File
# Begin Source File

SOURCE=.\Drprof_P.cpp
# End Source File
# Begin Source File

SOURCE=.\Drprof_P.h
# End Source File
# Begin Source File

SOURCE=.\Drsolid.cpp
# End Source File
# Begin Source File

SOURCE=.\GenObj_d.def

!IF  "$(CFG)" == "GenObjs - Win32 Release"

!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OGen_dll.cpp
# End Source File
# Begin Source File

SOURCE=.\Pat_SubDiv4.cpp
# End Source File
# Begin Source File

SOURCE=.\Pat_Tan3.cpp
# End Source File
# Begin Source File

SOURCE=.\Pat_Tan3.h
# End Source File
# Begin Source File

SOURCE=.\Pat_Tan4.cpp
# End Source File
# Begin Source File

SOURCE=.\Pat_Tan4.h
# End Source File
# Begin Source File

SOURCE=.\Pat_Twist4.cpp
# End Source File
# Begin Source File

SOURCE=.\Pentahed.cpp
# End Source File
# Begin Source File

SOURCE=.\Rat_Twist4.cpp
# End Source File
# Begin Source File

SOURCE=.\Solid4.cpp
# End Source File
# Begin Source File

SOURCE=.\SolidHex.cpp
# End Source File
# Begin Source File

SOURCE=.\SolidPen.cpp
# End Source File
# Begin Source File

SOURCE=.\Surface3.cpp
# End Source File
# Begin Source File

SOURCE=.\Surface4.cpp
# End Source File
# Begin Source File

SOURCE=.\Triangle.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Curve.h
# End Source File
# Begin Source File

SOURCE=.\Curve_1.h
# End Source File
# Begin Source File

SOURCE=.\Curve_2.h
# End Source File
# Begin Source File

SOURCE=.\Curve_3.h
# End Source File
# Begin Source File

SOURCE=.\Drcurve.h
# End Source File
# Begin Source File

SOURCE=.\Drobj3d.h
# End Source File
# Begin Source File

SOURCE=.\Drpatch.h
# End Source File
# Begin Source File

SOURCE=.\Drprof_c.h
# End Source File
# Begin Source File

SOURCE=.\Drsolid.h
# End Source File
# Begin Source File

SOURCE=.\OGen_dll.h
# End Source File
# Begin Source File

SOURCE=.\Pat_Twist4.h
# End Source File
# Begin Source File

SOURCE=..\DataBase\PatchGeomPage.h
# End Source File
# Begin Source File

SOURCE=.\Pentahed.h
# End Source File
# Begin Source File

SOURCE=.\Rat_Twist4.h
# End Source File
# Begin Source File

SOURCE=.\Solid4.h
# End Source File
# Begin Source File

SOURCE=.\SolidHex.h
# End Source File
# Begin Source File

SOURCE=.\SolidPen.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Surface3.h
# End Source File
# Begin Source File

SOURCE=.\Surface4.h
# End Source File
# Begin Source File

SOURCE=.\Triangle.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project