# Microsoft Developer Studio Project File - Name="CreOpMgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CreOpMgr - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CreOpMgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CreOpMgr.mak" CFG="CreOpMgr - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CreOpMgr - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CreOpMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
F90=df.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

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

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /ZI /Od /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFX_EXT" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 IGBx_D32.lib OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_d32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib MO3D_D32.lib MMgr_D32.lib EMgr_D32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /def:".\CMgr_d.def" /out:"c:\drgraf4_0\applic\Debug/CMgr_D32.dll" /implib:"c:\drgraf4_0\applic\Debug/CMgr_D32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "CreOpMgr - Win32 Release"
# Name "CreOpMgr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CMgr.rc
# End Source File
# Begin Source File

SOURCE=.\CMgr_d.def

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CMgrDll.cpp
# End Source File
# Begin Source File

SOURCE=.\CMgrDll.h
# End Source File
# Begin Source File

SOURCE=.\CreODlgM.cpp
# End Source File
# Begin Source File

SOURCE=.\CreOpMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\CreOpMgr.h
# End Source File
# Begin Source File

SOURCE=.\CurCreOp.cpp
# End Source File
# Begin Source File

SOURCE=.\CurCreOp.h
# End Source File
# Begin Source File

SOURCE=.\DegElevate.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_croi.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CurveBlend.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_LALL.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_LSy3.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_LSym.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_SpnC.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_spnn.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_spnO.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_SpnP.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_SpnS.cpp
# End Source File
# Begin Source File

SOURCE=.\Mi_cprof.cpp
# End Source File
# Begin Source File

SOURCE=.\MI_CSPN.cpp
# End Source File
# Begin Source File

SOURCE=.\MI_NSPN.cpp
# End Source File
# Begin Source File

SOURCE=.\MI_OSPN.cpp
# End Source File
# Begin Source File

SOURCE=.\MI_PSPN.cpp
# End Source File
# Begin Source File

SOURCE=.\MI_SSPN.cpp
# End Source File
# Begin Source File

SOURCE=.\NodCreOp.cpp
# End Source File
# Begin Source File

SOURCE=.\NodCreOp.h
# End Source File
# Begin Source File

SOURCE=.\O3DCreOp.cpp
# End Source File
# Begin Source File

SOURCE=.\O3DCreOp.h
# End Source File
# Begin Source File

SOURCE=.\PatCreOp.cpp
# End Source File
# Begin Source File

SOURCE=.\PatCreOp.h
# End Source File
# Begin Source File

SOURCE=.\RegenCur.cpp
# End Source File
# Begin Source File

SOURCE=.\RegenNod.cpp
# End Source File
# Begin Source File

SOURCE=.\RegenPat.cpp
# End Source File
# Begin Source File

SOURCE=.\RegenProf_C.cpp
# End Source File
# Begin Source File

SOURCE=.\RegenSol.cpp
# End Source File
# Begin Source File

SOURCE=.\SolCreOp.cpp
# End Source File
# Begin Source File

SOURCE=.\SolCreOp.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CMgrRsrc.h
# End Source File
# Begin Source File

SOURCE=.\CreODlgM.h
# End Source File
# Begin Source File

SOURCE=.\DegElevate.h
# End Source File
# Begin Source File

SOURCE=.\dlg_croi.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CurveBlend.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_LALL.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_LSy3.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_LSym.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_LSyT.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_RotT.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SpnC.h
# End Source File
# Begin Source File

SOURCE=.\dlg_spnn.h
# End Source File
# Begin Source File

SOURCE=.\dlg_spnO.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SpnP.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_SpnS.h
# End Source File
# Begin Source File

SOURCE=.\DlgROTT.h
# End Source File
# Begin Source File

SOURCE=.\Mi_cprof.h
# End Source File
# Begin Source File

SOURCE=.\Mi_CSPN.h
# End Source File
# Begin Source File

SOURCE=.\Mi_NSPN.h
# End Source File
# Begin Source File

SOURCE=.\Mi_OSPN.h
# End Source File
# Begin Source File

SOURCE=.\Mi_PSPN.h
# End Source File
# Begin Source File

SOURCE=.\Mi_SSPN.h
# End Source File
# Begin Source File

SOURCE=.\RegenCur.h
# End Source File
# Begin Source File

SOURCE=.\RegenNod.h
# End Source File
# Begin Source File

SOURCE=.\RegenPat.h
# End Source File
# Begin Source File

SOURCE=.\RegenProf_C.h
# End Source File
# Begin Source File

SOURCE=.\RegenSol.h
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
