# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=IGenBox - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to IGenBox - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IGenBox - Win32 Release" && "$(CFG)" !=\
 "IGenBox - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "IGenBox.mak" CFG="IGenBox - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IGenBox - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IGenBox - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "IGenBox - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe
CPP=cl.exe

!IF  "$(CFG)" == "IGenBox - Win32 Release"

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

ALL : "$(OUTDIR)\IGenBox.dll"

CLEAN : 
	-@erase ".\Release\IGenBox.dll"
	-@erase ".\Release\IGenMgr.obj"
	-@erase ".\Release\Palette.obj"
	-@erase ".\Release\Patchbox.obj"
	-@erase ".\Release\DynLbar.obj"
	-@erase ".\Release\Mainbox.obj"
	-@erase ".\Release\GOpbox.obj"
	-@erase ".\Release\IGenbox.obj"
	-@erase ".\Release\COpbox.obj"
	-@erase ".\Release\Patchbar.obj"
	-@erase ".\Release\Suppbox.obj"
	-@erase ".\Release\Cntlbox.obj"
	-@erase ".\Release\MainBar.obj"
	-@erase ".\Release\GOpbar.obj"
	-@erase ".\Release\IGenbar.obj"
	-@erase ".\Release\EDimBox.obj"
	-@erase ".\Release\COpbar.obj"
	-@erase ".\Release\Nodebox.obj"
	-@erase ".\Release\Suppbar.obj"
	-@erase ".\Release\SpeLbox.obj"
	-@erase ".\Release\StaLbox.obj"
	-@erase ".\Release\Curvebox.obj"
	-@erase ".\Release\CNTLbar.obj"
	-@erase ".\Release\Solidbox.obj"
	-@erase ".\Release\OldGlob.obj"
	-@erase ".\Release\IGendll.obj"
	-@erase ".\Release\EDimBar.obj"
	-@erase ".\Release\BoxWnd.obj"
	-@erase ".\Release\Nodebar.obj"
	-@erase ".\Release\DynLbox.obj"
	-@erase ".\Release\OldTool.obj"
	-@erase ".\Release\SpeLbar.obj"
	-@erase ".\Release\StaLbar.obj"
	-@erase ".\Release\Curvebar.obj"
	-@erase ".\Release\Solidbar.obj"
	-@erase ".\Release\IGenbox.res"
	-@erase ".\Release\IGenBox.lib"
	-@erase ".\Release\IGenBox.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/IGenBox.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/IGenbox.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IGenBox.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/IGenBox.pdb" /machine:I386 /def:".\IGenBox_d.def"\
 /out:"$(OUTDIR)/IGenBox.dll" /implib:"$(OUTDIR)/IGenBox.lib" 
DEF_FILE= \
	".\IGenBox_d.def"
LINK32_OBJS= \
	"$(INTDIR)/IGenMgr.obj" \
	"$(INTDIR)/Palette.obj" \
	"$(INTDIR)/Patchbox.obj" \
	"$(INTDIR)/DynLbar.obj" \
	"$(INTDIR)/Mainbox.obj" \
	"$(INTDIR)/GOpbox.obj" \
	"$(INTDIR)/IGenbox.obj" \
	"$(INTDIR)/COpbox.obj" \
	"$(INTDIR)/Patchbar.obj" \
	"$(INTDIR)/Suppbox.obj" \
	"$(INTDIR)/Cntlbox.obj" \
	"$(INTDIR)/MainBar.obj" \
	"$(INTDIR)/GOpbar.obj" \
	"$(INTDIR)/IGenbar.obj" \
	"$(INTDIR)/EDimBox.obj" \
	"$(INTDIR)/COpbar.obj" \
	"$(INTDIR)/Nodebox.obj" \
	"$(INTDIR)/Suppbar.obj" \
	"$(INTDIR)/SpeLbox.obj" \
	"$(INTDIR)/StaLbox.obj" \
	"$(INTDIR)/Curvebox.obj" \
	"$(INTDIR)/CNTLbar.obj" \
	"$(INTDIR)/Solidbox.obj" \
	"$(INTDIR)/OldGlob.obj" \
	"$(INTDIR)/IGendll.obj" \
	"$(INTDIR)/EDimBar.obj" \
	"$(INTDIR)/BoxWnd.obj" \
	"$(INTDIR)/Nodebar.obj" \
	"$(INTDIR)/DynLbox.obj" \
	"$(INTDIR)/OldTool.obj" \
	"$(INTDIR)/SpeLbar.obj" \
	"$(INTDIR)/StaLbar.obj" \
	"$(INTDIR)/Curvebar.obj" \
	"$(INTDIR)/Solidbar.obj" \
	"$(INTDIR)/IGenbox.res"

"$(OUTDIR)\IGenBox.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

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

ALL : "$(OUTDIR)\IGBx_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\..\Applic\Debug\IGBx_D32.dll"
	-@erase ".\Debug\MainBar.obj"
	-@erase ".\Debug\GOpbar.obj"
	-@erase ".\Debug\IGenMgr.obj"
	-@erase ".\Debug\IGenbar.obj"
	-@erase ".\Debug\EDimBox.obj"
	-@erase ".\Debug\COpbar.obj"
	-@erase ".\Debug\Nodebox.obj"
	-@erase ".\Debug\Patchbar.obj"
	-@erase ".\Debug\StaLbox.obj"
	-@erase ".\Debug\CNTLbar.obj"
	-@erase ".\Debug\IGendll.obj"
	-@erase ".\Debug\EDimBar.obj"
	-@erase ".\Debug\Suppbox.obj"
	-@erase ".\Debug\BoxWnd.obj"
	-@erase ".\Debug\Nodebar.obj"
	-@erase ".\Debug\Curvebox.obj"
	-@erase ".\Debug\DynLbox.obj"
	-@erase ".\Debug\Patchbox.obj"
	-@erase ".\Debug\StaLbar.obj"
	-@erase ".\Debug\Solidbox.obj"
	-@erase ".\Debug\Suppbar.obj"
	-@erase ".\Debug\SpeLbox.obj"
	-@erase ".\Debug\Palette.obj"
	-@erase ".\Debug\OldGlob.obj"
	-@erase ".\Debug\Curvebar.obj"
	-@erase ".\Debug\DynLbar.obj"
	-@erase ".\Debug\Solidbar.obj"
	-@erase ".\Debug\Mainbox.obj"
	-@erase ".\Debug\GOpbox.obj"
	-@erase ".\Debug\IGenbox.obj"
	-@erase ".\Debug\COpbox.obj"
	-@erase ".\Debug\OldTool.obj"
	-@erase ".\Debug\SpeLbar.obj"
	-@erase ".\Debug\Cntlbox.obj"
	-@erase ".\Debug\IGenbox.res"
	-@erase "..\..\Applic\Debug\IGBx_D32.ilk"
	-@erase "..\..\Applic\Debug\IGBx_D32.lib"
	-@erase "..\..\Applic\Debug\IGBx_D32.exp"
	-@erase ".\Debug\IGBx_D32.pdb"
	-@erase ".\Debug\IGBx_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/IGenBox.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/IGenBox.pch"\
 /YX"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/IGenbox.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/IGenBox.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib Stal_D32.lib Supp_D32.lib EBox_D32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /out:"d:\DrGraf4_0\Applic\Debug/IGBx_D32.dll" /implib:"d:\DrGraf4_0\Applic\Debug/IGBx_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Dr3D_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib\
 OGen_D32.lib Stal_D32.lib Supp_D32.lib EBox_D32.lib /nologo /subsystem:windows\
 /dll /incremental:yes /pdb:"$(OUTDIR)/IGBx_D32.pdb"\
 /map:"$(INTDIR)/IGBx_D32.map" /debug /machine:I386 /def:".\IGenBox_d.def"\
 /out:"d:\DrGraf4_0\Applic\Debug/IGBx_D32.dll"\
 /implib:"d:\DrGraf4_0\Applic\Debug/IGBx_D32.lib" 
DEF_FILE= \
	".\IGenBox_d.def"
LINK32_OBJS= \
	"$(INTDIR)/MainBar.obj" \
	"$(INTDIR)/GOpbar.obj" \
	"$(INTDIR)/IGenMgr.obj" \
	"$(INTDIR)/IGenbar.obj" \
	"$(INTDIR)/EDimBox.obj" \
	"$(INTDIR)/COpbar.obj" \
	"$(INTDIR)/Nodebox.obj" \
	"$(INTDIR)/Patchbar.obj" \
	"$(INTDIR)/StaLbox.obj" \
	"$(INTDIR)/CNTLbar.obj" \
	"$(INTDIR)/IGendll.obj" \
	"$(INTDIR)/EDimBar.obj" \
	"$(INTDIR)/Suppbox.obj" \
	"$(INTDIR)/BoxWnd.obj" \
	"$(INTDIR)/Nodebar.obj" \
	"$(INTDIR)/Curvebox.obj" \
	"$(INTDIR)/DynLbox.obj" \
	"$(INTDIR)/Patchbox.obj" \
	"$(INTDIR)/StaLbar.obj" \
	"$(INTDIR)/Solidbox.obj" \
	"$(INTDIR)/Suppbar.obj" \
	"$(INTDIR)/SpeLbox.obj" \
	"$(INTDIR)/Palette.obj" \
	"$(INTDIR)/OldGlob.obj" \
	"$(INTDIR)/Curvebar.obj" \
	"$(INTDIR)/DynLbar.obj" \
	"$(INTDIR)/Solidbar.obj" \
	"$(INTDIR)/Mainbox.obj" \
	"$(INTDIR)/GOpbox.obj" \
	"$(INTDIR)/IGenbox.obj" \
	"$(INTDIR)/COpbox.obj" \
	"$(INTDIR)/OldTool.obj" \
	"$(INTDIR)/SpeLbar.obj" \
	"$(INTDIR)/Cntlbox.obj" \
	"$(INTDIR)/IGenbox.res"

"$(OUTDIR)\IGBx_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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

# Name "IGenBox - Win32 Release"
# Name "IGenBox - Win32 Debug"

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\BoxWnd.cpp
DEP_CPP_BOXWN=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\BoxWnd.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\Palette.h"\
	".\OldTool.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	

"$(INTDIR)\BoxWnd.obj" : $(SOURCE) $(DEP_CPP_BOXWN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGenbar.cpp
DEP_CPP_IGENB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\IGenButt.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	".\IGenBar.h"\
	".\BoxWnd.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Palette.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	

"$(INTDIR)\IGenbar.obj" : $(SOURCE) $(DEP_CPP_IGENB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGenbox.cpp
DEP_CPP_IGENBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\IGenButt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	

"$(INTDIR)\IGenbox.obj" : $(SOURCE) $(DEP_CPP_IGENBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGendll.cpp
DEP_CPP_IGEND=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Glb_Mo.h"\
	".\IGendll.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	

"$(INTDIR)\IGendll.obj" : $(SOURCE) $(DEP_CPP_IGEND) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGenMgr.cpp
DEP_CPP_IGENM=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\IGenMgr.h"\
	

"$(INTDIR)\IGenMgr.obj" : $(SOURCE) $(DEP_CPP_IGENM) "$(INTDIR)"


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

SOURCE=.\IGenbox.rc
DEP_RSC_IGENBOX=\
	".\Res\Button.cur"\
	".\Res\CntlBox.bmp"\
	".\Res\CurveBox.bmp"\
	".\Res\GOpbox.bmp"\
	".\Res\PatchBox.bmp"\
	".\Res\solidbox.bmp"\
	".\Res\NodeBox.bmp"\
	".\Res\SpelBox.bmp"\
	".\Res\DynLBar.bmp"\
	".\Res\StaLBox.bmp"\
	".\Res\Suppbox.bmp"\
	".\Res\EDimbox.bmp"\
	".\Res\IGenBox.bmp"\
	".\Res\MainBox.bmp"\
	".\Res\COpbox.bmp"\
	".\BoxBMPID.h"\
	

"$(INTDIR)\IGenbox.res" : $(SOURCE) $(DEP_RSC_IGENBOX) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGenBox_d.def

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

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

SOURCE=.\Suppbox.cpp
DEP_CPP_SUPPB=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\Suppbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\SuppRsrc.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\Suppbox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\OldTool.h"\
	".\Suppbar.h"\
	

"$(INTDIR)\Suppbox.obj" : $(SOURCE) $(DEP_CPP_SUPPB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DynLbox.cpp
DEP_CPP_DYNLB=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\DynLbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\DynLRsrc.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\DynLbox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\OldTool.h"\
	".\DynLbar.h"\
	

"$(INTDIR)\DynLbox.obj" : $(SOURCE) $(DEP_CPP_DYNLB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpeLbar.cpp
DEP_CPP_SPELB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\SpeLRsrc.h"\
	".\SpeLbutt.h"\
	".\SpeLbox.h"\
	".\SpeLbar.h"\
	".\BoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\SpeLbar.obj" : $(SOURCE) $(DEP_CPP_SPELB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpeLbox.cpp
DEP_CPP_SPELBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\SpeLbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\SpeLRsrc.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\SpeLbox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\OldTool.h"\
	".\SpeLbar.h"\
	

"$(INTDIR)\SpeLbox.obj" : $(SOURCE) $(DEP_CPP_SPELBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StaLbar.cpp
DEP_CPP_STALB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\StaLRsrc.h"\
	".\StaLbutt.h"\
	".\StaLbox.h"\
	".\StaLbar.h"\
	".\BoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\StaLbar.obj" : $(SOURCE) $(DEP_CPP_STALB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StaLbox.cpp
DEP_CPP_STALBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\StaLbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\StaLRsrc.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\StaLbox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\OldTool.h"\
	".\StaLbar.h"\
	

"$(INTDIR)\StaLbox.obj" : $(SOURCE) $(DEP_CPP_STALBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Suppbar.cpp
DEP_CPP_SUPPBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\SuppRsrc.h"\
	".\Suppbutt.h"\
	".\Suppbox.h"\
	".\Suppbar.h"\
	".\BoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Suppbar.obj" : $(SOURCE) $(DEP_CPP_SUPPBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DynLbar.cpp
DEP_CPP_DYNLBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\DynLRsrc.h"\
	".\DynLbutt.h"\
	".\DynLbox.h"\
	".\DynLbar.h"\
	".\BoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\DynLbar.obj" : $(SOURCE) $(DEP_CPP_DYNLBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CNTLbar.cpp
DEP_CPP_CNTLB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\Cntlbutt.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\BoxWnd.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\Palette.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	

"$(INTDIR)\CNTLbar.obj" : $(SOURCE) $(DEP_CPP_CNTLB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cntlbox.cpp
DEP_CPP_CNTLBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\Cntlbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\SuppRsrc.h"\
	".\StaLRsrc.h"\
	".\SpeLRsrc.h"\
	".\DynLRsrc.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
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
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\..\MOUSEMGR\O3DMouse.h"\
	{$(INCLUDE)}"\dlg_Supi.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	

"$(INTDIR)\Cntlbox.obj" : $(SOURCE) $(DEP_CPP_CNTLBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Solidbox.cpp
DEP_CPP_SOLID=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\Sboxbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\Solidbox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\Solidbar.h"\
	

"$(INTDIR)\Solidbox.obj" : $(SOURCE) $(DEP_CPP_SOLID) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Curvebox.cpp
DEP_CPP_CURVE=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\Cboxbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\Curvebox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\Curvebar.h"\
	

"$(INTDIR)\Curvebox.obj" : $(SOURCE) $(DEP_CPP_CURVE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Nodebar.cpp
DEP_CPP_NODEB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\Nboxbutt.h"\
	".\Nodebox.h"\
	".\Nodebar.h"\
	".\BoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Nodebar.obj" : $(SOURCE) $(DEP_CPP_NODEB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Nodebox.cpp
DEP_CPP_NODEBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\Nboxbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\Nodebox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\Nodebar.h"\
	

"$(INTDIR)\Nodebox.obj" : $(SOURCE) $(DEP_CPP_NODEBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Patchbar.cpp
DEP_CPP_PATCH=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\Pboxbutt.h"\
	".\Patchbox.h"\
	".\Patchbar.h"\
	".\BoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Patchbar.obj" : $(SOURCE) $(DEP_CPP_PATCH) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Patchbox.cpp
DEP_CPP_PATCHB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\Pboxbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	".\Patchbox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\Patchbar.h"\
	

"$(INTDIR)\Patchbox.obj" : $(SOURCE) $(DEP_CPP_PATCHB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Solidbar.cpp
DEP_CPP_SOLIDB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\Sboxbutt.h"\
	".\Solidbox.h"\
	".\Solidbar.h"\
	".\BoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Solidbar.obj" : $(SOURCE) $(DEP_CPP_SOLIDB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Curvebar.cpp
DEP_CPP_CURVEB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\Cboxbutt.h"\
	".\Curvebox.h"\
	".\Curvebar.h"\
	".\BoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\Curvebar.obj" : $(SOURCE) $(DEP_CPP_CURVEB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDimBox.cpp
DEP_CPP_EDIMB=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	".\Palette.h"\
	".\EDimButt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\EoxWndID.h"\
	{$(INCLUDE)}"\EoxBMPID.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
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
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\OldTool.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	

"$(INTDIR)\EDimBox.obj" : $(SOURCE) $(DEP_CPP_EDIMB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDimBar.cpp
DEP_CPP_EDIMBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\EDimButt.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	".\EDimBar.h"\
	".\BoxWnd.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\EDimBar.obj" : $(SOURCE) $(DEP_CPP_EDIMBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainBar.cpp
DEP_CPP_MAINB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\MainButt.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	".\MainBar.h"\
	".\BoxWnd.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\Palette.h"\
	".\COpbar.h"\
	

"$(INTDIR)\MainBar.obj" : $(SOURCE) $(DEP_CPP_MAINB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mainbox.cpp
DEP_CPP_MAINBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\OldGlob.h"\
	".\OldTool.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\Palette.h"\
	".\MainButt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\VOprBox.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\COpbox.h"\
	".\GOpbar.h"\
	".\COpbar.h"\
	

"$(INTDIR)\Mainbox.obj" : $(SOURCE) $(DEP_CPP_MAINBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GOpbar.cpp
DEP_CPP_GOPBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\GOpbutt.h"\
	".\GOpbox.h"\
	".\GOpbar.h"\
	".\BoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\GOpbar.obj" : $(SOURCE) $(DEP_CPP_GOPBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GOpbox.cpp
DEP_CPP_GOPBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	".\Palette.h"\
	".\GOpbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	".\GOpbox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\COpbox.h"\
	".\COpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\OldTool.h"\
	".\GOpbar.h"\
	

"$(INTDIR)\GOpbox.obj" : $(SOURCE) $(DEP_CPP_GOPBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\COpbutt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COpbar.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COpbox.cpp
DEP_CPP_COPBO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	".\Palette.h"\
	".\COpbutt.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	{$(INCLUDE)}"\Def_Mo.h"\
	{$(INCLUDE)}"\Ext_Mo.h"\
	".\COpbox.h"\
	".\..\..\APPLIC\aboutbox.h"\
	".\..\..\APPLIC\Banner.h"\
	".\..\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\DrawBox\VOprBar.h"\
	".\..\DrawBox\palette.h"\
	".\..\DrawBox\Oldtool.h"\
	".\BoxWnd.h"\
	".\MainBar.h"\
	".\GOpbox.h"\
	".\GOpbar.h"\
	".\IGenBar.h"\
	".\Nodebox.h"\
	".\Curvebox.h"\
	".\Patchbox.h"\
	".\Solidbox.h"\
	".\Nodebar.h"\
	".\Curvebar.h"\
	".\Patchbar.h"\
	".\Solidbar.h"\
	{$(INCLUDE)}"\CNTLbar.h"\
	".\Suppbox.h"\
	".\StaLbox.h"\
	".\DynLbox.h"\
	".\SpeLbox.h"\
	".\Suppbar.h"\
	".\StaLbar.h"\
	".\DynLbar.h"\
	".\SpeLbar.h"\
	".\EDimBar.h"\
	{$(INCLUDE)}"\MeshBox0.h"\
	{$(INCLUDE)}"\MeshBox1.h"\
	{$(INCLUDE)}"\MeshBox2.h"\
	{$(INCLUDE)}"\MeshBox3.h"\
	".\..\ELEMBOX\EoxWnd.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar0.h"\
	{$(INCLUDE)}"\..\ELEMBOX\palette.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Oldtool.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar1.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PipeBar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar2.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TriBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\QuadBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tribar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Quadbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\MeshBar3.h"\
	{$(INCLUDE)}"\..\ELEMBOX\HexBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\PenBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\TetBox.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Hexbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Penbar.h"\
	{$(INCLUDE)}"\..\ELEMBOX\Tetbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\DLdmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Dbmouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SpLMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SLDMouse.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\SupMouse.h"\
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
	{$(INCLUDE)}"\..\..\Mousemgr\SolMouse.h"\
	{$(INCLUDE)}"\dlg_O3DI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\PatMouse.h"\
	{$(INCLUDE)}"\dlg_SolI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_sol_I.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\CurMouse.h"\
	{$(INCLUDE)}"\dlg_PatI.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_pat_i.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\NodMouse.h"\
	{$(INCLUDE)}"\dlg_lqci.h"\
	{$(INCLUDE)}"\dlg_crci.h"\
	{$(INCLUDE)}"\..\..\Mousemgr\Mi_cur_i.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\dlg_nodi.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	".\..\..\MMgrCur\MCurRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\DLdEdit.h"\
	{$(INCLUDE)}"\DbEdit.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\SpLEdit.h"\
	{$(INCLUDE)}"\SLDEdit.h"\
	{$(INCLUDE)}"\SupEdit.h"\
	{$(INCLUDE)}"\SolEdit.h"\
	{$(INCLUDE)}"\PatEdit.h"\
	{$(INCLUDE)}"\CurEdit.h"\
	{$(INCLUDE)}"\NodEdit.h"\
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
	"..\..\MeshObj\FaceInfo.h"\
	".\OldTool.h"\
	".\COpbar.h"\
	

"$(INTDIR)\COpbox.obj" : $(SOURCE) $(DEP_CPP_COPBO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\COpbox.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COpbar.cpp
DEP_CPP_COPBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\BoxWndID.h"\
	".\BoxBMPID.h"\
	".\COpbutt.h"\
	".\COpbox.h"\
	".\COpbar.h"\
	".\BoxWnd.h"\
	".\Palette.h"\
	".\OldTool.h"\
	

"$(INTDIR)\COpbar.obj" : $(SOURCE) $(DEP_CPP_COPBA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StaLbutt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cntlbutt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DynLbutt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EDimButt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GOpbutt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGenButt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainButt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pboxbutt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sboxbutt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpeLbutt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cboxbutt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Nboxbutt.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IGenRsrc.h

!IF  "$(CFG)" == "IGenBox - Win32 Release"

!ELSEIF  "$(CFG)" == "IGenBox - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
