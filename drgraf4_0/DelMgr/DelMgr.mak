# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=DelMgr - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DelMgr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DelMgr - Win32 Release" && "$(CFG)" != "DelMgr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DelMgr.mak" CFG="DelMgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DelMgr - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DelMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "DelMgr - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "DelMgr - Win32 Release"

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

ALL : "$(OUTDIR)\DelMgr.dll"

CLEAN : 
	-@erase ".\Release\DelMgr.dll"
	-@erase ".\Release\PatDel.obj"
	-@erase ".\Release\DelMgr.obj"
	-@erase ".\Release\SupDel.obj"
	-@erase ".\Release\DLDDel.obj"
	-@erase ".\Release\SpLDel.obj"
	-@erase ".\Release\SLDDel.obj"
	-@erase ".\Release\DmgrDll.obj"
	-@erase ".\Release\NodDel.obj"
	-@erase ".\Release\SolDel.obj"
	-@erase ".\Release\CurDel.obj"
	-@erase ".\Release\Dmgr.res"
	-@erase ".\Release\DelMgr.lib"
	-@erase ".\Release\DelMgr.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/DelMgr.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dmgr.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DelMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/DelMgr.pdb" /machine:I386 /def:".\Dmgr_d.def"\
 /out:"$(OUTDIR)/DelMgr.dll" /implib:"$(OUTDIR)/DelMgr.lib" 
DEF_FILE= \
	".\Dmgr_d.def"
LINK32_OBJS= \
	".\Release\PatDel.obj" \
	".\Release\DelMgr.obj" \
	".\Release\SupDel.obj" \
	".\Release\DLDDel.obj" \
	".\Release\SpLDel.obj" \
	".\Release\SLDDel.obj" \
	".\Release\DmgrDll.obj" \
	".\Release\NodDel.obj" \
	".\Release\SolDel.obj" \
	".\Release\CurDel.obj" \
	".\Release\Dmgr.res"

"$(OUTDIR)\DelMgr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

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

ALL : "$(OUTDIR)\DMgr_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\applic\Debug\DMgr_d32.dll"
	-@erase ".\Debug\DelMgr.obj"
	-@erase ".\Debug\NodDel.obj"
	-@erase ".\Debug\SupDel.obj"
	-@erase ".\Debug\DLDDel.obj"
	-@erase ".\Debug\SpLDel.obj"
	-@erase ".\Debug\DmgrDll.obj"
	-@erase ".\Debug\SLDDel.obj"
	-@erase ".\Debug\SolDel.obj"
	-@erase ".\Debug\CurDel.obj"
	-@erase ".\Debug\PatDel.obj"
	-@erase ".\Debug\Dmgr.res"
	-@erase "..\applic\Debug\DMgr_d32.ilk"
	-@erase "..\applic\Debug\DMgr_d32.lib"
	-@erase "..\applic\Debug\DMgr_d32.exp"
	-@erase ".\Debug\DMgr_d32.pdb"
	-@erase ".\Debug\DMgr_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/DelMgr.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/DelMgr.pch" /YX"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dmgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DelMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib MMgr_D32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug\DMgr_d32.dll" /implib:"d:\drgraf4_0\applic\Debug/DMgr_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib\
 OGen_D32.lib Supp_D32.lib StaL_D32.lib EDlg_D32.lib DDlg_D32.lib Dr3D_D32.lib\
 MSup_D32.lib MStL_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib\
 MMgr_D32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/DMgr_d32.pdb" /map:"$(INTDIR)/DMgr_d32.map" /debug\
 /machine:I386 /def:".\Dmgr_d.def" /out:"d:\drgraf4_0\applic\Debug\DMgr_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/DMgr_d32.lib" 
DEF_FILE= \
	".\Dmgr_d.def"
LINK32_OBJS= \
	".\Debug\DelMgr.obj" \
	".\Debug\NodDel.obj" \
	".\Debug\SupDel.obj" \
	".\Debug\DLDDel.obj" \
	".\Debug\SpLDel.obj" \
	".\Debug\DmgrDll.obj" \
	".\Debug\SLDDel.obj" \
	".\Debug\SolDel.obj" \
	".\Debug\CurDel.obj" \
	".\Debug\PatDel.obj" \
	".\Debug\Dmgr.res"

"$(OUTDIR)\DMgr_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DelMgr - Win32 Release"
# Name "DelMgr - Win32 Debug"

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\SupDel.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CurDel.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DelMgr.cpp

!IF  "$(CFG)" == "DelMgr - Win32 Release"

DEP_CPP_DELMG=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\DmgrDll.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Curdef.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_MoBox.h"\
	{$(INCLUDE)}"\VOprBox.h"\
	{$(INCLUDE)}"\Mainbox.h"\
	{$(INCLUDE)}"\IGenbox.h"\
	{$(INCLUDE)}"\CntlBox.h"\
	{$(INCLUDE)}"\EDimBox.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	".\DLDDel.h"\
	".\DbDel.h"\
	".\SpLDel.h"\
	".\SLDDel.h"\
	".\SupDel.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	".\SolDel.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	".\PatDel.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	".\CurDel.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\NodDel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	

"$(INTDIR)\DelMgr.obj" : $(SOURCE) $(DEP_CPP_DELMG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

DEP_CPP_DELMG=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\DmgrDll.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Curdef.h"\
	{$(INCLUDE)}"\DelMgr.h"\
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
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
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
	".\DLDDel.h"\
	".\DbDel.h"\
	".\SpLDel.h"\
	".\SLDDel.h"\
	".\SupDel.h"\
	".\SolDel.h"\
	".\PatDel.h"\
	".\CurDel.h"\
	".\NodDel.h"\
	

"$(INTDIR)\DelMgr.obj" : $(SOURCE) $(DEP_CPP_DELMG) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DelMgr.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DLDDel.cpp

!IF  "$(CFG)" == "DelMgr - Win32 Release"

DEP_CPP_DLDDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	".\DLDDel.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	".\SpLDel.h"\
	".\SLDDel.h"\
	".\SupDel.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	".\SolDel.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	".\PatDel.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	".\CurDel.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\NodDel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	

"$(INTDIR)\DLDDel.obj" : $(SOURCE) $(DEP_CPP_DLDDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

DEP_CPP_DLDDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	".\DLDDel.h"\
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
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
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
	".\DbDel.h"\
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
	".\SpLDel.h"\
	".\SLDDel.h"\
	".\SupDel.h"\
	".\SolDel.h"\
	".\PatDel.h"\
	".\CurDel.h"\
	".\NodDel.h"\
	

"$(INTDIR)\DLDDel.obj" : $(SOURCE) $(DEP_CPP_DLDDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DLDDel.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dmgr.rc
DEP_RSC_DMGR_=\
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
	

"$(INTDIR)\Dmgr.res" : $(SOURCE) $(DEP_RSC_DMGR_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DmgrDll.cpp
DEP_CPP_DMGRD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\DmgrDll.h"\
	

"$(INTDIR)\DmgrDll.obj" : $(SOURCE) $(DEP_CPP_DMGRD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DmgrDll.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DmgrRsrc.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NodDel.cpp

!IF  "$(CFG)" == "DelMgr - Win32 Release"

DEP_CPP_NODDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Mp_xtrud.h"\
	{$(INCLUDE)}"\Mp_rotat.h"\
	{$(INCLUDE)}"\Mp_loft2.h"\
	{$(INCLUDE)}"\Mp_CoonP.h"\
	{$(INCLUDE)}"\Mp_CooP3.h"\
	{$(INCLUDE)}"\Mp_duct.h"\
	{$(INCLUDE)}"\Mp_sweep.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	".\NodDel.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	

"$(INTDIR)\NodDel.obj" : $(SOURCE) $(DEP_CPP_NODDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

DEP_CPP_NODDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MNodmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Mp_xtrud.h"\
	{$(INCLUDE)}"\Mp_rotat.h"\
	{$(INCLUDE)}"\Mp_loft2.h"\
	{$(INCLUDE)}"\Mp_CoonP.h"\
	{$(INCLUDE)}"\Mp_CooP3.h"\
	{$(INCLUDE)}"\Mp_duct.h"\
	{$(INCLUDE)}"\Mp_sweep.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	".\NodDel.h"\
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
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
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
	".\DLDDel.h"\
	".\DbDel.h"\
	".\SpLDel.h"\
	".\SLDDel.h"\
	".\SupDel.h"\
	".\SolDel.h"\
	".\PatDel.h"\
	".\CurDel.h"\
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
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\NodDel.obj" : $(SOURCE) $(DEP_CPP_NODDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NodDel.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PatDel.cpp

!IF  "$(CFG)" == "DelMgr - Win32 Release"

DEP_CPP_PATDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MPatMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\PatDel.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	".\CurDel.h"\
	".\NodDel.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	

"$(INTDIR)\PatDel.obj" : $(SOURCE) $(DEP_CPP_PATDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

DEP_CPP_PATDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MPatMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\PatDel.h"\
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
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
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
	".\DLDDel.h"\
	".\DbDel.h"\
	".\SpLDel.h"\
	".\SLDDel.h"\
	".\SupDel.h"\
	".\SolDel.h"\
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
	".\CurDel.h"\
	".\NodDel.h"\
	

"$(INTDIR)\PatDel.obj" : $(SOURCE) $(DEP_CPP_PATDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PatDel.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SLDDel.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SolDel.cpp

!IF  "$(CFG)" == "DelMgr - Win32 Release"

DEP_CPP_SOLDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MSolMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\SolDel.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	".\PatDel.h"\
	".\CurDel.h"\
	".\NodDel.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	

"$(INTDIR)\SolDel.obj" : $(SOURCE) $(DEP_CPP_SOLDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

DEP_CPP_SOLDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MSolMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\SolDel.h"\
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
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
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
	".\DLDDel.h"\
	".\DbDel.h"\
	".\SpLDel.h"\
	".\SLDDel.h"\
	".\SupDel.h"\
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
	".\PatDel.h"\
	".\CurDel.h"\
	".\NodDel.h"\
	

"$(INTDIR)\SolDel.obj" : $(SOURCE) $(DEP_CPP_SOLDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SolDel.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpLDel.cpp

!IF  "$(CFG)" == "DelMgr - Win32 Release"

DEP_CPP_SPLDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	".\SpLDel.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	".\SLDDel.h"\
	".\SupDel.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	".\SolDel.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	".\PatDel.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	".\CurDel.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\NodDel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	

"$(INTDIR)\SpLDel.obj" : $(SOURCE) $(DEP_CPP_SPLDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

DEP_CPP_SPLDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	".\SpLDel.h"\
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
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
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
	".\DLDDel.h"\
	".\DbDel.h"\
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
	".\SLDDel.h"\
	".\SupDel.h"\
	".\SolDel.h"\
	".\PatDel.h"\
	".\CurDel.h"\
	".\NodDel.h"\
	

"$(INTDIR)\SpLDel.obj" : $(SOURCE) $(DEP_CPP_SPLDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpLDel.h

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SupDel.cpp

!IF  "$(CFG)" == "DelMgr - Win32 Release"

DEP_CPP_SUPDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Mi_LSupp.h"\
	".\SupDel.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Glb_Supp.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Mi_gangs.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\SolDel.h"\
	".\PatDel.h"\
	".\CurDel.h"\
	".\NodDel.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	

"$(INTDIR)\SupDel.obj" : $(SOURCE) $(DEP_CPP_SUPDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

DEP_CPP_SUPDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Mi_LSupp.h"\
	".\SupDel.h"\
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
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
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
	".\DLDDel.h"\
	".\DbDel.h"\
	".\SpLDel.h"\
	".\SLDDel.h"\
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
	".\SolDel.h"\
	".\PatDel.h"\
	".\CurDel.h"\
	".\NodDel.h"\
	

"$(INTDIR)\SupDel.obj" : $(SOURCE) $(DEP_CPP_SUPDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CurDel.cpp

!IF  "$(CFG)" == "DelMgr - Win32 Release"

DEP_CPP_CURDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MCurmgr.h"\
	".\CurDel.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	".\NodDel.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	

"$(INTDIR)\CurDel.obj" : $(SOURCE) $(DEP_CPP_CURDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

DEP_CPP_CURDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgrafrm.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\MCurmgr.h"\
	".\CurDel.h"\
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
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
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
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
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
	".\DLDDel.h"\
	".\DbDel.h"\
	".\SpLDel.h"\
	".\SLDDel.h"\
	".\SupDel.h"\
	".\SolDel.h"\
	".\PatDel.h"\
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
	".\NodDel.h"\
	

"$(INTDIR)\CurDel.obj" : $(SOURCE) $(DEP_CPP_CURDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SLDDel.cpp

!IF  "$(CFG)" == "DelMgr - Win32 Release"

DEP_CPP_SLDDE=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	".\SLDDel.h"\
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
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Ext_StaL.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\SupDel.h"\
	".\SolDel.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	".\PatDel.h"\
	".\CurDel.h"\
	".\NodDel.h"\
	{$(INCLUDE)}"\Mouse.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	

"$(INTDIR)\SLDDel.obj" : $(SOURCE) $(DEP_CPP_SLDDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

DEP_CPP_SLDDE=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	{$(INCLUDE)}"\SLDNod.h"\
	{$(INCLUDE)}"\SLDCur.h"\
	{$(INCLUDE)}"\SLDPat.h"\
	".\SLDDel.h"\
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
	{$(INCLUDE)}"\Drawbox.h"\
	".\..\APPLIC\StatCntl.h"\
	".\..\APPLIC\drstatus.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\MouseMgr.h"\
	{$(INCLUDE)}"\CreOpMgr.h"\
	{$(INCLUDE)}"\EditMgr.h"\
	{$(INCLUDE)}"\DelMgr.h"\
	{$(INCLUDE)}"\PostMgr.h"\
	{$(INCLUDE)}"\BoxWnd.h"\
	".\..\TOOLBOXS\DrawBox\VOprBar.h"\
	{$(INCLUDE)}"\Palette.h"\
	".\..\TOOLBOXS\DrawBox\Oldtool.h"\
	".\..\TOOLBOXS\IGenBox\BoxWnd.h"\
	{$(INCLUDE)}"\MainBar.h"\
	{$(INCLUDE)}"\GOpbox.h"\
	".\..\TOOLBOXS\IGenBox\COpBox.h"\
	".\..\TOOLBOXS\IGenBox\palette.h"\
	".\..\TOOLBOXS\IGenBox\Oldtool.h"\
	{$(INCLUDE)}"\GOpbar.h"\
	".\..\TOOLBOXS\IGenBox\COpBar.h"\
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
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	".\..\MouseMgr\DLdMouse.h"\
	".\..\MouseMgr\dbMouse.h"\
	".\..\MouseMgr\SpLMouse.h"\
	".\..\MouseMgr\SLDMouse.h"\
	".\..\MouseMgr\SupMouse.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
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
	".\DLDDel.h"\
	".\DbDel.h"\
	".\SpLDel.h"\
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
	{$(INCLUDE)}"\..\Mousemgr\SLDObj.h"\
	".\SupDel.h"\
	".\SolDel.h"\
	".\PatDel.h"\
	".\CurDel.h"\
	".\NodDel.h"\
	

"$(INTDIR)\SLDDel.obj" : $(SOURCE) $(DEP_CPP_SLDDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dmgr_d.def

!IF  "$(CFG)" == "DelMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DelMgr - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
