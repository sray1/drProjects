# Microsoft Visual C++ generated build script - Do not modify

PROJ = DBOX_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\TOOLBOXS\DRAWBOX\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DRAWBAR.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W4 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"D_BOX.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D OMgr_D EBox_D ldllcew libw oldnames commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = DBOX_D.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = DRAWBAR.SBR \
		STDAFX.SBR \
		COLORSQU.SBR \
		DRAWBOX.SBR \
		DBOXDLL.SBR


DRAWBAR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\toolboxs\inc\dboxbutt.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\inc\drawbar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\colorsqu.h


STDAFX_DEP = d:\drgraf\allheads\stdafx.h


DBOX_RCDEP = d:\drgraf\toolboxs\drawbox\res\palette.bmp \
	d:\drgraf\toolboxs\drawbox\res\button.cur


COLORSQU_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\inc\dboxbutt.h \
	d:\drgraf\toolboxs\inc\drawbar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\colorsqu.h


DRAWBOX_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\toolboxs\inc\dboxbutt.h \
	d:\drgraf\toolboxs\inc\dbextern.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\inc\drawbar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\colorsqu.h


DBOXDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\toolboxs\inc\dbglobal.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\toolboxs\inc\dboxdll.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\inc\dboxbutt.h \
	d:\drgraf\toolboxs\inc\drawbar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\colorsqu.h


all:	$(PROJ).DLL

DRAWBAR.OBJ:	DRAWBAR.CPP $(DRAWBAR_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DRAWBAR.CPP

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STDAFX.CPP

DBOX.RES:	DBOX.RC $(DBOX_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DBOX.RC

COLORSQU.OBJ:	COLORSQU.CPP $(COLORSQU_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COLORSQU.CPP

DRAWBOX.OBJ:	DRAWBOX.CPP $(DRAWBOX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRAWBOX.CPP

DBOXDLL.OBJ:	DBOXDLL.CPP $(DBOXDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DBOXDLL.CPP


$(PROJ).DLL::	DBOX.RES

$(PROJ).DLL::	DRAWBAR.OBJ STDAFX.OBJ COLORSQU.OBJ DRAWBOX.OBJ DBOXDLL.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DRAWBAR.OBJ +
STDAFX.OBJ +
COLORSQU.OBJ +
DRAWBOX.OBJ +
DBOXDLL.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
d:\msvc\lib\+
d:\msvc\mfc\lib\+
d:\drgraf\lib\+
d:\c3d\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) DBOX.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	DBOX.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DBOX.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
