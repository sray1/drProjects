# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Dboxebox - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Dboxebox - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dboxebox - Win32 Release" && "$(CFG)" !=\
 "Dboxebox - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dboxebox32.mak" CFG="Dboxebox - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dboxebox - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Dboxebox - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Dboxebox - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Dboxebox - Win32 Release"

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

ALL : "$(OUTDIR)\Dboxebox32.exe"

CLEAN : 
	-@erase ".\Release\Dboxebox32.exe"
	-@erase ".\Release\Dboxedoc.obj"
	-@erase ".\Release\Dboxebox32.pch"
	-@erase ".\Release\Dboxevw.obj"
	-@erase ".\Release\Dboxebox.obj"
	-@erase ".\Release\Stdafx.obj"
	-@erase ".\Release\toolbar.obj"
	-@erase ".\Release\Mainfrm.obj"
	-@erase ".\Release\globals.obj"
	-@erase ".\Release\Dboxebox.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dboxebox32.pch" /Yu"STDAFX.H"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dboxebox.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dboxebox32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 EBox_D.lib DBox_D.lib oldnames.lib /nologo /stack:0x2800 /subsystem:windows /machine:IX86
# ADD LINK32 EBox_D.lib DBox_D.lib oldnames.lib /nologo /stack:0x2800 /subsystem:windows /machine:IX86
LINK32_FLAGS=EBox_D.lib DBox_D.lib oldnames.lib /nologo /stack:0x2800\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Dboxebox32.pdb"\
 /machine:IX86 /def:".\Dboxebox.def" /out:"$(OUTDIR)/Dboxebox32.exe" 
DEF_FILE= \
	".\Dboxebox.def"
LINK32_OBJS= \
	"$(INTDIR)/Dboxedoc.obj" \
	"$(INTDIR)/Dboxevw.obj" \
	"$(INTDIR)/Dboxebox.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/toolbar.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/globals.obj" \
	"$(INTDIR)/Dboxebox.res"

"$(OUTDIR)\Dboxebox32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dboxebox - Win32 Debug"

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

ALL : "$(OUTDIR)\Dboxebox32.exe" "$(OUTDIR)\Dboxebox32.pch"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Dboxebox32.pch"
	-@erase ".\Debug\Dboxebox32.exe"
	-@erase ".\Debug\Dboxebox.obj"
	-@erase ".\Debug\Dboxedoc.obj"
	-@erase ".\Debug\toolbar.obj"
	-@erase ".\Debug\Mainfrm.obj"
	-@erase ".\Debug\globals.obj"
	-@erase ".\Debug\Dboxevw.obj"
	-@erase ".\Debug\Stdafx.obj"
	-@erase ".\Debug\Dboxebox.res"
	-@erase ".\Debug\Dboxebox32.pdb"
	-@erase ".\Debug\Dboxebox32.map"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"STDAFX.H" /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Dboxebox32.pch" /YX"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dboxebox.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dboxebox32.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 EBox_D.lib DBox_D.lib oldnames.lib /nologo /stack:0x2800 /subsystem:windows /map:"FULL" /debug /machine:IX86
# ADD LINK32 EBox_D32.lib DBox_D32.lib /nologo /stack:0x2800 /subsystem:windows /incremental:no /map /debug /machine:IX86
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=EBox_D32.lib DBox_D32.lib /nologo /stack:0x2800 /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Dboxebox32.pdb" /map:"$(INTDIR)/Dboxebox32.map"\
 /debug /machine:IX86 /def:".\Dboxebox.def" /out:"$(OUTDIR)/Dboxebox32.exe" 
DEF_FILE= \
	".\Dboxebox.def"
LINK32_OBJS= \
	"$(INTDIR)/Dboxebox.obj" \
	"$(INTDIR)/Dboxedoc.obj" \
	"$(INTDIR)/toolbar.obj" \
	"$(INTDIR)/Mainfrm.obj" \
	"$(INTDIR)/globals.obj" \
	"$(INTDIR)/Dboxevw.obj" \
	"$(INTDIR)/Stdafx.obj" \
	"$(INTDIR)/Dboxebox.res"

"$(OUTDIR)\Dboxebox32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

################################################################################
# Begin Target

# Name "Dboxebox - Win32 Release"
# Name "Dboxebox - Win32 Debug"

!IF  "$(CFG)" == "Dboxebox - Win32 Release"

!ELSEIF  "$(CFG)" == "Dboxebox - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Dboxebox.rc

!IF  "$(CFG)" == "Dboxebox - Win32 Release"


"$(INTDIR)\Dboxebox.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Dboxebox - Win32 Debug"

DEP_RSC_DBOXE=\
	".\Res\Dboxebox.ico"\
	".\Res\Dboxedoc.ico"\
	{$(INCLUDE)}"\Res\Button.cur"\
	".\Res\Dboxebox.rc2"\
	

"$(INTDIR)\Dboxebox.res" : $(SOURCE) $(DEP_RSC_DBOXE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "Dboxebox - Win32 Release"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dboxebox32.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dboxebox32.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Dboxebox - Win32 Debug"

# ADD BASE CPP /Yc"STDAFX.H"
# ADD CPP /Yc"STDAFX.H"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Fp"$(INTDIR)/Dboxebox32.pch" /Yc"STDAFX.H"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dboxebox32.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dboxebox.cpp

!IF  "$(CFG)" == "Dboxebox - Win32 Release"

DEP_CPP_DBOXEB=\
	".\stdafx.h"\
	{$(INCLUDE)}"\globals.h"\
	{$(INCLUDE)}"\toolbar.h"\
	{$(INCLUDE)}"\statbar.h"\
	".\Dboxebox.h"\
	".\Mainfrm.h"\
	".\Dboxedoc.h"\
	".\Dboxevw.h"\
	{$(INCLUDE)}"\Eboxdll.h"\
	{$(INCLUDE)}"\Dboxdll.h"\
	{$(INCLUDE)}"\Glb_elem.h"\
	{$(INCLUDE)}"\Dbglobal.h"\
	{$(INCLUDE)}"\Elembox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	{$(INCLUDE)}"\Elembar.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Palette.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\Eldefine.h"\
	{$(INCLUDE)}"\Drdefine.h"\
	{$(INCLUDE)}"\Spdefine.h"\
	

"$(INTDIR)\Dboxebox.obj" : $(SOURCE) $(DEP_CPP_DBOXEB) "$(INTDIR)"\
 "$(INTDIR)\Dboxebox32.pch"


!ELSEIF  "$(CFG)" == "Dboxebox - Win32 Debug"

DEP_CPP_DBOXEB=\
	".\stdafx.h"\
	{$(INCLUDE)}"\globals.h"\
	{$(INCLUDE)}"\toolbar.h"\
	{$(INCLUDE)}"\statbar.h"\
	".\Dboxebox.h"\
	".\Mainfrm.h"\
	".\Dboxedoc.h"\
	".\Dboxevw.h"\
	{$(INCLUDE)}"\Eboxdll.h"\
	{$(INCLUDE)}"\Dboxdll.h"\
	{$(INCLUDE)}"\Glb_elem.h"\
	{$(INCLUDE)}"\Dbglobal.h"\
	{$(INCLUDE)}"\Elembox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	{$(INCLUDE)}"\Eldefine.h"\
	{$(INCLUDE)}"\Drdefine.h"\
	{$(INCLUDE)}"\Spdefine.h"\
	{$(INCLUDE)}"\Elembar.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\Palette.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	

"$(INTDIR)\Dboxebox.obj" : $(SOURCE) $(DEP_CPP_DBOXEB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Mainfrm.cpp
DEP_CPP_MAINF=\
	".\stdafx.h"\
	".\Dboxebox.h"\
	".\Mainfrm.h"\
	

"$(INTDIR)\Mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Dboxebox32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dboxevw.cpp

!IF  "$(CFG)" == "Dboxebox - Win32 Release"

DEP_CPP_DBOXEV=\
	".\stdafx.h"\
	".\Dboxebox.h"\
	".\Mainfrm.h"\
	".\Dbebextn.h"\
	".\Dboxedoc.h"\
	".\Dboxevw.h"\
	{$(INCLUDE)}"\Elembox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	{$(INCLUDE)}"\Elembar.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Palette.h"\
	{$(INCLUDE)}"\toolbar.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	

"$(INTDIR)\Dboxevw.obj" : $(SOURCE) $(DEP_CPP_DBOXEV) "$(INTDIR)"\
 "$(INTDIR)\Dboxebox32.pch"


!ELSEIF  "$(CFG)" == "Dboxebox - Win32 Debug"

DEP_CPP_DBOXEV=\
	".\stdafx.h"\
	".\Dboxebox.h"\
	".\Mainfrm.h"\
	".\Dbebextn.h"\
	".\Dboxedoc.h"\
	".\Dboxevw.h"\
	{$(INCLUDE)}"\Elembox.h"\
	{$(INCLUDE)}"\Drawbox.h"\
	{$(INCLUDE)}"\Elembar.h"\
	{$(INCLUDE)}"\Curvebox.h"\
	{$(INCLUDE)}"\Patchbox.h"\
	{$(INCLUDE)}"\Solidbox.h"\
	{$(INCLUDE)}"\Dboxbutt.h"\
	{$(INCLUDE)}"\Drawbar.h"\
	{$(INCLUDE)}"\Colorsqu.h"\
	{$(INCLUDE)}"\Palette.h"\
	{$(INCLUDE)}"\Curvebar.h"\
	{$(INCLUDE)}"\Patchbar.h"\
	{$(INCLUDE)}"\Solidbar.h"\
	{$(INCLUDE)}"\toolbar.h"\
	

"$(INTDIR)\Dboxevw.obj" : $(SOURCE) $(DEP_CPP_DBOXEV) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dboxebox.def

!IF  "$(CFG)" == "Dboxebox - Win32 Release"

!ELSEIF  "$(CFG)" == "Dboxebox - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dboxedoc.cpp
DEP_CPP_DBOXED=\
	".\stdafx.h"\
	".\Dboxebox.h"\
	".\Dboxedoc.h"\
	

"$(INTDIR)\Dboxedoc.obj" : $(SOURCE) $(DEP_CPP_DBOXED) "$(INTDIR)"\
 "$(INTDIR)\Dboxebox32.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=\drgraf4_0\Toolboxs\Elembox\toolbar.cpp
DEP_CPP_TOOLB=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\..\Elembox\toolbar.h"\
	".\..\Elembox\globals.h"\
	

"$(INTDIR)\toolbar.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"\
 "$(INTDIR)\Dboxebox32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\drgraf4_0\Toolboxs\Elembox\globals.cpp
DEP_CPP_GLOBA=\
	{$(INCLUDE)}"\Stdafx.h"\
	".\..\Elembox\globals.h"\
	

"$(INTDIR)\globals.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"\
 "$(INTDIR)\Dboxebox32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
