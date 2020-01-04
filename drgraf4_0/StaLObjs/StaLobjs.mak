# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=StaLobjs - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to StaLobjs - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "StaLobjs - Win32 Release" && "$(CFG)" !=\
 "StaLobjs - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "StaLobjs.mak" CFG="StaLobjs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StaLobjs - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "StaLobjs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "StaLobjs - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "StaLobjs - Win32 Release"

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

ALL : "$(OUTDIR)\StaLobjs.dll"

CLEAN : 
	-@erase ".\Release\StaLobjs.dll"
	-@erase ".\Release\StaLdll.obj"
	-@erase ".\Release\DrStatic.obj"
	-@erase ".\Release\StaLobjs.lib"
	-@erase ".\Release\StaLobjs.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/StaLobjs.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/StaLobjs.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/StaLobjs.pdb" /machine:I386 /def:".\StaL_d.def"\
 /out:"$(OUTDIR)/StaLobjs.dll" /implib:"$(OUTDIR)/StaLobjs.lib" 
DEF_FILE= \
	".\StaL_d.def"
LINK32_OBJS= \
	".\Release\StaLdll.obj" \
	".\Release\DrStatic.obj"

"$(OUTDIR)\StaLobjs.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "StaLobjs - Win32 Debug"

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

ALL : "$(OUTDIR)\StaL_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase "..\applic\Debug\StaL_D32.dll"
	-@erase ".\Debug\StaLdll.obj"
	-@erase ".\Debug\DrStatic.obj"
	-@erase "..\applic\Debug\StaL_D32.lib"
	-@erase "..\applic\Debug\StaL_D32.exp"
	-@erase ".\Debug\StaL_D32.pdb"
	-@erase ".\Debug\StaL_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/StaLobjs.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/StaLobjs.pch" /YX"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/StaLobjs.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib OGen_D32.lib Draw_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug\StaL_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/StaL_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Dr3D_D32.lib Spec_D32.lib OGen_D32.lib Draw_D32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/StaL_D32.pdb"\
 /map:"$(INTDIR)/StaL_D32.map" /debug /machine:I386 /def:".\StaL_d.def"\
 /out:"d:\drgraf4_0\applic\Debug\StaL_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/StaL_D32.lib" 
DEF_FILE= \
	".\StaL_d.def"
LINK32_OBJS= \
	".\Debug\StaLdll.obj" \
	".\Debug\DrStatic.obj"

"$(OUTDIR)\StaL_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "StaLobjs - Win32 Release"
# Name "StaLobjs - Win32 Debug"

!IF  "$(CFG)" == "StaLobjs - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLobjs - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StaLdll.cpp
DEP_CPP_STALD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\StaLdll.h"\
	{$(INCLUDE)}"\Glb_StaL.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	

!IF  "$(CFG)" == "StaLobjs - Win32 Release"


"$(INTDIR)\StaLdll.obj" : $(SOURCE) $(DEP_CPP_STALD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "StaLobjs - Win32 Debug"


"$(INTDIR)\StaLdll.obj" : $(SOURCE) $(DEP_CPP_STALD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StaL_d.def

!IF  "$(CFG)" == "StaLobjs - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLobjs - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrStatic.h

!IF  "$(CFG)" == "StaLobjs - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLobjs - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrStatic.cpp
DEP_CPP_DRSTA=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Ext_StaL.h"\
	".\DrStatic.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\DrStatic.obj" : $(SOURCE) $(DEP_CPP_DRSTA) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
