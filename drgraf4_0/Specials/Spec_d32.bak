# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Spec_d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Spec_d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Spec_d - Win32 Release" && "$(CFG)" != "Spec_d - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Spec_d32.mak" CFG="Spec_d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Spec_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Spec_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Spec_d - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "Spec_d - Win32 Release"

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

ALL : "$(OUTDIR)\Spec_d32.dll" "$(OUTDIR)\Spec_d32.bsc"

CLEAN : 
	-@erase ".\Release\Spec_d32.bsc"
	-@erase ".\Release\Scalefac.sbr"
	-@erase ".\Release\Dlistmgr.sbr"
	-@erase ".\Release\Datawind.sbr"
	-@erase ".\Release\Drfont.sbr"
	-@erase ".\Release\Drpen.sbr"
	-@erase ".\Release\Obj3dmnu.sbr"
	-@erase ".\Release\Patchmnu.sbr"
	-@erase ".\Release\Drobject.sbr"
	-@erase ".\Release\Layer.sbr"
	-@erase ".\Release\Booleans.sbr"
	-@erase ".\Release\Specdll.sbr"
	-@erase ".\Release\Mapfacto.sbr"
	-@erase ".\Release\Hitnet.sbr"
	-@erase ".\Release\Precison.sbr"
	-@erase ".\Release\Matobj.sbr"
	-@erase ".\Release\Unit.sbr"
	-@erase ".\Release\Spec_d32.dll"
	-@erase ".\Release\Hitnet.obj"
	-@erase ".\Release\Precison.obj"
	-@erase ".\Release\Matobj.obj"
	-@erase ".\Release\Unit.obj"
	-@erase ".\Release\Scalefac.obj"
	-@erase ".\Release\Dlistmgr.obj"
	-@erase ".\Release\Datawind.obj"
	-@erase ".\Release\Drfont.obj"
	-@erase ".\Release\Drpen.obj"
	-@erase ".\Release\Obj3dmnu.obj"
	-@erase ".\Release\Patchmnu.obj"
	-@erase ".\Release\Drobject.obj"
	-@erase ".\Release\Layer.obj"
	-@erase ".\Release\Booleans.obj"
	-@erase ".\Release\Specdll.obj"
	-@erase ".\Release\Mapfacto.obj"
	-@erase ".\Release\Spec_d32.lib"
	-@erase ".\Release\Spec_d32.exp"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Spec_d32.pch"\
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Spec_d32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/Scalefac.sbr" \
	"$(INTDIR)/Dlistmgr.sbr" \
	"$(INTDIR)/Datawind.sbr" \
	"$(INTDIR)/Drfont.sbr" \
	"$(INTDIR)/Drpen.sbr" \
	"$(INTDIR)/Obj3dmnu.sbr" \
	"$(INTDIR)/Patchmnu.sbr" \
	"$(INTDIR)/Drobject.sbr" \
	"$(INTDIR)/Layer.sbr" \
	"$(INTDIR)/Booleans.sbr" \
	"$(INTDIR)/Specdll.sbr" \
	"$(INTDIR)/Mapfacto.sbr" \
	"$(INTDIR)/Hitnet.sbr" \
	"$(INTDIR)/Precison.sbr" \
	"$(INTDIR)/Matobj.sbr" \
	"$(INTDIR)/Unit.sbr"

"$(OUTDIR)\Spec_d32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
LINK32_FLAGS=oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Spec_d32.pdb" /map:"FULL" /machine:IX86\
 /def:".\Spec_d.def" /out:"$(OUTDIR)/Spec_d32.dll"\
 /implib:"$(OUTDIR)/Spec_d32.lib" 
DEF_FILE= \
	".\Spec_d.def"
LINK32_OBJS= \
	"$(INTDIR)/Hitnet.obj" \
	"$(INTDIR)/Precison.obj" \
	"$(INTDIR)/Matobj.obj" \
	"$(INTDIR)/Unit.obj" \
	"$(INTDIR)/Scalefac.obj" \
	"$(INTDIR)/Dlistmgr.obj" \
	"$(INTDIR)/Datawind.obj" \
	"$(INTDIR)/Drfont.obj" \
	"$(INTDIR)/Drpen.obj" \
	"$(INTDIR)/Obj3dmnu.obj" \
	"$(INTDIR)/Patchmnu.obj" \
	"$(INTDIR)/Drobject.obj" \
	"$(INTDIR)/Layer.obj" \
	"$(INTDIR)/Booleans.obj" \
	"$(INTDIR)/Specdll.obj" \
	"$(INTDIR)/Mapfacto.obj"

"$(OUTDIR)\Spec_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"

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

ALL : "$(OUTDIR)\Spec_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase "..\applic\Debug\Spec_d32.dll"
	-@erase ".\Debug\Unit.obj"
	-@erase ".\Debug\Layer.obj"
	-@erase ".\Debug\Drobject.obj"
	-@erase ".\Debug\Mapfacto.obj"
	-@erase ".\Debug\Matobj.obj"
	-@erase ".\Debug\Precison.obj"
	-@erase ".\Debug\Specdll.obj"
	-@erase ".\Debug\Obj3dmnu.obj"
	-@erase ".\Debug\Patchmnu.obj"
	-@erase ".\Debug\Scalefac.obj"
	-@erase ".\Debug\Dlistmgr.obj"
	-@erase ".\Debug\Datawind.obj"
	-@erase ".\Debug\Hitnet.obj"
	-@erase ".\Debug\Booleans.obj"
	-@erase ".\Debug\Drpen.obj"
	-@erase ".\Debug\Drfont.obj"
	-@erase "..\applic\Debug\Spec_d32.lib"
	-@erase "..\applic\Debug\Spec_d32.exp"
	-@erase ".\Debug\Spec_d32.pdb"
	-@erase ".\Debug\Spec_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "SUPPORT_OBSOLETE_SYSTEMS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D " _AFXEXT" /YX"stdafx.h" /c
# SUBTRACT CPP /Gy
CPP_PROJ=/nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D " _AFXEXT" /Fp"$(INTDIR)/Spec_d32.pch" /YX"stdafx.h" /Fo"$(INTDIR)/"\
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Spec_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 Dr3D_D.lib oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Dr3D_d32.lib /nologo /version:32.0 /subsystem:windows /dll /incremental:no /map /debug /machine:IX86 /out:"d:\drgraf4_0\applic\Debug\Spec_d32.dll" /implib:"d:\drgraf4_0\applic\Debug\Spec_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Dr3D_d32.lib /nologo /version:32.0 /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Spec_d32.pdb" /map:"$(INTDIR)/Spec_d32.map"\
 /debug /machine:IX86 /def:".\Spec_d.def"\
 /out:"d:\drgraf4_0\applic\Debug\Spec_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug\Spec_d32.lib" 
DEF_FILE= \
	".\Spec_d.def"
LINK32_OBJS= \
	"$(INTDIR)/Unit.obj" \
	"$(INTDIR)/Layer.obj" \
	"$(INTDIR)/Drobject.obj" \
	"$(INTDIR)/Mapfacto.obj" \
	"$(INTDIR)/Matobj.obj" \
	"$(INTDIR)/Precison.obj" \
	"$(INTDIR)/Specdll.obj" \
	"$(INTDIR)/Obj3dmnu.obj" \
	"$(INTDIR)/Patchmnu.obj" \
	"$(INTDIR)/Scalefac.obj" \
	"$(INTDIR)/Dlistmgr.obj" \
	"$(INTDIR)/Datawind.obj" \
	"$(INTDIR)/Hitnet.obj" \
	"$(INTDIR)/Booleans.obj" \
	"$(INTDIR)/Drpen.obj" \
	"$(INTDIR)/Drfont.obj"

"$(OUTDIR)\Spec_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Spec_d - Win32 Release"
# Name "Spec_d - Win32 Debug"

!IF  "$(CFG)" == "Spec_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Datawind.cpp
DEP_CPP_DATAW=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Datawind.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Datawind.obj" : $(SOURCE) $(DEP_CPP_DATAW) "$(INTDIR)"

"$(INTDIR)\Datawind.sbr" : $(SOURCE) $(DEP_CPP_DATAW) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Datawind.obj" : $(SOURCE) $(DEP_CPP_DATAW) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Booleans.cpp
DEP_CPP_BOOLE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Booleans.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Booleans.obj" : $(SOURCE) $(DEP_CPP_BOOLE) "$(INTDIR)"

"$(INTDIR)\Booleans.sbr" : $(SOURCE) $(DEP_CPP_BOOLE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Booleans.obj" : $(SOURCE) $(DEP_CPP_BOOLE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drfont.cpp
DEP_CPP_DRFON=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Drfont.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Drfont.obj" : $(SOURCE) $(DEP_CPP_DRFON) "$(INTDIR)"

"$(INTDIR)\Drfont.sbr" : $(SOURCE) $(DEP_CPP_DRFON) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Drfont.obj" : $(SOURCE) $(DEP_CPP_DRFON) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drpen.cpp
DEP_CPP_DRPEN=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Drpen.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Drpen.obj" : $(SOURCE) $(DEP_CPP_DRPEN) "$(INTDIR)"

"$(INTDIR)\Drpen.sbr" : $(SOURCE) $(DEP_CPP_DRPEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Drpen.obj" : $(SOURCE) $(DEP_CPP_DRPEN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hitnet.cpp
DEP_CPP_HITNE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Lims.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Hitnet.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Hitnet.obj" : $(SOURCE) $(DEP_CPP_HITNE) "$(INTDIR)"

"$(INTDIR)\Hitnet.sbr" : $(SOURCE) $(DEP_CPP_HITNE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Hitnet.obj" : $(SOURCE) $(DEP_CPP_HITNE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Layer.cpp
DEP_CPP_LAYER=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Layer.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Layer.obj" : $(SOURCE) $(DEP_CPP_LAYER) "$(INTDIR)"

"$(INTDIR)\Layer.sbr" : $(SOURCE) $(DEP_CPP_LAYER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Layer.obj" : $(SOURCE) $(DEP_CPP_LAYER) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mapfacto.cpp
DEP_CPP_MAPFA=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Mapfacto.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Mapfacto.obj" : $(SOURCE) $(DEP_CPP_MAPFA) "$(INTDIR)"

"$(INTDIR)\Mapfacto.sbr" : $(SOURCE) $(DEP_CPP_MAPFA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Mapfacto.obj" : $(SOURCE) $(DEP_CPP_MAPFA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Unit.cpp
DEP_CPP_UNIT_=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Unit.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Unit.obj" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"

"$(INTDIR)\Unit.sbr" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Unit.obj" : $(SOURCE) $(DEP_CPP_UNIT_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Precison.cpp
DEP_CPP_PRECI=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Precison.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Precison.obj" : $(SOURCE) $(DEP_CPP_PRECI) "$(INTDIR)"

"$(INTDIR)\Precison.sbr" : $(SOURCE) $(DEP_CPP_PRECI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Precison.obj" : $(SOURCE) $(DEP_CPP_PRECI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Scalefac.cpp
DEP_CPP_SCALE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Scalefac.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Scalefac.obj" : $(SOURCE) $(DEP_CPP_SCALE) "$(INTDIR)"

"$(INTDIR)\Scalefac.sbr" : $(SOURCE) $(DEP_CPP_SCALE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Scalefac.obj" : $(SOURCE) $(DEP_CPP_SCALE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Specdll.cpp
DEP_CPP_SPECD=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Glb_Spec.h"\
	".\Specdll.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Specdll.obj" : $(SOURCE) $(DEP_CPP_SPECD) "$(INTDIR)"

"$(INTDIR)\Specdll.sbr" : $(SOURCE) $(DEP_CPP_SPECD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Specdll.obj" : $(SOURCE) $(DEP_CPP_SPECD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drobject.cpp
DEP_CPP_DROBJ=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Drclip.h"\
	{$(INCLUDE)}"\Xform.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Drobject.obj" : $(SOURCE) $(DEP_CPP_DROBJ) "$(INTDIR)"

"$(INTDIR)\Drobject.sbr" : $(SOURCE) $(DEP_CPP_DROBJ) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Drobject.obj" : $(SOURCE) $(DEP_CPP_DROBJ) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Obj3dmnu.cpp
DEP_CPP_OBJ3D=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Obj3dmnu.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Obj3dmnu.obj" : $(SOURCE) $(DEP_CPP_OBJ3D) "$(INTDIR)"

"$(INTDIR)\Obj3dmnu.sbr" : $(SOURCE) $(DEP_CPP_OBJ3D) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Obj3dmnu.obj" : $(SOURCE) $(DEP_CPP_OBJ3D) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Patchmnu.cpp
DEP_CPP_PATCH=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Spec.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	".\Patchmnu.h"\
	".\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Patchmnu.obj" : $(SOURCE) $(DEP_CPP_PATCH) "$(INTDIR)"

"$(INTDIR)\Patchmnu.sbr" : $(SOURCE) $(DEP_CPP_PATCH) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Patchmnu.obj" : $(SOURCE) $(DEP_CPP_PATCH) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlistmgr.cpp
DEP_CPP_DLIST=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Drobject.h"\
	".\Dlistmgr.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Dlistmgr.obj" : $(SOURCE) $(DEP_CPP_DLIST) "$(INTDIR)"

"$(INTDIR)\Dlistmgr.sbr" : $(SOURCE) $(DEP_CPP_DLIST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Dlistmgr.obj" : $(SOURCE) $(DEP_CPP_DLIST) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Spec_d.def

!IF  "$(CFG)" == "Spec_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Matobj.h

!IF  "$(CFG)" == "Spec_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Matobj.cpp
DEP_CPP_MATOB=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	

!IF  "$(CFG)" == "Spec_d - Win32 Release"


"$(INTDIR)\Matobj.obj" : $(SOURCE) $(DEP_CPP_MATOB) "$(INTDIR)"

"$(INTDIR)\Matobj.sbr" : $(SOURCE) $(DEP_CPP_MATOB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Spec_d - Win32 Debug"


"$(INTDIR)\Matobj.obj" : $(SOURCE) $(DEP_CPP_MATOB) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
