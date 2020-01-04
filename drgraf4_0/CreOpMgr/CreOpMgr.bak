# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=CreOpMgr - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to CreOpMgr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CreOpMgr - Win32 Release" && "$(CFG)" !=\
 "CreOpMgr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "CreOpMgr.mak" CFG="CreOpMgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CreOpMgr - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CreOpMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "CreOpMgr - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\CreOpMgr.dll"

CLEAN : 
	-@erase ".\Release\CreOpMgr.dll"
	-@erase ".\Release\O3DCreOp.obj"
	-@erase ".\Release\CMgrDll.obj"
	-@erase ".\Release\NodCreOp.obj"
	-@erase ".\Release\SolCreOp.obj"
	-@erase ".\Release\PatCreOp.obj"
	-@erase ".\Release\CurCreOp.obj"
	-@erase ".\Release\CreOpMgr.obj"
	-@erase ".\Release\CMgr.res"
	-@erase ".\Release\CreOpMgr.lib"
	-@erase ".\Release\CreOpMgr.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/CreOpMgr.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CMgr.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CreOpMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/CreOpMgr.pdb" /machine:I386 /def:".\CMgr_d.def"\
 /out:"$(OUTDIR)/CreOpMgr.dll" /implib:"$(OUTDIR)/CreOpMgr.lib" 
DEF_FILE= \
	".\CMgr_d.def"
LINK32_OBJS= \
	"$(INTDIR)/O3DCreOp.obj" \
	"$(INTDIR)/CMgrDll.obj" \
	"$(INTDIR)/NodCreOp.obj" \
	"$(INTDIR)/SolCreOp.obj" \
	"$(INTDIR)/PatCreOp.obj" \
	"$(INTDIR)/CurCreOp.obj" \
	"$(INTDIR)/CreOpMgr.obj" \
	"$(INTDIR)/CMgr.res"

"$(OUTDIR)\CreOpMgr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\CMgr_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\applic\Debug\CMgr_D32.dll"
	-@erase ".\Debug\SolCreOp.obj"
	-@erase ".\Debug\PatCreOp.obj"
	-@erase ".\Debug\CurCreOp.obj"
	-@erase ".\Debug\CreOpMgr.obj"
	-@erase ".\Debug\O3DCreOp.obj"
	-@erase ".\Debug\CMgrDll.obj"
	-@erase ".\Debug\NodCreOp.obj"
	-@erase ".\Debug\CMgr.res"
	-@erase "..\applic\Debug\CMgr_D32.ilk"
	-@erase "..\applic\Debug\CMgr_D32.lib"
	-@erase "..\applic\Debug\CMgr_D32.exp"
	-@erase ".\Debug\CMgr_D32.pdb"
	-@erase ".\Debug\CMgr_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/CreOpMgr.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/CreOpMgr.pch" /YX"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CMgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CreOpMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_d32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib MO3D_D32.lib MMgr_D32.lib PMgr_D32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib:"OMgr_D32.lib Spec_d32.lib Draw_D32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib " /out:"d:\drgraf4_0\applic\Debug/CMgr_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/CMgr_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_d32.lib Elem_D32.lib\
 OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib\
 MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib\
 MO3D_D32.lib MMgr_D32.lib PMgr_D32.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/CMgr_D32.pdb" /map:"$(INTDIR)/CMgr_D32.map"\
 /debug /machine:I386\
 /nodefaultlib:"OMgr_D32.lib Spec_d32.lib Draw_D32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib "\
 /def:".\CMgr_d.def" /out:"d:\drgraf4_0\applic\Debug/CMgr_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/CMgr_D32.lib" 
DEF_FILE= \
	".\CMgr_d.def"
LINK32_OBJS= \
	"$(INTDIR)/SolCreOp.obj" \
	"$(INTDIR)/PatCreOp.obj" \
	"$(INTDIR)/CurCreOp.obj" \
	"$(INTDIR)/CreOpMgr.obj" \
	"$(INTDIR)/O3DCreOp.obj" \
	"$(INTDIR)/CMgrDll.obj" \
	"$(INTDIR)/NodCreOp.obj" \
	"$(INTDIR)/CMgr.res"

"$(OUTDIR)\CMgr_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "CreOpMgr - Win32 Release"
# Name "CreOpMgr - Win32 Debug"

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\CreOpMgr.h

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CreOpMgr.cpp
DEP_CPP_CREOP=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\CMgrDll.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Curdef.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
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
	".\O3DCreOp.h"\
	".\SolCreOp.h"\
	".\PatCreOp.h"\
	".\CurCreOp.h"\
	".\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	

"$(INTDIR)\CreOpMgr.obj" : $(SOURCE) $(DEP_CPP_CREOP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CMgrDll.cpp

"$(INTDIR)\CMgrDll.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CMgrDll.h

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NodCreOp.cpp
DEP_CPP_NODCR=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\NodCreOp.h"\
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
	".\O3DCreOp.h"\
	".\SolCreOp.h"\
	".\PatCreOp.h"\
	".\CurCreOp.h"\
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
	

"$(INTDIR)\NodCreOp.obj" : $(SOURCE) $(DEP_CPP_NODCR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\NodCreOp.h

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CMgr.rc
DEP_RSC_CMGR_=\
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
	

"$(INTDIR)\CMgr.res" : $(SOURCE) $(DEP_RSC_CMGR_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CMgr_d.def

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CurCreOp.h

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CurCreOp.cpp
DEP_CPP_CURCR=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	{$(INCLUDE)}"\Mi_CSPN.h"\
	{$(INCLUDE)}"\Mi_cprof.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\CurCreOp.h"\
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
	".\O3DCreOp.h"\
	".\SolCreOp.h"\
	".\PatCreOp.h"\
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
	{$(INCLUDE)}"\Mi_NSPN.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	".\NodCreOp.h"\
	

"$(INTDIR)\CurCreOp.obj" : $(SOURCE) $(DEP_CPP_CURCR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PatCreOp.h

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PatCreOp.cpp
DEP_CPP_PATCR=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	".\PatCreOp.h"\
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
	".\O3DCreOp.h"\
	".\SolCreOp.h"\
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
	".\CurCreOp.h"\
	".\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	

"$(INTDIR)\PatCreOp.obj" : $(SOURCE) $(DEP_CPP_PATCR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SolCreOp.h

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SolCreOp.cpp
DEP_CPP_SOLCR=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	".\SolCreOp.h"\
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
	".\O3DCreOp.h"\
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
	".\PatCreOp.h"\
	".\CurCreOp.h"\
	".\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	

"$(INTDIR)\SolCreOp.obj" : $(SOURCE) $(DEP_CPP_SOLCR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\O3DCreOp.h

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\O3DCreOp.cpp

!IF  "$(CFG)" == "CreOpMgr - Win32 Release"

DEP_CPP_O3DCR=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	".\O3DCreOp.h"\
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
	".\SolCreOp.h"\
	".\PatCreOp.h"\
	".\CurCreOp.h"\
	".\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	

"$(INTDIR)\O3DCreOp.obj" : $(SOURCE) $(DEP_CPP_O3DCR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CreOpMgr - Win32 Debug"

DEP_CPP_O3DCR=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	".\O3DCreOp.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
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
	{$(INCLUDE)}"\MsObjMgr.h"\
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
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	{$(INCLUDE)}"\Mi_SSPN.h"\
	".\SolCreOp.h"\
	".\..\APPLIC\mdib.h"\
	".\..\TOOLBOXS\DrawBox\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	".\..\TOOLBOXS\IGenBox\MainBar.h"\
	".\..\TOOLBOXS\IGenBox\GOpBox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\IGenBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBox.h"\
	".\..\TOOLBOXS\IGenBox\CurveBox.h"\
	".\..\TOOLBOXS\IGenBox\PatchBox.h"\
	".\..\TOOLBOXS\IGenBox\SolidBox.h"\
	".\..\TOOLBOXS\IGenBox\CntlBar.h"\
	".\..\TOOLBOXS\IGenBox\SuppBox.h"\
	".\..\TOOLBOXS\IGenBox\StaLBox.h"\
	".\..\TOOLBOXS\IGenBox\DynLBox.h"\
	".\..\TOOLBOXS\IGenBox\SpeLBox.h"\
	".\..\TOOLBOXS\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\TOOLBOXS\DrawBox\dboxButt.h"\
	".\..\TOOLBOXS\DrawBox\drawbar.h"\
	".\..\TOOLBOXS\DrawBox\colorsqu.h"\
	".\..\MouseMgr\DLdMouse.h"\
	".\..\MouseMgr\dbMouse.h"\
	".\..\EditMgr\MNodEdit.h"\
	".\..\EditMgr\DLdEdit.h"\
	".\..\EditMgr\dbEdit.h"\
	".\..\DelMgr\DLdDel.h"\
	".\..\DelMgr\dbDel.h"\
	".\..\PostMgr\PatPost.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Mi_PSPN.h"\
	".\PatCreOp.h"\
	".\..\TOOLBOXS\DrawBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\GOpBar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
	".\..\TOOLBOXS\IGenBox\NodeBar.h"\
	".\..\TOOLBOXS\IGenBox\CurveBar.h"\
	".\..\TOOLBOXS\IGenBox\PatchBar.h"\
	".\..\TOOLBOXS\IGenBox\SolidBar.h"\
	".\..\TOOLBOXS\IGenBox\Suppbar.h"\
	".\..\TOOLBOXS\IGenBox\StaLbar.h"\
	".\..\TOOLBOXS\IGenBox\DynLbar.h"\
	".\..\TOOLBOXS\IGenBox\SpeLbar.h"\
	".\..\TOOLBOXS\ELEMBOX\EoxWnd.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar0.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar1.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBox.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar2.h"\
	".\..\TOOLBOXS\ELEMBOX\TriBox.h"\
	".\..\TOOLBOXS\ELEMBOX\QuadBox.h"\
	".\..\TOOLBOXS\ELEMBOX\MeshBar3.h"\
	".\..\TOOLBOXS\ELEMBOX\HexBox.h"\
	".\..\TOOLBOXS\ELEMBOX\PenBox.h"\
	".\..\TOOLBOXS\ELEMBOX\TetBox.h"\
	".\..\MouseMgr\SpLMouse.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\EditMgr\SpLEdit.h"\
	".\..\DelMgr\SpLDel.h"\
	".\..\PostMgr\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\..\PostMgr\Po_FE2D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	{$(INCLUDE)}"\Mi_CSPN.h"\
	".\CurCreOp.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	".\..\TOOLBOXS\ELEMBOX\palette.h"\
	".\..\TOOLBOXS\ELEMBOX\PipeBar.h"\
	".\..\TOOLBOXS\ELEMBOX\Tribar.h"\
	".\..\TOOLBOXS\ELEMBOX\Quadbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Hexbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Penbar.h"\
	".\..\TOOLBOXS\ELEMBOX\Tetbar.h"\
	".\..\MouseMgr\SLDMouse.h"\
	".\..\EditMgr\SLDEdit.h"\
	".\..\DelMgr\SLDDel.h"\
	".\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\PostMgr\Po_FE1D.h"\
	".\..\PostMgr\Po_Pipe.h"\
	".\..\PostMgr\Po_Beam.h"\
	".\..\PostMgr\Po_Truss.h"\
	".\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	".\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	".\..\TOOLBOXS\ELEMBOX\Oldtool.h"\
	".\..\MouseMgr\SupMouse.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	".\..\EditMgr\SupEdit.h"\
	".\..\DelMgr\SupDel.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	".\..\MeshObj\FaceInfo.h"\
	".\..\MouseMgr\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MouseMgr\SLDCur.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\EditMgr\SolEdit.h"\
	".\..\DelMgr\SolDel.h"\
	".\..\MouseMgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MouseMgr\SLDNod.h"\
	".\..\EditMgr\PatEdit.h"\
	".\..\DelMgr\PatDel.h"\
	".\..\MouseMgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MouseMgr\MI_Sol_I.h"\
	".\..\MouseMgr\SLDObj.h"\
	".\..\EditMgr\CurEdit.h"\
	".\..\DelMgr\CurDel.h"\
	".\..\MouseMgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MouseMgr\MI_Pat_I.h"\
	".\..\EditMgr\NodEdit.h"\
	".\..\DelMgr\NodDel.h"\
	".\..\MouseMgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MouseMgr\MI_Cur_I.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	

"$(INTDIR)\O3DCreOp.obj" : $(SOURCE) $(DEP_CPP_O3DCR) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
