# Microsoft Developer Studio Project File - Name="EditMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=EditMgr - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EditMgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EditMgr.mak" CFG="EditMgr - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EditMgr - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EditMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EditMgr - Win32 Release"

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
# ADD BASE F90 /compile_only /nologo /threads /I "Release/"
# ADD F90 /compile_only /nologo /threads /I "Release/"
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

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

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
# ADD BASE F90 /compile_only /debug:full /nologo /threads /I "Debug/"
# ADD F90 /compile_only /debug:full /nologo /threads /I "Debug/"
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /ZI /Od /D "_AFXEXT" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFX_EXT" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib MMgr_D32.lib CMgr_D32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /def:".\Emgr_d.def" /out:"c:\drgraf4_0\applic\Debug\EMgr_d32.dll" /implib:"c:\drgraf4_0\applic\Debug/EMgr_d32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "EditMgr - Win32 Release"
# Name "EditMgr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CurEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\CurEdit.h
# End Source File
# Begin Source File

SOURCE=.\DLDEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DLdEdit.h
# End Source File
# Begin Source File

SOURCE=.\dlg_enoA.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_ENod.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDlgM.cpp
# End Source File
# Begin Source File

SOURCE=.\EditMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\EditMgr.h
# End Source File
# Begin Source File

SOURCE=.\Emgr.rc
# End Source File
# Begin Source File

SOURCE=.\Emgr_d.def

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EmgrDll.cpp
# End Source File
# Begin Source File

SOURCE=.\EmgrDll.h
# End Source File
# Begin Source File

SOURCE=.\EmgrRsrc.h
# End Source File
# Begin Source File

SOURCE=.\NodEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\NodEdit.h
# End Source File
# Begin Source File

SOURCE=.\PatEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\PatEdit.h
# End Source File
# Begin Source File

SOURCE=.\SLDEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\SLDEdit.h
# End Source File
# Begin Source File

SOURCE=.\SolEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\SolEdit.h
# End Source File
# Begin Source File

SOURCE=.\SpLEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\SpLEdit.h
# End Source File
# Begin Source File

SOURCE=.\SupEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\SupEdit.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\dlg_enoA.h
# End Source File
# Begin Source File

SOURCE=.\dlg_enod.h
# End Source File
# Begin Source File

SOURCE=.\EditDlgM.h
# End Source File
# Begin Source File

SOURCE=..\MditMgr\Regen1D.h
# End Source File
# Begin Source File

SOURCE=..\MditMgr\Regen2D.h
# End Source File
# Begin Source File

SOURCE=..\MditMgr\Regen3D.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
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
# End Group
# End Target
# End Project
