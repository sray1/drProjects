# Microsoft Visual C++ generated build script - Do not modify

PROJ = DRGRAF_D
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\DRGRAF\APPLIC\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W4 /Zi /AL /Od /D "_AFXDLL" /D "_DEBUG" /GA /GEf /Fd"DRGRAF.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AL /O1 /D "NDEBUG" /D "_AFXDLL" /FR /GA /GEf 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:40000 /ALIGN:16 /ONERROR:NOEXE /CO /MAP  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:20480 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = MFC250D View_D OMgr_D Dr3D_D MMgr_D Spec_D SDlg_D Elem_D EDlg_D Draw_D DDlg_D EBox_D DBox_D oldnames libw llibcew compobj storage ole2 ole2disp ole2nls mfcoleui mfco250d commdlg.lib olecli.lib shell.lib ver.lib 
LIBS_R_WEXE = mfc250 oldnames libw llibcew compobj storage ole2 ole2disp ole2nls mfcoleui mfco250 commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = DRGRAF_D.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		DRGRAF.SBR \
		DRGRAFRM.SBR \
		DRGRADOC.SBR \
		CNTRITEM.SBR \
		12VIEW.SBR \
		DRGRACFM.SBR \
		ABOUTBOX.SBR \
		DATAVIEW.SBR \
		DRSTATUS.SBR \
		23VIEW.SBR \
		31VIEW.SBR \
		3DVIEW.SBR \
		CLOCK.SBR \
		BANNER.SBR \
		MDIB.SBR


DRGRAF_RCDEP = d:\drgraf\applic\res\dsicon.ico \
	d:\drgraf\applic\res\dsicon2.ico \
	d:\drgraf\applic\res\image1d.bmp \
	d:\drgraf\applic\res\image1f.bmp \
	d:\drgraf\applic\res\image2d.bmp \
	d:\drgraf\applic\res\image2f.bmp \
	d:\drgraf\applic\res\image2u.bmp \
	d:\drgraf\applic\res\image1u.bmp \
	d:\drgraf\applic\res\drcafe.bmp \
	d:\drgraf\applic\lview\seashore.bmp \
	d:\drgraf\applic\res\jasmin.bmp \
	d:\drgraf\applic\res\button.cur \
	d:\drgraf\applic\res\drgraf.rc2


STDAFX_DEP = d:\drgraf\allheads\stdafx.h


DRGRAF_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\aboutbox.h \
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
	d:\drgraf\allheads\spdefine.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\drobject.h \
	d:\drgraf\allheads\dlistmgr.h \
	d:\drgraf\allheads\glb_type.h \
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\scalefac.h \
	d:\drgraf\allheads\unit.h \
	d:\drgraf\allheads\drgracfm.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\mi_cur_i.h \
	d:\drgraf\allheads\in_crcle.h \
	d:\drgraf\allheads\drcurve.h \
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
	d:\drgraf\allheads\12view.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\camera.h \
	d:\drgraf\allheads\23view.h \
	d:\drgraf\allheads\31view.h \
	d:\drgraf\allheads\3dview.h \
	d:\drgraf\allheads\dataview.h \
	d:\drgraf\allheads\rowview.h \
	d:\drgraf\allheads\colorpal.h \
	d:\drgraf\allheads\viewdll.h \
	d:\drgraf\allheads\omgrdll.h \
	d:\drgraf\allheads\dr3ddll.h \
	d:\drgraf\allheads\mmgrdll.h \
	d:\drgraf\allheads\specdll.h \
	d:\drgraf\allheads\sdlgdll.h \
	d:\drgraf\allheads\elemdll.h \
	d:\drgraf\allheads\edlgdll.h \
	d:\drgraf\allheads\drawdll.h \
	d:\drgraf\allheads\ddlgdll.h \
	d:\drgraf\toolboxs\inc\eboxdll.h \
	d:\drgraf\toolboxs\inc\dboxdll.h \
	d:\drgraf\allheads\glb_elem.h \
	d:\drgraf\allheads\eldefine.h \
	d:\drgraf\toolboxs\inc\dbglobal.h \
	d:\drgraf\allheads\drdefine.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h


DRGRAFRM_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\glb_view.h \
	d:\drgraf\allheads\banner.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\clock.h \
	d:\drgraf\allheads\drgraf.h \
	d:\drgraf\allheads\aboutbox.h \
	d:\drgraf\allheads\drgracfm.h \
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
	d:\drgraf\allheads\12view.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\camera.h \
	d:\drgraf\allheads\23view.h \
	d:\drgraf\allheads\31view.h \
	d:\drgraf\allheads\3dview.h \
	d:\drgraf\allheads\dataview.h \
	d:\drgraf\allheads\rowview.h \
	d:\drgraf\allheads\sdlgmgr.h \
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
	d:\drgraf\allheads\unit.h


DRGRADOC_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\cntritem.h \
	d:\drgraf\allheads\sdlgmgr.h \
	d:\drgraf\allheads\msdefine.h \
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\mi_cur_i.h \
	d:\drgraf\allheads\in_crcle.h \
	d:\drgraf\allheads\drcurve.h \
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
	d:\drgraf\allheads\booleans.h \
	d:\drgraf\allheads\datawind.h \
	d:\drgraf\allheads\drfont.h \
	d:\drgraf\allheads\drpen.h \
	d:\drgraf\allheads\hitnet.h \
	d:\drgraf\allheads\layer.h \
	d:\drgraf\allheads\patchmnu.h \
	d:\drgraf\allheads\obj3dmnu.h \
	d:\drgraf\allheads\eboxmgr.h \
	d:\drgraf\allheads\dboxmgr.h


CNTRITEM_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\cntritem.h


12VIEW_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\cntritem.h \
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
	d:\drgraf\allheads\12view.h \
	d:\drgraf\allheads\drawview.h \
	d:\drgraf\allheads\axisdraw.h \
	d:\drgraf\allheads\viewinfo.h \
	d:\drgraf\allheads\camera.h


DRGRACFM_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\drgracfm.h


ABOUTBOX_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\aboutbox.h


DATAVIEW_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\drgradoc.h \
	d:\drgraf\allheads\mousemgr.h \
	d:\drgraf\allheads\elmouse.h \
	d:\drgraf\allheads\mouse.h \
	d:\drgraf\allheads\mi_cur_i.h \
	d:\drgraf\allheads\in_crcle.h \
	d:\drgraf\allheads\drcurve.h \
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
	d:\drgraf\allheads\dataview.h \
	d:\drgraf\allheads\rowview.h


DRSTATUS_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\precison.h \
	d:\drgraf\allheads\scalefac.h \
	d:\drgraf\allheads\mapfacto.h \
	d:\drgraf\allheads\unit.h \
	d:\drgraf\allheads\dbebextn.h \
	d:\drgraf\allheads\drstatus.h


23VIEW_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\cntritem.h \
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
	d:\drgraf\allheads\23view.h \
	d:\drgraf\allheads\drawview.h


31VIEW_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\cntritem.h \
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
	d:\drgraf\allheads\31view.h \
	d:\drgraf\allheads\drawview.h


3DVIEW_DEP = d:\drgraf\allheads\stdafx.h \
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
	d:\drgraf\allheads\cntritem.h \
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
	d:\drgraf\allheads\3dview.h \
	d:\drgraf\allheads\drawview.h


CLOCK_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\allheads\clock.h


BANNER_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\applic\mdib.h \
	d:\drgraf\allheads\banner.h


MDIB_DEP = d:\drgraf\allheads\stdafx.h \
	d:\drgraf\applic\mdib.h


all:	$(PROJ).EXE

DRGRAF.RES:	DRGRAF.RC $(DRGRAF_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DRGRAF.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

DRGRAF.OBJ:	DRGRAF.CPP $(DRGRAF_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRGRAF.CPP

DRGRAFRM.OBJ:	DRGRAFRM.CPP $(DRGRAFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRGRAFRM.CPP

DRGRADOC.OBJ:	DRGRADOC.CPP $(DRGRADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRGRADOC.CPP

CNTRITEM.OBJ:	CNTRITEM.CPP $(CNTRITEM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CNTRITEM.CPP

12VIEW.OBJ:	12VIEW.CPP $(12VIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c 12VIEW.CPP

DRGRACFM.OBJ:	DRGRACFM.CPP $(DRGRACFM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRGRACFM.CPP

ABOUTBOX.OBJ:	ABOUTBOX.CPP $(ABOUTBOX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ABOUTBOX.CPP

DATAVIEW.OBJ:	DATAVIEW.CPP $(DATAVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DATAVIEW.CPP

DRSTATUS.OBJ:	DRSTATUS.CPP $(DRSTATUS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DRSTATUS.CPP

23VIEW.OBJ:	23VIEW.CPP $(23VIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c 23VIEW.CPP

31VIEW.OBJ:	31VIEW.CPP $(31VIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c 31VIEW.CPP

3DVIEW.OBJ:	3DVIEW.CPP $(3DVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c 3DVIEW.CPP

CLOCK.OBJ:	CLOCK.CPP $(CLOCK_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CLOCK.CPP

BANNER.OBJ:	BANNER.CPP $(BANNER_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c BANNER.CPP

MDIB.OBJ:	MDIB.CPP $(MDIB_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MDIB.CPP


$(PROJ).EXE::	DRGRAF.RES

$(PROJ).EXE::	STDAFX.OBJ DRGRAF.OBJ DRGRAFRM.OBJ DRGRADOC.OBJ CNTRITEM.OBJ 12VIEW.OBJ \
	DRGRACFM.OBJ ABOUTBOX.OBJ DATAVIEW.OBJ DRSTATUS.OBJ 23VIEW.OBJ 31VIEW.OBJ 3DVIEW.OBJ \
	CLOCK.OBJ BANNER.OBJ MDIB.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
DRGRAF.OBJ +
DRGRAFRM.OBJ +
DRGRADOC.OBJ +
CNTRITEM.OBJ +
12VIEW.OBJ +
DRGRACFM.OBJ +
ABOUTBOX.OBJ +
DATAVIEW.OBJ +
DRSTATUS.OBJ +
23VIEW.OBJ +
31VIEW.OBJ +
3DVIEW.OBJ +
CLOCK.OBJ +
BANNER.OBJ +
MDIB.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\msvc\lib\+
d:\msvc\mfc\lib\+
d:\drgraf\lib_D\+
d:\c3d\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) DRGRAF.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	DRGRAF.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DRGRAF.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
