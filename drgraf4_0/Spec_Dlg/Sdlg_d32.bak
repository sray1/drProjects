# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Sdlg_d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Sdlg_d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Sdlg_d - Win32 Release" && "$(CFG)" != "Sdlg_d - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Sdlg_d32.mak" CFG="Sdlg_d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Sdlg_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Sdlg_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Sdlg_d - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"

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

ALL : "$(OUTDIR)\Sdlg_d32.dll" "$(OUTDIR)\Sdlg_d32.bsc"

CLEAN : 
	-@erase ".\Release\Sdlg_d32.bsc"
	-@erase ".\Release\Dlg_layr.sbr"
	-@erase ".\Release\Dlg_sfac.sbr"
	-@erase ".\Release\Dlg_unit.sbr"
	-@erase ".\Release\Dlg_prec.sbr"
	-@erase ".\Release\Dlg_pen.sbr"
	-@erase ".\Release\Dlgobj3d.sbr"
	-@erase ".\Release\Sdlgdll.sbr"
	-@erase ".\Release\Dlg_HNet.sbr"
	-@erase ".\Release\Dlgpatch.sbr"
	-@erase ".\Release\Sdlgmgr.sbr"
	-@erase ".\Release\Sdlg_d32.dll"
	-@erase ".\Release\Sdlgmgr.obj"
	-@erase ".\Release\Dlg_layr.obj"
	-@erase ".\Release\Dlg_sfac.obj"
	-@erase ".\Release\Dlg_unit.obj"
	-@erase ".\Release\Dlg_prec.obj"
	-@erase ".\Release\Dlg_pen.obj"
	-@erase ".\Release\Dlgobj3d.obj"
	-@erase ".\Release\Sdlgdll.obj"
	-@erase ".\Release\Dlg_HNet.obj"
	-@erase ".\Release\Dlgpatch.obj"
	-@erase ".\Release\Spec_dlg.res"
	-@erase ".\Release\Sdlg_d32.lib"
	-@erase ".\Release\Sdlg_d32.exp"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Sdlg_d32.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Spec_dlg.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Sdlg_d32.bsc" 
BSC32_SBRS= \
	".\Release\Dlg_layr.sbr" \
	".\Release\Dlg_sfac.sbr" \
	".\Release\Dlg_unit.sbr" \
	".\Release\Dlg_prec.sbr" \
	".\Release\Dlg_pen.sbr" \
	".\Release\Dlgobj3d.sbr" \
	".\Release\Sdlgdll.sbr" \
	".\Release\Dlg_HNet.sbr" \
	".\Release\Dlgpatch.sbr" \
	".\Release\Sdlgmgr.sbr"

"$(OUTDIR)\Sdlg_d32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Sdlg_d32.pdb" /map:"FULL" /machine:IX86 /def:".\Sdlg_d.def"\
 /out:"$(OUTDIR)/Sdlg_d32.dll" /implib:"$(OUTDIR)/Sdlg_d32.lib" 
DEF_FILE= \
	".\Sdlg_d.def"
LINK32_OBJS= \
	".\Release\Sdlgmgr.obj" \
	".\Release\Dlg_layr.obj" \
	".\Release\Dlg_sfac.obj" \
	".\Release\Dlg_unit.obj" \
	".\Release\Dlg_prec.obj" \
	".\Release\Dlg_pen.obj" \
	".\Release\Dlgobj3d.obj" \
	".\Release\Sdlgdll.obj" \
	".\Release\Dlg_HNet.obj" \
	".\Release\Dlgpatch.obj" \
	".\Release\Spec_dlg.res"

"$(OUTDIR)\Sdlg_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"

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

ALL : "$(OUTDIR)\Sdlg_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase "..\applic\Debug\Sdlg_d32.dll"
	-@erase ".\Debug\Dlg_prec.obj"
	-@erase ".\Debug\Sdlgmgr.obj"
	-@erase ".\Debug\Dlgobj3d.obj"
	-@erase ".\Debug\Sdlgdll.obj"
	-@erase ".\Debug\Dlg_HNet.obj"
	-@erase ".\Debug\Dlgpatch.obj"
	-@erase ".\Debug\Dlg_pen.obj"
	-@erase ".\Debug\Dlg_layr.obj"
	-@erase ".\Debug\Dlg_sfac.obj"
	-@erase ".\Debug\Dlg_unit.obj"
	-@erase ".\Debug\Spec_dlg.res"
	-@erase "..\applic\Debug\Sdlg_d32.ilk"
	-@erase "..\applic\Debug\Sdlg_d32.lib"
	-@erase "..\applic\Debug\Sdlg_d32.exp"
	-@erase ".\Debug\Sdlg_d32.pdb"
	-@erase ".\Debug\Sdlg_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Sdlg_d32.pch" /YX"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Spec_dlg.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Sdlg_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 OMgr_D.lib oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Spec_D32.lib OMgr_D32.lib Dr3D_D32.lib Elem_D32.lib /nologo /subsystem:windows /dll /map /debug /machine:IX86 /out:"d:\drgraf4_0\applic\Debug\Sdlg_d32.dll" /implib:"d:\drgraf4_0\applic\Debug\Sdlg_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Spec_D32.lib OMgr_D32.lib Dr3D_D32.lib Elem_D32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/Sdlg_d32.pdb"\
 /map:"$(INTDIR)/Sdlg_d32.map" /debug /machine:IX86 /def:".\Sdlg_d.def"\
 /out:"d:\drgraf4_0\applic\Debug\Sdlg_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug\Sdlg_d32.lib" 
DEF_FILE= \
	".\Sdlg_d.def"
LINK32_OBJS= \
	".\Debug\Dlg_prec.obj" \
	".\Debug\Sdlgmgr.obj" \
	".\Debug\Dlgobj3d.obj" \
	".\Debug\Sdlgdll.obj" \
	".\Debug\Dlg_HNet.obj" \
	".\Debug\Dlgpatch.obj" \
	".\Debug\Dlg_pen.obj" \
	".\Debug\Dlg_layr.obj" \
	".\Debug\Dlg_sfac.obj" \
	".\Debug\Dlg_unit.obj" \
	".\Debug\Spec_dlg.res"

"$(OUTDIR)\Sdlg_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Sdlg_d - Win32 Release"
# Name "Sdlg_d - Win32 Debug"

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Dlg_layr.cpp
DEP_CPP_DLG_L=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Dlg_layr.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
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
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"


"$(INTDIR)\Dlg_layr.obj" : $(SOURCE) $(DEP_CPP_DLG_L) "$(INTDIR)"

"$(INTDIR)\Dlg_layr.sbr" : $(SOURCE) $(DEP_CPP_DLG_L) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"


"$(INTDIR)\Dlg_layr.obj" : $(SOURCE) $(DEP_CPP_DLG_L) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_pen.cpp
DEP_CPP_DLG_P=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	".\dlg_pen.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
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
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"


"$(INTDIR)\Dlg_pen.obj" : $(SOURCE) $(DEP_CPP_DLG_P) "$(INTDIR)"

"$(INTDIR)\Dlg_pen.sbr" : $(SOURCE) $(DEP_CPP_DLG_P) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"


"$(INTDIR)\Dlg_pen.obj" : $(SOURCE) $(DEP_CPP_DLG_P) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_prec.cpp
DEP_CPP_DLG_PR=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Precison.h"\
	".\Dlg_prec.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
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
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"


"$(INTDIR)\Dlg_prec.obj" : $(SOURCE) $(DEP_CPP_DLG_PR) "$(INTDIR)"

"$(INTDIR)\Dlg_prec.sbr" : $(SOURCE) $(DEP_CPP_DLG_PR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"


"$(INTDIR)\Dlg_prec.obj" : $(SOURCE) $(DEP_CPP_DLG_PR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_sfac.cpp
DEP_CPP_DLG_S=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	".\Dlg_sfac.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
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
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Unit.h"\
	

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"


"$(INTDIR)\Dlg_sfac.obj" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"

"$(INTDIR)\Dlg_sfac.sbr" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"


"$(INTDIR)\Dlg_sfac.obj" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_unit.cpp
DEP_CPP_DLG_U=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	".\Dlg_unit.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
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
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"


"$(INTDIR)\Dlg_unit.obj" : $(SOURCE) $(DEP_CPP_DLG_U) "$(INTDIR)"

"$(INTDIR)\Dlg_unit.sbr" : $(SOURCE) $(DEP_CPP_DLG_U) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"


"$(INTDIR)\Dlg_unit.obj" : $(SOURCE) $(DEP_CPP_DLG_U) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sdlgdll.cpp
DEP_CPP_SDLGD=\
	".\Stdafx.h"\
	".\Sdlgdll.h"\
	

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"


"$(INTDIR)\Sdlgdll.obj" : $(SOURCE) $(DEP_CPP_SDLGD) "$(INTDIR)"

"$(INTDIR)\Sdlgdll.sbr" : $(SOURCE) $(DEP_CPP_SDLGD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"


"$(INTDIR)\Sdlgdll.obj" : $(SOURCE) $(DEP_CPP_SDLGD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Spec_dlg.rc
DEP_RSC_SPEC_=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	

"$(INTDIR)\Spec_dlg.res" : $(SOURCE) $(DEP_RSC_SPEC_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sdlgmgr.cpp
DEP_CPP_SDLGM=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Dlg_HNet.h"\
	".\Dlg_layr.h"\
	".\dlg_pen.h"\
	".\Dlg_sfac.h"\
	".\Dlg_prec.h"\
	".\Dlg_unit.h"\
	".\Dlgobj3d.h"\
	".\Dlgpatch.h"\
	".\Sdlgdll.h"\
	".\Sdlgmgr.h"\
	

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"


"$(INTDIR)\Sdlgmgr.obj" : $(SOURCE) $(DEP_CPP_SDLGM) "$(INTDIR)"

"$(INTDIR)\Sdlgmgr.sbr" : $(SOURCE) $(DEP_CPP_SDLGM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"


"$(INTDIR)\Sdlgmgr.obj" : $(SOURCE) $(DEP_CPP_SDLGM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlgobj3d.cpp
DEP_CPP_DLGOB=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	".\Dlgobj3d.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
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
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"


"$(INTDIR)\Dlgobj3d.obj" : $(SOURCE) $(DEP_CPP_DLGOB) "$(INTDIR)"

"$(INTDIR)\Dlgobj3d.sbr" : $(SOURCE) $(DEP_CPP_DLGOB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"


"$(INTDIR)\Dlgobj3d.obj" : $(SOURCE) $(DEP_CPP_DLGOB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlgpatch.cpp
DEP_CPP_DLGPA=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	".\Dlgpatch.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
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
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"


"$(INTDIR)\Dlgpatch.obj" : $(SOURCE) $(DEP_CPP_DLGPA) "$(INTDIR)"

"$(INTDIR)\Dlgpatch.sbr" : $(SOURCE) $(DEP_CPP_DLGPA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"


"$(INTDIR)\Dlgpatch.obj" : $(SOURCE) $(DEP_CPP_DLGPA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Sdlg_d.def

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_HNet.cpp
DEP_CPP_DLG_H=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Lims.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	".\Dlg_HNet.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
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
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	

!IF  "$(CFG)" == "Sdlg_d - Win32 Release"


"$(INTDIR)\Dlg_HNet.obj" : $(SOURCE) $(DEP_CPP_DLG_H) "$(INTDIR)"

"$(INTDIR)\Dlg_HNet.sbr" : $(SOURCE) $(DEP_CPP_DLG_H) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Sdlg_d - Win32 Debug"


"$(INTDIR)\Dlg_HNet.obj" : $(SOURCE) $(DEP_CPP_DLG_H) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
