# Microsoft Visual C++ generated build script - Do not modify

PROJ = MOUSE_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\MOUSEMGR\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DBMOUSE.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W4 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"MOUSE_D.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D OMgr_D Spec_d Draw_D Elem_D EDlg_D DDlg_D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = MOUSE_D.DEF
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
SBRS = MOUSEDLL.SBR \
		MOUSE.SBR \
		DBMOUSE.SBR \
		MOUSEMGR.SBR \
		ELMOUSE.SBR


MOUSEDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\mousemgr\mousedll.h \
	d:\drgraf\toolboxs\drawbox\inc\drawbox.h \
	d:\drgraf\toolboxs\drawbox\inc\dboxbutt.h \
	d:\drgraf\toolboxs\drawbox\inc\drawbar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\drawbox\inc\colorsqu.h


MOUSE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\mousemgr\otherids.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\waitcur.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\precison.h


DBMOUSE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\mousemgr\otherids.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\waitcur.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\dbobject.h \
	d:\drgraf\allheads\curdef.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\booleans.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\freehand.h \
	d:\drgraf\allheads\dlg_ilab.h \
	d:\drgraf\allheads\label.h \
	d:\drgraf\allheads\node.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\dlg_elab.h


MOUSEMGR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\curdef.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\dbmouse.h


ELMOUSE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\mousemgr\otherids.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\waitcur.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\dbobject.h \
	d:\drgraf\allheads\dlg_node.h \
	d:\drgraf\allheads\node.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\label.h \
	d:\drgraf\allheads\dlg_pipe.h \
	d:\drgraf\allheads\pipe.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elglobal.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\booleans.h


all:	$(PROJ).DLL

MOUSEDLL.OBJ:	MOUSEDLL.CPP $(MOUSEDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MOUSEDLL.CPP

MOUSE.OBJ:	MOUSE.CPP $(MOUSE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MOUSE.CPP

DBMOUSE.OBJ:	DBMOUSE.CPP $(DBMOUSE_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DBMOUSE.CPP

MOUSEMGR.OBJ:	MOUSEMGR.CPP $(MOUSEMGR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MOUSEMGR.CPP

ELMOUSE.OBJ:	ELMOUSE.CPP $(ELMOUSE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ELMOUSE.CPP


$(PROJ).DLL::	MOUSEDLL.OBJ MOUSE.OBJ DBMOUSE.OBJ MOUSEMGR.OBJ ELMOUSE.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
MOUSEDLL.OBJ +
MOUSE.OBJ +
DBMOUSE.OBJ +
MOUSEMGR.OBJ +
ELMOUSE.OBJ +
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
	$(RC) $(RESFLAGS) $@
	implib /nowep $(PROJ).LIB $(PROJ).DLL


run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
