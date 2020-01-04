# Microsoft Visual C++ generated build script - Do not modify

PROJ = SPEC_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\SPECIALS\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DATAWIND.CPP
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /D "SUPPORT_OBSOLETE_SYSTEMS" /GD /GEf /Fd"SPEC_D.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D Dr3D_D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = SPEC_D.DEF
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
SBRS = DATAWIND.SBR \
		BOOLEANS.SBR \
		DRFONT.SBR \
		DRPEN.SBR \
		HITNET.SBR \
		LAYER.SBR \
		MAPFACTO.SBR \
		UNIT.SBR \
		PRECISON.SBR \
		SCALEFAC.SBR \
		SPECDLL.SBR \
		DROBJECT.SBR \
		OBJ3DMNU.SBR \
		PATCHMNU.SBR \
		DLISTMGR.SBR


DATAWIND_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\datawind.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


BOOLEANS_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\booleans.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


DRFONT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


DRPEN_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


HITNET_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\hitnet.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


LAYER_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


MAPFACTO_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


UNIT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\unit.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


PRECISON_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


SCALEFAC_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\scalefac.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


SPECDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spglobal.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\specdll.h \
	d:\drgraf\allheads\drawbox.h


DROBJECT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drclip.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h


OBJ3DMNU_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\obj3dmnu.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


PATCHMNU_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\patchmnu.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


DLISTMGR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h


all:	$(PROJ).DLL

DATAWIND.OBJ:	DATAWIND.CPP $(DATAWIND_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DATAWIND.CPP

BOOLEANS.OBJ:	BOOLEANS.CPP $(BOOLEANS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BOOLEANS.CPP

DRFONT.OBJ:	DRFONT.CPP $(DRFONT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRFONT.CPP

DRPEN.OBJ:	DRPEN.CPP $(DRPEN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRPEN.CPP

HITNET.OBJ:	HITNET.CPP $(HITNET_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c HITNET.CPP

LAYER.OBJ:	LAYER.CPP $(LAYER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LAYER.CPP

MAPFACTO.OBJ:	MAPFACTO.CPP $(MAPFACTO_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAPFACTO.CPP

UNIT.OBJ:	UNIT.CPP $(UNIT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c UNIT.CPP

PRECISON.OBJ:	PRECISON.CPP $(PRECISON_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PRECISON.CPP

SCALEFAC.OBJ:	SCALEFAC.CPP $(SCALEFAC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SCALEFAC.CPP

SPECDLL.OBJ:	SPECDLL.CPP $(SPECDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPECDLL.CPP

DROBJECT.OBJ:	DROBJECT.CPP $(DROBJECT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DROBJECT.CPP

OBJ3DMNU.OBJ:	OBJ3DMNU.CPP $(OBJ3DMNU_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c OBJ3DMNU.CPP

PATCHMNU.OBJ:	PATCHMNU.CPP $(PATCHMNU_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PATCHMNU.CPP

DLISTMGR.OBJ:	DLISTMGR.CPP $(DLISTMGR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLISTMGR.CPP


$(PROJ).DLL::	DATAWIND.OBJ BOOLEANS.OBJ DRFONT.OBJ DRPEN.OBJ HITNET.OBJ LAYER.OBJ \
	MAPFACTO.OBJ UNIT.OBJ PRECISON.OBJ SCALEFAC.OBJ SPECDLL.OBJ DROBJECT.OBJ OBJ3DMNU.OBJ \
	PATCHMNU.OBJ DLISTMGR.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DATAWIND.OBJ +
BOOLEANS.OBJ +
DRFONT.OBJ +
DRPEN.OBJ +
HITNET.OBJ +
LAYER.OBJ +
MAPFACTO.OBJ +
UNIT.OBJ +
PRECISON.OBJ +
SCALEFAC.OBJ +
SPECDLL.OBJ +
DROBJECT.OBJ +
OBJ3DMNU.OBJ +
PATCHMNU.OBJ +
DLISTMGR.OBJ +
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
