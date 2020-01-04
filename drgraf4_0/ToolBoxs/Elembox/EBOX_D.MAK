# Microsoft Visual C++ generated build script - Do not modify

PROJ = EBOX_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\TOOLBOXS\ELEMBOX\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = ELEMBOX.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W4 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"E_BOX.PDB"
CFLAGS_R_WDLL = /nologo /G2 /W4 /ALw /O1 /D "NDEBUG" /D "_AFXDLL" /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D ldllcew libw oldnames commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = MFC250 oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = EBOX_D.DEF
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
SBRS = ELEMBOX.SBR \
		ELEMBAR.SBR \
		PALETTE.SBR \
		STDAFX.SBR \
		EBOXDLL.SBR \
		PATCHBOX.SBR \
		PATCHBAR.SBR \
		CURVEBAR.SBR \
		CURVEBOX.SBR \
		SOLIDBAR.SBR \
		SOLIDBOX.SBR


EBOX_RCDEP = d:\drgraf\toolboxs\elembox\res\button.cur \
	d:\drgraf\toolboxs\elembox\res\elembar.bmp \
	d:\drgraf\toolboxs\elembox\res\patch.bmp \
	d:\drgraf\toolboxs\elembox\res\curve.bmp \
	d:\drgraf\toolboxs\elembox\res\solid.bmp


ELEMBOX_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\in_crcle.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\inter_c1.h \
	d:\drgraf\allheads\inter_c2.h \
	d:\drgraf\allheads\inter_c3.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
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
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\eboxbutt.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\toolboxs\inc\elembox.h \
	d:\drgraf\toolboxs\inc\elembar.h \
	d:\drgraf\toolboxs\inc\curvebox.h \
	d:\drgraf\toolboxs\inc\curvebar.h \
	d:\drgraf\toolboxs\inc\patchbox.h \
	d:\drgraf\toolboxs\inc\patchbar.h \
	d:\drgraf\toolboxs\inc\solidbox.h \
	d:\drgraf\toolboxs\inc\solidbar.h


ELEMBAR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\toolboxs\inc\eboxbutt.h \
	d:\drgraf\toolboxs\inc\elembox.h \
	d:\drgraf\toolboxs\inc\elembar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\curvebox.h \
	d:\drgraf\toolboxs\inc\curvebar.h \
	d:\drgraf\toolboxs\inc\patchbox.h \
	d:\drgraf\toolboxs\inc\patchbar.h \
	d:\drgraf\toolboxs\inc\solidbox.h \
	d:\drgraf\toolboxs\inc\solidbar.h


PALETTE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\palette.h


STDAFX_DEP = d:\drgraf\allheads\stdafx.h


EBOXDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_elem.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\cuglobal.h \
	d:\drgraf\allheads\paglobal.h \
	d:\drgraf\allheads\soglobal.h \
	d:\drgraf\toolboxs\inc\eboxdll.h \
	d:\drgraf\toolboxs\inc\elembox.h \
	d:\drgraf\toolboxs\inc\elembar.h \
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\curvebox.h \
	d:\drgraf\toolboxs\inc\curvebar.h \
	d:\drgraf\toolboxs\inc\patchbox.h \
	d:\drgraf\toolboxs\inc\patchbar.h \
	d:\drgraf\toolboxs\inc\solidbox.h \
	d:\drgraf\toolboxs\inc\solidbar.h


PATCHBOX_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\in_crcle.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\inter_c1.h \
	d:\drgraf\allheads\inter_c2.h \
	d:\drgraf\allheads\inter_c3.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
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
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\pboxbutt.h \
	d:\drgraf\allheads\paextern.h \
	d:\drgraf\toolboxs\inc\patchbox.h \
	d:\drgraf\toolboxs\inc\patchbar.h


PATCHBAR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\toolboxs\inc\pboxbutt.h \
	d:\drgraf\toolboxs\inc\patchbox.h \
	d:\drgraf\toolboxs\inc\patchbar.h \
	d:\drgraf\allheads\palette.h


CURVEBAR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\toolboxs\inc\cboxbutt.h \
	d:\drgraf\toolboxs\inc\curvebox.h \
	d:\drgraf\toolboxs\inc\curvebar.h \
	d:\drgraf\allheads\palette.h


CURVEBOX_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\in_crcle.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\inter_c1.h \
	d:\drgraf\allheads\inter_c2.h \
	d:\drgraf\allheads\inter_c3.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
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
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\cboxbutt.h \
	d:\drgraf\allheads\cuextern.h \
	d:\drgraf\toolboxs\inc\curvebox.h \
	d:\drgraf\toolboxs\inc\curvebar.h


SOLIDBAR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\toolboxs\inc\sboxbutt.h \
	d:\drgraf\toolboxs\inc\solidbox.h \
	d:\drgraf\toolboxs\inc\solidbar.h \
	d:\drgraf\allheads\palette.h


SOLIDBOX_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\in_crcle.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\inter_c1.h \
	d:\drgraf\allheads\inter_c2.h \
	d:\drgraf\allheads\inter_c3.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
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
	d:\drgraf\allheads\palette.h \
	d:\drgraf\toolboxs\inc\sboxbutt.h \
	d:\drgraf\allheads\soextern.h \
	d:\drgraf\toolboxs\inc\solidbox.h \
	d:\drgraf\toolboxs\inc\solidbar.h


all:	$(PROJ).DLL

EBOX.RES:	EBOX.RC $(EBOX_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EBOX.RC

ELEMBOX.OBJ:	ELEMBOX.CPP $(ELEMBOX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c ELEMBOX.CPP

ELEMBAR.OBJ:	ELEMBAR.CPP $(ELEMBAR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ELEMBAR.CPP

PALETTE.OBJ:	PALETTE.CPP $(PALETTE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PALETTE.CPP

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STDAFX.CPP

EBOXDLL.OBJ:	EBOXDLL.CPP $(EBOXDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EBOXDLL.CPP

PATCHBOX.OBJ:	PATCHBOX.CPP $(PATCHBOX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PATCHBOX.CPP

PATCHBAR.OBJ:	PATCHBAR.CPP $(PATCHBAR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PATCHBAR.CPP

CURVEBAR.OBJ:	CURVEBAR.CPP $(CURVEBAR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CURVEBAR.CPP

CURVEBOX.OBJ:	CURVEBOX.CPP $(CURVEBOX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CURVEBOX.CPP

SOLIDBAR.OBJ:	SOLIDBAR.CPP $(SOLIDBAR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SOLIDBAR.CPP

SOLIDBOX.OBJ:	SOLIDBOX.CPP $(SOLIDBOX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SOLIDBOX.CPP


$(PROJ).DLL::	EBOX.RES

$(PROJ).DLL::	ELEMBOX.OBJ ELEMBAR.OBJ PALETTE.OBJ STDAFX.OBJ EBOXDLL.OBJ PATCHBOX.OBJ \
	PATCHBAR.OBJ CURVEBAR.OBJ CURVEBOX.OBJ SOLIDBAR.OBJ SOLIDBOX.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
ELEMBOX.OBJ +
ELEMBAR.OBJ +
PALETTE.OBJ +
STDAFX.OBJ +
EBOXDLL.OBJ +
PATCHBOX.OBJ +
PATCHBAR.OBJ +
CURVEBAR.OBJ +
CURVEBOX.OBJ +
SOLIDBAR.OBJ +
SOLIDBOX.OBJ +
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
	$(RC) $(RESFLAGS) EBOX.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	EBOX.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EBOX.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
