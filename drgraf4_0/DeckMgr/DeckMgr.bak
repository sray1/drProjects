# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=DeckMgr - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DeckMgr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DeckMgr - Win32 Release" && "$(CFG)" !=\
 "DeckMgr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DeckMgr.mak" CFG="DeckMgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DeckMgr - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DeckMgr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "DeckMgr - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "DeckMgr - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\DeckMgr.dll"

CLEAN : 
	-@erase ".\Release\DeckMgr.dll"
	-@erase ".\Release\DeckMgr.obj"
	-@erase ".\Release\DeckWalk.obj"
	-@erase ".\Release\DeckDll.obj"
	-@erase ".\Release\DeckMgr.res"
	-@erase ".\Release\DeckMgr.lib"
	-@erase ".\Release\DeckMgr.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/DeckMgr.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DeckMgr.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DeckMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/DeckMgr.pdb" /machine:I386 /def:".\DeckMgr.def"\
 /out:"$(OUTDIR)/DeckMgr.dll" /implib:"$(OUTDIR)/DeckMgr.lib" 
DEF_FILE= \
	".\DeckMgr.def"
LINK32_OBJS= \
	"$(INTDIR)/DeckMgr.obj" \
	"$(INTDIR)/DeckWalk.obj" \
	"$(INTDIR)/DeckDll.obj" \
	"$(INTDIR)/DeckMgr.res"

"$(OUTDIR)\DeckMgr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DeckMgr - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Deck_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\applic\Debug\Deck_D32.dll"
	-@erase ".\Debug\DeckDll.obj"
	-@erase ".\Debug\DeckWalk.obj"
	-@erase ".\Debug\DeckMgr.obj"
	-@erase ".\Debug\DeckMgr.res"
	-@erase "..\applic\Debug\Deck_D32.ilk"
	-@erase "..\applic\Debug\Deck_D32.lib"
	-@erase "..\applic\Debug\Deck_D32.exp"
	-@erase ".\Debug\Deck_D32.pdb"
	-@erase ".\Debug\Deck_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/DeckMgr.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/DeckMgr.pch" /YX"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/DeckMgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DeckMgr.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Spec_D32.lib Mesh_d32.lib Elem_D32.lib OMgr_D32.lib Elem_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib Dr3D_D32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug/Deck_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/Deck_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Spec_D32.lib Mesh_d32.lib Elem_D32.lib OMgr_D32.lib Elem_D32.lib\
 OGen_D32.lib Supp_D32.lib StaL_D32.lib Dr3D_D32.lib /nologo /subsystem:windows\
 /dll /incremental:yes /pdb:"$(OUTDIR)/Deck_D32.pdb"\
 /map:"$(INTDIR)/Deck_D32.map" /debug /machine:I386 /def:".\DeckMgr.def"\
 /out:"d:\drgraf4_0\applic\Debug/Deck_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/Deck_D32.lib" 
DEF_FILE= \
	".\DeckMgr.def"
LINK32_OBJS= \
	"$(INTDIR)/DeckDll.obj" \
	"$(INTDIR)/DeckWalk.obj" \
	"$(INTDIR)/DeckMgr.obj" \
	"$(INTDIR)/DeckMgr.res"

"$(OUTDIR)\Deck_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DeckMgr - Win32 Release"
# Name "DeckMgr - Win32 Debug"

!IF  "$(CFG)" == "DeckMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DeckMgr - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\DeckMgr.def

!IF  "$(CFG)" == "DeckMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DeckMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DeckMgr.rc
DEP_RSC_DECKM=\
	".\res\DeckMgr.rc2"\
	

!IF  "$(CFG)" == "DeckMgr - Win32 Release"


"$(INTDIR)\DeckMgr.res" : $(SOURCE) $(DEP_RSC_DECKM) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "DeckMgr - Win32 Debug"


"$(INTDIR)\DeckMgr.res" : $(SOURCE) $(DEP_RSC_DECKM) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DeckMgr.h

!IF  "$(CFG)" == "DeckMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DeckMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DeckMgr.cpp
DEP_CPP_DECKMG=\
	".\StdAfx.h"\
	".\DeckDll.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_SpeL.h"\
	{$(INCLUDE)}"\Def_DynL.h"\
	".\DeckWalk.h"\
	{$(INCLUDE)}"\DeckMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

"$(INTDIR)\DeckMgr.obj" : $(SOURCE) $(DEP_CPP_DECKMG) "$(INTDIR)"\
 "$(INTDIR)\DeckMgr.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DeckDll.h

!IF  "$(CFG)" == "DeckMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DeckMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DeckDll.cpp
DEP_CPP_DECKD=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\DmgrDll.h"\
	

"$(INTDIR)\DeckDll.obj" : $(SOURCE) $(DEP_CPP_DECKD) "$(INTDIR)"\
 "$(INTDIR)\DeckMgr.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DeckWalk.h

!IF  "$(CFG)" == "DeckMgr - Win32 Release"

!ELSEIF  "$(CFG)" == "DeckMgr - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DeckWalk.cpp
DEP_CPP_DECKW=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\DrMesh2D.h"\
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\DrEdge.h"\
	".\DeckWalk.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\..\GenObjs\Triangle.h"\
	".\..\GenObjs\DrCurve.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	".\..\MeshObj\FaceInfo.h"\
	

"$(INTDIR)\DeckWalk.obj" : $(SOURCE) $(DEP_CPP_DECKW) "$(INTDIR)"\
 "$(INTDIR)\DeckMgr.pch"


# End Source File
# End Target
# End Project
################################################################################
