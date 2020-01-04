# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Edlg_d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Edlg_d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Edlg_d - Win32 Release" && "$(CFG)" != "Edlg_d - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Edlg_d32.mak" CFG="Edlg_d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Edlg_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Edlg_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Edlg_d - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

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

ALL : "$(OUTDIR)\Edlg_d32.dll" "$(OUTDIR)\Edlg_d32.bsc"

CLEAN : 
	-@erase ".\Release\Edlg_d32.bsc"
	-@erase ".\Release\dlg_FE1i.sbr"
	-@erase ".\Release\Edlgdll.sbr"
	-@erase ".\Release\dlg_fe0i.sbr"
	-@erase ".\Release\Edlgmgr.sbr"
	-@erase ".\Release\dlg_fe2i.sbr"
	-@erase ".\Release\Edlg_d32.dll"
	-@erase ".\Release\dlg_FE1i.obj"
	-@erase ".\Release\Edlgdll.obj"
	-@erase ".\Release\dlg_fe0i.obj"
	-@erase ".\Release\Edlgmgr.obj"
	-@erase ".\Release\dlg_fe2i.obj"
	-@erase ".\Release\Elem_dlg.res"
	-@erase ".\Release\Edlg_d32.lib"
	-@erase ".\Release\Edlg_d32.exp"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Edlg_d32.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Elem_dlg.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Edlg_d32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/dlg_FE1i.sbr" \
	"$(INTDIR)/Edlgdll.sbr" \
	"$(INTDIR)/dlg_fe0i.sbr" \
	"$(INTDIR)/Edlgmgr.sbr" \
	"$(INTDIR)/dlg_fe2i.sbr"

"$(OUTDIR)\Edlg_d32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
LINK32_FLAGS=oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/Edlg_d32.pdb" /map:"FULL" /machine:IX86\
 /def:".\Edlg_d.def" /out:"$(OUTDIR)/Edlg_d32.dll"\
 /implib:"$(OUTDIR)/Edlg_d32.lib" 
DEF_FILE= \
	".\Edlg_d.def"
LINK32_OBJS= \
	"$(INTDIR)/dlg_FE1i.obj" \
	"$(INTDIR)/Edlgdll.obj" \
	"$(INTDIR)/dlg_fe0i.obj" \
	"$(INTDIR)/Edlgmgr.obj" \
	"$(INTDIR)/dlg_fe2i.obj" \
	"$(INTDIR)/Elem_dlg.res"

"$(OUTDIR)\Edlg_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

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

ALL : "$(OUTDIR)\Edlg_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase "..\applic\Debug\Edlg_d32.dll"
	-@erase ".\Debug\Edlgdll.obj"
	-@erase ".\Debug\dlg_fe2i.obj"
	-@erase ".\Debug\Edlgmgr.obj"
	-@erase ".\Debug\dlg_FE1i.obj"
	-@erase ".\Debug\dlg_fe0i.obj"
	-@erase ".\Debug\Elem_dlg.res"
	-@erase "..\applic\Debug\Edlg_d32.lib"
	-@erase "..\applic\Debug\Edlg_d32.exp"
	-@erase ".\Debug\Edlg_d32.pdb"
	-@erase ".\Debug\Edlg_d32..map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Edlg_d32.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Elem_dlg.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Edlg_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 Spec_D.lib OMgr_D.lib Elem_D.lib Draw_D.lib Dr3D_D.lib oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Spec_D32.lib Elem_D32.lib OMgr_D32.lib Draw_D32.lib Dr3D_D32.lib /nologo /subsystem:windows /dll /incremental:no /map:"Debug/Edlg_d32..map" /debug /machine:IX86 /out:"d:\drgraf4_0\applic\Debug\Edlg_d32.dll" /implib:"d:\drgraf4_0\applic\Debug\Edlg_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Spec_D32.lib Elem_D32.lib OMgr_D32.lib Draw_D32.lib Dr3D_D32.lib\
 /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/Edlg_d32.pdb"\
 /map:"$(INTDIR)/Edlg_d32..map" /debug /machine:IX86 /def:".\Edlg_d.def"\
 /out:"d:\drgraf4_0\applic\Debug\Edlg_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug\Edlg_d32.lib" 
DEF_FILE= \
	".\Edlg_d.def"
LINK32_OBJS= \
	"$(INTDIR)/Edlgdll.obj" \
	"$(INTDIR)/dlg_fe2i.obj" \
	"$(INTDIR)/Edlgmgr.obj" \
	"$(INTDIR)/dlg_FE1i.obj" \
	"$(INTDIR)/dlg_fe0i.obj" \
	"$(INTDIR)/Elem_dlg.res"

"$(OUTDIR)\Edlg_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Edlg_d - Win32 Release"
# Name "Edlg_d - Win32 Debug"

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Edlgdll.cpp
DEP_CPP_EDLGD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Edlgdll.h"\
	

!IF  "$(CFG)" == "Edlg_d - Win32 Release"


"$(INTDIR)\Edlgdll.obj" : $(SOURCE) $(DEP_CPP_EDLGD) "$(INTDIR)"

"$(INTDIR)\Edlgdll.sbr" : $(SOURCE) $(DEP_CPP_EDLGD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"


"$(INTDIR)\Edlgdll.obj" : $(SOURCE) $(DEP_CPP_EDLGD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Edlgmgr.cpp
DEP_CPP_EDLGM=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Edlgmgr.h"\
	

!IF  "$(CFG)" == "Edlg_d - Win32 Release"


"$(INTDIR)\Edlgmgr.obj" : $(SOURCE) $(DEP_CPP_EDLGM) "$(INTDIR)"

"$(INTDIR)\Edlgmgr.sbr" : $(SOURCE) $(DEP_CPP_EDLGM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"


"$(INTDIR)\Edlgmgr.obj" : $(SOURCE) $(DEP_CPP_EDLGM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Elem_dlg.rc
DEP_RSC_ELEM_=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	".\..\Applic\Res\Ico_pipe.ico"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\edlgrsrc.hm"\
	

"$(INTDIR)\Elem_dlg.res" : $(SOURCE) $(DEP_RSC_ELEM_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Edlg_d.def

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_fe1i.h

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_FE1i.cpp
DEP_CPP_DLG_F=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Edlgdll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_EInf.h"\
	{$(INCLUDE)}"\Property.h"\
	{$(INCLUDE)}"\Mat_1D.h"\
	{$(INCLUDE)}"\Release.h"\
	{$(INCLUDE)}"\SIndex.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\dlg_fe1i.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\..\GLOBHEAD\Def_IGen.h"\
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
	

!IF  "$(CFG)" == "Edlg_d - Win32 Release"


"$(INTDIR)\dlg_FE1i.obj" : $(SOURCE) $(DEP_CPP_DLG_F) "$(INTDIR)"

"$(INTDIR)\dlg_FE1i.sbr" : $(SOURCE) $(DEP_CPP_DLG_F) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"


"$(INTDIR)\dlg_FE1i.obj" : $(SOURCE) $(DEP_CPP_DLG_F) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\edlgrsrc.h

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Edlgdll.h

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Edlgmgr.h

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_FE0i.h

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_fe0i.cpp
DEP_CPP_DLG_FE=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Edlgdll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_EInf.h"\
	{$(INCLUDE)}"\Property.h"\
	{$(INCLUDE)}"\Mat_0D.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\dlg_FE0i.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\..\GLOBHEAD\Def_IGen.h"\
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
	

!IF  "$(CFG)" == "Edlg_d - Win32 Release"


"$(INTDIR)\dlg_fe0i.obj" : $(SOURCE) $(DEP_CPP_DLG_FE) "$(INTDIR)"

"$(INTDIR)\dlg_fe0i.sbr" : $(SOURCE) $(DEP_CPP_DLG_FE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"


"$(INTDIR)\dlg_fe0i.obj" : $(SOURCE) $(DEP_CPP_DLG_FE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_fe2i.h

!IF  "$(CFG)" == "Edlg_d - Win32 Release"

!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_fe2i.cpp
DEP_CPP_DLG_FE2=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Edlgdll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Def_EInf.h"\
	{$(INCLUDE)}"\Property.h"\
	{$(INCLUDE)}"\Mat_2D.h"\
	{$(INCLUDE)}"\Release.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\dlg_fe2i.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\..\GLOBHEAD\Def_IGen.h"\
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
	{$(INCLUDE)}"\Mat_1D.h"\
	

!IF  "$(CFG)" == "Edlg_d - Win32 Release"


"$(INTDIR)\dlg_fe2i.obj" : $(SOURCE) $(DEP_CPP_DLG_FE2) "$(INTDIR)"

"$(INTDIR)\dlg_fe2i.sbr" : $(SOURCE) $(DEP_CPP_DLG_FE2) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Edlg_d - Win32 Debug"


"$(INTDIR)\dlg_fe2i.obj" : $(SOURCE) $(DEP_CPP_DLG_FE2) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
