# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=StaLMouse - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to StaLMouse - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "StaLMouse - Win32 Release" && "$(CFG)" !=\
 "StaLMouse - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "StaLMouse.mak" CFG="StaLMouse - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StaLMouse - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "StaLMouse - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "StaLMouse - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

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

ALL : "$(OUTDIR)\StaLMouse.dll"

CLEAN : 
	-@erase ".\Release\StaLMouse.dll"
	-@erase ".\Release\Dlg_StLC.obj"
	-@erase ".\Release\Dlg_StLA.obj"
	-@erase ".\Release\MSTLdll.obj"
	-@erase ".\Release\Dlg_IsoP.obj"
	-@erase ".\Release\Mi_StaL.obj"
	-@erase ".\Release\dlg_Many.obj"
	-@erase ".\Release\dlg_StLI.obj"
	-@erase ".\Release\MSTLMgr.obj"
	-@erase ".\Release\StaLMgr.res"
	-@erase ".\Release\StaLMouse.lib"
	-@erase ".\Release\StaLMouse.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/StaLMouse.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/StaLMgr.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/StaLMouse.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/StaLMouse.pdb" /machine:I386 /def:".\MStL_d.def"\
 /out:"$(OUTDIR)/StaLMouse.dll" /implib:"$(OUTDIR)/StaLMouse.lib" 
DEF_FILE= \
	".\MStL_d.def"
LINK32_OBJS= \
	".\Release\Dlg_StLC.obj" \
	".\Release\Dlg_StLA.obj" \
	".\Release\MSTLdll.obj" \
	".\Release\Dlg_IsoP.obj" \
	".\Release\Mi_StaL.obj" \
	".\Release\dlg_Many.obj" \
	".\Release\dlg_StLI.obj" \
	".\Release\MSTLMgr.obj" \
	".\Release\StaLMgr.res"

"$(OUTDIR)\StaLMouse.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

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

ALL : "$(OUTDIR)\MStL_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\Applic\Debug\MStL_D32.dll"
	-@erase ".\Debug\MSTLdll.obj"
	-@erase ".\Debug\Mi_StaL.obj"
	-@erase ".\Debug\Dlg_StLA.obj"
	-@erase ".\Debug\dlg_Many.obj"
	-@erase ".\Debug\dlg_StLI.obj"
	-@erase ".\Debug\Dlg_IsoP.obj"
	-@erase ".\Debug\Dlg_StLC.obj"
	-@erase ".\Debug\MSTLMgr.obj"
	-@erase ".\StaLMgr.res"
	-@erase "..\Applic\Debug\MStL_D32.ilk"
	-@erase "..\Applic\Debug\MStL_D32.lib"
	-@erase "..\Applic\Debug\MStL_D32.exp"
	-@erase ".\Debug\MStL_D32.pdb"
	-@erase ".\Debug\MStL_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/StaLMouse.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_MBCS" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXEXT" /D "_MBCS" /Fp"$(INTDIR)/StaLMouse.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /fo"StaLMgr.res" /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"StaLMgr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/StaLMouse.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 OMgr_D32.lib Spec_d32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib Supp_D32.lib StaL_D32.lib Dr3D_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib MSol_d32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /out:"d:/drGraf4_0/Applic/Debug/MStL_D32.dll" /implib:"d:/drGraf4_0/Applic/Debug/MStL_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=OMgr_D32.lib Spec_d32.lib Elem_D32.lib Draw_D32.lib OGen_D32.lib\
 Supp_D32.lib StaL_D32.lib Dr3D_D32.lib MNod_D32.lib MCur_D32.lib MPat_D32.lib\
 MSol_d32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/MStL_D32.pdb" /map:"$(INTDIR)/MStL_D32.map" /debug\
 /machine:I386 /def:".\MStL_d.def" /out:"d:/drGraf4_0/Applic/Debug/MStL_D32.dll"\
 /implib:"d:/drGraf4_0/Applic/Debug/MStL_D32.lib" 
DEF_FILE= \
	".\MStL_d.def"
LINK32_OBJS= \
	".\Debug\MSTLdll.obj" \
	".\Debug\Mi_StaL.obj" \
	".\Debug\Dlg_StLA.obj" \
	".\Debug\dlg_Many.obj" \
	".\Debug\dlg_StLI.obj" \
	".\Debug\Dlg_IsoP.obj" \
	".\Debug\Dlg_StLC.obj" \
	".\Debug\MSTLMgr.obj" \
	".\StaLMgr.res"

"$(OUTDIR)\MStL_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "StaLMouse - Win32 Release"
# Name "StaLMouse - Win32 Debug"

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MSTLdll.cpp
DEP_CPP_MSTLD=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Glb_StaL.h"\
	".\MSTLdll.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	

!IF  "$(CFG)" == "StaLMouse - Win32 Release"


"$(INTDIR)\MSTLdll.obj" : $(SOURCE) $(DEP_CPP_MSTLD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"


"$(INTDIR)\MSTLdll.obj" : $(SOURCE) $(DEP_CPP_MSTLD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MStL_d.def

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StaLMgr.rc

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

DEP_RSC_STALM=\
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
	{$(INCLUDE)}"\MSupRsrc.h"\
	".\MSTLRsrc.hm"\
	

"$(INTDIR)\StaLMgr.res" : $(SOURCE) $(DEP_RSC_STALM) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

DEP_RSC_STALM=\
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
	{$(INCLUDE)}"\MSupRsrc.h"\
	".\MSTLRsrc.hm"\
	

"$(INTDIR)\StaLMgr.res" : $(SOURCE) $(DEP_RSC_STALM) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSTLRsrc.h

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSTLMgr.h

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSTLMgr.cpp
DEP_CPP_MSTLM=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	".\Dlg_IsoP.h"\
	".\dlg_Many.h"\
	".\MSTLdll.h"\
	".\MSTLMgr.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	

!IF  "$(CFG)" == "StaLMouse - Win32 Release"


"$(INTDIR)\MSTLMgr.obj" : $(SOURCE) $(DEP_CPP_MSTLM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"


"$(INTDIR)\MSTLMgr.obj" : $(SOURCE) $(DEP_CPP_MSTLM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_IsoP.cpp
DEP_CPP_DLG_I=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MSTLMgr.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\Dlg_IsoP.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	

"$(INTDIR)\Dlg_IsoP.obj" : $(SOURCE) $(DEP_CPP_DLG_I) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_IsoP.h

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_StLA.h

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_StLA.cpp
DEP_CPP_DLG_S=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MSTLdll.h"\
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
	{$(INCLUDE)}"\MSupRsrc.h"\
	".\Dlg_StLA.h"\
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
	{$(INCLUDE)}"\Def_StaL.h"\
	

"$(INTDIR)\Dlg_StLA.obj" : $(SOURCE) $(DEP_CPP_DLG_S) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_StLI.cpp
DEP_CPP_DLG_ST=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MSTLdll.h"\
	{$(INCLUDE)}"\Usermsg.h"\
	{$(INCLUDE)}"\Def_Lims.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MSupRsrc.h"\
	".\Dlg_StLA.h"\
	".\Dlg_StLC.h"\
	{$(INCLUDE)}"\dlg_StLI.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\3dmath.h"\
	

"$(INTDIR)\dlg_StLI.obj" : $(SOURCE) $(DEP_CPP_DLG_ST) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_StLI.h

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_StaL.h

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mi_StaL.cpp
DEP_CPP_MI_ST=\
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
	{$(INCLUDE)}"\Def_Draw.h"\
	{$(INCLUDE)}"\Drlabel.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	{$(INCLUDE)}"\DrStatic.h"\
	{$(INCLUDE)}"\Def_Spec.h"\
	{$(INCLUDE)}"\Drpen.h"\
	{$(INCLUDE)}"\Layer.h"\
	{$(INCLUDE)}"\Precison.h"\
	{$(INCLUDE)}"\Mapfacto.h"\
	{$(INCLUDE)}"\Scalefac.h"\
	".\Mi_StaL.h"\
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
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Ext_StaL.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\Mi_gangs.h"\
	{$(INCLUDE)}"\Mi_gangp.h"\
	{$(INCLUDE)}"\Drpatch.h"\
	{$(INCLUDE)}"\Drsolid.h"\
	{$(INCLUDE)}"\Mi_GangC.h"\
	{$(INCLUDE)}"\Mi_GangN.h"\
	".\..\GenObjs\Triangle.h"\
	

"$(INTDIR)\Mi_StaL.obj" : $(SOURCE) $(DEP_CPP_MI_ST) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_StLC.h

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dlg_StLC.cpp
DEP_CPP_DLG_STL=\
	{$(INCLUDE)}"\Stdafx.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Drgraf.h"\
	{$(INCLUDE)}"\Drgradoc.h"\
	{$(INCLUDE)}"\Objmgr.h"\
	{$(INCLUDE)}"\Newobjs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drcurve.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	{$(INCLUDE)}"\MCurRsrc.h"\
	{$(INCLUDE)}"\MPatRsrc.h"\
	".\Dlg_StLC.h"\
	{$(INCLUDE)}"\Aboutbox.h"\
	{$(INCLUDE)}"\Banner.h"\
	{$(INCLUDE)}"\Mdib.h"\
	{$(INCLUDE)}"\MsObjMgr.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\ElemInfo.h"\
	{$(INCLUDE)}"\Matobj.h"\
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
	

"$(INTDIR)\Dlg_StLC.obj" : $(SOURCE) $(DEP_CPP_DLG_STL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_Many.h

!IF  "$(CFG)" == "StaLMouse - Win32 Release"

!ELSEIF  "$(CFG)" == "StaLMouse - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlg_Many.cpp
DEP_CPP_DLG_M=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\MSTLMgr.h"\
	{$(INCLUDE)}"\CommRsrc.h"\
	".\dlg_Many.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Str_StaL.h"\
	{$(INCLUDE)}"\Def_StaL.h"\
	

"$(INTDIR)\dlg_Many.obj" : $(SOURCE) $(DEP_CPP_DLG_M) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
