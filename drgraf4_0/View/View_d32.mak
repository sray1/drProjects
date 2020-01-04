# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=View_d - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to View_d - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "View_d - Win32 Release" && "$(CFG)" != "View_d - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "View_d32.mak" CFG="View_d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "View_d - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "View_d - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "View_d - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "View_d - Win32 Release"

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

ALL : "$(OUTDIR)\View_d32.dll" "$(OUTDIR)\View_d32.bsc"

CLEAN : 
	-@erase ".\Release\View_d32.bsc"
	-@erase ".\Release\Rn_wire0.sbr"
	-@erase ".\Release\Axisdraw.sbr"
	-@erase ".\Release\Light.sbr"
	-@erase ".\Release\Colorpal.sbr"
	-@erase ".\Release\Render.sbr"
	-@erase ".\Release\Textures.sbr"
	-@erase ".\Release\Viewdll.sbr"
	-@erase ".\Release\Draxis.sbr"
	-@erase ".\Release\Rn_wire2.sbr"
	-@erase ".\Release\Zbuffer.sbr"
	-@erase ".\Release\Viewinfo.sbr"
	-@erase ".\Release\Rn_wire1.sbr"
	-@erase ".\Release\View_d32.dll"
	-@erase ".\Release\Viewinfo.obj"
	-@erase ".\Release\Rn_wire1.obj"
	-@erase ".\Release\Rn_wire0.obj"
	-@erase ".\Release\Axisdraw.obj"
	-@erase ".\Release\Light.obj"
	-@erase ".\Release\Colorpal.obj"
	-@erase ".\Release\Render.obj"
	-@erase ".\Release\Textures.obj"
	-@erase ".\Release\Viewdll.obj"
	-@erase ".\Release\Draxis.obj"
	-@erase ".\Release\Rn_wire2.obj"
	-@erase ".\Release\Zbuffer.obj"
	-@erase ".\Release\View.res"
	-@erase ".\Release\View_d32.lib"
	-@erase ".\Release\View_d32.exp"
	-@erase ".\FULL"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/View_d32.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/View.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/View_d32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/Rn_wire0.sbr" \
	"$(INTDIR)/Axisdraw.sbr" \
	"$(INTDIR)/Light.sbr" \
	"$(INTDIR)/Colorpal.sbr" \
	"$(INTDIR)/Render.sbr" \
	"$(INTDIR)/Textures.sbr" \
	"$(INTDIR)/Viewdll.sbr" \
	"$(INTDIR)/Draxis.sbr" \
	"$(INTDIR)/Rn_wire2.sbr" \
	"$(INTDIR)/Zbuffer.sbr" \
	"$(INTDIR)/Viewinfo.sbr" \
	"$(INTDIR)/Rn_wire1.sbr"

"$(OUTDIR)\View_d32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
# ADD LINK32 oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /machine:IX86
LINK32_FLAGS=oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/View_d32.pdb" /map:"FULL" /machine:IX86\
 /def:".\View_d.def" /out:"$(OUTDIR)/View_d32.dll"\
 /implib:"$(OUTDIR)/View_d32.lib" 
DEF_FILE= \
	".\View_d.def"
LINK32_OBJS= \
	"$(INTDIR)/Viewinfo.obj" \
	"$(INTDIR)/Rn_wire1.obj" \
	"$(INTDIR)/Rn_wire0.obj" \
	"$(INTDIR)/Axisdraw.obj" \
	"$(INTDIR)/Light.obj" \
	"$(INTDIR)/Colorpal.obj" \
	"$(INTDIR)/Render.obj" \
	"$(INTDIR)/Textures.obj" \
	"$(INTDIR)/Viewdll.obj" \
	"$(INTDIR)/Draxis.obj" \
	"$(INTDIR)/Rn_wire2.obj" \
	"$(INTDIR)/Zbuffer.obj" \
	"$(INTDIR)/View.res"

"$(OUTDIR)\View_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"

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

ALL : "$(OUTDIR)\View_d32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase "..\applic\Debug\View_d32.dll"
	-@erase ".\Debug\Viewdll.obj"
	-@erase ".\Debug\Rn_wire2.obj"
	-@erase ".\Debug\Light.obj"
	-@erase ".\Debug\Viewinfo.obj"
	-@erase ".\Debug\Rn_wire1.obj"
	-@erase ".\Debug\Colorpal.obj"
	-@erase ".\Debug\Zbuffer.obj"
	-@erase ".\Debug\Rn_wire0.obj"
	-@erase ".\Debug\Textures.obj"
	-@erase ".\Debug\Axisdraw.obj"
	-@erase ".\Debug\Render.obj"
	-@erase ".\Debug\Draxis.obj"
	-@erase ".\Debug\View.res"
	-@erase "..\applic\Debug\View_d32.lib"
	-@erase "..\applic\Debug\View_d32.exp"
	-@erase ".\Debug\View_d32.pdb"
	-@erase ".\Debug\View_d32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/View_d32.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/View.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/View_d32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 OMgr_D.lib Spec_D.lib Draw_D.lib Dr3D_D.lib EBox_D.lib DBox_D.lib SDlg_D.lib oldnames.lib ldllcew.lib /nologo /subsystem:windows /dll /map:"FULL" /debug /machine:IX86
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib OMgr_d32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:IX86 /out:"d:\drgraf4_0\applic\Debug\View_d32.dll" /implib:"d:\drgraf4_0\applic\Debug\View_d32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Dr3D_D32.lib Spec_D32.lib Mesh_D32.lib Elem_D32.lib Draw_D32.lib\
 OGen_D32.lib Supp_D32.lib StaL_D32.lib OMgr_d32.lib /nologo /subsystem:windows\
 /dll /incremental:no /pdb:"$(OUTDIR)/View_d32.pdb"\
 /map:"$(INTDIR)/View_d32.map" /debug /machine:IX86 /def:".\View_d.def"\
 /out:"d:\drgraf4_0\applic\Debug\View_d32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug\View_d32.lib" 
DEF_FILE= \
	".\View_d.def"
LINK32_OBJS= \
	"$(INTDIR)/Viewdll.obj" \
	"$(INTDIR)/Rn_wire2.obj" \
	"$(INTDIR)/Light.obj" \
	"$(INTDIR)/Viewinfo.obj" \
	"$(INTDIR)/Rn_wire1.obj" \
	"$(INTDIR)/Colorpal.obj" \
	"$(INTDIR)/Zbuffer.obj" \
	"$(INTDIR)/Rn_wire0.obj" \
	"$(INTDIR)/Textures.obj" \
	"$(INTDIR)/Axisdraw.obj" \
	"$(INTDIR)/Render.obj" \
	"$(INTDIR)/Draxis.obj" \
	"$(INTDIR)/View.res"

"$(OUTDIR)\View_d32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "View_d - Win32 Release"
# Name "View_d - Win32 Debug"

!IF  "$(CFG)" == "View_d - Win32 Release"

!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Viewdll.cpp
DEP_CPP_VIEWD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\ViewDll.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Viewdll.obj" : $(SOURCE) $(DEP_CPP_VIEWD) "$(INTDIR)"

"$(INTDIR)\Viewdll.sbr" : $(SOURCE) $(DEP_CPP_VIEWD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Viewdll.obj" : $(SOURCE) $(DEP_CPP_VIEWD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Render.cpp
DEP_CPP_RENDE=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	".\Textures.h"\
	".\Light.h"\
	".\Zbuffer.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\Render.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
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
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Render.obj" : $(SOURCE) $(DEP_CPP_RENDE) "$(INTDIR)"

"$(INTDIR)\Render.sbr" : $(SOURCE) $(DEP_CPP_RENDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Render.obj" : $(SOURCE) $(DEP_CPP_RENDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rn_wire0.cpp
DEP_CPP_RN_WI=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	".\Render.h"\
	".\Rn_wire0.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Type.h"\
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
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\Zbuffer.h"\
	".\Textures.h"\
	".\Light.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Rn_wire0.obj" : $(SOURCE) $(DEP_CPP_RN_WI) "$(INTDIR)"

"$(INTDIR)\Rn_wire0.sbr" : $(SOURCE) $(DEP_CPP_RN_WI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Rn_wire0.obj" : $(SOURCE) $(DEP_CPP_RN_WI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Colorpal.cpp
DEP_CPP_COLOR=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\ColorPal.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Colorpal.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"

"$(INTDIR)\Colorpal.sbr" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Colorpal.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Light.cpp
DEP_CPP_LIGHT=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\ColorPal.h"\
	{$(INCLUDE)}"\Xform.h"\
	".\Light.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Light.obj" : $(SOURCE) $(DEP_CPP_LIGHT) "$(INTDIR)"

"$(INTDIR)\Light.sbr" : $(SOURCE) $(DEP_CPP_LIGHT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Light.obj" : $(SOURCE) $(DEP_CPP_LIGHT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Textures.cpp
DEP_CPP_TEXTU=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\Textures.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_View.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Textures.obj" : $(SOURCE) $(DEP_CPP_TEXTU) "$(INTDIR)"

"$(INTDIR)\Textures.sbr" : $(SOURCE) $(DEP_CPP_TEXTU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Textures.obj" : $(SOURCE) $(DEP_CPP_TEXTU) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Zbuffer.cpp
DEP_CPP_ZBUFF=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\Zbuffer.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Zbuffer.obj" : $(SOURCE) $(DEP_CPP_ZBUFF) "$(INTDIR)"

"$(INTDIR)\Zbuffer.sbr" : $(SOURCE) $(DEP_CPP_ZBUFF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Zbuffer.obj" : $(SOURCE) $(DEP_CPP_ZBUFF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\View.rc

!IF  "$(CFG)" == "View_d - Win32 Release"

DEP_RSC_VIEW_=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	".\..\applic\RES\CURVEBIT.BMP"\
	

"$(INTDIR)\View.res" : $(SOURCE) $(DEP_RSC_VIEW_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"

DEP_RSC_VIEW_=\
	".\..\Applic\Res\Image1d.bmp"\
	".\..\Applic\Res\Image1f.bmp"\
	".\..\Applic\Res\Image2d.bmp"\
	".\..\Applic\Res\Image2f.bmp"\
	".\..\Applic\Res\Image2u.bmp"\
	".\..\Applic\Res\Image1u.bmp"\
	".\..\applic\RES\CURVEBIT.BMP"\
	{$(INCLUDE)}"\CommRsrc.h"\
	

"$(INTDIR)\View.res" : $(SOURCE) $(DEP_RSC_VIEW_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rn_wire1.cpp
DEP_CPP_RN_WIR=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	{$(INCLUDE)}"\DrFE0D.h"\
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	".\Render.h"\
	".\Rn_wire1.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Type.h"\
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
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\Zbuffer.h"\
	".\Textures.h"\
	".\Light.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Rn_wire1.obj" : $(SOURCE) $(DEP_CPP_RN_WIR) "$(INTDIR)"

"$(INTDIR)\Rn_wire1.sbr" : $(SOURCE) $(DEP_CPP_RN_WIR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Rn_wire1.obj" : $(SOURCE) $(DEP_CPP_RN_WIR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Viewinfo.cpp
DEP_CPP_VIEWI=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\ViewDll.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Viewinfo.obj" : $(SOURCE) $(DEP_CPP_VIEWI) "$(INTDIR)"

"$(INTDIR)\Viewinfo.sbr" : $(SOURCE) $(DEP_CPP_VIEWI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Viewinfo.obj" : $(SOURCE) $(DEP_CPP_VIEWI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Axisdraw.cpp
DEP_CPP_AXISD=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\ViewDll.h"\
	".\Draxis.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Axisdraw.obj" : $(SOURCE) $(DEP_CPP_AXISD) "$(INTDIR)"

"$(INTDIR)\Axisdraw.sbr" : $(SOURCE) $(DEP_CPP_AXISD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Axisdraw.obj" : $(SOURCE) $(DEP_CPP_AXISD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Draxis.cpp
DEP_CPP_DRAXI=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\drawview.h"\
	".\Draxis.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Draxis.obj" : $(SOURCE) $(DEP_CPP_DRAXI) "$(INTDIR)"

"$(INTDIR)\Draxis.sbr" : $(SOURCE) $(DEP_CPP_DRAXI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Draxis.obj" : $(SOURCE) $(DEP_CPP_DRAXI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\View_d.def

!IF  "$(CFG)" == "View_d - Win32 Release"

!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rn_wire2.cpp
DEP_CPP_RN_WIRE=\
	{$(INCLUDE)}"\Stdafx.h"\
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
	{$(INCLUDE)}"\DrFE1D.h"\
	{$(INCLUDE)}"\DrFE2D.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Drprof_c.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drclip.h"\
	".\Render.h"\
	".\Rn_wire2.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Type.h"\
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
	{$(INCLUDE)}"\Str_Supp.h"\
	{$(INCLUDE)}"\Str_Mesh.h"\
	{$(INCLUDE)}"\Def_Mesh.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Triangle.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\Zbuffer.h"\
	".\Textures.h"\
	".\Light.h"\
	{$(INCLUDE)}"\drawview.h"\
	{$(INCLUDE)}"\Axisdraw.h"\
	{$(INCLUDE)}"\Viewinfo.h"\
	{$(INCLUDE)}"\Def_Mous.h"\
	".\..\APPLIC\DVM_Genr.h"\
	".\..\APPLIC\DVM_Edit.h"\
	".\..\APPLIC\DVM_Del.h"\
	".\..\APPLIC\DVM_CreO.h"\
	".\..\APPLIC\DVM_Post.h"\
	

!IF  "$(CFG)" == "View_d - Win32 Release"


"$(INTDIR)\Rn_wire2.obj" : $(SOURCE) $(DEP_CPP_RN_WIRE) "$(INTDIR)"

"$(INTDIR)\Rn_wire2.sbr" : $(SOURCE) $(DEP_CPP_RN_WIRE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"


"$(INTDIR)\Rn_wire2.obj" : $(SOURCE) $(DEP_CPP_RN_WIRE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rn_wire2.h

!IF  "$(CFG)" == "View_d - Win32 Release"

!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rn_wire1.h

!IF  "$(CFG)" == "View_d - Win32 Release"

!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rn_wire0.h

!IF  "$(CFG)" == "View_d - Win32 Release"

!ELSEIF  "$(CFG)" == "View_d - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
