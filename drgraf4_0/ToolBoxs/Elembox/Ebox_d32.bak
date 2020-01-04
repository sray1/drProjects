# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Ebox_d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Ebox_d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Ebox_d - Win32 Release" && "$(CFG)" != "Ebox_d - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ebox_d32.mak" CFG="Ebox_d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ebox_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Ebox_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Ebox_d - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe
CPP=cl.exe

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

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

ALL : "$(OUTDIR)\Ebox_d32.dll"

CLEAN : 
	-@erase ".\Release\Ebox_d32.dll"
	-@erase ".\Release\Quadbox.obj"
	-@erase ".\Release\Pipebar.obj"
	-@erase ".\Release\Tetbar.obj"
	-@erase ".\Release\MeshBar0.obj"
	-@erase ".\Release\MeshBox3.obj"
	-@erase ".\Release\Penbox.obj"
	-@erase ".\Release\Palette.obj"
	-@erase ".\Release\Stdafx.obj"
	-@erase ".\Release\PipeBox.obj"
	-@erase ".\Release\MeshBox2.obj"
	-@erase ".\Release\Hexbox.obj"
	-@erase ".\Release\OldGlob.obj"
	-@erase ".\Release\Penbar.obj"
	-@erase ".\Release\MeshBar3.obj"
	-@erase ".\Release\MeshBox1.obj"
	-@erase ".\Release\OldTool.obj"
	-@erase ".\Release\Tribox.obj"
	-@erase ".\Release\MeshBar2.obj"
	-@erase ".\Release\Hexbar.obj"
	-@erase ".\Release\Eboxdll.obj"
	-@erase ".\Release\EoxWnd.obj"
	-@erase ".\Release\Quadbar.obj"
	-@erase ".\Release\MeshBox0.obj"
	-@erase ".\Release\Tetbox.obj"
	-@erase ".\Release\MeshBar1.obj"
	-@erase ".\Release\Tribar.obj"
	-@erase ".\Release\Ebox.res"
	-@erase ".\Release\Ebox_d32.lib"
	-@erase ".\Release\Ebox_d32.exp"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W4 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MD /W4 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W4 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Ebox_d32.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Ebox.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ebox_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
LINK32_FLAGS=oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Ebox_d32.pdb" /map:"FULL" /machine:IX86\
 /def:".\Ebox_d.def" /out:"$(OUTDIR)/Ebox_d32.dll"\
 /implib:"$(OUTDIR)/Ebox_d32.lib" 
DEF_FILE= \
	".\Ebox_d.def"
LINK32_OBJS= \
	".\Release\Quadbox.obj" \
	".\Release\Pipebar.obj" \
	".\Release\Tetbar.obj" \
	".\Release\MeshBar0.obj" \
	".\Release\MeshBox3.obj" \
	".\Release\Penbox.obj" \
	".\Release\Palette.obj" \
	".\Release\Stdafx.obj" \
	".\Release\PipeBox.obj" \
	".\Release\MeshBox2.obj" \
	".\Release\Hexbox.obj" \
	".\Release\OldGlob.obj" \
	".\Release\Penbar.obj" \
	".\Release\MeshBar3.obj" \
	".\Release\MeshBox1.obj" \
	".\Release\OldTool.obj" \
	".\Release\Tribox.obj" \
	".\Release\MeshBar2.obj" \
	".\Release\Hexbar.obj" \
	".\Release\Eboxdll.obj" \
	".\Release\EoxWnd.obj" \
	".\Release\Quadbar.obj" \
	".\Release\MeshBox0.obj" \
	".\Release\Tetbox.obj" \
	".\Release\MeshBar1.obj" \
	".\Release\Tribar.obj" \
	".\Release\Ebox.res"

"$(OUTDIR)\Ebox_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

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

ALL : "$(OUTDIR)\Ebox_d32.dll"

CLEAN : 
	-@erase ".\E_BOX.PDB"
	-@erase "..\..\applic\Debug\Ebox_d32.dll"
	-@erase ".\Debug\Quadbox.obj"
	-@erase ".\Debug\Stdafx.obj"
	-@erase ".\Debug\MeshBar0.obj"
	-@erase ".\Debug\MeshBox1.obj"
	-@erase ".\Debug\OldTool.obj"
	-@erase ".\Debug\Eboxdll.obj"
	-@erase ".\Debug\Penbox.obj"
	-@erase ".\Debug\Quadbar.obj"
	-@erase ".\Debug\Tribox.obj"
	-@erase ".\Debug\PipeBox.obj"
	-@erase ".\Debug\MeshBox0.obj"
	-@erase ".\Debug\MeshBar3.obj"
	-@erase ".\Debug\Tetbox.obj"
	-@erase ".\Debug\Hexbox.obj"
	-@erase ".\Debug\Penbar.obj"
	-@erase ".\Debug\Tribar.obj"
	-@erase ".\Debug\Pipebar.obj"
	-@erase ".\Debug\MeshBar2.obj"
	-@erase ".\Debug\MeshBox3.obj"
	-@erase ".\Debug\Tetbar.obj"
	-@erase ".\Debug\Hexbar.obj"
	-@erase ".\Debug\MeshBar1.obj"
	-@erase ".\Debug\EoxWnd.obj"
	-@erase ".\Debug\Palette.obj"
	-@erase ".\Debug\MeshBox2.obj"
	-@erase ".\Debug\OldGlob.obj"
	-@erase ".\Debug\Ebox.res"
	-@erase "..\..\applic\Debug\Ebox_d32.lib"
	-@erase "..\..\applic\Debug\Ebox_d32.exp"
	-@erase ".\Debug\Ebox_d32.pdb"
	-@erase ".\Debug\Ebox_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /Fd"E_BOX.PDB" /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /Fd"E_BOX.PDB" /c
CPP_PROJ=/nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Ebox_d32.pch" /YX"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"E_BOX.PDB" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Ebox.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ebox_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 ldllcew.lib oldnames.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib /nologo /subsystem:windows /dll /incremental:no /map:"d:\drgraf4_0\toolboxs\elembox\Debug\Ebox_d32.map" /debug /machine:IX86 /out:"d:\drgraf4_0\applic\Debug\Ebox_d32.dll" /implib:"d:\drgraf4_0\applic\Debug\Ebox_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Dr3D_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib\
 OGen_D32.lib Supp_D32.lib StaL_D32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Ebox_d32.pdb" /map:"$(INTDIR)/Ebox_d32.map"\
 /debug /machine:IX86 /def:".\Ebox_d.def"\
 /out:"d:\drgraf4_0\applic\Debug\Ebox_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug\Ebox_d32.lib" 
DEF_FILE= \
	".\Ebox_d.def"
LINK32_OBJS= \
	".\Debug\Quadbox.obj" \
	".\Debug\Stdafx.obj" \
	".\Debug\MeshBar0.obj" \
	".\Debug\MeshBox1.obj" \
	".\Debug\OldTool.obj" \
	".\Debug\Eboxdll.obj" \
	".\Debug\Penbox.obj" \
	".\Debug\Quadbar.obj" \
	".\Debug\Tribox.obj" \
	".\Debug\PipeBox.obj" \
	".\Debug\MeshBox0.obj" \
	".\Debug\MeshBar3.obj" \
	".\Debug\Tetbox.obj" \
	".\Debug\Hexbox.obj" \
	".\Debug\Penbar.obj" \
	".\Debug\Tribar.obj" \
	".\Debug\Pipebar.obj" \
	".\Debug\MeshBar2.obj" \
	".\Debug\MeshBox3.obj" \
	".\Debug\Tetbar.obj" \
	".\Debug\Hexbar.obj" \
	".\Debug\MeshBar1.obj" \
	".\Debug\EoxWnd.obj" \
	".\Debug\Palette.obj" \
	".\Debug\MeshBox2.obj" \
	".\Debug\OldGlob.obj" \
	".\Debug\Ebox.res"

"$(OUTDIR)\Ebox_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

F90_PROJ=/I "Release/" /Fo"Release/" 

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

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

################################################################################
# Begin Target

# Name "Ebox_d - Win32 Release"
# Name "Ebox_d - Win32 Debug"

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Ebox.rc

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

DEP_RSC_EBOX_=\
	".\Res\Button.cur"\
	".\Res\CntlBox.bmp"\
	".\Res\CurveBar.bmp"\
	".\Res\Operbox.bmp"\
	".\Res\ElemBox.bmp"\
	".\Res\Patchbar.bmp"\
	".\Res\solidbar.bmp"\
	".\Res\pipebar.bmp"\
	".\Res\tribar.bmp"\
	".\Res\penbar.bmp"\
	".\Res\hexbar.bmp"\
	".\Res\tetbar.bmp"\
	".\Res\brickbar.bmp"\
	".\Res\quadbar.bmp"\
	".\Res\Suppbox.bmp"\
	".\Res\Nodebar.bmp"\
	".\Res\StaLBar.bmp"\
	".\Res\DynLBar.bmp"\
	".\Res\ModaBar.bmp"\
	".\BoxBMPID.h"\
	

"$(INTDIR)\Ebox.res" : $(SOURCE) $(DEP_RSC_EBOX_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

DEP_RSC_EBOX_=\
	".\Res\Button.cur"\
	".\Res\MeshBox0.bmp"\
	".\Res\MeshBox1.bmp"\
	".\Res\MeshBox2.bmp"\
	".\Res\MeshBox3.bmp"\
	".\Res\pipebox.bmp"\
	".\Res\tribox.bmp"\
	".\Res\penbox.bmp"\
	".\Res\hexbox.bmp"\
	".\Res\tetBox.bmp"\
	".\Res\brickbox.bmp"\
	".\Res\quadbox.bmp"\
	

"$(INTDIR)\Ebox.res" : $(SOURCE) $(DEP_RSC_EBOX_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	{$(INCLUDE)}"\Stdafx.h"\
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Eboxdll.cpp
DEP_CPP_EBOXD=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Glb_Mo.h"\
	".\EBoxDll.h"\
	".\..\..\GLOBHEAD\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	

"$(INTDIR)\Eboxdll.obj" : $(SOURCE) $(DEP_CPP_EBOXD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ebox_d.def

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OldTool.cpp
DEP_CPP_OLDTO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldTool.h"\
	".\OldGlob.h"\
	

"$(INTDIR)\OldTool.obj" : $(SOURCE) $(DEP_CPP_OLDTO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\OldGlob.cpp
DEP_CPP_OLDGL=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	

"$(INTDIR)\OldGlob.obj" : $(SOURCE) $(DEP_CPP_OLDGL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Palette.cpp
DEP_CPP_PALET=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	".\Palette.h"\
	

"$(INTDIR)\Palette.obj" : $(SOURCE) $(DEP_CPP_PALET) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Penbar.cpp
DEP_CPP_PENBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	".\PENbutt.h"\
	".\Penbox.h"\
	".\Penbar.h"\
	".\EoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Penbar.obj" : $(SOURCE) $(DEP_CPP_PENBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Penbox.cpp
DEP_CPP_PENBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	".\Palette.h"\
	".\PENbutt.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\Penbox.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\EoxWnd.h"\
	".\MeshBar0.h"\
	".\MeshBar1.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\MeshBar2.h"\
	".\Tribox.h"\
	".\Quadbox.h"\
	".\Tribar.h"\
	".\QuadBar.h"\
	".\MeshBar3.h"\
	".\Hexbox.h"\
	".\TETbox.h"\
	".\HexBar.h"\
	".\TETBar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	".\Penbar.h"\
	

"$(INTDIR)\Penbox.obj" : $(SOURCE) $(DEP_CPP_PENBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tribar.cpp
DEP_CPP_TRIBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	".\TRIbutt.h"\
	".\Tribox.h"\
	".\Tribar.h"\
	".\EoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Tribar.obj" : $(SOURCE) $(DEP_CPP_TRIBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tribox.cpp
DEP_CPP_TRIBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	".\Palette.h"\
	".\TRIbutt.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\Tribox.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\EoxWnd.h"\
	".\MeshBar0.h"\
	".\MeshBar1.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\MeshBar2.h"\
	".\Quadbox.h"\
	".\QuadBar.h"\
	".\MeshBar3.h"\
	".\Hexbox.h"\
	".\Penbox.h"\
	".\TETbox.h"\
	".\HexBar.h"\
	".\Penbar.h"\
	".\TETBar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	".\Tribar.h"\
	

"$(INTDIR)\Tribox.obj" : $(SOURCE) $(DEP_CPP_TRIBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Quadbox.cpp
DEP_CPP_QUADB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	".\Palette.h"\
	".\Quadbutt.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\Quadbox.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\EoxWnd.h"\
	".\MeshBar0.h"\
	".\MeshBar1.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\MeshBar2.h"\
	".\Tribox.h"\
	".\Tribar.h"\
	".\MeshBar3.h"\
	".\Hexbox.h"\
	".\Penbox.h"\
	".\TETbox.h"\
	".\HexBar.h"\
	".\Penbar.h"\
	".\TETBar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	".\QuadBar.h"\
	

"$(INTDIR)\Quadbox.obj" : $(SOURCE) $(DEP_CPP_QUADB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Quadbar.cpp
DEP_CPP_QUADBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	".\Quadbutt.h"\
	".\Quadbox.h"\
	".\QuadBar.h"\
	".\EoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Quadbar.obj" : $(SOURCE) $(DEP_CPP_QUADBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hexbox.cpp
DEP_CPP_HEXBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	".\Palette.h"\
	".\HEXbutt.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\Hexbox.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\EoxWnd.h"\
	".\MeshBar0.h"\
	".\MeshBar1.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\MeshBar2.h"\
	".\Tribox.h"\
	".\Quadbox.h"\
	".\Tribar.h"\
	".\QuadBar.h"\
	".\MeshBar3.h"\
	".\Penbox.h"\
	".\TETbox.h"\
	".\Penbar.h"\
	".\TETBar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	".\HexBar.h"\
	

"$(INTDIR)\Hexbox.obj" : $(SOURCE) $(DEP_CPP_HEXBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hexbar.cpp
DEP_CPP_HEXBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	".\HEXbutt.h"\
	".\Hexbox.h"\
	".\HexBar.h"\
	".\EoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Hexbar.obj" : $(SOURCE) $(DEP_CPP_HEXBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tetbox.cpp
DEP_CPP_TETBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	".\Palette.h"\
	".\TETbutt.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\TETbox.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\EoxWnd.h"\
	".\MeshBar0.h"\
	".\MeshBar1.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\MeshBar2.h"\
	".\Tribox.h"\
	".\Quadbox.h"\
	".\Tribar.h"\
	".\QuadBar.h"\
	".\MeshBar3.h"\
	".\Hexbox.h"\
	".\Penbox.h"\
	".\HexBar.h"\
	".\Penbar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	".\TETBar.h"\
	

"$(INTDIR)\Tetbox.obj" : $(SOURCE) $(DEP_CPP_TETBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tetbar.cpp
DEP_CPP_TETBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	".\TETbutt.h"\
	".\TETbox.h"\
	".\TETBar.h"\
	".\EoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Tetbar.obj" : $(SOURCE) $(DEP_CPP_TETBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBar3.cpp
DEP_CPP_MESHB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	".\Meshbut3.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\MeshBar3.h"\
	".\EoxWnd.h"\
	".\Hexbox.h"\
	".\Penbox.h"\
	".\TETbox.h"\
	".\HexBar.h"\
	".\Palette.h"\
	".\Penbar.h"\
	".\TETBar.h"\
	

"$(INTDIR)\MeshBar3.obj" : $(SOURCE) $(DEP_CPP_MESHB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBar1.cpp
DEP_CPP_MESHBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	".\Meshbut1.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	".\MeshBar1.h"\
	".\EoxWnd.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\Palette.h"\
	

"$(INTDIR)\MeshBar1.obj" : $(SOURCE) $(DEP_CPP_MESHBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBar2.cpp
DEP_CPP_MESHBAR=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	".\Meshbut2.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	".\MeshBar2.h"\
	".\EoxWnd.h"\
	".\Tribox.h"\
	".\Quadbox.h"\
	".\Tribar.h"\
	".\Palette.h"\
	".\QuadBar.h"\
	

"$(INTDIR)\MeshBar2.obj" : $(SOURCE) $(DEP_CPP_MESHBAR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBar0.cpp
DEP_CPP_MESHBAR0=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	".\Meshbut0.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	".\MeshBar0.h"\
	".\EoxWnd.h"\
	".\Palette.h"\
	

"$(INTDIR)\MeshBar0.obj" : $(SOURCE) $(DEP_CPP_MESHBAR0) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBox3.cpp
DEP_CPP_MESHBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\Meshbut3.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	".\EoxWnd.h"\
	".\MeshBar0.h"\
	".\MeshBar1.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\MeshBar2.h"\
	".\Tribox.h"\
	".\Quadbox.h"\
	".\Tribar.h"\
	".\QuadBar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	".\MeshBar3.h"\
	".\Hexbox.h"\
	".\Penbox.h"\
	".\TETbox.h"\
	".\HexBar.h"\
	".\Penbar.h"\
	".\TETBar.h"\
	

"$(INTDIR)\MeshBox3.obj" : $(SOURCE) $(DEP_CPP_MESHBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBox2.cpp
DEP_CPP_MESHBOX=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\Meshbut2.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\EoxWnd.h"\
	".\MeshBar0.h"\
	".\MeshBar1.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\MeshBar3.h"\
	".\Hexbox.h"\
	".\Penbox.h"\
	".\TETbox.h"\
	".\HexBar.h"\
	".\Penbar.h"\
	".\TETBar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	".\MeshBar2.h"\
	".\Tribox.h"\
	".\Quadbox.h"\
	".\Tribar.h"\
	".\QuadBar.h"\
	

"$(INTDIR)\MeshBox2.obj" : $(SOURCE) $(DEP_CPP_MESHBOX) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBox1.cpp
DEP_CPP_MESHBOX1=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\Meshbut1.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\EoxWnd.h"\
	".\MeshBar0.h"\
	".\MeshBar2.h"\
	".\Tribox.h"\
	".\Quadbox.h"\
	".\Tribar.h"\
	".\QuadBar.h"\
	".\MeshBar3.h"\
	".\Hexbox.h"\
	".\Penbox.h"\
	".\TETbox.h"\
	".\HexBar.h"\
	".\Penbar.h"\
	".\TETBar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	".\MeshBar1.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	

"$(INTDIR)\MeshBox1.obj" : $(SOURCE) $(DEP_CPP_MESHBOX1) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBox0.cpp
DEP_CPP_MESHBOX0=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\Meshbut0.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\EoxWnd.h"\
	".\MeshBar1.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\MeshBar2.h"\
	".\Tribox.h"\
	".\Quadbox.h"\
	".\Tribar.h"\
	".\QuadBar.h"\
	".\MeshBar3.h"\
	".\Hexbox.h"\
	".\Penbox.h"\
	".\TETbox.h"\
	".\HexBar.h"\
	".\Penbar.h"\
	".\TETBar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	".\MeshBar0.h"\
	

"$(INTDIR)\MeshBox0.obj" : $(SOURCE) $(DEP_CPP_MESHBOX0) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tribox.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hexbox.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBar0.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBar1.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBar2.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBar3.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBox0.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBox1.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBox2.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshBox3.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Penbar.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Penbox.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QuadBar.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Quadbox.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TETBar.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TETbox.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tribar.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HexBar.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PipeBox.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PipeBox.cpp
DEP_CPP_PIPEB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	".\Palette.h"\
	".\PIPEbutt.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\PipeBox.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\EoxWnd.h"\
	".\MeshBar0.h"\
	".\MeshBar1.h"\
	".\MeshBar2.h"\
	".\Tribox.h"\
	".\Quadbox.h"\
	".\Tribar.h"\
	".\QuadBar.h"\
	".\MeshBar3.h"\
	".\Hexbox.h"\
	".\Penbox.h"\
	".\TETbox.h"\
	".\HexBar.h"\
	".\Penbar.h"\
	".\TETBar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	".\Pipebar.h"\
	

"$(INTDIR)\PipeBox.obj" : $(SOURCE) $(DEP_CPP_PIPEB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pipebar.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pipebar.cpp
DEP_CPP_PIPEBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\EoxWndID.h"\
	".\EoxBMPID.h"\
	".\PIPEbutt.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\EoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Pipebar.obj" : $(SOURCE) $(DEP_CPP_PIPEBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EoxWnd.h

!IF  "$(CFG)" == "Ebox_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ebox_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EoxWnd.cpp
DEP_CPP_EOXWN=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\EoxWnd.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\IGenBox\EDimBox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\..\APPLIC\StatCntl.h"\
	".\..\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\Drawbox\palette.h"\
	".\..\Drawbox\Oldtool.h"\
	".\..\IGenBox\BoxWnd.h"\
	".\..\IGenBox\MainBar.h"\
	".\..\IGenBox\GOpBox.h"\
	".\..\IGenBox\COpBox.h"\
	".\..\IGenBox\palette.h"\
	".\..\IGenBox\Oldtool.h"\
	".\..\IGenBox\GOpBar.h"\
	".\..\IGenBox\COpBar.h"\
	".\..\IGenBox\IGenBar.h"\
	{$(INCLUDE)}"\Nodebox.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Nodebar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\..\IGenBox\SuppBox.h"\
	".\..\IGenBox\StaLBox.h"\
	".\..\IGenBox\DynLBox.h"\
	".\..\IGenBox\SpeLBox.h"\
	".\..\IGenBox\Suppbar.h"\
	".\..\IGenBox\StaLbar.h"\
	".\..\IGenBox\DynLbar.h"\
	".\..\IGenBox\SpeLbar.h"\
	".\..\IGenBox\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\MeshBar0.h"\
	".\Palette.h"\
	".\OldTool.h"\
	".\MeshBar1.h"\
	".\PipeBox.h"\
	".\Pipebar.h"\
	".\MeshBar2.h"\
	".\Tribox.h"\
	".\Quadbox.h"\
	".\Tribar.h"\
	".\QuadBar.h"\
	".\MeshBar3.h"\
	".\Hexbox.h"\
	".\Penbox.h"\
	".\TETbox.h"\
	".\HexBar.h"\
	".\Penbar.h"\
	".\TETBar.h"\
	".\..\Drawbox\dboxButt.h"\
	".\..\Drawbox\drawbar.h"\
	".\..\Drawbox\colorsqu.h"\
	".\..\..\MOUSEMGR\DLdMouse.h"\
	".\..\..\MOUSEMGR\dbMouse.h"\
	".\..\..\MOUSEMGR\SpLMouse.h"\
	".\..\..\MOUSEMGR\SLDMouse.h"\
	".\..\..\MOUSEMGR\SupMouse.h"\
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
	".\..\..\GLOBHEAD\Def_IGen.h"\
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
	".\..\..\MOUSEMGR\SLDCur.h"\
	".\..\..\MOUSEMGR\SLDNod.h"\
	".\..\..\MOUSEMGR\SLDObj.h"\
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
	

"$(INTDIR)\EoxWnd.obj" : $(SOURCE) $(DEP_CPP_EOXWN) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
