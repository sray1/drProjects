# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Omgr_d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Omgr_d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Omgr_d - Win32 Release" && "$(CFG)" != "Omgr_d - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Omgr_d32.mak" CFG="Omgr_d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Omgr_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Omgr_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Omgr_d - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "Omgr_d - Win32 Release"

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

ALL : "$(OUTDIR)\Omgr_d32.dll" "$(OUTDIR)\Omgr_d32.bsc"

CLEAN : 
	-@erase ".\Release\Omgr_d32.bsc"
	-@erase ".\Release\Newobjs.sbr"
	-@erase ".\Release\Objmgr.sbr"
	-@erase ".\Release\MsObjMgr.sbr"
	-@erase ".\Release\Omgrdll.sbr"
	-@erase ".\Release\Omgr_d32.dll"
	-@erase ".\Release\Omgrdll.obj"
	-@erase ".\Release\Newobjs.obj"
	-@erase ".\Release\Objmgr.obj"
	-@erase ".\Release\MsObjMgr.obj"
	-@erase ".\Release\Omgr_d32.lib"
	-@erase ".\Release\Omgr_d32.exp"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Omgr_d32.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Omgr_d32.bsc" 
BSC32_SBRS= \
	".\Release\Newobjs.sbr" \
	".\Release\Objmgr.sbr" \
	".\Release\MsObjMgr.sbr" \
	".\Release\Omgrdll.sbr"

"$(OUTDIR)\Omgr_d32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
LINK32_FLAGS=oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Omgr_d32.pdb" /map:"FULL" /machine:IX86\
 /def:".\Omgr_d.def" /out:"$(OUTDIR)/Omgr_d32.dll"\
 /implib:"$(OUTDIR)/Omgr_d32.lib" 
DEF_FILE= \
	".\Omgr_d.def"
LINK32_OBJS= \
	".\Release\Omgrdll.obj" \
	".\Release\Newobjs.obj" \
	".\Release\Objmgr.obj" \
	".\Release\MsObjMgr.obj"

"$(OUTDIR)\Omgr_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Omgr_d - Win32 Debug"

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

ALL : "$(OUTDIR)\Omgr_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase "..\applic\Debug\Omgr_d32.dll"
	-@erase ".\Debug\Omgrdll.obj"
	-@erase ".\Debug\MsObjMgr.obj"
	-@erase ".\Debug\Objmgr.obj"
	-@erase ".\Debug\Newobjs.obj"
	-@erase "..\applic\Debug\Omgr_d32.lib"
	-@erase "..\applic\Debug\Omgr_d32.exp"
	-@erase ".\Debug\Omgr_d32.pdb"
	-@erase ".\Debug\Omgr_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Omgr_d32.pch" /YX"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Omgr_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 Spec_D.lib Elem_D.lib Draw_D.lib Dr3D_D.lib oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib Draw_D32.lib OGen_D32.lib Mesh_D32.lib Elem_D32.lib Supp_D32.lib StaL_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:IX86 /out:"d:\drgraf4_0\applic\Debug\Omgr_d32.dll" /implib:"d:\drgraf4_0\applic\Debug\Omgr_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Dr3D_D32.lib Spec_D32.lib Draw_D32.lib OGen_D32.lib Mesh_D32.lib\
 Elem_D32.lib Supp_D32.lib StaL_D32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Omgr_d32.pdb" /map:"$(INTDIR)/Omgr_d32.map"\
 /debug /machine:IX86 /def:".\Omgr_d.def"\
 /out:"d:\drgraf4_0\applic\Debug\Omgr_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug\Omgr_d32.lib" 
DEF_FILE= \
	".\Omgr_d.def"
LINK32_OBJS= \
	".\Debug\Omgrdll.obj" \
	".\Debug\MsObjMgr.obj" \
	".\Debug\Objmgr.obj" \
	".\Debug\Newobjs.obj"

"$(OUTDIR)\Omgr_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Omgr_d - Win32 Release"
# Name "Omgr_d - Win32 Debug"

!IF  "$(CFG)" == "Omgr_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Omgr_d - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Objmgr.cpp

!IF  "$(CFG)" == "Omgr_d - Win32 Release"

DEP_CPP_OBJMG=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	".\Newobjs.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Ext_Draw.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Dr3dmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\..\GLOBHEAD\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
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
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	

"$(INTDIR)\Objmgr.obj" : $(SOURCE) $(DEP_CPP_OBJMG) "$(INTDIR)"

"$(INTDIR)\Objmgr.sbr" : $(SOURCE) $(DEP_CPP_OBJMG) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Omgr_d - Win32 Debug"

DEP_CPP_OBJMG=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	".\Newobjs.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Ext_Draw.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Dr3dmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\..\GLOBHEAD\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
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
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	

"$(INTDIR)\Objmgr.obj" : $(SOURCE) $(DEP_CPP_OBJMG) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Omgrdll.cpp
DEP_CPP_OMGRD=\
	".\Stdafx.h"\
	".\Omgrdll.h"\
	{$(INCLUDE)}"\Glb_Cur.h"\
	{$(INCLUDE)}"\Glb_Pat.h"\
	{$(INCLUDE)}"\Glb_Sol.h"\
	{$(INCLUDE)}"\Glb_elem.h"\
	{$(INCLUDE)}"\Glb_EInf.h"\
	{$(INCLUDE)}"\Glb_Spec.h"\
	{$(INCLUDE)}"\Glb_Draw.h"\
	".\..\GLOBHEAD\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_EInf.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	

!IF  "$(CFG)" == "Omgr_d - Win32 Release"


"$(INTDIR)\Omgrdll.obj" : $(SOURCE) $(DEP_CPP_OMGRD) "$(INTDIR)"

"$(INTDIR)\Omgrdll.sbr" : $(SOURCE) $(DEP_CPP_OMGRD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Omgr_d - Win32 Debug"


"$(INTDIR)\Omgrdll.obj" : $(SOURCE) $(DEP_CPP_OMGRD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Newobjs.cpp

!IF  "$(CFG)" == "Omgr_d - Win32 Release"

DEP_CPP_NEWOB=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Ext_Cur.h"\
	{$(INCLUDE)}"\Ext_Pat.h"\
	{$(INCLUDE)}"\Ext_Sol.h"\
	".\..\GLOBHEAD\Def_IGen.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\Drprof_P.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_EInf.h"\
	{$(INCLUDE)}"\Ext_EInf.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrMesh3D.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Dr_Qu_4.h"\
	{$(INCLUDE)}"\Dr_Qu_8.h"\
	{$(INCLUDE)}"\Dr_Qu_9.h"\
	{$(INCLUDE)}"\Dr_Qu_12.h"\
	{$(INCLUDE)}"\Dr_Qu_16.h"\
	{$(INCLUDE)}"\Dr_Tr_3.h"\
	{$(INCLUDE)}"\Dr_Tr_6.h"\
	{$(INCLUDE)}"\Dr_Tr_9.h"\
	{$(INCLUDE)}"\Dr_Tr_10.h"\
	{$(INCLUDE)}"\DrFE3D.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Ext_Draw.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drfrehnd.h"\
	{$(INCLUDE)}"\Drgrid.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	".\Newobjs.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	
NODEP_CPP_NEWOB=\
	".\Dr_Qu_10.h"\
	

"$(INTDIR)\Newobjs.obj" : $(SOURCE) $(DEP_CPP_NEWOB) "$(INTDIR)"

"$(INTDIR)\Newobjs.sbr" : $(SOURCE) $(DEP_CPP_NEWOB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Omgr_d - Win32 Debug"

DEP_CPP_NEWOB=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Ext_Cur.h"\
	{$(INCLUDE)}"\Ext_Pat.h"\
	{$(INCLUDE)}"\Ext_Sol.h"\
	".\..\GLOBHEAD\Def_IGen.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\Drprof_P.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_EInf.h"\
	{$(INCLUDE)}"\Ext_EInf.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\DrMesh1D.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrMesh3D.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrPipe.h"\
	{$(INCLUDE)}"\DrBeam.h"\
	{$(INCLUDE)}"\DrTruss.h"\
	{$(INCLUDE)}"\DrElbow.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Dr_Qu_4.h"\
	{$(INCLUDE)}"\Dr_Qu_8.h"\
	{$(INCLUDE)}"\Dr_Qu_9.h"\
	{$(INCLUDE)}"\Dr_Qu_12.h"\
	{$(INCLUDE)}"\Dr_Qu_16.h"\
	{$(INCLUDE)}"\Dr_Tr_3.h"\
	{$(INCLUDE)}"\Dr_Tr_6.h"\
	{$(INCLUDE)}"\Dr_Tr_9.h"\
	{$(INCLUDE)}"\Dr_Tr_10.h"\
	{$(INCLUDE)}"\DrFE3D.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Ext_Draw.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Drfrehnd.h"\
	{$(INCLUDE)}"\Drgrid.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	".\Newobjs.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	
NODEP_CPP_NEWOB=\
	".\Dr_Qu_10.h"\
	

"$(INTDIR)\Newobjs.obj" : $(SOURCE) $(DEP_CPP_NEWOB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Omgr_d.def

!IF  "$(CFG)" == "Omgr_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Omgr_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Objmgr.h

!IF  "$(CFG)" == "Omgr_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Omgr_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Newobjs.h

!IF  "$(CFG)" == "Omgr_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Omgr_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsObjMgr.h

!IF  "$(CFG)" == "Omgr_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Omgr_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsObjMgr.cpp

!IF  "$(CFG)" == "Omgr_d - Win32 Release"

DEP_CPP_MSOBJ=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	".\Newobjs.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_EInf.h"\
	{$(INCLUDE)}"\Ext_EInf.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Ext_Draw.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Dr3dmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Objmgr.h"\
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
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\..\GLOBHEAD\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	

"$(INTDIR)\MsObjMgr.obj" : $(SOURCE) $(DEP_CPP_MSOBJ) "$(INTDIR)"

"$(INTDIR)\MsObjMgr.sbr" : $(SOURCE) $(DEP_CPP_MSOBJ) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Omgr_d - Win32 Debug"

DEP_CPP_MSOBJ=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	".\Newobjs.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_EInf.h"\
	{$(INCLUDE)}"\Ext_EInf.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Ext_Draw.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Dr3dmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Objmgr.h"\
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
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\..\GLOBHEAD\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	

"$(INTDIR)\MsObjMgr.obj" : $(SOURCE) $(DEP_CPP_MSOBJ) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
