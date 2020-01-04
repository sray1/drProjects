# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Draw_d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Draw_d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Draw_d - Win32 Release" && "$(CFG)" != "Draw_d - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Draw_d32.mak" CFG="Draw_d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Draw_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Draw_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Draw_d - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "Draw_d - Win32 Release"

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

ALL : "$(OUTDIR)\Draw_d32.dll" "$(OUTDIR)\Draw_d32.bsc"

CLEAN : 
	-@erase ".\Release\Draw_d32.bsc"
	-@erase ".\Release\Drfrehnd.sbr"
	-@erase ".\Release\Drawdll.sbr"
	-@erase ".\Release\Drprism.sbr"
	-@erase ".\Release\Drlabel.sbr"
	-@erase ".\Release\Drgrid.sbr"
	-@erase ".\Release\Draw_d32.dll"
	-@erase ".\Release\Drgrid.obj"
	-@erase ".\Release\Drfrehnd.obj"
	-@erase ".\Release\Drawdll.obj"
	-@erase ".\Release\Drprism.obj"
	-@erase ".\Release\Drlabel.obj"
	-@erase ".\Release\Draw_d32.lib"
	-@erase ".\Release\Draw_d32.exp"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Draw_d32.pch"\
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Draw_d32.bsc" 
BSC32_SBRS= \
	".\Release\Drfrehnd.sbr" \
	".\Release\Drawdll.sbr" \
	".\Release\Drprism.sbr" \
	".\Release\Drlabel.sbr" \
	".\Release\Drgrid.sbr"

"$(OUTDIR)\Draw_d32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib Elem_D32.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
LINK32_FLAGS=Dr3D_D32.lib Spec_D32.lib Elem_D32.lib /nologo /subsystem:windows\
 /dll /incremental:no /pdb:"$(OUTDIR)/Draw_d32.pdb" /map:"FULL" /machine:IX86\
 /def:".\Draw_d.def" /out:"$(OUTDIR)/Draw_d32.dll"\
 /implib:"$(OUTDIR)/Draw_d32.lib" 
DEF_FILE= \
	".\Draw_d.def"
LINK32_OBJS= \
	".\Release\Drgrid.obj" \
	".\Release\Drfrehnd.obj" \
	".\Release\Drawdll.obj" \
	".\Release\Drprism.obj" \
	".\Release\Drlabel.obj"

"$(OUTDIR)\Draw_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Draw_d - Win32 Debug"

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

ALL : "$(OUTDIR)\Draw_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase "..\applic\Debug\Draw_d32.dll"
	-@erase ".\Debug\Drlabel.obj"
	-@erase ".\Debug\Drfrehnd.obj"
	-@erase ".\Debug\Drgrid.obj"
	-@erase ".\Debug\Drawdll.obj"
	-@erase ".\Debug\Drprism.obj"
	-@erase "..\applic\Debug\Draw_d32.lib"
	-@erase "..\applic\Debug\Draw_d32.exp"
	-@erase ".\Debug\Draw_d32.pdb"
	-@erase ".\Debug\Draw_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Draw_d32.pch" /YX"stdafx.h" /Fo"$(INTDIR)/"\
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Draw_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 Dr3D_D.lib Spec_D.lib Elem_D.lib oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib OGen_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:IX86 /out:"d:\drgraf4_0\applic\Debug\Draw_d32.dll" /implib:"d:\drgraf4_0\applic\Debug\Draw_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Dr3D_D32.lib Spec_D32.lib OGen_D32.lib /nologo /subsystem:windows\
 /dll /incremental:no /pdb:"$(OUTDIR)/Draw_d32.pdb"\
 /map:"$(INTDIR)/Draw_d32.map" /debug /machine:IX86 /def:".\Draw_d.def"\
 /out:"d:\drgraf4_0\applic\Debug\Draw_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug\Draw_d32.lib" 
DEF_FILE= \
	".\Draw_d.def"
LINK32_OBJS= \
	".\Debug\Drlabel.obj" \
	".\Debug\Drfrehnd.obj" \
	".\Debug\Drgrid.obj" \
	".\Debug\Drawdll.obj" \
	".\Debug\Drprism.obj"

"$(OUTDIR)\Draw_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Draw_d - Win32 Release"
# Name "Draw_d - Win32 Debug"

!IF  "$(CFG)" == "Draw_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Draw_d - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Drawdll.cpp
DEP_CPP_DRAWD=\
	".\Stdafx.h"\
	".\Drawdll.h"\
	{$(INCLUDE)}"\Glb_Draw.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	

!IF  "$(CFG)" == "Draw_d - Win32 Release"


"$(INTDIR)\Drawdll.obj" : $(SOURCE) $(DEP_CPP_DRAWD) "$(INTDIR)"

"$(INTDIR)\Drawdll.sbr" : $(SOURCE) $(DEP_CPP_DRAWD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Draw_d - Win32 Debug"


"$(INTDIR)\Drawdll.obj" : $(SOURCE) $(DEP_CPP_DRAWD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drfrehnd.cpp
DEP_CPP_DRFRE=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Ext_Draw.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\Drfrehnd.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	{$(INCLUDE)}"\Drobject.h"\
	".\..\Specials\MatObj.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

!IF  "$(CFG)" == "Draw_d - Win32 Release"


"$(INTDIR)\Drfrehnd.obj" : $(SOURCE) $(DEP_CPP_DRFRE) "$(INTDIR)"

"$(INTDIR)\Drfrehnd.sbr" : $(SOURCE) $(DEP_CPP_DRFRE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Draw_d - Win32 Debug"


"$(INTDIR)\Drfrehnd.obj" : $(SOURCE) $(DEP_CPP_DRFRE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drlabel.cpp
DEP_CPP_DRLAB=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Ext_Draw.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\Drlabel.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Drnode.h"\
	".\..\Specials\MatObj.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

!IF  "$(CFG)" == "Draw_d - Win32 Release"


"$(INTDIR)\Drlabel.obj" : $(SOURCE) $(DEP_CPP_DRLAB) "$(INTDIR)"

"$(INTDIR)\Drlabel.sbr" : $(SOURCE) $(DEP_CPP_DRLAB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Draw_d - Win32 Debug"


"$(INTDIR)\Drlabel.obj" : $(SOURCE) $(DEP_CPP_DRLAB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drprism.cpp
DEP_CPP_DRPRI=\
	".\Stdafx.h"\
	".\DrPrism.h"\
	

!IF  "$(CFG)" == "Draw_d - Win32 Release"


"$(INTDIR)\Drprism.obj" : $(SOURCE) $(DEP_CPP_DRPRI) "$(INTDIR)"

"$(INTDIR)\Drprism.sbr" : $(SOURCE) $(DEP_CPP_DRPRI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Draw_d - Win32 Debug"


"$(INTDIR)\Drprism.obj" : $(SOURCE) $(DEP_CPP_DRPRI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drgrid.cpp
DEP_CPP_DRGRI=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Ext_Draw.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	".\Drgrid.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\Specials\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Draw.h"\
	

!IF  "$(CFG)" == "Draw_d - Win32 Release"


"$(INTDIR)\Drgrid.obj" : $(SOURCE) $(DEP_CPP_DRGRI) "$(INTDIR)"

"$(INTDIR)\Drgrid.sbr" : $(SOURCE) $(DEP_CPP_DRGRI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Draw_d - Win32 Debug"


"$(INTDIR)\Drgrid.obj" : $(SOURCE) $(DEP_CPP_DRGRI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Draw_d.def

!IF  "$(CFG)" == "Draw_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Draw_d - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
