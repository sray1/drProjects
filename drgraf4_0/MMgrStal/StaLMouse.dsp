# Microsoft Developer Studio Project File - Name="StaLMouse" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=StaLMouse - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StaLMouse.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StaLMouse.mak" CFG="StaLMouse - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StaLMouse - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "StaLMouse - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

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

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

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
# ADD RSC /l 0x409 /fo".\StaLMgr.res" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib Dr3D_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_d32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /def:".\MStL_d.def" /out:"c:/drGraf4_0/Applic/Debug/MStL_D32.dll" /implib:"c:/drGraf4_0/Applic/Debug/MStL_D32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "StaLMouse - Win32 Release"
# Name "StaLMouse - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Dlg_IsoP.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_IsoP.h
# End Source File
# Begin Source File

SOURCE=.\dlg_Many.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_Many.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_StLA.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_StLA.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_StLC.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_StLC.h
# End Source File
# Begin Source File

SOURCE=.\dlg_StLI.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_StLI.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Uniform.cpp
# End Source File
# Begin Source File

SOURCE=.\Mi_StaL.cpp
# End Source File
# Begin Source File

SOURCE=.\Mi_StaL.h
# End Source File
# Begin Source File

SOURCE=.\MStL_d.def

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MSTLdll.cpp
# End Source File
# Begin Source File

SOURCE=.\MSTLMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\MSTLMgr.h
# End Source File
# Begin Source File

SOURCE=.\MSTLRsrc.h
# End Source File
# Begin Source File

SOURCE=.\SLDCur.cpp
# End Source File
# Begin Source File

SOURCE=.\SLDNod.cpp
# End Source File
# Begin Source File

SOURCE=.\SLDObj.cpp
# End Source File
# Begin Source File

SOURCE=.\SLDPat.cpp
# End Source File
# Begin Source File

SOURCE=.\StaLMgr.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Dlg_Uniform.h
# End Source File
# Begin Source File

SOURCE=.\MSTLdll.h
# End Source File
# Begin Source File

SOURCE=.\MSTLRsrc.hm
# End Source File
# Begin Source File

SOURCE=.\SLDCur.h
# End Source File
# Begin Source File

SOURCE=.\SLDNod.h
# End Source File
# Begin Source File

SOURCE=.\SLDObj.h
# End Source File
# Begin Source File

SOURCE=.\SLDPat.h
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
