# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=MMgrSupp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MMgrSupp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MMgrSupp - Win32 Release" && "$(CFG)" !=\
 "MMgrSupp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MMgrSupp.mak" CFG="MMgrSupp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MMgrSupp - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MMgrSupp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "MMgrSupp - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "MMgrSupp - Win32 Release"

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

ALL : "$(OUTDIR)\MMgrSupp.dll"

CLEAN : 
	-@erase ".\Release\MMgrSupp.dll"
	-@erase ".\Release\MSupdll.obj"
	-@erase ".\Release\Mi_LSupp.obj"
	-@erase ".\Release\dlg_SupA.obj"
	-@erase ".\Release\dlg_supE.obj"
	-@erase ".\Release\MSupMgr.obj"
	-@erase ".\Release\dlg_Supi.obj"
	-@erase ".\Release\SuppMgr.res"
	-@erase ".\Release\MMgrSupp.lib"
	-@erase ".\Release\MMgrSupp.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/MMgrSupp.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SuppMgr.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrSupp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/MMgrSupp.pdb" /machine:I386 /def:".\MSup_d.def"\
 /out:"$(OUTDIR)/MMgrSupp.dll" /implib:"$(OUTDIR)/MMgrSupp.lib" 
DEF_FILE= \
	".\MSup_d.def"
LINK32_OBJS= \
	".\Release\MSupdll.obj" \
	".\Release\Mi_LSupp.obj" \
	".\Release\dlg_SupA.obj" \
	".\Release\dlg_supE.obj" \
	".\Release\MSupMgr.obj" \
	".\Release\dlg_Supi.obj" \
	".\Release\SuppMgr.res"

"$(OUTDIR)\MMgrSupp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MMgrSupp - Win32 Debug"

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

ALL : "$(OUTDIR)\MSup_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\Applic\Debug\MSup_D32.dll"
	-@erase ".\Debug\dlg_Supi.obj"
	-@erase ".\Debug\MSupMgr.obj"
	-@erase ".\Debug\Mi_LSupp.obj"
	-@erase ".\Debug\dlg_SupA.obj"
	-@erase ".\Debug\MSupdll.obj"
	-@erase ".\Debug\dlg_supE.obj"
	-@erase ".\Debug\SuppMgr.res"
	-@erase "..\Applic\Debug\MSup_D32.lib"
	-@erase "..\Applic\Debug\MSup_D32.exp"
	-@erase ".\Debug\MSup_D32.pdb"
	-@erase ".\Debug\MSup_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/MMgrSupp.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXEXT" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MMgrSupp.pch"\
 /YX"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/SuppMgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MMgrSupp.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib Supp_D32.lib Dr3D_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_d32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /out:"d:\drGraf4_0\Applic\Debug/MSup_D32.dll" /implib:"d:\drGraf4_0\Applic\Debug/MSup_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib\
 Supp_D32.lib Dr3D_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_d32.lib\
 /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/MSup_D32.pdb"\
 /map:"$(INTDIR)/MSup_D32.map" /debug /machine:I386 /def:".\MSup_d.def"\
 /out:"d:\drGraf4_0\Applic\Debug/MSup_D32.dll"\
 /implib:"d:\drGraf4_0\Applic\Debug/MSup_D32.lib" 
DEF_FILE= \
	".\MSup_d.def"
LINK32_OBJS= \
	".\Debug\dlg_Supi.obj" \
	".\Debug\MSupMgr.obj" \
	".\Debug\Mi_LSupp.obj" \
	".\Debug\dlg_SupA.obj" \
	".\Debug\MSupdll.obj" \
	".\Debug\dlg_supE.obj" \
	".\Debug\SuppMgr.res"

"$(OUTDIR)\MSup_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MMgrSupp - Win32 Release"
# Name "MMgrSupp - Win32 Debug"

!IF  "$(CFG)" == "MMgrSupp - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSupp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Mi_LSupp.cpp
DEP_CPP_MI_LS=\
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
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	".\Mi_LSupp.h"\
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
	{$(INCLUDE)}"\Unit.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Glb_Supp.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Triangle.h"\
	

!IF  "$(CFG)" == "MMgrSupp - Win32 Release"


"$(INTDIR)\Mi_LSupp.obj" : $(SOURCE) $(DEP_CPP_MI_LS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "MMgrSupp - Win32 Debug"


"$(INTDIR)\Mi_LSupp.obj" : $(SOURCE) $(DEP_CPP_MI_LS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSupdll.cpp
DEP_CPP_MSUPD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MSupdll.h"\
	

"$(INTDIR)\MSupdll.obj" : $(SOURCE) $(DEP_CPP_MSUPD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSup_d.def

!IF  "$(CFG)" == "MMgrSupp - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSupp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSupRsrc.h

!IF  "$(CFG)" == "MMgrSupp - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSupp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSupMgr.h

!IF  "$(CFG)" == "MMgrSupp - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSupp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSupMgr.cpp
DEP_CPP_MSUPM=\
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
	{$(INCLUDE)}"\DrLinSup.h"\
	".\dlg_supE.h"\
	".\MSupdll.h"\
	".\MSupRsrc.h"\
	".\MSupMgr.h"\
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
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	

"$(INTDIR)\MSupMgr.obj" : $(SOURCE) $(DEP_CPP_MSUPM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SuppMgr.rc

!IF  "$(CFG)" == "MMgrSupp - Win32 Release"

DEP_RSC_SUPPM=\
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
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\MSupRsrc.hm"\
	

"$(INTDIR)\SuppMgr.res" : $(SOURCE) $(DEP_RSC_SUPPM) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/SuppMgr.res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "MMgrSupp - Win32 Debug"

DEP_RSC_SUPPM=\
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
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\MSupRsrc.h"\
	".\MSupRsrc.hm"\
	
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409

"$(INTDIR)\SuppMgr.res" : $(SOURCE) $(DEP_RSC_SUPPM) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/SuppMgr.res" /d "_DEBUG" /d "_AFXDLL"\
 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_Supi.h

!IF  "$(CFG)" == "MMgrSupp - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSupp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_Supi.cpp
DEP_CPP_DLG_S=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MSupdll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\Def_Lims.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\dlg_SupA.h"\
	".\dlg_Supi.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\MSupRsrc.h"\
	

"$(INTDIR)\dlg_Supi.obj" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_SupA.h

!IF  "$(CFG)" == "MMgrSupp - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSupp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_SupA.cpp
DEP_CPP_DLG_SU=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MSupdll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	".\dlg_SupA.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	".\MSupRsrc.h"\
	

"$(INTDIR)\dlg_SupA.obj" : $(SOURCE) $(DEP_CPP_DLG_SU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_supE.h

!IF  "$(CFG)" == "MMgrSupp - Win32 Release"

!ELSEIF  "$(CFG)" == "MMgrSupp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_supE.cpp
DEP_CPP_DLG_SUP=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MSupdll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	".\dlg_supE.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_Supp.h"\
	{$(INCLUDE)}"\DrLinSup.h"\
	".\MSupRsrc.h"\
	{$(INCLUDE)}"\Str_Supp.h"\
	

"$(INTDIR)\dlg_supE.obj" : $(SOURCE) $(DEP_CPP_DLG_SUP) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
