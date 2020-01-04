# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Ddlg_d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Ddlg_d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Ddlg_d - Win32 Release" && "$(CFG)" != "Ddlg_d - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ddlg_d32.mak" CFG="Ddlg_d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ddlg_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Ddlg_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Ddlg_d - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "Ddlg_d - Win32 Release"

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

ALL : "$(OUTDIR)\Ddlg_d32.dll" "$(OUTDIR)\Ddlg_d32.bsc"

CLEAN : 
	-@erase ".\Release\Ddlg_d32.bsc"
	-@erase ".\Release\Ddlgmgr.sbr"
	-@erase ".\Release\Dlg_grid.sbr"
	-@erase ".\Release\Ddlgdll.sbr"
	-@erase ".\Release\Dlg_ilab.sbr"
	-@erase ".\Release\Dlg_elab.sbr"
	-@erase ".\Release\Ddlg_d32.dll"
	-@erase ".\Release\Dlg_elab.obj"
	-@erase ".\Release\Ddlgmgr.obj"
	-@erase ".\Release\Dlg_grid.obj"
	-@erase ".\Release\Ddlgdll.obj"
	-@erase ".\Release\Dlg_ilab.obj"
	-@erase ".\Release\Ddlgrsrc.res"
	-@erase ".\Release\Ddlg_d32.lib"
	-@erase ".\Release\Ddlg_d32.exp"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Ddlg_d32.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Ddlgrsrc.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ddlg_d32.bsc" 
BSC32_SBRS= \
	".\Release\Ddlgmgr.sbr" \
	".\Release\Dlg_grid.sbr" \
	".\Release\Ddlgdll.sbr" \
	".\Release\Dlg_ilab.sbr" \
	".\Release\Dlg_elab.sbr"

"$(OUTDIR)\Ddlg_d32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# SUBTRACT LINK32 /incremental:yes
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Ddlg_d32.pdb" /map:"FULL" /machine:IX86 /def:".\Ddlg_d.def"\
 /out:"$(OUTDIR)/Ddlg_d32.dll" /implib:"$(OUTDIR)/Ddlg_d32.lib" 
DEF_FILE= \
	".\Ddlg_d.def"
LINK32_OBJS= \
	".\Release\Dlg_elab.obj" \
	".\Release\Ddlgmgr.obj" \
	".\Release\Dlg_grid.obj" \
	".\Release\Ddlgdll.obj" \
	".\Release\Dlg_ilab.obj" \
	".\Release\Ddlgrsrc.res"

"$(OUTDIR)\Ddlg_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Ddlg_d - Win32 Debug"

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

ALL : "$(OUTDIR)\Ddlg_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase "..\applic\Debug\Ddlg_d32.dll"
	-@erase ".\Debug\Dlg_grid.obj"
	-@erase ".\Debug\Dlg_elab.obj"
	-@erase ".\Debug\Dlg_ilab.obj"
	-@erase ".\Debug\Ddlgdll.obj"
	-@erase ".\Debug\Ddlgmgr.obj"
	-@erase ".\Debug\Ddlgrsrc.res"
	-@erase "..\applic\Debug\Ddlg_d32.lib"
	-@erase "..\applic\Debug\Ddlg_d32.exp"
	-@erase ".\Debug\Ddlg_d32.pdb"
	-@erase ".\Debug\Ddlg_d32..map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Ddlg_d32.pch" /YX"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Ddlgrsrc.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ddlg_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 Spec_D.lib OMgr_D.lib draw_D.lib oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 OGen_D32.lib Draw_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib OMgr_D32.lib Dr3D_D32.lib /nologo /subsystem:windows /dll /incremental:no /map:"Debug/Ddlg_d32..map" /debug /machine:IX86 /out:"d:\drgraf4_0\applic\Debug\Ddlg_d32.dll" /implib:"d:\drgraf4_0\applic\Debug\Ddlg_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OGen_D32.lib Draw_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib\
 OMgr_D32.lib Dr3D_D32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Ddlg_d32.pdb" /map:"$(INTDIR)/Ddlg_d32..map" /debug\
 /machine:IX86 /def:".\Ddlg_d.def" /out:"d:\drgraf4_0\applic\Debug\Ddlg_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug\Ddlg_d32.lib" 
DEF_FILE= \
	".\Ddlg_d.def"
LINK32_OBJS= \
	".\Debug\Dlg_grid.obj" \
	".\Debug\Dlg_elab.obj" \
	".\Debug\Dlg_ilab.obj" \
	".\Debug\Ddlgdll.obj" \
	".\Debug\Ddlgmgr.obj" \
	".\Debug\Ddlgrsrc.res"

"$(OUTDIR)\Ddlg_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Ddlg_d - Win32 Release"
# Name "Ddlg_d - Win32 Debug"

!IF  "$(CFG)" == "Ddlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ddlg_d - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Dlg_elab.cpp
DEP_CPP_DLG_E=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Drfont.h"\
	".\Dlg_elab.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	".\Ddlgrsrc.h"\
	

!IF  "$(CFG)" == "Ddlg_d - Win32 Release"


"$(INTDIR)\Dlg_elab.obj" : $(SOURCE) $(DEP_CPP_DLG_E) "$(INTDIR)"

"$(INTDIR)\Dlg_elab.sbr" : $(SOURCE) $(DEP_CPP_DLG_E) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Ddlg_d - Win32 Debug"


"$(INTDIR)\Dlg_elab.obj" : $(SOURCE) $(DEP_CPP_DLG_E) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_ilab.cpp
DEP_CPP_DLG_I=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	".\Dlg_ilab.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	".\Ddlgrsrc.h"\
	

!IF  "$(CFG)" == "Ddlg_d - Win32 Release"


"$(INTDIR)\Dlg_ilab.obj" : $(SOURCE) $(DEP_CPP_DLG_I) "$(INTDIR)"

"$(INTDIR)\Dlg_ilab.sbr" : $(SOURCE) $(DEP_CPP_DLG_I) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Ddlg_d - Win32 Debug"


"$(INTDIR)\Dlg_ilab.obj" : $(SOURCE) $(DEP_CPP_DLG_I) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ddlgdll.cpp
DEP_CPP_DDLGD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Ddlgdll.h"\
	

!IF  "$(CFG)" == "Ddlg_d - Win32 Release"


"$(INTDIR)\Ddlgdll.obj" : $(SOURCE) $(DEP_CPP_DDLGD) "$(INTDIR)"

"$(INTDIR)\Ddlgdll.sbr" : $(SOURCE) $(DEP_CPP_DDLGD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Ddlg_d - Win32 Debug"


"$(INTDIR)\Ddlgdll.obj" : $(SOURCE) $(DEP_CPP_DDLGD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ddlgmgr.cpp
DEP_CPP_DDLGM=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\Dlg_ilab.h"\
	".\Dlg_elab.h"\
	".\Dlg_grid.h"\
	".\Ddlgdll.h"\
	".\Ddlgrsrc.h"\
	".\Ddlgmgr.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
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
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drgrid.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	

!IF  "$(CFG)" == "Ddlg_d - Win32 Release"


"$(INTDIR)\Ddlgmgr.obj" : $(SOURCE) $(DEP_CPP_DDLGM) "$(INTDIR)"

"$(INTDIR)\Ddlgmgr.sbr" : $(SOURCE) $(DEP_CPP_DDLGM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Ddlg_d - Win32 Debug"


"$(INTDIR)\Ddlgmgr.obj" : $(SOURCE) $(DEP_CPP_DDLGM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ddlgrsrc.rc

!IF  "$(CFG)" == "Ddlg_d - Win32 Release"


"$(INTDIR)\Ddlgrsrc.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ddlg_d - Win32 Debug"

DEP_RSC_DDLGR=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	

"$(INTDIR)\Ddlgrsrc.res" : $(SOURCE) $(DEP_RSC_DDLGR) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_grid.cpp
DEP_CPP_DLG_G=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	".\Dlg_grid.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	".\Ddlgrsrc.h"\
	{$(INCLUDE)}"\Drgrid.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	

!IF  "$(CFG)" == "Ddlg_d - Win32 Release"


"$(INTDIR)\Dlg_grid.obj" : $(SOURCE) $(DEP_CPP_DLG_G) "$(INTDIR)"

"$(INTDIR)\Dlg_grid.sbr" : $(SOURCE) $(DEP_CPP_DLG_G) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Ddlg_d - Win32 Debug"


"$(INTDIR)\Dlg_grid.obj" : $(SOURCE) $(DEP_CPP_DLG_G) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ddlg_d.def

!IF  "$(CFG)" == "Ddlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Ddlg_d - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
