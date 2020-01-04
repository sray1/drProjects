# Microsoft Visual C++ generated build script - Do not modify

PROJ = VIEW_D
DEBUG = 1
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\VIEW\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DRAWVIEW.CPP
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /D "_AFXDLL" /GD /GEf /Fd"VIEW_D.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = mfc250D OMgr_D Spec_D Draw_D Dr3D_D EBox_D DBox_D SDlg_D oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo /k
RUNFLAGS = 
DEFFILE = VIEW_D.DEF
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
SBRS = DRAWVIEW.SBR \
		ROWVIEW.SBR \
		VIEWDLL.SBR \
		RENDER.SBR \
		RN_WIRE0.SBR \
		COLORPAL.SBR \
		LIGHT.SBR \
		TEXTURES.SBR \
		ZBUFFER.SBR \
		RN_WIRE1.SBR \
		PR_WIRE0.SBR \
		PR_WIRE1.SBR \
		VIEWINFO.SBR \
		AXISDRAW.SBR \
		DRAXIS.SBR \
		PR_WIRE2.SBR \
		RN_WIRE2.SBR


DRAWVIEW_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
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
	d:\drgraf\allheads\drgrafrm.h \
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
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\scalefac.h \
	d:\drgraf\allheads\unit.h \
	d:\drgraf\allheads\dbebextn.h \
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\sdlgmgr.h \
	d:\drgraf\view\pr_wire0.h \
	d:\drgraf\allheads\rn_wire0.h \
	d:\drgraf\allheads\render.h \
	d:\drgraf\allheads\zbuffer.h \
	d:\drgraf\allheads\textures.h \
	d:\drgraf\allheads\light.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\camera.h \
	d:\drgraf\view\pr_wire1.h \
	d:\drgraf\allheads\rn_wire1.h \
	d:\drgraf\view\pr_wire2.h \
	d:\drgraf\allheads\rn_wire2.h


ROWVIEW_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\rowview.h


VIEWDLL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\viewdll.h


RENDER_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
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
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\textures.h \
	d:\drgraf\allheads\light.h \
	d:\drgraf\allheads\zbuffer.h \
	d:\drgraf\allheads\render.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\camera.h


RN_WIRE0_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
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
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drpipe.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\render.h \
	d:\drgraf\allheads\zbuffer.h \
	d:\drgraf\allheads\textures.h \
	d:\drgraf\allheads\light.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\camera.h \
	d:\drgraf\view\pr_wire0.h \
	d:\drgraf\allheads\rn_wire0.h


COLORPAL_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\colorpal.h


LIGHT_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\colorpal.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\light.h


TEXTURES_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\rnglobal.h \
	d:\drgraf\allheads\textures.h


ZBUFFER_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\zbuffer.h


VIEW_RCDEP = d:\drgraf\res\image1d.bmp \
	d:\drgraf\res\image1f.bmp \
	d:\drgraf\res\image2d.bmp \
	d:\drgraf\res\image2f.bmp \
	d:\drgraf\res\image2u.bmp \
	d:\drgraf\res\image1u.bmp \
	d:\drgraf\res\curvebit.bmp


RN_WIRE1_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
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
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drpipe.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\render.h \
	d:\drgraf\allheads\zbuffer.h \
	d:\drgraf\allheads\textures.h \
	d:\drgraf\allheads\light.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\camera.h \
	d:\drgraf\allheads\rn_wire1.h


PR_WIRE0_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
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
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\view\pr_wire0.h


PR_WIRE1_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
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
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\sdlgmgr.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\view\pr_wire1.h


VIEWINFO_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\viewdll.h \
	d:\drgraf\allheads\viewinfo.h


AXISDRAW_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\viewdll.h \
	d:\drgraf\view\draxis.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\axisdraw.h


DRAXIS_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\globals.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\camera.h \
	d:\drgraf\view\draxis.h


PR_WIRE2_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
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
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\xform.h \
	d:\drgraf\allheads\drclip.h \
	d:\drgraf\allheads\3dmath.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\sdlgmgr.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\render.h \
	d:\drgraf\allheads\zbuffer.h \
	d:\drgraf\allheads\textures.h \
	d:\drgraf\allheads\light.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\camera.h \
	d:\drgraf\view\pr_wire2.h


RN_WIRE2_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
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
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\allheads\drpipe.h \
	d:\drgraf\allheads\3ddefine.h \
	d:\drgraf\allheads\drclip.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drlabel.h \
	d:\drgraf\allheads\render.h \
	d:\drgraf\allheads\zbuffer.h \
	d:\drgraf\allheads\textures.h \
	d:\drgraf\allheads\light.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\camera.h \
	d:\drgraf\allheads\rn_wire2.h


all:	$(PROJ).DLL

DRAWVIEW.OBJ:	DRAWVIEW.CPP $(DRAWVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DRAWVIEW.CPP

ROWVIEW.OBJ:	ROWVIEW.CPP $(ROWVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ROWVIEW.CPP

VIEWDLL.OBJ:	VIEWDLL.CPP $(VIEWDLL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VIEWDLL.CPP

RENDER.OBJ:	RENDER.CPP $(RENDER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RENDER.CPP

RN_WIRE0.OBJ:	RN_WIRE0.CPP $(RN_WIRE0_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RN_WIRE0.CPP

COLORPAL.OBJ:	COLORPAL.CPP $(COLORPAL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COLORPAL.CPP

LIGHT.OBJ:	LIGHT.CPP $(LIGHT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LIGHT.CPP

TEXTURES.OBJ:	TEXTURES.CPP $(TEXTURES_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TEXTURES.CPP

ZBUFFER.OBJ:	ZBUFFER.CPP $(ZBUFFER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ZBUFFER.CPP

VIEW.RES:	VIEW.RC $(VIEW_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r VIEW.RC

RN_WIRE1.OBJ:	RN_WIRE1.CPP $(RN_WIRE1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RN_WIRE1.CPP

PR_WIRE0.OBJ:	PR_WIRE0.CPP $(PR_WIRE0_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PR_WIRE0.CPP

PR_WIRE1.OBJ:	PR_WIRE1.CPP $(PR_WIRE1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PR_WIRE1.CPP

VIEWINFO.OBJ:	VIEWINFO.CPP $(VIEWINFO_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VIEWINFO.CPP

AXISDRAW.OBJ:	AXISDRAW.CPP $(AXISDRAW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c AXISDRAW.CPP

DRAXIS.OBJ:	DRAXIS.CPP $(DRAXIS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRAXIS.CPP

PR_WIRE2.OBJ:	PR_WIRE2.CPP $(PR_WIRE2_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PR_WIRE2.CPP

RN_WIRE2.OBJ:	RN_WIRE2.CPP $(RN_WIRE2_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c RN_WIRE2.CPP


$(PROJ).DLL::	VIEW.RES

$(PROJ).DLL::	DRAWVIEW.OBJ ROWVIEW.OBJ VIEWDLL.OBJ RENDER.OBJ RN_WIRE0.OBJ COLORPAL.OBJ \
	LIGHT.OBJ TEXTURES.OBJ ZBUFFER.OBJ RN_WIRE1.OBJ PR_WIRE0.OBJ PR_WIRE1.OBJ VIEWINFO.OBJ \
	AXISDRAW.OBJ DRAXIS.OBJ PR_WIRE2.OBJ RN_WIRE2.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DRAWVIEW.OBJ +
ROWVIEW.OBJ +
VIEWDLL.OBJ +
RENDER.OBJ +
RN_WIRE0.OBJ +
COLORPAL.OBJ +
LIGHT.OBJ +
TEXTURES.OBJ +
ZBUFFER.OBJ +
RN_WIRE1.OBJ +
PR_WIRE0.OBJ +
PR_WIRE1.OBJ +
VIEWINFO.OBJ +
AXISDRAW.OBJ +
DRAXIS.OBJ +
PR_WIRE2.OBJ +
RN_WIRE2.OBJ +
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
	$(RC) $(RESFLAGS) VIEW.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	VIEW.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) VIEW.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
