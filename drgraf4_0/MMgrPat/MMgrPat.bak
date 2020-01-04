# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=MMgrPat - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MMgrPat - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MMgrPat - Win32 Release" && "$(CFG)" !=\
 "MMgrPat - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMgrPat.mak" CFG="MMgrPat - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MMgrPat - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MMgrPat - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "MMgrPat - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

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

ALL : "$(OUTDIR)\MMgrPat.dll"

CLEAN : 
	-@erase ".\Release\MMgrPat.dll"
	-@erase ".\Release\Pa_CoonP.obj"
	-@erase ".\Release\Pa_sweep.obj"
	-@erase ".\Release\Dlg_SpnP.obj"
	-@erase ".\Release\Dlg_rotp.obj"
	-@erase ".\Release\Pa_duct.obj"
	-@erase ".\Release\dlg_PatI.obj"
	-@erase ".\Release\Mp_xtrud.obj"
	-@erase ".\Release\MI_PSPN.obj"
	-@erase ".\Release\Pa_rotat.obj"
	-@erase ".\Release\Mi_gangp.obj"
	-@erase ".\Release\Pa_loft4.obj"
	-@erase ".\Release\Mp_duct.obj"
	-@erase ".\Release\Dlg_rend.obj"
	-@erase ".\Release\MPatMgr.obj"
	-@erase ".\Release\Mp_loft2.obj"
	-@erase ".\Release\Mp_rotat.obj"
	-@erase ".\Release\Mp_CooP3.obj"
	-@erase ".\Release\Dlg_swip.obj"
	-@erase ".\Release\Dlg_duct.obj"
	-@erase ".\Release\Dlg_PatT.obj"
	-@erase ".\Release\dlg_coop.obj"
	-@erase ".\Release\Pa_loft2.obj"
	-@erase ".\Release\Pa_xtrud.obj"
	-@erase ".\Release\MPatdll.obj"
	-@erase ".\Release\Dlg_loft.obj"
	-@erase ".\Release\Mp_CoonP.obj"
	-@erase ".\Release\Dlg_Cop3.obj"
	-@erase ".\Release\Dlg_CooT.obj"
	-@erase ".\Release\Dlg_xtrd.obj"
	-@erase ".\Release\Pa_CooP3.obj"
	-@erase ".\Release\Mp_sweep.obj"
	-@erase ".\Release\Dlg_pcon.obj"
	-@erase ".\Release\MPatMgr.res"
	-@erase ".\Release\MMgrPat.lib"
	-@erase ".\Release\MMgrPat.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/MMgrPat.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MPatMgr.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrPat.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/MMgrPat.pdb" /machine:I386 /def:".\MPatMgr.def"\
 /out:"$(OUTDIR)/MMgrPat.dll" /implib:"$(OUTDIR)/MMgrPat.lib" 
DEF_FILE= \
	".\MPatMgr.def"
LINK32_OBJS= \
	".\Release\Pa_CoonP.obj" \
	".\Release\Pa_sweep.obj" \
	".\Release\Dlg_SpnP.obj" \
	".\Release\Dlg_rotp.obj" \
	".\Release\Pa_duct.obj" \
	".\Release\dlg_PatI.obj" \
	".\Release\Mp_xtrud.obj" \
	".\Release\MI_PSPN.obj" \
	".\Release\Pa_rotat.obj" \
	".\Release\Mi_gangp.obj" \
	".\Release\Pa_loft4.obj" \
	".\Release\Mp_duct.obj" \
	".\Release\Dlg_rend.obj" \
	".\Release\MPatMgr.obj" \
	".\Release\Mp_loft2.obj" \
	".\Release\Mp_rotat.obj" \
	".\Release\Mp_CooP3.obj" \
	".\Release\Dlg_swip.obj" \
	".\Release\Dlg_duct.obj" \
	".\Release\Dlg_PatT.obj" \
	".\Release\dlg_coop.obj" \
	".\Release\Pa_loft2.obj" \
	".\Release\Pa_xtrud.obj" \
	".\Release\MPatdll.obj" \
	".\Release\Dlg_loft.obj" \
	".\Release\Mp_CoonP.obj" \
	".\Release\Dlg_Cop3.obj" \
	".\Release\Dlg_CooT.obj" \
	".\Release\Dlg_xtrd.obj" \
	".\Release\Pa_CooP3.obj" \
	".\Release\Mp_sweep.obj" \
	".\Release\Dlg_pcon.obj" \
	".\Release\MPatMgr.res"

"$(OUTDIR)\MMgrPat.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

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

ALL : "$(OUTDIR)\MPat_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\applic\Debug\MPat_D32.dll"
	-@erase ".\Debug\Mp_CooP3.obj"
	-@erase ".\Debug\Dlg_swip.obj"
	-@erase ".\Debug\Dlg_duct.obj"
	-@erase ".\Debug\Dlg_PatT.obj"
	-@erase ".\Debug\Pa_duct.obj"
	-@erase ".\Debug\dlg_coop.obj"
	-@erase ".\Debug\MI_PSPN.obj"
	-@erase ".\Debug\Pa_loft4.obj"
	-@erase ".\Debug\Pa_xtrud.obj"
	-@erase ".\Debug\Dlg_loft.obj"
	-@erase ".\Debug\Mp_CoonP.obj"
	-@erase ".\Debug\Dlg_Cop3.obj"
	-@erase ".\Debug\Dlg_CooT.obj"
	-@erase ".\Debug\Dlg_xtrd.obj"
	-@erase ".\Debug\Pa_CooP3.obj"
	-@erase ".\Debug\Mp_sweep.obj"
	-@erase ".\Debug\Dlg_pcon.obj"
	-@erase ".\Debug\Pa_CoonP.obj"
	-@erase ".\Debug\Pa_sweep.obj"
	-@erase ".\Debug\Dlg_SpnP.obj"
	-@erase ".\Debug\Mp_rotat.obj"
	-@erase ".\Debug\Dlg_rotp.obj"
	-@erase ".\Debug\MPatMgr.obj"
	-@erase ".\Debug\dlg_PatI.obj"
	-@erase ".\Debug\Pa_loft2.obj"
	-@erase ".\Debug\Pa_rotat.obj"
	-@erase ".\Debug\Mi_gangp.obj"
	-@erase ".\Debug\MPatdll.obj"
	-@erase ".\Debug\Dlg_rend.obj"
	-@erase ".\Debug\Mp_duct.obj"
	-@erase ".\Debug\Mp_loft2.obj"
	-@erase ".\Debug\Mp_xtrud.obj"
	-@erase ".\Debug\MPatMgr.res"
	-@erase "..\applic\Debug\MPat_D32.lib"
	-@erase "..\applic\Debug\MPat_D32.exp"
	-@erase ".\Debug\MPat_D32.pdb"
	-@erase ".\Debug\MPat_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/MMgrPat.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/MMgrPat.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MPatMgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrPat.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib OGen_D32.lib Dr3D_D32.lib MNod_D32.lib MCur_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug/MPat_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/MPat_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Draw_D32.lib Mesh_D32.lib Elem_D32.lib\
 OGen_D32.lib Dr3D_D32.lib MNod_D32.lib MCur_D32.lib /nologo /subsystem:windows\
 /dll /incremental:no /pdb:"$(OUTDIR)/MPat_D32.pdb"\
 /map:"$(INTDIR)/MPat_D32.map" /debug /machine:I386 /def:".\MPatMgr.def"\
 /out:"d:\drgraf4_0\applic\Debug/MPat_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/MPat_D32.lib" 
DEF_FILE= \
	".\MPatMgr.def"
LINK32_OBJS= \
	".\Debug\Mp_CooP3.obj" \
	".\Debug\Dlg_swip.obj" \
	".\Debug\Dlg_duct.obj" \
	".\Debug\Dlg_PatT.obj" \
	".\Debug\Pa_duct.obj" \
	".\Debug\dlg_coop.obj" \
	".\Debug\MI_PSPN.obj" \
	".\Debug\Pa_loft4.obj" \
	".\Debug\Pa_xtrud.obj" \
	".\Debug\Dlg_loft.obj" \
	".\Debug\Mp_CoonP.obj" \
	".\Debug\Dlg_Cop3.obj" \
	".\Debug\Dlg_CooT.obj" \
	".\Debug\Dlg_xtrd.obj" \
	".\Debug\Pa_CooP3.obj" \
	".\Debug\Mp_sweep.obj" \
	".\Debug\Dlg_pcon.obj" \
	".\Debug\Pa_CoonP.obj" \
	".\Debug\Pa_sweep.obj" \
	".\Debug\Dlg_SpnP.obj" \
	".\Debug\Mp_rotat.obj" \
	".\Debug\Dlg_rotp.obj" \
	".\Debug\MPatMgr.obj" \
	".\Debug\dlg_PatI.obj" \
	".\Debug\Pa_loft2.obj" \
	".\Debug\Pa_rotat.obj" \
	".\Debug\Mi_gangp.obj" \
	".\Debug\MPatdll.obj" \
	".\Debug\Dlg_rend.obj" \
	".\Debug\Mp_duct.obj" \
	".\Debug\Mp_loft2.obj" \
	".\Debug\Mp_xtrud.obj" \
	".\Debug\MPatMgr.res"

"$(OUTDIR)\MPat_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MMgrPat - Win32 Release"
# Name "MMgrPat - Win32 Debug"

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MPatRsrc.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_PatT.cpp
DEP_CPP_DLG_P=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	".\MPatRsrc.h"\
	".\Dlg_PatT.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	

!IF  "$(CFG)" == "MMgrPat - Win32 Release"


"$(INTDIR)\Dlg_PatT.obj" : $(SOURCE) $(DEP_CPP_DLG_P) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"


"$(INTDIR)\Dlg_PatT.obj" : $(SOURCE) $(DEP_CPP_DLG_P) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_PatT.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_pcon.cpp
DEP_CPP_DLG_PC=\
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
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\Dlg_pcon.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	".\MPatRsrc.h"\
	

"$(INTDIR)\Dlg_pcon.obj" : $(SOURCE) $(DEP_CPP_DLG_PC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_pcon.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_rend.cpp
DEP_CPP_DLG_R=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Dlg_rend.h"\
	".\MPatRsrc.h"\
	

"$(INTDIR)\Dlg_rend.obj" : $(SOURCE) $(DEP_CPP_DLG_R) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_rend.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_rotp.cpp
DEP_CPP_DLG_RO=\
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
	{$(INCLUDE)}"\MCurRsrc.h"\
	".\MPatRsrc.h"\
	".\Dlg_rotp.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	

"$(INTDIR)\Dlg_rotp.obj" : $(SOURCE) $(DEP_CPP_DLG_RO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_rotp.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_SpnP.cpp
DEP_CPP_DLG_S=\
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
	".\Dlg_LTyp.h"\
	{$(INCLUDE)}"\Dlg_LALL.h"\
	{$(INCLUDE)}"\Dlg_LSyT.h"\
	{$(INCLUDE)}"\Dlg_LSym.h"\
	{$(INCLUDE)}"\Dlg_LSy3.h"\
	".\Dlg_SpnP.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	".\MPatRsrc.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
	

"$(INTDIR)\Dlg_SpnP.obj" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_SpnP.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_xtrd.cpp
DEP_CPP_DLG_X=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	".\MPatRsrc.h"\
	".\Dlg_xtrd.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	

"$(INTDIR)\Dlg_xtrd.obj" : $(SOURCE) $(DEP_CPP_DLG_X) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_xtrd.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPatdll.cpp
DEP_CPP_MPATD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MPatdll.h"\
	

"$(INTDIR)\MPatdll.obj" : $(SOURCE) $(DEP_CPP_MPATD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPatdll.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPatMgr.cpp
DEP_CPP_MPATM=\
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
	".\Dlg_pcon.h"\
	".\Dlg_xtrd.h"\
	".\Dlg_rotp.h"\
	".\Dlg_loft.h"\
	".\Dlg_swip.h"\
	".\Dlg_duct.h"\
	".\dlg_coop.h"\
	".\dlg_cop3.h"\
	".\Dlg_CooT.h"\
	".\Dlg_SpnP.h"\
	".\MPatdll.h"\
	".\MPatRsrc.h"\
	".\MPatMgr.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\MPatMgr.obj" : $(SOURCE) $(DEP_CPP_MPATM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPatMgr.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPatMgr.rc

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

DEP_RSC_MPATMG=\
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
	".\MPatRsrc.hm"\
	

"$(INTDIR)\MPatMgr.res" : $(SOURCE) $(DEP_RSC_MPATMG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

DEP_RSC_MPATMG=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	".\..\Applic\Res\Curvebit.bmp"\
	".\..\Applic\Res\Ico_pipe.ico"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	".\MPatRsrc.h"\
	".\MPatRsrc.hm"\
	

"$(INTDIR)\MPatMgr.res" : $(SOURCE) $(DEP_RSC_MPATMG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pa_xtrud.cpp
DEP_CPP_PA_XT=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\PA_Xtrud.h"\
	

"$(INTDIR)\Pa_xtrud.obj" : $(SOURCE) $(DEP_CPP_PA_XT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_gangp.cpp
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
	".\MPatMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\Mi_gangp.obj" : $(SOURCE) $(DEP_CPP_MI_GA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mp_CoonP.cpp
DEP_CPP_MP_CO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MPatMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Pa_CoonP.h"\
	".\Mp_CoonP.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mp_CoonP.obj" : $(SOURCE) $(DEP_CPP_MP_CO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mp_CooP3.cpp
DEP_CPP_MP_COO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MPatMgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Pa_CooP3.h"\
	".\Mp_CooP3.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mp_CooP3.obj" : $(SOURCE) $(DEP_CPP_MP_COO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mp_duct.cpp
DEP_CPP_MP_DU=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MPatMgr.h"\
	".\Dlg_duct.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Pa_duct.h"\
	".\Mp_duct.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	".\MPatRsrc.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\Mp_duct.obj" : $(SOURCE) $(DEP_CPP_MP_DU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mp_loft2.cpp
DEP_CPP_MP_LO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MPatMgr.h"\
	".\Dlg_loft.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Pa_loft2.h"\
	".\Mp_loft2.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	".\MPatRsrc.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mp_loft2.obj" : $(SOURCE) $(DEP_CPP_MP_LO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mp_rotat.cpp
DEP_CPP_MP_RO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MPatMgr.h"\
	".\Dlg_rotp.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Pa_rotat.h"\
	".\Mp_rotat.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	".\MPatRsrc.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mp_rotat.obj" : $(SOURCE) $(DEP_CPP_MP_RO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mp_sweep.cpp
DEP_CPP_MP_SW=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MPatMgr.h"\
	".\Dlg_swip.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Pa_sweep.h"\
	".\Mp_sweep.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	".\MPatRsrc.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	

"$(INTDIR)\Mp_sweep.obj" : $(SOURCE) $(DEP_CPP_MP_SW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mp_xtrud.cpp
DEP_CPP_MP_XT=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MPatMgr.h"\
	".\Dlg_xtrd.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\PA_Xtrud.h"\
	".\Mp_xtrud.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	".\MPatRsrc.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mp_xtrud.obj" : $(SOURCE) $(DEP_CPP_MP_XT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pa_CoonP.cpp
DEP_CPP_PA_CO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Pa_CoonP.h"\
	

"$(INTDIR)\Pa_CoonP.obj" : $(SOURCE) $(DEP_CPP_PA_CO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pa_CooP3.cpp
DEP_CPP_PA_COO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Pa_CooP3.h"\
	

"$(INTDIR)\Pa_CooP3.obj" : $(SOURCE) $(DEP_CPP_PA_COO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pa_duct.cpp
DEP_CPP_PA_DU=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\PA_Xtrud.h"\
	".\Pa_rotat.h"\
	".\Pa_duct.h"\
	{$(INCLUDE)}"\Def_View.h"\
	

"$(INTDIR)\Pa_duct.obj" : $(SOURCE) $(DEP_CPP_PA_DU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pa_loft2.cpp
DEP_CPP_PA_LO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Pa_loft2.h"\
	

"$(INTDIR)\Pa_loft2.obj" : $(SOURCE) $(DEP_CPP_PA_LO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pa_loft4.cpp
DEP_CPP_PA_LOF=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\PA_Loft4.h"\
	

"$(INTDIR)\Pa_loft4.obj" : $(SOURCE) $(DEP_CPP_PA_LOF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pa_rotat.cpp
DEP_CPP_PA_RO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Pa_rotat.h"\
	{$(INCLUDE)}"\Def_View.h"\
	

"$(INTDIR)\Pa_rotat.obj" : $(SOURCE) $(DEP_CPP_PA_RO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pa_sweep.cpp
DEP_CPP_PA_SW=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\PA_Xtrud.h"\
	".\Pa_rotat.h"\
	".\Pa_sweep.h"\
	{$(INCLUDE)}"\Def_View.h"\
	

"$(INTDIR)\Pa_sweep.obj" : $(SOURCE) $(DEP_CPP_PA_SW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_swip.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_coop.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CooT.cpp
DEP_CPP_DLG_C=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Dlg_CooT.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\MPatRsrc.h"\
	

"$(INTDIR)\Dlg_CooT.obj" : $(SOURCE) $(DEP_CPP_DLG_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CooT.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_Cop3.cpp
DEP_CPP_DLG_CO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
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
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\dlg_cop3.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\MPatRsrc.h"\
	

"$(INTDIR)\Dlg_Cop3.obj" : $(SOURCE) $(DEP_CPP_DLG_CO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_cop3.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_duct.cpp
DEP_CPP_DLG_D=\
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
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\MPatRsrc.h"\
	".\Dlg_duct.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	

"$(INTDIR)\Dlg_duct.obj" : $(SOURCE) $(DEP_CPP_DLG_D) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_duct.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_loft.cpp
DEP_CPP_DLG_L=\
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
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	".\Dlg_loft.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	".\MPatRsrc.h"\
	

"$(INTDIR)\Dlg_loft.obj" : $(SOURCE) $(DEP_CPP_DLG_L) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_loft.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_swip.cpp
DEP_CPP_DLG_SW=\
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
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\MPatRsrc.h"\
	".\Dlg_swip.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	

"$(INTDIR)\Dlg_swip.obj" : $(SOURCE) $(DEP_CPP_DLG_SW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_coop.cpp
DEP_CPP_DLG_COO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
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
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\dlg_coop.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	".\MPatRsrc.h"\
	

"$(INTDIR)\dlg_coop.obj" : $(SOURCE) $(DEP_CPP_DLG_COO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MPatMgr.def

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_PatI.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_PatI.cpp
DEP_CPP_DLG_PA=\
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
	".\dlg_PatI.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	".\MPatRsrc.h"\
	

"$(INTDIR)\dlg_PatI.obj" : $(SOURCE) $(DEP_CPP_DLG_PA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_PSPN.h

!IF  "$(CFG)" == "MMgrPat - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrPat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_PSPN.cpp
DEP_CPP_MI_PS=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	".\MPatMgr.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	".\Dlg_SpnP.h"\
	".\Mi_PSPN.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	".\MPatRsrc.h"\
	{$(INCLUDE)}"\Mi_CSPN.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	

"$(INTDIR)\MI_PSPN.obj" : $(SOURCE) $(DEP_CPP_MI_PS) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
