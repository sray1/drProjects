# Microsoft Developer Studio Project File - Name="MMgrMs2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MMgrMs2 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MMgrMs2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMgrMs2.mak" CFG="MMgrMs2 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MMgrMs2 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MMgrMs2 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MMgrMs2 - Win32 Release"

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

!ELSEIF  "$(CFG)" == "MMgrMs2 - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib OGen_D32.lib Dr3D_D32.lib MMgr_D32.lib MNod_D32.lib MMs0_D32.lib MMs1_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /def:".\MMs2Mgr.def" /out:"c:\drgraf4_0\applic\Debug/MMs2_D32.dll" /implib:"c:\drgraf4_0\applic\Debug/MMs2_D32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "MMgrMs2 - Win32 Release"
# Name "MMgrMs2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Dlg_2Mrg.cpp
# End Source File
# Begin Source File

SOURCE=.\Mi_2Prof.cpp
# End Source File
# Begin Source File

SOURCE=.\Mi_Gang2.cpp
# End Source File
# Begin Source File

SOURCE=.\Mi_Qang2.cpp
# End Source File
# Begin Source File

SOURCE=.\Mi_Tang2.cpp
# End Source File
# Begin Source File

SOURCE=.\MMs2dll.cpp
# End Source File
# Begin Source File

SOURCE=.\MMs2dll.h
# End Source File
# Begin Source File

SOURCE=.\MMs2Mgr.cpp
# End Source File
# Begin Source File

SOURCE=.\MMs2Mgr.def

!IF  "$(CFG)" == "MMgrMs2 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MMs2Mgr.h
# End Source File
# Begin Source File

SOURCE=.\MMs2Mgr.rc
# End Source File
# Begin Source File

SOURCE=.\MMs2Rsrc.h
# End Source File
# Begin Source File

SOURCE=.\Po_FE2D.cpp
# End Source File
# Begin Source File

SOURCE=.\Po_Qu_12.cpp
# End Source File
# Begin Source File

SOURCE=.\Po_Qu_16.cpp
# End Source File
# Begin Source File

SOURCE=.\Po_Qu_4.cpp
# End Source File
# Begin Source File

SOURCE=.\Po_Qu_8.cpp
# End Source File
# Begin Source File

SOURCE=.\Po_Qu_9.cpp
# End Source File
# Begin Source File

SOURCE=.\Po_Tr_10.cpp
# End Source File
# Begin Source File

SOURCE=.\Po_Tr_3.cpp
# End Source File
# Begin Source File

SOURCE=.\Po_Tr_6.cpp
# End Source File
# Begin Source File

SOURCE=.\Po_Tr_9.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Dlg_2Mrg.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Spn2.h
# End Source File
# Begin Source File

SOURCE=.\Mi_2Prof.h
# End Source File
# Begin Source File

SOURCE=.\Mi_2SPN.h
# End Source File
# Begin Source File

SOURCE=.\Mi_Gang2.h
# End Source File
# Begin Source File

SOURCE=.\Mi_Qang2.h
# End Source File
# Begin Source File

SOURCE=.\Mi_Tang2.h
# End Source File
# Begin Source File

SOURCE=.\MMs2Rsrc.hm
# End Source File
# Begin Source File

SOURCE=.\Po_FE2D.h
# End Source File
# Begin Source File

SOURCE=.\Po_Qu_12.h
# End Source File
# Begin Source File

SOURCE=.\Po_Qu_16.h
# End Source File
# Begin Source File

SOURCE=.\Po_Qu_4.h
# End Source File
# Begin Source File

SOURCE=.\Po_Qu_8.h
# End Source File
# Begin Source File

SOURCE=.\Po_Qu_9.h
# End Source File
# Begin Source File

SOURCE=.\Po_Tr_10.h
# End Source File
# Begin Source File

SOURCE=.\Po_Tr_3.h
# End Source File
# Begin Source File

SOURCE=.\Po_Tr_6.h
# End Source File
# Begin Source File

SOURCE=.\Po_Tr_9.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\Applic\Res\Curvebit.bmp
# End Source File
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
