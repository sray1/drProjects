# Microsoft Visual C++ generated build script - Do not modify

PROJ = DDLG_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\DRAW_DLG\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP =             
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"DDLG_D.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D Spec_D OMgr_D draw_D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = DDLG_D.DEF
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
SBRS = DLG_ELAB.SBR \
		DLG_ILAB.SBR \
		DDLGDLL.SBR \
		DDLGMGR.SBR


DLG_ELAB_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\draw_dlg\dlg_elab.h


DLG_ILAB_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\draw_dlg\dlg_ilab.h


DDLGDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\ddlgdll.h \
	d:\drgraf\allheads\drawbox.h


DDLGMGR_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\draw_dlg\dlg_ilab.h \
	d:\drgraf\draw_dlg\dlg_elab.h \
	d:\drgraf\allheads\ddlgdll.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\draw_dlg\ddlgmgr.h


DDLGRSRC_RCDEP = d:\drgraf\res\image1d.bmp \
	d:\drgraf\res\image1f.bmp \
	d:\drgraf\res\image2d.bmp \
	d:\drgraf\res\image2f.bmp \
	d:\drgraf\res\image2u.bmp \
	d:\drgraf\res\image1u.bmp


all:	$(PROJ).DLL

DLG_ELAB.OBJ:	DLG_ELAB.CPP $(DLG_ELAB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_ELAB.CPP

DLG_ILAB.OBJ:	DLG_ILAB.CPP $(DLG_ILAB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_ILAB.CPP

DDLGDLL.OBJ:	DDLGDLL.CPP $(DDLGDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DDLGDLL.CPP

DDLGMGR.OBJ:	DDLGMGR.CPP $(DDLGMGR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DDLGMGR.CPP

DDLGRSRC.RES:	DDLGRSRC.RC $(DDLGRSRC_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DDLGRSRC.RC


$(PROJ).DLL::	DDLGRSRC.RES

$(PROJ).DLL::	DLG_ELAB.OBJ DLG_ILAB.OBJ DDLGDLL.OBJ DDLGMGR.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DLG_ELAB.OBJ +
DLG_ILAB.OBJ +
DDLGDLL.OBJ +
DDLGMGR.OBJ +
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
	$(RC) $(RESFLAGS) DDLGRSRC.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	DDLGRSRC.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DDLGRSRC.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
