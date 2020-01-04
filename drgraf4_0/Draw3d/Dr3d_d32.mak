# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Dr3d_d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Dr3d_d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dr3d_d - Win32 Release" && "$(CFG)" != "Dr3d_d - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dr3d_d32.mak" CFG="Dr3d_d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dr3d_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dr3d_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Dr3d_d - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "Dr3d_d - Win32 Release"

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

ALL : "$(OUTDIR)\lib"

CLEAN : 
	-@erase ".\Release\vc40.pdb"
	-@erase ".\drgraf4_0\lib"
	-@erase ".\Release\Xform.obj"
	-@erase ".\Release\Dr3ddll.obj"
	-@erase ".\Release\Drclip.obj"
	-@erase ".\Release\Dr3dmgr.obj"
	-@erase ".\Release\3dmath.obj"
	-@erase ".\Release\Dr3d.res"
	-@erase ".\Release\MsMath.obj"
	-@erase ".\Release\lib.lib"
	-@erase ".\Release\lib.exp"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W4 /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W4 /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dr3d_d32.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dr3d.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dr3d_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 libcmt.lib,nafx /nologo /version:32.1 /subsystem:windows /verbose /dll /map:"FULL" /machine:IX86 /out:"drgraf4_0\lib"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=libcmt.lib,nafx /nologo /version:32.1 /subsystem:windows /verbose\
 /dll /incremental:no /pdb:"$(OUTDIR)/lib.pdb" /map:"FULL" /machine:IX86\
 /def:".\Dr3d_d.def" /out:"drgraf4_0\lib" /implib:"$(OUTDIR)/lib.lib" 
DEF_FILE= \
	".\Dr3d_d.def"
LINK32_OBJS= \
	"$(INTDIR)/Xform.obj" \
	"$(INTDIR)/Dr3ddll.obj" \
	"$(INTDIR)/Drclip.obj" \
	"$(INTDIR)/Dr3dmgr.obj" \
	"$(INTDIR)/3dmath.obj" \
	"$(INTDIR)/MsMath.obj" \
	"$(INTDIR)/Dr3d.res"

"$(OUTDIR)\lib" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dr3d_d - Win32 Debug"

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

ALL : "$(OUTDIR)\Dr3d_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase "..\applic\Debug\Dr3d_d32.dll"
	-@erase ".\Debug\Xform.obj"
	-@erase ".\Debug\Dr3ddll.obj"
	-@erase ".\Debug\3dmath.obj"
	-@erase ".\Debug\Dr3dmgr.obj"
	-@erase ".\Debug\Drclip.obj"
	-@erase ".\Debug\Dr3d.res"
	-@erase ".\Debug\MsMath.obj"
	-@erase "..\applic\Debug\Dr3d_d32.lib"
	-@erase "..\applic\Debug\Dr3d_d32.exp"
	-@erase ".\Debug\Dr3d_d32.pdb"
	-@erase ".\Debug\Dr3d_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /G3 /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W4 /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_MBCS " /YX"stdafx.x" /c
# SUBTRACT CPP /Gy /Fr
CPP_PROJ=/nologo /MDd /W4 /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXEXT" /D "_MBCS " /Fp"$(INTDIR)/Dr3d_d32.pch" /YX"stdafx.x"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dr3d.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dr3d_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 /nologo /version:32.1 /subsystem:windows /dll /incremental:no /map /debug /machine:IX86 /out:"d:\drgraf4_0\applic\Debug\Dr3d_d32.dll" /implib:"d:\drgraf4_0\applic\Debug\Dr3d_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /version:32.1 /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Dr3d_d32.pdb" /map:"$(INTDIR)/Dr3d_d32.map" /debug\
 /machine:IX86 /def:".\Dr3d_d.def" /out:"d:\drgraf4_0\applic\Debug\Dr3d_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug\Dr3d_d32.lib" 
DEF_FILE= \
	".\Dr3d_d.def"
LINK32_OBJS= \
	"$(INTDIR)/Xform.obj" \
	"$(INTDIR)/Dr3ddll.obj" \
	"$(INTDIR)/3dmath.obj" \
	"$(INTDIR)/Dr3dmgr.obj" \
	"$(INTDIR)/Drclip.obj" \
	"$(INTDIR)/MsMath.obj" \
	"$(INTDIR)/Dr3d.res"

"$(OUTDIR)\Dr3d_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Dr3d_d - Win32 Release"
# Name "Dr3d_d - Win32 Debug"

!IF  "$(CFG)" == "Dr3d_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Dr3d_d - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Dr3ddll.cpp
DEP_CPP_DR3DD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Dr3DDll.h"\
	

!IF  "$(CFG)" == "Dr3d_d - Win32 Release"


"$(INTDIR)\Dr3ddll.obj" : $(SOURCE) $(DEP_CPP_DR3DD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Dr3d_d - Win32 Debug"


"$(INTDIR)\Dr3ddll.obj" : $(SOURCE) $(DEP_CPP_DR3DD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dr3d.rc

"$(INTDIR)\Dr3d.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dr3dmgr.cpp
DEP_CPP_DR3DM=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Curdef.h"\
	".\Dr3DDll.h"\
	{$(INCLUDE)}"\Dr3dmgr.h"\
	{$(INCLUDE)}"\Def_View.h"\
	

"$(INTDIR)\Dr3dmgr.obj" : $(SOURCE) $(DEP_CPP_DR3DM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dr3d_d.def

!IF  "$(CFG)" == "Dr3d_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Dr3d_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Xform.cpp
DEP_CPP_XFORM=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\Xform.h"\
	{$(INCLUDE)}"\Def_View.h"\
	

"$(INTDIR)\Xform.obj" : $(SOURCE) $(DEP_CPP_XFORM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\3dmath.cpp
DEP_CPP_3DMAT=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Lims.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

"$(INTDIR)\3dmath.obj" : $(SOURCE) $(DEP_CPP_3DMAT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drclip.cpp
DEP_CPP_DRCLI=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drclip.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	

"$(INTDIR)\Drclip.obj" : $(SOURCE) $(DEP_CPP_DRCLI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsMath.h

!IF  "$(CFG)" == "Dr3d_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Dr3d_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MsMath.cpp
DEP_CPP_MSMAT=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_MLim.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	".\MsMath.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

"$(INTDIR)\MsMath.obj" : $(SOURCE) $(DEP_CPP_MSMAT) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
