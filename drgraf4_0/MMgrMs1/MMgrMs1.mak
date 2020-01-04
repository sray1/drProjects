# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=MMgrMs1 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MMgrMs1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MMgrMs1 - Win32 Release" && "$(CFG)" !=\
 "MMgrMs1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMgrMs1.mak" CFG="MMgrMs1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MMgrMs1 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MMgrMs1 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "MMgrMs1 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

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

ALL : "$(OUTDIR)\MMgrMs1.dll"

CLEAN : 
	-@erase ".\Release\MMgrMs1.dll"
	-@erase ".\Release\Elg_CNO3.obj"
	-@erase ".\Release\Dlg_wts.obj"
	-@erase ".\Release\Inter_c3.obj"
	-@erase ".\Release\Dlg_CrcI.obj"
	-@erase ".\Release\Cu_Circl.obj"
	-@erase ".\Release\Dlg_tang.obj"
	-@erase ".\Release\In_crcle.obj"
	-@erase ".\Release\Dlg_CMsN.obj"
	-@erase ".\Release\Inter_c2.obj"
	-@erase ".\Release\Mc_Quad.obj"
	-@erase ".\Release\Dlg_CMsR.obj"
	-@erase ".\Release\Mc_Lin.obj"
	-@erase ".\Release\Dlg_CClk.obj"
	-@erase ".\Release\Mc_Circl.obj"
	-@erase ".\Release\MMs1Mgr.obj"
	-@erase ".\Release\Inter_c1.obj"
	-@erase ".\Release\MI_CSPN.obj"
	-@erase ".\Release\Dlg_cpro.obj"
	-@erase ".\Release\Dlg_CMes.obj"
	-@erase ".\Release\Dlg_CPSI.obj"
	-@erase ".\Release\Mc_Cube.obj"
	-@erase ".\Release\Dlg_LMTR.obj"
	-@erase ".\Release\Dlg_SpnC.obj"
	-@erase ".\Release\Dlg_CrcT.obj"
	-@erase ".\Release\MMs1dll.obj"
	-@erase ".\Release\Dlg_knot.obj"
	-@erase ".\Release\Dlg_CMsU.obj"
	-@erase ".\Release\dlg_lqci.obj"
	-@erase ".\Release\Mi_GangC.obj"
	-@erase ".\Release\Mi_cprof.obj"
	-@erase ".\Release\Dlg_LMR.obj"
	-@erase ".\Release\MMs1Mgr.res"
	-@erase ".\Release\MMgrMs1.lib"
	-@erase ".\Release\MMgrMs1.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/MMgrMs1.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MMs1Mgr.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrMs1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/MMgrMs1.pdb" /machine:I386 /def:".\MMs1Mgr.def"\
 /out:"$(OUTDIR)/MMgrMs1.dll" /implib:"$(OUTDIR)/MMgrMs1.lib" 
DEF_FILE= \
	".\MMs1Mgr.def"
LINK32_OBJS= \
	".\Release\Elg_CNO3.obj" \
	".\Release\Dlg_wts.obj" \
	".\Release\Inter_c3.obj" \
	".\Release\Dlg_CrcI.obj" \
	".\Release\Cu_Circl.obj" \
	".\Release\Dlg_tang.obj" \
	".\Release\In_crcle.obj" \
	".\Release\Dlg_CMsN.obj" \
	".\Release\Inter_c2.obj" \
	".\Release\Mc_Quad.obj" \
	".\Release\Dlg_CMsR.obj" \
	".\Release\Mc_Lin.obj" \
	".\Release\Dlg_CClk.obj" \
	".\Release\Mc_Circl.obj" \
	".\Release\MMs1Mgr.obj" \
	".\Release\Inter_c1.obj" \
	".\Release\MI_CSPN.obj" \
	".\Release\Dlg_cpro.obj" \
	".\Release\Dlg_CMes.obj" \
	".\Release\Dlg_CPSI.obj" \
	".\Release\Mc_Cube.obj" \
	".\Release\Dlg_LMTR.obj" \
	".\Release\Dlg_SpnC.obj" \
	".\Release\Dlg_CrcT.obj" \
	".\Release\MMs1dll.obj" \
	".\Release\Dlg_knot.obj" \
	".\Release\Dlg_CMsU.obj" \
	".\Release\dlg_lqci.obj" \
	".\Release\Mi_GangC.obj" \
	".\Release\Mi_cprof.obj" \
	".\Release\Dlg_LMR.obj" \
	".\Release\MMs1Mgr.res"

"$(OUTDIR)\MMgrMs1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

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

ALL : "$(OUTDIR)\MMs1_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\applic\Debug\MMs1_D32.dll"
	-@erase ".\Debug\Dlg_CClk.obj"
	-@erase ".\Debug\Mc_Circl.obj"
	-@erase ".\Debug\Inter_c1.obj"
	-@erase ".\Debug\Dlg_CrcI.obj"
	-@erase ".\Debug\Dlg_cpro.obj"
	-@erase ".\Debug\Dlg_CMes.obj"
	-@erase ".\Debug\Dlg_CPSI.obj"
	-@erase ".\Debug\Cu_Circl.obj"
	-@erase ".\Debug\MI_CSPN.obj"
	-@erase ".\Debug\Dlg_tang.obj"
	-@erase ".\Debug\Dlg_SpnC.obj"
	-@erase ".\Debug\Dlg_LMR.obj"
	-@erase ".\Debug\Mc_Lin.obj"
	-@erase ".\Debug\In_crcle.obj"
	-@erase ".\Debug\Dlg_knot.obj"
	-@erase ".\Debug\Dlg_CMsN.obj"
	-@erase ".\Debug\MMs1dll.obj"
	-@erase ".\Debug\Dlg_CMsR.obj"
	-@erase ".\Debug\Mi_GangC.obj"
	-@erase ".\Debug\Mc_Quad.obj"
	-@erase ".\Debug\Dlg_LMTR.obj"
	-@erase ".\Debug\Elg_CNO3.obj"
	-@erase ".\Debug\Inter_c3.obj"
	-@erase ".\Debug\MMs1Mgr.obj"
	-@erase ".\Debug\Dlg_CrcT.obj"
	-@erase ".\Debug\Dlg_wts.obj"
	-@erase ".\Debug\Dlg_CMsU.obj"
	-@erase ".\Debug\Mc_Cube.obj"
	-@erase ".\Debug\dlg_lqci.obj"
	-@erase ".\Debug\Inter_c2.obj"
	-@erase ".\Debug\Mi_cprof.obj"
	-@erase ".\Debug\MMs1Mgr.res"
	-@erase "..\applic\Debug\MMs1_D32.lib"
	-@erase "..\applic\Debug\MMs1_D32.exp"
	-@erase ".\Debug\MMs1_D32.pdb"
	-@erase ".\Debug\MMs1_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/MMgrMs1.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/MMgrMs1.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MMs1Mgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrMs1.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Elem_D32.lib OGen_D32.lib Dr3D_D32.lib MNod_D32.lib /nologo /version:1.0 /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug/MMs1_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/MMs1_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Draw_D32.lib Elem_D32.lib OGen_D32.lib\
 Dr3D_D32.lib MNod_D32.lib /nologo /version:1.0 /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/MMs1_D32.pdb" /map:"$(INTDIR)/MMs1_D32.map"\
 /debug /machine:I386 /def:".\MMs1Mgr.def"\
 /out:"d:\drgraf4_0\applic\Debug/MMs1_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/MMs1_D32.lib" 
DEF_FILE= \
	".\MMs1Mgr.def"
LINK32_OBJS= \
	".\Debug\Dlg_CClk.obj" \
	".\Debug\Mc_Circl.obj" \
	".\Debug\Inter_c1.obj" \
	".\Debug\Dlg_CrcI.obj" \
	".\Debug\Dlg_cpro.obj" \
	".\Debug\Dlg_CMes.obj" \
	".\Debug\Dlg_CPSI.obj" \
	".\Debug\Cu_Circl.obj" \
	".\Debug\MI_CSPN.obj" \
	".\Debug\Dlg_tang.obj" \
	".\Debug\Dlg_SpnC.obj" \
	".\Debug\Dlg_LMR.obj" \
	".\Debug\Mc_Lin.obj" \
	".\Debug\In_crcle.obj" \
	".\Debug\Dlg_knot.obj" \
	".\Debug\Dlg_CMsN.obj" \
	".\Debug\MMs1dll.obj" \
	".\Debug\Dlg_CMsR.obj" \
	".\Debug\Mi_GangC.obj" \
	".\Debug\Mc_Quad.obj" \
	".\Debug\Dlg_LMTR.obj" \
	".\Debug\Elg_CNO3.obj" \
	".\Debug\Inter_c3.obj" \
	".\Debug\MMs1Mgr.obj" \
	".\Debug\Dlg_CrcT.obj" \
	".\Debug\Dlg_wts.obj" \
	".\Debug\Dlg_CMsU.obj" \
	".\Debug\Mc_Cube.obj" \
	".\Debug\dlg_lqci.obj" \
	".\Debug\Inter_c2.obj" \
	".\Debug\Mi_cprof.obj" \
	".\Debug\MMs1Mgr.res"

"$(OUTDIR)\MMs1_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MMgrMs1 - Win32 Release"
# Name "MMgrMs1 - Win32 Debug"

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MMs1Rsrc.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CClk.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CrcI.cpp
DEP_CPP_DLG_C=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Lims.h"\
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
	".\MMs1dll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\dlg_crci.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"


"$(INTDIR)\Dlg_CrcI.obj" : $(SOURCE) $(DEP_CPP_DLG_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"


"$(INTDIR)\Dlg_CrcI.obj" : $(SOURCE) $(DEP_CPP_DLG_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_crci.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CrcT.cpp
DEP_CPP_DLG_CR=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	".\Dlg_CrcT.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	

"$(INTDIR)\Dlg_CrcT.obj" : $(SOURCE) $(DEP_CPP_DLG_CR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CrcT.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_knot.cpp
DEP_CPP_DLG_K=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\Dlg_knot.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	

"$(INTDIR)\Dlg_knot.obj" : $(SOURCE) $(DEP_CPP_DLG_K) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_knot.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_lqci.cpp
DEP_CPP_DLG_L=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MMs1dll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\dlg_lqci.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\dlg_lqci.obj" : $(SOURCE) $(DEP_CPP_DLG_L) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_lqci.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_tang.cpp
DEP_CPP_DLG_T=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	".\Dlg_tang.h"\
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
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Dlg_tang.obj" : $(SOURCE) $(DEP_CPP_DLG_T) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_tang.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MMs1dll.cpp
DEP_CPP_MCURD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MMs1dll.h"\
	

"$(INTDIR)\MMs1dll.obj" : $(SOURCE) $(DEP_CPP_MCURD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MMs1dll.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MMs1Mgr.cpp
DEP_CPP_MCURM=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	".\Dlg_CClk.h"\
	".\Dlg_CrcT.h"\
	".\Dlg_cpro.h"\
	".\Dlg_CPSI.h"\
	".\Dlg_SpnC.h"\
	".\MMs1dll.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	".\MMs1mgr.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	

"$(INTDIR)\MMs1Mgr.obj" : $(SOURCE) $(DEP_CPP_MCURM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MMs1mgr.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MMs1Mgr.rc

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

DEP_RSC_MCURMG=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	".\..\Applic\Res\Curvebit.bmp"\
	".\..\Applic\Res\Ico_pipe.ico"\
	".\MMs1Rsrc.hm"\
	

"$(INTDIR)\MMs1Mgr.res" : $(SOURCE) $(DEP_RSC_MCURMG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

DEP_RSC_MCURMG=\
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
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	".\MMs1Rsrc.hm"\
	

"$(INTDIR)\MMs1Mgr.res" : $(SOURCE) $(DEP_RSC_MCURMG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CClk.cpp
DEP_CPP_DLG_CC=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	".\Dlg_knot.h"\
	".\Dlg_wts.h"\
	".\Dlg_tang.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\Dlg_CClk.h"\
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
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Dlg_CClk.obj" : $(SOURCE) $(DEP_CPP_DLG_CC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CMsN.cpp
DEP_CPP_DLG_CM=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\Dlg_CMsN.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Dlg_CMsN.obj" : $(SOURCE) $(DEP_CPP_DLG_CM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CMsR.cpp
DEP_CPP_DLG_CMS=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Dlg_CMsR.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Dlg_CMsR.obj" : $(SOURCE) $(DEP_CPP_DLG_CMS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CMsU.cpp
DEP_CPP_DLG_CMSU=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Dlg_CMsU.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Dlg_CMsU.obj" : $(SOURCE) $(DEP_CPP_DLG_CMSU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CMes.cpp
DEP_CPP_DLG_CME=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	".\Dlg_CMsN.h"\
	".\Dlg_CMsU.h"\
	".\Dlg_CMes.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Dlg_CMes.obj" : $(SOURCE) $(DEP_CPP_DLG_CME) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MMs1Mgr.def

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_wts.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_wts.cpp
DEP_CPP_DLG_W=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\Dlg_wts.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	

"$(INTDIR)\Dlg_wts.obj" : $(SOURCE) $(DEP_CPP_DLG_W) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_GangC.cpp
DEP_CPP_MI_GA=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MMs1mgr.h"\
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Drfont.h"\
	{$(INCLUDE)}"\Booleans.h"\
	".\MC_Circl.h"\
	".\MC_Lin.h"\
	".\MC_Quad.h"\
	".\MC_Cube.h"\
	".\Dlg_CClk.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	".\Mi_GangC.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Def_Ms.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	".\Inter_c1.h"\
	".\Inter_c2.h"\
	".\Inter_c3.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Mi_GangC.obj" : $(SOURCE) $(DEP_CPP_MI_GA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cu_Circl.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\In_crcle.cpp
DEP_CPP_IN_CR=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	".\In_crcle.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\In_crcle.obj" : $(SOURCE) $(DEP_CPP_IN_CR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\In_crcle.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Inter_c1.cpp
DEP_CPP_INTER=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\Inter_c1.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\Inter_c1.obj" : $(SOURCE) $(DEP_CPP_INTER) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Inter_c1.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Inter_c2.cpp
DEP_CPP_INTER_=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\Inter_c2.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\Inter_c2.obj" : $(SOURCE) $(DEP_CPP_INTER_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Inter_c2.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Inter_c3.cpp
DEP_CPP_INTER_C=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\Inter_c3.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\Inter_c3.obj" : $(SOURCE) $(DEP_CPP_INTER_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Inter_c3.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mc_Circl.cpp
DEP_CPP_MC_CI=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MMs1mgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Cu_Circl.h"\
	".\MC_Circl.h"\
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
	".\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mc_Circl.obj" : $(SOURCE) $(DEP_CPP_MC_CI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MC_Circl.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mc_Cube.cpp
DEP_CPP_MC_CU=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MMs1mgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Inter_c3.h"\
	".\MC_Cube.h"\
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
	".\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mc_Cube.obj" : $(SOURCE) $(DEP_CPP_MC_CU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MC_Cube.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mc_Lin.cpp
DEP_CPP_MC_LI=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MMs1mgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Inter_c1.h"\
	".\MC_Lin.h"\
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
	".\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mc_Lin.obj" : $(SOURCE) $(DEP_CPP_MC_LI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MC_Lin.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mc_Quad.cpp
DEP_CPP_MC_QU=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MMs1mgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	".\Inter_c2.h"\
	".\MC_Quad.h"\
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
	".\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mc_Quad.obj" : $(SOURCE) $(DEP_CPP_MC_QU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MC_Quad.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cu_Circl.cpp
DEP_CPP_CU_CI=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Cu_Circl.h"\
	{$(INCLUDE)}"\Def_View.h"\
	

"$(INTDIR)\Cu_Circl.obj" : $(SOURCE) $(DEP_CPP_CU_CI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_GangC.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_SpnC.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_cpro.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_SpnC.cpp
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
	".\Dlg_SpnC.h"\
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
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Dlg_SpnC.obj" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_cpro.cpp
DEP_CPP_DLG_CP=\
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
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Dlg_LMTR.h"\
	{$(INCLUDE)}"\Dlg_LMR.h"\
	{$(INCLUDE)}"\Dlg_plmC.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\Dlg_cpro.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	".\..\MMgrPat\MPatRsrc.h"\
	

"$(INTDIR)\Dlg_cpro.obj" : $(SOURCE) $(DEP_CPP_DLG_CP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LMR.cpp
DEP_CPP_DLG_LM=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
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
	{$(INCLUDE)}"\Dlg_LMR.h"\
	{$(INCLUDE)}"\Def_Type.h"\
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
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Dlg_LMR.obj" : $(SOURCE) $(DEP_CPP_DLG_LM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LMR.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LMTR.cpp
DEP_CPP_DLG_LMT=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
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
	{$(INCLUDE)}"\Dlg_LMTR.h"\
	{$(INCLUDE)}"\Def_Type.h"\
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
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Dlg_LMTR.obj" : $(SOURCE) $(DEP_CPP_DLG_LMT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LMTR.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Elg_CNO3.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Elg_CNO3.cpp
DEP_CPP_ELG_C=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Def_Lims.h"\
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
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\Elg_CNO3.h"\
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
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Elg_CNO3.obj" : $(SOURCE) $(DEP_CPP_ELG_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_CSPN.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_CSPN.cpp
DEP_CPP_MI_CS=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	".\MMs1mgr.h"\
	".\Dlg_SpnC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	".\Mi_CSPN.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	{$(INCLUDE)}"\Triangle.h"\
	

"$(INTDIR)\MI_CSPN.obj" : $(SOURCE) $(DEP_CPP_MI_CS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CPSI.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_CPSI.cpp
DEP_CPP_DLG_CPS=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\Dlg_CPSI.h"\
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
	{$(INCLUDE)}"\MMs1Rsrc.h"\
	

"$(INTDIR)\Dlg_CPSI.obj" : $(SOURCE) $(DEP_CPP_DLG_CPS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_cprof.h

!IF  "$(CFG)" == "MMgrMs1 - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrMs1 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_cprof.cpp
DEP_CPP_MI_CP=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\MMs1mgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Mi_cprof.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
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
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	".\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\Mi_cprof.obj" : $(SOURCE) $(DEP_CPP_MI_CP) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
