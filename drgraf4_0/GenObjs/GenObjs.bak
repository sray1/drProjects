# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=GenObjs - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to GenObjs - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "GenObjs - Win32 Release" && "$(CFG)" !=\
 "GenObjs - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "GenObjs.mak" CFG="GenObjs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GenObjs - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GenObjs - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "GenObjs - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe
F90=fl32.exe

!IF  "$(CFG)" == "GenObjs - Win32 Release"

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

ALL : "$(OUTDIR)\GenObjs.dll"

CLEAN : 
	-@erase ".\Release\GenObjs.dll"
	-@erase ".\Release\Drprof_c.obj"
	-@erase ".\Release\SolidHex.obj"
	-@erase ".\Release\Curve_3.obj"
	-@erase ".\Release\OGen_dll.obj"
	-@erase ".\Release\Drcurve.obj"
	-@erase ".\Release\Solid4.obj"
	-@erase ".\Release\Triangle.obj"
	-@erase ".\Release\Drprof_P.obj"
	-@erase ".\Release\SolidPen.obj"
	-@erase ".\Release\Drnode.obj"
	-@erase ".\Release\Curve_2.obj"
	-@erase ".\Release\Pentahed.obj"
	-@erase ".\Release\Drobj3d.obj"
	-@erase ".\Release\Surface4.obj"
	-@erase ".\Release\Pat_Tan4.obj"
	-@erase ".\Release\Curve_1.obj"
	-@erase ".\Release\Drpatch.obj"
	-@erase ".\Release\Surface3.obj"
	-@erase ".\Release\Pat_Tan3.obj"
	-@erase ".\Release\Drsolid.obj"
	-@erase ".\Release\Curve.obj"
	-@erase ".\Release\GenObjs.lib"
	-@erase ".\Release\GenObjs.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Ox /I "Release/" /c /nologo /MT
# ADD F90 /Ox /I "Release/" /c /nologo /MT
F90_PROJ=/Ox /I "Release/" /c /nologo /MT /Fo"Release/" 
F90_OBJS=.\Release/
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/GenObjs.pch" /YX /Fo"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/GenObjs.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/GenObjs.pdb" /machine:I386 /def:".\GenObj_d.def"\
 /out:"$(OUTDIR)/GenObjs.dll" /implib:"$(OUTDIR)/GenObjs.lib" 
DEF_FILE= \
	".\GenObj_d.def"
LINK32_OBJS= \
	".\Release\Drprof_c.obj" \
	".\Release\SolidHex.obj" \
	".\Release\Curve_3.obj" \
	".\Release\OGen_dll.obj" \
	".\Release\Drcurve.obj" \
	".\Release\Solid4.obj" \
	".\Release\Triangle.obj" \
	".\Release\Drprof_P.obj" \
	".\Release\SolidPen.obj" \
	".\Release\Drnode.obj" \
	".\Release\Curve_2.obj" \
	".\Release\Pentahed.obj" \
	".\Release\Drobj3d.obj" \
	".\Release\Surface4.obj" \
	".\Release\Pat_Tan4.obj" \
	".\Release\Curve_1.obj" \
	".\Release\Drpatch.obj" \
	".\Release\Surface3.obj" \
	".\Release\Pat_Tan3.obj" \
	".\Release\Drsolid.obj" \
	".\Release\Curve.obj"

"$(OUTDIR)\GenObjs.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

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

ALL : "$(OUTDIR)\OGen_D32.dll"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\applic\Debug\OGen_D32.dll"
	-@erase ".\Debug\SolidHex.obj"
	-@erase ".\Debug\Surface3.obj"
	-@erase ".\Debug\OGen_dll.obj"
	-@erase ".\Debug\Drobj3d.obj"
	-@erase ".\Debug\Triangle.obj"
	-@erase ".\Debug\SolidPen.obj"
	-@erase ".\Debug\Pentahed.obj"
	-@erase ".\Debug\Curve_3.obj"
	-@erase ".\Debug\Drpatch.obj"
	-@erase ".\Debug\Pat_Tan4.obj"
	-@erase ".\Debug\Drprof_c.obj"
	-@erase ".\Debug\Drsolid.obj"
	-@erase ".\Debug\Curve_2.obj"
	-@erase ".\Debug\Solid4.obj"
	-@erase ".\Debug\Drprof_P.obj"
	-@erase ".\Debug\Curve.obj"
	-@erase ".\Debug\Pat_Tan3.obj"
	-@erase ".\Debug\Drnode.obj"
	-@erase ".\Debug\Curve_1.obj"
	-@erase ".\Debug\Surface4.obj"
	-@erase ".\Debug\Drcurve.obj"
	-@erase "..\applic\Debug\OGen_D32.lib"
	-@erase "..\applic\Debug\OGen_D32.exp"
	-@erase ".\Debug\OGen_D32.pdb"
	-@erase ".\Debug\OGen_D32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE F90 /Zi /I "Debug/" /c /nologo /MT
# ADD F90 /Zi /I "Debug/" /c /nologo /MT
F90_PROJ=/Zi /I "Debug/" /c /nologo /MT /Fo"Debug/" /Fd"Debug/GenObjs.pdb" 
F90_OBJS=.\Debug/
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXEXT" /D "_MBCS" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXEXT" /D "_MBCS" /Fp"$(INTDIR)/GenObjs.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/GenObjs.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 Dr3D_D32.lib Spec_D32.lib /nologo /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /out:"d:\drgraf4_0\applic\Debug/OGen_D32.dll" /implib:"d:\drgraf4_0\applic\Debug/OGen_D32.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=Dr3D_D32.lib Spec_D32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/OGen_D32.pdb" /map:"$(INTDIR)/OGen_D32.map"\
 /debug /machine:I386 /def:".\GenObj_d.def"\
 /out:"d:\drgraf4_0\applic\Debug/OGen_D32.dll"\
 /implib:"d:\drgraf4_0\applic\Debug/OGen_D32.lib" 
DEF_FILE= \
	".\GenObj_d.def"
LINK32_OBJS= \
	".\Debug\SolidHex.obj" \
	".\Debug\Surface3.obj" \
	".\Debug\OGen_dll.obj" \
	".\Debug\Drobj3d.obj" \
	".\Debug\Triangle.obj" \
	".\Debug\SolidPen.obj" \
	".\Debug\Pentahed.obj" \
	".\Debug\Curve_3.obj" \
	".\Debug\Drpatch.obj" \
	".\Debug\Pat_Tan4.obj" \
	".\Debug\Drprof_c.obj" \
	".\Debug\Drsolid.obj" \
	".\Debug\Curve_2.obj" \
	".\Debug\Solid4.obj" \
	".\Debug\Drprof_P.obj" \
	".\Debug\Curve.obj" \
	".\Debug\Pat_Tan3.obj" \
	".\Debug\Drnode.obj" \
	".\Debug\Curve_1.obj" \
	".\Debug\Surface4.obj" \
	".\Debug\Drcurve.obj"

"$(OUTDIR)\OGen_D32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "GenObjs - Win32 Release"
# Name "GenObjs - Win32 Debug"

!IF  "$(CFG)" == "GenObjs - Win32 Release"

!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Triangle.cpp
DEP_CPP_TRIAN=\
	".\Stdafx.h"\
	".\Triangle.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	

!IF  "$(CFG)" == "GenObjs - Win32 Release"


"$(INTDIR)\Triangle.obj" : $(SOURCE) $(DEP_CPP_TRIAN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"


"$(INTDIR)\Triangle.obj" : $(SOURCE) $(DEP_CPP_TRIAN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Curve_1.cpp
DEP_CPP_CURVE=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Curve_1.h"\
	".\Curve.h"\
	

"$(INTDIR)\Curve_1.obj" : $(SOURCE) $(DEP_CPP_CURVE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Curve_2.cpp
DEP_CPP_CURVE_=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Curve_2.h"\
	".\Curve.h"\
	

"$(INTDIR)\Curve_2.obj" : $(SOURCE) $(DEP_CPP_CURVE_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Curve_3.cpp
DEP_CPP_CURVE_3=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Curve_3.h"\
	".\Curve.h"\
	

"$(INTDIR)\Curve_3.obj" : $(SOURCE) $(DEP_CPP_CURVE_3) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drcurve.cpp
DEP_CPP_DRCUR=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Ext_Cur.h"\
	{$(INCLUDE)}"\Drnode.h"\
	".\Curve.h"\
	".\Curve_1.h"\
	".\Curve_2.h"\
	".\Curve_3.h"\
	".\Drcurve.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	

"$(INTDIR)\Drcurve.obj" : $(SOURCE) $(DEP_CPP_DRCUR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drobj3d.cpp
DEP_CPP_DROBJ=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Drnode.h"\
	".\Drpatch.h"\
	".\Drobj3d.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\Triangle.h"\
	".\Drcurve.h"\
	

"$(INTDIR)\Drobj3d.obj" : $(SOURCE) $(DEP_CPP_DROBJ) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drpatch.cpp

!IF  "$(CFG)" == "GenObjs - Win32 Release"

DEP_CPP_DRPAT=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Pat.h"\
	{$(INCLUDE)}"\Drnode.h"\
	".\Surface3.h"\
	".\Surface4.h"\
	".\Pat_Tan3.h"\
	".\Pat_Tan4.h"\
	".\Drcurve.h"\
	".\Drpatch.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\Triangle.h"\
	
NODEP_CPP_DRPAT=\
	".\DrFE2D.h"\
	

"$(INTDIR)\Drpatch.obj" : $(SOURCE) $(DEP_CPP_DRPAT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

DEP_CPP_DRPAT=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Pat.h"\
	{$(INCLUDE)}"\Drnode.h"\
	".\Surface3.h"\
	".\Surface4.h"\
	".\Pat_Tan3.h"\
	".\Pat_Tan4.h"\
	".\Drcurve.h"\
	".\Drpatch.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\Triangle.h"\
	

"$(INTDIR)\Drpatch.obj" : $(SOURCE) $(DEP_CPP_DRPAT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drprof_c.cpp
DEP_CPP_DRPRO=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Ext_Cur.h"\
	".\Drcurve.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Drprof_c.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	

"$(INTDIR)\Drprof_c.obj" : $(SOURCE) $(DEP_CPP_DRPRO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drsolid.cpp

!IF  "$(CFG)" == "GenObjs - Win32 Release"

DEP_CPP_DRSOL=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Sol.h"\
	{$(INCLUDE)}"\Drnode.h"\
	".\SolidHex.h"\
	".\SolidPen.h"\
	".\Pentahed.h"\
	".\Drcurve.h"\
	".\Drsolid.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\Surface4.h"\
	".\Surface3.h"\
	".\Drpatch.h"\
	".\Triangle.h"\
	
NODEP_CPP_DRSOL=\
	".\DrFE2D.h"\
	".\DrFE3D.h"\
	

"$(INTDIR)\Drsolid.obj" : $(SOURCE) $(DEP_CPP_DRSOL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

DEP_CPP_DRSOL=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Sol.h"\
	{$(INCLUDE)}"\Drnode.h"\
	".\SolidHex.h"\
	".\SolidPen.h"\
	".\Pentahed.h"\
	".\Drcurve.h"\
	".\Drsolid.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	".\Surface4.h"\
	".\Surface3.h"\
	".\Drpatch.h"\
	".\Triangle.h"\
	

"$(INTDIR)\Drsolid.obj" : $(SOURCE) $(DEP_CPP_DRSOL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pentahed.cpp
DEP_CPP_PENTA=\
	".\Stdafx.h"\
	".\Pentahed.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	

"$(INTDIR)\Pentahed.obj" : $(SOURCE) $(DEP_CPP_PENTA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Solid4.cpp
DEP_CPP_SOLID=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Curve_1.h"\
	".\Curve_2.h"\
	".\Curve_3.h"\
	".\Solid4.h"\
	".\Curve.h"\
	".\Surface4.h"\
	

"$(INTDIR)\Solid4.obj" : $(SOURCE) $(DEP_CPP_SOLID) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SolidHex.cpp
DEP_CPP_SOLIDH=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Curve_1.h"\
	".\Curve_2.h"\
	".\Curve_3.h"\
	".\SolidHex.h"\
	".\Curve.h"\
	".\Surface4.h"\
	

"$(INTDIR)\SolidHex.obj" : $(SOURCE) $(DEP_CPP_SOLIDH) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SolidPen.cpp
DEP_CPP_SOLIDP=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Curve.h"\
	".\Surface4.h"\
	".\Triangle.h"\
	".\Pentahed.h"\
	".\SolidPen.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\Surface3.h"\
	

"$(INTDIR)\SolidPen.obj" : $(SOURCE) $(DEP_CPP_SOLIDP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Surface3.cpp
DEP_CPP_SURFA=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Triangle.h"\
	".\Surface3.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	

"$(INTDIR)\Surface3.obj" : $(SOURCE) $(DEP_CPP_SURFA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Surface4.cpp
DEP_CPP_SURFAC=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Curve_1.h"\
	".\Curve_2.h"\
	".\Curve_3.h"\
	".\Surface4.h"\
	".\Curve.h"\
	

"$(INTDIR)\Surface4.obj" : $(SOURCE) $(DEP_CPP_SURFAC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Curve.cpp
DEP_CPP_CURVE_C=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	".\Curve.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	

"$(INTDIR)\Curve.obj" : $(SOURCE) $(DEP_CPP_CURVE_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GenObj_d.def

!IF  "$(CFG)" == "GenObjs - Win32 Release"

!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OGen_dll.cpp
DEP_CPP_OGEN_=\
	".\Stdafx.h"\
	".\OGen_dll.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Glb_elem.h"\
	{$(INCLUDE)}"\Glb_Cur.h"\
	{$(INCLUDE)}"\Glb_Pat.h"\
	{$(INCLUDE)}"\Glb_Sol.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	

"$(INTDIR)\OGen_dll.obj" : $(SOURCE) $(DEP_CPP_OGEN_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pat_Tan4.h

!IF  "$(CFG)" == "GenObjs - Win32 Release"

!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pat_Tan4.cpp
DEP_CPP_PAT_T=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Curve_1.h"\
	".\Curve_2.h"\
	".\Curve_3.h"\
	".\Pat_Tan4.h"\
	".\Curve.h"\
	".\Surface4.h"\
	

"$(INTDIR)\Pat_Tan4.obj" : $(SOURCE) $(DEP_CPP_PAT_T) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pat_Tan3.h

!IF  "$(CFG)" == "GenObjs - Win32 Release"

!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pat_Tan3.cpp
DEP_CPP_PAT_TA=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	".\Triangle.h"\
	".\Pat_Tan3.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	".\Surface3.h"\
	

"$(INTDIR)\Pat_Tan3.obj" : $(SOURCE) $(DEP_CPP_PAT_TA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drprof_P.h

!IF  "$(CFG)" == "GenObjs - Win32 Release"

!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drprof_P.cpp
DEP_CPP_DRPROF=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Def_3d.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Ext_Pat.h"\
	".\Drpatch.h"\
	{$(INCLUDE)}"\Matobj.h"\
	".\Drprof_P.h"\
	{$(INCLUDE)}"\Def_View.h"\
	".\Triangle.h"\
	".\Drcurve.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	".\Drprof_c.h"\
	

"$(INTDIR)\Drprof_P.obj" : $(SOURCE) $(DEP_CPP_DRPROF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drnode.h

!IF  "$(CFG)" == "GenObjs - Win32 Release"

!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Drnode.cpp

!IF  "$(CFG)" == "GenObjs - Win32 Release"

DEP_CPP_DRNOD=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drclip.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	
NODEP_CPP_DRNOD=\
	".\DrFE2D.h"\
	".\DrFE3D.h"\
	

"$(INTDIR)\Drnode.obj" : $(SOURCE) $(DEP_CPP_DRNOD) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GenObjs - Win32 Debug"

DEP_CPP_DRNOD=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\Def_Type.h"\
	{$(INCLUDE)}"\Def_Objs.h"\
	{$(INCLUDE)}"\Def_View.h"\
	{$(INCLUDE)}"\3dmath.h"\
	{$(INCLUDE)}"\Xform.h"\
	{$(INCLUDE)}"\Drclip.h"\
	{$(INCLUDE)}"\Def_IGen.h"\
	{$(INCLUDE)}"\Def_Elem.h"\
	{$(INCLUDE)}"\Ext_Elem.h"\
	{$(INCLUDE)}"\Def_Card.h"\
	{$(INCLUDE)}"\Drnode.h"\
	{$(INCLUDE)}"\Drobject.h"\
	{$(INCLUDE)}"\Dlistmgr.h"\
	{$(INCLUDE)}"\Str_Gen.h"\
	{$(INCLUDE)}"\Def_CuPS.h"\
	{$(INCLUDE)}"\Matobj.h"\
	{$(INCLUDE)}"\Def_Rend.h"\
	

"$(INTDIR)\Drnode.obj" : $(SOURCE) $(DEP_CPP_DRNOD) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
