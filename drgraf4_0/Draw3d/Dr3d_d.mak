# Microsoft Visual C++ generated build script - Do not modify

PROJ = DR3D_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\DRAW3D\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DR3DDLL.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G3 /W4 /Zi /ALw /YX /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"DR3D_D.PDB"  /Bd /Fp"DR3D_D.PCH"
CFLAGS_R_WDLL = /nologo /W3 /ALw /YX /O1 /D "NDEBUG" /FR /GD /Fp"DR3D_D.PCH"
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo /k
RUNFLAGS = 
DEFFILE = DR3D_D.DEF
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
SBRS = 3DMATH.SBR \
		DR3DDLL.SBR \
		DRCLIP.SBR \
		XFORM.SBR \
		DR3DMGR.SBR


3DMATH_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\3dmath.h


DR3DDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dglobal.h \
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\dr3ddll.h


DRCLIP_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drclip.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_view.h


XFORM_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h


DR3DMGR_DEP = d:\drgraf\allheads\stdafx.h


DR3DMGR_DEP = d:\drgraf\allheads\curdef.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\dr3ddll.h \
	d:\drgraf\allheads\dr3dmgr.h


all:	$(PROJ).DLL

3DMATH.OBJ:	3DMATH.CPP $(3DMATH_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c 3DMATH.CPP

DR3DDLL.OBJ:	DR3DDLL.CPP $(DR3DDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DR3DDLL.CPP

DRCLIP.OBJ:	DRCLIP.CPP $(DRCLIP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRCLIP.CPP

XFORM.OBJ:	XFORM.CPP $(XFORM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c XFORM.CPP

DR3D.RES:	DR3D.RC $(DR3D_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DR3D.RC

DR3DMGR.OBJ:	DR3DMGR.CPP $(DR3DMGR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DR3DMGR.CPP


$(PROJ).DLL::	DR3D.RES

$(PROJ).DLL::	3DMATH.OBJ DR3DDLL.OBJ DRCLIP.OBJ XFORM.OBJ DR3DMGR.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
3DMATH.OBJ +
DR3DDLL.OBJ +
DRCLIP.OBJ +
XFORM.OBJ +
DR3DMGR.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
d:\msvc\lib\+
d:\msvc\mfc\lib\+
d:\drgraf\lib_d\+
d:\c3d\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) DR3D.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	DR3D.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DR3D.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
