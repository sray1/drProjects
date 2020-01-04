# Microsoft Visual C++ generated build script - Do not modify

PROJ = DRAW_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\DRAWOBJS\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DRAWDLL.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"DRAW_D.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D Dr3D_D Spec_D Elem_D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = DRAW_D.DEF
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
SBRS = DRAWDLL.SBR \
		DRFREHND.SBR \
		DRLABEL.SBR \
		DRPRISM.SBR \
		DRGRID.SBR


DRAWDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drglobal.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drawdll.h \
	d:\drgraf\allheads\drawbox.h


DRFREHND_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drextern.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drfrehnd.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


DRLABEL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\drextern.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h


DRPRISM_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drprism.h


DRGRID_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drextern.h \
	d:\drgraf\allheads\drgrid.h


all:	$(PROJ).DLL

DRAWDLL.OBJ:	DRAWDLL.CPP $(DRAWDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DRAWDLL.CPP

DRFREHND.OBJ:	DRFREHND.CPP $(DRFREHND_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRFREHND.CPP

DRLABEL.OBJ:	DRLABEL.CPP $(DRLABEL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRLABEL.CPP

DRPRISM.OBJ:	DRPRISM.CPP $(DRPRISM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRPRISM.CPP

DRGRID.OBJ:	DRGRID.CPP $(DRGRID_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRGRID.CPP


$(PROJ).DLL::	DRAWDLL.OBJ DRFREHND.OBJ DRLABEL.OBJ DRPRISM.OBJ DRGRID.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DRAWDLL.OBJ +
DRFREHND.OBJ +
DRLABEL.OBJ +
DRPRISM.OBJ +
DRGRID.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
d:\msvc\lib\+
d:\msvc\mfc\lib\+
d:\drgraf\lib_D\+
d:\c3d\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@
	implib /nowep $(PROJ).LIB $(PROJ).DLL


run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
