# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Dbox_d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Dbox_d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dbox_d - Win32 Release" && "$(CFG)" != "Dbox_d - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dbox_d32.mak" CFG="Dbox_d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dbox_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dbox_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Dbox_d - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "Dbox_d - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Dbox_d32.dll" "$(OUTDIR)\Dbox_d32.bsc"

CLEAN : 
	-@erase ".\Release\Dbox_d32.bsc"
	-@erase ".\Release\Dboxdll.sbr"
	-@erase ".\Release\Drawbox.sbr"
	-@erase ".\Release\Colorsqu.sbr"
	-@erase ".\Release\Drawbar.sbr"
	-@erase ".\Release\Stdafx.sbr"
	-@erase ".\Release\Palette.sbr"
	-@erase ".\Release\VOprbox.sbr"
	-@erase ".\Release\OldGlob.sbr"
	-@erase ".\Release\BoxWnd.sbr"
	-@erase ".\Release\Oldtool.sbr"
	-@erase ".\Release\VOprBar.sbr"
	-@erase ".\Release\Dbox_d32.dll"
	-@erase ".\Release\Oldtool.obj"
	-@erase ".\Release\VOprBar.obj"
	-@erase ".\Release\Dboxdll.obj"
	-@erase ".\Release\Drawbox.obj"
	-@erase ".\Release\Colorsqu.obj"
	-@erase ".\Release\Drawbar.obj"
	-@erase ".\Release\Stdafx.obj"
	-@erase ".\Release\Palette.obj"
	-@erase ".\Release\VOprbox.obj"
	-@erase ".\Release\OldGlob.obj"
	-@erase ".\Release\BoxWnd.obj"
	-@erase ".\Release\Dbox.res"
	-@erase ".\Release\Dbox_d32.lib"
	-@erase ".\Release\Dbox_d32.exp"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Dbox_d32.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dbox.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dbox_d32.bsc" 
BSC32_SBRS= \
	".\Release\Dboxdll.sbr" \
	".\Release\Drawbox.sbr" \
	".\Release\Colorsqu.sbr" \
	".\Release\Drawbar.sbr" \
	".\Release\Stdafx.sbr" \
	".\Release\Palette.sbr" \
	".\Release\VOprbox.sbr" \
	".\Release\OldGlob.sbr" \
	".\Release\BoxWnd.sbr" \
	".\Release\Oldtool.sbr" \
	".\Release\VOprBar.sbr"

"$(OUTDIR)\Dbox_d32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Dbox_d32.pdb" /map:"FULL" /machine:IX86 /def:".\Dbox_d.def"\
 /out:"$(OUTDIR)/Dbox_d32.dll" /implib:"$(OUTDIR)/Dbox_d32.lib" 
DEF_FILE= \
	".\Dbox_d.def"
LINK32_OBJS= \
	".\Release\Oldtool.obj" \
	".\Release\VOprBar.obj" \
	".\Release\Dboxdll.obj" \
	".\Release\Drawbox.obj" \
	".\Release\Colorsqu.obj" \
	".\Release\Drawbar.obj" \
	".\Release\Stdafx.obj" \
	".\Release\Palette.obj" \
	".\Release\VOprbox.obj" \
	".\Release\OldGlob.obj" \
	".\Release\BoxWnd.obj" \
	".\Release\Dbox.res"

"$(OUTDIR)\Dbox_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"

# PROP BASE Use_MFC 2
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

ALL : "$(OUTDIR)\Dbox_d32.dll"

CLEAN : 
	-@erase ".\D_BOX.PDB"
	-@erase "..\..\applic\Debug\Dbox_d32.dll"
	-@erase ".\Debug\BoxWnd.obj"
	-@erase ".\Debug\Colorsqu.obj"
	-@erase ".\Debug\Drawbox.obj"
	-@erase ".\Debug\VOprbox.obj"
	-@erase ".\Debug\OldGlob.obj"
	-@erase ".\Debug\Drawbar.obj"
	-@erase ".\Debug\Oldtool.obj"
	-@erase ".\Debug\VOprBar.obj"
	-@erase ".\Debug\Palette.obj"
	-@erase ".\Debug\Dboxdll.obj"
	-@erase ".\Debug\Stdafx.obj"
	-@erase ".\Debug\Dbox.res"
	-@erase "..\..\applic\Debug\Dbox_d32.lib"
	-@erase "..\..\applic\Debug\Dbox_d32.exp"
	-@erase ".\Debug\Dbox_d32.pdb"
	-@erase ".\Debug\Dbox_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /Fd"D_BOX.PDB" /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /Fd"D_BOX.PDB" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Dbox_d32.pch" /YX"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"D_BOX.PDB" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dbox.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dbox_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 OMgr_D.lib EBox_D.lib ldllcew.lib oldnames.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib Supp_D32.lib StaL_D32.lib OMgr_D32.lib Dr3D_D32.lib OGen_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:IX86 /out:"d:\drgraf4_0\applic\Debug\Dbox_d32.dll" /implib:"d:\drgraf4_0\applic\Debug\Dbox_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib Supp_D32.lib\
 StaL_D32.lib OMgr_D32.lib Dr3D_D32.lib OGen_D32.lib /nologo /subsystem:windows\
 /dll /incremental:no /pdb:"$(OUTDIR)/Dbox_d32.pdb"\
 /map:"$(INTDIR)/Dbox_d32.map" /debug /machine:IX86 /def:".\Dbox_d.def"\
 /out:"d:\drgraf4_0\applic\Debug\Dbox_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug\Dbox_d32.lib" 
DEF_FILE= \
	".\Dbox_d.def"
LINK32_OBJS= \
	".\Debug\BoxWnd.obj" \
	".\Debug\Colorsqu.obj" \
	".\Debug\Drawbox.obj" \
	".\Debug\VOprbox.obj" \
	".\Debug\OldGlob.obj" \
	".\Debug\Drawbar.obj" \
	".\Debug\Oldtool.obj" \
	".\Debug\VOprBar.obj" \
	".\Debug\Palette.obj" \
	".\Debug\Dboxdll.obj" \
	".\Debug\Stdafx.obj" \
	".\Debug\Dbox.res"

"$(OUTDIR)\Dbox_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

F90_PROJ=/I "Release/" /Fo"Release/" 

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

################################################################################
# Begin Target

# Name "Dbox_d - Win32 Release"
# Name "Dbox_d - Win32 Debug"

!IF  "$(CFG)" == "Dbox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Drawbar.cpp
DEP_CPP_DRAWB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\Palette.h"\
	

!IF  "$(CFG)" == "Dbox_d - Win32 Release"


"$(INTDIR)\Drawbar.obj" : $(SOURCE) $(DEP_CPP_DRAWB) "$(INTDIR)"

"$(INTDIR)\Drawbar.sbr" : $(SOURCE) $(DEP_CPP_DRAWB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"


"$(INTDIR)\Drawbar.obj" : $(SOURCE) $(DEP_CPP_DRAWB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	{$(INCLUDE)}"\Stdafx.h"\
	

!IF  "$(CFG)" == "Dbox_d - Win32 Release"


"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

"$(INTDIR)\Stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"


"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dbox.rc
DEP_RSC_DBOX_=\
	".\RES\PALETTE.BMP"\
	".\Res\VOprBox.bmp"\
	".\RES\BUTTON.CUR"\
	

"$(INTDIR)\Dbox.res" : $(SOURCE) $(DEP_RSC_DBOX_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Colorsqu.cpp
DEP_CPP_COLOR=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\OldTool.h"\
	

!IF  "$(CFG)" == "Dbox_d - Win32 Release"


"$(INTDIR)\Colorsqu.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"

"$(INTDIR)\Colorsqu.sbr" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"


"$(INTDIR)\Colorsqu.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drawbox.cpp

!IF  "$(CFG)" == "Dbox_d - Win32 Release"

DEP_CPP_DRAWBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Ext_DBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	{$(INCLUDE)}"\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	{$(INCLUDE)}"\Suppbox.h"\
	{$(INCLUDE)}"\StaLbox.h"\
	{$(INCLUDE)}"\DynLbox.h"\
	{$(INCLUDE)}"\SpeLbox.h"\
	{$(INCLUDE)}"\Suppbar.h"\
	{$(INCLUDE)}"\StaLbar.h"\
	{$(INCLUDE)}"\DynLbar.h"\
	{$(INCLUDE)}"\SpeLbar.h"\
	{$(INCLUDE)}"\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	".\..\ELEMBOX\MeshBar0.h"\
	".\..\ELEMBOX\palette.h"\
	".\..\Elembox\Oldtool.h"\
	".\..\ELEMBOX\MeshBar1.h"\
	".\..\ELEMBOX\PipeBox.h"\
	".\..\ELEMBOX\PipeBar.h"\
	".\..\ELEMBOX\MeshBar2.h"\
	".\..\ELEMBOX\TriBox.h"\
	".\..\ELEMBOX\QuadBox.h"\
	".\..\ELEMBOX\Tribar.h"\
	".\..\ELEMBOX\Quadbar.h"\
	".\..\ELEMBOX\MeshBar3.h"\
	".\..\ELEMBOX\HexBox.h"\
	".\..\ELEMBOX\PenBox.h"\
	".\..\ELEMBOX\TetBox.h"\
	".\..\ELEMBOX\Hexbar.h"\
	".\..\ELEMBOX\Penbar.h"\
	".\..\ELEMBOX\Tetbar.h"\
	".\..\..\MOUSEMGR\DLdmouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLmouse.h"\
	".\..\..\MOUSEMGR\SLdmouse.h"\
	".\..\..\MOUSEMGR\Supmouse.h"\
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
	".\..\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\..\Mousemgr\SLDCur.h"\
	".\..\..\Mousemgr\SLDNod.h"\
	".\..\..\Mousemgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\..\CreOpMgr\O3DCreOp.h"\
	".\..\..\CreOpMgr\SolCreOp.h"\
	".\..\..\CreOpMgr\PatCreOp.h"\
	".\..\..\CreOpMgr\CurCreOp.h"\
	".\..\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	

"$(INTDIR)\Drawbox.obj" : $(SOURCE) $(DEP_CPP_DRAWBO) "$(INTDIR)"

"$(INTDIR)\Drawbox.sbr" : $(SOURCE) $(DEP_CPP_DRAWBO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"

DEP_CPP_DRAWBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Ext_DBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	{$(INCLUDE)}"\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	{$(INCLUDE)}"\Suppbox.h"\
	{$(INCLUDE)}"\StaLbox.h"\
	{$(INCLUDE)}"\DynLbox.h"\
	{$(INCLUDE)}"\SpeLbox.h"\
	{$(INCLUDE)}"\Suppbar.h"\
	{$(INCLUDE)}"\StaLbar.h"\
	{$(INCLUDE)}"\DynLbar.h"\
	{$(INCLUDE)}"\SpeLbar.h"\
	{$(INCLUDE)}"\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	".\..\ELEMBOX\MeshBar0.h"\
	".\..\ELEMBOX\palette.h"\
	".\..\Elembox\Oldtool.h"\
	".\..\ELEMBOX\MeshBar1.h"\
	".\..\ELEMBOX\PipeBox.h"\
	".\..\ELEMBOX\PipeBar.h"\
	".\..\ELEMBOX\MeshBar2.h"\
	".\..\ELEMBOX\TriBox.h"\
	".\..\ELEMBOX\QuadBox.h"\
	".\..\ELEMBOX\Tribar.h"\
	".\..\ELEMBOX\Quadbar.h"\
	".\..\ELEMBOX\MeshBar3.h"\
	".\..\ELEMBOX\HexBox.h"\
	".\..\ELEMBOX\PenBox.h"\
	".\..\ELEMBOX\TetBox.h"\
	".\..\ELEMBOX\Hexbar.h"\
	".\..\ELEMBOX\Penbar.h"\
	".\..\ELEMBOX\Tetbar.h"\
	".\..\..\MOUSEMGR\DLdmouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLmouse.h"\
	".\..\..\MOUSEMGR\SLdmouse.h"\
	".\..\..\MOUSEMGR\Supmouse.h"\
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
	".\..\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\..\Mousemgr\SLDCur.h"\
	".\..\..\Mousemgr\SLDNod.h"\
	".\..\..\Mousemgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\..\CreOpMgr\O3DCreOp.h"\
	".\..\..\CreOpMgr\SolCreOp.h"\
	".\..\..\CreOpMgr\PatCreOp.h"\
	".\..\..\CreOpMgr\CurCreOp.h"\
	".\..\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\..\..\EditMgr\MNodEdit.h"\
	".\..\..\EditMgr\DLdEdit.h"\
	".\..\..\EditMgr\dbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\..\EditMgr\SpLEdit.h"\
	".\..\..\EditMgr\SLDEdit.h"\
	".\..\..\EditMgr\SupEdit.h"\
	".\..\..\EditMgr\SolEdit.h"\
	".\..\..\EditMgr\PatEdit.h"\
	".\..\..\EditMgr\CurEdit.h"\
	".\..\..\EditMgr\NodEdit.h"\
	".\..\..\DelMgr\DLdDel.h"\
	".\..\..\DelMgr\dbDel.h"\
	".\..\..\DelMgr\SpLDel.h"\
	".\..\..\DelMgr\SLDDel.h"\
	".\..\..\DelMgr\SupDel.h"\
	".\..\..\DelMgr\SolDel.h"\
	".\..\..\DelMgr\PatDel.h"\
	".\..\..\DelMgr\CurDel.h"\
	".\..\..\DelMgr\NodDel.h"\
	".\..\..\PostMgr\PatPost.h"\
	".\..\..\PostMgr\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\..\..\PostMgr\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\..\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\..\PostMgr\Po_FE1D.h"\
	".\..\..\PostMgr\Po_Pipe.h"\
	".\..\..\PostMgr\Po_Beam.h"\
	".\..\..\PostMgr\Po_Truss.h"\
	".\..\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\..\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	

"$(INTDIR)\Drawbox.obj" : $(SOURCE) $(DEP_CPP_DRAWBO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dboxdll.cpp
DEP_CPP_DBOXD=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Glb_Mo.h"\
	{$(INCLUDE)}"\Glb_DBox.h"\
	{$(INCLUDE)}"\Dboxdll.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	

!IF  "$(CFG)" == "Dbox_d - Win32 Release"


"$(INTDIR)\Dboxdll.obj" : $(SOURCE) $(DEP_CPP_DBOXD) "$(INTDIR)"

"$(INTDIR)\Dboxdll.sbr" : $(SOURCE) $(DEP_CPP_DBOXD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"


"$(INTDIR)\Dboxdll.obj" : $(SOURCE) $(DEP_CPP_DBOXD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dbox_d.def

!IF  "$(CFG)" == "Dbox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Palette.cpp
DEP_CPP_PALET=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Palette.h"\
	

!IF  "$(CFG)" == "Dbox_d - Win32 Release"


"$(INTDIR)\Palette.obj" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"

"$(INTDIR)\Palette.sbr" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"


"$(INTDIR)\Palette.obj" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Oldtool.cpp
DEP_CPP_OLDTO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldTool.h"\
	".\OldGlob.h"\
	

!IF  "$(CFG)" == "Dbox_d - Win32 Release"


"$(INTDIR)\Oldtool.obj" : $(SOURCE) $(DEP_CPP_OLDTO) "$(INTDIR)"

"$(INTDIR)\Oldtool.sbr" : $(SOURCE) $(DEP_CPP_OLDTO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"


"$(INTDIR)\Oldtool.obj" : $(SOURCE) $(DEP_CPP_OLDTO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OldGlob.cpp
DEP_CPP_OLDGL=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	

!IF  "$(CFG)" == "Dbox_d - Win32 Release"


"$(INTDIR)\OldGlob.obj" : $(SOURCE) $(DEP_CPP_OLDGL) "$(INTDIR)"

"$(INTDIR)\OldGlob.sbr" : $(SOURCE) $(DEP_CPP_OLDGL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"


"$(INTDIR)\OldGlob.obj" : $(SOURCE) $(DEP_CPP_OLDGL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VOprButt.h

!IF  "$(CFG)" == "Dbox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VOprBar.h

!IF  "$(CFG)" == "Dbox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VOprbox.cpp

!IF  "$(CFG)" == "Dbox_d - Win32 Release"

DEP_CPP_VOPRB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\VOprButt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	{$(INCLUDE)}"\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	{$(INCLUDE)}"\Suppbox.h"\
	{$(INCLUDE)}"\StaLbox.h"\
	{$(INCLUDE)}"\DynLbox.h"\
	{$(INCLUDE)}"\SpeLbox.h"\
	{$(INCLUDE)}"\Suppbar.h"\
	{$(INCLUDE)}"\StaLbar.h"\
	{$(INCLUDE)}"\DynLbar.h"\
	{$(INCLUDE)}"\SpeLbar.h"\
	{$(INCLUDE)}"\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	".\..\ELEMBOX\MeshBar0.h"\
	".\..\ELEMBOX\palette.h"\
	".\..\Elembox\Oldtool.h"\
	".\..\ELEMBOX\MeshBar1.h"\
	".\..\ELEMBOX\PipeBox.h"\
	".\..\ELEMBOX\PipeBar.h"\
	".\..\ELEMBOX\MeshBar2.h"\
	".\..\ELEMBOX\TriBox.h"\
	".\..\ELEMBOX\QuadBox.h"\
	".\..\ELEMBOX\Tribar.h"\
	".\..\ELEMBOX\Quadbar.h"\
	".\..\ELEMBOX\MeshBar3.h"\
	".\..\ELEMBOX\HexBox.h"\
	".\..\ELEMBOX\PenBox.h"\
	".\..\ELEMBOX\TetBox.h"\
	".\..\ELEMBOX\Hexbar.h"\
	".\..\ELEMBOX\Penbar.h"\
	".\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	".\..\..\MOUSEMGR\DLdmouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLmouse.h"\
	".\..\..\MOUSEMGR\SLdmouse.h"\
	".\..\..\MOUSEMGR\Supmouse.h"\
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
	".\..\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\..\Mousemgr\SLDCur.h"\
	".\..\..\Mousemgr\SLDNod.h"\
	".\..\..\Mousemgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\..\CreOpMgr\O3DCreOp.h"\
	".\..\..\CreOpMgr\SolCreOp.h"\
	".\..\..\CreOpMgr\PatCreOp.h"\
	".\..\..\CreOpMgr\CurCreOp.h"\
	".\..\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\VOprBar.h"\
	

"$(INTDIR)\VOprbox.obj" : $(SOURCE) $(DEP_CPP_VOPRB) "$(INTDIR)"

"$(INTDIR)\VOprbox.sbr" : $(SOURCE) $(DEP_CPP_VOPRB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"

DEP_CPP_VOPRB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\VOprButt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	{$(INCLUDE)}"\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	{$(INCLUDE)}"\Suppbox.h"\
	{$(INCLUDE)}"\StaLbox.h"\
	{$(INCLUDE)}"\DynLbox.h"\
	{$(INCLUDE)}"\SpeLbox.h"\
	{$(INCLUDE)}"\Suppbar.h"\
	{$(INCLUDE)}"\StaLbar.h"\
	{$(INCLUDE)}"\DynLbar.h"\
	{$(INCLUDE)}"\SpeLbar.h"\
	{$(INCLUDE)}"\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	".\..\ELEMBOX\MeshBar0.h"\
	".\..\ELEMBOX\palette.h"\
	".\..\Elembox\Oldtool.h"\
	".\..\ELEMBOX\MeshBar1.h"\
	".\..\ELEMBOX\PipeBox.h"\
	".\..\ELEMBOX\PipeBar.h"\
	".\..\ELEMBOX\MeshBar2.h"\
	".\..\ELEMBOX\TriBox.h"\
	".\..\ELEMBOX\QuadBox.h"\
	".\..\ELEMBOX\Tribar.h"\
	".\..\ELEMBOX\Quadbar.h"\
	".\..\ELEMBOX\MeshBar3.h"\
	".\..\ELEMBOX\HexBox.h"\
	".\..\ELEMBOX\PenBox.h"\
	".\..\ELEMBOX\TetBox.h"\
	".\..\ELEMBOX\Hexbar.h"\
	".\..\ELEMBOX\Penbar.h"\
	".\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	".\..\..\MOUSEMGR\DLdmouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLmouse.h"\
	".\..\..\MOUSEMGR\SLdmouse.h"\
	".\..\..\MOUSEMGR\Supmouse.h"\
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
	".\..\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\..\Mousemgr\SLDCur.h"\
	".\..\..\Mousemgr\SLDNod.h"\
	".\..\..\Mousemgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\..\CreOpMgr\O3DCreOp.h"\
	".\..\..\CreOpMgr\SolCreOp.h"\
	".\..\..\CreOpMgr\PatCreOp.h"\
	".\..\..\CreOpMgr\CurCreOp.h"\
	".\..\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\..\..\EditMgr\MNodEdit.h"\
	".\..\..\EditMgr\DLdEdit.h"\
	".\..\..\EditMgr\dbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\..\EditMgr\SpLEdit.h"\
	".\..\..\EditMgr\SLDEdit.h"\
	".\..\..\EditMgr\SupEdit.h"\
	".\..\..\EditMgr\SolEdit.h"\
	".\..\..\EditMgr\PatEdit.h"\
	".\..\..\EditMgr\CurEdit.h"\
	".\..\..\EditMgr\NodEdit.h"\
	".\..\..\DelMgr\DLdDel.h"\
	".\..\..\DelMgr\dbDel.h"\
	".\..\..\DelMgr\SpLDel.h"\
	".\..\..\DelMgr\SLDDel.h"\
	".\..\..\DelMgr\SupDel.h"\
	".\..\..\DelMgr\SolDel.h"\
	".\..\..\DelMgr\PatDel.h"\
	".\..\..\DelMgr\CurDel.h"\
	".\..\..\DelMgr\NodDel.h"\
	".\..\..\PostMgr\PatPost.h"\
	".\..\..\PostMgr\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\..\..\PostMgr\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\..\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\..\PostMgr\Po_FE1D.h"\
	".\..\..\PostMgr\Po_Pipe.h"\
	".\..\..\PostMgr\Po_Beam.h"\
	".\..\..\PostMgr\Po_Truss.h"\
	".\..\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\..\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\VOprBar.h"\
	

"$(INTDIR)\VOprbox.obj" : $(SOURCE) $(DEP_CPP_VOPRB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VOprBox.h

!IF  "$(CFG)" == "Dbox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\VOprBar.cpp
DEP_CPP_VOPRBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\VOprButt.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	".\VOprBar.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	{$(INCLUDE)}"\Palette.h"\
	

!IF  "$(CFG)" == "Dbox_d - Win32 Release"


"$(INTDIR)\VOprBar.obj" : $(SOURCE) $(DEP_CPP_VOPRBA) "$(INTDIR)"

"$(INTDIR)\VOprBar.sbr" : $(SOURCE) $(DEP_CPP_VOPRBA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"


"$(INTDIR)\VOprBar.obj" : $(SOURCE) $(DEP_CPP_VOPRBA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BoxWnd.h

!IF  "$(CFG)" == "Dbox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BoxWnd.cpp

!IF  "$(CFG)" == "Dbox_d - Win32 Release"

DEP_CPP_BOXWN=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	".\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\OldTool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	{$(INCLUDE)}"\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	{$(INCLUDE)}"\Suppbox.h"\
	{$(INCLUDE)}"\StaLbox.h"\
	{$(INCLUDE)}"\DynLbox.h"\
	{$(INCLUDE)}"\SpeLbox.h"\
	{$(INCLUDE)}"\Suppbar.h"\
	{$(INCLUDE)}"\StaLbar.h"\
	{$(INCLUDE)}"\DynLbar.h"\
	{$(INCLUDE)}"\SpeLbar.h"\
	{$(INCLUDE)}"\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	".\..\ELEMBOX\MeshBar0.h"\
	".\..\ELEMBOX\palette.h"\
	".\..\Elembox\Oldtool.h"\
	".\..\ELEMBOX\MeshBar1.h"\
	".\..\ELEMBOX\PipeBox.h"\
	".\..\ELEMBOX\PipeBar.h"\
	".\..\ELEMBOX\MeshBar2.h"\
	".\..\ELEMBOX\TriBox.h"\
	".\..\ELEMBOX\QuadBox.h"\
	".\..\ELEMBOX\Tribar.h"\
	".\..\ELEMBOX\Quadbar.h"\
	".\..\ELEMBOX\MeshBar3.h"\
	".\..\ELEMBOX\HexBox.h"\
	".\..\ELEMBOX\PenBox.h"\
	".\..\ELEMBOX\TetBox.h"\
	".\..\ELEMBOX\Hexbar.h"\
	".\..\ELEMBOX\Penbar.h"\
	".\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	".\..\..\MOUSEMGR\DLdmouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLmouse.h"\
	".\..\..\MOUSEMGR\SLdmouse.h"\
	".\..\..\MOUSEMGR\Supmouse.h"\
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
	".\..\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\..\Mousemgr\SLDCur.h"\
	".\..\..\Mousemgr\SLDNod.h"\
	".\..\..\Mousemgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\..\CreOpMgr\O3DCreOp.h"\
	".\..\..\CreOpMgr\SolCreOp.h"\
	".\..\..\CreOpMgr\PatCreOp.h"\
	".\..\..\CreOpMgr\CurCreOp.h"\
	".\..\..\CreOpMgr\NodCreOp.h"\
	

"$(INTDIR)\BoxWnd.obj" : $(SOURCE) $(DEP_CPP_BOXWN) "$(INTDIR)"

"$(INTDIR)\BoxWnd.sbr" : $(SOURCE) $(DEP_CPP_BOXWN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dbox_d - Win32 Debug"

DEP_CPP_BOXWN=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	".\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\OldTool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	{$(INCLUDE)}"\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	{$(INCLUDE)}"\Suppbox.h"\
	{$(INCLUDE)}"\StaLbox.h"\
	{$(INCLUDE)}"\DynLbox.h"\
	{$(INCLUDE)}"\SpeLbox.h"\
	{$(INCLUDE)}"\Suppbar.h"\
	{$(INCLUDE)}"\StaLbar.h"\
	{$(INCLUDE)}"\DynLbar.h"\
	{$(INCLUDE)}"\SpeLbar.h"\
	{$(INCLUDE)}"\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	".\..\ELEMBOX\MeshBar0.h"\
	".\..\ELEMBOX\palette.h"\
	".\..\Elembox\Oldtool.h"\
	".\..\ELEMBOX\MeshBar1.h"\
	".\..\ELEMBOX\PipeBox.h"\
	".\..\ELEMBOX\PipeBar.h"\
	".\..\ELEMBOX\MeshBar2.h"\
	".\..\ELEMBOX\TriBox.h"\
	".\..\ELEMBOX\QuadBox.h"\
	".\..\ELEMBOX\Tribar.h"\
	".\..\ELEMBOX\Quadbar.h"\
	".\..\ELEMBOX\MeshBar3.h"\
	".\..\ELEMBOX\HexBox.h"\
	".\..\ELEMBOX\PenBox.h"\
	".\..\ELEMBOX\TetBox.h"\
	".\..\ELEMBOX\Hexbar.h"\
	".\..\ELEMBOX\Penbar.h"\
	".\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	".\..\..\MOUSEMGR\DLdmouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLmouse.h"\
	".\..\..\MOUSEMGR\SLdmouse.h"\
	".\..\..\MOUSEMGR\Supmouse.h"\
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
	".\..\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\..\..\MOUSEMGR\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	".\..\..\MOUSEMGR\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	".\..\..\MOUSEMGR\MI_Sol_I.h"\
	".\..\..\MOUSEMGR\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	".\..\..\MOUSEMGR\MI_Pat_I.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\..\MOUSEMGR\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	".\..\..\MOUSEMGR\MI_Cur_I.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\..\MMgrPat\MPatRsrc.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\..\MMgrSupp\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	".\..\..\Mousemgr\SLDCur.h"\
	".\..\..\Mousemgr\SLDNod.h"\
	".\..\..\Mousemgr\SLDObj.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\..\..\CreOpMgr\O3DCreOp.h"\
	".\..\..\CreOpMgr\SolCreOp.h"\
	".\..\..\CreOpMgr\PatCreOp.h"\
	".\..\..\CreOpMgr\CurCreOp.h"\
	".\..\..\CreOpMgr\NodCreOp.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\dlg_croi.h"\
	".\..\..\EditMgr\MNodEdit.h"\
	".\..\..\EditMgr\DLdEdit.h"\
	".\..\..\EditMgr\dbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	".\..\..\EditMgr\SpLEdit.h"\
	".\..\..\EditMgr\SLDEdit.h"\
	".\..\..\EditMgr\SupEdit.h"\
	".\..\..\EditMgr\SolEdit.h"\
	".\..\..\EditMgr\PatEdit.h"\
	".\..\..\EditMgr\CurEdit.h"\
	".\..\..\EditMgr\NodEdit.h"\
	".\..\..\DelMgr\DLdDel.h"\
	".\..\..\DelMgr\dbDel.h"\
	".\..\..\DelMgr\SpLDel.h"\
	".\..\..\DelMgr\SLDDel.h"\
	".\..\..\DelMgr\SupDel.h"\
	".\..\..\DelMgr\SolDel.h"\
	".\..\..\DelMgr\PatDel.h"\
	".\..\..\DelMgr\CurDel.h"\
	".\..\..\DelMgr\NodDel.h"\
	".\..\..\PostMgr\PatPost.h"\
	".\..\..\PostMgr\CurPost.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	".\..\..\PostMgr\Po_FE2D.h"\
	{$(INCLUDE)}"\dlg_fe2i.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	".\..\..\PostMgr\NodPost.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	".\..\..\PostMgr\Po_FE1D.h"\
	".\..\..\PostMgr\Po_Pipe.h"\
	".\..\..\PostMgr\Po_Beam.h"\
	".\..\..\PostMgr\Po_Truss.h"\
	".\..\..\PostMgr\Po_Elbow.h"\
	{$(INCLUDE)}"\dlg_fe1i.h"\
	{$(INCLUDE)}"\dlg_FE0i.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	".\..\..\PostMgr\Po_FE0D.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\..\..\MeshObj\FaceInfo.h"\
	

"$(INTDIR)\BoxWnd.obj" : $(SOURCE) $(DEP_CPP_BOXWN) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
