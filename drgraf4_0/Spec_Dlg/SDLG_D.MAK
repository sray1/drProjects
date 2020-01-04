# Microsoft Visual C++ generated build script - Do not modify

PROJ = SDLG_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\SPEC_DLG\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DLG_LAYR.CPP
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"SDLG_D.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D OMgr_D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = SDLG_D.DEF
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
SBRS = DLG_LAYR.SBR \
		DLG_PEN.SBR \
		DLG_PREC.SBR \
		DLG_SFAC.SBR \
		DLG_UNIT.SBR \
		SPIN.SBR \
		SDLGDLL.SBR \
		PAREDIT.SBR \
		SDLGMGR.SBR \
		DLGOBJ3D.SBR \
		DLGPATCH.SBR


DLG_LAYR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\mi_cur_i.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\inter_c3.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\mi_obj3d.h \
	d:\drgraf\allheads\drobj3d.h \
	d:\drgraf\allheads\glb_mous.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\booleans.h \
	d:\drgraf\allheads\datawind.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\hitnet.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\patchmnu.h \
	d:\drgraf\allheads\obj3dmnu.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\spec_dlg\dlg_layr.h


DLG_PEN_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\mi_cur_i.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\inter_c3.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\mi_obj3d.h \
	d:\drgraf\allheads\drobj3d.h \
	d:\drgraf\allheads\glb_mous.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\booleans.h \
	d:\drgraf\allheads\datawind.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\hitnet.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\patchmnu.h \
	d:\drgraf\allheads\obj3dmnu.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\spec_dlg\dlg_pen.h \
	d:\drgraf\allheads\paredit.h \
	d:\drgraf\allheads\spin.h \
	d:\drgraf\allheads\muscroll.h \
	d:\drgraf\spec_dlg\otherids.h


DLG_PREC_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgrafrm.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\toolboxs\inc\elembox.h \
	d:\drgraf\toolboxs\inc\elembar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\curvebox.h \
	d:\drgraf\toolboxs\inc\curvebar.h \
	d:\drgraf\toolboxs\inc\patchbox.h \
	d:\drgraf\toolboxs\inc\patchbar.h \
	d:\drgraf\toolboxs\inc\solidbox.h \
	d:\drgraf\toolboxs\inc\solidbar.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\inc\dboxbutt.h \
	d:\drgraf\toolboxs\inc\drawbar.h \
	d:\drgraf\toolboxs\inc\colorsqu.h \
	d:\drgraf\allheads\drstatus.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\scalefac.h \
	d:\drgraf\allheads\unit.h \
	d:\drgraf\spec_dlg\dlg_prec.h


DLG_SFAC_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgrafrm.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\toolboxs\inc\elembox.h \
	d:\drgraf\toolboxs\inc\elembar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\curvebox.h \
	d:\drgraf\toolboxs\inc\curvebar.h \
	d:\drgraf\toolboxs\inc\patchbox.h \
	d:\drgraf\toolboxs\inc\patchbar.h \
	d:\drgraf\toolboxs\inc\solidbox.h \
	d:\drgraf\toolboxs\inc\solidbar.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\inc\dboxbutt.h \
	d:\drgraf\toolboxs\inc\drawbar.h \
	d:\drgraf\toolboxs\inc\colorsqu.h \
	d:\drgraf\allheads\drstatus.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\scalefac.h \
	d:\drgraf\allheads\unit.h \
	d:\drgraf\spec_dlg\dlg_sfac.h


DLG_UNIT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgrafrm.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\toolboxs\inc\elembox.h \
	d:\drgraf\toolboxs\inc\elembar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\curvebox.h \
	d:\drgraf\toolboxs\inc\curvebar.h \
	d:\drgraf\toolboxs\inc\patchbox.h \
	d:\drgraf\toolboxs\inc\patchbar.h \
	d:\drgraf\toolboxs\inc\solidbox.h \
	d:\drgraf\toolboxs\inc\solidbar.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\inc\dboxbutt.h \
	d:\drgraf\toolboxs\inc\drawbar.h \
	d:\drgraf\toolboxs\inc\colorsqu.h \
	d:\drgraf\allheads\drstatus.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\scalefac.h \
	d:\drgraf\allheads\unit.h \
	d:\drgraf\spec_dlg\dlg_unit.h


SPIN_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spin.h \
	d:\drgraf\allheads\muscroll.h


SDLGDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\spec_dlg\sdlgdll.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\inc\dboxbutt.h \
	d:\drgraf\toolboxs\inc\drawbar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\colorsqu.h


SPEC_DLG_RCDEP = d:\drgraf\res\image1d.bmp \
	d:\drgraf\res\image1f.bmp \
	d:\drgraf\res\image2d.bmp \
	d:\drgraf\res\image2f.bmp \
	d:\drgraf\res\image2u.bmp \
	d:\drgraf\res\image1u.bmp \
	d:\drgraf\spec_dlg\spec_dlg.rc2


PAREDIT_DEP = d:\drgraf\allheads\paredit.h \
	d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spin.h \
	d:\drgraf\allheads\muscroll.h


SDLGMGR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\spec_dlg\dlg_layr.h \
	d:\drgraf\spec_dlg\dlg_pen.h \
	d:\drgraf\allheads\paredit.h \
	d:\drgraf\allheads\spin.h \
	d:\drgraf\allheads\muscroll.h \
	d:\drgraf\spec_dlg\otherids.h \
	d:\drgraf\spec_dlg\dlg_sfac.h \
	d:\drgraf\spec_dlg\dlg_prec.h \
	d:\drgraf\spec_dlg\dlg_unit.h \
	d:\drgraf\spec_dlg\dlgobj3d.h \
	d:\drgraf\spec_dlg\dlgpatch.h \
	d:\drgraf\spec_dlg\sdlgdll.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\toolboxs\inc\dboxbutt.h \
	d:\drgraf\toolboxs\inc\drawbar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\colorsqu.h \
	d:\drgraf\allheads\sdlgmgr.h


DLGOBJ3D_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\mi_cur_i.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\inter_c3.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\mi_obj3d.h \
	d:\drgraf\allheads\drobj3d.h \
	d:\drgraf\allheads\glb_mous.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\booleans.h \
	d:\drgraf\allheads\datawind.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\hitnet.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\patchmnu.h \
	d:\drgraf\allheads\obj3dmnu.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\spec_dlg\dlgobj3d.h


DLGPATCH_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\mi_cur_i.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\inter_c3.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\mi_obj3d.h \
	d:\drgraf\allheads\drobj3d.h \
	d:\drgraf\allheads\glb_mous.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\booleans.h \
	d:\drgraf\allheads\datawind.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\hitnet.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\patchmnu.h \
	d:\drgraf\allheads\obj3dmnu.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\spec_dlg\dlgpatch.h


all:	$(PROJ).DLL

DLG_LAYR.OBJ:	DLG_LAYR.CPP $(DLG_LAYR_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DLG_LAYR.CPP

DLG_PEN.OBJ:	DLG_PEN.CPP $(DLG_PEN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_PEN.CPP

DLG_PREC.OBJ:	DLG_PREC.CPP $(DLG_PREC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_PREC.CPP

DLG_SFAC.OBJ:	DLG_SFAC.CPP $(DLG_SFAC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_SFAC.CPP

DLG_UNIT.OBJ:	DLG_UNIT.CPP $(DLG_UNIT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_UNIT.CPP

SPIN.OBJ:	SPIN.CPP $(SPIN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SPIN.CPP

SDLGDLL.OBJ:	SDLGDLL.CPP $(SDLGDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SDLGDLL.CPP

SPEC_DLG.RES:	SPEC_DLG.RC $(SPEC_DLG_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r SPEC_DLG.RC

PAREDIT.OBJ:	PAREDIT.CPP $(PAREDIT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PAREDIT.CPP

SDLGMGR.OBJ:	SDLGMGR.CPP $(SDLGMGR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SDLGMGR.CPP

DLGOBJ3D.OBJ:	DLGOBJ3D.CPP $(DLGOBJ3D_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLGOBJ3D.CPP

DLGPATCH.OBJ:	DLGPATCH.CPP $(DLGPATCH_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLGPATCH.CPP


$(PROJ).DLL::	SPEC_DLG.RES

$(PROJ).DLL::	DLG_LAYR.OBJ DLG_PEN.OBJ DLG_PREC.OBJ DLG_SFAC.OBJ DLG_UNIT.OBJ SPIN.OBJ \
	SDLGDLL.OBJ PAREDIT.OBJ SDLGMGR.OBJ DLGOBJ3D.OBJ DLGPATCH.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DLG_LAYR.OBJ +
DLG_PEN.OBJ +
DLG_PREC.OBJ +
DLG_SFAC.OBJ +
DLG_UNIT.OBJ +
SPIN.OBJ +
SDLGDLL.OBJ +
PAREDIT.OBJ +
SDLGMGR.OBJ +
DLGOBJ3D.OBJ +
DLGPATCH.OBJ +
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
	$(RC) $(RESFLAGS) SPEC_DLG.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	SPEC_DLG.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) SPEC_DLG.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
