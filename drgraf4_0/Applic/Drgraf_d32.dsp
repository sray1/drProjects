# Microsoft Developer Studio Project File - Name="Drgraf_d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Drgraf_d - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Drgraf_d32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Drgraf_d32.mak" CFG="Drgraf_d - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Drgraf_d - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Drgraf_d - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Drgraf_d - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"STDAFX.H" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib /nologo /stack:0x5000 /subsystem:windows /machine:IX86
# ADD LINK32 oldnames.lib /nologo /stack:0x5000 /subsystem:windows /machine:IX86

!ELSEIF  "$(CFG)" == "Drgraf_d - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /Fd"DRGRAF.PDB" /c
# ADD CPP /nologo /MDd /W4 /GR /GX /ZI /Od /D "_AFXDLL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFX_EXT" /YX"stdafx.h" /Fd".\DRGRAF.PDB" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 View_D.lib OMgr_D.lib Dr3D_D.lib MMgr_D.lib Spec_D.lib SDlg_D.lib Elem_D.lib EDlg_D.lib Draw_D.lib DDlg_D.lib EBox_D.lib DBox_D.lib oldnames.lib ver.lib /nologo /stack:0x9c40 /subsystem:windows /map /debug /machine:IX86
# ADD LINK32 winMM.lib Dr3D_D32.lib Spec_D32.lib Mesh_d32.lib Elem_D32.lib OGen_D32.lib Draw_D32.lib Supp_D32.lib StaL_D32.lib OMgr_D32.lib SDlg_D32.lib EDlg_D32.lib DDlg_D32.lib IGBx_D32.lib EBox_D32.lib DBox_D32.lib MMgr_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib MO3D_D32.lib MSup_D32.lib MStL_D32.lib CMgr_D32.lib EMgr_D32.lib DMGR_D32.lib PMgr_D32.lib MMs0_D32.lib MMs1_D32.lib MMs2_D32.lib CreM_D32.lib Mdit_D32.lib Deck_D32.lib View_D32.lib Auxi_D32.lib DBase_D32.lib /nologo /subsystem:windows /incremental:no /map /debug /machine:IX86 /out:"c:\drgraf4_0\Applic\Debug\Drgraf_d32.exe"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Drgraf_d - Win32 Release"
# Name "Drgraf_d - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\12view.cpp
# End Source File
# Begin Source File

SOURCE=.\23view.cpp
# End Source File
# Begin Source File

SOURCE=.\31view.cpp
# End Source File
# Begin Source File

SOURCE=.\3dview.cpp
# End Source File
# Begin Source File

SOURCE=.\Aboutbox.cpp
# End Source File
# Begin Source File

SOURCE=.\ADlgMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\AxDataVu.cpp
# End Source File
# Begin Source File

SOURCE=.\AxDrawVu.cpp
# End Source File
# Begin Source File

SOURCE=.\Banner.cpp
# End Source File
# Begin Source File

SOURCE=.\Clock.cpp
# End Source File
# Begin Source File

SOURCE=.\Cntritem.cpp
# End Source File
# Begin Source File

SOURCE=.\Dataview.cpp
# End Source File
# Begin Source File

SOURCE=.\DeckView.cpp
# End Source File
# Begin Source File

SOURCE=.\DeckView.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CTim.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_NoEL.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_NoEL.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_NoLE.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_NoLE.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Shrink.cpp
# End Source File
# Begin Source File

SOURCE=.\Drawview.cpp
# End Source File
# Begin Source File

SOURCE=.\Drgracfm.cpp
# End Source File
# Begin Source File

SOURCE=.\Drgradoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Drgraf.cpp
# End Source File
# Begin Source File

SOURCE=.\Drgraf.rc
# End Source File
# Begin Source File

SOURCE=.\Drgraf_d.def
# End Source File
# Begin Source File

SOURCE=.\Drgrafrm.cpp
# End Source File
# Begin Source File

SOURCE=.\DrSplit.cpp
# End Source File
# Begin Source File

SOURCE=.\Drstatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DVM_CreM.cpp
# End Source File
# Begin Source File

SOURCE=.\DVM_CreO.cpp
# End Source File
# Begin Source File

SOURCE=.\DVM_Del.cpp
# End Source File
# Begin Source File

SOURCE=.\DVM_Edit.cpp
# End Source File
# Begin Source File

SOURCE=.\DVM_Genr.cpp
# End Source File
# Begin Source File

SOURCE=.\DVM_Mdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DVM_Post.cpp
# End Source File
# Begin Source File

SOURCE=.\HsDataVu.cpp
# End Source File
# Begin Source File

SOURCE=.\HsDrawVu.cpp
# End Source File
# Begin Source File

SOURCE=.\Mdib.cpp
# End Source File
# Begin Source File

SOURCE=.\MsDataVu.cpp
# End Source File
# Begin Source File

SOURCE=.\Oldglob.cpp
# End Source File
# Begin Source File

SOURCE=.\Oldstat.cpp
# End Source File
# Begin Source File

SOURCE=.\OldTool.cpp
# End Source File
# Begin Source File

SOURCE=.\ProbElemDim.cpp
# End Source File
# Begin Source File

SOURCE=.\Rowview.cpp
# End Source File
# Begin Source File

SOURCE=.\SpDataVu.cpp
# End Source File
# Begin Source File

SOURCE=.\SpDrawVu.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\StatCntl.cpp
# End Source File
# Begin Source File

SOURCE=.\Stdafx.cpp
# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"
# End Source File
# Begin Source File

SOURCE=.\XVM_Genr.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\12view.h
# End Source File
# Begin Source File

SOURCE=.\23view.h
# End Source File
# Begin Source File

SOURCE=.\31view.h
# End Source File
# Begin Source File

SOURCE=.\3dview.h
# End Source File
# Begin Source File

SOURCE=.\Aboutbox.h
# End Source File
# Begin Source File

SOURCE=.\ADlgMgr.h
# End Source File
# Begin Source File

SOURCE=.\AxDataVu.h
# End Source File
# Begin Source File

SOURCE=.\AxDrawVu.h
# End Source File
# Begin Source File

SOURCE=.\Banner.h
# End Source File
# Begin Source File

SOURCE=.\Clock.h
# End Source File
# Begin Source File

SOURCE=.\Cntritem.h
# End Source File
# Begin Source File

SOURCE=.\Dataview.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_CTim.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Shrink.h
# End Source File
# Begin Source File

SOURCE=.\drawview.h
# End Source File
# Begin Source File

SOURCE=.\Drgracfm.h
# End Source File
# Begin Source File

SOURCE=.\Drgradoc.h
# End Source File
# Begin Source File

SOURCE=.\Drgraf.h
# End Source File
# Begin Source File

SOURCE=.\Drgrafrm.h
# End Source File
# Begin Source File

SOURCE=.\DrSplit.h
# End Source File
# Begin Source File

SOURCE=.\Drstatus.h
# End Source File
# Begin Source File

SOURCE=.\DVM_CreM.h
# End Source File
# Begin Source File

SOURCE=.\DVM_Del.h
# End Source File
# Begin Source File

SOURCE=.\DVM_Edit.h
# End Source File
# Begin Source File

SOURCE=.\DVM_Genr.h
# End Source File
# Begin Source File

SOURCE=.\DVM_Mdit.h
# End Source File
# Begin Source File

SOURCE=.\HsDataVu.h
# End Source File
# Begin Source File

SOURCE=.\HsDrawVu.h
# End Source File
# Begin Source File

SOURCE=.\Mdib.h
# End Source File
# Begin Source File

SOURCE=.\Oldglob.h
# End Source File
# Begin Source File

SOURCE=.\Oldstat.h
# End Source File
# Begin Source File

SOURCE=.\OldTool.h
# End Source File
# Begin Source File

SOURCE=.\ProbElemDim.h
# End Source File
# Begin Source File

SOURCE=.\resource.hm
# End Source File
# Begin Source File

SOURCE=.\SpDataVu.h
# End Source File
# Begin Source File

SOURCE=.\SpDrawVu.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\statcntl.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\XVM_Genr.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\BUTTON.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\DRCAFE.BMP
# End Source File
# Begin Source File

SOURCE=.\res\drgraf.rc2
# End Source File
# Begin Source File

SOURCE=.\RES\DSICON.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\DSICON2.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\IMAGE1D.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\IMAGE1F.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\IMAGE1U.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\IMAGE2D.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\IMAGE2F.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\IMAGE2U.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\JASMIN.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\SEASHORE.BMP
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\TOOLBAR.BMP
# End Source File
# End Group
# Begin Source File

SOURCE=.\temp.txt
# End Source File
# End Target
# End Project
# Section Drgraf_d : {2E370310-4BFD-11CF-9A10-88537EDAE885}
# 	0:8:Splash.h:D:\drgraf4_0\Applic\Splash.h
# 	0:10:Splash.cpp:D:\drgraf4_0\Applic\Splash.cpp
# 	1:10:IDB_SPLASH:103
# 	2:10:ResHdrName:resource.h
# 	2:11:ProjHdrName:stdafx.h
# 	2:10:WrapperDef:_SPLASH_SCRN_
# 	2:12:SplClassName:CSplashCom
# 	2:21:SplashScreenInsertKey:4.0
# 	2:10:HeaderName:Splash.h
# 	2:10:ImplemName:Splash.cpp
# 	2:7:BmpID16:IDB_SPLASH
# End Section