# Microsoft Developer Studio Generated NMAKE File, Based on dllhusk.dsp
!IF "$(CFG)" == ""
CFG=DLLHusk - Win32 Release
!MESSAGE No configuration specified.  Defaulting to DLLHusk - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "DLLHusk - Win32 Release" && "$(CFG)" !=\
 "DLLHusk - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "dllhusk.mak" CFG="DLLHusk - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DLLHusk - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DLLHusk - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DLLHusk - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

ALL : "TestDll2 - Win32 Release" "TestDll1 - Win32 Release"\
 "$(OUTDIR)\dllhusk.exe"

CLEAN : 
	-@erase "$(INTDIR)\dllhusk.obj"
	-@erase "$(INTDIR)\dllhusk.res"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\dllhusk.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/dllhusk.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/dllhusk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Release\TestDll1.lib Release\TestDll2.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/dllhusk.pdb" /machine:I386\
 /out:"$(OUTDIR)/dllhusk.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dllhusk.obj" \
	"$(INTDIR)\dllhusk.res" \
	"$(INTDIR)\mainfrm.obj" \
	"$(OUTDIR)\TestDll1.lib" \
	"$(OUTDIR)\TestDll2.lib"

"$(OUTDIR)\dllhusk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DLLHusk - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

ALL : "TestDll2 - Win32 Debug" "TestDll1 - Win32 Debug" "$(OUTDIR)\dllhusk.exe"

CLEAN : 
	-@erase "$(INTDIR)\dllhusk.obj"
	-@erase "$(INTDIR)\dllhusk.res"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\dllhusk.exe"
	-@erase "$(OUTDIR)\dllhusk.ilk"
	-@erase "$(OUTDIR)\dllhusk.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/dllhusk.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/dllhusk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Debug\TestDll1.lib Debug\TestDll2.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/dllhusk.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/dllhusk.exe" 
LINK32_OBJS= \
	"$(INTDIR)\dllhusk.obj" \
	"$(INTDIR)\dllhusk.res" \
	"$(INTDIR)\mainfrm.obj" \
	"$(OUTDIR)\TestDll1.lib" \
	"$(OUTDIR)\TestDll2.lib"

"$(OUTDIR)\dllhusk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) $(CPP_PROJ) $<  


!IF "$(CFG)" == "DLLHusk - Win32 Release" || "$(CFG)" ==\
 "DLLHusk - Win32 Debug"
SOURCE=.\dllhusk.cpp
DEP_CPP_DLLHU=\
	".\dllhusk.h"\
	".\mainfrm.h"\
	".\stdafx.h"\
	".\testdll1.h"\
	".\testdll2.h"\
	

!IF  "$(CFG)" == "DLLHusk - Win32 Release"


"$(INTDIR)\dllhusk.obj" : $(SOURCE) $(DEP_CPP_DLLHU) "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "DLLHusk - Win32 Debug"


"$(INTDIR)\dllhusk.obj" : $(SOURCE) $(DEP_CPP_DLLHU) "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\dllhusk.rc
DEP_RSC_DLLHUS=\
	".\res\dllhusk.ico"\
	".\res\toolbar.bmp"\
	

"$(INTDIR)\dllhusk.res" : $(SOURCE) $(DEP_RSC_DLLHUS) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\mainfrm.cpp
DEP_CPP_MAINF=\
	".\dllhusk.h"\
	".\mainfrm.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "DLLHusk - Win32 Release"


"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ELSEIF  "$(CFG)" == "DLLHusk - Win32 Debug"


"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /FD /c $(SOURCE)


!ENDIF 

SOURCE=.\dllhusk.h
SOURCE=.\mainfrm.h
SOURCE=.\stdafx.h
SOURCE=.\testdll1.h
SOURCE=.\testdll2.h
SOURCE=.\res\dllhusk.ico
SOURCE=.\res\toolbar.bmp

!IF  "$(CFG)" == "DLLHusk - Win32 Release"

"TestDll1 - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\TestDll1.mak CFG="TestDll1 - Win32 Release" 
   cd "."

!ELSEIF  "$(CFG)" == "DLLHusk - Win32 Debug"

"TestDll1 - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\TestDll1.mak CFG="TestDll1 - Win32 Debug" 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "DLLHusk - Win32 Release"

"TestDll2 - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\TestDll2.mak CFG="TestDll2 - Win32 Release" 
   cd "."

!ELSEIF  "$(CFG)" == "DLLHusk - Win32 Debug"

"TestDll2 - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\TestDll2.mak CFG="TestDll2 - Win32 Debug" 
   cd "."

!ENDIF 


!ENDIF 

