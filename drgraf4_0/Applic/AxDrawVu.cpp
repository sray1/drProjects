// drawview.cpp : implementation of the CAxDrawVu class         BASE Class
//


#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <Float.h>		// FLT_MAX
#include <afxcoll.h>	// CStringList etc.

 
#include "drgraf.h"
#include "drgradoc.h"
/////////////////////////////////////////////// Dialogs
#include "resource.h"                     // resource for Help IDR etc
#include "viewrsrc.h"                     // resource for GoodBy Id etc. InfoView etc
#include "Dlg_NoLE.h"                    // Label of Elements
#include "Dlg_NoEL.h"                    // Element
/////////////////////////////////////////////// toolboxes
#include "drgrafrm.h"
/////////////////////
#include "AxObjMgr.h"
#include "dListMgr.h"
#include "DrObject.h"
///////////////////// DrawOperationObjs
#include "Def_3D.h"
#include "XForm.h"
#include "3DMath.h"
///////////////////// IGen
#include "Def_IGen.h"
#include "Ext_Cur.h"
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
#include "AX_Wire0.h"
//////////////////////
#include "DrFont.h" 
#include "Def_MoBox.h" 
#include "AxDrawVu.h" 

//////////////////////////////////////
#define VIEWABLE_INDEX_BEGIN	0	
#define	new						DEBUG_NEW
#define	BUFF_SIZE				1024
//////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CAxDrawVu, CScrollView)
/////////////////////////////////////////////////////////////////////////////
// CAxDrawVu

BEGIN_MESSAGE_MAP(CAxDrawVu, CScrollView)
	//{{AFX_MSG_MAP(CAxDrawVu)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_COMMAND(IDM_OPTION_PENCHANGE, OnOptionPenchange)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_PENCHANGE, OnUpdateOptionPenchange)
	ON_COMMAND(IDM_OPTION_REFRESH, OnOptionRefresh)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_REFRESH, OnUpdateOptionRefresh)
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
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
	ON_COMMAND(IDM_NOSHOW_CENTROID, OnNoshowCentroid)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_CENTROID, OnUpdateNoshowCentroid)
	ON_COMMAND(IDM_NOSHOW_D_CURVE, OnNoshowDCurve)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_D_CURVE, OnUpdateNoshowDCurve)
	ON_COMMAND(IDM_NOSHOW_P_CURVE, OnNoshowPCurve)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_P_CURVE, OnUpdateNoshowPCurve)
	ON_COMMAND(IDM_MODE_DESIGN, OnModeDesign)
	ON_UPDATE_COMMAND_UI(IDM_MODE_DESIGN, OnUpdateModeDesign)
	ON_COMMAND(IDM_MODE_INTERPOLATE, OnModeInterpolate)
	ON_UPDATE_COMMAND_UI(IDM_MODE_INTERPOLATE, OnUpdateModeInterpolate)
	ON_COMMAND(ID_SUMMARY_CURVE_DIRTY, OnSummaryCurveDirty)
	ON_COMMAND(ID_SUMMARY_CURVE_POSTED, OnSummaryCurvePosted)
	ON_COMMAND(ID_SUMMARY_NODE_ALLTYPES, OnSummaryNodeAlltypes)
	ON_COMMAND(ID_SUMMARY_NODE_CONTROL, OnSummaryNodeControl)
	ON_COMMAND(ID_SUMMARY_NODE_MESH, OnSummaryNodeMesh)
	ON_COMMAND(IDM_NOSHOW_MNLABEL, OnNoshowMnlabel)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_MNLABEL, OnUpdateNoshowMnlabel)
	ON_COMMAND(IDM_NOSHOW_MNODES, OnNoshowMnodes)
	ON_UPDATE_COMMAND_UI(IDM_NOSHOW_MNODES, OnUpdateNoshowMnodes)
	ON_MESSAGE(WM_COMMANDHELP,OnCommandHelp)
	ON_MESSAGE(WM_HELPHITTEST,OnHelpHitTest)
	ON_COMMAND(IDM_MODE_GENERATOR, OnViewModeGenerator)
	ON_UPDATE_COMMAND_UI(IDM_MODE_GENERATOR, OnUpdateViewModeGenerator)
	ON_COMMAND(IDM_MODE_MESH, OnViewModeMesh)
	ON_UPDATE_COMMAND_UI(IDM_MODE_MESH, OnUpdateViewModeMesh)
	//}}AFX_MSG_MAP
	ON_WM_MOUSEACTIVATE()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAxDrawVu diagnostics

#ifdef _DEBUG
void CAxDrawVu::AssertValid() const
{
	CScrollView::AssertValid();
}

void CAxDrawVu::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CAxDrawVu construction, initialization, and destruction

CAxDrawVu::CAxDrawVu()
{
	//////////////////////////
	m_bViewGene = TRUE;
	m_bViewMesh = FALSE;
	///////////////////////////////////////////
//	m_GenMode		= REVERSE; // Interpolation
	m_GenMode		= FORWARD; // Interpolation
	/////////////////////////////////////////////// NonViewables <11
	m_nPrevSelectedObjIndex = VIEWABLE_INDEX_BEGIN;    
	m_nPrevSelectedObjType  = NONE;    
	/////////////////////////// Dirty	
	m_bNS_D_Curve	= FALSE;
	/////////////////////////// Posted	
	m_bNS_P_Curve	= TRUE;
	/////////////////////////// Node	
	m_bNS_CNLabel 	= FALSE;	
	m_bNS_CNode		= FALSE;	
	m_bNS_NLabel	= FALSE;	
	m_bNS_Node		= FALSE;	
	m_bNS_MNLabel	= FALSE;	
	m_bNS_MNode		= FALSE;
	///
	m_bNS_CShape	= TRUE; 
//////////////////////////////////////////////////////////////////////////////	
}

CAxDrawVu::~CAxDrawVu()
{
} 

BOOL CAxDrawVu::PreCreateWindow(CREATESTRUCT& cs)
{

	m_ClassName = AfxRegisterWndClass
		(CS_HREDRAW| CS_VREDRAW,
		0,
		(HBRUSH)::GetStockObject(BLACK_BRUSH),
		0);
	cs.lpszClass	= m_ClassName;
	//////////////////////////
//	cs.style |= WS_VSCROLL|WS_HSCROLL;
	BOOL bRtn = CScrollView::PreCreateWindow(cs);
	
	return bRtn;
}

LRESULT CAxDrawVu::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
	if (lParam == 0)
	{
		if(m_nView == VIEW12)
			lParam = HID_BASE_RESOURCE + IDR_VIEW12;
		else
			return FALSE;
	}
	// context already determined above
	AfxGetApp()->WinHelp(lParam);
	return TRUE;
}

LRESULT CAxDrawVu::OnHelpHitTest(WPARAM wParam, LPARAM lParam)
{
	if(m_nView == VIEW12)
		return HID_BASE_RESOURCE + IDR_VIEW12;
	else
		return HID_BASE_RESOURCE + IDR_VIEWUNKNOWN;	
}
/////////////////////////////////////////////////////////////////////////////
// CAxDrawVu updating and drawing
void CAxDrawVu::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// The size of text that is displayed, printed or previewed changes
	// depending on the DC.  We explicitly call OnPrepareDC() to prepare
	// CClientDC objects used for calculating text positions and to
	// prepare the text metric member variables of the CAxDrawVu object.
	// The framework also calls OnPrepareDC() before passing the DC to
	// OnDraw().

	CScrollView::OnPrepareDC(pDC, pInfo);
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
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

void CAxDrawVu::SetScalevv3DToLP()
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
	  
pMATRIX CAxDrawVu::GetMatrix(MATRICES mType)
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

void CAxDrawVu::SetMatrix(MATRICES mType,pMATRIX pMat)
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

void CAxDrawVu::OnInitialUpdate()
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= (CDrGrafDoc*)GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CPrecision* pPrecision  = (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	CDrFont* pDrFont		= (CDrFont*)pObjectMgr->GetSpecObject(DRFONT); 
	////////////////////////////////////////////////////////////  
	SetScrollSizes(pMapFactor->GetMapModeIndex(),
						pObjectMgr->GetDocSize() );

//	GetParentFrame()->RecalcLayout();This will be done OnZoomToFit	
//	m_sizeDoc = GetTotalSize(); 
	m_sizeDoc = pObjectMgr->GetDocSize(); 
//	GetParentFrame()->RecalcLayout(); // this sets view window
//	SetScaleToFitSize(m_sizeDoc);
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
	///////////////////////////////
	m_bParallel	= TRUE;		// true disables perspective 
	/////////////////////////// View Orientation Parameters (VRC) /////////////
	p3DMath->Set3DPts(&m_VRP,0.0,0.0,0.0);	// View Reference Point(Origin)
	p3DMath->Set3DPts(&m_VPN,0.0,0.0,1.0);	// View Plane Normal(z-Axis)
	p3DMath->Set3DPts(&m_VUP,0.0,1.0,0.0);	// View Up Vector(y-axis)
	///////////// View Mapping Parameters (VRC) /////////////
	m_Umin		= 0;		// View Plane Window(VRC)
	m_Umax		=  m_Width_U;
	m_Vmin		= 0;
	m_Vmax		=  m_Width_V;
	m_dFront	=  FLT_MAX,				// near clipping plane
	m_dBack		=  -FLT_MAX;			// far clipping plane
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
	//////////////////////////////////////////////////////////// RePosition OperStat/CurrStat
	GetClientRect(&clientRect);
	CPoint ptLeftTop;
	ptLeftTop.x = clientRect.left + (clientRect.Width() - 102)/2;  
	ptLeftTop.y = clientRect.top + 1;
	ClientToScreen(&ptLeftTop);
	pWnd->GetOperStat()->SetWindowPos(NULL,ptLeftTop.x,ptLeftTop.y,102,20,SWP_NOZORDER|SWP_SHOWWINDOW);
	////////////// 
	ptLeftTop.x = clientRect.left + 1;  
	ptLeftTop.y = clientRect.bottom - 40;
	ClientToScreen(&ptLeftTop);
	pWnd->GetCurrStat()->SetWindowPos(NULL,ptLeftTop.x,ptLeftTop.y,300,40,SWP_NOZORDER|SWP_SHOWWINDOW);
	//////////////

}	

void CAxDrawVu::UpdateAllOtherMatButLocal()
{
    UpdateViewMatrix();
   	if(!m_bParallel)
   		UpdatePerToParMatrix();
    UpdateCombinedMatrix();
	UpdateWin3DtoViewPort3DMatrix();
	UpdatePenultimateMatrix();				// Penultimate
	UpdateUltimateMatrix();				// Ultimate
}

void CAxDrawVu::UpdateViewMatrix()
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

void CAxDrawVu::UpdatePerToParMatrix()
{
	C3DMath Math3D;
	Math3D.GetIdentityMATRIX(&m_PerToParM);
	//////////////////////////
	CXForm XForm(m_bParallel);
	//////////////////////////
	XForm.PerToParCVVMATRIX(&m_PerToParM,m_dzMin); 
	///////////////
}	

void CAxDrawVu::UpdateCombinedMatrix()
{
	//////////////////////////
	CXForm XForm(m_bParallel);
	//////////////////////////
	XForm.ComposeCombineMATRIX
			(&m_LocalM,&m_ViewM,&m_ComposedM);		// Composed
}

void CAxDrawVu::UpdateWin3DtoViewPort3DMatrix()
{

	//////////////////////////
	CXForm XForm(m_bParallel);
	//////////////////////////
	XForm.ComposeWin3DtoScreen3DMATRIX
			(&m_vv3DM,m_VPmin,m_VPmax);				// Winto3DViewport3D
	//////////////////////////////////////////////
}

void CAxDrawVu::UpdatePenultimateMatrix()
{
	//////////////////////////
	CXForm XForm(m_bParallel);
	//////////////////////////
	XForm.ComposeCombineMATRIX
			(&m_ComposedM,&m_vv3DM,&m_PenultiM);		// Penultimate
	//////////////////////////
}

void CAxDrawVu::UpdateUltimateMatrix()
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

void CAxDrawVu::UpdateObject(int nInvalidObjIndex,int nObjType,int nViewNumber)
{ 


	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
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

void CAxDrawVu::OnDraw(CDC* pDC)
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
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
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
 		pObjectMgr->SetViewChanged(FALSE);
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
	///////////
	SetCursor( saveCurs );
}

void CAxDrawVu::ShowScreenGrid(CDC* pDC)
{
	int stepx = 100,stepy = 100; 
	//////////////////////////
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	///////////////////////////////////////////////////////////////////// TextOut 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
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

void CAxDrawVu::ShowCurrentOptions(CDC* pDC)
{
/*
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

		default:
			break;
	}
  	////////////////////////////////////// Encode
	j += sprintf(buf+j,"%s ",nameC);
	str->ReleaseBuffer();
	///////////////////////////////////////////////////////////////////// TextOut 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
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
//	int mapModeOld		= pDC->SetMapMode(MM_TEXT);
//	CPoint VuportOrgOld	= pDC->SetViewportOrg(0,0);
//	CPoint WndOrgOld	= pDC->SetWindowOrg(0,0);
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

//	pDC->SetMapMode(mapModeOld);
//	pDC->SetViewportOrg(VuportOrgOld);
//	pDC->SetWindowOrg(WndOrgOld);

	pDC->SetTextColor(crColorOld);
	pDC->SetBkMode(modeOld);
 	Font.DeleteObject();
    Pen.DeleteObject();
	/////
 	delete str;
	///////////
*/
}

void CAxDrawVu::GoDoAxis(CDC* pDC)
{
//	NOT USED
}
//////////////////////
#define	NODE_SIZE	5
#define	TEXT_OFF	3

void CAxDrawVu::GoDoPoint(CDC* PtrDC,POINT* pt,CString& text)
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

void CAxDrawVu::GoDoLine(CDC* PtrDC,POINT* pt1,POINT* pt2)
{ 

   	//////////////////////////////////////////////// Draw
   	PtrDC->MoveTo(pt1->x,pt1->y);
   	PtrDC->LineTo(pt2->x,pt2->y);
	/////////////////////////////// 
   	
}   

void CAxDrawVu::GetObjectReadyforRender(CDC* pDC,CDrObject* pObject,
													int nObjType)
{
	if(!(pObject->IsShow()))
		return;
	///////////////////////////////////////////////////
	Pack_NSBools(m_bNS); 
	/////////////////////////////////////////////////// Render
	CAxWire_0	Wire_0(this,m_bParallel,m_bNS);
	////////////////
	Wire_0.Init
		(
			m_nView,FALSE,m_VDir,
			&m_ViewM,&m_ComposedM,&m_vv3DM,m_dzMin,
			m_dScale_U,m_dScale_V,0.0
		);
	Wire_0.RenderReadyOBJECT(pDC,pObject,nObjType);
	///////////////////
}

void CAxDrawVu::Pack_NSBools(BOOL bNS[])
{
	/////////////////////////////////////////////////// Pack NSBOOLs
	bNS[14] = m_bNS_2DLabel;  
	bNS[15] = m_bNS_3DLabel; 
	bNS[16] = m_bNS_CNLabel; 
	bNS[17] = m_bNS_CNode; 
	bNS[18] = m_bNS_NLabel; 
	bNS[19] = m_bNS_Node; 
	bNS[20] = m_bNS_CShape; 
	bNS[22] = m_bNS_Centroid; 
	bNS[26] = m_bNS_D_Curve; 
	bNS[30] = m_bNS_P_Curve;
	////////////////////////////// MeshNode
	bNS[42] = m_bNS_MNLabel;	
	bNS[43] = m_bNS_MNode;	
	////////////////////////////// StaticLoad
	 
    
}

void CAxDrawVu::GoRender(CDC* pDC,CRect RectClip,int nActiveObjType,int nActiveObjIndex)
{ 
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
    /////////////////////////////////////////////////////////////////////
	Pack_NSBools(m_bNS); 
	/////////////////////////////////////////////////// Render
	CAxWire_0	Wire_0(this,TRUE,m_bNS);
	////////////////
	Wire_0.Init
		(
			m_nView,FALSE,m_VDir,
			&m_ViewM,&m_ComposedM,&m_vv3DM,m_dzMin,
			m_dScale_U,m_dScale_V,0.0
		);
	/////////////////// GoDoIt	
	Wire_0.RenderScene_AUXILLIARY((CClientDC*)pDC,RectClip,nActiveObjType,
							nActiveObjIndex,m_nView);
	///////////////////
}

void CAxDrawVu::Transform(pWORLD pptIn, pWORLD pptOut)
{
	
	CXForm XForm(m_bParallel);
	/////////////////////////////////////
	XForm.Transform(pptIn,pptOut,&m_ComposedM);
	/////////////////////////////////////	
    return;
}                            

void CAxDrawVu::Project(pWORLD pptIn, pWORLD pptOut,BOOL bSize)
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
// Overrides of CScrollView for implementing printing.
/*
BOOL CAxDrawVu::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CAxDrawVu::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
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

void CAxDrawVu::OnPrint(CDC* pDC, CPrintInfo* pInfo)
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

BOOL CAxDrawVu::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CDrgrafCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CAxDrawVu::OnInsertObject()
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
void CAxDrawVu::OnCancelEdit()
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
void CAxDrawVu::OnSetFocus(CWnd* pOldWnd)
{
	/////////////////////////////////////////////////////

	CScrollView::OnSetFocus(pOldWnd);
}
*/
/////////////////////////////////////////////////////////////////////////////
// CAxDrawVu commands
void CAxDrawVu::MouseActivateViewMatUpdate()
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

void CAxDrawVu::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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

int CAxDrawVu::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

void CAxDrawVu::ShowAxes()
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


void CAxDrawVu::OnOptionAxison()
{
	////////////////////////////////////////////////////////	
	if(!(m_wndAxisDraw.GetStyle() & WS_VISIBLE))// not Visible
		ShowAxes();
	else
		m_wndAxisDraw.ShowWindow(SW_HIDE);
	
}

void CAxDrawVu::OnKillFocus(CWnd* pNewWnd)
{
	CScrollView::OnKillFocus(pNewWnd);
	//////////////////////////////////////////////// do nothing	
//	if(m_wndAxisDraw.GetSafeHwnd() != 0)// visible
//		m_wndAxisDraw.DestroyWindow();
//		m_wndAxisDraw.ShowWindow(SW_HIDE);
	
}

void CAxDrawVu::OnUpdateOptionAxison(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((m_wndAxisDraw.GetStyle() & WS_VISIBLE) != NULL);
	
}

void CAxDrawVu::OnOptionPenchange()
{   

	CSDlgMgr* pSDlgMgr;
	/////////////////////////
	pSDlgMgr->DoModal_SpecObjs(DRPEN);
	return;
	/////////////////////////	
	
}

void CAxDrawVu::OnUpdateOptionPenchange(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CAxDrawVu::OnOptionRefresh()
{
	// TODO: Add your command handler code here
	
}

void CAxDrawVu::OnUpdateOptionRefresh(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}
/////////////////////////////// end of module /////////////////////

BOOL CAxDrawVu::OnEraseBkgnd(CDC* pDC)
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

void CAxDrawVu::OnSetFocus(CWnd* pOldWnd)
{
	CScrollView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	///////////////////////
//	Invalidate();			// repaint the entire scene
	/////////////
}

void CAxDrawVu::OnNoShowCNodes()
{
	m_bNS_CNode = !m_bNS_CNode;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CAxDrawVu::OnUpdateNoShowCNodes(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_CNode);
}

void CAxDrawVu::OnNoShowCNLabel()
{
	m_bNS_CNLabel = !m_bNS_CNLabel;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CAxDrawVu::OnUpdateNoShowCNLabel(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_CNLabel);
}


void CAxDrawVu::OnNoShowNodes()
{
	m_bNS_Node = !m_bNS_Node;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CAxDrawVu::OnUpdateNoShowNodes(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_Node);
}

void CAxDrawVu::OnNoshowMnodes() 
{
	m_bNS_MNode = !m_bNS_MNode;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CAxDrawVu::OnNoShowNLabel()
{
	m_bNS_NLabel = !m_bNS_NLabel;	
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CAxDrawVu::OnUpdateNoShowNLabel(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_NLabel);
}

void CAxDrawVu::OnUpdateNoshowMnodes(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_MNode);
}

void CAxDrawVu::OnNoshowMnlabel() 
{
	m_bNS_MNLabel = !m_bNS_MNLabel;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CAxDrawVu::OnUpdateNoshowMnlabel(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bNS_MNLabel);
}

void CAxDrawVu::OnNoShowCShape()
{
	m_bNS_CShape = !m_bNS_CShape;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CAxDrawVu::OnUpdateNoShowCShape(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_CShape);
}

void CAxDrawVu::OnNoshowCentroid()
{
	m_bNS_Centroid	= !m_bNS_Centroid;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
	
}

void CAxDrawVu::OnUpdateNoshowCentroid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_Centroid);
}

void CAxDrawVu::OnNoshowDCurve()
{
	m_bNS_D_Curve	= !m_bNS_D_Curve;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CAxDrawVu::OnUpdateNoshowDCurve(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_D_Curve);
}

void CAxDrawVu::OnNoshowPCurve()
{
	m_bNS_P_Curve	= !m_bNS_P_Curve;
	///////////////////////////////
	SetSceneChangedOnNoShow();
	//////////////////////////
}

void CAxDrawVu::OnUpdateNoshowPCurve(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bNS_P_Curve);
}

void CAxDrawVu::SetSceneChangedOnNoShow()
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	pObjectMgr->SetSceneChanged(TRUE);
	pDoc->UpdateAllViews(NULL);
	//////////////////////////
}

/////////////////////////////////////////////////////////////////////
void CAxDrawVu::OnModeDesign()
{
	if(m_GenMode == REVERSE)
		m_GenMode = FORWARD;
}

void CAxDrawVu::OnUpdateModeDesign(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_GenMode == FORWARD);
}

void CAxDrawVu::OnModeInterpolate()
{
	if(m_GenMode == FORWARD)
		m_GenMode = REVERSE;
}

void CAxDrawVu::OnUpdateModeInterpolate(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_GenMode == REVERSE);
}
//////////////////////////////////////////////////////////////////////
CDListMgr* CAxDrawVu::GetList(UINT nType)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	CDListMgr* 	pDListMgr 	= pObjectMgr->GetObjectList(nType);
	/////////////
	return pDListMgr;
}

void CAxDrawVu::ShowCountBox(LPCTSTR string,int nCount)
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

void CAxDrawVu::OnSummaryNodeMesh() 
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


void CAxDrawVu::OnSummaryCurveDirty() 
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

void CAxDrawVu::OnSummaryCurvePosted() 
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

void CAxDrawVu::OnSummaryNodeAlltypes() 
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

void CAxDrawVu::OnSummaryNodeControl() 
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

/////////////////////////////////////////////////////////////// Mouse Handler
void CAxDrawVu::MouseMove(UINT nFlags, CPoint point)
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

		case GOP_EDIT:
		case GOP_MOVE:
		///////////////////////////
			m_DVM_Edit.MouseMove(this, nFlags, point);
			break;

		case GOP_DELETE:
		///////////////////////////
			m_DVM_Del.MouseMove(this,nFlags,point);
			break;

	}
}

void CAxDrawVu::LButtonDown(UINT nFlags, CPoint point)
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

		case GOP_EDIT:
		case GOP_MOVE:
		///////////////////////////
			m_DVM_Edit.LButtonDown(this,nFlags,point);
			break;

		case GOP_DELETE:
		///////////////////////////
			m_DVM_Del.LButtonDown(this,nFlags,point);
			break;

	}
}

void CAxDrawVu::LButtonUp(UINT nFlags, CPoint point)
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

		case GOP_EDIT:
		case GOP_MOVE:
		///////////////////////////
			m_DVM_Edit.LButtonUp(this,nFlags,point);
			break;

		case GOP_DELETE:
		///////////////////////////
			m_DVM_Del.LButtonUp(this,nFlags,point);
			break;
/*
		case GOP_POST:
		///////////////////////////
			m_DVM_Post.LButtonUp(this,nFlags,point);
			break;
*/
	}
}

void CAxDrawVu::RButtonDown(UINT nFlags, CPoint point)
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

		case GOP_EDIT:
		case GOP_MOVE:
		///////////////////////////
			m_DVM_Edit.RButtonDown(this,nFlags,point);
			break;

		case GOP_DELETE:
		///////////////////////////
			m_DVM_Del.RButtonDown(this,nFlags,point);
			break;
/*
		case GOP_POST:
		///////////////////////////
			m_DVM_Post.RButtonDown(this,nFlags,point);
			break;
*/
	}
}
		
void CAxDrawVu::RButtonUp(UINT nFlags,CPoint point)
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

		case GOP_EDIT:
		case GOP_MOVE:
		///////////////////////////
			m_DVM_Edit.RButtonUp(this,nFlags,point);
			break;

		case GOP_DELETE:
		///////////////////////////
			m_DVM_Del.RButtonUp(this,nFlags,point);
			break;
/*
		case GOP_POST:
		///////////////////////////
			m_DVM_Post.RButtonUp(this,nFlags,point);
			break;
*/
	}
}

void CAxDrawVu::OnViewModeGenerator() 
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_bViewGene = TRUE;
	m_bViewMesh = FALSE;
	////////////////////
	pWnd->SetMeshMode(m_bViewMesh); // Edit/Creop etc. depends on this
	pWnd->OnModeChange();
	//////////////////////////
	Invalidate();
	UpdateWindow();
	///////////////
}

void CAxDrawVu::OnUpdateViewModeGenerator(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bViewGene);
}

void CAxDrawVu::OnViewModeMesh() 
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	m_bViewGene = FALSE;
	m_bViewMesh = TRUE;
	////////////////////
	pWnd->SetMeshMode(m_bViewMesh); // Edit/Creop etc. depends on this
	pWnd->OnModeChange();
	//////////////////////////
	Invalidate();
	UpdateWindow();
	///////////////
}

void CAxDrawVu::OnUpdateViewModeMesh(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bViewMesh);
}
//////////////////////////////////////////// end of module //////////////////
