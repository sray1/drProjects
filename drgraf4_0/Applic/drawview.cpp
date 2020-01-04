// drawview.cpp : implementation of the CDrawView class         BASE Class
//


#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <Float.h>		// FLT_MAX
#include <afxcoll.h>	// CStringList etc.

 
#include "drgraf.h"
#include "drgradoc.h"
#include "Def_Mo.h"	// AllMode
/////////////////////////////////////////////// Dialogs
#include "resource.h"                     // resource for Help IDR etc
#include "viewrsrc.h"                     // resource for GoodBy Id etc. InfoView etc
#include "Dlg_Shrink.h"                    // resource
#include "Dlg_NoLE.h"                    // Label of Elements
#include "Dlg_NoEL.h"                    // Element
/////////////////////////////////////////////// toolboxes
#include "drgrafrm.h"
#include "Def_Elem.h"
#include "Ext_Elem.h"
#include "Ext_DBox.h"
/////////////////////
#include "ObjMgr.h"
#include "dListMgr.h"
#include "DrObject.h"
///////////////////// DrawOperationObjs
#include "Def_3D.h"
#include "XForm.h"
#include "3DMath.h"
/////////////////////////////////////////////////////////////////////////
//#include <3DSOLIDS.h>		//	Paint level rendering
//#include <3DSOLIDP.h>		//	ZBuffered rendering controller
//#include <CAMERA.h>			//	View control
//#include <CLUTS.H>			//	Color palette support
//#include <CONTOURS.h>		//	Contour (iso-line) drawing
//#include <3dcurves.h> 		//	curve interpolation functions
//#include <LOADBMPF.h>		//	Bitmap file handling
//#include <3dmt2pch.h>		//	surfaces from MxN matrices
//#include <ZPOLY.h>			//	hybrid painters / zbuffer flat shaded
//#include <3dxfdraw.h>		//	points and lines
//#include <3dgrid.h> 		//  grids

//#define	SPAN	(256L<<16)
//#define	SPAN	(32L<<16)
/////////////////////////////////////////////////////////////////////////
///////////////////// IGen
#include "Def_IGen.h"
#include "Ext_Cur.h"
#include "Ext_Pat.h"
#include "Ext_Sol.h"
///////////////////// Supports
#include "Def_Supp.h"
#include "Ext_Supp.h"
///////////////////// StaticLoads
#include "Def_StaL.h"
#include "Ext_StaL.h"
#include "DrStatic.h"
///////////////////// DrawObjs
#include "Def_Draw.h"
#include "DrLabel.h"
///////////////////// SpecObjs
#include "Def_Spec.h" 
#include "SDlgMgr.h"
#include "MapFacto.h"
#include "Precison.h"
#include "DrFont.h"
//////////////////////
#include "Def_Rend.h"
#include "RN_Wire0.h"
#include "RN_Wire1.h"
//#include "PR_Wire2.h"
#include "RN_Wire2.h"
//////////////////////
#include "DrFont.h" 
#include "Def_MoBox.h" 
#include "drawview.h" 

//////////////////////////////////////
#define VIEWABLE_INDEX_BEGIN	0	
#define	new						DEBUG_NEW
#define	BUFF_SIZE				1024
//////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CDrawView, CScrollView)
/////////////////////////////////////////////////////////////////////////////
// CDrawView

BEGIN_MESSAGE_MAP(CDrawView, CScrollView)
	//{{AFX_MSG_MAP(CDrawView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_COMMAND(IDM_3D_AMBIENTLIGHT, On3dAmbientlight)
	ON_UPDATE_COMMAND_UI(IDM_3D_AMBIENTLIGHT, OnUpdate3dAmbientlight)
	ON_COMMAND(IDM_3D_EYEPOSITION, On3dEyeposition)
	ON_UPDATE_COMMAND_UI(IDM_3D_EYEPOSITION, OnUpdate3dEyeposition)
	ON_COMMAND(IDM_3D_LIGHTSOURCE, On3dLightsource)
	ON_UPDATE_COMMAND_UI(IDM_3D_LIGHTSOURCE, OnUpdate3dLightsource)
	ON_COMMAND(IDM_3D_PROJECTION_PARALLEL, On3dProjectionParallel)
	ON_UPDATE_COMMAND_UI(IDM_3D_PROJECTION_PARALLEL, OnUpdate3dProjectionParallel)
	ON_COMMAND(IDM_3D_PROJECTION_PERSPECTIVE, On3dProjectionPerspective)
	ON_UPDATE_COMMAND_UI(IDM_3D_PROJECTION_PERSPECTIVE, OnUpdate3dProjectionPerspective)
	ON_COMMAND(IDM_3D_RENDERING, On3dRendering)
	ON_UPDATE_COMMAND_UI(IDM_3D_RENDERING, OnUpdate3dRendering)
	ON_COMMAND(IDM_OPTION_AXISON, OnOptionAxison)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_AXISON, OnUpdateOptionAxison)
	ON_COMMAND(IDM_OPTION_CURSOR, OnOptionCursor)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_CURSOR, OnUpdateOptionCursor)
	ON_COMMAND(IDM_OPTION_PENCHANGE, OnOptionPenchange)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_PENCHANGE, OnUpdateOptionPenchange)
	ON_COMMAND(IDM_OPTION_REFRESH, OnOptionRefresh)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_REFRESH, OnUpdateOptionRefresh)
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_COMMAND(IDM_NOSHOW_CNLABEL, OnNoShowCNLabel)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_CNLABEL, OnUpdateNoShowCNLabel)
	ON_COMMAND(IDM_NOSHOW_CNODES, OnNoShowCNodes)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_CNODES, OnUpdateNoShowCNodes)
	ON_COMMAND(IDM_NOSHOW_NLABEL, OnNoShowNLabel)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_NLABEL, OnUpdateNoShowNLabel)
	ON_COMMAND(IDM_NOSHOW_NODES, OnNoShowNodes)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_NODES, OnUpdateNoShowNodes)
	ON_COMMAND(IDM_NOSHOW_CONTROLSHAPE, OnNoShowCShape)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_CONTROLSHAPE, OnUpdateNoShowCShape)
	ON_WM_KILLFOCUS()
	ON_COMMAND(IDM_3D_FS_PAINTER, On3dFsPainter)
	ON_UPDATE_COMMAND_UI(IDM_3D_FS_PAINTER, OnUpdate3dFsPainter)
	ON_COMMAND(IDM_3D_FS_ZBUFFER, On3dFsZbuffer)
	ON_UPDATE_COMMAND_UI(IDM_3D_FS_ZBUFFER, OnUpdate3dFsZbuffer)
	ON_COMMAND(IDM_3D_WF_HIDDEN, On3dWfHidden)
	ON_UPDATE_COMMAND_UI(IDM_3D_WF_HIDDEN, OnUpdate3dWfHidden)
	ON_COMMAND(IDM_3D_WF_PURE, On3dWfPure)
	ON_UPDATE_COMMAND_UI(IDM_3D_WF_PURE, OnUpdate3dWfPure)
	ON_COMMAND(IDM_3D_ZB_GOURAUD, On3dZbGouraud)
	ON_UPDATE_COMMAND_UI(IDM_3D_ZB_GOURAUD, OnUpdate3dZbGouraud)
	ON_COMMAND(IDM_3D_ZB_PHONG, On3dZbPhong)
	ON_UPDATE_COMMAND_UI(IDM_3D_ZB_PHONG, OnUpdate3dZbPhong)
	ON_COMMAND(IDM_NOSHOW_CENTROID, OnNoshowCentroid)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_CENTROID, OnUpdateNoshowCentroid)
	ON_COMMAND(IDM_NOSHOW_D_CURVE, OnNoshowDCurve)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_D_CURVE, OnUpdateNoshowDCurve)
	ON_COMMAND(IDM_NOSHOW_D_OBJECT, OnNoshowDObject)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_D_OBJECT, OnUpdateNoshowDObject)
	ON_COMMAND(IDM_NOSHOW_D_PATCH, OnNoshowDPatch)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_D_PATCH, OnUpdateNoshowDPatch)
	ON_COMMAND(IDM_NOSHOW_D_SOLID, OnNoshowDSolid)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_D_SOLID, OnUpdateNoshowDSolid)
 	ON_COMMAND(IDM_NOSHOW_D_PROFILE_C, OnNoshowDProfile_C)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_D_PROFILE_C, OnUpdateNoshowDProfile_C)
	ON_COMMAND(IDM_NOSHOW_D_PROFILE_P, OnNoshowDProfile_P)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_D_PROFILE_P, OnUpdateNoshowDProfile_P)
	ON_COMMAND(IDM_NOSHOW_D_PROFILE_S, OnNoshowDProfile_S)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_D_PROFILE_S, OnUpdateNoshowDProfile_S)
	ON_COMMAND(IDM_NOSHOW_NORMALS, OnNoshowNormals)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_NORMALS, OnUpdateNoshowNormals)
	ON_COMMAND(IDM_NOSHOW_P_CURVE, OnNoshowPCurve)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_P_CURVE, OnUpdateNoshowPCurve)
	ON_COMMAND(IDM_NOSHOW_P_OBJECT, OnNoshowPObject)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_P_OBJECT, OnUpdateNoshowPObject)
	ON_COMMAND(IDM_NOSHOW_P_PATCH, OnNoshowPPatch)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_P_PATCH, OnUpdateNoshowPPatch)
	ON_COMMAND(IDM_NOSHOW_P_SOLID, OnNoshowPSolid)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_P_SOLID, OnUpdateNoshowPSolid)
	ON_COMMAND(IDM_NOSHOW_P_PROFILE_C, OnNoshowPProfile_C)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_P_PROFILE_C, OnUpdateNoshowPProfile_C)
	ON_COMMAND(IDM_NOSHOW_P_PROFILE_P, OnNoshowPProfile_P)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_P_PROFILE_P, OnUpdateNoshowPProfile_P)
	ON_COMMAND(IDM_NOSHOW_P_PROFILE_S, OnNoshowPProfile_S)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_P_PROFILE_S, OnUpdateNoshowPProfile_S)
	ON_COMMAND(IDM_NOSHOW_VC_BCP, OnNoshowVcBcp)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_BCP, OnUpdateNoshowVcBcp)
	ON_COMMAND(IDM_NOSHOW_VC_CVV, OnNoshowVcCvv)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_CVV, OnUpdateNoshowVcCvv)
	ON_COMMAND(IDM_NOSHOW_VC_FCP, OnNoshowVcFcp)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_FCP, OnUpdateNoshowVcFcp)
	ON_COMMAND(IDM_NOSHOW_VC_PLANE, OnNoshowVcPlane)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_PLANE, OnUpdateNoshowVcPlane)
	ON_COMMAND(IDM_NOSHOW_VC_PRP, OnNoshowVcPrp)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_PRP, OnUpdateNoshowVcPrp)
	ON_COMMAND(IDM_NOSHOW_VC_VCS, OnNoshowVcVcs)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_VCS, OnUpdateNoshowVcVcs)
	ON_COMMAND(IDM_NOSHOW_VC_VDIR, OnNoshowVcVdir)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_VDIR, OnUpdateNoshowVcVdir)
	ON_COMMAND(IDM_NOSHOW_VC_VPN, OnNoshowVcVpn)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_VPN, OnUpdateNoshowVcVpn)
	ON_COMMAND(IDM_NOSHOW_VC_VRP, OnNoshowVcVrp)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_VRP, OnUpdateNoshowVcVrp)
	ON_COMMAND(IDM_NOSHOW_VC_VUP, OnNoshowVcVup)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_VUP, OnUpdateNoshowVcVup)
	ON_COMMAND(IDM_NOSHOW_VC_VV, OnNoshowVcVv)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_VV, OnUpdateNoshowVcVv)
	ON_COMMAND(IDM_NOSHOW_VC_WC, OnNoshowVcWc)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_WC, OnUpdateNoshowVcWc)
	ON_COMMAND(IDM_NOSHOW_VC_WCS, OnNoshowVcWcs)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_VC_WCS, OnUpdateNoshowVcWcs)
	ON_COMMAND(IDM_MODE_DESIGN, OnModeDesign)
	ON_UPDATE_COMMAND_UI(IDM_MODE_DESIGN, OnUpdateModeDesign)
	ON_COMMAND(IDM_MODE_INTERPOLATE, OnModeInterpolate)
	ON_UPDATE_COMMAND_UI(IDM_MODE_INTERPOLATE, OnUpdateModeInterpolate)
	ON_COMMAND(ID_SUMMARY_CURVE_DIRTY, OnSummaryCurveDirty)
	ON_COMMAND(ID_SUMMARY_CURVE_POSTED, OnSummaryCurvePosted)
	ON_COMMAND(ID_SUMMARY_ELEMENTS, OnSummaryElements)
	ON_COMMAND(ID_SUMMARY_NODE_ALLTYPES, OnSummaryNodeAlltypes)
	ON_COMMAND(ID_SUMMARY_NODE_CONTROL, OnSummaryNodeControl)
	ON_COMMAND(ID_SUMMARY_NODE_MESH, OnSummaryNodeMesh)
	ON_COMMAND(ID_SUMMARY_OBJECT, OnSummaryObject)
	ON_COMMAND(ID_SUMMARY_PATCH_DIRTY, OnSummaryPatchDirty)
	ON_COMMAND(ID_SUMMARY_PATCH_POSTED, OnSummaryPatchPosted)
	ON_COMMAND(ID_SUMMARY_SOLID_DIRTY, OnSummarySolidDirty)
	ON_COMMAND(ID_SUMMARY_SOLID_POSTED, OnSummarySolidPosted)
	ON_COMMAND(IDM_3D_SHRINKON, On3dShrinkOn)
	ON_UPDATE_COMMAND_UI(IDM_3D_SHRINKON, OnUpdate3dShrinkOn)
	ON_COMMAND(IDM_3D_CULLING3D, On3dCulling3D)
	ON_UPDATE_COMMAND_UI(IDM_3D_CULLING3D, OnUpdate3dCulling3D)
	ON_COMMAND(IDM_NOSHOW_LINEARSUPPORT_RIGID, OnNoshowLinearsupportRigid)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_LINEARSUPPORT_RIGID, OnUpdateNoshowLinearsupportRigid)
	ON_COMMAND(IDM_NOSHOW_LINEARSUPPORT_SNUBBER, OnNoshowLinearsupportSnubber)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_LINEARSUPPORT_SNUBBER, OnUpdateNoshowLinearsupportSnubber)
	ON_COMMAND(IDM_NOSHOW_LINEARSUPPORT_SPRING, OnNoshowLinearsupportSpring)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_LINEARSUPPORT_SPRING, OnUpdateNoshowLinearsupportSpring)
	ON_COMMAND(ID_SUMMARY_LINEARSUPPORT_RIGID, OnSummaryLinearsupportRigid)
	ON_COMMAND(ID_SUMMARY_LINEARSUPPORT_SNUBBER, OnSummaryLinearsupportSnubber)
	ON_COMMAND(ID_SUMMARY_LINEARSUPPORT_SPRING, OnSummaryLinearsupportSpring)
	ON_COMMAND(IDM_NOSHOW_MNLABEL, OnNoshowMnlabel)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_MNLABEL, OnUpdateNoshowMnlabel)
	ON_COMMAND(IDM_NOSHOW_MNODES, OnNoshowMnodes)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_MNODES, OnUpdateNoshowMnodes)
	ON_COMMAND(IDM_NOSHOW_STATIC_FORCE, OnNoshowStaticForce)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_STATIC_FORCE, OnUpdateNoshowStaticForce)
	ON_COMMAND(IDM_NOSHOW_STATIC_DISPLACE, OnNoshowStaticDisplace)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_STATIC_DISPLACE, OnUpdateNoshowStaticDisplace)
	ON_COMMAND(IDM_NOSHOW_STATIC_PRESSURE, OnNoshowStaticPressure)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_STATIC_PRESSURE, OnUpdateNoshowStaticPressure)
	ON_COMMAND(IDM_NOSHOW_STATIC_THERMAL, OnNoshowStaticThermal)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_STATIC_THERMAL, OnUpdateNoshowStaticThermal)
	ON_COMMAND(IDM_NOSHOW_STATIC_LUMPWT, OnNoshowStaticLumpWt)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_STATIC_LUMPWT, OnUpdateNoshowStaticLumpWt)
	ON_COMMAND(ID_SUMMARY_STATIC_FORCE, OnSummaryStaticForce)
	ON_COMMAND(ID_SUMMARY_STATIC_DISPLACE, OnSummaryStaticDisplace)
	ON_COMMAND(ID_SUMMARY_STATIC_PRESSURE, OnSummaryStaticPressure)
	ON_COMMAND(ID_SUMMARY_STATIC_THERMAL, OnSummaryStaticThermal)
	ON_COMMAND(ID_SUMMARY_STATIC_LUMPWT, OnSummaryStaticLumpWt)
	ON_MESSAGE(WM_COMMANDHELP,OnCommandHelp)
	ON_MESSAGE(WM_HELPHITTEST,OnHelpHitTest)
	ON_COMMAND(IDM_MODE_GENERATOR, OnViewModeGenerator)
	ON_UPDATE_COMMAND_UI(IDM_MODE_GENERATOR, OnUpdateViewModeGenerator)
	ON_COMMAND(IDM_MODE_MESH, OnViewModeMesh)
	ON_UPDATE_COMMAND_UI(IDM_MODE_MESH, OnUpdateViewModeMesh)
	ON_COMMAND(IDM_NOSHOW_ELEMENTS, OnNoshowElements)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_ELEMENTS, OnUpdateNoshowElements)
	ON_COMMAND(IDM_NOSHOW_LABEL_ELEMENTS, OnNoshowLabelElements)
	ON_COMMAND(IDM_NOSHOWLABELS_D_CURVE, OnNoshowlabelsDCurve)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_D_CURVE, OnUpdateNoshowlabelsDCurve)
	ON_COMMAND(IDM_NOSHOWLABELS_D_OBJECT, OnNoshowlabelsDObject)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_D_OBJECT, OnUpdateNoshowlabelsDObject)
	ON_COMMAND(IDM_NOSHOWLABELS_D_PATCH, OnNoshowlabelsDPatch)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_D_PATCH, OnUpdateNoshowlabelsDPatch)
	ON_COMMAND(IDM_NOSHOWLABELS_D_PROFILE_S, OnNoshowlabelsDProfileS)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_D_PROFILE_S, OnUpdateNoshowlabelsDProfileS)
	ON_COMMAND(IDM_NOSHOWLABELS_D_SOLID, OnNoshowlabelsDSolid)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_D_SOLID, OnUpdateNoshowlabelsDSolid)
	ON_COMMAND(IDM_NOSHOWLABELS_LINEARSUPPORT_RIGID, OnNoshowlabelsLinearsupportRigid)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_LINEARSUPPORT_RIGID, OnUpdateNoshowlabelsLinearsupportRigid)
	ON_COMMAND(IDM_NOSHOWLABELS_LINEARSUPPORT_SPRING, OnNoshowlabelsLinearsupportSpring)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_LINEARSUPPORT_SPRING, OnUpdateNoshowlabelsLinearsupportSpring)
	ON_COMMAND(IDM_NOSHOWLABELS_P_CURVE, OnNoshowlabelsPCurve)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_P_CURVE, OnUpdateNoshowlabelsPCurve)
	ON_COMMAND(IDM_NOSHOWLABELS_P_OBJECT, OnNoshowlabelsPObject)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_P_OBJECT, OnUpdateNoshowlabelsPObject)
	ON_COMMAND(IDM_NOSHOWLABELS_P_PATCH, OnNoshowlabelsPPatch)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_P_PATCH, OnUpdateNoshowlabelsPPatch)
	ON_COMMAND(IDM_NOSHOWLABELS_P_SOLID, OnNoshowlabelsPSolid)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_P_SOLID, OnUpdateNoshowlabelsPSolid)
	ON_COMMAND(IDM_NOSHOWLABELS_STATIC_DISPLACE, OnNoshowlabelsStaticDisplace)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_STATIC_DISPLACE, OnUpdateNoshowlabelsStaticDisplace)
	ON_COMMAND(IDM_NOSHOWLABELS_STATIC_FORCE, OnNoshowlabelsStaticForce)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_STATIC_FORCE, OnUpdateNoshowlabelsStaticForce)
	ON_COMMAND(IDM_NOSHOWLABELS_STATIC_GRAVITY, OnNoshowlabelsStaticGravity)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_STATIC_GRAVITY, OnUpdateNoshowlabelsStaticGravity)
	ON_COMMAND(IDM_NOSHOWLABELS_STATIC_LUMPWT, OnNoshowlabelsStaticLumpwt)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_STATIC_LUMPWT, OnUpdateNoshowlabelsStaticLumpwt)
	ON_COMMAND(IDM_NOSHOWLABELS_STATIC_THERMAL, OnNoshowlabelsStaticThermal)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOWLABELS_STATIC_THERMAL, OnUpdateNoshowlabelsStaticThermal)
	//}}AFX_MSG_MAP
	ON_WM_MOUSEACTIVATE()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_MESSAGE(ID_UPDATE_EYEPOS,OnUpdateEyePos)
	ON_MESSAGE(ID_GOODBYE_EYEPOS,OnGoodByeEyePos)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawView diagnostics

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CDrawView construction, initialization, and destruction

CDrawView::CDrawView()
{
	if(!(m_SortList.IsEmpty())  )
		m_SortList.RemoveAll();
	//////////////////////////
	m_bViewGene = TRUE;
	m_bViewMesh = FALSE;
	///////////////////////////////////////////
//	m_GenMode		= REVERSE; // Interpolation
	m_GenMode		= FORWARD; // Interpolation
	////////////////////////
	m_bCameraChanged= TRUE;
	m_bRendChanged	= TRUE;
	/////////////////////////////////////////////////////////// Modeless Dialogs
	m_pViewInfoDlg	= new CViewInfo(this);                                                                                
//	m_pAxisDrawDlg	= new CAxisDraw(this);                                                                                
	/////////////////////////////////////////////// NonViewables <11
	m_nPrevSelectedObjIndex = VIEWABLE_INDEX_BEGIN;    
	m_nPrevSelectedObjType  = NONE;    
	////////////////////////////// NoShow Controls
	int i;
	//////
	for (i=0;i<MAX_NOSOEL;i++)
		m_bNoSoEL[i] = FALSE;
	for (i=0;i<MAX_NOSOLABEL;i++)
		m_bNoSoLabEL[i] = FALSE;
	////////////////////
	m_bNS_Force			= FALSE;	
	m_bNS_Displace		= FALSE;
	m_bNS_Pressure		= FALSE;
	m_bNS_Thermal		= FALSE;
	m_bNS_LumpWt		= FALSE;
	for (i=0;i<MAX_NOSOLABSTATIC;i++)
		m_bNS_LabStatic[i] = FALSE;
	/////////////////////////// Support
	m_bNS_RIGID			= FALSE; 
	m_bNS_Lin_Spring	= FALSE; 
	m_bNS_Lin_Snubber	= FALSE; 
	m_bNS_Non_Spring	= TRUE; 
	m_bNS_Non_Snubber	= TRUE; 
	for (i=0;i<MAX_NOSOLABSUPPORT;i++)
		m_bNS_LabSupp[i] = FALSE;
	/////////////////////////// Dirty	
	m_bNS_D_Object		= FALSE;			
	m_bNS_D_Solid		= FALSE;	
	m_bNS_D_Patch		= FALSE;	
	m_bNS_D_Curve		= FALSE;
	m_bNS_D_Profile_S	= FALSE; 
	m_bNS_D_Profile_P	= FALSE; 
	m_bNS_D_Profile_C	= FALSE; 
	for (i=0;i<MAX_NOSOLABDIRTY;i++)
		m_bNS_LabDirty[i] = FALSE;
	/////////////////////////// Posted	
	m_bNS_P_Object	= TRUE;			
	m_bNS_P_Solid	= TRUE;	
	m_bNS_P_Patch	= TRUE;	
	m_bNS_P_Curve	= TRUE;
	m_bNS_P_Profile_S = FALSE; 
	m_bNS_P_Profile_P = FALSE; 
	m_bNS_P_Profile_C = FALSE; 
	for (i=0;i<MAX_NOSOLABPOSTED;i++)
		m_bNS_LabPosted[i] = FALSE;
	/////////////////////////// Node	
	m_bNS_2DLabel 	= FALSE;	
	m_bNS_3DLabel 	= FALSE;	
	m_bNS_CNLabel 	= FALSE;	
	m_bNS_CNode		= FALSE;	
	m_bNS_NLabel	= FALSE;	
	m_bNS_Node		= FALSE;	
	m_bNS_MNLabel	= FALSE;	
	m_bNS_MNode		= FALSE;
	///
	m_bNS_CShape	= TRUE; 
	///////////////////////////
	m_bNS_Normal	= TRUE;
	m_bNS_Centroid	= TRUE;
	/////////////////////////// View Controls	
	m_bNS_CVV		= TRUE;
	m_bNS_VV		= TRUE;
	m_bNS_VRP		= TRUE;
	m_bNS_PRP		= TRUE;
	m_bNS_VUP		= TRUE;
	m_bNS_VPN		= TRUE;
	m_bNS_CW		= TRUE;
	m_bNS_VPlane	= TRUE;
	m_bNS_VDIR		= TRUE;
	m_bNS_WC		= TRUE;
	m_bNS_VRC		= TRUE;
	m_bNS_NPC		= TRUE;
	m_bNS_Front		= TRUE;
	m_bNS_Back		= TRUE;
	/////////////////////// Culling
	m_bCulling3D	= FALSE;
	/////////////////////// Shrink
	m_bShrinkOn		= FALSE;
	m_dShrink		= 1.0;
/*	
	Set3dInterrupt( TRUE, WM_RBUTTONDOWN, WM_RBUTTONUP );
	pL				= NULL;
	hCLUT			= Make256ColorPalette();
	interaction		= VIEWING;

	SetPt3d( &Right, f_1,f_0,f_0 );
	SetPt3d( &Up, f_0,f_1,f_0 );
	SetPt3d( &View, f_0,f_0,f_1 );
	SetPt3d( &Current, f_0,f_0,f_0 );
	SetSubdivisions( subdivisions );

	SetCamera( f_0,f_64,-f_256, f_0, f_0, f_0, Lens50mm, f_0 );

	LtSource	LS[2];
	Set3dLtSource(
		&LS[0], (colorFactor)65000, (colorFactor)32000, (colorFactor)32000,
		f_0p5, Int2Fix( 160 ), Int2Fix( 50 ), Int2Fix( -160 )
	);
	Set3dLtSource(
		&LS[1], (colorFactor)32000, (colorFactor)32000, (colorFactor)65000,
		f_0p25, Int2Fix( -160 ), Int2Fix( 0 ), Int2Fix( -260 )
	);
	pL = NewLighting( (colorFactor)48000, 32000, 32000, fixratio( 10, 100 ), 2, LS );
*/
//////////////////////////////////////////////////////////////////////////////	
}

CDrawView::~CDrawView()
{
	delete m_pViewInfoDlg;                                                                                
//	delete m_pAxisDrawDlg;                                                                                
} 

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{

	m_ClassName = AfxRegisterWndClass
		(CS_HREDRAW| CS_VREDRAW,
		0,
		(HBRUSH)::GetStockObject(BLACK_BRUSH),
		0);
	cs.lpszClass	= m_ClassName;
	//////////////////////////
//	cs.style |= WS_VSCROLL|WS_HSCROLL;
	BOOL bRtn = CView::PreCreateWindow(cs);
	
	return bRtn;
}

LRESULT CDrawView::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
	if (lParam == 0)
	{
		if(m_nView == VIEW12)
			lParam = HID_BASE_RESOURCE + IDR_VIEW12;
		else
		if(m_nView == VIEW23)
			lParam = HID_BASE_RESOURCE + IDR_VIEW23;
		else
		if(m_nView == VIEW31)
			lParam = HID_BASE_RESOURCE + IDR_VIEW31;
		else
		if(m_nView == VIEWISO)
			lParam = HID_BASE_RESOURCE + IDR_VIEW3D;
		else
		if(m_nView == VIEWDAT)
			lParam = HID_BASE_RESOURCE + IDR_VIEWDAT;
		else
			return FALSE;
	}
	// context already determined above
	AfxGetApp()->WinHelp(lParam);
	return TRUE;
}

LRESULT CDrawView::OnHelpHitTest(WPARAM wParam, LPARAM lParam)
{
	if(m_nView == VIEW12)
		return HID_BASE_RESOURCE + IDR_VIEW12;
	else
	if(m_nView == VIEW23)
		return HID_BASE_RESOURCE + IDR_VIEW23;
	else
	if(m_nView == VIEW31)
		return HID_BASE_RESOURCE + IDR_VIEW31;
	else
	if(m_nView == VIEWISO)
		return HID_BASE_RESOURCE + IDR_VIEW3D;
	else
	if(m_nView == VIEWDAT)
		return HID_BASE_RESOURCE + IDR_VIEWDAT;
	else
		return HID_BASE_RESOURCE + IDR_VIEWUNKNOWN;	
}
/////////////////////////////////////////////////////////////////////////////
// CDrawView updating and drawing
void CDrawView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// The size of text that is displayed, printed or previewed changes
	// depending on the DC.  We explicitly call OnPrepareDC() to prepare
	// CClientDC objects used for calculating text positions and to
	// prepare the text metric member variables of the CDrawView object.
	// The framework also calls OnPrepareDC() before passing the DC to
	// OnDraw().

	CScrollView::OnPrepareDC(pDC, pInfo);
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CMapFactor* pMapFactor	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	/////////////////////////////////////////////////////////// MapMode
	int nMapModeOld = pDC->SetMapMode(pMapFactor->GetMapModeIndex());
	/////////////////////////////////////////////////////////////////  
	POINT ptDoc;
	ptDoc.x = 0;
	ptDoc.y = (pObjectMgr->GetDocSize().cy);
	pDC->SetWindowOrg(ptDoc);
//	pDC->SetROP2(R2_XORPEN);
	/////////////////////////////////////////////////////////// BkMode
//	pDC->SetBkMode(TRANSPARENT);
//	pDC->SetBkColor(0);
	////////////////////////////	
}

void CDrawView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
	////////////////////////////////////
	if(m_wndAxisDraw.GetStyle() & WS_VISIBLE)// visible
		ShowAxes();
	///////////////
/*	
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
	////////////////////////////////		
//	UpdateScrollSizes();
*/
	///////////////////
	CClientDC dc(this);
	int nMM;
	CSize sizeTotal,sizePage,sizeLine; 
	GetDeviceScrollSizes(nMM,sizeTotal,sizePage,sizeLine); 
	if(!nMM)
		return;
	OnPrepareDC(&dc);
	//////////////////////////////////////////////// Update Window Info
	m_sizeView.cx		= cx;
	m_sizeView.cy		= cy;
	dc.DPtoLP(&m_sizeView);
	///////////////////////
	Invalidate();
	UpdateWindow();
	///////////////
/*	
	Init3DWindow();
	////////////////////////////////////// Update Matrices
	UpdateAllOtherMatButLocal();
	//////////////////////////
	Invalidate();
	UpdateWindow();
	///////////////
*/
/*
	////////////////////////////////////// Axis Window
	int AxisW = cx/4;	
	int AxisH = AxisW;
	CRect AxisR;
	AxisR.left 	= ::GetSystemMetrics(SM_CXBORDER)+1;
	AxisR.top 	= cy - AxisH - 20;
	AxisR.right = AxisR.left + AxisW;
	AxisR.bottom= AxisR.top  + AxisH;
	//////
	m_wndAxisDraw.MoveWindow(&AxisR);
	//////////////
*/	
}

void CDrawView::SetScalevv3DToLP()
{
	if(m_OpMode == OP_INPUT)
	{
		m_dScale_U = (double)m_sizeDoc.cx;  
		m_dScale_V = (double)m_sizeDoc.cy;
	}
	else
	if(m_OpMode == OP_OUTPUT)
	{		
		m_dScale_U = (double)m_FOV.cx * m_dZoomFac_U;  
		m_dScale_V = (double)m_FOV.cy * m_dZoomFac_V;
	}	
};
	  
pMATRIX CDrawView::GetMatrix(MATRICES mType)
{
	if(mType ==	MT_IDENTITY)
		return 	&m_IdentityM;	// identity transform MATRIX
	else	
	if(mType ==	MT_LOCAL)
		return	&m_LocalM;		// instancing transform MATRIX
	else	
	if(mType ==	MT_VIEWER)
		return 	&m_ViewM;		// viewers transform MATRIX
	else	
	if(mType ==	MT_COMBINED)
		return 	&m_ComposedM;	// viewer & instance combined MATRIX 
	else	
	if(mType ==	MT_VV3D)
		return 	&m_vv3DM;		// 3DWindow to 3DViewport MATRIX
	else	
	if(mType ==	MT_PENULTI)
		return 	&m_PenultiM;	// instancing to 3DViewport MATRIX
	else	
	if(mType ==	MT_ULTIMATE)
		return 	&m_UltimateM;	// instancing to 2DViewport MATRIX(includes Projection)
	else
		return (pMATRIX)NULL;
}

void CDrawView::SetMatrix(MATRICES mType,pMATRIX pMat)
{
	if(mType ==	MT_IDENTITY)
		m_IdentityM = *pMat;	// identity transform MATRIX
	else	
	if(mType ==	MT_LOCAL)
		m_LocalM = *pMat;		// instancing transform MATRIX
	else	
	if(mType ==	MT_VIEWER)
		m_ViewM = *pMat;		// viewers transform MATRIX
	else	
	if(mType ==	MT_COMBINED)
		m_ComposedM = *pMat;	// viewer & instance combined MATRIX 
	else	
	if(mType ==	MT_VV3D)
		m_vv3DM = *pMat;		// Window to 3D Viewport MATRIX

}

void CDrawView::OnInitialUpdate()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision  = (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	CDrFont* pDrFont		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT); 
	////////////////////////////////////////////////////////////  
	SetScrollSizes(pMapFactor->GetMapModeIndex(),
						pObjectMgr->GetDocSize() );

//	GetParentFrame()->RecalcLayout();This will be done OnZoomToFit	
//	SetScaleToFitSize(pObjectMgr->GetDocSize());
	m_sizeDoc = GetTotalSize(); 
	//////////////////////////////////////////////////////////////////////// Show Origin
	CClientDC dc(this);
	OnPrepareDC(&dc);
	/////////////
	POINT ptDoc;
	ptDoc.x = 0;
	ptDoc.y = 0;
	/////////////////////////////////////
	dc.LPtoDP(&ptDoc);
	ScrollToDevicePosition(ptDoc);
	///////////////////////////////////////// Init: 
	CRect clientRect;
	GetClientRect(&clientRect);
	dc.DPtoLP(&clientRect);
	clientRect.NormalizeRect();
	////////////////////////////////////////// 
	m_sizeView.cx	= clientRect.Width();
	m_sizeView.cy	= clientRect.Height();
	/////////////////////////////////////////////////////////
	m_FOV.cx		= m_sizeView.cx;
	m_FOV.cy		= m_sizeView.cy;
	m_dZoomFac_U	= 1.0;
	m_dZoomFac_V	= 1.0;
	/////////////////////////////////////////// Scale from vv3DToLP
	SetScalevv3DToLP(); // depends on DocSize & ZoomFac
	///////////////////////////////////////////////// N O T E
	// since Node storage is with Precision times long     //
	// ViewPlane Window Center(CW), width & height must be //
	// found by Scaling DocSize with WorldBase		       //
	/////////////////////////////////////////////////////////	
	double dWorldBase,dMapFactor;
	dWorldBase 	= (double) pPrecision->GetWorldBase();
	dMapFactor  = pMapFactor->GetMapFactor();
    ///////////////////////////////////////////
    m_Width_U	= (double)m_sizeDoc.cx  * dWorldBase;
    m_Width_V	= (double)m_sizeDoc.cy  * dWorldBase;
	pObjectMgr->SCtoDS(&m_Width_U);
	pObjectMgr->SCtoDS(&m_Width_V);
	///////////////////////////////////////////////
	C3DMath Math3D;
	C3DMath* p3DMath = &Math3D;
	/////////////////////////////////////////////// Rendition
	m_Rendition 	= WF_PURE;
	m_bCulling3D	= FALSE;
	///////////////////////////////
	m_bParallel	= TRUE;		// true disables perspective 
	/////////////////////////// View Orientation Parameters (VRC) /////////////
	if(m_nView == VIEW12)
	{
		p3DMath->Set3DPts(&m_VRP,0.0,0.0,0.0);	// View Reference Point(Origin)
		p3DMath->Set3DPts(&m_VPN,0.0,0.0,1.0);	// View Plane Normal(z-Axis)
		p3DMath->Set3DPts(&m_VUP,0.0,1.0,0.0);	// View Up Vector(y-axis)
	}
	else
	if(m_nView == VIEW23)
	{
		p3DMath->Set3DPts(&m_VRP,0.0,0.0,0.0);	// View Reference Point(Origin)
		p3DMath->Set3DPts(&m_VPN,-1.0,0.0,0.0);	// View Plane Normal(-x-Axis)
		p3DMath->Set3DPts(&m_VUP,0.0,1.0,0.0);	// View Up Vector(y-axis)
	}
	else
	if(m_nView == VIEW31)
	{
		p3DMath->Set3DPts(&m_VRP,0.0,0.0,0.0);	// View Reference Point(Origin)
		p3DMath->Set3DPts(&m_VPN,0.0,1.0,0.0);	// View Plane Normal(y-Axis)
		p3DMath->Set3DPts(&m_VUP,1.0,0.0,0.0);	// View Up Vector(z-axis)
	}
	else
	if(m_nView == VIEWISO)
	{
		p3DMath->Set3DPts(&m_VRP,0.0,0.0,0.0);	// View Reference Point(Origin)
		p3DMath->Set3DPts(&m_VPN,sqrt(.5),0,sqrt(.5));	// View Plane Normal(iso-Axis)
		p3DMath->Set3DPts(&m_VUP,0.0,1.0,0.0);	// View Up Vector(y-axis)
		//////////////////////////////////////
	}
	///////////// View Mapping Parameters (VRC) /////////////
	if(m_OpMode == OP_INPUT)
	{
	   	////////////////////////////////////////////////// 
		m_Umin		= 0;		// View Plane Window(VRC)
		m_Umax		=  m_Width_U;
		m_Vmin		= 0;
		m_Vmax		=  m_Width_V;
		m_dFront	=  FLT_MAX,				// near clipping plane
		m_dBack		=  -FLT_MAX;			// far clipping plane
	}
	else
	if(m_OpMode == OP_OUTPUT)
	{
	   	////////////////////////////////////////////////// 
		m_Umin		= -1;		// View Plane Window(VRC)
		m_Umax		=  7;
		m_Vmin		= -1;
		m_Vmax		=  7;
		m_dFront	=  60,		// near clipping plane
		m_dBack		=  -5;		// far clipping plane
		////////////////////////////////////////////////////////////
		/////////////////////////// strip Scale Factor (World Coord)
		pObjectMgr->SCtoDS(&m_Umin);
		pObjectMgr->SCtoDS(&m_Umax);
		pObjectMgr->SCtoDS(&m_Vmin);
		pObjectMgr->SCtoDS(&m_Vmax);
		pObjectMgr->SCtoDS(&m_dFront);
		pObjectMgr->SCtoDS(&m_dBack);
		//////////////////////////////
		m_Umin 		*= (dWorldBase/dMapFactor); 
		m_Umax 		*= (dWorldBase/dMapFactor); 
		m_Vmin 		*= (dWorldBase/dMapFactor); 
		m_Vmax 		*= (dWorldBase/dMapFactor);
		m_dFront 	*= (dWorldBase/dMapFactor);
		m_dBack 	*= (dWorldBase/dMapFactor);
		////////////////////////////////// 
	}
	/////////////////////////////
	p3DMath->Set3DPts(&m_CW,(m_Umax+m_Umin)*.5,(m_Vmax+m_Vmin)*.5,0.0);// Window Center
	p3DMath->Set3DPts(&m_PRP,m_CW.x,m_CW.y,10.*(dWorldBase/dMapFactor));// View Projection Point
   	/////////////////////////////////////////////////// 3D ViewPort
	p3DMath->Set3DPts(&m_VPmin,0.,0.,0.);//  Min 0<=VPxmin etc <=1
	p3DMath->Set3DPts(&m_VPmax,1,1,1);//  Max
    /////////////////////////////////////////////////// MATRICES
	p3DMath->GetIdentityMATRIX(&m_IdentityM);	// Identity 
    m_LocalM		= m_IdentityM;				// Local
    ////////////////////////////////////////////// All Others
	UpdateAllOtherMatButLocal();
	/////////////////////////////////////////////////// View Direction
	if(m_bParallel)
	{                                  				// Needed for
		m_VDir.x = m_CW.x - m_PRP.x;          		// BackFace(3D)
		m_VDir.y = m_CW.y - m_PRP.y;         		// Culling
		m_VDir.z = m_CW.z - m_PRP.z;
	}	                     	
	else
		m_VDir = m_PRP;
	//////////////////////////////// normalize
	double len;
	len = sqrt(m_VDir.x*m_VDir.x + m_VDir.y*m_VDir.y + m_VDir.z*m_VDir.z);
	m_VDir.x /= len; 	
	m_VDir.y /= len; 	
	m_VDir.z /= len; 	
	/////////////////////////////////////////////// Set Globals
	m_bWF_PURE		= TRUE;		// Use wireframe drawing?
	m_bWF_CULL		= FALSE;	// Use wireframe drawing?
	m_bWF_HIDDEN	= FALSE;	// Use wireframe drawing?
	m_bFS_PAINTER	= FALSE;	// Flat DepthSort where applicable.
	m_bFS_ZBUFFER	= FALSE;	// Flat DepthSort where applicable.
	m_bZB_GOURAUD	= FALSE;	// Use ZBuffered rendering?
	m_bZB_PHONG		= FALSE;	// Use ZBuffered rendering?
	m_bOffScreen	= FALSE;	// Draw offscreen?
	m_bAntialias	= FALSE;	// Antialias during ZBuffered rendering?
	m_bShadows		= FALSE;	// Cast shadows during ZBuffered rendering?
    /////////////////////////////////////////////// Shrink
	m_bShrinkOn		= FALSE;
	m_dShrink		= 1.0;
	///////////////////////////////
/*
	LtSource	LS[2];
	Set3dLtSource(
		&LS[0], (colorFactor)65000, (colorFactor)32000, (colorFactor)32000,
		f_0p5, Int2Fix( 160 ), Int2Fix( 50 ), Int2Fix( -160 )
	);
	Set3dLtSource(
		&LS[1], (colorFactor)32000, (colorFactor)32000, (colorFactor)65000,
		f_0p25, Int2Fix( -160 ), Int2Fix( 0 ), Int2Fix( -260 )
	);
	pL = NewLighting( (colorFactor)48000, 32000, 32000, fixratio( 10, 100 ), 2, LS );
*/	
	//////////////////////////////////////////////////////////// RePosition OperStat
	GetClientRect(&clientRect);
	CPoint ptLeftTop;
	ptLeftTop.x = clientRect.left + (clientRect.Width() - 102)/2;  
	ptLeftTop.y = clientRect.top + 1;
	ClientToScreen(&ptLeftTop);
	pWnd->GetOperStat()->SetWindowPos(NULL,ptLeftTop.x,ptLeftTop.y,102,20,SWP_NOZORDER|SWP_SHOWWINDOW);
	////////////// 
/*
	ptLeftTop.x = clientRect.left + 1;  
	ptLeftTop.y = clientRect.bottom - 40;
	ClientToScreen(&ptLeftTop);
	pWnd->GetCurrStat()->SetWindowPos(NULL,ptLeftTop.x,ptLeftTop.y,300,40,SWP_NOZORDER|SWP_SHOWWINDOW);
*/
  //////////////

}	

void CDrawView::UpdateAllOtherMatButLocal()
{
    UpdateViewMatrix();
   	if(!m_bParallel)
   		UpdatePerToParMatrix();
    UpdateCombinedMatrix();
	UpdateWin3DtoViewPort3DMatrix();
	UpdatePenultimateMatrix();				// Penultimate
	UpdateUltimateMatrix();				// Ultimate
}

void CDrawView::UpdateViewMatrix()
{
	//////////////////////////
	CXForm XForm(m_bParallel);
	//////////////////////////
	m_dzMin = XForm.ComposeViewMATRIX
				(
					&m_ViewM,m_VRP,m_VPN,m_VUP,m_CW,m_PRP,
//					m_dFront,m_dBack,m_Width_U,m_Width_V
					m_dFront,m_dBack,m_Umax-m_Umin,m_Vmax-m_Vmin
				);	
	//////////////////////////
}

void CDrawView::UpdatePerToParMatrix()
{
	C3DMath Math3D;
	Math3D.GetIdentityMATRIX(&m_PerToParM);
	//////////////////////////
	CXForm XForm(m_bParallel);
	//////////////////////////
	XForm.PerToParCVVMATRIX(&m_PerToParM,m_dzMin); 
	///////////////
}	

void CDrawView::UpdateCombinedMatrix()
{
	//////////////////////////
	CXForm XForm(m_bParallel);
	//////////////////////////
	XForm.ComposeCombineMATRIX
			(&m_LocalM,&m_ViewM,&m_ComposedM);		// Composed
}

void CDrawView::UpdateWin3DtoViewPort3DMatrix()
{

	//////////////////////////
	CXForm XForm(m_bParallel);
	//////////////////////////
	XForm.ComposeWin3DtoScreen3DMATRIX
			(&m_vv3DM,m_VPmin,m_VPmax);				// Winto3DViewport3D
	//////////////////////////////////////////////
}

void CDrawView::UpdatePenultimateMatrix()
{
	//////////////////////////
	CXForm XForm(m_bParallel);
	//////////////////////////
	XForm.ComposeCombineMATRIX
			(&m_ComposedM,&m_vv3DM,&m_PenultiM);		// Penultimate
	//////////////////////////
}

void CDrawView::UpdateUltimateMatrix()
{
	//////////////////////////////////////////////////	
	// RIGHT NOW WE PROJECT  POINTWISE SEPARATELY	//
	//		SO, WE DONOT NEED THIS MATRIX			//
	//				USE IT LATER					//
	//		ARBITRARILY SET TO m_PenultiM			//				 
	//////////////////////////////////////////////////
	m_UltimateM = m_PenultiM;		// Ultimate
	//////////////////////////
}

void CDrawView::UpdateObject(int nInvalidObjIndex,int nObjType,int nViewNumber)
{ 


	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	// When the currently selected Object changes:
	// scroll the view so that the newly selected Object is visible, and
	// ask the derived class to repaint the selected and previously
	// selected Objects.

	CClientDC dc(this);
	OnPrepareDC(&dc);

	CRect rectClient;
	GetClientRect(&rectClient);
	
	CRect rectInvalid;
	int iList	= pObjectMgr->ObjTypeToListIndex(nObjType);
	CDListMgr*	pList = pObjectMgr->GetObjectListFromIndex(iList);
	////////////////////////////////////////////////////////////// Ignore Not Viewable
	CDrObject* pObject  = (CDrObject*)pList->GetObject(nInvalidObjIndex);
	int nElemType		= pObject->GetElemType();
	if( nElemType <0) 	// Not Viewable
		return;
	////////////////////////////////////////////////////////////// Compute Bounding Rect
/*
	if (pObjectMgr->IsViewChanged() )
	{
    	/////////////////////////////////////////////// MATRICES
		UpdateAllOtherMatButLocal();
		/////////////////////////////////
//		pObjectMgr->SetViewChanged(FALSE);
	}
*/
	if (pObjectMgr->IsSceneChanged() )
	{
		/////////////////////////////////////////////// GetReady
		GetObjectReadyforRender(&dc,pObject,nObjType);
		/////////////////
//		pObjectMgr->SetSceneChanged(FALSE); // done later onPreviousElement
	}	
	//////////////////////////////////////////////////////////////		
	rectInvalid	   		= pObject->GetBoundingRect();
    /////////////////////////
	dc.LPtoDP(&rectInvalid);
	/////////////////////////

	// If necessary, scroll the window so the newly selected Object is
	// visible
	
	POINT pt = GetDeviceScrollPosition(); 
	
	BOOL bNeedToScroll = FALSE;
	
	if (rectInvalid.left < rectClient.left)
	{
		pt.x += rectInvalid.left;
		bNeedToScroll = TRUE;
	}
	if (rectInvalid.right > rectClient.right)
	{
		pt.x += rectInvalid.right - rectClient.right;
		bNeedToScroll = TRUE;
	}
	if (rectInvalid.top < rectClient.top)
	{
		pt.y += rectInvalid.top;
		bNeedToScroll = TRUE;
	}
	if (rectInvalid.bottom > rectClient.bottom)
	{
		pt.y += rectInvalid.bottom - rectClient.bottom;
		bNeedToScroll = TRUE;
	}
	////////////////////////////////////////////////////// Keep ScrollDevPt.>=0
	if(pt.x<0) pt.x = 0;
	if(pt.y<0) pt.y = 0;
	////////////////////
	CPoint ptW(0,0);
	if (bNeedToScroll)
	{
		ScrollToDevicePosition(pt);
		// Scrolling will cause the newly selected Object to be
		// redrawn in the invalidated area of the window.
		
        // to skip assertion of Window Origin of Viewscroll.Onpreparedc.93
        dc.SetWindowOrg(ptW); 
		OnPrepareDC(&dc);  // Need to prepare the DC again because
			// ScrollToDevicePosition() will have changed the viewport
			// origin.  The DC is used some more below.
	}

	// Invalidate Selected Object
	/////////////////////////
//	InvalidateRect(&rectInvalid);     // already in client(Device) coord
//	OnPrepareDC(&dc);  				  // Need to prepare the DC again because ???
//	UpdateWindow();                   // Paint it right now!
									  // Node Label Current Index
									  // will be lost otherwise 
	InvalidateRect(&rectInvalid);	  // already in client(Device) coord
//	Invalidate();									  	
	///////////////////////////////////////
	int nSelectedObjIndex = nInvalidObjIndex;	
	int nSelectedObjType  = nObjType;	
	if( m_nPrevSelectedObjType	== NONE)
	{
		/////////////////////////// Initialize
		m_nPrevSelectedObjIndex = nSelectedObjIndex;
		m_nPrevSelectedObjType	= nObjType;
		return;
	}
	// Give the derived class an opportunity to repaint the
	// previously selected Object, perhaps to Change color/un-highlight it.
	if ( 
			(m_nPrevSelectedObjIndex != nSelectedObjIndex) ||
			(m_nPrevSelectedObjType != nSelectedObjType)
	   )
	{
		iList	= pObjectMgr->ObjTypeToListIndex(m_nPrevSelectedObjType);
		pList	= pObjectMgr->GetObjectListFromIndex(iList);
		////////////////////////////////////////////////////	
		pObject = (CDrObject*)pList->GetObject(m_nPrevSelectedObjIndex);
		if(pObject)
		{
			if(m_OpMode == OP_OUTPUT)
			{
				if((m_nPrevSelectedObjType == PATCH) || (m_nPrevSelectedObjType == CURVE) )
					if( pObject->IsDirty() )	
						return;
			}		
			////////////////////////////////////////////////////////// Compute Bounding Rect
			if (pObjectMgr->IsSceneChanged() )
			{
				GetObjectReadyforRender(&dc,pObject,m_nPrevSelectedObjType);
				/////////////////
				pObjectMgr->SetSceneChanged(FALSE);
				/////////////////	
			}	
			rectInvalid	   = pObject->GetBoundingRect();
			//////////////////////////////////////////////////////////		
			dc.LPtoDP(&rectInvalid);
			InvalidateRect(&rectInvalid);
//			OnPrepareDC(&dc);  // Need to prepare the DC again because ???
		}
		//////////////////////////////////////////// update
		m_nPrevSelectedObjIndex = nSelectedObjIndex;
		m_nPrevSelectedObjType	= nSelectedObjType;
	}


}

void CDrawView::OnDraw(CDC* pDC)
{

	////////////////////////////////////////////////////////////// Grid
	if(!pDC->IsPrinting() )
		ShowScreenGrid(pDC);
	////////////////////////////////////////////////////////////// Options
//	ShowCurrentOptions(pDC);
	////////////////////////////////////////////////////////////// Axes
//	GoDoAxis(pDC);															NOT USED
	////////////////////////////////////////////////////////////// ViewControls
//	GoDoViewControls(pDC);													NEED TO WORK ON IT 082896                                       
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////
	// N O T E:			For INDEXing Purpose					//
	//                                                          //
	//	1.	OBJ3D, Individual Elements, UnPosted(Dirty) PATCHes	//
	//		 & CURVEs are in THE List							//
	//	2.	POSTED PATCHes are in PATCH LIST of their OBJ3D.	//
	//	3.	POSTED CURVEs are in CURVE LIST of their OBJ3D.		//
	//	4.	GENERATED POLYs are in POLY LIST of their PATCH.    //
    //  5.  GENERATED NODEs are in NODE LIST of their POLY.     //
    //															//
    //////////////////////////////////////////////////////////////
	HCURSOR		saveCurs;
	BOOL		interrupted = FALSE;
	
	saveCurs = SetCursor( LoadCursor( NULL, IDC_WAIT ) );
	//////////////////////////////
	CRect 	RectClip;
	pDC->GetClipBox(&RectClip); // Get the invalidated region
	pDC->LPtoDP(&RectClip);
    ////////////////////////////////////////////////// PreProcess Objects
    												// For Rendering
	if(pObjectMgr->IsViewChanged())
	{
    	/////////////////////////////////////////////// MATRICES
		UpdateAllOtherMatButLocal();
		//////////////////////		
 	}
	/////////////////////////////////////////////////// Render
	int nActiveObjIndex = pObjectMgr->GetActiveObjectIndex();
	int nActiveObjType	= pObjectMgr->GetActiveObjectType();
	if 	(	GetObjectCount() == 0 || 
			nActiveObjIndex < VIEWABLE_INDEX_BEGIN
		)
		return;
	///////////////////////////////////////	
	GoRender(pDC,RectClip,nActiveObjType,nActiveObjIndex);
	///////////////////////////////////////
	pObjectMgr->SetViewChanged(FALSE);
	pObjectMgr->SetSceneChanged(FALSE);
	/////////////////////////////////////// House Demo
//	GoDoHouse(pDC);							NOT NEEDED ANYMORE 082896
	///////////
	SetCursor( saveCurs );
}

void CDrawView::ShowScreenGrid(CDC* pDC)
{
	int stepx = 100,stepy = 100; 
	//////////////////////////
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	///////////////////////////////////////////////////////////////////// TextOut 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen* pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
    /////////////////////////////////////////////////// Color
	int i,totx,toty;
	CRect clientRect;
	GetClientRect(&clientRect);
 	pDC->DPtoLP(&clientRect);
	////////////////////////////
	clientRect.NormalizeRect();
	///////////////
	CBrush* pBrushOld = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
   	CPen    Pen;
   	CPen*   pPenOld; 
	COLORREF colr = RGB(128,128,128)| 0x2000000;                       
   	Pen.CreatePen (pDrPen->GetStyle(),0,colr );
  	pPenOld = pDC->SelectObject(&Pen);
	//////////////////
	totx = clientRect.Width();
	toty = clientRect.Height();
	for (i = clientRect.left;i<clientRect.left + totx;i += stepx)
	{
		pDC->MoveTo(i,clientRect.top);
		pDC->LineTo(i,clientRect.bottom);
	}
	for (i = clientRect.top;i<clientRect.top + toty;i += stepy)
	{
		pDC->MoveTo(clientRect.left,i);
		pDC->LineTo(clientRect.right,i);
	}
  	///////////////////////////////////////////////////// Reset
	pDC->SelectObject(pPenOld);
	pDC->SelectObject(pBrushOld);
    Pen.DeleteObject();
	///////////
}

void CDrawView::ShowCurrentOptions(CDC* pDC)
{
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////// CREATE
	int i,j;
	CString nameO("UNKNOWN");
	CString nameI("UNKNOWN");
	CString nameC("UNKNOWN");
	//////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////////////////////// Encode
	j = sprintf(buf,"Current Options: ");
	/////////////////////////////////////// Oper (Temporarily: TODO: create GLB_Oper.h)
	UINT OperID	= pWnd->GetCurrentOperID();
	///////////
	if(OperID == COP_CREATE)
		nameO = "CREATE";
	///////////////////
	j += sprintf(buf+j,"%s ",nameO);
	/////////////////////////////////////// IGen
	UINT IGenID	= pWnd->GetCurrentIGenID();
   	/////////////////////////
	switch(IGenID)
	{
		case NODE:
   			for (i = 0;i<nMax_ElemTypes;i++)
   				if(ElTypes[i].num == (int)IGenID) 
   				{
   					nameI = ElTypes[i].ObjName;
   					break;
   				}
			break;

 		case CURVE:
  			for (i = 0;i<nMax_CurveTypes;i++)
   				if(CuTypes[i].num == (int)IGenID) 
   				{
   					nameI = CuTypes[i].ObjName;
   					break;
   				}	
			break;

 		case PATCH:
  			for (i = 0;i<nMax_PatchTypes;i++)
   				if(PaTypes[i].num == (int)IGenID) 
   				{
   					nameI = PaTypes[i].ObjName;
   					break;
   				}	
			break;

 		case SOLID:
  			for (i = 0;i<nMax_SolidTypes;i++)
   				if(SoTypes[i].num == (int)IGenID) 
   				{
   					nameI = SoTypes[i].ObjName;
   					break;
   				}
			break;

		default:
			break;
	}
  	////////////////////////////////////// Encode
	j += sprintf(buf+j,"%s ",nameI);
	////////////////////////////////////////////// CntlID
	UINT CntlID	= pWnd->GetCurrentCntlID();
   	/////////////////////////
	switch(CntlID)
	{
		case ELEMENT:
   			for (i = 0;i<nMax_ElemTypes;i++)
   				if(ElTypes[i].num == (int)CntlID) 
   				{
   					nameC = ElTypes[i].ObjName;
   					break;
   				}
			break;

 		case STATICLOAD:
 		case FORCE:
 		case DISPLACE:
 		case PRESSURE:
 		case THERMAL:
 		case LUMPWT:
  			for (i = 0;i<nMax_StaLTypes;i++)
   				if(StaLTypes[i].num == (int)CntlID) 
   				{
   					nameC = StaLTypes[i].ObjName;
   					break;
   				}	
			break;

 		case SUPPORT:
 		case SUPPORT_RIGID:
 		case SUPPORT_LINSPRING:
 		case SUPPORT_LINSNUBBER:
 		case SUPPORT_NLSPRING:
 		case SUPPORT_NLSNUBBER:
  			for (i = 0;i<nMax_SuppTypes;i++)
   				if(SuTypes[i].num == (int)CntlID) 
   				{
   					nameC = SuTypes[i].ObjName;
   					break;
   				}	
			break;
/*
 		case SPECTRALOAD:
  			for (i = 0;i<nMax_SolidTypes;i++)
   				if(SoTypes[i].num == IGenID) 
   				{
   					name = SoTypes[i].ObjName;
   					break;
   				}
			break;
*/
		default:
			break;
	}
  	////////////////////////////////////// Encode
	j += sprintf(buf+j,"%s ",nameC);
	str->ReleaseBuffer();
	///////////////////////////////////////////////////////////////////// TextOut 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrFont* pDrFont		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT);
	CDrPen* pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CPrecision* pPrecision	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	long lWorldBase			= (long)pPrecision->GetWorldBase();
    /////////////////////////////////////////////////// Color
	CRect clientRect;
	GetClientRect(&clientRect);
 	pDC->DPtoLP(&clientRect);
	////////////////////////////
	clientRect.NormalizeRect();
	////////////////////////
  	COLORREF crColorOld;
   	COLORREF crColor	= pDrFont->GetTextColor();
	crColorOld			= pDC->SetTextColor(crColor);
	int modeOld			= pDC->SetBkMode(TRANSPARENT);
	/////////////////////////////////////////////////// Font
	LOGFONT Lf			= pDrFont->GetCurrentLogFont();
	CFont Font;
	////////////////
	Lf.lfWeight		= FW_BOLD;
	Lf.lfItalic		= TRUE;
	Lf.lfUnderline	= TRUE;
	////////////////
	Font.CreateFontIndirect(&Lf);
	CFont* pOldFont = (CFont*)(pDC->SelectObject(&Font));
	/////////////////
/*
	int mapModeOld		= pDC->SetMapMode(MM_TEXT);
	CPoint VuportOrgOld	= pDC->SetViewportOrg(0,0);
	CPoint WndOrgOld	= pDC->SetWindowOrg(0,0);
*/
	///////////////
	clientRect.DeflateRect( 5, 5 );
	CBrush* pBrushOld = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
   	CPen    Pen;
   	CPen*   pPenOld;                        
   	Pen.CreatePen (pDrPen->GetStyle(),pDrPen->GetWidth(),pDrPen->GetColor());
  	pPenOld = pDC->SelectObject(&Pen);
	/////////
//	pDC->Rectangle(&clientRect);
	CString s;
	s = *str;
	///////////////////////////////////////////////////// MapMode
	int OldMode		= pDC->GetMapMode();
	CPoint ptWOrg	= pDC->GetWindowOrg();
	CPoint ptVOrg	= pDC->GetViewportOrg();

	pDC->SetMapMode(MM_TEXT);
	pDC->SetWindowOrg(0,0);
	pDC->SetViewportOrg(0,0);
	/////////////////////////
	CPoint ptScroll = GetDeviceScrollPosition();
	CPoint pt;
	pt.x = ptVOrg.x + ptScroll.x + 10;
	pt.y = ptVOrg.y + ptScroll.y + 10;
	BOOL bOk = pDC->TextOut(pt.x,pt.y,s);
	////////////////////
 	pDC->SetMapMode(OldMode);
	pDC->SetWindowOrg(ptWOrg);
	pDC->SetViewportOrg(ptVOrg);
  	///////////////////////////////////////////////////// Reset
	pDC->SelectObject(pPenOld);
	pDC->SelectObject(pBrushOld);
	pDC->SelectObject(pOldFont);
/*
	pDC->SetMapMode(mapModeOld);
	pDC->SetViewportOrg(VuportOrgOld);
	pDC->SetWindowOrg(WndOrgOld);
*/
	pDC->SetTextColor(crColorOld);
	pDC->SetBkMode(modeOld);
 	Font.DeleteObject();
    Pen.DeleteObject();
	/////
 	delete str;
	///////////
}

void CDrawView::GoDoAxis(CDC* pDC)
{
//	NOT USED
}

void CDrawView::GoDoHouse(CDC* pDC)
{
	int		nDataPts = 10;
	WORLD	DataPt[] = {	// data points for House
		{ 0., 0.,3.0}
	,	{1.6, 0.,3.0}
	,	{1.6,1.0,3.0}
	,	{ .8,1.6,3.0}
	,	{ 0.,1.0,3.0}
	,	{ 0., 0.,5.4}
	,	{1.6, 0.,5.4}
	,	{1.6,1.0,5.4}
	,	{ .8,1.6,5.4}
	,	{ 0.,1.0,5.4}
	};
	
	////////////////////////////////////////// Scale
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current Node
	long  lWorldBase  	= pPrecision->GetWorldBase(); 
    double dWorldBase 	= (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////////// 
	C3DMath Math3D;
	C3DMath* p3DMath = &Math3D;
	///////////////////////////
	int i;
	for (i=0;i<nDataPts;i++)
	{
		/////////////////////////// strip Scale Factor (World Coord)
		pObjectMgr->SCtoDS(&(DataPt[i].x));
		pObjectMgr->SCtoDS(&(DataPt[i].y));
		pObjectMgr->SCtoDS(&(DataPt[i].z));
    	//////////////////////////////
		p3DMath->Scale3DPts(dWorldBase/dMapFactor,&DataPt[i]);
	}
	////////////////////////////////////////// Transform & Project
	WORLD 	Per;
	WORLD xfDataPt[10];
	POINT ptDataPt[10];
	///////////////////////// 
	for (i=0;i<nDataPts;i++)
	{
		/////////////////////////////////////// Xform
		Transform(&DataPt[i], &xfDataPt[i]);
		/////////////////////////////////////// clip
		// do it in a while
		/////////////////////////////////////// if Perspective,change Pers->Par
		if(!m_bParallel)
		{
			CXForm XForm(m_bParallel);
			XForm.TransformPerToParCVV(m_dzMin, &xfDataPt[i], &Per);
//			XForm.Transform(&xfDataPt[i], &Per, &m_PerToParM); 
			xfDataPt[i] = Per; 
			
		}	 
		Project(&xfDataPt[i], &DataPt[i],TRUE);
	}
	////////////////////////////////////////// Points
	for (i=0;i<nDataPts;i++)
	{
		ptDataPt[i].x = (int)(DataPt[i].x);
		ptDataPt[i].y = (int)(DataPt[i].y);
	}
	///////////////////////////////////////////////////////////////////// Draw 
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
 	///////////////////////////////////////////////
   	CPen    Pen;
   	CPen*   PtrOldPen;
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen 
   	Pen.CreatePen (pDrPen->GetStyle(),pDrPen->GetWidth(),pDrPen->GetColor()); 
   	PtrOldPen = pDC->SelectObject(&Pen);
   	////////////////////////////////////
	pDC->Polyline(ptDataPt,5);	
	GoDoLine(pDC,&ptDataPt[4],&ptDataPt[0]);
	pDC->Polyline(&ptDataPt[5],5);	
	GoDoLine(pDC,&ptDataPt[9],&ptDataPt[5]);
	////////
	GoDoLine(pDC,&ptDataPt[0],&ptDataPt[5]);
	GoDoLine(pDC,&ptDataPt[1],&ptDataPt[6]);
	GoDoLine(pDC,&ptDataPt[2],&ptDataPt[7]);
	GoDoLine(pDC,&ptDataPt[3],&ptDataPt[8]);
	GoDoLine(pDC,&ptDataPt[4],&ptDataPt[9]);
	///////////////////////////////////////////////////////////////////////////
   	pDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
	//////////////////////////////////////////	

}

void CDrawView::GoDoViewControls(CDC* pDC)
{

	///////////////////////////////////////////////
	C3DMath Math3D;
	C3DMath* p3DMath = &Math3D;
    ////////////////////////////////////////////////// 
	WORLD VDIR,VPN,CW,PRP,VRP,Vx,Vy,Vz,Wo,Wx,Wy,Wz;
	WORLD xfCW,xfPRP,xfVRP,xfWo,xfVx,xfVy,xfVz,xfWx,xfWy,xfWz;
	POINT ptCW,ptPRP,ptVRP,ptWo,ptVx,ptVy,ptVz,ptWx,ptWy,ptWz; 
	CString str;
	////////////////////////////
	VRP	= GetVRP();
	VPN = GetVPN();
	PRP	= GetPRP();
	CW	= GetCW();
//	p3DMath->Set3DPts(&Vx,VRP.x+50.,0.0,0.0);// 
//	p3DMath->Set3DPts(&Vy,0.0,VRP.y+50.,0.0);// 
//	p3DMath->Set3DPts(&Vz,0.0,0.0,VRP.z+50.);// 
	p3DMath->Set3DPts(&Wo,0.0,0.0,0.0);// 
	p3DMath->Set3DPts(&Wx,10000.,0.0,0.0);// 
	p3DMath->Set3DPts(&Wy,0.0,10000.,0.0);// 
	p3DMath->Set3DPts(&Wz,0.0,0.0,10000.);// 
	///////////////////////////////////////////////// XForm & Project
	Transform(&VRP, &xfVRP);
	Project(&xfVRP, &VRP,TRUE);
	ptVRP.x = (int)VRP.x;
	ptVRP.y = (int)VRP.y;
/*	
	Transform(&Vx, &xfVx);
	Project(&xfVx, &Vx,TRUE);
	ptVx.x = (int)Vx.x;
	ptVx.y = (int)Vx.y;
	Transform(&Vy, &xfVy);
	Project(&xfVy, &Vy,TRUE);
	ptVy.x = (int)Vy.x;
	ptVy.y = (int)Vy.y;
	Transform(&Vz,&xfVz);
	Project(&xfVz, &Vz,TRUE);
	ptVz.x = (int)Vz.x;
	ptVz.y = (int)Vz.y;
*/	
	/////////////////////////
	Transform(&Wo, &xfWo);
	Project(&xfWo, &Wo,TRUE);
	ptWo.x = (int)Wo.x;
	ptWo.y = (int)Wo.y;
	Transform(&Wx, &xfWx);
	Project(&xfWx, &Wx,TRUE);
	ptWx.x = (int)Wx.x;
	ptWx.y = (int)Wx.y;
	Transform(&Wy, &xfWy);
	Project(&xfWy, &Wy,TRUE);
	ptWy.x = (int)Wy.x;
	ptWy.y = (int)Wy.y;
	Transform(&Wz,&xfWz);
	Project(&xfWz, &Wz,TRUE);
	ptWz.x = (int)Wz.x;
	ptWz.y = (int)Wz.y;
	/////////////////////////
	Transform(&PRP, &xfPRP);
	Project(&xfPRP, &PRP,TRUE);
	ptPRP.x = (int)PRP.x;
	ptPRP.y = (int)PRP.y;
	/////////////////////////
	Transform(&CW, &xfCW);
	Project(&xfCW, &CW,TRUE);
	ptCW.x = (int)CW.x;
	ptCW.y = (int)CW.y;
	//////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
 	///////////////////////////////////////////////
   	CPen    Pen;
   	CPen*   PtrOldPen;
	/////////////////////////////////////////////////// 
//	IF bLayerON = FALSE make PEN: DASHED or something     TO BE Done Later
    /////////////////////////////////////////////////// Pen 
   	Pen.CreatePen (pDrPen->GetStyle(),pDrPen->GetWidth(),pDrPen->GetColor()); 
   	PtrOldPen = pDC->SelectObject(&Pen);
	////////////////////////////// DoIt
	str = "VRP";
	GoDoPoint(pDC,&ptVRP,str);
//	GoDoLine(pDC,&ptVRP,&ptVx);
//	GoDoLine(pDC,&ptVRP,&ptVy);
//	GoDoLine(pDC,&ptVRP,&ptVz);
	///////////////////////////
	str = "Wo";
	GoDoPoint(pDC,&ptWo,str);
	str = "X";
	GoDoPoint(pDC,&ptWx,str);
	str = "Y";
	GoDoPoint(pDC,&ptWy,str);
	str = "Z";
	GoDoPoint(pDC,&ptWz,str);
	GoDoLine(pDC,&ptWo,&ptWx);
	GoDoLine(pDC,&ptWo,&ptWy);
	GoDoLine(pDC,&ptWo,&ptWz);
	////////////////////////
	str = "PRP";
	GoDoPoint(pDC,&ptPRP,str);
	str = "CW";
	GoDoPoint(pDC,&ptCW,str);
	GoDoLine(pDC,&ptPRP,&ptCW);
	///////////////////////////////////////////////////////////////////////////
   	pDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject(); 
}	 
//////////////////////
#define	NODE_SIZE	5
#define	TEXT_OFF	3

void CDrawView::GoDoPoint(CDC* PtrDC,POINT* pt,CString& text)
{ 

   	//////////////////////////////////////////////// Draw
   	////////////////////////////////////// Cross 
   	PtrDC->MoveTo(pt->x-2*NODE_SIZE,pt->y);
   	PtrDC->LineTo(pt->x+2*NODE_SIZE,pt->y);
   	PtrDC->MoveTo(pt->x,pt->y-2*NODE_SIZE);
   	PtrDC->LineTo(pt->x,pt->y+2*NODE_SIZE);
   	////////////////////////////////////// Text
   	PtrDC->TextOut(pt->x+TEXT_OFF,pt->y+TEXT_OFF, text );	// draw the string
	/////////////////////////////// 
   	
}   

void CDrawView::GoDoLine(CDC* PtrDC,POINT* pt1,POINT* pt2)
{ 

   	//////////////////////////////////////////////// Draw
   	PtrDC->MoveTo(pt1->x,pt1->y);
   	PtrDC->LineTo(pt2->x,pt2->y);
	/////////////////////////////// 
   	
}   

void CDrawView::GetObjectReadyforRender(CDC* pDC,CDrObject* pObject,
													int nObjType)
{
	if(!(pObject->IsShow()))
		return;
	///////////////////////////////////////////////////
	Pack_NSBools(m_bNS); 
	/////////////////////////////////////////////////// Render
	if(m_Rendition == WF_PURE)
	{
		if(!m_bCulling3D)
		{
			CWire_0	Wire_0(this,WF_PURE,m_bParallel,m_bNS,m_bNoSoEL,m_bNoSoLabEL);
			////////////////
			Wire_0.Init
				(
					m_nView,m_bCulling3D,m_VDir,
					&m_ViewM,&m_ComposedM,&m_vv3DM,m_dzMin,
					m_dScale_U,m_dScale_V,m_dShrink
				);
			Wire_0.RenderReadyOBJECT(pDC,pObject,nObjType);
			///////////////////
		}
		else
		{
			CWire_1	Wire_1(this,WF_PURE,m_bParallel,m_bNS,m_bNoSoEL,m_bNoSoLabEL);
			////////////////
			Wire_1.Init
				(
					m_nView,m_bCulling3D,m_VDir,
					&m_ViewM,&m_ComposedM,&m_vv3DM,m_dzMin,
					m_dScale_U,m_dScale_V,m_dShrink
				);
			Wire_1.RenderReadyOBJECT(pDC,pObject,nObjType);
			///////////////////
		}
		///////	
	}
}

void CDrawView::Pack_NSBools(BOOL bNS[])
{
	/////////////////////////////////////////////////// Pack NSBOOLs
	bNS[ 0] = m_bNS_CVV;  
	bNS[ 1] = m_bNS_VV; 
	bNS[ 2] = m_bNS_VRP; 
	bNS[ 3] = m_bNS_PRP; 
	bNS[ 4] = m_bNS_VUP; 
	bNS[ 5] = m_bNS_VPN; 
	bNS[ 6] = m_bNS_CW; 
	bNS[ 7] = m_bNS_VPlane; 
	bNS[ 8] = m_bNS_VDIR; 
	bNS[ 9] = m_bNS_WC; 
	bNS[10] = m_bNS_VRC; 
	bNS[11] = m_bNS_NPC; 
	bNS[12] = m_bNS_Front; 
	bNS[13] = m_bNS_Back;
	/////////////////////// 
	bNS[14] = m_bNS_2DLabel;  
	bNS[15] = m_bNS_3DLabel; 
	bNS[16] = m_bNS_CNLabel; 
	bNS[17] = m_bNS_CNode; 
	bNS[18] = m_bNS_NLabel; 
	bNS[19] = m_bNS_Node; 
	bNS[20] = m_bNS_CShape; 
	bNS[21] = m_bNS_Normal; 
	bNS[22] = m_bNS_Centroid; 
	bNS[23] = m_bNS_D_Object; 
	bNS[24] = m_bNS_D_Solid; 
	bNS[25] = m_bNS_D_Patch; 
	bNS[26] = m_bNS_D_Curve; 
	bNS[27] = m_bNS_P_Object; 
	bNS[28] = m_bNS_P_Solid; 
	bNS[29] = m_bNS_P_Patch; 
	bNS[30] = m_bNS_P_Curve;
    ////////////////////////////
	bNS[31] = m_bNS_D_Profile_S; 
	bNS[32] = m_bNS_D_Profile_P; 
	bNS[33] = m_bNS_D_Profile_C;
    ////////////////////////////
	bNS[34] = m_bNS_P_Profile_S; 
	bNS[35] = m_bNS_P_Profile_P; 
	bNS[36] = m_bNS_P_Profile_C;
	////////////////////////////
	bNS[37] = m_bNS_RIGID; 
	bNS[38] = m_bNS_Lin_Spring; 
	bNS[39] = m_bNS_Lin_Snubber; 
	bNS[40] = m_bNS_Non_Spring; 
	bNS[41] = m_bNS_Non_Snubber;
	////////////////////////////// MeshNode
	bNS[42] = m_bNS_MNLabel;	
	bNS[43] = m_bNS_MNode;	
	////////////////////////////// StaticLoad
	bNS[44]	= m_bNS_Force;	
	bNS[45] = m_bNS_Displace;
	bNS[46] = m_bNS_Pressure;
	bNS[47] = m_bNS_Thermal;
	bNS[48] = m_bNS_LumpWt;
	////////////////////////////// Labels
	int i, nStart = 50;
	///////////////////
	for (i=0;i<MAX_NOSOLABDIRTY;i++)
		bNS[nStart+i] = m_bNS_LabDirty[i];
	nStart += MAX_NOSOLABDIRTY; 
	//
	for (i=0;i<MAX_NOSOLABPOSTED;i++)
		bNS[nStart+i] = m_bNS_LabPosted[i];
	nStart += MAX_NOSOLABPOSTED; 
	//
	for (i=0;i<MAX_NOSOLABSUPPORT;i++)
		bNS[nStart+i] = m_bNS_LabSupp[i];
	nStart += MAX_NOSOLABSUPPORT; 
	//
	for (i=0;i<MAX_NOSOLABSTATIC;i++)
		bNS[nStart+i] = m_bNS_LabStatic[i];
	nStart += MAX_NOSOLABSTATIC; 
	//////////////////////////////////////	 
    
}

void CDrawView::GoRender(CDC* pDC,CRect RectClip,int nActiveObjType,int nActiveObjIndex)
{ 
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
	Pack_NSBools(m_bNS); 
	/////////////////////////////////////////////////// Render
	if(m_Rendition == WF_PURE)
	{
    	/////////////////////////////////////////////////// godoit	
		if(!m_bCulling3D)
		{
			CWire_0	Wire_0(this,WF_PURE,m_bParallel,m_bNS,m_bNoSoEL,m_bNoSoLabEL);
			////////////////
			Wire_0.Init
				(
					m_nView,m_bCulling3D,m_VDir,
					&m_ViewM,&m_ComposedM,&m_vv3DM,m_dzMin,
					m_dScale_U,m_dScale_V,m_dShrink
				);
			/////////////////// GoDoIt	
			if(m_bViewGene)
				Wire_0.RenderScene_GENERATOR((CClientDC*)pDC,RectClip,nActiveObjType,
									nActiveObjIndex,m_nView);
			if(m_bViewMesh)
				Wire_0.RenderScene_MESH((CClientDC*)pDC,RectClip,nActiveObjType,
									nActiveObjIndex,m_nView);
			///////////////////
		}	
		else
		{ 
 
	   		/////////////////////////////////////////////////// godoit	
			CWire_1	Wire_1(this,WF_PURE,m_bParallel,m_bNS,m_bNoSoEL,m_bNoSoLabEL);
			////////////////
			Wire_1.Init
				(
					m_nView,m_bCulling3D,m_VDir,
					&m_ViewM,&m_ComposedM,&m_vv3DM,m_dzMin,
					m_dScale_U,m_dScale_V,m_dShrink
				);
			/////////////////// GoDoIt	
			Wire_1.RenderSCENE((CClientDC*)pDC,RectClip,nActiveObjType,
									nActiveObjIndex,m_nView);
			///////////////////
		}
	   
	}
	///////	
	else
	if(m_Rendition == WF_HIDDEN)
	{ 
 		if(!(m_SortList.IsEmpty())  )
			m_SortList.RemoveAll();
  		/////////////////////////////////////////////////// init/prepare	
		CWire_2	Wire_2(this,WF_HIDDEN,m_bParallel,m_bNS,m_bNoSoEL,m_bNoSoLabEL);
		//////////////////// 
		Wire_2.Init
		(
			m_nView,m_bCulling3D,m_VDir,
			&m_ViewM,&m_ComposedM,&m_vv3DM,m_dzMin,
			m_dScale_U,m_dScale_V,
			m_dShrink,&m_SortList
		);
		///////////////////////////// prepare	
		Wire_2.RenderReadySCENE(pDC);
    	/////////////////////////////////////////////////// godoit	
		Wire_2.RenderSCENE((CClientDC*)pDC,RectClip,nActiveObjType,
								nActiveObjIndex,m_nView);
		////////////////
	}
	///////	
}

void CDrawView::Transform(pWORLD pptIn, pWORLD pptOut)
{
	
	CXForm XForm(m_bParallel);
	/////////////////////////////////////
	XForm.Transform(pptIn,pptOut,&m_ComposedM);
	/////////////////////////////////////	
    return;
}                            

void CDrawView::Project(pWORLD pptIn, pWORLD pptOut,BOOL bSize)
{

	CXForm XForm(m_bParallel);
	////////////////////////////////
	WORLD pt2;
	/////////////////////////////////////
	XForm.Project(&m_vv3DM,pptIn,&pt2);
	//////////////////////////////////////////////// end transform/Project
	if(bSize)
	{
		pptOut->x = (int)(pt2.x * m_dScale_U);
		pptOut->y = (int)(pt2.y * m_dScale_V);
	}
	else	
	{
		pptOut->x = pt2.x;
		pptOut->y = pt2.y;
		pptOut->z = pt2.z;
	}
    //////////////////////////////////////////////// Restore Old 3d context
//	pXForm->SetZoom(dzoom );
	////////////////////////
    return;
}                            
/////////////////////////////////////////////////////////////////////////////
// Implementation
/////////////////////////////////////////////////////////////////////////////
// Overrides of CView for implementing printing.
/*
BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// OnBeginPrinting() is called after the user has committed to
	// printing by OK'ing the Print dialog, and after the framework
	// has created a CDC object for the printer or the preview view.

	// This is the right opportunity to set up the page range.
	// Given the CDC object, we can determine how many rows will
	// fit on a page, so we can in turn determine how many printed
	// pages represent the entire document.

	int nPageHeight = pDC->GetDeviceCaps(VERTRES);
	CalculateRowMetrics(pDC);
	m_nRowsPerPrintedPage = nPageHeight / m_nRowHeight;
	int nPrintableRowCount = LastViewableRow() + 1;
	if (GetRowCount() < nPrintableRowCount)
		nPrintableRowCount = GetRowCount();
	pInfo->SetMaxPage((nPrintableRowCount + m_nRowsPerPrintedPage - 1)
		/ m_nRowsPerPrintedPage);
	pInfo->m_nCurPage = 1;  // start previewing at page# 1
}

void CDrawView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// Print the rows for the current page.

	int yTopOfPage = (pInfo->m_nCurPage -1) * m_nRowsPerPrintedPage
		* m_nRowHeight;

	// Orient the viewport so that the first row to be printed
	// has a viewport coordinate of (0,0).
	pDC->SetViewportOrg(0, -yTopOfPage);

	// Draw as many rows as will fit on the printed page.
	// Clip the printed page so that there is no partially shown
	// row at the bottom of the page (the same row which will be fully
	// shown at the top of the next page).

	int nPageWidth = pDC->GetDeviceCaps(HORZRES);
	CRect rectClip = CRect(0, yTopOfPage, nPageWidth,
		 yTopOfPage + m_nRowsPerPrintedPage * m_nRowHeight);
	pDC->IntersectClipRect(&rectClip);
	OnDraw(pDC);
}
*/
/////////////////////////////////////////////////////////////////////////////
/*
// OLE Client support and commands

BOOL CDrawView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CDrgrafCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CDrawView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CDrgrafCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CDrgrafCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CDrGrafDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CDrgrafCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);

		// If item created from class list (not from file) then launch
		//  the server to edit the item.
		if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.
void CDrawView::OnCancelEdit()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}
// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CDrawView::OnSetFocus(CWnd* pOldWnd)
{
	/////////////////////////////////////////////////////

	CScrollView::OnSetFocus(pOldWnd);
}
*/
/////////////////////////////////////////////////////////////////////////////
// CDrawView commands
void CDrawView::MouseActivateViewMatUpdate()
{
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	CString str;
	////////////////////////
	if
	(
		m_nView == VIEW12 ||
		m_nView == VIEW23 ||
		m_nView == VIEW31
	)
	{
		pWnd->SetOpMode(OP_INPUT);
		if(pWnd->GetCurMenuID() != IDR_INPUTMENU)
			pWnd->SwitchMenu(IDR_INPUTMENU);
		////////////////////////////////////
		pWnd->ModeLessOn();
		///////////////////
//todo		pWnd->GetViewBox()->ShowWindow(SW_HIDE);
		pWnd->GetDrawBox()->ShowWindow(SW_HIDE);
		pWnd->GetIGenBox()->ShowWindow(SW_SHOW);
		pWnd->GetCntlBox()->ShowWindow(SW_SHOW);
		//////////////////////////////////////// StatCntls
//todo		pWnd->GetViewStat()->ShowWindow(SW_HIDE);
		pWnd->GetCntlStat()->ShowWindow(SW_SHOW);
		pWnd->GetIGenStat()->ShowWindow(SW_SHOW);
		pWnd->GetCurrStat()->ShowWindow(SW_SHOW);
		pWnd->GetDrawStat()->ShowWindow(SW_SHOW);
		///
		pWnd->GetAutoAcceptStat()->ShowWindow(SW_SHOW);
		pWnd->GetSingleSegStat()->ShowWindow(SW_SHOW);
		pWnd->GetBLineStat()->ShowWindow(SW_SHOW);
		////////////////////////////////////////
		pWnd->GetOperStat()->ShowWindow(SW_SHOW);
/*
		str = "START";
		pWnd->SetstrOperID(str);
		pWnd->UpdateStaticControls();
*/
		/////////////////////////////////////////
/*
		SetScalevv3DToLP();
		SetParallel(TRUE);
		SetCulling3D(FALSE);
		SetRnMode(WF_PURE);
*/
	}
	else
	if(m_nView == VIEWISO)
	{
		pWnd->SetOpMode(OP_OUTPUT);
		if(pWnd->GetCurMenuID() != IDR_OUTPUTMENU)
			pWnd->SwitchMenu(IDR_OUTPUTMENU);
		//////////////////////////////////////// close MeshBox, ElemBox & DrawBox etc
		pWnd->ModeLessOff();
		////////////////////
		pWnd->GetDrawBox()->ShowWindow(SW_SHOW);
		pWnd->GetIGenBox()->ShowWindow(SW_HIDE);
		pWnd->GetCntlBox()->ShowWindow(SW_HIDE);
		pWnd->GetOperBox()->ShowWindow(SW_HIDE);
		//////////////////////////////////////// StatCntls
		pWnd->GetOperStat()->ShowWindow(SW_HIDE);
		pWnd->GetCntlStat()->ShowWindow(SW_HIDE);
		pWnd->GetIGenStat()->ShowWindow(SW_HIDE);
		pWnd->GetCurrStat()->ShowWindow(SW_HIDE);
		pWnd->GetDrawStat()->ShowWindow(SW_HIDE);
		///
		pWnd->GetAutoAcceptStat()->ShowWindow(SW_HIDE);
		pWnd->GetSingleSegStat()->ShowWindow(SW_HIDE);
		pWnd->GetBLineStat()->ShowWindow(SW_HIDE);
		////////////////////////////////////////
/*
		pWnd->GetViewStat()->ShowWindow(SW_SHOW);
		str = "VIEW";
		pWnd->SetstrOperID(str);
		pWnd->UpdateStaticControls();
*/
		/////////////////////////////////////////
	}
/*
	/////////////////////////////// MATRICES
	UpdateAllOtherMatButLocal();
	////////////////////////////////
*/
}

void CDrawView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
		case VK_HOME:
			ChangeSelectionToObjectIndex(0);
			break;
		case VK_END:
			ChangeSelectionToObjectIndex(GetObjectCount() - 1);
			break;
		case VK_UP:
			ChangeSelectionNextObjectIndex(FALSE);
			break;
		case VK_DOWN:
			ChangeSelectionNextObjectIndex(TRUE);
			break;
		case VK_PRIOR:
			OnVScroll(SB_PAGEUP,
				0,  // nPos not used for PAGEUP
				GetScrollBarCtrl(SB_VERT));
			break;
		case VK_NEXT:
			OnVScroll(SB_PAGEDOWN,
				0,  // nPos not used for PAGEDOWN
				GetScrollBarCtrl(SB_VERT));
			break;
		default:
			CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
	}
}
/////////////////////////////////////////////////////////////////////////////
// CDrGrafView message handlers

int CDrawView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	////////////////////////////////////////////// Axis Window
	CRect Rect;
	Rect.left = Rect.top = Rect.right = Rect.bottom = 0;
	BOOL bOk = m_wndAxisDraw.Create
				(
					NULL,
					NULL,
					WS_CHILD,
					Rect,
					this,
					IDW_AXISDRAW
				);
	if(bOk)				
		return 0;
	else
		return -1;	
}

void CDrawView::On3dAmbientlight()
{
	// TODO: Add your command handler code here
	
}

void CDrawView::OnUpdate3dAmbientlight(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrawView::On3dEyeposition()
{
	/////////////////////////////////////// Only for 3DView
//091398	if(m_nView != VIEWISO)
//091398		return;
	////////////////////////////////////////////////////////	
	if(m_pViewInfoDlg->GetSafeHwnd() ==0)// not created already
		m_pViewInfoDlg->Create();
	else
		m_pViewInfoDlg->SetActiveWindow(); 
	////////////////////////////////////////////////////////////////////////////	
	C3DMath		Math3D;
	C3DMath* 	p3DMath = &Math3D;
	///////////////////////////////// 
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision  = (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////////////  
	double dWorldBase,dMapFactor;
	dWorldBase 	= (double) pPrecision->GetWorldBase();
	dMapFactor  = pMapFactor->GetMapFactor();
	/////////////////////////////////////// change to world scaled 
	double 	dUmin,dUmax,dVmin,dVmax,dFront,dBack;
	WORLD 	CW,PRP,VRP;
	///////////////
	double r =1./(dWorldBase/dMapFactor); 
	dUmin 	= m_Umin * r; 
	dUmax 	= m_Umax * r; 
	dVmin 	= m_Vmin * r; 
	dVmax 	= m_Vmax * r; 
	dFront 	= m_dFront * r; 
	dBack 	= m_dBack  * r; 
	///////////////////////
	CW		= m_CW;
	PRP		= m_PRP;
	VRP		= m_VRP; 
	p3DMath->Scale3DPts(r,&CW);
	p3DMath->Scale3DPts(r,&PRP);
	p3DMath->Scale3DPts(r,&VRP);
	/////////////////////////// Scale Factor (World Coord)
	pObjectMgr->DStoSC(&dUmin);
	pObjectMgr->DStoSC(&dUmax);
	pObjectMgr->DStoSC(&dVmin);
	pObjectMgr->DStoSC(&dVmax);
	pObjectMgr->DStoSC(&dFront);
	pObjectMgr->DStoSC(&dBack);
	///////////////////////////
	pObjectMgr->DStoSC(&PRP.x);
	pObjectMgr->DStoSC(&PRP.y);
	pObjectMgr->DStoSC(&PRP.z);
	pObjectMgr->DStoSC(&VRP.x);
	pObjectMgr->DStoSC(&VRP.y);
	pObjectMgr->DStoSC(&VRP.z);
	pObjectMgr->DStoSC(&CW.x);
	pObjectMgr->DStoSC(&CW.y);
	pObjectMgr->DStoSC(&CW.z);
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////// Put Data
	m_pViewInfoDlg->m_dBack 	= dBack;
	m_pViewInfoDlg->m_dFront 	= dFront;
	
	m_pViewInfoDlg->m_Umax 		= dUmax;
	m_pViewInfoDlg->m_Umin 		= dUmin;
	m_pViewInfoDlg->m_Vmax 		= dVmax;
	m_pViewInfoDlg->m_Vmin 		= dVmin;
	
	m_pViewInfoDlg->m_PRP_X 	= PRP.x;
	m_pViewInfoDlg->m_PRP_Y 	= PRP.y;
	m_pViewInfoDlg->m_PRP_Z 	= PRP.z;
	
	m_pViewInfoDlg->m_VPN_X 	= m_VPN.x;
	m_pViewInfoDlg->m_VPN_Y 	= m_VPN.y;
	m_pViewInfoDlg->m_VPN_Z 	= m_VPN.z;
	
	m_pViewInfoDlg->m_VRP_X 	= VRP.x;
	m_pViewInfoDlg->m_VRP_Y 	= VRP.y;
	m_pViewInfoDlg->m_VRP_Z 	= VRP.z;
	
	m_pViewInfoDlg->m_VUP_X 	= m_VUP.x;
	m_pViewInfoDlg->m_VUP_Y 	= m_VUP.y;
	m_pViewInfoDlg->m_VUP_Z 	= m_VUP.z;
	//////////////////////////////////
	m_pViewInfoDlg->UpdateData(FALSE); // to screen
	////////////////			
}
///////////////////////////////////////////////////// OnOK/OnCancel
long CDrawView::OnGoodByeEyePos(UINT wParam, long lParam)
{
	
	m_pViewInfoDlg->DestroyWindow();
	//////////
	return 0L;
}
	 
long CDrawView::OnUpdateEyePos(UINT wParam, long lParam)
{

	m_pViewInfoDlg->UpdateData(TRUE);
	///////////////////////////////// Reset data
	C3DMath		Math3D;
	C3DMath* 	p3DMath = &Math3D;
	////////////////////////////////////////////////////////////////////////////	
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision  = (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////////////  
	double dWorldBase,dMapFactor;
	dWorldBase 	= (double) pPrecision->GetWorldBase();
	dMapFactor  = pMapFactor->GetMapFactor();
	/////////////////////////////////////// change to world scaled 
	double 	dUmin,dUmax,dVmin,dVmax,dFront,dBack;
	WORLD 	CW,PRP,VRP;
	/////////////////////////////////////// Get Data
	dBack	= m_pViewInfoDlg->m_dBack;
	dFront	= m_pViewInfoDlg->m_dFront;
	
	dUmax	= m_pViewInfoDlg->m_Umax;
	dUmin	= m_pViewInfoDlg->m_Umin;
	dVmax	= m_pViewInfoDlg->m_Vmax;
	dVmin	= m_pViewInfoDlg->m_Vmin;
	
	PRP.x	= m_pViewInfoDlg->m_PRP_X;
	PRP.y	= m_pViewInfoDlg->m_PRP_Y;
	PRP.z	= m_pViewInfoDlg->m_PRP_Z;
	
	VRP.x	= m_pViewInfoDlg->m_VRP_X;
	VRP.y	= m_pViewInfoDlg->m_VRP_Y;
	VRP.z	= m_pViewInfoDlg->m_VRP_Z;
	////////////////////////////////// strip
	pObjectMgr->SCtoDS(&PRP.x);
	pObjectMgr->SCtoDS(&PRP.y);
	pObjectMgr->SCtoDS(&PRP.z);
	pObjectMgr->SCtoDS(&VRP.x);
	pObjectMgr->SCtoDS(&VRP.y);
	pObjectMgr->SCtoDS(&VRP.z);
	///////////////////////////
	pObjectMgr->SCtoDS(&dUmin);
	pObjectMgr->SCtoDS(&dUmax);
	pObjectMgr->SCtoDS(&dVmin);
	pObjectMgr->SCtoDS(&dVmax);
	pObjectMgr->SCtoDS(&dFront);
	pObjectMgr->SCtoDS(&dBack);
	/////////////////////////////////
	double r = dWorldBase/dMapFactor;
	//////// 
	dUmin 	= dUmin * r; 
	dUmax 	= dUmax * r; 
	dVmin 	= dVmin * r; 
	dVmax 	= dVmax * r; 
	dFront 	= dFront * r; 
	dBack 	= dBack  * r; 
	///////////////////////////
	p3DMath->Scale3DPts(r,&PRP);
	p3DMath->Scale3DPts(r,&VRP);
	///////////////////////////////////////////////////////////////////////////
	Math3D.Set3DPts(&m_VRP,VRP.x,VRP.y,VRP.z);			// View Reference Point
	Math3D.Set3DPts(&m_VPN,
					m_pViewInfoDlg->m_VPN_X,
					m_pViewInfoDlg->m_VPN_Y,
					m_pViewInfoDlg->m_VPN_Z
					);			// View Plane Normal
	Math3D.Set3DPts(&m_VUP,
					m_pViewInfoDlg->m_VUP_X,
					m_pViewInfoDlg->m_VUP_Y,
					m_pViewInfoDlg->m_VUP_Z
					);			// View Up Vector
	/////////////////// View Mapping Parameters /////////////
	Math3D.Set3DPts(&m_PRP,PRP.x,PRP.y,PRP.z);			// View Reference Point
	m_Umin 		= dUmin;		// View Plane Window 
	m_Umax 		= dUmax;
	m_Vmin 		= dVmin;
	m_Vmax 		= dVmax;
	m_dFront 	= dFront;	// near clipping plane
	m_dBack 	= dBack;	// far clipping plane 
	/////////////////////////////////////
	Math3D.Set3DPts(&m_CW,
					(m_Umax+m_Umin)*.5,
					(m_Vmax+m_Vmin)*.5,
					0.0);// Window Center
    /////////////////////////////////////////////////// MATRICES
	p3DMath->GetIdentityMATRIX(&m_IdentityM);	// Identity 
    m_LocalM		= m_IdentityM;				// Local
    ////////////////////////////////////////////// Others
	UpdateAllOtherMatButLocal();
	/////////////////////////////////////////////////// View Direction
	if(m_bParallel)
	{                                  				// Needed for
		m_VDir.x = m_CW.x - m_PRP.x;          		// BackFace(3D)
		m_VDir.y = m_CW.y - m_PRP.y;         		// Culling
		m_VDir.z = m_CW.z - m_PRP.z;
	}	                     	
	else                                             	
		m_VDir = m_PRP;
	///////////////////////////////////////
	pObjectMgr->SetSceneChanged(TRUE);
	///////////////////////////////////////
	Invalidate();
	UpdateWindow();
	///////////////////////////// Axis Draw Window
	m_wndAxisDraw.Invalidate();
	m_wndAxisDraw.UpdateWindow();
	///////////////
	return 0L;
}	 
void CDrawView::OnUpdate3dEyeposition(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_pViewInfoDlg->GetSafeHwnd() == !0);
	// TODO: Add your command update UI handler code here
	
}
void CDrawView::On3dLightsource()
{
	// TODO: Add your command handler code here
	
}

void CDrawView::OnUpdate3dLightsource(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrawView::On3dProjectionParallel()
{
	m_bParallel = TRUE;	
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
	pObjectMgr->SetViewChanged(TRUE);		
	///////////////////////////////////////
	Invalidate();
	UpdateWindow();
}

void CDrawView::OnUpdate3dProjectionParallel(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bParallel);
}

void CDrawView::On3dProjectionPerspective()
{
	m_bParallel = FALSE;
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    /////////////////////////////////////////////////////////////////////
	pObjectMgr->SetViewChanged(TRUE);		
	///////////////////////////////////////
	Invalidate();
	UpdateWindow();
}

void CDrawView::OnUpdate3dProjectionPerspective(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(!m_bParallel);
}

void CDrawView::On3dRendering()
{
	// TODO: Add your command handler code here
	
}

void CDrawView::OnUpdate3dRendering(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrawView::ShowAxes()
{
	////////////////////////////////////////////////////////	
	CRect BoxRect;
	CWnd  wndTopMost;
	m_wndAxisDraw.GetWindowRect(&BoxRect);
	CRect FrameRect;
	GetClientRect(&FrameRect);
//	ClientToScreen(&FrameRect);
	/////////////////////////////////////////////////////////////// NodInBox 
	int Boxwidth  		= 120;
	int Boxheight 		= 120;
	///////////////////////////////////////
	BoxRect.bottom	= FrameRect.bottom;   //	
	BoxRect.top		= BoxRect.bottom	- Boxheight; //
	BoxRect.left	= FrameRect.left;
	BoxRect.right	= BoxRect.left		+ Boxwidth;
	//////////////////////////////
	m_wndAxisDraw.SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                       BoxRect.Height(),SWP_NOZORDER|SWP_SHOWWINDOW);
	//////////////////////////////////////////////////////////////  
}


void CDrawView::OnOptionAxison()
{
	////////////////////////////////////////////////////////	
	if(!(m_wndAxisDraw.GetStyle() & WS_VISIBLE))// not Visible
		ShowAxes();
	else
		m_wndAxisDraw.ShowWindow(SW_HIDE);
	
}

void CDrawView::OnKillFocus(CWnd* pNewWnd)
{
	CScrollView::OnKillFocus(pNewWnd);
	//////////////////////////////////////////////// do nothing	
//	if(m_wndAxisDraw.GetSafeHwnd() != 0)// visible
//		m_wndAxisDraw.DestroyWindow();
//		m_wndAxisDraw.ShowWindow(SW_HIDE);
	
}

void CDrawView::OnUpdateOptionAxison(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((m_wndAxisDraw.GetStyle() & WS_VISIBLE) != NULL);
	
}

void CDrawView::OnOptionCursor()
{
	// TODO: Add your command handler code here
	
}

void CDrawView::OnUpdateOptionCursor(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrawView::OnOptionPenchange()
{   

	CSDlgMgr* pSDlgMgr;
	/////////////////////////
	pSDlgMgr->DoModal_SpecObjs(DRPEN);
	return;
	/////////////////////////	
	
}

void CDrawView::OnUpdateOptionPenchange(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrawView::OnOptionRefresh()
{
	// TODO: Add your command handler code here
	
}

void CDrawView::OnUpdateOptionRefresh(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}
/////////////////////////////// end of module /////////////////////

BOOL CDrawView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect	r;
	CBrush	br(RGB(0,0,0));
	CBrush	*oldBr = pDC->SelectObject( &br );
	GetClientRect(&r);
	pDC->Rectangle( &r );
	pDC->SelectObject( oldBr );
	br.DeleteObject();
	
	return CScrollView::OnEraseBkgnd(pDC);
}

void CDrawView::OnSetFocus(CWnd* pOldWnd)
{
	CScrollView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	///////////////////////
//	Invalidate();			// repaint the entire scene
	/////////////
}

void CDrawView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	///////////////////////
	Invalidate();			// repaint the entire scene
	/////////////
}

void CDrawView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	///////////////////////
	Invalidate();			// repaint the entire scene
	/////////////
}

void CDrawView::OnNoshowElements() 
{
#ifdef _DEBUG
		////////////////////////////////////////////////////
		CString strRes;
		strRes.LoadString(IDS_CHECK_RESOURCE);
		TRACE("resource string = %s\n", (const char*) strRes);
#endif
	////////////////////////////////////////////////////////	
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(AfxGetInstanceHandle()); // EXE's instance handle 
	/////////////////////////////////////////	 
	CDlg_NoELem Dlg_NoEL;
	////////////////////////////////////////// init
	Dlg_NoEL.m_bAll		= m_bNoSoEL[ 0];
	Dlg_NoEL.m_bNone	= m_bNoSoEL[ 1];
	//
	Dlg_NoEL.m_bBallJt	= m_bNoSoEL[11];
	///////////
	Dlg_NoEL.m_bTruss	= m_bNoSoEL[20];
	Dlg_NoEL.m_bBeam	= m_bNoSoEL[21];
	Dlg_NoEL.m_bPipe	= m_bNoSoEL[22];
	Dlg_NoEL.m_bElbow	= m_bNoSoEL[23];
	///////////
	Dlg_NoEL.m_bTr_3	= m_bNoSoEL[30];
	Dlg_NoEL.m_bTr_6	= m_bNoSoEL[31];
	Dlg_NoEL.m_bTr_9	= m_bNoSoEL[32];
	Dlg_NoEL.m_bTr_10	= m_bNoSoEL[33];
	Dlg_NoEL.m_bQu_4	= m_bNoSoEL[34];
	Dlg_NoEL.m_bQu_8	= m_bNoSoEL[35];
	Dlg_NoEL.m_bQu_9	= m_bNoSoEL[36];
	Dlg_NoEL.m_bQu_12	= m_bNoSoEL[37];
	Dlg_NoEL.m_bQu_16	= m_bNoSoEL[38];
	///////////
	Dlg_NoEL.m_bTetra	= m_bNoSoEL[60];
	Dlg_NoEL.m_bPenta	= m_bNoSoEL[70];
	Dlg_NoEL.m_bHexa	= m_bNoSoEL[80];
	////////////////////////////////////////// Do it
	if(Dlg_NoEL.DoModal() == IDOK)
	{
		m_bNoSoEL[ 0] = Dlg_NoEL.m_bAll;
		m_bNoSoEL[ 1] = Dlg_NoEL.m_bNone;
		//
		m_bNoSoEL[11] = Dlg_NoEL.m_bBallJt;
		///////////
		m_bNoSoEL[20] = Dlg_NoEL.m_bTruss;
		m_bNoSoEL[21] = Dlg_NoEL.m_bBeam;
		m_bNoSoEL[22] = Dlg_NoEL.m_bPipe;
		m_bNoSoEL[23] = Dlg_NoEL.m_bElbow;
		///////////
		m_bNoSoEL[30] = Dlg_NoEL.m_bTr_3;
		m_bNoSoEL[31] = Dlg_NoEL.m_bTr_6;
		m_bNoSoEL[32] = Dlg_NoEL.m_bTr_9;
		m_bNoSoEL[33] = Dlg_NoEL.m_bTr_10;
		m_bNoSoEL[34] = Dlg_NoEL.m_bQu_4;
		m_bNoSoEL[35] = Dlg_NoEL.m_bQu_8;
		m_bNoSoEL[36] = Dlg_NoEL.m_bQu_9;
		m_bNoSoEL[37] = Dlg_NoEL.m_bQu_12;
		m_bNoSoEL[38] = Dlg_NoEL.m_bQu_16;
		///////////
		m_bNoSoEL[60] = Dlg_NoEL.m_bTetra;
		m_bNoSoEL[70] = Dlg_NoEL.m_bPenta;
		m_bNoSoEL[80] = Dlg_NoEL.m_bHexa;
	}
	////////////////////////////////////////////////////
	SetRendChanged(TRUE);
	GetDocument()->UpdateAllViews(NULL);
	////////////////////////////////////
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	//////////////////////
#ifdef _DEBUG
		////////////////////////////////////////////////////
		strRes.LoadString(IDS_CHECK_RESOURCE);
		TRACE("resource string = %s\n", (const char*) strRes); 
#endif
}

void CDrawView::OnUpdateNoshowElements(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDrawView::OnNoshowLabelElements() 
{
#ifdef _DEBUG
		////////////////////////////////////////////////////
		CString strRes;
		strRes.LoadString(IDS_CHECK_RESOURCE);
		TRACE("resource string = %s\n", (const char*) strRes);
#endif
	////////////////////////////////////////////////////////	
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(AfxGetInstanceHandle()); // EXE's instance handle 
	/////////////////////////////////////////	 
	CDlg_NoLabELem Dlg_NoEL;
	////////////////////////////////////////// init
	Dlg_NoEL.m_bAll		= m_bNoSoLabEL[ 0];
	Dlg_NoEL.m_bNone	= m_bNoSoLabEL[ 1];
	//
	Dlg_NoEL.m_bBallJt	= m_bNoSoLabEL[11];
	///////////
	Dlg_NoEL.m_bTruss	= m_bNoSoLabEL[20];
	Dlg_NoEL.m_bBeam	= m_bNoSoLabEL[21];
	Dlg_NoEL.m_bPipe	= m_bNoSoLabEL[22];
	Dlg_NoEL.m_bElbow	= m_bNoSoLabEL[23];
	///////////
	Dlg_NoEL.m_bTr_3	= m_bNoSoLabEL[30];
	Dlg_NoEL.m_bTr_6	= m_bNoSoLabEL[31];
	Dlg_NoEL.m_bTr_9	= m_bNoSoLabEL[32];
	Dlg_NoEL.m_bTr_10	= m_bNoSoLabEL[33];
	Dlg_NoEL.m_bQu_4	= m_bNoSoLabEL[34];
	Dlg_NoEL.m_bQu_8	= m_bNoSoLabEL[35];
	Dlg_NoEL.m_bQu_9	= m_bNoSoLabEL[36];
	Dlg_NoEL.m_bQu_12	= m_bNoSoLabEL[37];
	Dlg_NoEL.m_bQu_16	= m_bNoSoLabEL[38];
	///////////
	Dlg_NoEL.m_bTetra	= m_bNoSoLabEL[60];
	Dlg_NoEL.m_bPenta	= m_bNoSoLabEL[70];
	Dlg_NoEL.m_bHexa	= m_bNoSoLabEL[80];
	////////////////////////////////////////// Do it
	if(Dlg_NoEL.DoModal() == IDOK)
	{
		m_bNoSoLabEL[ 0] = Dlg_NoEL.m_bAll;
		m_bNoSoLabEL[ 1] = Dlg_NoEL.m_bNone;
		//
		m_bNoSoLabEL[11] = Dlg_NoEL.m_bBallJt;
		///////////
		m_bNoSoLabEL[20] = Dlg_NoEL.m_bTruss;
		m_bNoSoLabEL[21] = Dlg_NoEL.m_bBeam;
		m_bNoSoLabEL[22] = Dlg_NoEL.m_bPipe;
		m_bNoSoLabEL[23] = Dlg_NoEL.m_bElbow;
		///////////
		m_bNoSoLabEL[30] = Dlg_NoEL.m_bTr_3;
		m_bNoSoLabEL[31] = Dlg_NoEL.m_bTr_6;
		m_bNoSoLabEL[32] = Dlg_NoEL.m_bTr_9;
		m_bNoSoLabEL[33] = Dlg_NoEL.m_bTr_10;
		m_bNoSoLabEL[34] = Dlg_NoEL.m_bQu_4;
		m_bNoSoLabEL[35] = Dlg_NoEL.m_bQu_8;
		m_bNoSoLabEL[36] = Dlg_NoEL.m_bQu_9;
		m_bNoSoLabEL[37] = Dlg_NoEL.m_bQu_12;
		m_bNoSoLabEL[38] = Dlg_NoEL.m_bQu_16;
		///////////
		m_bNoSoLabEL[60] = Dlg_NoEL.m_bTetra;
		m_bNoSoLabEL[70] = Dlg_NoEL.m_bPenta;
		m_bNoSoLabEL[80] = Dlg_NoEL.m_bHexa;
	}
	////////////////////////////////////////////////////
	SetRendChanged(TRUE);
	GetDocument()->UpdateAllViews(NULL);
	////////////////////////////////////
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
	//////////////////////
#ifdef _DEBUG
		////////////////////////////////////////////////////
		strRes.LoadString(IDS_CHECK_RESOURCE);
		TRACE("resource string = %s\n", (const char*) strRes); 
#endif
}

void CDrawView::OnNoShowCNLabel()
{
	m_bNS_CNLabel = !m_bNS_CNLabel;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoShowCNLabel(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_CNLabel);
}

void CDrawView::OnNoShowCNodes()
{
	m_bNS_CNode = !m_bNS_CNode;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoShowCNodes(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_CNode);
}

void CDrawView::OnNoShowNLabel()
{
	m_bNS_NLabel = !m_bNS_NLabel;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoShowNLabel(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_NLabel);
}

void CDrawView::OnNoShowNodes()
{
	m_bNS_Node = !m_bNS_Node;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoShowNodes(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_Node);
}

void CDrawView::OnNoShowCShape()
{
	m_bNS_CShape = !m_bNS_CShape;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnNoshowMnlabel() 
{
	m_bNS_MNLabel = !m_bNS_MNLabel;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowMnlabel(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_MNLabel);
}

void CDrawView::OnNoshowMnodes() 
{
	m_bNS_MNode = !m_bNS_MNode;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowMnodes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_MNode);
}

void CDrawView::OnUpdateNoShowCShape(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_CShape);
}

void CDrawView::On3dFsPainter()
{
	if(m_Rendition == !FS_PAINTER)
	{
		m_Rendition = FS_PAINTER;
		/////////////////////////
		SetRendChanged(TRUE);
		GetDocument()->UpdateAllViews(NULL);
	}	
}

void CDrawView::OnUpdate3dFsPainter(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Rendition == FS_PAINTER);
}

void CDrawView::On3dFsZbuffer()
{
	if(m_Rendition == !FS_ZBUFFER)
	{
		m_Rendition = FS_ZBUFFER;
		/////////////////////////
		SetRendChanged(TRUE);
		GetDocument()->UpdateAllViews(NULL);
	}	
}

void CDrawView::OnUpdate3dFsZbuffer(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Rendition == FS_ZBUFFER);
} 

void CDrawView::On3dCulling3D() 
{
	m_bCulling3D = !m_bCulling3D;
	/////////////////////////////
	SetRendChanged(TRUE);
	GetDocument()->UpdateAllViews(NULL);
	
}

void CDrawView::OnUpdate3dCulling3D(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bCulling3D);
}

void CDrawView::On3dWfHidden()
{
	if(m_Rendition == !WF_HIDDEN)
	{
		m_Rendition = WF_HIDDEN;
		SetRendChanged(TRUE);
		GetDocument()->UpdateAllViews(NULL);
	}	
}

void CDrawView::OnUpdate3dWfHidden(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Rendition == WF_HIDDEN);
}

void CDrawView::On3dWfPure()
{
	if(m_Rendition == !WF_PURE)
	{
		m_Rendition = WF_PURE;
		SetRendChanged(TRUE);
		GetDocument()->UpdateAllViews(NULL);
	}		
}

void CDrawView::OnUpdate3dWfPure(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Rendition == WF_PURE);
}

void CDrawView::On3dZbGouraud()
{
	if(m_Rendition == !ZB_GOURAUD)
	{
		m_Rendition = ZB_GOURAUD;
		SetRendChanged(TRUE);
		GetDocument()->UpdateAllViews(NULL);
	}		
}

void CDrawView::OnUpdate3dZbGouraud(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Rendition == ZB_GOURAUD);
}

void CDrawView::On3dZbPhong()
{
	if(m_Rendition == !ZB_PHONG)
	{
		m_Rendition = ZB_PHONG;
		SetRendChanged(TRUE);
		GetDocument()->UpdateAllViews(NULL);
	}		
}

void CDrawView::OnUpdate3dZbPhong(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_Rendition == ZB_PHONG);
}

void CDrawView::On3dShrinkOn() 
{
	m_bShrinkOn = !m_bShrinkOn;
	///////////////////////////
	if(m_bShrinkOn)
	{
#ifdef _DEBUG
		////////////////////////////////////////////////////
		CString strRes;
		strRes.LoadString(IDS_CHECK_RESOURCE);
		TRACE("resource string = %s\n", (const char*) strRes);
#endif
		////////////////////////////////////////////////////////	
		HINSTANCE hInstResourceClient = AfxGetResourceHandle();
		AfxSetResourceHandle(AfxGetInstanceHandle()); // EXE's instance handle 
		/////////////////////////////////////////	 
		CDlg_Shrink Shrink;
		if(Shrink.DoModal() == IDOK)
			m_dShrink = Shrink.m_dShrink;
		else
		{
			m_bShrinkOn = FALSE;
			m_dShrink	= 1.0;
		}
		////////////////////////////////////////////////////
		AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
		////////////////////
#ifdef _DEBUG
		////////////////////////////////////////////////////
		strRes.LoadString(IDS_CHECK_RESOURCE);
		TRACE("resource string = %s\n", (const char*) strRes); 
#endif
	}
	else
		m_dShrink	= 1.0;
	//////////////////////
	SetRendChanged(TRUE);
	GetDocument()->UpdateAllViews(NULL);
	////////////////////////////////////
}

void CDrawView::OnUpdate3dShrinkOn(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bShrinkOn);
}

void CDrawView::OnNoshowCentroid()
{
	m_bNS_Centroid	= !m_bNS_Centroid;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
	
}

void CDrawView::OnUpdateNoshowCentroid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_Centroid);
}

void CDrawView::OnNoshowDCurve()
{
	m_bNS_D_Curve	= !m_bNS_D_Curve;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowDCurve(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_D_Curve);
}

void CDrawView::OnNoshowDObject()
{
	m_bNS_D_Object	= !m_bNS_D_Object;			
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowDObject(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_D_Object);
}

void CDrawView::OnNoshowDPatch()
{
	m_bNS_D_Patch	= !m_bNS_D_Patch;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowDPatch(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_D_Patch);
}

void CDrawView::OnNoshowDSolid()
{
	m_bNS_D_Solid	= !m_bNS_D_Solid;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowDSolid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_D_Solid);
}

void CDrawView::OnNoshowDProfile_C()
{
	m_bNS_D_Profile_C	= !m_bNS_D_Profile_C;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowDProfile_C(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_D_Profile_C);
}

void CDrawView::OnNoshowDProfile_P()
{
	m_bNS_D_Profile_P	= !m_bNS_D_Profile_P;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowDProfile_P(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_D_Profile_P);
}

void CDrawView::OnNoshowDProfile_S()
{
	m_bNS_D_Profile_S	= !m_bNS_D_Profile_S;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowDProfile_S(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_D_Profile_S);
}

void CDrawView::OnNoshowNormals()
{
	m_bNS_Normal	= !m_bNS_Normal;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowNormals(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_Normal);
}

void CDrawView::OnNoshowPCurve()
{
	m_bNS_P_Curve	= !m_bNS_P_Curve;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowPCurve(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_P_Curve);
}

void CDrawView::OnNoshowPObject()
{
	m_bNS_P_Object	= !m_bNS_P_Object;			
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowPObject(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_P_Object);
}

void CDrawView::OnNoshowPPatch()
{
	m_bNS_P_Patch	= !m_bNS_P_Patch;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowPPatch(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_P_Patch);
}

void CDrawView::OnNoshowPSolid()
{
	m_bNS_P_Solid	= !m_bNS_P_Solid;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowPSolid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_P_Solid);
}

void CDrawView::OnNoshowPProfile_C()
{
	m_bNS_P_Profile_C	= !m_bNS_P_Profile_C;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowPProfile_C(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_P_Profile_C);
}

void CDrawView::OnNoshowPProfile_P()
{
	m_bNS_P_Profile_P	= !m_bNS_P_Profile_P;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowPProfile_P(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_P_Profile_P);
}

void CDrawView::OnNoshowPProfile_S()
{
	m_bNS_P_Profile_S	= !m_bNS_P_Profile_S;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowPProfile_S(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_P_Profile_S);
}

void CDrawView::OnNoshowVcBcp()
{
	m_bNS_Back		= !m_bNS_Back;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcBcp(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_Back);
}

void CDrawView::OnNoshowVcCvv()
{
	m_bNS_CVV		= !m_bNS_CVV;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcCvv(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_CVV);
}

void CDrawView::OnNoshowVcFcp()
{
	m_bNS_Front		= !m_bNS_Front;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcFcp(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_Front);
}

void CDrawView::OnNoshowVcPlane()
{
	m_bNS_VPlane	= !m_bNS_VPlane;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcPlane(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_VPlane);
}

void CDrawView::OnNoshowVcPrp()
{
	m_bNS_PRP		= !m_bNS_PRP;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcPrp(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_PRP);
}

void CDrawView::OnNoshowVcVcs()
{
	m_bNS_VRC		= !m_bNS_VRC;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcVcs(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_VRC);
}

void CDrawView::OnNoshowVcVdir()
{
	m_bNS_VDIR		= !m_bNS_VDIR;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcVdir(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_VDIR);
}

void CDrawView::OnNoshowVcVpn()
{
	m_bNS_VPN		= !m_bNS_VPN;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcVpn(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_VPN);
}

void CDrawView::OnNoshowVcVrp()
{
	m_bNS_VRP		= !m_bNS_VRP;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcVrp(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_VRP);
}

void CDrawView::OnNoshowVcVup()
{
	m_bNS_VUP		= !m_bNS_VUP;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcVup(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_VUP);
}

void CDrawView::OnNoshowVcVv()
{
	m_bNS_VV		= !m_bNS_VV;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcVv(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_VV);
}

void CDrawView::OnNoshowVcWc()
{
	m_bNS_CW		= !m_bNS_CW;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcWc(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_CW);
}

void CDrawView::OnNoshowVcWcs()
{
	m_bNS_WC		= !m_bNS_WC;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowVcWcs(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_WC);
}

void CDrawView::SetSceneChangedOnNoShow()
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	pObjectMgr->SetSceneChanged(TRUE);
	pDoc->UpdateAllViews(NULL);
	//////////////////////////
}
/////////////////////////////////////////////////////////////////////
void CDrawView::OnModeDesign()
{
	if(m_GenMode == REVERSE)
		m_GenMode = FORWARD;
}

void CDrawView::OnUpdateModeDesign(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_GenMode == FORWARD);
}

void CDrawView::OnModeInterpolate()
{
	if(m_GenMode == FORWARD)
		m_GenMode = REVERSE;
}

void CDrawView::OnUpdateModeInterpolate(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_GenMode == REVERSE);
}
//////////////////////////////////////////////////////////////////////
CDListMgr* CDrawView::GetList(UINT nType)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* 	pDListMgr 	= pObjectMgr->GetObjectList(nType);
	/////////////
	return pDListMgr;
}

void CDrawView::ShowCountBox(LPCTSTR string,int nCount)
{
	/////////////////////////////////////////////////////////////
	CString* str = new CString;
	char* buf = str->GetBuffer(BUFF_SIZE);
	////////////////////
	int j;
	j  = sprintf( buf,"***** DataBase Info *****\n\n");
	j += sprintf( buf + j, "%s = %d\n",string,nCount);
	////
	AfxMessageBox(*str,MB_ICONINFORMATION);
	///////////////////
}

void CDrawView::OnSummaryCurveDirty() 
{
	CDListMgr* 	pDListMgr 	= GetList(CURVE);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == CURVE)
			if(pObject->IsDirty())
				nCount++;
   	}
	////////////////////
	ShowCountBox("No. of Dirty Curves",nCount);
	///////////////
}

void CDrawView::OnSummaryCurvePosted() 
{
	CDListMgr* 	pDListMgr 	= GetList(CURVE);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == CURVE)
			if(pObject->IsPosted())
				nCount++;
   	}
	////////////////////
	ShowCountBox("No. of Posted Curves",nCount);
	///////////////
}

void CDrawView::OnSummaryElements() 
{
	// TODO: Add your command handler code here
	
}

void CDrawView::OnSummaryNodeAlltypes() 
{
	CDListMgr* 	pDListMgr 	= GetList(NODE);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == NODE)
			nCount++;
   	}
	////////////////////
	ShowCountBox("No. of Total Nodes",nCount);
	///////////////
}

void CDrawView::OnSummaryNodeControl() 
{
	CDListMgr* 	pDListMgr 	= GetList(NODE);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == NODE)
		{
			CDrNode* pNode = (CDrNode*)pObject;
			if(pNode->IsControlNode())
				nCount++;
		}
   	}
	////////////////////
	ShowCountBox("No. of Control Nodes",nCount);
	///////////////
}

void CDrawView::OnSummaryNodeMesh() 
{
	CDListMgr* 	pDListMgr 	= GetList(NODE);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == NODE)
		{
			CDrNode* pNode = (CDrNode*)pObject;
			if(pNode->IsMeshNode())
				nCount++;
		}
   	}
	////////////////////
	ShowCountBox("No. of Mesh Nodes",nCount);
	///////////////
}

void CDrawView::OnSummaryObject() 
{
	// TODO: Add your command handler code here
	
}

void CDrawView::OnSummaryPatchDirty() 
{
	CDListMgr* 	pDListMgr 	= GetList(PATCH);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == PATCH)
			if(pObject->IsDirty())
				nCount++;
   	}
	////////////////////
	ShowCountBox("No. of Dirty Patches",nCount);
	///////////////
}

void CDrawView::OnSummaryPatchPosted() 
{
	CDListMgr* 	pDListMgr 	= GetList(PATCH);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == PATCH)
			if(pObject->IsPosted())
				nCount++;
   	}
	////////////////////
	ShowCountBox("No. of Posted Patches",nCount);
	///////////////
}

void CDrawView::OnSummarySolidDirty() 
{
	CDListMgr* 	pDListMgr 	= GetList(SOLID);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == SOLID)
			if(pObject->IsDirty())
				nCount++;
   	}
	////////////////////
	ShowCountBox("No. of Dirty Solids",nCount);
	///////////////
}

void CDrawView::OnSummarySolidPosted() 
{
	CDListMgr* 	pDListMgr 	= GetList(SOLID);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == SOLID)
			if(pObject->IsPosted())
				nCount++;
   	}
	////////////////////
	ShowCountBox("No. of Posted Solids",nCount);
	///////////////
}
/////////////////////////////////////////////////////////////////////// Support
void CDrawView::OnNoshowLinearsupportRigid() 
{
	m_bNS_RIGID = !m_bNS_RIGID;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowLinearsupportRigid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_RIGID);
}

void CDrawView::OnNoshowLinearsupportSnubber() 
{
	m_bNS_Lin_Snubber = !m_bNS_Lin_Snubber;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowLinearsupportSnubber(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_Lin_Snubber);
}

void CDrawView::OnNoshowLinearsupportSpring() 
{
	m_bNS_Lin_Spring = !m_bNS_Lin_Spring;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowLinearsupportSpring(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_Lin_Spring);
}

void CDrawView::OnSummaryLinearsupportRigid() 
{
	CDListMgr* 	pDListMgr 	= GetList(LIN_SUPPORT);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrLinSup* pSupp = (CDrLinSup*)pDListMgr->GetNextObject( pos);
		if((pSupp->GetSuppCard())->SuppProc == SUP_RIGID)
				nCount++;
   	}
	////////////////////
	ShowCountBox("No. of Rigid Support",nCount);
	///////////////
}

void CDrawView::OnSummaryLinearsupportSnubber() 
{
	CDListMgr* 	pDListMgr 	= GetList(LIN_SUPPORT);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrLinSup* pSupp = (CDrLinSup*)pDListMgr->GetNextObject( pos);
		if((pSupp->GetSuppCard())->SuppProc == SUP_LINSNU)
		{
			for(int i=0;i<6;i++)
			{
				if(	(pSupp->GetSuppCard())->kode[i] == 1 )
					nCount++;
			}
		}
   	}
	////////////////////
	ShowCountBox("No. of Linear Snubbers",nCount);
	///////////////
}

void CDrawView::OnSummaryLinearsupportSpring() 
{
	CDListMgr* 	pDListMgr 	= GetList(LIN_SUPPORT);
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrLinSup* pSupp = (CDrLinSup*)pDListMgr->GetNextObject( pos);
		if((pSupp->GetSuppCard())->SuppProc == SUP_LINSPR)
		{
			for(int i=0;i<6;i++)
			{
				if(	(pSupp->GetSuppCard())->kode[i] == 1 )
					nCount++;
			}
		}
   	}
	////////////////////
	ShowCountBox("No. of Linear Springs",nCount);
	///////////////
}
/////////////////////////////////////////////////////////////////////// StaticLoads
void CDrawView::OnNoshowStaticForce() 
{
	m_bNS_Force = !m_bNS_Force;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowStaticForce(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_Force);
}

void CDrawView::OnNoshowStaticDisplace() 
{
	m_bNS_Displace = !m_bNS_Displace;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowStaticDisplace(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_Displace);
}

void CDrawView::OnNoshowStaticPressure() 
{
	m_bNS_Pressure = !m_bNS_Pressure;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowStaticPressure(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_Pressure);
}

void CDrawView::OnNoshowStaticThermal() 
{
	m_bNS_Thermal = !m_bNS_Thermal;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowStaticThermal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_Thermal);
}

void CDrawView::OnNoshowStaticLumpWt() 
{
	m_bNS_LumpWt = !m_bNS_LumpWt;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CDrawView::OnUpdateNoshowStaticLumpWt(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LumpWt);
}

void CDrawView::OnSummaryStaticForce() 
{
	CDListMgr* 	pDListMgr 	= GetList(STATICLOAD);
	CStringList strList;
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrStatic* pF_M = (CDrStatic*)pDListMgr->GetNextObject( pos);
		if(pF_M->GetStaLCard()->StaLProc != STL_FORCE)
			continue;
		////////////
		CString LoadID = pF_M->GetStaLCard()->load_id;
		///////////////////////////////////
		if(!strList.Find(LoadID) ) // not in List yet
		{
			nCount++;
			strList.AddTail(LoadID);
		}
   	}
	////////////////////
	CString str;
	char* pBuf = str.GetBuffer(120);
	sprintf(pBuf,"No. of Different Nodal Force LoadIDs = %d\nNo. of Nodes with Imposed Force = ",
					nCount);
	ShowCountBox(str,pDListMgr->GetCount());
	str.ReleaseBuffer();
	///////////////
}

void CDrawView::OnSummaryStaticDisplace() 
{
	CDListMgr* 	pDListMgr 	= GetList(STATICLOAD);
	CStringList strList;
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrStatic* pD_R = (CDrStatic*)pDListMgr->GetNextObject( pos);
		CString LoadID = pD_R->GetStaLCard()->load_id;
		///////////////////////////////////
		if(!strList.Find(LoadID) ) // not in List yet
		{
			nCount++;
			strList.AddTail(LoadID);
		}
   	}
	////////////////////
	CString str;
	char* pBuf = str.GetBuffer(120);
	sprintf(pBuf,"No. of Different Support Displacement LoadIDs = \nNo. of Supports with Imposed Displacements = ",
					nCount);
	ShowCountBox(str,pDListMgr->GetCount());
	str.ReleaseBuffer();
	///////////////
}

void CDrawView::OnSummaryStaticPressure() 
{
	CDListMgr* 	pDListMgr 	= GetList(STATICLOAD);
	CStringList strList;
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrStatic* pPrs = (CDrStatic*)pDListMgr->GetNextObject( pos);
		CString LoadID = pPrs->GetStaLCard()->load_id;
		///////////////////////////////////
		if(!strList.Find(LoadID) ) // not in List yet
				nCount++;
   	}
	////////////////////
	CString str;
	char* pBuf = str.GetBuffer(120);
	sprintf(pBuf,"No. of Different Pressure LoadIDs = \nNo. of Lines with Imposed Pressure = ",
					nCount);
	ShowCountBox(str,pDListMgr->GetCount());
	str.ReleaseBuffer();
	///////////////
}

void CDrawView::OnSummaryStaticThermal() 
{
	CDListMgr* 	pDListMgr 	= GetList(STATICLOAD);
	CStringList strList;
	/////////////
	int nCount=0;
    //////////////////////////////////////////////////////////	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		CDrStatic* pThr = (CDrStatic*)pDListMgr->GetNextObject( pos);
		CString LoadID = pThr->GetStaLCard()->load_id;
		///////////////////////////////////
		if(!strList.Find(LoadID) ) // not in List yet
				nCount++;
   	}
	////////////////////
	CString str;
	char* pBuf = str.GetBuffer(120);
	sprintf(pBuf,"No. of Different Thermal LoadIDs = \nNo. of Lines with Imposed Thermal Loads = ",
					nCount);
	ShowCountBox(str,pDListMgr->GetCount());
	str.ReleaseBuffer();
	///////////////
}

void CDrawView::OnSummaryStaticLumpWt() 
{
	CDListMgr* 	pDListMgr 	= GetList(STATICLOAD);
	////////////////////
	ShowCountBox("No. of Nodal LumpWts = ",pDListMgr->GetCount());
	///////////////
}

/////////////////////////////////////////////////////////////// Mouse Handler
void CDrawView::MouseMove(UINT nFlags, CPoint point)
{
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	////////////////////////////////////////////////////////////// Reset BackColor of StatControl
	if( pWnd->GetLastStatCntlHit() )
	{
		(pWnd->GetLastStatCntlHit())->Invalidate();
		(pWnd->GetLastStatCntlHit())->UpdateWindow();
		//////////////////////////
		pWnd->SetLastStatCntlHit(NULL);
	}
	//////////////////////////////////////////////////////////////
	switch(pWnd->GetCurrentOperID())
	{
		case COP_CREATE:
		///////////////////////////
			m_DVM_Genr.MouseMove(this, nFlags, point);
			break;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		///////////////////////////
			if(bMeshMode)
				m_DVM_CreM.MouseMove(this, nFlags, point);
			else
				m_DVM_CreO.MouseMove(this, nFlags, point);
			break;

		case GOP_EDIT:
		case GOP_MOVE:
		///////////////////////////
			if(bMeshMode)
				m_DVM_Mdit.MouseMove(this, nFlags, point);
			else
				m_DVM_Edit.MouseMove(this, nFlags, point);
			break;

		case GOP_DELETE:
		///////////////////////////
			m_DVM_Del.MouseMove(this,nFlags,point);
			break;

		case GOP_POST:
		///////////////////////////
			m_DVM_Post.MouseMove(this,nFlags,point);
			break;
	}
}

void CDrawView::LButtonDown(UINT nFlags, CPoint point)
{
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	//////////////////////////////////////////////////////////////
	switch(pWnd->GetCurrentOperID())
	{
		case COP_CREATE:
		///////////////////////////
			m_DVM_Genr.LButtonDown(this,nFlags,point);
			break;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		///////////////////////////
			if(bMeshMode)
				m_DVM_CreM.LButtonDown(this, nFlags, point);
			else
				m_DVM_CreO.LButtonDown(this, nFlags, point);
			break;

		case GOP_EDIT:
		case GOP_MOVE:
		///////////////////////////
			if(bMeshMode)
				m_DVM_Mdit.LButtonDown(this,nFlags,point);
			else
				m_DVM_Edit.LButtonDown(this,nFlags,point);
			break;

		case GOP_DELETE:
		///////////////////////////
			m_DVM_Del.LButtonDown(this,nFlags,point);
			break;

		case GOP_POST:
		///////////////////////////
			m_DVM_Post.LButtonDown(this,nFlags,point);
			break;
	}
}

void CDrawView::LButtonUp(UINT nFlags, CPoint point)
{
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	//////////////////////////////////////////////////////////////
	switch(pWnd->GetCurrentOperID())
	{
		case COP_CREATE:
		///////////////////////////
			m_DVM_Genr.LButtonUp(this,nFlags,point);
			break;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		///////////////////////////
			if(bMeshMode)
				m_DVM_CreM.LButtonUp(this, nFlags, point);
			else
				m_DVM_CreO.LButtonUp(this, nFlags, point);
			break;

		case GOP_EDIT:
		case GOP_MOVE:
		///////////////////////////
			if(bMeshMode)
				m_DVM_Mdit.LButtonUp(this,nFlags,point);
			else
				m_DVM_Edit.LButtonUp(this,nFlags,point);
			break;

		case GOP_DELETE:
		///////////////////////////
			m_DVM_Del.LButtonUp(this,nFlags,point);
			break;

		case GOP_POST:
		///////////////////////////
			m_DVM_Post.LButtonUp(this,nFlags,point);
			break;
	}
}

void CDrawView::RButtonDown(UINT nFlags, CPoint point)
{ 
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	//////////////////////////////////////////////////////////////
	switch(pWnd->GetCurrentOperID())
	{
		case COP_CREATE:
		///////////////////////////
			m_DVM_Genr.RButtonDown(this,nFlags,point);
			break;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		///////////////////////////
			if(bMeshMode)
				m_DVM_CreM.RButtonDown(this, nFlags, point);
			else
				m_DVM_CreO.RButtonDown(this, nFlags, point);
			break;

		case GOP_EDIT:
		case GOP_MOVE:
		///////////////////////////
			if(bMeshMode)
				m_DVM_Mdit.RButtonDown(this,nFlags,point);
			else
				m_DVM_Edit.RButtonDown(this,nFlags,point);
			break;

		case GOP_DELETE:
		///////////////////////////
			m_DVM_Del.RButtonDown(this,nFlags,point);
			break;

		case GOP_POST:
		///////////////////////////
			m_DVM_Post.RButtonDown(this,nFlags,point);
			break;
	}
}
		
void CDrawView::RButtonUp(UINT nFlags,CPoint point)
{
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	BOOL bMeshMode = pWnd->IsMeshMode();	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	//////////////////////////////////////////////////////////////
	switch(pWnd->GetCurrentOperID())
	{
		case COP_CREATE:
		///////////////////////////
			m_DVM_Genr.RButtonUp(this,nFlags,point);
			break;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		///////////////////////////
			if(bMeshMode)
				m_DVM_CreM.RButtonUp(this, nFlags, point);
			else
				m_DVM_CreO.RButtonUp(this, nFlags, point);
			break;

		case GOP_EDIT:
		case GOP_MOVE:
		///////////////////////////
			if(bMeshMode)
				m_DVM_Mdit.RButtonUp(this,nFlags,point);
			else
				m_DVM_Edit.RButtonUp(this,nFlags,point);
			break;

		case GOP_DELETE:
		///////////////////////////
			m_DVM_Del.RButtonUp(this,nFlags,point);
			break;

		case GOP_POST:
		///////////////////////////
			m_DVM_Post.RButtonUp(this,nFlags,point);
			break;
	}
}

void CDrawView::OnViewModeGenerator() 
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_bViewGene = TRUE;
	m_bViewMesh = FALSE;
	////////////////////
	pWnd->SetMeshMode(m_bViewMesh); // Edit/Creop etc. depends on this
	pWnd->OnModeChange();
	pWnd->SetCurrentModeID(MO_GENERATOR);	// ALLMODES in Def_Mo.h
	CString str = "GENERATION Mode";
	pWnd->UpdateModeStat(str);
	//////////////////////////
	Invalidate();
	UpdateWindow();
	///////////////
}

void CDrawView::OnUpdateViewModeGenerator(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bViewGene);
}

void CDrawView::OnViewModeMesh() 
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_bViewGene = FALSE;
	m_bViewMesh = TRUE;
	////////////////////
	pWnd->SetMeshMode(m_bViewMesh); // Edit/Creop etc. depends on this
	pWnd->OnModeChange();
	pWnd->SetCurrentModeID(MO_MESH);	// ALLMODES in Def_Mo.h
	CString str = "MESH Mode";
	pWnd->UpdateModeStat(str);
	//////////////////////////
	Invalidate();
	UpdateWindow();
	///////////////
}

void CDrawView::OnUpdateViewModeMesh(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bViewMesh);
}

void CDrawView::OnNoshowlabelsDCurve() 
{
	m_bNS_LabDirty[0] = !m_bNS_LabDirty[0];
}

void CDrawView::OnUpdateNoshowlabelsDCurve(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabDirty[0]);
}

void CDrawView::OnNoshowlabelsDObject() 
{
	m_bNS_LabDirty[6] = !m_bNS_LabDirty[6];
}

void CDrawView::OnUpdateNoshowlabelsDObject(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabDirty[6]);
}

void CDrawView::OnNoshowlabelsDPatch() 
{
	m_bNS_LabDirty[2] = !m_bNS_LabDirty[2];
}

void CDrawView::OnUpdateNoshowlabelsDPatch(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabDirty[2]);
}

void CDrawView::OnNoshowlabelsDProfileS() 
{
	m_bNS_LabDirty[5] = !m_bNS_LabDirty[5];
}

void CDrawView::OnUpdateNoshowlabelsDProfileS(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabDirty[5]);
}

void CDrawView::OnNoshowlabelsDSolid() 
{
	m_bNS_LabDirty[4] = !m_bNS_LabDirty[4];
}

void CDrawView::OnUpdateNoshowlabelsDSolid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabDirty[4]);
}

void CDrawView::OnNoshowlabelsLinearsupportRigid() 
{
	m_bNS_LabSupp[0] = !m_bNS_LabSupp[0];
}

void CDrawView::OnUpdateNoshowlabelsLinearsupportRigid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabSupp[0]);
}

void CDrawView::OnNoshowlabelsLinearsupportSpring() 
{
	m_bNS_LabSupp[1] = !m_bNS_LabSupp[1];
}

void CDrawView::OnUpdateNoshowlabelsLinearsupportSpring(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabSupp[1]);
}

void CDrawView::OnNoshowlabelsPCurve() 
{
	m_bNS_LabPosted[0] = !m_bNS_LabPosted[0];
}

void CDrawView::OnUpdateNoshowlabelsPCurve(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabPosted[0]);
}

void CDrawView::OnNoshowlabelsPObject() 
{
	m_bNS_LabPosted[6] = !m_bNS_LabPosted[6];
}

void CDrawView::OnUpdateNoshowlabelsPObject(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabPosted[6]);
}

void CDrawView::OnNoshowlabelsPPatch() 
{
	m_bNS_LabPosted[2] = !m_bNS_LabPosted[2];
}

void CDrawView::OnUpdateNoshowlabelsPPatch(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabPosted[2]);
}

void CDrawView::OnNoshowlabelsPSolid() 
{
	m_bNS_LabPosted[4] = !m_bNS_LabPosted[4];
}

void CDrawView::OnUpdateNoshowlabelsPSolid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabPosted[4]);
}

void CDrawView::OnNoshowlabelsStaticDisplace() 
{
	m_bNS_LabStatic[1] = !m_bNS_LabStatic[1];
}

void CDrawView::OnUpdateNoshowlabelsStaticDisplace(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabStatic[1]);
}

void CDrawView::OnNoshowlabelsStaticForce() 
{
	m_bNS_LabStatic[0] = !m_bNS_LabStatic[0];
}

void CDrawView::OnUpdateNoshowlabelsStaticForce(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabStatic[0]);
}

void CDrawView::OnNoshowlabelsStaticGravity() 
{
	m_bNS_LabStatic[5] = !m_bNS_LabStatic[5];
}

void CDrawView::OnUpdateNoshowlabelsStaticGravity(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabStatic[5]);
}

void CDrawView::OnNoshowlabelsStaticLumpwt() 
{
	m_bNS_LabStatic[4] = !m_bNS_LabStatic[4];
}

void CDrawView::OnUpdateNoshowlabelsStaticLumpwt(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabStatic[4]);
}

void CDrawView::OnNoshowlabelsStaticThermal() 
{
	m_bNS_LabStatic[3] = !m_bNS_LabStatic[3];
}

void CDrawView::OnUpdateNoshowlabelsStaticThermal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_LabStatic[3]);
}
//////////////////////////////////////////// end of module //////////////////