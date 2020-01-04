# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=MMgrNod - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MMgrNod - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MMgrNod - Win32 Release" && "$(CFG)" !=\
 "MMgrNod - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMgrNod.mak" CFG="MMgrNod - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MMgrNod - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MMgrNod - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "MMgrNod - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

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

ALL : "$(OUTDIR)\MMgrNod.dll"

CLEAN : 
	-@erase ".\Release\MMgrNod.dll"
	-@erase ".\Release\dlg_nodi.obj"
	-@erase ".\Release\MNoddll.obj"
	-@erase ".\Release\MI_NSPN.obj"
	-@erase ".\Release\dlg_CrOi.obj"
	-@erase ".\Release\Dlg_LSym.obj"
	-@erase ".\Release\dlg_enoA.obj"
	-@erase ".\Release\Dlg_LALL.obj"
	-@erase ".\Release\Dlg_LSyT.obj"
	-@erase ".\Release\Dlg_SpnN.obj"
	-@erase ".\Release\MNodMgr.obj"
	-@erase ".\Release\Mi_GangN.obj"
	-@erase ".\Release\dlg_ENod.obj"
	-@erase ".\Release\Dlg_LSy3.obj"
	-@erase ".\Release\Dlg_node.obj"
	-@erase ".\Release\MNodMgr.res"
	-@erase ".\Release\MMgrNod.lib"
	-@erase ".\Release\MMgrNod.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/MMgrNod.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MNodMgr.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrNod.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/MMgrNod.pdb" /machine:I386 /def:".\MNodMgr.def"\
 /out:"$(OUTDIR)/MMgrNod.dll" /implib:"$(OUTDIR)/MMgrNod.lib" 
DEF_FILE= \
	".\MNodMgr.def"
LINK32_OBJS= \
	".\Release\dlg_nodi.obj" \
	".\Release\MNoddll.obj" \
	".\Release\MI_NSPN.obj" \
	".\Release\dlg_CrOi.obj" \
	".\Release\Dlg_LSym.obj" \
	".\Release\dlg_enoA.obj" \
	".\Release\Dlg_LALL.obj" \
	".\Release\Dlg_LSyT.obj" \
	".\Release\Dlg_SpnN.obj" \
	".\Release\MNodMgr.obj" \
	".\Release\Mi_GangN.obj" \
	".\Release\dlg_ENod.obj" \
	".\Release\Dlg_LSy3.obj" \
	".\Release\Dlg_node.obj" \
	".\Release\MNodMgr.res"

"$(OUTDIR)\MMgrNod.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

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

ALL : "$(OUTDIR)\MNod_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\applic\Debug\MNod_d32.dll"
	-@erase ".\Debug\Mi_GangN.obj"
	-@erase ".\Debug\MNoddll.obj"
	-@erase ".\Debug\MI_NSPN.obj"
	-@erase ".\Debug\Dlg_node.obj"
	-@erase ".\Debug\dlg_enoA.obj"
	-@erase ".\Debug\dlg_nodi.obj"
	-@erase ".\Debug\Dlg_LSyT.obj"
	-@erase ".\Debug\dlg_ENod.obj"
	-@erase ".\Debug\Dlg_LSy3.obj"
	-@erase ".\Debug\dlg_CrOi.obj"
	-@erase ".\Debug\MNodMgr.obj"
	-@erase ".\Debug\Dlg_LSym.obj"
	-@erase ".\Debug\Dlg_LALL.obj"
	-@erase ".\Debug\Dlg_SpnN.obj"
	-@erase ".\Debug\MNodMgr.res"
	-@erase "..\applic\Debug\MNod_d32.lib"
	-@erase "..\applic\Debug\MNod_d32.exp"
	-@erase ".\Debug\MNod_d32.pdb"
	-@erase ".\Debug\MNod_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /I "Debug/"
F90_PROJ=/I "Debug/" /Fo"Debug/" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/MMgrNod.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MNodMgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrNod.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Draw_D32.lib Elem_D32.lib OGen_D32.lib Dr3D_D32.lib /nologo /version:1.0 /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug\MNod_d32.dll" /implib:"d:\drgraf4_0\applic\Debug/MNod_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Draw_D32.lib Elem_D32.lib OGen_D32.lib\
 Dr3D_D32.lib /nologo /version:1.0 /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/MNod_d32.pdb" /map:"$(INTDIR)/MNod_d32.map" /debug\
 /machine:I386 /def:".\MNodMgr.def"\
 /out:"d:\drgraf4_0\applic\Debug\MNod_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/MNod_d32.lib" 
DEF_FILE= \
	".\MNodMgr.def"
LINK32_OBJS= \
	".\Debug\Mi_GangN.obj" \
	".\Debug\MNoddll.obj" \
	".\Debug\MI_NSPN.obj" \
	".\Debug\Dlg_node.obj" \
	".\Debug\dlg_enoA.obj" \
	".\Debug\dlg_nodi.obj" \
	".\Debug\Dlg_LSyT.obj" \
	".\Debug\dlg_ENod.obj" \
	".\Debug\Dlg_LSy3.obj" \
	".\Debug\dlg_CrOi.obj" \
	".\Debug\MNodMgr.obj" \
	".\Debug\Dlg_LSym.obj" \
	".\Debug\Dlg_LALL.obj" \
	".\Debug\Dlg_SpnN.obj" \
	".\Debug\MNodMgr.res"

"$(OUTDIR)\MNod_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MMgrNod - Win32 Release"
# Name "MMgrNod - Win32 Debug"

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MNodRsrc.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_enoA.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_node.cpp
DEP_CPP_DLG_N=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Drfont.h"\
	".\CommRsrc.h"\
	".\Dlg_node.h"\
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
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Unit.h"\
	".\..\GRAFMGR\stdafx.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

!IF  "$(CFG)" == "MMgrNod - Win32 Release"


"$(INTDIR)\Dlg_node.obj" : $(SOURCE) $(DEP_CPP_DLG_N) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"


"$(INTDIR)\Dlg_node.obj" : $(SOURCE) $(DEP_CPP_DLG_N) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_node.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_nodi.cpp
DEP_CPP_DLG_NO=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	".\MNoddll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\CommRsrc.h"\
	".\Dlg_node.h"\
	".\dlg_nodi.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	

"$(INTDIR)\dlg_nodi.obj" : $(SOURCE) $(DEP_CPP_DLG_NO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_nodi.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_GangN.cpp
DEP_CPP_MI_GA=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Lims.h"\
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
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
	{$(INCLUDE)}"\Mouse.h"\
	".\Mi_GangN.h"\
	".\..\APPLIC\aboutbox.h"\
	".\..\APPLIC\Banner.h"\
	".\..\APPLIC\mdib.h"\
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
	{$(INCLUDE)}"\Def_Mous.h"\
	

"$(INTDIR)\Mi_GangN.obj" : $(SOURCE) $(DEP_CPP_MI_GA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_GangN.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MNoddll.cpp
DEP_CPP_MNODD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MNoddll.h"\
	

"$(INTDIR)\MNoddll.obj" : $(SOURCE) $(DEP_CPP_MNODD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MNoddll.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MNodMgr.cpp
DEP_CPP_MNODM=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	".\MNoddll.h"\
	{$(INCLUDE)}"\Dlg_LSyT.h"\
	".\dlg_spnn.h"\
	".\dlg_enod.h"\
	".\MNodmgr.h"\
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
	

"$(INTDIR)\MNodMgr.obj" : $(SOURCE) $(DEP_CPP_MNODM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MNodmgr.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MNodMgr.rc
DEP_RSC_MNODMG=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	".\..\Applic\Res\Ico_pipe.ico"\
	".\CommRsrc.h"\
	".\MNodRsrc.hm"\
	

"$(INTDIR)\MNodMgr.res" : $(SOURCE) $(DEP_RSC_MNODMG) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_enoA.cpp
DEP_CPP_DLG_E=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Drfont.h"\
	".\dlg_enoA.h"\
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
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\dlg_enoA.obj" : $(SOURCE) $(DEP_CPP_DLG_E) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_enod.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_ENod.cpp
DEP_CPP_DLG_EN=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	{$(INCLUDE)}"\Drfont.h"\
	".\CommRsrc.h"\
	".\dlg_enoA.h"\
	".\dlg_enod.h"\
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
	{$(INCLUDE)}"\Booleans.h"\
	{$(INCLUDE)}"\Datawind.h"\
	{$(INCLUDE)}"\Hitnet.h"\
	{$(INCLUDE)}"\Patchmnu.h"\
	{$(INCLUDE)}"\Obj3dmnu.h"\
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\dlg_ENod.obj" : $(SOURCE) $(DEP_CPP_DLG_EN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_NSPN.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MI_NSPN.cpp
DEP_CPP_MI_NS=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	".\MNodmgr.h"\
	".\Mi_GangN.h"\
	".\dlg_spnn.h"\
	".\Mi_NSPN.h"\
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
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drobj3d.h"\
	".\..\GenObjs\Triangle.h"\
	

"$(INTDIR)\MI_NSPN.obj" : $(SOURCE) $(DEP_CPP_MI_NS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_spnn.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_SpnN.cpp
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
	{$(INCLUDE)}"\Drnode.h"\
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
	".\dlg_spnn.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	

"$(INTDIR)\Dlg_SpnN.obj" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LSyT.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LALL.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LSy3.cpp
DEP_CPP_DLG_L=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
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
	".\CommRsrc.h"\
	{$(INCLUDE)}"\Dlg_LSy3.h"\
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
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\Dlg_LSy3.obj" : $(SOURCE) $(DEP_CPP_DLG_L) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LSy3.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LSym.cpp
DEP_CPP_DLG_LS=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
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
	{$(INCLUDE)}"\Dlg_LSym.h"\
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
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\Dlg_LSym.obj" : $(SOURCE) $(DEP_CPP_DLG_LS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LSym.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LSyT.cpp
DEP_CPP_DLG_LSY=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Dlg_LSyT.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	

"$(INTDIR)\Dlg_LSyT.obj" : $(SOURCE) $(DEP_CPP_DLG_LSY) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_LALL.cpp
DEP_CPP_DLG_LA=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
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
	{$(INCLUDE)}"\Dlg_LALL.h"\
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
	".\..\GenObjs\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	

"$(INTDIR)\Dlg_LALL.obj" : $(SOURCE) $(DEP_CPP_DLG_LA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MNodMgr.def

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_croi.h

!IF  "$(CFG)" == "MMgrNod - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrNod - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_CrOi.cpp
DEP_CPP_DLG_C=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MNoddll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	".\CommRsrc.h"\
	".\dlg_croi.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	

"$(INTDIR)\dlg_CrOi.obj" : $(SOURCE) $(DEP_CPP_DLG_C) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
