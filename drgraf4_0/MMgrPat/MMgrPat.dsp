# Microsoft Developer Studio Project File - Name="MMgrPat" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MMgrPat - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MMgrPat.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMgrPat.mak" CFG="MMgrPat - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MMgrPat - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MMgrPat - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

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

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

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
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib OGen_D32.lib Dr3D_D32.lib MNod_D32.lib MCur_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /def:".\MPatMgr.def" /out:"c:\drgraf4_0\applic\Debug/MPat_D32.dll" /implib:"c:\drgraf4_0\applic\Debug/MPat_D32.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "MMgrPat - Win32 Release"
# Name "MMgrPat - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BasePage.cpp
# End Source File
# Begin Source File

SOURCE=.\DegElevate.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CooT.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_CooT.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Gordon.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_LoftCC.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_loftX.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PatT.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PatT.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Coons.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Duct.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_pi_EndCond.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Gordon.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Loft.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Revolv.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Sweep.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Tensor.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Xtrude.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Radius.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_rend.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_rend.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_tang.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_TenBlend.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Tensor.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_Torq.cpp
# End Source File
# Begin Source File

SOURCE=.\Loft_Com.cpp
# End Source File
# Begin Source File

SOURCE=.\Mi_gangp.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp_CooP3.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp_CooP4.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp_duct.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp_Gordon.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp_loftX.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp_rotat.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp_sweep.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp_Tensor.cpp
# End Source File
# Begin Source File

SOURCE=.\Mp_xtrud.cpp
# End Source File
# Begin Source File

SOURCE=.\MPatdll.cpp
# End Source File
# Begin Source File

SOURCE=.\MPatdll.h
# End Source File
# Begin Source File

SOURCE=.\MPatMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\MPatMgr.def

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MPatMgr.h
# End Source File
# Begin Source File

SOURCE=.\MPatMgr.rc
# End Source File
# Begin Source File

SOURCE=.\MPatRsrc.h
# End Source File
# Begin Source File

SOURCE=.\Pa_CoonP.cpp
# End Source File
# Begin Source File

SOURCE=.\Pa_CooP3.cpp
# End Source File
# Begin Source File

SOURCE=.\Pa_duct.cpp
# End Source File
# Begin Source File

SOURCE=.\Pa_loft2.cpp
# End Source File
# Begin Source File

SOURCE=.\Pa_loft4.cpp
# End Source File
# Begin Source File

SOURCE=.\Pa_rotat.cpp
# End Source File
# Begin Source File

SOURCE=.\Pa_sweep.cpp
# End Source File
# Begin Source File

SOURCE=.\Pa_xtrud.cpp
# End Source File
# Begin Source File

SOURCE=.\Sheet_PATI.cpp
# End Source File
# Begin Source File

SOURCE=.\Twist.cpp
# End Source File
# Begin Source File

SOURCE=.\XtruLens.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\BasePage.h
# End Source File
# Begin Source File

SOURCE=.\DegElevate.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Gordon.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_loft2.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_LoftCC.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_loftX.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_LTyp.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Coons.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Duct.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_EndCond.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Gordon.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Loft.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Revolv.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Sweep.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Tensor.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_PI_Xtrude.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Radius.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_tang.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_TenBlend.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Tensor.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_Torq.h
# End Source File
# Begin Source File

SOURCE=.\Loft_Com.h
# End Source File
# Begin Source File

SOURCE=.\Mi_gangp.h
# End Source File
# Begin Source File

SOURCE=.\Mp_CooP3.h
# End Source File
# Begin Source File

SOURCE=.\Mp_CooP4.h
# End Source File
# Begin Source File

SOURCE=.\Mp_duct.h
# End Source File
# Begin Source File

SOURCE=.\Mp_Gordon.h
# End Source File
# Begin Source File

SOURCE=.\Mp_loft2.h
# End Source File
# Begin Source File

SOURCE=.\Mp_loftX.h
# End Source File
# Begin Source File

SOURCE=.\Mp_rotat.h
# End Source File
# Begin Source File

SOURCE=.\Mp_sweep.h
# End Source File
# Begin Source File

SOURCE=.\Mp_Tensor.h
# End Source File
# Begin Source File

SOURCE=.\Mp_xtrud.h
# End Source File
# Begin Source File

SOURCE=.\MPatRsrc.hm
# End Source File
# Begin Source File

SOURCE=.\Pa_CoonP.h
# End Source File
# Begin Source File

SOURCE=.\Pa_CooP3.h
# End Source File
# Begin Source File

SOURCE=.\Pa_duct.h
# End Source File
# Begin Source File

SOURCE=.\Pa_loft2.h
# End Source File
# Begin Source File

SOURCE=.\PA_Loft4.h
# End Source File
# Begin Source File

SOURCE=.\Pa_rotat.h
# End Source File
# Begin Source File

SOURCE=.\Pa_sweep.h
# End Source File
# Begin Source File

SOURCE=.\PA_Xtrud.h
# End Source File
# Begin Source File

SOURCE=.\Sheet_PATI.h
# End Source File
# Begin Source File

SOURCE=.\Twist.h
# End Source File
# Begin Source File

SOURCE=.\XtruLens.h
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
# Begin Source File

SOURCE=.\temp.txt
# End Source File
# End Target
# End Project
