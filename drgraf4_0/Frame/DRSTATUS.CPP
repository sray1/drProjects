// drstatus.cpp : implementation file
//

#include "drstatus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////
// CDrStatusBar

CDrStatusBar::CDrStatusBar()
{
}

CDrStatusBar::~CDrStatusBar()
{
}

/******************

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

struct AFX_STATUSPANE
{
	UINT    nID;       | 	 r *  M    �
  l    	 �*       �
  p    	 �*       �  �
  �r ���
 	  *      �    	 �*       �
  "t    	  *  W    �
  $x   �
   making a pane 4 pixels wider
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

void CDrStatusBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{ 
}
//////////////////////////////
CTopStatusBar::CTopStatusBar()
{
//	Init();
}

int CTopStatusBar::Init()
{
	CString str;
	UINT nID, nStyle;
	int cxWidth;

	
	GetPaneInfo(0,nID,nStyle,cxWidth);
	SetPaneInfo(0,nID,SBPS_POPOUT,70);
	SetPaneText(0,"DRAWING:",TRUE);

	GetPaneInfo(1,nID,nStyle,cxWidth);
	SetPaneInfo(1,nID,SBPS_NORMAL,100);
	 
	GetPaneInfo(2,nID,nStyle,cxWidth);
	SetPaneInfo(2,nID,SBPS_POPOUT,50);
	SetPaneText(2,"LAYER:",TRUE);
	 
	GetPaneInfo(3,nID,nStyle,cxWidth);
	SetPaneInfo(3,nID,SBPS_NORMAL,30);
	
	GetPaneInfo(4,nID,nStyle,cxWidth);
	SetPaneInfo(4,nID,SBPS_POPOUT,40);
	SetPaneText(4,"UNIT:",TRUE);
	
	GetPaneInfo(5,nID,nStyle,cxWidth);
	SetPaneInfo(5,nID,SBPS_NORMAL,150);
	 
	GetPaneInfo(7,nID,nStyle,cxWidth);
	SetPaneInfo(7,nID,SBPS_POPOUT,40); 
	SetPaneText(7,"TIME:",TRUE);
	
	GetPaneInfo(8,nID,nStyle,cxWidth);
	SetPaneInfo(8,nID,SBPS_NORMAL,70); 
	
	GetPaneInfo(9,nID,nStyle,cxWidth);
	SetPaneInfo(9,nID,SBPS_POPOUT,40); 
	SetPaneText(9,"DATE:",TRUE); 
	
	GetPaneInfo(10,nID,nStyle,cxWidth);
	SetPaneInfo(10,nID,SBPS_NORMAL,90); 
	
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
//////////////////////////////
CBotStatusBar::CBotStatusBar()
{
//	Init();
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
///////////////////////////// end of module ///////////////////

