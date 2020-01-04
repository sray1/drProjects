# Microsoft Visual C++ generated build script - Do not modify

PROJ = ELEM_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\ELEMOBJS\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = ELEMDLL.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /D "_MESSAGETRACE" /GD /GEf /Fd"ELEM_D.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D Spec_D Dr3D_D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo /k
RUNFLAGS = 
DEFFILE = ELEM_D.DEF
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
SBRS = ELEMDLL.SBR \
		DRCURVE.SBR \
		DRNODE.SBR \
		DROBJ3D.SBR \
		DRPATCH.SBR \
		DRPIPE.SBR \
		DRPLATE.SBR \
		DRSOLID.SBR \
		DRFE3D.SBR \
		CURVE_1.SBR \
		CURVE_2.SBR \
		CURVE_3.SBR \
		DRPROF_C.SBR \
		MATOBJ.SBR \
		CURVE.SBR \
		SURFACE4.SBR


ELEMDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_elem.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elemdll.h \
	d:\drgraf\allheads\drawbox.h


DRCURVE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\mi_pat_i.h \
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
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
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
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\curve.h \
	d:\drgraf\allheads\curve_1.h \
	d:\drgraf\allheads\curve_2.h \
	d:\drgraf\allheads\curve_3.h


DRNODE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\drclip.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drfe3d.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\crdefine.h


DROBJ3D_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\drobj3d.h \
	d:\drgraf\allheads\drsolid.h


DRPATCH_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\surface4.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\drpatch.h


DRPIPE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drpipe.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h


DRPLATE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h


DRSOLID_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drfe3d.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\drpatch.h


DRFE3D_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drfe3d.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h


CURVE_1_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\mi_pat_i.h \
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
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
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
	d:\drgraf\allheads\curve_1.h \
	d:\drgraf\allheads\curve.h


CURVE_2_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\mi_pat_i.h \
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
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
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
	d:\drgraf\allheads\curve_2.h \
	d:\drgraf\allheads\curve.h


CURVE_3_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\mi_pat_i.h \
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
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
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
	d:\drgraf\allheads\curve_3.h \
	d:\drgraf\allheads\curve.h


DRPROF_C_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\matobj.h \
	d:\drgraf\allheads\drprof_c.h


MATOBJ_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\matobj.h \
	d:\drgraf\allheads\glb_type.h


CURVE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\curve.h \
	d:\drgraf\allheads\glb_cups.h


SURFACE4_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\allheads\curve_1.h \
	d:\drgraf\allheads\curve.h \
	d:\drgraf\allheads\curve_2.h \
	d:\drgraf\allheads\curve_3.h


all:	$(PROJ).DLL

ELEMDLL.OBJ:	ELEMDLL.CPP $(ELEMDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c ELEMDLL.CPP

DRCURVE.OBJ:	DRCURVE.CPP $(DRCURVE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRCURVE.CPP

DRNODE.OBJ:	DRNODE.CPP $(DRNODE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRNODE.CPP

DROBJ3D.OBJ:	DROBJ3D.CPP $(DROBJ3D_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DROBJ3D.CPP

DRPATCH.OBJ:	DRPATCH.CPP $(DRPATCH_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRPATCH.CPP

DRPIPE.OBJ:	DRPIPE.CPP $(DRPIPE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRPIPE.CPP

DRPLATE.OBJ:	DRPLATE.CPP $(DRPLATE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRPLATE.CPP

DRSOLID.OBJ:	DRSOLID.CPP $(DRSOLID_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRSOLID.CPP

DRFE3D.OBJ:	DRFE3D.CPP $(DRFE3D_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRFE3D.CPP

CURVE_1.OBJ:	CURVE_1.CPP $(CURVE_1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CURVE_1.CPP

CURVE_2.OBJ:	CURVE_2.CPP $(CURVE_2_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CURVE_2.CPP

CURVE_3.OBJ:	CURVE_3.CPP $(CURVE_3_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CURVE_3.CPP

DRPROF_C.OBJ:	DRPROF_C.CPP $(DRPROF_C_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRPROF_C.CPP

MATOBJ.OBJ:	MATOBJ.CPP $(MATOBJ_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MATOBJ.CPP

CURVE.OBJ:	CURVE.CPP $(CURVE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CURVE.CPP

SURFACE4.OBJ:	SURFACE4.CPP $(SURFACE4_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SURFACE4.CPP


$(PROJ).DLL::	ELEMDLL.OBJ DRCURVE.OBJ DRNODE.OBJ DROBJ3D.OBJ DRPATCH.OBJ DRPIPE.OBJ \
	DRPLATE.OBJ DRSOLID.OBJ DRFE3D.OBJ CURVE_1.OBJ CURVE_2.OBJ CURVE_3.OBJ DRPROF_C.OBJ \
	MATOBJ.OBJ CURVE.OBJ SURFACE4.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
ELEMDLL.OBJ +
DRCURVE.OBJ +
DRNODE.OBJ +
DROBJ3D.OBJ +
DRPATCH.OBJ +
DRPIPE.OBJ +
DRPLATE.OBJ +
DRSOLID.OBJ +
DRFE3D.OBJ +
CURVE_1.OBJ +
CURVE_2.OBJ +
CURVE_3.OBJ +
DRPROF_C.OBJ +
MATOBJ.OBJ +
CURVE.OBJ +
SURFACE4.OBJ +
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
