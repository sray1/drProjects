# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=CreOMMgr - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to CreOMMgr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CreOMMgr - Win32 Release" && "$(CFG)" !=\
 "CreOMMgr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "CreOMMgr.mak" CFG="CreOMMgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CreOMMgr - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CreOMMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "CreOMMgr - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

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

ALL : "$(OUTDIR)\CreOMMgr.dll"

CLEAN : 
	-@erase ".\Release\CreOMMgr.dll"
	-@erase ".\Release\Mi_1Prof.obj"
	-@erase ".\Release\CreOMMgr.pch"
	-@erase ".\Release\O3DCreOM.obj"
	-@erase ".\Release\MI_0SPN.obj"
	-@erase ".\Release\NodCreOM.obj"
	-@erase ".\Release\SolCreOM.obj"
	-@erase ".\Release\CreMDll.obj"
	-@erase ".\Release\PatCreOM.obj"
	-@erase ".\Release\CreOMMgr.obj"
	-@erase ".\Release\CurCreOM.obj"
	-@erase ".\Release\MI_1SPN.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\CreM.res"
	-@erase ".\Release\CreOMMgr.lib"
	-@erase ".\Release\CreOMMgr.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/CreOMMgr.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CreM.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CreOMMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/CreOMMgr.pdb" /machine:I386 /def:".\CreOMMgr.def"\
 /out:"$(OUTDIR)/CreOMMgr.dll" /implib:"$(OUTDIR)/CreOMMgr.lib" 
DEF_FILE= \
	".\CreOMMgr.def"
LINK32_OBJS= \
	"$(INTDIR)/Mi_1Prof.obj" \
	"$(INTDIR)/O3DCreOM.obj" \
	"$(INTDIR)/MI_0SPN.obj" \
	"$(INTDIR)/NodCreOM.obj" \
	"$(INTDIR)/SolCreOM.obj" \
	"$(INTDIR)/CreMDll.obj" \
	"$(INTDIR)/PatCreOM.obj" \
	"$(INTDIR)/CreOMMgr.obj" \
	"$(INTDIR)/CurCreOM.obj" \
	"$(INTDIR)/MI_1SPN.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/CreM.res"

"$(OUTDIR)\CreOMMgr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

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

ALL : "$(OUTDIR)\CreM_D32.dll" ".\Debug\CreOMMgr.pch"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\CreOMMgr.pch"
	-@erase "..\applic\Debug\CreM_D32.dll"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\O3DCreOM.obj"
	-@erase ".\Debug\MI_0SPN.obj"
	-@erase ".\Debug\CreMDll.obj"
	-@erase ".\Debug\Mi_1Prof.obj"
	-@erase ".\Debug\PatCreOM.obj"
	-@erase ".\Debug\CreOMMgr.obj"
	-@erase ".\Debug\CurCreOM.obj"
	-@erase ".\Debug\MI_1SPN.obj"
	-@erase ".\Debug\NodCreOM.obj"
	-@erase ".\Debug\SolCreOM.obj"
	-@erase ".\Debug\CreM.res"
	-@erase "..\applic\Debug\CreM_D32.ilk"
	-@erase "..\applic\Debug\CreM_D32.lib"
	-@erase "..\applic\Debug\CreM_D32.exp"
	-@erase ".\Debug\CreM_D32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/CreOMMgr.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/CreOMMgr.pch" /YX"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CreM.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CreOMMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_d32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib MO3D_D32.lib MMgr_D32.lib PMgr_D32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /def:".\CreOM_d.def" /out:"d:\drgraf4_0\applic\Debug/CreM_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/CreM_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_d32.lib Elem_D32.lib\
 OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib\
 MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib\
 MO3D_D32.lib MMgr_D32.lib PMgr_D32.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/CreM_D32.pdb" /debug /machine:I386\
 /def:".\CreOM_d.def" /out:"d:\drgraf4_0\applic\Debug/CreM_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/CreM_D32.lib" 
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/O3DCreOM.obj" \
	"$(INTDIR)/MI_0SPN.obj" \
	"$(INTDIR)/CreMDll.obj" \
	"$(INTDIR)/Mi_1Prof.obj" \
	"$(INTDIR)/PatCreOM.obj" \
	"$(INTDIR)/CreOMMgr.obj" \
	"$(INTDIR)/CurCreOM.obj" \
	"$(INTDIR)/MI_1SPN.obj" \
	"$(INTDIR)/NodCreOM.obj" \
	"$(INTDIR)/SolCreOM.obj" \
	"$(INTDIR)/CreM.res"

"$(OUTDIR)\CreM_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "CreOMMgr - Win32 Release"
# Name "CreOMMgr - Win32 Debug"

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\CreOMMgr.cpp

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

DEP_CPP_CREOM=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\CMgrDll.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Curdef.h"\
	".\CreOMMgr.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\O3DCreOM.h"\
	{$(INCLUDE)}"\SolCreOM.h"\
	".\PatCreOM.h"\
	".\CurCreOM.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\CreOMMgr.obj" : $(SOURCE) $(DEP_CPP_CREOM) "$(INTDIR)"\
 "$(INTDIR)\CreOMMgr.pch"


!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

DEP_CPP_CREOM=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\CMgrDll.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Curdef.h"\
	".\CreOMMgr.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
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
	".\..\PostMgr\PatPost.h"\
	".\..\PostMgr\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\..\PostMgr\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\PostMgr\Po_FE1D.h"\
	".\..\PostMgr\Po_Pipe.h"\
	".\..\PostMgr\Po_Beam.h"\
	".\..\PostMgr\Po_Truss.h"\
	".\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\O3DCreOM.h"\
	{$(INCLUDE)}"\SolCreOM.h"\
	".\PatCreOM.h"\
	".\CurCreOM.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	

"$(INTDIR)\CreOMMgr.obj" : $(SOURCE) $(DEP_CPP_CREOM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CreOMMgr.def

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/CreOMMgr.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CreOMMgr.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/CreOMMgr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\CreOMMgr.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CreOMMgr.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CurCreOM.cpp

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

DEP_CPP_CURCR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\MCurmgr.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	".\Mi_1SPN.h"\
	".\Mi_1Prof.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\CurCreOM.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\Mi_0SPN.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	

"$(INTDIR)\CurCreOM.obj" : $(SOURCE) $(DEP_CPP_CURCR) "$(INTDIR)"\
 "$(INTDIR)\CreOMMgr.pch"


!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

DEP_CPP_CURCR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\MCurmgr.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	".\Mi_1SPN.h"\
	".\Mi_1Prof.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\CurCreOM.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
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
	".\..\PostMgr\PatPost.h"\
	".\..\PostMgr\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\..\PostMgr\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\PostMgr\Po_FE1D.h"\
	".\..\PostMgr\Po_Pipe.h"\
	".\..\PostMgr\Po_Beam.h"\
	".\..\PostMgr\Po_Truss.h"\
	".\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
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
	{$(INCLUDE)}"\Mi_GangN.h"\
	".\Mi_0SPN.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	".\NodCreOM.h"\
	

"$(INTDIR)\CurCreOM.obj" : $(SOURCE) $(DEP_CPP_CURCR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CurCreOM.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_0SPN.cpp
DEP_CPP_MI_0S=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\dlg_spnn.h"\
	".\Mi_0SPN.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\GenObjs\Triangle.h"\
	

"$(INTDIR)\MI_0SPN.obj" : $(SOURCE) $(DEP_CPP_MI_0S) "$(INTDIR)"\
 "$(INTDIR)\CreOMMgr.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_0SPN.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_1Prof.cpp
DEP_CPP_MI_1P=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\MCurmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Mi_1Prof.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
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
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mi_1Prof.obj" : $(SOURCE) $(DEP_CPP_MI_1P) "$(INTDIR)"\
 "$(INTDIR)\CreOMMgr.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_1Prof.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_1SPN.cpp
DEP_CPP_MI_1S=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\MCurmgr.h"\
	{$(INCLUDE)}"\Dlg_SpnC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_CSPN.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\GenObjs\Triangle.h"\
	

"$(INTDIR)\MI_1SPN.obj" : $(SOURCE) $(DEP_CPP_MI_1S) "$(INTDIR)"\
 "$(INTDIR)\CreOMMgr.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_1SPN.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NodCreOM.cpp

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

DEP_CPP_NODCR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Mi_Gang0.h"\
	".\Mi_0SPN.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Mouse.h"\
	

"$(INTDIR)\NodCreOM.obj" : $(SOURCE) $(DEP_CPP_NODCR) "$(INTDIR)"\
 "$(INTDIR)\CreOMMgr.pch"


!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

DEP_CPP_NODCR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Mi_Gang0.h"\
	".\Mi_0SPN.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
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
	".\..\PostMgr\PatPost.h"\
	".\..\PostMgr\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\..\PostMgr\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\PostMgr\Po_FE1D.h"\
	".\..\PostMgr\Po_Pipe.h"\
	".\..\PostMgr\Po_Beam.h"\
	".\..\PostMgr\Po_Truss.h"\
	".\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
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
	

"$(INTDIR)\NodCreOM.obj" : $(SOURCE) $(DEP_CPP_NODCR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NodCreOM.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\O3DCreOM.cpp

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

DEP_CPP_O3DCR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Mi_OSPN.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\O3DCreOM.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	{$(INCLUDE)}"\Mi_SSPN.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Mi_PSPN.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mi_CSPN.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	{$(INCLUDE)}"\SolCreOM.h"\
	".\PatCreOM.h"\
	".\CurCreOM.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\O3DCreOM.obj" : $(SOURCE) $(DEP_CPP_O3DCR) "$(INTDIR)"\
 "$(INTDIR)\CreOMMgr.pch"


!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

DEP_CPP_O3DCR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Mi_OSPN.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\O3DCreOM.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
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
	".\..\PostMgr\PatPost.h"\
	".\..\PostMgr\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\..\PostMgr\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\PostMgr\Po_FE1D.h"\
	".\..\PostMgr\Po_Pipe.h"\
	".\..\PostMgr\Po_Beam.h"\
	".\..\PostMgr\Po_Truss.h"\
	".\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
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
	{$(INCLUDE)}"\Mi_SSPN.h"\
	{$(INCLUDE)}"\Mi_PSPN.h"\
	{$(INCLUDE)}"\Mi_CSPN.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	{$(INCLUDE)}"\SolCreOM.h"\
	".\PatCreOM.h"\
	".\CurCreOM.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	

"$(INTDIR)\O3DCreOM.obj" : $(SOURCE) $(DEP_CPP_O3DCR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\O3DCreOM.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PatCreOM.cpp

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

DEP_CPP_PATCR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Mi_PSPN.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\PatCreOM.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Mi_CSPN.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\CurCreOM.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\PatCreOM.obj" : $(SOURCE) $(DEP_CPP_PATCR) "$(INTDIR)"\
 "$(INTDIR)\CreOMMgr.pch"


!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

DEP_CPP_PATCR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Mi_PSPN.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\PatCreOM.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
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
	".\..\PostMgr\PatPost.h"\
	".\..\PostMgr\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\..\PostMgr\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\PostMgr\Po_FE1D.h"\
	".\..\PostMgr\Po_Pipe.h"\
	".\..\PostMgr\Po_Beam.h"\
	".\..\PostMgr\Po_Truss.h"\
	".\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
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
	{$(INCLUDE)}"\Mi_CSPN.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	".\CurCreOM.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	

"$(INTDIR)\PatCreOM.obj" : $(SOURCE) $(DEP_CPP_PATCR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PatCreOM.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SolCreOM.cpp

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

DEP_CPP_SOLCR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Mi_SSPN.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	{$(INCLUDE)}"\SolCreOM.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Mi_PSPN.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mi_CSPN.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\PatCreOM.h"\
	".\CurCreOM.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\SolCreOM.obj" : $(SOURCE) $(DEP_CPP_SOLCR) "$(INTDIR)"\
 "$(INTDIR)\CreOMMgr.pch"


!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

DEP_CPP_SOLCR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Mi_SSPN.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	{$(INCLUDE)}"\SolCreOM.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
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
	".\..\PostMgr\PatPost.h"\
	".\..\PostMgr\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\..\PostMgr\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\PostMgr\Po_FE1D.h"\
	".\..\PostMgr\Po_Pipe.h"\
	".\..\PostMgr\Po_Beam.h"\
	".\..\PostMgr\Po_Truss.h"\
	".\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
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
	{$(INCLUDE)}"\Mi_PSPN.h"\
	{$(INCLUDE)}"\Mi_CSPN.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	".\PatCreOM.h"\
	".\CurCreOM.h"\
	".\NodCreOM.h"\
	{$(INCLUDE)}"\Drprof_1.h"\
	

"$(INTDIR)\SolCreOM.obj" : $(SOURCE) $(DEP_CPP_SOLCR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CreMDll.h

!IF  "$(CFG)" == "CreOMMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOMMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CreMDll.cpp
DEP_CPP_CREMD=\
	".\StdAfx.h"\
	".\CreMDll.h"\
	

"$(INTDIR)\CreMDll.obj" : $(SOURCE) $(DEP_CPP_CREMD) "$(INTDIR)"\
 "$(INTDIR)\CreOMMgr.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CreM.rc
DEP_RSC_CREM_=\
	".\..\Applic\Res\Cur_iso.cur"\
	".\..\Applic\Res\Curh_12.cur"\
	".\..\Applic\Res\Curh_23.cur"\
	".\..\Applic\Res\Curh_31.cur"\
	".\..\Applic\Res\Curtext.cur"\
	".\..\Applic\Res\000%.cur"\
	".\..\Applic\Res\012%.cur"\
	".\..\Applic\Res\025%.cur"\
	".\..\Applic\Res\037%.cur"\
	".\..\Applic\Res\050%.cur"\
	".\..\Applic\Res\062%.cur"\
	".\..\Applic\Res\075%.cur"\
	".\..\Applic\Res\087%.cur"\
	".\..\Applic\Res\100%.cur"\
	

"$(INTDIR)\CreM.res" : $(SOURCE) $(DEP_RSC_CREM_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
