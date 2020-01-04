# Microsoft Visual C++ generated build script - Do not modify

PROJ = OMGR_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\GRAFMGR\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = OBJMGR.CPP  
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"OMGR_D.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D Spec_D Elem_D Draw_D Dr3D_D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = OMGR_D.DEF
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
SBRS = OBJMGR.SBR \
		OMGRDLL.SBR \
		EBOXMGR.SBR \
		DBOXMGR.SBR \
		NEWOBJS.SBR


OBJMGR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\tldefine.h \
	d:\drgraf\allheads\tlglobal.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elglobal.h \
	d:\drgraf\allheads\drpipe.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\dr3dmgr.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\booleans.h \
	d:\drgraf\allheads\datawind.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\hitnet.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\scalefac.h \
	d:\drgraf\allheads\unit.h \
	d:\drgraf\allheads\patchmnu.h \
	d:\drgraf\allheads\obj3dmnu.h


OMGRDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\omgrdll.h \
	d:\drgraf\allheads\drawbox.h


EBOXMGR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\eboxmgr.h


DBOXMGR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\dboxmgr.h


NEWOBJS_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\tldefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\booleans.h \
	d:\drgraf\allheads\datawind.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\hitnet.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\scalefac.h \
	d:\drgraf\allheads\unit.h \
	d:\drgraf\allheads\obj3dmnu.h \
	d:\drgraf\allheads\patchmnu.h \
	d:\drgraf\allheads\newobjs.h


all:	$(PROJ).DLL

OBJMGR.OBJ:	OBJMGR.CPP $(OBJMGR_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c OBJMGR.CPP

OMGRDLL.OBJ:	OMGRDLL.CPP $(OMGRDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c OMGRDLL.CPP

EBOXMGR.OBJ:	EBOXMGR.CPP $(EBOXMGR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EBOXMGR.CPP

DBOXMGR.OBJ:	DBOXMGR.CPP $(DBOXMGR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DBOXMGR.CPP

NEWOBJS.OBJ:	NEWOBJS.CPP $(NEWOBJS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c NEWOBJS.CPP


$(PROJ).DLL::	OBJMGR.OBJ OMGRDLL.OBJ EBOXMGR.OBJ DBOXMGR.OBJ NEWOBJS.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
OBJMGR.OBJ +
OMGRDLL.OBJ +
EBOXMGR.OBJ +
DBOXMGR.OBJ +
NEWOBJS.OBJ +
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
