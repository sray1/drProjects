# Microsoft Visual C++ generated build script - Do not modify

PROJ = DBOXEBOX
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\TOOLBOXS\DBOXEBOX\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_AFXDLL" /D "_DEBUG" /GA /GEf /Fd"DBOXEBOX.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W4 /AL /D "NDEBUG" /D "_AFXDLL" /GA /GEf 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mfc250d EBox_D DBox_D oldnames libw llibcew commdlg.lib shell.lib 
LIBS_R_WEXE = mfc250 EBox_D DBox_D oldnames libw llibcew commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = DBOXEBOX.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		DBOXEBOX.SBR \
		MAINFRM.SBR \
		DBOXEDOC.SBR \
		DBOXEVW.SBR


DBOXEBOX_RCDEP = d:\drgraf\toolboxs\dboxebox\res\dboxebox.ico \
	d:\drgraf\toolboxs\dboxebox\res\dboxedoc.ico \
	d:\drgraf\toolboxs\dboxebox\res\button.cur \
	d:\drgraf\toolboxs\dboxebox\res\dboxebox.rc2


STDAFX_DEP = d:\drgraf\allheads\stdafx.h


DBOXEBOX_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\toolboxs\dboxebox\dboxebox.h \
	d:\drgraf\toolboxs\dboxebox\mainfrm.h \
	d:\drgraf\allheads\elembox.h \
	d:\drgraf\toolboxs\elembox\inc\elembar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\drawbox\inc\dboxbutt.h \
	d:\drgraf\toolboxs\drawbox\inc\drawbar.h \
	d:\drgraf\toolboxs\drawbox\inc\colorsqu.h \
	d:\drgraf\toolboxs\dboxebox\dboxedoc.h \
	d:\drgraf\toolboxs\dboxebox\dboxevw.h \
	d:\drgraf\toolboxs\elembox\inc\eboxdll.h \
	d:\drgraf\toolboxs\drawbox\inc\dboxdll.h \
	d:\drgraf\allheads\elglobal.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\toolboxs\drawbox\inc\dbglobal.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\spdefine.h


MAINFRM_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\toolboxs\dboxebox\dboxebox.h \
	d:\drgraf\toolboxs\dboxebox\mainfrm.h \
	d:\drgraf\allheads\elembox.h \
	d:\drgraf\toolboxs\elembox\inc\elembar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\drawbox\inc\dboxbutt.h \
	d:\drgraf\toolboxs\drawbox\inc\drawbar.h \
	d:\drgraf\toolboxs\drawbox\inc\colorsqu.h


DBOXEDOC_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\toolboxs\dboxebox\dboxebox.h \
	d:\drgraf\toolboxs\dboxebox\dboxedoc.h


DBOXEVW_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\toolboxs\dboxebox\dboxebox.h \
	d:\drgraf\toolboxs\dboxebox\mainfrm.h \
	d:\drgraf\allheads\elembox.h \
	d:\drgraf\toolboxs\elembox\inc\elembar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\drawbox\inc\dboxbutt.h \
	d:\drgraf\toolboxs\drawbox\inc\drawbar.h \
	d:\drgraf\toolboxs\drawbox\inc\colorsqu.h \
	d:\drgraf\allheads\dbebextn.h \
	d:\drgraf\toolboxs\dboxebox\dboxedoc.h \
	d:\drgraf\toolboxs\dboxebox\dboxevw.h


all:	$(PROJ).EXE

DBOXEBOX.RES:	DBOXEBOX.RC $(DBOXEBOX_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DBOXEBOX.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

DBOXEBOX.OBJ:	DBOXEBOX.CPP $(DBOXEBOX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DBOXEBOX.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

DBOXEDOC.OBJ:	DBOXEDOC.CPP $(DBOXEDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DBOXEDOC.CPP

DBOXEVW.OBJ:	DBOXEVW.CPP $(DBOXEVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DBOXEVW.CPP


$(PROJ).EXE::	DBOXEBOX.RES

$(PROJ).EXE::	STDAFX.OBJ DBOXEBOX.OBJ MAINFRM.OBJ DBOXEDOC.OBJ DBOXEVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
DBOXEBOX.OBJ +
MAINFRM.OBJ +
DBOXEDOC.OBJ +
DBOXEVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\msvc\lib\+
d:\msvc\mfc\lib\+
d:\drgraf\lib\+
d:\c3d\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) DBOXEBOX.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	DBOXEBOX.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DBOXEBOX.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
