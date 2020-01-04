# Microsoft Visual C++ generated build script - Do not modify

PROJ = MMGR_D
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
LIBS_D_WDLL = MFC250D OMgr_D Spec_d Draw_D Elem_D EDlg_D DDlg_D Dr3D_D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = MMGR_D.DEF
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
SBRS = MOUSE.SBR \
		DBMOUSE.SBR \
		MOUSEMGR.SBR \
		ELMOUSE.SBR \
		MMGRDLL.SBR \
		MI_CURVE.SBR \
		MI_PATCH.SBR \
		MI_SOLID.SBR \
		MI_OBJ3D.SBR \
		MI_CUR_I.SBR \
		INTER_C3.SBR \
		INTER_C1.SBR \
		INTER_C2.SBR \
		IN_CRCLE.SBR \
		MI_CPROF.SBR \
		MI_GANGP.SBR \
		MI_PAT_I.SBR \
		MP_DUCT.SBR \
		MP_LOFT2.SBR \
		MP_ROTAT.SBR \
		MP_SWEEP.SBR \
		MP_XTRUD.SBR \
		PA_DUCT.SBR \
		PA_LOFT2.SBR \
		PA_ROTAT.SBR \
		PA_SWEEP.SBR \
		PA_XTRUD.SBR


MOUSE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_view.h \
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
	d:\drgraf\allheads\precison.h


DBMOUSE_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\ddlgmgr.h \
	d:\drgraf\allheads\curdef.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\drfrehnd.h \
	d:\drgraf\allheads\drgrid.h \
	d:\drgraf\allheads\drextern.h


MOUSEMGR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\mmgrdll.h \
	d:\drgraf\allheads\drawbox.h \
	d:\drgraf\allheads\curdef.h \
	d:\drgraf\allheads\glb_view.h \
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
	d:\drgraf\allheads\dbmouse.h


ELMOUSE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\glb_mous.h \
	d:\drgraf\allheads\glb_rend.h \
	d:\drgraf\allheads\camera.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\mi_pat_i.h \
	d:\drgraf\allheads\mi_cur_i.h \
	d:\drgraf\allheads\in_crcle.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\glb_cups.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\glb_elem.h \
	d:\drgraf\allheads\drpipe.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mi_cprof.h \
	d:\drgraf\allheads\drprof_c.h \
	d:\drgraf\allheads\matobj.h


MMGRDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\mmgrdll.h \
	d:\drgraf\allheads\drawbox.h


MMGR_RCDEP = d:\drgraf\mousemgr\res\cur_iso.cur \
	d:\drgraf\mousemgr\res\curh_12.cur \
	d:\drgraf\mousemgr\res\curh_23.cur \
	d:\drgraf\mousemgr\res\curh_31.cur \
	d:\drgraf\mousemgr\res\curtext.cur \
	d:\drgraf\mousemgr\res\000%.cur \
	d:\drgraf\mousemgr\res\012%.cur \
	d:\drgraf\mousemgr\res\025%.cur \
	d:\drgraf\mousemgr\res\037%.cur \
	d:\drgraf\mousemgr\res\050%.cur \
	d:\drgraf\mousemgr\res\062%.cur \
	d:\drgraf\mousemgr\res\075%.cur \
	d:\drgraf\mousemgr\res\087%.cur \
	d:\drgraf\mousemgr\res\100%.cur


MI_CURVE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_cups.h \
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
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\precison.h


MI_PATCH_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_objs.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\mousemgr\pa_xtrud.h \
	d:\drgraf\mousemgr\pa_rotat.h \
	d:\drgraf\mousemgr\pa_duct.h \
	d:\drgraf\mousemgr\pa_sweep.h \
	d:\drgraf\mousemgr\pa_loft2.h


MI_SOLID_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_objs.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\mousemgr\pa_xtrud.h \
	d:\drgraf\mousemgr\pa_rotat.h \
	d:\drgraf\mousemgr\pa_duct.h \
	d:\drgraf\mousemgr\pa_sweep.h \
	d:\drgraf\mousemgr\pa_loft2.h


MI_OBJ3D_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\precison.h


MI_CUR_I_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_cups.h \
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
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\precison.h


INTER_C3_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\3dmath.h


INTER_C1_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\3dmath.h


INTER_C2_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\inter_c2.h \      ÌÌÌÌÌª           ˆˆp           ‘‘      ››››››››››››       nnnnnnnnnnh    nnnnnnnnnn`      ˆˆˆ         *******.îîîîîîîî'''''''         "1â"2â""""î.îâîî6¡“91‘13‘æææææææÿ1añ?ÿ?11öföffffÿÿÿŸÿÿ?™™óÿÿùÿÿÿDDDoÿÿff÷ÿÿöDDDÿù™™™™™™™™™™™™ŸÿDHˆˆˆˆˆˆˆˆˆˆˆˆ„D »»»»»»»»»»»»»»                      
®ªªª           ÌÏÌüÌÌ                          	      	¹¹¹¹¹¹¹¹¹¹¹¹°   11111111110     ææææææææææ €    ææææææææææ                   ¢¢¢¢¢¢¢®îîîîîîîîrrrrrrrp        #"""â"""â"»²"îîcc“»³n“žc»»¾\allheads\spdefine.h \
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
	d:\drgraf\allheads\3dmath.h


IN_CRCLE_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h


MI_CPROF_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\drprof_c.h \
	d:\drgraf\allheads\matobj.h \
	d:\drgraf\allheads\mi_cprof.h


MI_GANGP_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_objs.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\mousemgr\mi_gangp.h


MI_PAT_I_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_objs.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\mousemgr\mp_xtrud.h \
	d:\drgraf\mousemgr\mi_gangp.h \
	d:\drgraf\mousemgr\mp_rotat.h \
	d:\drgraf\mousemgr\mp_duct.h \
	d:\drgraf\mousemgr\mp_sweep.h \
	d:\drgraf\mousemgr\mp_loft2.h


MP_DUCT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_objs.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\mousemgr\pa_duct.h \
	d:\drgraf\mousemgr\mp_duct.h \
	d:\drgraf\mousemgr\mi_gangp.h


MP_LOFT2_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_objs.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\mousemgr\pa_loft2.h \
	d:\drgraf\mousemgr\mp_loft2.h \
	d:\drgraf\mousemgr\mi_gangp.h


MP_ROTAT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_objs.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\mousemgr\pa_rotat.h \
	d:\drgraf\mousemgr\mp_rotat.h \
	d:\drgraf\mousemgr\mi_gangp.h


MP_SWEEP_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_objs.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\mousemgr\pa_sweep.h \
	d:\drgraf\mousemgr\mp_sweep.h \
	d:\drgraf\mousemgr\mi_gangp.h


MP_XTRUD_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_objs.h \
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
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\elem_dlg\edlgmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\mousemgr\pa_xtrud.h \
	d:\drgraf\mousemgr\mp_xtrud.h \
	d:\drgraf\mousemgr\mi_gangp.h


PA_DUCT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\mousemgr\pa_xtrud.h \
	d:\drgraf\mousemgr\pa_rotat.h \
	d:\drgraf\mousemgr\pa_duct.h


PA_LOFT2_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\mousemgr\pa_loft2.h


PA_ROTAT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\mousemgr\pa_rotat.h


PA_SWEEP_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\mousemgr\pa_xtrud.h \
	d:\drgraf\mousemgr\pa_rotat.h \
	d:\drgraf\mousemgr\pa_sweep.h


PA_XTRUD_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\glb_objs.h \
	d:\drgraf\allheads\glb_cups.h \
	d:\drgraf\mousemgr\pa_xtrud.h


all:	$(PROJ).DLL

MOUSE.OBJ:	MOUSE.CPP $(MOUSE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MOUSE.CPP

DBMOUSE.OBJ:	DBMOUSE.CPP $(DBMOUSE_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DBMOUSE.CPP

MOUSEMGR.OBJ:	MOUSEMGR.CPP $(MOUSEMGR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MOUSEMGR.CPP

ELMOUSE.OBJ:	ELMOUSE.CPP $(ELMOUSE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ELMOUSE.CPP

MMGRDLL.OBJ:	MMGRDLL.CPP $(MMGRDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MMGRDLL.CPP

MMGR.RES:	MMGR.RC $(MMGR_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r MMGR.RC

MI_CURVE.OBJ:	MI_CURVE.CPP $(MI_CURVE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MI_CURVE.CPP

MI_PATCH.OBJ:	MI_PATCH.CPP $(MI_PATCH_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MI_PATCH.CPP

MI_SOLID.OBJ:	MI_SOLID.CPP $(MI_SOLID_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MI_SOLID.CPP

MI_OBJ3D.OBJ:	MI_OBJ3D.CPP $(MI_OBJ3D_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MI_OBJ3D.CPP

MI_CUR_I.OBJ:	MI_CUR_I.CPP $(MI_CUR_I_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MI_CUR_I.CPP

INTER_C3.OBJ:	INTER_C3.CPP $(INTER_C3_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c INTER_C3.CPP

INTER_C1.OBJ:	INTER_C1.CPP $(INTER_C1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c INTER_C1.CPP

INTER_C2.OBJ:	INTER_C2.CPP $(INTER_C2_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c INTER_C2.CPP

IN_CRCLE.OBJ:	IN_CRCLE.CPP $(IN_CRCLE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c IN_CRCLE.CPP

MI_CPROF.OBJ:	MI_CPROF.CPP $(MI_CPROF_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MI_CPROF.CPP

MI_GANGP.OBJ:	MI_GANGP.CPP $(MI_GANGP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MI_GANGP.CPP

MI_PAT_I.OBJ:	MI_PAT_I.CPP $(MI_PAT_I_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MI_PAT_I.CPP

MP_DUCT.OBJ:	MP_DUCT.CPP $(MP_DUCT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MP_DUCT.CPP

MP_LOFT2.OBJ:	MP_LOFT2.CPP $(MP_LOFT2_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MP_LOFT2.CPP

MP_ROTAT.OBJ:	MP_ROTAT.CPP $(MP_ROTAT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MP_ROTAT.CPP

MP_SWEEP.OBJ:	MP_SWEEP.CPP $(MP_SWEEP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MP_SWEEP.CPP

MP_XTRUD.OBJ:	MP_XTRUD.CPP $(MP_XTRUD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MP_XTRUD.CPP

PA_DUCT.OBJ:	PA_DUCT.CPP $(PA_DUCT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PA_DUCT.CPP

PA_LOFT2.OBJ:	PA_LOFT2.CPP $(PA_LOFT2_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PA_LOFT2.CPP

PA_ROTAT.OBJ:	PA_ROTAT.CPP $(PA_ROTAT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PA_ROTAT.CPP

PA_SWEEP.OBJ:	PA_SWEEP.CPP $(PA_SWEEP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PA_SWEEP.CPP

PA_XTRUD.OBJ:	PA_XTRUD.CPP $(PA_XTRUD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PA_XTRUD.CPP


$(PROJ).DLL::	MMGR.RES

$(PROJ).DLL::	MOUSE.OBJ DBMOUSE.OBJ MOUSEMGR.OBJ ELMOUSE.OBJ MMGRDLL.OBJ MI_CURVE.OBJ \
	MI_PATCH.OBJ MI_SOLID.OBJ MI_OBJ3D.OBJ MI_CUR_I.OBJ INTER_C3.OBJ INTER_C1.OBJ INTER_C2.OBJ \
	IN_CRCLE.OBJ MI_CPROF.OBJ MI_GANGP.OBJ MI_PAT_I.OBJ MP_DUCT.OBJ MP_LOFT2.OBJ MP_ROTAT.OBJ \
	MP_SWEEP.OBJ MP_XTRUD.OBJ PA_DUCT.OBJ PA_LOFT2.OBJ PA_ROTAT.OBJ PA_SWEEP.OBJ PA_XTRUD.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
MOUSE.OBJ +
DBMOUSE.OBJ +
MOUSEMGR.OBJ +
ELMOUSE.OBJ +
MMGRDLL.OBJ +
MI_CURVE.OBJ +
MI_PATCH.OBJ +
MI_SOLID.OBJ +
MI_OBJ3D.OBJ +
MI_CUR_I.OBJ +
INTER_C3.OBJ +
INTER_C1.OBJ +
INTER_C2.OBJ +
IN_CRCLE.OBJ +
MI_CPROF.OBJ +
MI_GANGP.OBJ +
MI_PAT_I.OBJ +
MP_DUCT.OBJ +
MP_LOFT2.OBJ +
MP_ROTAT.OBJ +
MP_SWEEP.OBJ +
MP_XTRUD.OBJ +
PA_DUCT.OBJ +
PA_LOFT2.OBJ +
PA_ROTAT.OBJ +
PA_SWEEP.OBJ +
PA_XTRUD.OBJ +
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
	$(RC) $(RESFLAGS) MMGR.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	MMGR.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) MMGR.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
