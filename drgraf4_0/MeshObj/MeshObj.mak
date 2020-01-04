# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=MeshObj - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MeshObj - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MeshObj - Win32 Release" && "$(CFG)" !=\
 "MeshObj - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MeshObj.mak" CFG="MeshObj - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MeshObj - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MeshObj - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "MeshObj - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "MeshObj - Win32 Release"

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

ALL : "$(OUTDIR)\MeshObj.dll"

CLEAN : 
	-@erase ".\Release\MeshObj.dll"
	-@erase ".\Release\DrEdge.obj"
	-@erase ".\Release\MeshObj.pch"
	-@erase ".\Release\DrMesh1D.obj"
	-@erase ".\Release\DrFE3D.obj"
	-@erase ".\Release\DrFE2D.obj"
	-@erase ".\Release\FaceInfo.obj"
	-@erase ".\Release\EdgeInfo.obj"
	-@erase ".\Release\DrMesh3D.obj"
	-@erase ".\Release\Mesh_dll.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\DrFE1D.obj"
	-@erase ".\Release\DrMesh2D.obj"
	-@erase ".\Release\DrFace.obj"
	-@erase ".\Release\DrFE0D.obj"
	-@erase ".\Release\MeshObj.res"
	-@erase ".\Release\Drprof_1.obj"
	-@erase ".\Release\MeshObj.lib"
	-@erase ".\Release\MeshObj.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/MeshObj.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MeshObj.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MeshObj.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/MeshObj.pdb" /machine:I386 /def:".\MeshObj.def"\
 /out:"$(OUTDIR)/MeshObj.dll" /implib:"$(OUTDIR)/MeshObj.lib" 
DEF_FILE= \
	".\MeshObj.def"
LINK32_OBJS= \
	".\Release\DrEdge.obj" \
	".\Release\DrMesh1D.obj" \
	".\Release\DrFE3D.obj" \
	".\Release\DrFE2D.obj" \
	".\Release\FaceInfo.obj" \
	".\Release\EdgeInfo.obj" \
	".\Release\DrMesh3D.obj" \
	".\Release\Mesh_dll.obj" \
	".\Release\StdAfx.obj" \
	".\Release\DrFE1D.obj" \
	".\Release\DrMesh2D.obj" \
	".\Release\DrFace.obj" \
	".\Release\DrFE0D.obj" \
	".\Release\Drprof_1.obj" \
	".\Release\MeshObj.res"

"$(OUTDIR)\MeshObj.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

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

ALL : "$(OUTDIR)\Mesh_D32.dll" ".\Debug\MeshObj.pch"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\MeshObj.pch"
	-@erase "..\applic\Debug\Mesh_D32.dll"
	-@erase ".\Debug\DrMesh1D.obj"
	-@erase ".\Debug\DrFE1D.obj"
	-@erase ".\Debug\DrFace.obj"
	-@erase ".\Debug\DrFE0D.obj"
	-@erase ".\Debug\FaceInfo.obj"
	-@erase ".\Debug\DrEdge.obj"
	-@erase ".\Debug\DrMesh3D.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\DrFE3D.obj"
	-@erase ".\Debug\DrMesh2D.obj"
	-@erase ".\Debug\DrFE2D.obj"
	-@erase ".\Debug\EdgeInfo.obj"
	-@erase ".\Debug\Mesh_dll.obj"
	-@erase ".\Debug\MeshObj.res"
	-@erase ".\Debug\Drprof_1.obj"
	-@erase "..\applic\Debug\Mesh_D32.lib"
	-@erase "..\applic\Debug\Mesh_D32.exp"
	-@erase ".\Debug\Mesh_D32.pdb"
	-@erase ".\Debug\Mesh_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/MeshObj.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_MBCS" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXEXT" /D "_MBCS" /Fp"$(INTDIR)/MeshObj.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MeshObj.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MeshObj.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib OGen_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug/Mesh_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/Mesh_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Dr3D_D32.lib Spec_D32.lib OGen_D32.lib /nologo /subsystem:windows\
 /dll /incremental:no /pdb:"$(OUTDIR)/Mesh_D32.pdb"\
 /map:"$(INTDIR)/Mesh_D32.map" /debug /machine:I386 /def:".\MeshObj.def"\
 /out:"d:\drgraf4_0\applic\Debug/Mesh_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/Mesh_D32.lib" 
DEF_FILE= \
	".\MeshObj.def"
LINK32_OBJS= \
	".\Debug\DrMesh1D.obj" \
	".\Debug\DrFE1D.obj" \
	".\Debug\DrFace.obj" \
	".\Debug\DrFE0D.obj" \
	".\Debug\FaceInfo.obj" \
	".\Debug\DrEdge.obj" \
	".\Debug\DrMesh3D.obj" \
	".\Debug\StdAfx.obj" \
	".\Debug\DrFE3D.obj" \
	".\Debug\DrMesh2D.obj" \
	".\Debug\DrFE2D.obj" \
	".\Debug\EdgeInfo.obj" \
	".\Debug\Mesh_dll.obj" \
	".\Debug\Drprof_1.obj" \
	".\Debug\MeshObj.res"

"$(OUTDIR)\Mesh_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MeshObj - Win32 Release"
# Name "MeshObj - Win32 Debug"

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshObj.def

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MeshObj - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/MeshObj.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MeshObj.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXEXT" /D "_MBCS" /Fp"$(INTDIR)/MeshObj.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MeshObj.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshObj.rc
DEP_RSC_MESHO=\
	".\res\MeshObj.rc2"\
	

"$(INTDIR)\MeshObj.res" : $(SOURCE) $(DEP_RSC_MESHO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mesh_dll.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mesh_dll.cpp
DEP_CPP_MESH_=\
	".\StdAfx.h"\
	".\Mesh_dll.h"\
	{$(INCLUDE)}"\Glb_elem.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	

"$(INTDIR)\Mesh_dll.obj" : $(SOURCE) $(DEP_CPP_MESH_) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrFE3D.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrFE0D.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrFE1D.cpp
DEP_CPP_DRFE1=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\DrFE0D.h"\
	".\DrFE1D.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	

"$(INTDIR)\DrFE1D.obj" : $(SOURCE) $(DEP_CPP_DRFE1) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrFE1D.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrFE2D.cpp
DEP_CPP_DRFE2=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\DrFE0D.h"\
	".\DrFE2D.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	

"$(INTDIR)\DrFE2D.obj" : $(SOURCE) $(DEP_CPP_DRFE2) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrFE2D.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrFE3D.cpp
DEP_CPP_DRFE3=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\DrFE0D.h"\
	".\DrFE3D.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	

"$(INTDIR)\DrFE3D.obj" : $(SOURCE) $(DEP_CPP_DRFE3) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrFE0D.cpp
DEP_CPP_DRFE0=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\DrFE2D.h"\
	".\DrFE0D.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\DrFE0D.obj" : $(SOURCE) $(DEP_CPP_DRFE0) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrMesh3D.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrMesh1D.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrMesh2D.cpp
DEP_CPP_DRMES=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\DrFE0D.h"\
	".\DrFE1D.h"\
	".\DrFE2D.h"\
	".\DrMesh2D.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\DrMesh2D.obj" : $(SOURCE) $(DEP_CPP_DRMES) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrMesh2D.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrMesh3D.cpp
DEP_CPP_DRMESH=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\DrFE0D.h"\
	".\DrFE1D.h"\
	".\DrFE2D.h"\
	".\DrFE3D.h"\
	".\DrMesh3D.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\DrMesh3D.obj" : $(SOURCE) $(DEP_CPP_DRMESH) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrMesh1D.cpp
DEP_CPP_DRMESH1=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\DrFE0D.h"\
	".\DrFE1D.h"\
	".\DrMesh1D.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\DrMesh1D.obj" : $(SOURCE) $(DEP_CPP_DRMESH1) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrEdge.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrEdge.cpp
DEP_CPP_DREDG=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	".\DrFE0D.h"\
	".\DrEdge.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\FaceInfo.h"\
	

"$(INTDIR)\DrEdge.obj" : $(SOURCE) $(DEP_CPP_DREDG) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\FaceInfo.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FaceInfo.cpp
DEP_CPP_FACEI=\
	".\StdAfx.h"\
	".\FaceInfo.h"\
	

"$(INTDIR)\FaceInfo.obj" : $(SOURCE) $(DEP_CPP_FACEI) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EdgeInfo.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EdgeInfo.cpp
DEP_CPP_EDGEI=\
	".\StdAfx.h"\
	".\EdgeInfo.h"\
	

"$(INTDIR)\EdgeInfo.obj" : $(SOURCE) $(DEP_CPP_EDGEI) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrFace.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DrFace.cpp
DEP_CPP_DRFAC=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	".\DrFace.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	

"$(INTDIR)\DrFace.obj" : $(SOURCE) $(DEP_CPP_DRFAC) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drprof_1.h

!IF  "$(CFG)" == "MeshObj - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshObj - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drprof_1.cpp
DEP_CPP_DRPRO=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Ext_Cur.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	".\..\SPECIALS\MatObj.h"\
	{$(INCLUDE)}"\DrProf_C.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\Drprof_1.obj" : $(SOURCE) $(DEP_CPP_DRPRO) "$(INTDIR)"\
 "$(INTDIR)\MeshObj.pch"


# End Source File
# End Target
# End Project
################################################################################
