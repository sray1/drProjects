# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=MMgrSol - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MMgrSol - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MMgrSol - Win32 Release" && "$(CFG)" !=\
 "MMgrSol - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMgrSol.mak" CFG="MMgrSol - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MMgrSol - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MMgrSol - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "MMgrSol - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

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

ALL : "$(OUTDIR)\MMgrSol.dll"

CLEAN : 
	-@erase ".\Release\MMgrSol.dll"
	-@erase ".\Release\Dlg_lmat.obj"
	-@erase ".\Release\ms_lof32.obj"
	-@erase ".\Release\Dlg_srot.obj"
	-@erase ".\Release\ms_duct.obj"
	-@erase ".\Release\MSoldll.obj"
	-@erase ".\Release\ms_Sweep.obj"
	-@erase ".\Release\Dlg_SpnS.obj"
	-@erase ".\Release\Ms_xtru3.obj"
	-@erase ".\Release\ms_rota3.obj"
	-@erase ".\Release\Dlg_slof.obj"
	-@erase ".\Release\Dlg_scon.obj"
	-@erase ".\Release\MI_SSPN.obj"
	-@erase ".\Release\mi_gangs.obj"
	-@erase ".\Release\ms_duc3.obj"
	-@erase ".\Release\Ms_xtrud.obj"
	-@erase ".\Release\ms_Swee3.obj"
	-@erase ".\Release\Dlg_sswi.obj"
	-@erase ".\Release\Dlg_sxtr.obj"
	-@erase ".\Release\dlg_SolI.obj"
	-@erase ".\Release\Dlg_sduc.obj"
	-@erase ".\Release\ms_lof42.obj"
	-@erase ".\Release\MSolMgr.obj"
	-@erase ".\Release\ms_rotat.obj"
	-@erase ".\Release\MSolMgr.res"
	-@erase ".\Release\MMgrSol.lib"
	-@erase ".\Release\MMgrSol.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/MMgrSol.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MSolMgr.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrSol.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/MMgrSol.pdb" /machine:I386 /def:".\MSolMgr.def"\
 /out:"$(OUTDIR)/MMgrSol.dll" /implib:"$(OUTDIR)/MMgrSol.lib" 
DEF_FILE= \
	".\MSolMgr.def"
LINK32_OBJS= \
	".\Release\Dlg_lmat.obj" \
	".\Release\ms_lof32.obj" \
	".\Release\Dlg_srot.obj" \
	".\Release\ms_duct.obj" \
	".\Release\MSoldll.obj" \
	".\Release\ms_Sweep.obj" \
	".\Release\Dlg_SpnS.obj" \
	".\Release\Ms_xtru3.obj" \
	".\Release\ms_rota3.obj" \
	".\Release\Dlg_slof.obj" \
	".\Release\Dlg_scon.obj" \
	".\Release\MI_SSPN.obj" \
	".\Release\mi_gangs.obj" \
	".\Release\ms_duc3.obj" \
	".\Release\Ms_xtrud.obj" \
	".\Release\ms_Swee3.obj" \
	".\Release\Dlg_sswi.obj" \
	".\Release\Dlg_sxtr.obj" \
	".\Release\dlg_SolI.obj" \
	".\Release\Dlg_sduc.obj" \
	".\Release\ms_lof42.obj" \
	".\Release\MSolMgr.obj" \
	".\Release\ms_rotat.obj" \
	".\Release\MSolMgr.res"

"$(OUTDIR)\MMgrSol.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

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

ALL : "$(OUTDIR)\MSol_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\applic\Debug\MSol_D32.dll"
	-@erase ".\Debug\ms_lof42.obj"
	-@erase ".\Debug\ms_rotat.obj"
	-@erase ".\Debug\mi_gangs.obj"
	-@erase ".\Debug\ms_Swee3.obj"
	-@erase ".\Debug\ms_lof32.obj"
	-@erase ".\Debug\Dlg_SpnS.obj"
	-@erase ".\Debug\Ms_xtru3.obj"
	-@erase ".\Debug\Dlg_sxtr.obj"
	-@erase ".\Debug\ms_rota3.obj"
	-@erase ".\Debug\dlg_SolI.obj"
	-@erase ".\Debug\Dlg_slof.obj"
	-@erase ".\Debug\Dlg_scon.obj"
	-@erase ".\Debug\ms_duct.obj"
	-@erase ".\Debug\Dlg_sduc.obj"
	-@erase ".\Debug\MSoldll.obj"
	-@erase ".\Debug\Ms_xtrud.obj"
	-@erase ".\Debug\Dlg_lmat.obj"
	-@erase ".\Debug\MI_SSPN.obj"
	-@erase ".\Debug\Dlg_sswi.obj"
	-@erase ".\Debug\ms_duc3.obj"
	-@erase ".\Debug\MSolMgr.obj"
	-@erase ".\Debug\Dlg_srot.obj"
	-@erase ".\Debug\ms_Sweep.obj"
	-@erase ".\Debug\MSolMgr.res"
	-@erase "..\applic\Debug\MSol_D32.lib"
	-@erase "..\applic\Debug\MSol_D32.exp"
	-@erase ".\Debug\MSol_D32.pdb"
	-@erase ".\Debug\MSol_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/MMgrSol.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/MMgrSol.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MSolMgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrSol.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Elem_D32.lib OGen_D32.lib Dr3D_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug/MSol_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/MSol_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Draw_D32.lib Elem_D32.lib OGen_D32.lib\
 Dr3D_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib /nologo /subsystem:windows\
 /dll /incremental:no /pdb:"$(OUTDIR)/MSol_D32.pdb"\
 /map:"$(INTDIR)/MSol_D32.map" /debug /machine:I386 /def:".\MSolMgr.def"\
 /out:"d:\drgraf4_0\applic\Debug/MSol_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/MSol_D32.lib" 
DEF_FILE= \
	".\MSolMgr.def"
LINK32_OBJS= \
	".\Debug\ms_lof42.obj" \
	".\Debug\ms_rotat.obj" \
	".\Debug\mi_gangs.obj" \
	".\Debug\ms_Swee3.obj" \
	".\Debug\ms_lof32.obj" \
	".\Debug\Dlg_SpnS.obj" \
	".\Debug\Ms_xtru3.obj" \
	".\Debug\Dlg_sxtr.obj" \
	".\Debug\ms_rota3.obj" \
	".\Debug\dlg_SolI.obj" \
	".\Debug\Dlg_slof.obj" \
	".\Debug\Dlg_scon.obj" \
	".\Debug\ms_duct.obj" \
	".\Debug\Dlg_sduc.obj" \
	".\Debug\MSoldll.obj" \
	".\Debug\Ms_xtrud.obj" \
	".\Debug\Dlg_lmat.obj" \
	".\Debug\MI_SSPN.obj" \
	".\Debug\Dlg_sswi.obj" \
	".\Debug\ms_duc3.obj" \
	".\Debug\MSolMgr.obj" \
	".\Debug\Dlg_srot.obj" \
	".\Debug\ms_Sweep.obj" \
	".\Debug\MSolMgr.res"

"$(OUTDIR)\MSol_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MMgrSol - Win32 Release"
# Name "MMgrSol - Win32 Debug"

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MSolMgr.def

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSolMgr.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_scon.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_sduc.cpp
DEP_CPP_DLG_S=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\Dlg_sduc.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	

!IF  "$(CFG)" == "MMgrSol - Win32 Release"


"$(INTDIR)\Dlg_sduc.obj" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"


"$(INTDIR)\Dlg_sduc.obj" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_sduc.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_slof.cpp
DEP_CPP_DLG_SL=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\Dlg_slof.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	

"$(INTDIR)\Dlg_slof.obj" : $(SOURCE) $(DEP_CPP_DLG_SL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_slof.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_SpnS.cpp
DEP_CPP_DLG_SP=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Dlg_LTyp.h"\
	{$(INCLUDE)}"\Dlg_LALL.h"\
	{$(INCLUDE)}"\Dlg_LSyT.h"\
	{$(INCLUDE)}"\Dlg_LSym.h"\
	{$(INCLUDE)}"\Dlg_LSy3.h"\
	".\Dlg_SpnS.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
	

"$(INTDIR)\Dlg_SpnS.obj" : $(SOURCE) $(DEP_CPP_DLG_SP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_SpnS.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_srot.cpp
DEP_CPP_DLG_SR=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\Dlg_srot.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	

"$(INTDIR)\Dlg_srot.obj" : $(SOURCE) $(DEP_CPP_DLG_SR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_srot.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_sswi.cpp
DEP_CPP_DLG_SS=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\Dlg_sswi.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	

"$(INTDIR)\Dlg_sswi.obj" : $(SOURCE) $(DEP_CPP_DLG_SS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_sswi.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_sxtr.cpp
DEP_CPP_DLG_SX=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\Dlg_sxtr.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	

"$(INTDIR)\Dlg_sxtr.obj" : $(SOURCE) $(DEP_CPP_DLG_SX) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_sxtr.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\mi_gangs.cpp
DEP_CPP_MI_GA=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	".\MSolMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Pentahed.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\mi_gangs.obj" : $(SOURCE) $(DEP_CPP_MI_GA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_gangs.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ms_duc3.cpp
DEP_CPP_MS_DU=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MSolMgr.h"\
	".\Dlg_sduc.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Pa_duct.h"\
	".\Ms_duc3.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\ms_duc3.obj" : $(SOURCE) $(DEP_CPP_MS_DU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_duc3.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ms_duct.cpp
DEP_CPP_MS_DUC=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MSolMgr.h"\
	".\Dlg_sduc.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Pa_duct.h"\
	".\Ms_duct.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\ms_duct.obj" : $(SOURCE) $(DEP_CPP_MS_DUC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_duct.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ms_lof32.cpp
DEP_CPP_MS_LO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MSolMgr.h"\
	".\Dlg_slof.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Pa_loft2.h"\
	".\Ms_lof32.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\ms_lof32.obj" : $(SOURCE) $(DEP_CPP_MS_LO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_lof32.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ms_lof42.cpp
DEP_CPP_MS_LOF=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\Dlg_slof.h"\
	".\MSolMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Pa_loft2.h"\
	".\Ms_lof42.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\ms_lof42.obj" : $(SOURCE) $(DEP_CPP_MS_LOF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_lof42.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ms_rota3.cpp
DEP_CPP_MS_RO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MSolMgr.h"\
	".\Dlg_srot.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Pa_rotat.h"\
	".\Ms_rota3.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\ms_rota3.obj" : $(SOURCE) $(DEP_CPP_MS_RO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_rota3.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ms_rotat.cpp
DEP_CPP_MS_ROT=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MSolMgr.h"\
	".\Dlg_srot.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Pa_rotat.h"\
	".\Ms_rotat.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\ms_rotat.obj" : $(SOURCE) $(DEP_CPP_MS_ROT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_rotat.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ms_Swee3.cpp
DEP_CPP_MS_SW=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MSolMgr.h"\
	".\Dlg_sswi.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Pa_sweep.h"\
	".\Ms_Swee3.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\ms_Swee3.obj" : $(SOURCE) $(DEP_CPP_MS_SW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_Swee3.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ms_Sweep.cpp
DEP_CPP_MS_SWE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MSolMgr.h"\
	".\Dlg_sswi.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Pa_sweep.h"\
	".\Ms_Sweep.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\ms_Sweep.obj" : $(SOURCE) $(DEP_CPP_MS_SWE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_Sweep.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_xtru3.cpp
DEP_CPP_MS_XT=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MSolMgr.h"\
	".\Dlg_sxtr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Pa_xtrud.h"\
	".\Ms_xtru3.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Ms_xtru3.obj" : $(SOURCE) $(DEP_CPP_MS_XT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_xtru3.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_xtrud.cpp
DEP_CPP_MS_XTR=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MSolMgr.h"\
	".\Dlg_sxtr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Pa_xtrud.h"\
	".\Ms_xtrud.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Ms_xtrud.obj" : $(SOURCE) $(DEP_CPP_MS_XTR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ms_xtrud.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSoldll.cpp
DEP_CPP_MSOLD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MSoldll.h"\
	

"$(INTDIR)\MSoldll.obj" : $(SOURCE) $(DEP_CPP_MSOLD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSoldll.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSolMgr.cpp
DEP_CPP_MSOLM=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Glb_Cur.h"\
	{$(INCLUDE)}"\Glb_Pat.h"\
	{$(INCLUDE)}"\Glb_Sol.h"\
	{$(INCLUDE)}"\Glb_elem.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	".\Dlg_scon.h"\
	".\Dlg_sxtr.h"\
	".\Dlg_srot.h"\
	".\Dlg_slof.h"\
	".\Dlg_sswi.h"\
	".\Dlg_sduc.h"\
	".\Dlg_SpnS.h"\
	".\MSoldll.h"\
	".\MSolMgr.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
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
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\MSolMgr.obj" : $(SOURCE) $(DEP_CPP_MSOLM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_scon.cpp
DEP_CPP_DLG_SC=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\Dlg_scon.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\Dlg_scon.obj" : $(SOURCE) $(DEP_CPP_DLG_SC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSolMgr.rc

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

DEP_RSC_MSOLMG=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	".\..\Applic\Res\Curvebit.bmp"\
	".\..\Applic\Res\Ico_pipe.ico"\
	".\MDlgrsrc.hm"\
	

"$(INTDIR)\MSolMgr.res" : $(SOURCE) $(DEP_RSC_MSOLMG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

DEP_RSC_MSOLMG=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	".\..\Applic\Res\Curvebit.bmp"\
	".\..\Applic\Res\Ico_pipe.ico"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MNodRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\MDlgrsrc.hm"\
	

"$(INTDIR)\MSolMgr.res" : $(SOURCE) $(DEP_RSC_MSOLMG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_lmat.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_lmat.cpp
DEP_CPP_DLG_L=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	".\Dlg_lmat.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\Dlg_lmat.obj" : $(SOURCE) $(DEP_CPP_DLG_L) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_SolI.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_SolI.cpp
DEP_CPP_DLG_SO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\dlg_SolI.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	

"$(INTDIR)\dlg_SolI.obj" : $(SOURCE) $(DEP_CPP_DLG_SO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_SSPN.h

!IF  "$(CFG)" == "MMgrSol - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSol - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_SSPN.cpp
DEP_CPP_MI_SS=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	".\MSolMgr.h"\
	".\Mi_gangs.h"\
	".\Dlg_SpnS.h"\
	".\Mi_SSPN.h"\
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
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Mi_PSPN.h"\
	{$(INCLUDE)}"\Mi_CSPN.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	

"$(INTDIR)\MI_SSPN.obj" : $(SOURCE) $(DEP_CPP_MI_SS) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
