// drstatus.cpp : implementation file
//
#include "stdafx.h"

#include "drgraf.h"
#include "drgrafrm.h"
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// SpecObjs
#include "Def_Spec.h" 
#include "Layer.h"
#include "Precison.h"
#include "ScaleFac.h"
#include "Mapfacto.h"
#include "Unit.h"
///////////////////// ElemBox/DrawBox
#include "Ext_Elem.h"
#include "Ext_DBox.h"

#include "drstatus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static CString strMeshType[] =
				{
					"",
					"LINEAR",
					"QUADRATIC",
					"Cubic HERMITE",
					"Cubic BEZIER",
					"Cubic B_SPLINE"
				};	
/////////////////////////////////////////////////////////////
/******************
// CDrStatusBar

CDrStatusBar::CDrStatusBar()
{
}

CDrStatusBar::~CDrStatusBar()
{
}


/////////////////////////////////////////////////////////////////////////////
// CDrStatusBar message handlers
/////////////////////////////////////////////////////////////////////From:Winfrm.cpp
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_STATUS_BAR, OnBarCheck)
 
 
void CFrameWnd::OnUpdateControlBarMenu(CCmdUI* pCmdUI)
{
	ASSERT(ID_VIEW_STATUS_BAR == AFX_IDW_STATUS_BAR);
	ASSERT(ID_VIEW_TOOLBAR == AFX_IDW_TOOLBAR);

	CWnd* pBar;
	if ((pBar = GetDescendantWindow(pCmdUI->m_nID)) == NULL)
	{
		pCmdUI->ContinueRouting();
		return; // not for us
	}

	pCmdUI->SetCheck((pBar->GetStyle() & WS_VISIBLE) != 0);
}

BOOL CFrameWnd::OnBarCheck(UINT nID)
{
	ASSERT(ID_VIEW_STATUS_BAR == AFX_IDW_STATUS_BAR);
	ASSERT(ID_VIEW_TOOLBAR == AFX_IDW_TOOLBAR);

	CWnd* pBar;
	if ((pBar = GetDescendantWindow(nID)) == NULL)
		return FALSE;   // not for us

	// toggle visible state
	pBar->ShowWindow((pBar->GetStyle() & WS_VISIBLE) == 0);
	RecalcLayout();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Support for standard status bar

void CFrameWnd::OnUpdateKeyIndicator(CCmdUI* pCmdUI)
{
	UINT nVK;

	switch (pCmdUI->m_nID)
	{
	case ID_INDICATOR_CAPS:
		nVK = VK_CAPITAL;
		break;

	case ID_INDICATOR_NUM:
		nVK = VK_NUMLOCK;
		break;

	case ID_INDICATOR_SCRL:
		nVK = VK_SCROLL;
		break;

	default:
		TRACE1("Warning: OnUpdateKeyIndicator - unknown indicator 0x%04X\n",
			pCmdUI->m_nID);
		pCmdUI->ContinueRouting();
		return; // not for us
	}

	pCmdUI->Enable(::GetKeyState(nVK) & 1);
		// enable static text based on toggled key state
	ASSERT(pCmdUI->m_bEnableChanged);
}
/////////////////////////////////////////////////////////////////////////////   
**************/
/////////////////////////////////////////////////////////////////////////////
// CStatusBar creation etc
/*
struct AFX_STATUSPANE
{
	UINT    nID;        // IDC of indicator: 0 => normal text area
	UINT    nStyle;     // style flags (SBPS_*)
	int     cxText;     // width of string area in pixels
						//   on both sides there is a 1 pixel gap and
						//    a one pixel border, making a pane 4 pixels wider
	LPCSTR  lpszText;   // always far strings
};
/////////////////////////////////////////////////////////////////////////////
// CStatusBar implementation
//#define CX_BORDER	1
void CDrStatusBar::DoPaint(CDC* pDC)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	CControlBar::DoPaint(pDC);      // draw border
	CRect rect;
	GetClientRect(rect);
	CalcInsideRect(rect);

	AFX_STATUSPANE* pSBP;
	int i;

	ASSERT(m_hFont != NULL);        // must have a font !
	HGDIOBJ hOldFont = pDC->SelectObject(m_hFont);

	int cxExtra = rect.Width() - m_cxRightBorder + m_cxDefaultGap;
	// first walk through to calculate extra space
	for (i = 0, pSBP = (AFX_STATUSPANE*)m_pData; i < m_nCount; i++, pSBP++)
		cxExtra -= (pSBP->cxText + CX_BORDER * 4 + m_cxDefaultGap);
	// if cxExtra <= 0 then we will not stretch but just clip 
	for (i = 0, pSBP = (AFX_STATUSPANE*)m_pData; i < m_nCount; i++, pSBP++)
	{
		ASSERT(pSBP->cxText >= 0);
		int cxText = pSBP->cxText;
		if ((pSBP->nStyle & SBPS_STRETCH) && cxExtra > 0)
		{
			cxText += cxExtra;
			cxExtra = 0;
		}
		rect.right = rect.left + cxText + CX_BORDER * 4;
		if (::RectVisible(pDC->m_hDC, &rect))
		{
			///////////////////////////////////////// Text Color
			// if pSBP->nID>0 (indicator) : black
			//             =0 (text area) ; purple
			///////////////////////////////////////
			SetTextColor(pDC->m_hDC, RGB(255,0,255));      // PURPLE
			if(pSBP->nID>0)
				SetTextColor(pDC->m_hDC, RGB(0,0,0));      // BLACK
		    //////////////////////////////////////////////////
			DrawStatusText(pDC->m_hDC, rect, pSBP->lpszText, pSBP->nStyle);
			///////////////////////// 
		}	
		rect.left = rect.right + m_cxDefaultGap;
	}
	pDC->SelectObject(hOldFont);
}

void PASCAL CDrStatusBar::DrawStatusText(HDC hDC, CRect const& rect,
			LPCSTR lpszText, UINT nStyle)
{
	ASSERT(hDC != NULL);

	HBRUSH hbrHilite = NULL;
	HBRUSH hbrShadow = NULL;
	if (!(nStyle & SBPS_NOBORDERS))
	{
		if (nStyle & SBPS_POPOUT)
		{
			// reverse colors
			hbrHilite = afxData.hbrBtnShadow;
			hbrShadow = afxData.hbrBtnHilite;
		}
		else
		{
			// normal colors
			hbrHilite = afxData.hbrBtnHilite;
			hbrShadow = afxData.hbrBtnShadow;
		}
	}

	// background is already grey
	UINT nOpts = ETO_CLIPPED;
	int nOldMode = SetBkMode(hDC, TRANSPARENT);
//	COLORREF crTextColor = SetTextColor(hDC, afxData.clrBtnText);
	COLORREF crBkColor = SetBkColor(hDC, afxData.clrBtnFace);

	// Draw the hilites
	if (hbrHilite != NULL)
	{
		HGDIOBJ hOldBrush = SelectObject(hDC, hbrHilite);
		if (hOldBrush)
		{
			PatBlt(hDC, rect.right, rect.bottom,
				-(rect.Width() - CX_BORDER),
				-CY_BORDER, PATCOPY);
			PatBlt(hDC, rect.right, rect.bottom,
				-CX_BORDER,
				-(rect.Height() - CY_BORDER), PATCOPY);
			SelectObject(hDC, hOldBrush);
		}
	}

	if (hbrShadow != NULL)
	{
		HGDIOBJ hOldBrush = SelectObject(hDC, hbrShadow);
		if (hOldBrush)
		{
			PatBlt(hDC, rect.left, rect.top,
				rect.Width(), CY_BORDER, PATCOPY);
			PatBlt(hDC, rect.left, rect.top,
				CX_BORDER, rect.Height(), PATCOPY);
			SelectObject(hDC, hOldBrush);
		}
	}

	// We need to adjust the rect for the ExtTextOut, and then adjust it back

	// just support left justified text
	if (lpszText != NULL && !(nStyle & SBPS_DISABLED))
	{
		CRect rectText(rect);
		rectText.InflateRect(-2*CX_BORDER, -CY_BORDER);

		// align on bottom (since descent is more important than ascent)
		SetTextAlign(hDC, TA_LEFT | TA_BOTTOM);
		ExtTextOut(hDC, rectText.left, rectText.bottom,
			nOpts, &rectText, lpszText, lstrlen(lpszText), NULL);
	}
}
*/
//////////////////////////////
///////////////////////////////////////////////////////////////////// TOP
CTopStatusBar::CTopStatusBar()
{
//	Init();
}

void CTopStatusBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{ 
}

int CTopStatusBar::Init()
{
	CString str;
	UINT nID, nStyle;
	int cxWidth;

	
	GetPaneInfo(0,nID,nStyle,cxWidth);
	SetPaneInfo(0,nID,SBPS_POPOUT,80);
	SetPaneText(0,"DRAWING:",TRUE);

	GetPaneInfo(1,nID,nStyle,cxWidth);
	SetPaneInfo(1,nID,SBPS_NORMAL,100);
	 
	GetPaneInfo(2,nID,nStyle,cxWidth);
	SetPaneInfo(2,nID,SBPS_POPOUT,60);
	SetPaneText(2,"LAYER:",TRUE);
	 
	GetPaneInfo(3,nID,nStyle,cxWidth);
	SetPaneInfo(3,nID,SBPS_NORMAL,30);
	
	GetPaneInfo(4,nID,nStyle,cxWidth);
	SetPaneInfo(4,nID,SBPS_POPOUT,45);
	SetPaneText(4,"UNIT:",TRUE);
	
	GetPaneInfo(5,nID,nStyle,cxWidth);
	SetPaneInfo(5,nID,SBPS_NORMAL,150);
	 
	GetPaneInfo(7,nID,nStyle,cxWidth);
	SetPaneInfo(7,nID,SBPS_POPOUT,40); 
	SetPaneText(7,"TIME:",TRUE);
	
	GetPaneInfo(8,nID,nStyle,cxWidth);
	SetPaneInfo(8,nID,SBPS_NORMAL,100); 
	
	GetPaneInfo(9,nID,nStyle,cxWidth);
	SetPaneInfo(9,nID,SBPS_POPOUT,45); 
	SetPaneText(9,"DATE:",TRUE); 
	
	GetPaneInfo(10,nID,nStyle,cxWidth);
	SetPaneInfo(10,nID,SBPS_NORMAL,100); 
	
	GetPaneInfo(6,nID,nStyle,cxWidth);
	SetPaneInfo(6,nID,SBPS_STRETCH,10); 
	/////////
	return 0;
	
}

static UINT BASED_CODE graph_indicators[] =
{

	ID_SEPARATOR,			// status line indicator
	ID_INDICATOR_TEXT_X,
	ID_SEPARATOR,			
	ID_INDICATOR_TEXT_Y,
	ID_SEPARATOR,			
	ID_INDICATOR_TEXT_Z,
	ID_SEPARATOR,			

};
//////////////////////////////////////////////////////////////////////////////////
void CTopStatusBar::UpdateStatusBar(CClientDC*  pDC)
{
	char buf[120];
	CString	str;    
	/////////////////////////////// MapMode 
	char* MapModes[] ={"","MM_TEXT","MM_LOMETRIC","MM_HIMETRIC","MM_LOENGLISH",
					  "MM_HIENGLISH","MM_TWIPS","MM_ISOMETRIC","MM-ANISOMETRIC"};
	//////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////////////// Drawing Mode
	///////////////////////////////////////////////////////// ElemBox
	if (pWnd->IsIGenBoxActive())
	{	
		int nID = pWnd->GetActiveObjectType();
		if(nID>=0) 
		{
			////////////////////////////////////////// get index 
			for (int i = 0; i<nMax_ElemTypes; i++)
			{
				if(nID == ElTypes[i].num)
				{
					str += ElTypes[i].ObjName; 
//					AfxMessageBox(str);
//					return;
				}
			} 
		}
	}		
	///////////////////////////////////////////////////////// DrawBox	
	if (pWnd->IsDrawBoxActive())
	{	
		int nID = pWnd->GetActiveObjectType();// 
		if(nID<0) return;
		/////////////////////////////////////////// Object
		for (int i = 0; i<nMax_DBoxTypes; i++)
		{
			if(nID == DbTypes[i].num)
			{

				str += DbTypes[i].ObjName;

			} 
		}
/*			
		/////////////////////////////////////////// Tool
		if((nID = pObjectMgr->GetDBoxMgr()->GetActiveToolType())>=0)
		{
			for (int j = 0; j<nMax_DBoxTypes; j++)
			{
				if(nID == DbTypes[j].num)
					str += DbTypes[j].ObjName;
			}	 
        }
        ///////////////////////////////////////////
*/
	}			
	////////////////////////
	SetPaneText(1,str,TRUE); 
	/////////////////////////////////////////////////////// Layer    
	CLayer* pLayer = (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	///////////////////////////////////////////////
	sprintf(buf,"%u",pLayer->GetCurrentLayer());
	str = buf;
	SetPaneText(3,str,TRUE); 
	/////////////////////////////////////////////////////// Unit
	CUnit* pUnit = (CUnit*)pObjectMgr->GetSpecObject(UNIT);
	///////////////////////////////////////////////
	str = pUnit->GetUnitName(pUnit->GetUnitIndex());
	SetPaneText(5,str,TRUE);
	////////////////////////////////////////////// 
	
}

///////////////////////////////////////////////////////////////////// BOTTOM
CBotStatusBar::CBotStatusBar()
{
//	Init();
}

void CBotStatusBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{ 
}

int CBotStatusBar::Init()
{

	if (!SetIndicators(graph_indicators,
		  sizeof(graph_indicators)/sizeof(UINT)))
	{
		TRACE("Failed to set indicators in status bar\n");
		return -1;		// fail to create
	}
	CString str;
	UINT nID, nStyle;
	int cxWidth;

	
	GetPaneInfo(1,nID,nStyle,cxWidth);
	SetPaneInfo(1,nID,SBPS_POPOUT,25);
	SetPaneText(1," X:",TRUE);

	GetPaneInfo(2,nID,nStyle,cxWidth);
	SetPaneInfo(2,nID,SBPS_NORMAL,110);
	 
	SetPaneInfo(3,nID,nStyle,cxWidth);
	SetPaneInfo(3,nID,SBPS_POPOUT,25);
	SetPaneText(3," Y:",TRUE);
	 
	GetPaneInfo(4,nID,nStyle,cxWidth);
	SetPaneInfo(4,nID,SBPS_NORMAL,110);
	
	GetPaneInfo(5,nID,nStyle,cxWidth);
	SetPaneInfo(5,nID,SBPS_POPOUT,25);
	SetPaneText(5," Z:",TRUE);
	
	GetPaneInfo(6,nID,nStyle,cxWidth);
	SetPaneInfo(6,nID,SBPS_NORMAL,110);
	
	GetPaneInfo(0,nID,nStyle,cxWidth);
	SetPaneInfo(0,nID,SBPS_STRETCH,10); 
	/////////
	return 0;
	
}
//////////////////////////////////////////////////////////////////////////////////
void CBotStatusBar::UpdateStatusBar(CClientDC*  pDC)
{
	char buf[120];
	CString	str;    
	/////////////////////////////// MapMode 
	char* MapModes[] ={"","MM_TEXT","MM_LOMETRIC","MM_HIMETRIC","MM_LOENGLISH",
					  "MM_HIENGLISH","MM_TWIPS","MM_ISOMETRIC","MM-ANISOMETRIC"};
	CString	Unit[] ={" in"," in"," ft"," ft"," mi"," mm"," cm"," m","km"};
	//////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 		= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CScaleFactor* pScaleFactor	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
    double dScaleFactor = pScaleFactor->GetScaleFactor();
	/////////////////////////////////////////////////////////////// 
	CUnit* pUnit		= (CUnit*)pObjectMgr->GetSpecObject(UNIT);
	int nUnitIndex 		= pUnit->GetUnitIndex();				  
	int nMapMode        = pDC->GetMapMode();
	///////////////////////////////////////////
	sprintf(buf,"MapMode = %s      Scale = 1 in : %.2f %s",
				MapModes[nMapMode],dScaleFactor,Unit[nUnitIndex] );
	str = buf;
	SetPaneText(0,str,TRUE); 
	///////////////////////////////////////  
	UINT nID,nStyle;
	int cxWidth;
	GetPaneInfo(0,nID,nStyle,cxWidth);
	SetPaneInfo(0,nID,SBPS_STRETCH,cxWidth);
	SetPaneText(0,"Go Ahead! Make My Day!!!",TRUE);
	///////////////////////////////////////    
    LPOINT3 MouseWIC = pWnd->GetMouseMgr()->GetStatusMouseWIC();       
    //////////////////////////////////////////
	CPrecision* pPrecision	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	double dWorldBase   	= (double)(pPrecision->GetWorldBase());
	//////////////////////////////////////////
    double xWorld 		= ((double)MouseWIC.x/dWorldBase);
    double yWorld 		= ((double)MouseWIC.y/dWorldBase);
    double zWorld 		= ((double)MouseWIC.z/dWorldBase);
    ///////////////////////////////////////////
	CMapFactor* pMapFactor	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR);
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////////
    xWorld 		*= dMapFactor;
    yWorld 		*= dMapFactor;
    zWorld 		*= dMapFactor;
    ////////////////////////// World Coord
    pObjectMgr->DStoSC(&xWorld);
    pObjectMgr->DStoSC(&yWorld);
    pObjectMgr->DStoSC(&zWorld); 
	//////////////////////////////////////////////// Bottom Status Bar 
	CString strAxis[6] = {" X: "," Y: "," Z: "," Horz:","Vert:","    "};
	/////////////////////////////////////////////////
	GetPaneInfo(1,nID,nStyle,cxWidth);
	SetPaneText(1,strAxis[0],TRUE); 
		 
	SetPaneInfo(3,nID,nStyle,cxWidth);
	SetPaneText(3,strAxis[1],TRUE);

	GetPaneInfo(5,nID,nStyle,cxWidth);
	SetPaneText(5,strAxis[2],TRUE);
    //////////////////////////////////////////////////
	sprintf(buf,"%.2f %s",xWorld,Unit[nUnitIndex]);
	SetPaneText(2,str=buf,TRUE);
	sprintf(buf,"%.2f %s",yWorld,Unit[nUnitIndex]);
	SetPaneText(4,str=buf,TRUE);
	sprintf(buf,"%.2f %s",zWorld,Unit[nUnitIndex]);
	SetPaneText(6,str=buf,TRUE);
	////////////////////////////////////////////// 
	///////////////////////////////////////////////////////// Drawing Mode/Tool
	int nMeshType			= pObjectMgr->GetMeshType();
	///////////////////////////////////////////////////////// ElemBox
	if (pWnd->IsIGenBoxActive())
	{	
		int nID = pWnd->GetActiveObjectType();
		if(nID<0) return; 
/*		
		////////////////////////////////////////////// object 
		for (int i = 0; i<nMax_ElemTypes; i++)
		{
			if(nID == ElTypes[i].num)
			{
				str += ElTypes[i].ObjName; 
//				AfxMessageBox(str);
//				return;
			}
		} 
*/		
		if(pObjectMgr->IsMeshGenOn())
			str = strMeshType[nMeshType] + " ";
		else
			str = "No FEM Mesh Generation ";	
		/////////////////////////////////////////// Tool
		if((nID = pWnd->GetActiveToolType())>=0)
		{
			for (int j = 0; j<nMax_ElemTypes; j++)
			{
				if(nID == ElTypes[j].num)
					str += ElTypes[j].ObjName;
			}
        }
        ///////////////////////////////////////////

	}		
	///////////////////////////////////////////////////////// DrawBox	
	if (pWnd->IsDrawBoxActive())
	{	
		int nID = pWnd->GetActiveObjectType();// 
		if(nID<0) return;
/*
		/////////////////////////////////////////// Object
		for (int i = 0; i<nMax_DBoxTypes; i++)
		{
			if(nID == DbTypes[i].num)
			{

				str += DbTypes[i].ObjName;

			} 
		}
*/			
		/////////////////////////////////////////// Tool
		if((nID = pWnd->GetActiveToolType())>=0)
		{
			for (int j = 0; j<nMax_DBoxTypes; j++)
			{
				if(nID == DbTypes[j].num)
					str += DbTypes[j].ObjName;
			}	 
        }
        ///////////////////////////////////////////

	}			
	////////////////////////
	SetPaneText(0,str,TRUE); 
	////////////////////////
}

///////////////////////////// end of module ///////////////////

