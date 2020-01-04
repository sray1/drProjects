# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=PostMgr - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to PostMgr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PostMgr - Win32 Release" && "$(CFG)" !=\
 "PostMgr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "PostMgr.mak" CFG="PostMgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PostMgr - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PostMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "PostMgr - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "PostMgr - Win32 Release"

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
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\PostMgr.dll"

CLEAN : 
	-@erase ".\Release\PostMgr.dll"
	-@erase ".\Release\Mi_Tang2.obj"
	-@erase ".\Release\NodPost.obj"
	-@erase ".\Release\Po_FE0D.obj"
	-@erase ".\Release\Po_Beam.obj"
	-@erase ".\Release\Po_Tr_10.obj"
	-@erase ".\Release\Mi_Gang0.obj"
	-@erase ".\Release\PatPost.obj"
	-@erase ".\Release\Po_Qu_12.obj"
	-@erase ".\Release\CurPost.obj"
	-@erase ".\Release\Po_Tr_9.obj"
	-@erase ".\Release\Po_Qu_16.obj"
	-@erase ".\Release\Po_Qu_9.obj"
	-@erase ".\Release\Po_Qu_4.obj"
	-@erase ".\Release\Po_Qu_8.obj"
	-@erase ".\Release\Po_FE2D.obj"
	-@erase ".\Release\Po_Tr_3.obj"
	-@erase ".\Release\PostMgr.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\PmgrDll.obj"
	-@erase ".\Release\Mi_gang2.obj"
	-@erase ".\Release\Po_FE1D.obj"
	-@erase ".\Release\Mi_Qang2.obj"
	-@erase ".\Release\Po_Tr_6.obj"
	-@erase ".\Release\Po_Pipe.obj"
	-@erase ".\Release\Mi_Gang1.obj"
	-@erase ".\Release\Po_Truss.obj"
	-@erase ".\Release\Po_Elbow.obj"
	-@erase ".\Release\Pmgr.res"
	-@erase ".\Release\PostMgr.lib"
	-@erase ".\Release\PostMgr.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/PostMgr.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Pmgr.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PostMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/PostMgr.pdb" /machine:I386 /def:".\Pmgr_d.def"\
 /out:"$(OUTDIR)/PostMgr.dll" /implib:"$(OUTDIR)/PostMgr.lib" 
DEF_FILE= \
	".\Pmgr_d.def"
LINK32_OBJS= \
	"$(INTDIR)/Mi_Tang2.obj" \
	"$(INTDIR)/NodPost.obj" \
	"$(INTDIR)/Po_FE0D.obj" \
	"$(INTDIR)/Po_Beam.obj" \
	"$(INTDIR)/Po_Tr_10.obj" \
	"$(INTDIR)/Mi_Gang0.obj" \
	"$(INTDIR)/PatPost.obj" \
	"$(INTDIR)/Po_Qu_12.obj" \
	"$(INTDIR)/CurPost.obj" \
	"$(INTDIR)/Po_Tr_9.obj" \
	"$(INTDIR)/Po_Qu_16.obj" \
	"$(INTDIR)/Po_Qu_9.obj" \
	"$(INTDIR)/Po_Qu_4.obj" \
	"$(INTDIR)/Po_Qu_8.obj" \
	"$(INTDIR)/Po_FE2D.obj" \
	"$(INTDIR)/Po_Tr_3.obj" \
	"$(INTDIR)/PostMgr.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/PmgrDll.obj" \
	"$(INTDIR)/Mi_gang2.obj" \
	"$(INTDIR)/Po_FE1D.obj" \
	"$(INTDIR)/Mi_Qang2.obj" \
	"$(INTDIR)/Po_Tr_6.obj" \
	"$(INTDIR)/Po_Pipe.obj" \
	"$(INTDIR)/Mi_Gang1.obj" \
	"$(INTDIR)/Po_Truss.obj" \
	"$(INTDIR)/Po_Elbow.obj" \
	"$(INTDIR)/Pmgr.res"

"$(OUTDIR)\PostMgr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

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
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\PMgr_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\applic\Debug\PMgr_D32.dll"
	-@erase ".\Debug\Po_Qu_8.obj"
	-@erase ".\Debug\Mi_Qang2.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\Po_FE0D.obj"
	-@erase ".\Debug\Po_Tr_3.obj"
	-@erase ".\Debug\Po_Truss.obj"
	-@erase ".\Debug\Po_Elbow.obj"
	-@erase ".\Debug\CurPost.obj"
	-@erase ".\Debug\Mi_gang2.obj"
	-@erase ".\Debug\Po_Qu_12.obj"
	-@erase ".\Debug\Po_Tr_6.obj"
	-@erase ".\Debug\Po_Qu_16.obj"
	-@erase ".\Debug\Po_FE2D.obj"
	-@erase ".\Debug\Mi_Gang1.obj"
	-@erase ".\Debug\PostMgr.obj"
	-@erase ".\Debug\NodPost.obj"
	-@erase ".\Debug\PmgrDll.obj"
	-@erase ".\Debug\Po_Beam.obj"
	-@erase ".\Debug\PatPost.obj"
	-@erase ".\Debug\Mi_Tang2.obj"
	-@erase ".\Debug\Po_Tr_9.obj"
	-@erase ".\Debug\Po_FE1D.obj"
	-@erase ".\Debug\Po_Tr_10.obj"
	-@erase ".\Debug\Mi_Gang0.obj"
	-@erase ".\Debug\Po_Qu_9.obj"
	-@erase ".\Debug\Po_Pipe.obj"
	-@erase ".\Debug\Po_Qu_4.obj"
	-@erase ".\Debug\Pmgr.res"
	-@erase "..\applic\Debug\PMgr_D32.ilk"
	-@erase "..\applic\Debug\PMgr_D32.lib"
	-@erase "..\applic\Debug\PMgr_D32.exp"
	-@erase ".\Debug\PMgr_D32.pdb"
	-@erase ".\Debug\PMgr_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/PostMgr.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/PostMgr.pch" /YX"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Pmgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PostMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib MMgr_D32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug/PMgr_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/PMgr_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib\
 OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib\
 MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib\
 MMgr_D32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/PMgr_D32.pdb" /map:"$(INTDIR)/PMgr_D32.map" /debug\
 /machine:I386 /def:".\Pmgr_d.def" /out:"d:\drgraf4_0\applic\Debug/PMgr_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/PMgr_D32.lib" 
DEF_FILE= \
	".\Pmgr_d.def"
LINK32_OBJS= \
	"$(INTDIR)/Po_Qu_8.obj" \
	"$(INTDIR)/Mi_Qang2.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Po_FE0D.obj" \
	"$(INTDIR)/Po_Tr_3.obj" \
	"$(INTDIR)/Po_Truss.obj" \
	"$(INTDIR)/Po_Elbow.obj" \
	"$(INTDIR)/CurPost.obj" \
	"$(INTDIR)/Mi_gang2.obj" \
	"$(INTDIR)/Po_Qu_12.obj" \
	"$(INTDIR)/Po_Tr_6.obj" \
	"$(INTDIR)/Po_Qu_16.obj" \
	"$(INTDIR)/Po_FE2D.obj" \
	"$(INTDIR)/Mi_Gang1.obj" \
	"$(INTDIR)/PostMgr.obj" \
	"$(INTDIR)/NodPost.obj" \
	"$(INTDIR)/PmgrDll.obj" \
	"$(INTDIR)/Po_Beam.obj" \
	"$(INTDIR)/PatPost.obj" \
	"$(INTDIR)/Mi_Tang2.obj" \
	"$(INTDIR)/Po_Tr_9.obj" \
	"$(INTDIR)/Po_FE1D.obj" \
	"$(INTDIR)/Po_Tr_10.obj" \
	"$(INTDIR)/Mi_Gang0.obj" \
	"$(INTDIR)/Po_Qu_9.obj" \
	"$(INTDIR)/Po_Pipe.obj" \
	"$(INTDIR)/Po_Qu_4.obj" \
	"$(INTDIR)/Pmgr.res"

"$(OUTDIR)\PMgr_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

################################################################################
# Begin Target

# Name "PostMgr - Win32 Release"
# Name "PostMgr - Win32 Debug"

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PmgrDll.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PostMgr - Win32 Release"


"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"


"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PmgrDll.cpp
DEP_CPP_PMGRD=\
	".\StdAfx.h"\
	".\PmgrDll.h"\
	

"$(INTDIR)\PmgrDll.obj" : $(SOURCE) $(DEP_CPP_PMGRD) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pmgr.rc
DEP_RSC_PMGR_=\
	".\..\Applic\Res\Cur_iso.cur"\
	".\..\Applic\Res\Curh_12.cur"\
	".\..\Applic\Res\Curh_23.cur"\
	".\..\Applic\Res\Curh_31.cur"\
	".\..\Applic\Res\Curtext.cur"\
	

"$(INTDIR)\Pmgr.res" : $(SOURCE) $(DEP_RSC_PMGR_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PmgrRsrc.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NodPost.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NodPost.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_NODPO=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\NodPost.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBox.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\NodPost.obj" : $(SOURCE) $(DEP_CPP_NODPO) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_NODPO=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\NodPost.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar0.h"\
	".\..\TOOLBOXS\ELEMBOX\palette.h"\
	".\..\TOOLBOXS\ELEMBOX\Oldtool.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar1.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBar.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar2.h"\
	".\..\TOOLBOXS\ELEMBOX\TriBox.h"\
	".\..\TOOLBOXS\ELEMBOX\QuadBox.h"\
	".\..\TOOLBOXS\ELEMBOX\Tribar.h"\
	".\..\TOOLBOXS\ELEMBOX\Quadbar.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar3.h"\
	".\..\TOOLBOXS\ELEMBOX\HexBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PenBox.h"\
	".\..\TOOLBOXS\ELEMBOX\TetBox.h"\
	".\..\TOOLBOXS\ELEMBOX\Hexbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Penbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Tetbar.h"\
	".\..\TOOLBOXS\DrawBox\dboxButt.h"\
	".\..\TOOLBOXS\DrawBox\drawbar.h"\
	".\..\TOOLBOXS\DrawBox\colorsqu.h"\
	".\..\MouseMgr\DLdMouse.h"\
	".\..\MouseMgr\dbMouse.h"\
	".\..\MouseMgr\SpLMouse.h"\
	".\..\MouseMgr\SLDMouse.h"\
	".\..\MouseMgr\SupMouse.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MouseMgr\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MouseMgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MouseMgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MouseMgr\MI_Sol_I.h"\
	".\..\MouseMgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MouseMgr\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MouseMgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MouseMgr\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MouseMgr\SLDCur.h"\
	".\..\MouseMgr\SLDNod.h"\
	".\..\MouseMgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\..\EditMgr\MNodEdit.h"\
	".\..\EditMgr\DLdEdit.h"\
	".\..\EditMgr\dbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\EditMgr\SpLEdit.h"\
	".\..\EditMgr\SLDEdit.h"\
	".\..\EditMgr\SupEdit.h"\
	".\..\EditMgr\SolEdit.h"\
	".\..\EditMgr\PatEdit.h"\
	".\..\EditMgr\CurEdit.h"\
	".\..\EditMgr\NodEdit.h"\
	".\..\DelMgr\DLdDel.h"\
	".\..\DelMgr\dbDel.h"\
	".\..\DelMgr\SpLDel.h"\
	".\..\DelMgr\SLDDel.h"\
	".\..\DelMgr\SupDel.h"\
	".\..\DelMgr\SolDel.h"\
	".\..\DelMgr\PatDel.h"\
	".\..\DelMgr\CurDel.h"\
	".\..\DelMgr\NodDel.h"\
	".\PatPost.h"\
	{$(INCLUDE)}"\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Po_FE1D.h"\
	".\Po_Pipe.h"\
	".\Po_Beam.h"\
	".\Po_Truss.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	

"$(INTDIR)\NodPost.obj" : $(SOURCE) $(DEP_CPP_NODPO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pmgr_d.def

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PostMgr.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PostMgr.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_POSTM=\
	".\StdAfx.h"\
	".\PmgrDll.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Curdef.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBox.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	".\PatPost.h"\
	{$(INCLUDE)}"\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Po_FE1D.h"\
	".\Po_Pipe.h"\
	".\Po_Beam.h"\
	".\Po_Truss.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\..\GenObjs\Triangle.h"\
	

"$(INTDIR)\PostMgr.obj" : $(SOURCE) $(DEP_CPP_POSTM) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_POSTM=\
	".\StdAfx.h"\
	".\PmgrDll.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Curdef.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar0.h"\
	".\..\TOOLBOXS\ELEMBOX\palette.h"\
	".\..\TOOLBOXS\ELEMBOX\Oldtool.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar1.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBar.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar2.h"\
	".\..\TOOLBOXS\ELEMBOX\TriBox.h"\
	".\..\TOOLBOXS\ELEMBOX\QuadBox.h"\
	".\..\TOOLBOXS\ELEMBOX\Tribar.h"\
	".\..\TOOLBOXS\ELEMBOX\Quadbar.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar3.h"\
	".\..\TOOLBOXS\ELEMBOX\HexBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PenBox.h"\
	".\..\TOOLBOXS\ELEMBOX\TetBox.h"\
	".\..\TOOLBOXS\ELEMBOX\Hexbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Penbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Tetbar.h"\
	".\..\TOOLBOXS\DrawBox\dboxButt.h"\
	".\..\TOOLBOXS\DrawBox\drawbar.h"\
	".\..\TOOLBOXS\DrawBox\colorsqu.h"\
	".\..\MouseMgr\DLdMouse.h"\
	".\..\MouseMgr\dbMouse.h"\
	".\..\MouseMgr\SpLMouse.h"\
	".\..\MouseMgr\SLDMouse.h"\
	".\..\MouseMgr\SupMouse.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MouseMgr\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	".\..\MouseMgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MouseMgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MouseMgr\MI_Sol_I.h"\
	".\..\MouseMgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MouseMgr\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MouseMgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MouseMgr\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MouseMgr\SLDCur.h"\
	".\..\MouseMgr\SLDNod.h"\
	".\..\MouseMgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\..\EditMgr\MNodEdit.h"\
	".\..\EditMgr\DLdEdit.h"\
	".\..\EditMgr\dbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\EditMgr\SpLEdit.h"\
	".\..\EditMgr\SLDEdit.h"\
	".\..\EditMgr\SupEdit.h"\
	".\..\EditMgr\SolEdit.h"\
	".\..\EditMgr\PatEdit.h"\
	".\..\EditMgr\CurEdit.h"\
	".\..\EditMgr\NodEdit.h"\
	".\..\DelMgr\DLdDel.h"\
	".\..\DelMgr\dbDel.h"\
	".\..\DelMgr\SpLDel.h"\
	".\..\DelMgr\SLDDel.h"\
	".\..\DelMgr\SupDel.h"\
	".\..\DelMgr\SolDel.h"\
	".\..\DelMgr\PatDel.h"\
	".\..\DelMgr\CurDel.h"\
	".\..\DelMgr\NodDel.h"\
	".\PatPost.h"\
	{$(INCLUDE)}"\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Po_FE1D.h"\
	".\Po_Pipe.h"\
	".\Po_Beam.h"\
	".\Po_Truss.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	

"$(INTDIR)\PostMgr.obj" : $(SOURCE) $(DEP_CPP_POSTM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CurPost.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CurPost.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_CURPO=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\Po_Pipe.h"\
	".\Po_Beam.h"\
	".\Po_Truss.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	".\Mi_Gang0.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\CurPost.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBox.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\NodPost.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	

"$(INTDIR)\CurPost.obj" : $(SOURCE) $(DEP_CPP_CURPO) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_CURPO=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\Po_Pipe.h"\
	".\Po_Beam.h"\
	".\Po_Truss.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	".\Mi_Gang0.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\CurPost.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar0.h"\
	".\..\TOOLBOXS\ELEMBOX\palette.h"\
	".\..\TOOLBOXS\ELEMBOX\Oldtool.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar1.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBar.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar2.h"\
	".\..\TOOLBOXS\ELEMBOX\TriBox.h"\
	".\..\TOOLBOXS\ELEMBOX\QuadBox.h"\
	".\..\TOOLBOXS\ELEMBOX\Tribar.h"\
	".\..\TOOLBOXS\ELEMBOX\Quadbar.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar3.h"\
	".\..\TOOLBOXS\ELEMBOX\HexBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PenBox.h"\
	".\..\TOOLBOXS\ELEMBOX\TetBox.h"\
	".\..\TOOLBOXS\ELEMBOX\Hexbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Penbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Tetbar.h"\
	".\..\TOOLBOXS\DrawBox\dboxButt.h"\
	".\..\TOOLBOXS\DrawBox\drawbar.h"\
	".\..\TOOLBOXS\DrawBox\colorsqu.h"\
	".\..\MouseMgr\DLdMouse.h"\
	".\..\MouseMgr\dbMouse.h"\
	".\..\MouseMgr\SpLMouse.h"\
	".\..\MouseMgr\SLDMouse.h"\
	".\..\MouseMgr\SupMouse.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MouseMgr\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MouseMgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MouseMgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MouseMgr\MI_Sol_I.h"\
	".\..\MouseMgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MouseMgr\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MouseMgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MouseMgr\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MouseMgr\SLDCur.h"\
	".\..\MouseMgr\SLDNod.h"\
	".\..\MouseMgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\..\EditMgr\MNodEdit.h"\
	".\..\EditMgr\DLdEdit.h"\
	".\..\EditMgr\dbEdit.h"\
	".\..\EditMgr\SpLEdit.h"\
	".\..\EditMgr\SLDEdit.h"\
	".\..\EditMgr\SupEdit.h"\
	".\..\EditMgr\SolEdit.h"\
	".\..\EditMgr\PatEdit.h"\
	".\..\EditMgr\CurEdit.h"\
	".\..\EditMgr\NodEdit.h"\
	".\..\DelMgr\DLdDel.h"\
	".\..\DelMgr\dbDel.h"\
	".\..\DelMgr\SpLDel.h"\
	".\..\DelMgr\SLDDel.h"\
	".\..\DelMgr\SupDel.h"\
	".\..\DelMgr\SolDel.h"\
	".\..\DelMgr\PatDel.h"\
	".\..\DelMgr\CurDel.h"\
	".\..\DelMgr\NodDel.h"\
	".\PatPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\NodPost.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	

"$(INTDIR)\CurPost.obj" : $(SOURCE) $(DEP_CPP_CURPO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_FE0D.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_FE0D.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_FE=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBox.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\Po_FE0D.obj" : $(SOURCE) $(DEP_CPP_PO_FE) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_FE=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar0.h"\
	".\..\TOOLBOXS\ELEMBOX\palette.h"\
	".\..\TOOLBOXS\ELEMBOX\Oldtool.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar1.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBar.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar2.h"\
	".\..\TOOLBOXS\ELEMBOX\TriBox.h"\
	".\..\TOOLBOXS\ELEMBOX\QuadBox.h"\
	".\..\TOOLBOXS\ELEMBOX\Tribar.h"\
	".\..\TOOLBOXS\ELEMBOX\Quadbar.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar3.h"\
	".\..\TOOLBOXS\ELEMBOX\HexBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PenBox.h"\
	".\..\TOOLBOXS\ELEMBOX\TetBox.h"\
	".\..\TOOLBOXS\ELEMBOX\Hexbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Penbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Tetbar.h"\
	".\..\TOOLBOXS\DrawBox\dboxButt.h"\
	".\..\TOOLBOXS\DrawBox\drawbar.h"\
	".\..\TOOLBOXS\DrawBox\colorsqu.h"\
	".\..\MouseMgr\DLdMouse.h"\
	".\..\MouseMgr\dbMouse.h"\
	".\..\MouseMgr\SpLMouse.h"\
	".\..\MouseMgr\SLDMouse.h"\
	".\..\MouseMgr\SupMouse.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MouseMgr\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MouseMgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MouseMgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MouseMgr\MI_Sol_I.h"\
	".\..\MouseMgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MouseMgr\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MouseMgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MouseMgr\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MouseMgr\SLDCur.h"\
	".\..\MouseMgr\SLDNod.h"\
	".\..\MouseMgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\..\EditMgr\MNodEdit.h"\
	".\..\EditMgr\DLdEdit.h"\
	".\..\EditMgr\dbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\EditMgr\SpLEdit.h"\
	".\..\EditMgr\SLDEdit.h"\
	".\..\EditMgr\SupEdit.h"\
	".\..\EditMgr\SolEdit.h"\
	".\..\EditMgr\PatEdit.h"\
	".\..\EditMgr\CurEdit.h"\
	".\..\EditMgr\NodEdit.h"\
	".\..\DelMgr\DLdDel.h"\
	".\..\DelMgr\dbDel.h"\
	".\..\DelMgr\SpLDel.h"\
	".\..\DelMgr\SLDDel.h"\
	".\..\DelMgr\SupDel.h"\
	".\..\DelMgr\SolDel.h"\
	".\..\DelMgr\PatDel.h"\
	".\..\DelMgr\CurDel.h"\
	".\..\DelMgr\NodDel.h"\
	".\PatPost.h"\
	{$(INCLUDE)}"\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Po_FE1D.h"\
	".\Po_Pipe.h"\
	".\Po_Beam.h"\
	".\Po_Truss.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	

"$(INTDIR)\Po_FE0D.obj" : $(SOURCE) $(DEP_CPP_PO_FE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_FE1D.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_FE1D.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_FE1=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Mi_Gang1.h"\
	".\Mi_gang2.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Po_FE2D.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	

"$(INTDIR)\Po_FE1D.obj" : $(SOURCE) $(DEP_CPP_PO_FE1) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_FE1=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Mi_Gang1.h"\
	".\Mi_gang2.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Po_FE2D.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	

"$(INTDIR)\Po_FE1D.obj" : $(SOURCE) $(DEP_CPP_PO_FE1) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Pipe.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Pipe.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_PI=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\Po_Pipe.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	

"$(INTDIR)\Po_Pipe.obj" : $(SOURCE) $(DEP_CPP_PO_PI) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_PI=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\Po_Pipe.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	

"$(INTDIR)\Po_Pipe.obj" : $(SOURCE) $(DEP_CPP_PO_PI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_Gang0.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_Gang0.cpp
DEP_CPP_MI_GA=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Lims.h"\
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Mouse.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	

"$(INTDIR)\Mi_Gang0.obj" : $(SOURCE) $(DEP_CPP_MI_GA) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Beam.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Beam.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_BE=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\Po_Beam.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	

"$(INTDIR)\Po_Beam.obj" : $(SOURCE) $(DEP_CPP_PO_BE) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_BE=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\Po_Beam.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	

"$(INTDIR)\Po_Beam.obj" : $(SOURCE) $(DEP_CPP_PO_BE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Truss.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Truss.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_TR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\Po_Truss.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	

"$(INTDIR)\Po_Truss.obj" : $(SOURCE) $(DEP_CPP_PO_TR) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_TR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\Po_Truss.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	

"$(INTDIR)\Po_Truss.obj" : $(SOURCE) $(DEP_CPP_PO_TR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Elbow.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Elbow.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_EL=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	

"$(INTDIR)\Po_Elbow.obj" : $(SOURCE) $(DEP_CPP_PO_EL) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_EL=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	

"$(INTDIR)\Po_Elbow.obj" : $(SOURCE) $(DEP_CPP_PO_EL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_Gang1.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_Gang1.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_MI_GAN=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\Po_Truss.h"\
	".\Po_Beam.h"\
	".\Po_Pipe.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	

"$(INTDIR)\Mi_Gang1.obj" : $(SOURCE) $(DEP_CPP_MI_GAN) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_MI_GAN=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\Po_Truss.h"\
	".\Po_Beam.h"\
	".\Po_Pipe.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	

"$(INTDIR)\Mi_Gang1.obj" : $(SOURCE) $(DEP_CPP_MI_GAN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_gang2.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_gang2.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_MI_GANG=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_Qu_4.h"\
	".\Po_Qu_8.h"\
	".\Po_Qu_9.h"\
	".\Po_Qu_12.h"\
	".\Po_Qu_16.h"\
	".\Po_Tr_3.h"\
	".\Po_Tr_6.h"\
	".\Po_Tr_9.h"\
	".\Po_Tr_10.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	".\Mi_Gang0.h"\
	".\Mi_gang2.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	

"$(INTDIR)\Mi_gang2.obj" : $(SOURCE) $(DEP_CPP_MI_GANG) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_MI_GANG=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_Qu_4.h"\
	".\Po_Qu_8.h"\
	".\Po_Qu_9.h"\
	".\Po_Qu_12.h"\
	".\Po_Qu_16.h"\
	".\Po_Tr_3.h"\
	".\Po_Tr_6.h"\
	".\Po_Tr_9.h"\
	".\Po_Tr_10.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	".\Mi_Gang0.h"\
	".\Mi_gang2.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	

"$(INTDIR)\Mi_gang2.obj" : $(SOURCE) $(DEP_CPP_MI_GANG) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PatPost.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PatPost.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PATPO=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	".\Mi_gang2.h"\
	".\Mi_Qang2.h"\
	".\Mi_Tang2.h"\
	".\PatPost.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBox.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\CurPost.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\NodPost.h"\
	".\Po_Pipe.h"\
	".\Po_Beam.h"\
	".\Po_Truss.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	

"$(INTDIR)\PatPost.obj" : $(SOURCE) $(DEP_CPP_PATPO) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PATPO=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	".\Mi_gang2.h"\
	".\Mi_Qang2.h"\
	".\Mi_Tang2.h"\
	".\PatPost.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar0.h"\
	".\..\TOOLBOXS\ELEMBOX\palette.h"\
	".\..\TOOLBOXS\ELEMBOX\Oldtool.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar1.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBar.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar2.h"\
	".\..\TOOLBOXS\ELEMBOX\TriBox.h"\
	".\..\TOOLBOXS\ELEMBOX\QuadBox.h"\
	".\..\TOOLBOXS\ELEMBOX\Tribar.h"\
	".\..\TOOLBOXS\ELEMBOX\Quadbar.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar3.h"\
	".\..\TOOLBOXS\ELEMBOX\HexBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PenBox.h"\
	".\..\TOOLBOXS\ELEMBOX\TetBox.h"\
	".\..\TOOLBOXS\ELEMBOX\Hexbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Penbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Tetbar.h"\
	".\..\TOOLBOXS\DrawBox\dboxButt.h"\
	".\..\TOOLBOXS\DrawBox\drawbar.h"\
	".\..\TOOLBOXS\DrawBox\colorsqu.h"\
	".\..\MouseMgr\DLdMouse.h"\
	".\..\MouseMgr\dbMouse.h"\
	".\..\MouseMgr\SpLMouse.h"\
	".\..\MouseMgr\SLDMouse.h"\
	".\..\MouseMgr\SupMouse.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MouseMgr\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MouseMgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MouseMgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MouseMgr\MI_Sol_I.h"\
	".\..\MouseMgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MouseMgr\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MouseMgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MouseMgr\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MouseMgr\SLDCur.h"\
	".\..\MouseMgr\SLDNod.h"\
	".\..\MouseMgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\..\EditMgr\MNodEdit.h"\
	".\..\EditMgr\DLdEdit.h"\
	".\..\EditMgr\dbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\EditMgr\SpLEdit.h"\
	".\..\EditMgr\SLDEdit.h"\
	".\..\EditMgr\SupEdit.h"\
	".\..\EditMgr\SolEdit.h"\
	".\..\EditMgr\PatEdit.h"\
	".\..\EditMgr\CurEdit.h"\
	".\..\EditMgr\NodEdit.h"\
	".\..\DelMgr\DLdDel.h"\
	".\..\DelMgr\dbDel.h"\
	".\..\DelMgr\SpLDel.h"\
	".\..\DelMgr\SLDDel.h"\
	".\..\DelMgr\SupDel.h"\
	".\..\DelMgr\SolDel.h"\
	".\..\DelMgr\PatDel.h"\
	".\..\DelMgr\CurDel.h"\
	".\..\DelMgr\NodDel.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\CurPost.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\NodPost.h"\
	".\Po_Pipe.h"\
	".\Po_Beam.h"\
	".\Po_Truss.h"\
	".\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	

"$(INTDIR)\PatPost.obj" : $(SOURCE) $(DEP_CPP_PATPO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_FE2D.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_FE2D.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_FE2=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Mi_gang2.h"\
	".\Mi_Qang2.h"\
	".\Mi_Tang2.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Mi_Gang1.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\Po_FE0D.h"\
	

"$(INTDIR)\Po_FE2D.obj" : $(SOURCE) $(DEP_CPP_PO_FE2) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_FE2=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Mi_gang2.h"\
	".\Mi_Qang2.h"\
	".\Mi_Tang2.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Mi_Gang1.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	

"$(INTDIR)\Po_FE2D.obj" : $(SOURCE) $(DEP_CPP_PO_FE2) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Qu_4.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Qu_4.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_QU=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Qu_4.h"\
	".\Mi_gang2.h"\
	".\Po_Qu_4.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Qu_4.obj" : $(SOURCE) $(DEP_CPP_PO_QU) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_QU=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Qu_4.h"\
	".\Mi_gang2.h"\
	".\Po_Qu_4.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Qu_4.obj" : $(SOURCE) $(DEP_CPP_PO_QU) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Tr_3.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Tr_3.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_TR_=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Tr_3.h"\
	".\Mi_gang2.h"\
	".\Po_Tr_3.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Tr_3.obj" : $(SOURCE) $(DEP_CPP_PO_TR_) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_TR_=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Tr_3.h"\
	".\Mi_gang2.h"\
	".\Po_Tr_3.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Tr_3.obj" : $(SOURCE) $(DEP_CPP_PO_TR_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Tr_6.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Tr_6.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_TR_6=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Tr_6.h"\
	".\Mi_gang2.h"\
	".\Po_Tr_6.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Tr_6.obj" : $(SOURCE) $(DEP_CPP_PO_TR_6) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_TR_6=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Tr_6.h"\
	".\Mi_gang2.h"\
	".\Po_Tr_6.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Tr_6.obj" : $(SOURCE) $(DEP_CPP_PO_TR_6) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Tr_9.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Tr_9.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_TR_9=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Tr_9.h"\
	".\Mi_gang2.h"\
	".\Po_Tr_9.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Tr_9.obj" : $(SOURCE) $(DEP_CPP_PO_TR_9) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_TR_9=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Tr_9.h"\
	".\Mi_gang2.h"\
	".\Po_Tr_9.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Tr_9.obj" : $(SOURCE) $(DEP_CPP_PO_TR_9) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Tr_10.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Tr_10.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_TR_1=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Tr_10.h"\
	".\Mi_gang2.h"\
	".\Po_Tr_10.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Tr_10.obj" : $(SOURCE) $(DEP_CPP_PO_TR_1) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_TR_1=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Tr_10.h"\
	".\Mi_gang2.h"\
	".\Po_Tr_10.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Tr_10.obj" : $(SOURCE) $(DEP_CPP_PO_TR_1) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Qu_8.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Qu_8.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_QU_=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Qu_8.h"\
	".\Mi_gang2.h"\
	".\Po_Qu_8.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Qu_8.obj" : $(SOURCE) $(DEP_CPP_PO_QU_) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_QU_=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Qu_8.h"\
	".\Mi_gang2.h"\
	".\Po_Qu_8.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Qu_8.obj" : $(SOURCE) $(DEP_CPP_PO_QU_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Qu_9.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Qu_9.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_QU_9=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Qu_9.h"\
	".\Mi_gang2.h"\
	".\Po_Qu_9.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Qu_9.obj" : $(SOURCE) $(DEP_CPP_PO_QU_9) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_QU_9=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Qu_9.h"\
	".\Mi_gang2.h"\
	".\Po_Qu_9.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Qu_9.obj" : $(SOURCE) $(DEP_CPP_PO_QU_9) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Qu_12.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Qu_12.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_QU_1=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\Dr_Qu_12.h"\
	".\Mi_gang2.h"\
	".\Po_Qu_12.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Qu_12.obj" : $(SOURCE) $(DEP_CPP_PO_QU_1) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_QU_1=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\Dr_Qu_12.h"\
	".\Mi_gang2.h"\
	".\Po_Qu_12.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Qu_12.obj" : $(SOURCE) $(DEP_CPP_PO_QU_1) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Qu_16.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Po_Qu_16.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_PO_QU_16=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Qu_16.h"\
	".\Mi_gang2.h"\
	".\Po_Qu_16.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Qu_16.obj" : $(SOURCE) $(DEP_CPP_PO_QU_16) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_PO_QU_16=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Dr_Qu_16.h"\
	".\Mi_gang2.h"\
	".\Po_Qu_16.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_Gang0.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Po_Qu_16.obj" : $(SOURCE) $(DEP_CPP_PO_QU_16) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_Tang2.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_Tang2.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_MI_TA=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	".\Mi_Gang0.h"\
	".\Mi_Tang2.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	".\Mi_gang2.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	

"$(INTDIR)\Mi_Tang2.obj" : $(SOURCE) $(DEP_CPP_MI_TA) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_MI_TA=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	".\Mi_Gang0.h"\
	".\Mi_Tang2.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	".\Mi_gang2.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Po_FE2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\Po_FE1D.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	

"$(INTDIR)\Mi_Tang2.obj" : $(SOURCE) $(DEP_CPP_MI_TA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_Qang2.h

!IF  "$(CFG)" == "PostMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_Qang2.cpp

!IF  "$(CFG)" == "PostMgr - Win32 Release"

DEP_CPP_MI_QA=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_Qu_4.h"\
	".\Po_Qu_8.h"\
	".\Po_Qu_9.h"\
	".\Po_Qu_12.h"\
	".\Po_Qu_16.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	".\Mi_Gang0.h"\
	".\Mi_Qang2.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Po_FE1D.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	".\Mi_gang2.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	

"$(INTDIR)\Mi_Qang2.obj" : $(SOURCE) $(DEP_CPP_MI_QA) "$(INTDIR)"\
 "$(INTDIR)\PostMgr.pch"


!ELSEIF  "$(CFG)" == "PostMgr - Win32 Debug"

DEP_CPP_MI_QA=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Po_Qu_4.h"\
	".\Po_Qu_8.h"\
	".\Po_Qu_9.h"\
	".\Po_Qu_12.h"\
	".\Po_Qu_16.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	".\Mi_Gang0.h"\
	".\Mi_Qang2.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\Po_FE2D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Po_FE1D.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	".\Po_FE0D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\Mi_gang2.h"\
	".\Mi_Gang1.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	

"$(INTDIR)\Mi_Qang2.obj" : $(SOURCE) $(DEP_CPP_MI_QA) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
