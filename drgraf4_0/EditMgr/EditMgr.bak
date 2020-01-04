# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=EditMgr - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to EditMgr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "EditMgr - Win32 Release" && "$(CFG)" !=\
 "EditMgr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "EditMgr.mak" CFG="EditMgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EditMgr - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "EditMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "EditMgr - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "EditMgr - Win32 Release"

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

ALL : "$(OUTDIR)\EditMgr.dll"

CLEAN : 
	-@erase ".\Release\EditMgr.dll"
	-@erase ".\Release\RegenSol.obj"
	-@erase ".\Release\SupEdit.obj"
	-@erase ".\Release\SpLEdit.obj"
	-@erase ".\Release\EmgrDll.obj"
	-@erase ".\Release\Regen2D.obj"
	-@erase ".\Release\NodEdit.obj"
	-@erase ".\Release\Regen1D.obj"
	-@erase ".\Release\SLDEdit.obj"
	-@erase ".\Release\RegenPat.obj"
	-@erase ".\Release\PatEdit.obj"
	-@erase ".\Release\CurEdit.obj"
	-@erase ".\Release\RegenCur.obj"
	-@erase ".\Release\MNodEdit.obj"
	-@erase ".\Release\DLDEdit.obj"
	-@erase ".\Release\Regen3D.obj"
	-@erase ".\Release\SolEdit.obj"
	-@erase ".\Release\EditMgr.obj"
	-@erase ".\Release\Emgr.res"
	-@erase ".\Release\EditMgr.lib"
	-@erase ".\Release\EditMgr.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/EditMgr.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Emgr.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/EditMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/EditMgr.pdb" /machine:I386 /def:".\Emgr_d.def"\
 /out:"$(OUTDIR)/EditMgr.dll" /implib:"$(OUTDIR)/EditMgr.lib" 
DEF_FILE= \
	".\Emgr_d.def"
LINK32_OBJS= \
	".\Release\RegenSol.obj" \
	".\Release\SupEdit.obj" \
	".\Release\SpLEdit.obj" \
	".\Release\EmgrDll.obj" \
	".\Release\Regen2D.obj" \
	".\Release\NodEdit.obj" \
	".\Release\Regen1D.obj" \
	".\Release\SLDEdit.obj" \
	".\Release\RegenPat.obj" \
	".\Release\PatEdit.obj" \
	".\Release\CurEdit.obj" \
	".\Release\RegenCur.obj" \
	".\Release\MNodEdit.obj" \
	".\Release\DLDEdit.obj" \
	".\Release\Regen3D.obj" \
	".\Release\SolEdit.obj" \
	".\Release\EditMgr.obj" \
	".\Release\Emgr.res"

"$(OUTDIR)\EditMgr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

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

ALL : "$(OUTDIR)\EMgr_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\applic\Debug\EMgr_d32.dll"
	-@erase ".\Debug\NodEdit.obj"
	-@erase ".\Debug\RegenSol.obj"
	-@erase ".\Debug\Regen1D.obj"
	-@erase ".\Debug\SLDEdit.obj"
	-@erase ".\Debug\PatEdit.obj"
	-@erase ".\Debug\CurEdit.obj"
	-@erase ".\Debug\DLDEdit.obj"
	-@erase ".\Debug\RegenPat.obj"
	-@erase ".\Debug\Regen3D.obj"
	-@erase ".\Debug\SolEdit.obj"
	-@erase ".\Debug\EditMgr.obj"
	-@erase ".\Debug\RegenCur.obj"
	-@erase ".\Debug\MNodEdit.obj"
	-@erase ".\Debug\SupEdit.obj"
	-@erase ".\Debug\SpLEdit.obj"
	-@erase ".\Debug\EmgrDll.obj"
	-@erase ".\Debug\Regen2D.obj"
	-@erase ".\Debug\Emgr.res"
	-@erase "..\applic\Debug\EMgr_d32.ilk"
	-@erase "..\applic\Debug\EMgr_d32.lib"
	-@erase "..\applic\Debug\EMgr_d32.exp"
	-@erase ".\Debug\EMgr_d32.pdb"
	-@erase ".\Debug\EMgr_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/EditMgr.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/EditMgr.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Emgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/EditMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib MMgr_D32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug\EMgr_d32.dll" /implib:"d:\drgraf4_0\applic\Debug/EMgr_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib\
 OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib\
 MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib\
 MMgr_D32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/EMgr_d32.pdb" /map:"$(INTDIR)/EMgr_d32.map" /debug\
 /machine:I386 /def:".\Emgr_d.def" /out:"d:\drgraf4_0\applic\Debug\EMgr_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/EMgr_d32.lib" 
DEF_FILE= \
	".\Emgr_d.def"
LINK32_OBJS= \
	".\Debug\NodEdit.obj" \
	".\Debug\RegenSol.obj" \
	".\Debug\Regen1D.obj" \
	".\Debug\SLDEdit.obj" \
	".\Debug\PatEdit.obj" \
	".\Debug\CurEdit.obj" \
	".\Debug\DLDEdit.obj" \
	".\Debug\RegenPat.obj" \
	".\Debug\Regen3D.obj" \
	".\Debug\SolEdit.obj" \
	".\Debug\EditMgr.obj" \
	".\Debug\RegenCur.obj" \
	".\Debug\MNodEdit.obj" \
	".\Debug\SupEdit.obj" \
	".\Debug\SpLEdit.obj" \
	".\Debug\EmgrDll.obj" \
	".\Debug\Regen2D.obj" \
	".\Debug\Emgr.res"

"$(OUTDIR)\EMgr_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "EditMgr - Win32 Release"
# Name "EditMgr - Win32 Debug"

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SupEdit.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CurEdit.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EditMgr.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_EDITM=\
	".\Stdafx.h"\
	".\EmgrDll.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Curdef.h"\
	{$(INCLUDE)}"\EditMgr.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\EditMgr.obj" : $(SOURCE) $(DEP_CPP_EDITM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_EDITM=\
	".\Stdafx.h"\
	".\EmgrDll.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Curdef.h"\
	{$(INCLUDE)}"\EditMgr.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\MNodEdit.h"\
	

"$(INTDIR)\EditMgr.obj" : $(SOURCE) $(DEP_CPP_EDITM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EditMgr.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Emgr.rc
DEP_RSC_EMGR_=\
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
	

"$(INTDIR)\Emgr.res" : $(SOURCE) $(DEP_RSC_EMGR_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EmgrDll.cpp
DEP_CPP_EMGRD=\
	".\Stdafx.h"\
	".\EmgrDll.h"\
	

"$(INTDIR)\EmgrDll.obj" : $(SOURCE) $(DEP_CPP_EMGRD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EmgrDll.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EmgrRsrc.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NodEdit.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_NODED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\RegenCur.h"\
	".\RegenPat.h"\
	".\RegenSol.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\NodEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	

"$(INTDIR)\NodEdit.obj" : $(SOURCE) $(DEP_CPP_NODED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_NODED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\RegenCur.h"\
	".\RegenPat.h"\
	".\RegenSol.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\NodEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	

"$(INTDIR)\NodEdit.obj" : $(SOURCE) $(DEP_CPP_NODED) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NodEdit.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PatEdit.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_PATED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MPatMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\PatEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\PatEdit.obj" : $(SOURCE) $(DEP_CPP_PATED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_PATED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MPatMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\PatEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\PatEdit.obj" : $(SOURCE) $(DEP_CPP_PATED) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PatEdit.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SupEdit.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_SUPED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MSupMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Mi_LSupp.h"\
	".\SupEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	{$(INCLUDE)}"\Glb_Supp.h"\
	{$(INCLUDE)}"\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\SupEdit.obj" : $(SOURCE) $(DEP_CPP_SUPED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_SUPED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MSupMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Mi_LSupp.h"\
	".\SupEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	{$(INCLUDE)}"\Glb_Supp.h"\
	{$(INCLUDE)}"\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\SupEdit.obj" : $(SOURCE) $(DEP_CPP_SUPED) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CurEdit.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_CURED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MCurmgr.h"\
	".\CurEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	".\NodEdit.h"\
	

"$(INTDIR)\CurEdit.obj" : $(SOURCE) $(DEP_CPP_CURED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_CURED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MCurmgr.h"\
	".\CurEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	".\NodEdit.h"\
	

"$(INTDIR)\CurEdit.obj" : $(SOURCE) $(DEP_CPP_CURED) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpLEdit.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DLDEdit.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_DLDED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	".\DLdEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\DLDEdit.obj" : $(SOURCE) $(DEP_CPP_DLDED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_DLDED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	".\DLdEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\DLDEdit.obj" : $(SOURCE) $(DEP_CPP_DLDED) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DLdEdit.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SLDEdit.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_SLDED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Mi_StaL.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	".\SLDEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\SpLEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	{$(INCLUDE)}"\Ext_StaL.h"\
	{$(INCLUDE)}"\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\SLDEdit.obj" : $(SOURCE) $(DEP_CPP_SLDED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_SLDED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Mi_StaL.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	".\SLDEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	{$(INCLUDE)}"\Ext_StaL.h"\
	{$(INCLUDE)}"\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\SLDEdit.obj" : $(SOURCE) $(DEP_CPP_SLDED) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SLDEdit.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SolEdit.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_SOLED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MSolMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\SolEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\SolEdit.obj" : $(SOURCE) $(DEP_CPP_SOLED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_SOLED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MSolMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\SolEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\SolEdit.obj" : $(SOURCE) $(DEP_CPP_SOLED) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SolEdit.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpLEdit.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_SPLED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	".\SpLEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\SpLEdit.obj" : $(SOURCE) $(DEP_CPP_SPLED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_SPLED=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	".\SpLEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
	

"$(INTDIR)\SpLEdit.obj" : $(SOURCE) $(DEP_CPP_SPLED) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Emgr_d.def

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegenPat.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegenPat.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_REGEN=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Mp_xtrud.h"\
	{$(INCLUDE)}"\Mp_rotat.h"\
	{$(INCLUDE)}"\Mp_loft2.h"\
	{$(INCLUDE)}"\Mp_CoonP.h"\
	{$(INCLUDE)}"\Mp_CooP3.h"\
	{$(INCLUDE)}"\Mp_duct.h"\
	{$(INCLUDE)}"\Mp_sweep.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\RegenPat.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\RegenPat.obj" : $(SOURCE) $(DEP_CPP_REGEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_REGEN=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Mp_xtrud.h"\
	{$(INCLUDE)}"\Mp_rotat.h"\
	{$(INCLUDE)}"\Mp_loft2.h"\
	{$(INCLUDE)}"\Mp_CoonP.h"\
	{$(INCLUDE)}"\Mp_CooP3.h"\
	{$(INCLUDE)}"\Mp_duct.h"\
	{$(INCLUDE)}"\Mp_sweep.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\RegenPat.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\RegenPat.obj" : $(SOURCE) $(DEP_CPP_REGEN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegenCur.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegenCur.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_REGENC=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	".\RegenCur.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	

"$(INTDIR)\RegenCur.obj" : $(SOURCE) $(DEP_CPP_REGENC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_REGENC=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	".\RegenCur.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	

"$(INTDIR)\RegenCur.obj" : $(SOURCE) $(DEP_CPP_REGENC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegenSol.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegenSol.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_REGENS=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Ms_xtrud.h"\
	{$(INCLUDE)}"\Ms_xtru3.h"\
	{$(INCLUDE)}"\Ms_rotat.h"\
	{$(INCLUDE)}"\Ms_rota3.h"\
	{$(INCLUDE)}"\Ms_lof42.h"\
	{$(INCLUDE)}"\Ms_lof32.h"\
	{$(INCLUDE)}"\Ms_duct.h"\
	{$(INCLUDE)}"\Ms_duc3.h"\
	{$(INCLUDE)}"\Ms_Sweep.h"\
	{$(INCLUDE)}"\Ms_Swee3.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\RegenSol.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	{$(INCLUDE)}"\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\RegenSol.obj" : $(SOURCE) $(DEP_CPP_REGENS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_REGENS=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Ms_xtrud.h"\
	{$(INCLUDE)}"\Ms_xtru3.h"\
	{$(INCLUDE)}"\Ms_rotat.h"\
	{$(INCLUDE)}"\Ms_rota3.h"\
	{$(INCLUDE)}"\Ms_lof42.h"\
	{$(INCLUDE)}"\Ms_lof32.h"\
	{$(INCLUDE)}"\Ms_duct.h"\
	{$(INCLUDE)}"\Ms_duc3.h"\
	{$(INCLUDE)}"\Ms_Sweep.h"\
	{$(INCLUDE)}"\Ms_Swee3.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\RegenSol.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	{$(INCLUDE)}"\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\RegenSol.obj" : $(SOURCE) $(DEP_CPP_REGENS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MNodEdit.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MNodEdit.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_MNODE=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\Regen1D.h"\
	".\Regen2D.h"\
	".\Regen3D.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\MNodEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\DLdEdit.h"\
	".\DbEdit.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
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
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
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
	

"$(INTDIR)\MNodEdit.obj" : $(SOURCE) $(DEP_CPP_MNODE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_MNODE=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\Regen1D.h"\
	".\Regen2D.h"\
	".\Regen3D.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\MNodEdit.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	{$(INCLUDE)}"\DrFE0D.h"\
	

"$(INTDIR)\MNodEdit.obj" : $(SOURCE) $(DEP_CPP_MNODE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Regen1D.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Regen1D.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_REGEN1=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	".\Regen1D.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
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
	".\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\PostMgr\Po_FE1D.h"\
	".\..\PostMgr\Po_Pipe.h"\
	".\..\PostMgr\Po_Beam.h"\
	".\..\PostMgr\Po_Truss.h"\
	".\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	".\..\PostMgr\Po_FE0D.h"\
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
	

"$(INTDIR)\Regen1D.obj" : $(SOURCE) $(DEP_CPP_REGEN1) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_REGEN1=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	".\Regen1D.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	{$(INCLUDE)}"\DrFE1D.h"\
	

"$(INTDIR)\Regen1D.obj" : $(SOURCE) $(DEP_CPP_REGEN1) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Regen2D.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Regen2D.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_REGEN2=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Regen2D.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
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
	

"$(INTDIR)\Regen2D.obj" : $(SOURCE) $(DEP_CPP_REGEN2) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_REGEN2=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Regen2D.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	

"$(INTDIR)\Regen2D.obj" : $(SOURCE) $(DEP_CPP_REGEN2) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Regen3D.h

!IF  "$(CFG)" == "EditMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Regen3D.cpp

!IF  "$(CFG)" == "EditMgr - Win32 Release"

DEP_CPP_REGEN3=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Regen3D.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
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
	".\MNodEdit.h"\
	".\DLdEdit.h"\
	".\DbEdit.h"\
	".\SpLEdit.h"\
	".\SLDEdit.h"\
	".\SupEdit.h"\
	".\SolEdit.h"\
	".\PatEdit.h"\
	".\CurEdit.h"\
	".\NodEdit.h"\
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
	".\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
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
	

"$(INTDIR)\Regen3D.obj" : $(SOURCE) $(DEP_CPP_REGEN3) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EditMgr - Win32 Debug"

DEP_CPP_REGEN3=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\MsMath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\Regen3D.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\DLdmouse.h"\
	".\..\MOUSEMGR\dbMouse.h"\
	".\..\MOUSEMGR\SpLMouse.h"\
	".\..\MOUSEMGR\SLDMouse.h"\
	{$(INCLUDE)}"\..\Mousemgr\SupMouse.h"\
	".\..\MOUSEMGR\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\MOUSEMGR\MI_Cur_I.h"\
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
	".\..\MOUSEMGR\SLDCur.h"\
	".\..\MOUSEMGR\SLDNod.h"\
	".\..\MOUSEMGR\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\CreOpMgr\O3DCreOp.h"\
	".\..\CreOpMgr\SolCreOp.h"\
	".\..\CreOpMgr\PatCreOp.h"\
	".\..\CreOpMgr\CurCreOp.h"\
	".\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
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
	

"$(INTDIR)\Regen3D.obj" : $(SOURCE) $(DEP_CPP_REGEN3) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
