# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=MMgrM3D - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MMgrM3D - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MMgrM3D - Win32 Release" && "$(CFG)" !=\
 "MMgrM3D - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMgrM3D.mak" CFG="MMgrM3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MMgrM3D - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MMgrM3D - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "MMgrM3D - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "MMgrM3D - Win32 Release"

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

ALL : "$(OUTDIR)\MMgrM3D.dll"

CLEAN : 
	-@erase ".\Release\MMgrM3D.dll"
	-@erase ".\Release\MM3DMgr.obj"
	-@erase ".\Release\MMgrM3D.pch"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\dlg_O3DI.obj"
	-@erase ".\Release\dlg_spnO.obj"
	-@erase ".\Release\MI_OSPN.obj"
	-@erase ".\Release\MM3Ddll.obj"
	-@erase ".\Release\MM3DMgr.res"
	-@erase ".\Release\MMgrM3D.lib"
	-@erase ".\Release\MMgrM3D.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/MMgrM3D.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MM3DMgr.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrM3D.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/MMgrM3D.pdb" /machine:I386 /def:".\MMgrM3D.def"\
 /out:"$(OUTDIR)/MMgrM3D.dll" /implib:"$(OUTDIR)/MMgrM3D.lib" 
DEF_FILE= \
	".\MMgrM3D.def"
LINK32_OBJS= \
	".\Release\MM3DMgr.obj" \
	".\Release\StdAfx.obj" \
	".\Release\dlg_O3DI.obj" \
	".\Release\dlg_spnO.obj" \
	".\Release\MI_OSPN.obj" \
	".\Release\MM3Ddll.obj" \
	".\Release\MM3DMgr.res"

"$(OUTDIR)\MMgrM3D.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MMgrM3D - Win32 Debug"

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

ALL : "$(OUTDIR)\MM3D_D32.dll" ".\Debug\MMgrM3D.pch"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\MMgrM3D.pch"
	-@erase "..\applic\Debug\MM3D_D32.dll"
	-@erase ".\Debug\MM3DMgr.obj"
	-@erase ".\Debug\dlg_spnO.obj"
	-@erase ".\Debug\dlg_O3DI.obj"
	-@erase ".\Debug\MI_OSPN.obj"
	-@erase ".\Debug\MM3Ddll.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\MMgrM3D.res"
	-@erase "..\applic\Debug\MM3D_D32.lib"
	-@erase "..\applic\Debug\MM3D_D32.exp"
	-@erase ".\Debug\MM3D_D32.pdb"
	-@erase ".\Debug\MM3D_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/MMgrM3D.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/MMgrM3D.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /fo"Debug/MMgrM3D.res" /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MMgrM3D.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrM3D.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Elem_D32.lib OGen_D32.lib Dr3D_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug/MM3D_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/MM3D_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Draw_D32.lib Elem_D32.lib OGen_D32.lib\
 Dr3D_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_D32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/MM3D_D32.pdb"\
 /map:"$(INTDIR)/MM3D_D32.map" /debug /machine:I386 /def:".\MMgrM3D.def"\
 /out:"d:\drgraf4_0\applic\Debug/MM3D_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/MM3D_D32.lib" 
DEF_FILE= \
	".\MMgrM3D.def"
LINK32_OBJS= \
	".\Debug\MM3DMgr.obj" \
	".\Debug\dlg_spnO.obj" \
	".\Debug\dlg_O3DI.obj" \
	".\Debug\MI_OSPN.obj" \
	".\Debug\MM3Ddll.obj" \
	".\Debug\StdAfx.obj" \
	".\Debug\MMgrM3D.res"

"$(OUTDIR)\MM3D_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MMgrM3D - Win32 Release"
# Name "MMgrM3D - Win32 Debug"

!IF  "$(CFG)" == "MMgrM3D - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrM3D - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "MMgrM3D - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/MMgrM3D.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MMgrM3D.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MMgrM3D - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/MMgrM3D.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MMgrM3D.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MM3Ddll.h

!IF  "$(CFG)" == "MMgrM3D - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrM3D - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MM3Ddll.cpp
DEP_CPP_MM3DD=\
	".\StdAfx.h"\
	".\MM3Ddll.h"\
	

"$(INTDIR)\MM3Ddll.obj" : $(SOURCE) $(DEP_CPP_MM3DD) "$(INTDIR)"\
 "$(INTDIR)\MMgrM3D.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MM3DMgr.h

!IF  "$(CFG)" == "MMgrM3D - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrM3D - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MM3DMgr.cpp
DEP_CPP_MM3DM=\
	".\StdAfx.h"\
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
	".\dlg_spnO.h"\
	".\MM3Ddll.h"\
	".\MM3DMgr.h"\
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
	".\..\GLOBHEAD\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	

"$(INTDIR)\MM3DMgr.obj" : $(SOURCE) $(DEP_CPP_MM3DM) "$(INTDIR)"\
 "$(INTDIR)\MMgrM3D.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MM3DMgr.rc

!IF  "$(CFG)" == "MMgrM3D - Win32 Release"

DEP_RSC_MM3DMG=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	".\..\Applic\Res\Ico_pipe.ico"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MNodRsrc.h"\
	".\MDlgrsrc.hm"\
	

"$(INTDIR)\MM3DMgr.res" : $(SOURCE) $(DEP_RSC_MM3DMG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "MMgrM3D - Win32 Debug"

DEP_RSC_MM3DMG=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	".\..\Applic\Res\Ico_pipe.ico"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MNodRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\MDlgrsrc.hm"\
	

"$(INTDIR)\MMgrM3D.res" : $(SOURCE) $(DEP_RSC_MM3DMG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_spnO.h

!IF  "$(CFG)" == "MMgrM3D - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrM3D - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_spnO.cpp
DEP_CPP_DLG_S=\
	".\StdAfx.h"\
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
	{$(INCLUDE)}"\Drobj3d.h"\
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
	".\dlg_spnO.h"\
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
	{$(INCLUDE)}"\MCurRsrc.h"\
	

"$(INTDIR)\dlg_spnO.obj" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"\
 "$(INTDIR)\MMgrM3D.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_O3DI.h

!IF  "$(CFG)" == "MMgrM3D - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrM3D - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_O3DI.cpp
DEP_CPP_DLG_O=\
	".\StdAfx.h"\
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
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\dlg_O3DI.h"\
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
	{$(INCLUDE)}"\Drobj3d.h"\
	

"$(INTDIR)\dlg_O3DI.obj" : $(SOURCE) $(DEP_CPP_DLG_O) "$(INTDIR)"\
 "$(INTDIR)\MMgrM3D.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_OSPN.h

!IF  "$(CFG)" == "MMgrM3D - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrM3D - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_OSPN.cpp
DEP_CPP_MI_OS=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	".\MM3DMgr.h"\
	".\dlg_spnO.h"\
	".\Mi_OSPN.h"\
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
	{$(INCLUDE)}"\Drobj3d.h"\
	{$(INCLUDE)}"\Mi_SSPN.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Mi_PSPN.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mi_CSPN.h"\
	{$(INCLUDE)}"\Mi_NSPN.h"\
	

"$(INTDIR)\MI_OSPN.obj" : $(SOURCE) $(DEP_CPP_MI_OS) "$(INTDIR)"\
 "$(INTDIR)\MMgrM3D.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MMgrM3D.def

!IF  "$(CFG)" == "MMgrM3D - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrM3D - Win32 Debug"

# PROP Exclude_From_Build 0

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
