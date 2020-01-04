# Microsoft Visual C++ generated build script - Do not modify

PROJ = EDLG_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\ELEM_DLG\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = EDLGDLL.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"EDLG_D.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = MFC250D Spec_D OMgr_D Elem_D Draw_D Dr3D_D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = EDLG_D.DEF
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
SBRS = EDLGDLL.SBR \
		EDLGMGR.SBR \
		DLG_PIPE.SBR \
		DLG_NODE.SBR \
		DLG_PLAT.SBR \
		DLG_CCON.SBR \
		DLG_CGEN.SBR \
		DLG_PCON.SBR \
		DLG_LOFT.SBR \
		DLG_ROTP.SBR \
		DLG_XTRD.SBR \
		DLG_DUCT.SBR \
		DLG_SWIP.SBR \
		DLG_LMAT.SBR \
		DLG_PPOS.SBR \
		DLG_REND.SBR \
		DLG_SCON.SBR \
		DLG_SDUC.SBR \
		DLG_SLOF.SBR \
		DLG_SPOS.SBR \
		DLG_SROT.SBR \
		DLG_SSWI.SBR \
		DLG_SXTR.SBR \
		DLG_POBJ.SBR


EDLGDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\edlgdll.h


EDLGMGR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\elglobal.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\elem_dlg\dlg_node.h \
	d:\drgraf\elem_dlg\dlg_pipe.h \
	d:\drgraf\allheads\drpipe.h \
	d:\drgraf\elem_dlg\dlg_plat.h \
	d:\drgraf\elem_dlg\dlg_cgen.h \
	d:\drgraf\elem_dlg\dlg_ccon.h \
	d:\drgraf\elem_dlg\dlg_pcon.h \
	d:\drgraf\elem_dlg\dlg_xtrd.h \
	d:\drgraf\elem_dlg\dlg_rotp.h \
	d:\drgraf\elem_dlg\dlg_loft.h \
	d:\drgraf\elem_dlg\dlg_swip.h \
	d:\drgraf\elem_dlg\dlg_duct.h \
	d:\drgraf\elem_dlg\dlg_ppos.h \
	d:\drgraf\elem_dlg\dlg_scon.h \
	d:\drgraf\elem_dlg\dlg_sxtr.h \
	d:\drgraf\elem_dlg\dlg_srot.h \
	d:\drgraf\elem_dlg\dlg_slof.h \
	d:\drgraf\elem_dlg\dlg_sswi.h \
	d:\drgraf\elem_dlg\dlg_sduc.h \
	d:\drgraf\elem_dlg\dlg_spos.h \
	d:\drgraf\elem_dlg\dlg_pobj.h \
	d:\drgraf\allheads\drobj3d.h \
	d:\drgraf\allheads\edlgdll.h \
	d:\drgraf\elem_dlg\edlgmgr.h


ELEM_DLG_RCDEP = d:\drgraf\res\image1d.bmp \
	d:\drgraf\res\image1f.bmp \
	d:\drgraf\res\image2d.bmp \
	d:\drgraf\res\image2f.bmp \
	d:\drgraf\res\image2u.bmp \
	d:\drgraf\res\image1u.bmp \
	d:\drgraf\res\curvebit.bmp \
	d:\drgraf\elem_dlg\ico_pipe.ico


DLG_PIPE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\drpipe.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_pipe.h


DLG_NODE_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\elem_dlg\dlg_node.h


DLG_PLAT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_plat.h


DLG_CCON_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_ccon.h


DLG_CGEN_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_cgen.h


DLG_PCON_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_pcon.h


DLG_LOFT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_loft.h


DLG_ROTP_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_rotp.h


DLG_XTRD_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\elem_dlg\dlg_xtrd.h


DLG_DUCT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_duct.h


DLG_SWIP_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_swip.h


DLG_LMAT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\elem_dlg\dlg_lmat.h \
	d:\drgraf\allheads\paredit.h \
	d:\drgraf\allheads\spin.h \
	d:\drgraf\allheads\muscroll.h \
	d:\drgraf\elem_dlg\otherids.h


DLG_PPOS_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\elem_dlg\dlg_lmat.h \
	d:\drgraf\allheads\paredit.h \
	d:\drgraf\allheads\spin.h \
	d:\drgraf\allheads\muscroll.h \
	d:\drgraf\elem_dlg\otherids.h \
	d:\drgraf\elem_dlg\dlg_rend.h \
	d:\drgraf\elem_dlg\dlg_ppos.h


DLG_REND_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\elem_dlg\dlg_rend.h


DLG_SCON_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_scon.h


DLG_SDUC_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_sduc.h


DLG_SLOF_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_slof.h


DLG_SPOS_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\elem_dlg\dlg_lmat.h \
	d:\drgraf\allheads\paredit.h \
	d:\drgraf\allheads\spin.h \
	d:\drgraf\allheads\muscroll.h \
	d:\drgraf\elem_dlg\otherids.h \
	d:\drgraf\elem_dlg\dlg_rend.h \
	d:\drgraf\elem_dlg\dlg_spos.h


DLG_SROT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_srot.h


DLG_SSWI_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\elem_dlg\dlg_sswi.h


DLG_SXTR_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\crdefine.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\elem_dlg\dlg_sxtr.h


DLG_POBJ_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\mi_patch.h \
	d:\drgraf\allheads\mi_curve.h \
	d:\drgraf\allheads\drcurve.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\drnode.h \
	d:\drgraf\allheads\crextern.h \
	d:\drgraf\allheads\drplate.h \
	d:\drgraf\allheads\drpatch.h \
	d:\drgraf\allheads\mi_solid.h \
	d:\drgraf\allheads\drsolid.h \
	d:\drgraf\allheads\dbmouse.h \
	d:\drgraf\allheads\objmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h \
	d:\drgraf\allheads\newobjs.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\elextern.h \
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\elem_dlg\dlg_lmat.h \
	d:\drgraf\allheads\paredit.h \
	d:\drgraf\allheads\spin.h \
	d:\drgraf\allheads\muscroll.h \
	d:\drgraf\elem_dlg\otherids.h \
	d:\drgraf\elem_dlg\dlg_pobj.h \
	d:\drgraf\allheads\drobj3d.h


all:	$(PROJ).DLL

EDLGDLL.OBJ:	EDLGDLL.CPP $(EDLGDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c EDLGDLL.CPP

EDLGMGR.OBJ:	EDLGMGR.CPP $(EDLGMGR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EDLGMGR.CPP

ELEM_DLG.RES:	ELEM_DLG.RC $(ELEM_DLG_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r ELEM_DLG.RC

DLG_PIPE.OBJ:	DLG_PIPE.CPP $(DLG_PIPE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_PIPE.CPP

DLG_NODE.OBJ:	DLG_NODE.CPP $(DLG_NODE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_NODE.CPP

DLG_PLAT.OBJ:	DLG_PLAT.CPP $(DLG_PLAT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_PLAT.CPP

DLG_CCON.OBJ:	DLG_CCON.CPP $(DLG_CCON_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_CCON.CPP

DLG_CGEN.OBJ:	DLG_CGEN.CPP $(DLG_CGEN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_CGEN.CPP

DLG_PCON.OBJ:	DLG_PCON.CPP $(DLG_PCON_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_PCON.CPP

DLG_LOFT.OBJ:	DLG_LOFT.CPP $(DLG_LOFT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_LOFT.CPP

DLG_ROTP.OBJ:	DLG_ROTP.CPP $(DLG_ROTP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_ROTP.CPP

DLG_XTRD.OBJ:	DLG_XTRD.CPP $(DLG_XTRD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_XTRD.CPP

DLG_DUCT.OBJ:	DLG_DUCT.CPP $(DLG_DUCT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_DUCT.CPP

DLG_SWIP.OBJ:	DLG_SWIP.CPP $(DLG_SWIP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_SWIP.CPP

DLG_LMAT.OBJ:	DLG_LMAT.CPP $(DLG_LMAT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_LMAT.CPP

DLG_PPOS.OBJ:	DLG_PPOS.CPP $(DLG_PPOS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_PPOS.CPP

DLG_REND.OBJ:	DLG_REND.CPP $(DLG_REND_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_REND.CPP

DLG_SCON.OBJ:	DLG_SCON.CPP $(DLG_SCON_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_SCON.CPP

DLG_SDUC.OBJ:	DLG_SDUC.CPP $(DLG_SDUC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_SDUC.CPP

DLG_SLOF.OBJ:	DLG_SLOF.CPP $(DLG_SLOF_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_SLOF.CPP

DLG_SPOS.OBJ:	DLG_SPOS.CPP $(DLG_SPOS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_SPOS.CPP

DLG_SROT.OBJ:	DLG_SROT.CPP $(DLG_SROT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_SROT.CPP

DLG_SSWI.OBJ:	DLG_SSWI.CPP $(DLG_SSWI_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_SSWI.CPP

DLG_SXTR.OBJ:	DLG_SXTR.CPP $(DLG_SXTR_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_SXTR.CPP

DLG_POBJ.OBJ:	DLG_POBJ.CPP $(DLG_POBJ_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DLG_POBJ.CPP


$(PROJ).DLL::	ELEM_DLG.RES

$(PROJ).DLL::	EDLGDLL.OBJ EDLGMGR.OBJ DLG_PIPE.OBJ DLG_NODE.OBJ DLG_PLAT.OBJ DLG_CCON.OBJ \
	DLG_CGEN.OBJ DLG_PCON.OBJ DLG_LOFT.OBJ DLG_ROTP.OBJ DLG_XTRD.OBJ DLG_DUCT.OBJ DLG_SWIP.OBJ \
	DLG_LMAT.OBJ DLG_PPOS.OBJ DLG_REND.OBJ DLG_SCON.OBJ DLG_SDUC.OBJ DLG_SLOF.OBJ DLG_SPOS.OBJ \
	DLG_SROT.OBJ DLG_SSWI.OBJ DLG_SXTR.OBJ DLG_POBJ.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
EDLGDLL.OBJ +
EDLGMGR.OBJ +
DLG_PIPE.OBJ +
DLG_NODE.OBJ +
DLG_PLAT.OBJ +
DLG_CCON.OBJ +
DLG_CGEN.OBJ +
DLG_PCON.OBJ +
DLG_LOFT.OBJ +
DLG_ROTP.OBJ +
DLG_XTRD.OBJ +
DLG_DUCT.OBJ +
DLG_SWIP.OBJ +
DLG_LMAT.OBJ +
DLG_PPOS.OBJ +
DLG_REND.OBJ +
DLG_SCON.OBJ +
DLG_SDUC.OBJ +
DLG_SLOF.OBJ +
DLG_SPOS.OBJ +
DLG_SROT.OBJ +
DLG_SSWI.OBJ +
DLG_SXTR.OBJ +
DLG_POBJ.OBJ +
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
	$(RC) $(RESFLAGS) ELEM_DLG.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	ELEM_DLG.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) ELEM_DLG.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
