// colorsqu.cpp : implementation file
//
#include "stdafx.h"
#include "afxext.h"      // for CStatic

#include "drgraf.h"
#include "drgrafrm.h"
////////////////////
#include "curdef.h"
/////////////////////
#include "StatCntl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////
#define	new					DEBUG_NEW
#define	BUFF_SIZE			1024
//
#define	CR_YELLOW			RGB(255,255,0)
/////////////////////////////////////////////////////////////////////////////
// CStatCntl
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CStatCntl, CWnd)
	//{{AFX_MSG_MAP(CStatCntl)
	ON_WM_PAINT()  
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP() 
//	ON_WM_MOUSEACTIVATE() 

IMPLEMENT_DYNCREATE(CStatCntl, CWnd)
///////////////////////////////////////////////////////////////////
CStatCntl::CStatCntl()
{
	m_bTrackMove     = FALSE;
};

CStatCntl::~CStatCntl()
{
	if(m_hWnd != NULL)	
	DestroyWindow();	
};

BOOL CStatCntl::Create(CWnd* pParentWnd,CRect rect,UINT uControlID)
{
	ASSERT(pParentWnd != NULL);
    ////////////////////////////////////////////////////////////////
	m_pParentWnd	= pParentWnd;
	m_ControlID		= uControlID;
	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWndStat = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx(	0,
	//					"AfxWnd",
						strAfxWndStat,
						NULL,
						WS_POPUP,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_ElemBOX*/,
						NULL
					);
	return bOk;				
}

BOOL CStatCntl::Create(CWnd* pParentWnd,CRect rect,UINT uControlID,UINT uParentID)
{
	m_ParentID		= uParentID;
	m_ControlID		= uControlID;
	m_pParentWnd	= pParentWnd;
	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWndStat = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx(	0,
	//					"AfxWnd",
						strAfxWndStat,
						NULL,
						WS_POPUP,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_ElemBOX*/,
						NULL
					);
	return bOk;				
}
/////////////////////////////////////////////////////////////////////////////
void CStatCntl::OnPaint()
{
	//////////
//	return;	// do nothing
	//////////

	CPaintDC dc(this); // device context for painting
	
	CRect clientRect;
	GetClientRect(&clientRect);
	CBrush	Br;
	CBrush* pBrOld;
	CPen	Pen;
	CPen*	pPenOld;
	/////////////////////////////////
	POINT ptCursor;
	GetCursorPos(&ptCursor);		// Screen Coords
	ClientToScreen(&clientRect);	// Screen Coords
	if(clientRect.PtInRect(ptCursor) )
		m_crBrColor = CR_YELLOW;
	else
		m_crBrColor = m_crBrColorDfalt;
	ScreenToClient(&clientRect);	// Back to Client Coords
	///////////////////////////////////

	Br.CreateSolidBrush(m_crBrColor);		//
    pBrOld	= dc.SelectObject(&Br);
	///////
   	Pen.CreatePen (m_nPenStyle,m_nPenWidth,m_crPenColor);	//
   	pPenOld = dc.SelectObject(&Pen);
	////////////////////////////
	dc.Rectangle(&clientRect);
	////////////////////////////
    dc.SelectObject(pBrOld);
	Pen.DeleteObject();
	Br.DeleteObject();
	///////////////////////////////////////// TextOut
 	// set font.
    CFont	Font;
    CFont*	pOldFont;
	Font.DeleteObject();
	////////////////
	Font.CreateFontIndirect(&m_lf);
	pOldFont = (CFont*)(dc.SelectObject(&Font));
	//////////////////////////////// Color
	dc.SetTextColor(m_crTextColor);	   	
	//////////////////////////////// Mode
	dc.SetBkMode(TRANSPARENT);	   	
    //////////////////////////////// Label Out
	CPoint	pt;
	CSize	szText1, szText2;
	////////////////////////////////////////////////////////// Show in 2Lines, if Needed
	CString temp1,temp2;
	int nIndex = m_strText.Find("@");
	temp1 = "";
	if(nIndex>=0)
	{
		temp1	= m_strText.Mid(0,nIndex);
		szText1 = dc.GetTextExtent(temp1);
	}
	temp2	= m_strText.Mid(nIndex+1,m_strText.GetLength());
	szText2 = dc.GetTextExtent(temp2);
	////////////////////////////////////////////////////////// One Line
	if(nIndex<0)
	{
		pt.x = (clientRect.left + clientRect.right - szText2.cx)/2;
		pt.y = (clientRect.top + clientRect.bottom - szText2.cy)/2;
		dc.TextOut(pt.x,pt.y,temp2);
	}
	else
	{
		pt.x = (clientRect.left + clientRect.right - szText1.cx)/2;
//		pt.y = (clientRect.top + clientRect.bottom - szText1.cy)/2 - szText1.cy;
		pt.y = (clientRect.top + clientRect.bottom)/2 - szText1.cy;
		dc.TextOut(pt.x,pt.y,temp1);

		pt.x = (clientRect.left + clientRect.right - szText2.cx)/2;
//		pt.y = (clientRect.top + clientRect.bottom - szText2.cy)/2 + szText2.cy;
		pt.y = (clientRect.top + clientRect.bottom)/2 + 3;
		dc.TextOut(pt.x,pt.y,temp2);
	}
	//////////////////////////////// Get Original Font back
	if(pOldFont != NULL)
		dc.SelectObject(pOldFont);
	Font.DeleteObject();
	////////////////////
/*
// color background 

   GetClientRect(&Rect);
   dc.FillRect(&Rect,Brush.FromHandle((HBRUSH)::GetStockObject(LTGRAY_BRUSH)) );

// Create inner border rectangle

   	Rect.left   += 2;
   	Rect.top    += 2;
   	Rect.right  -= 2;
   	Rect.bottom -= 2;		

   	PtrOldBrush= (CBrush*)dc.SelectStockObject(NULL_BRUSH); 
  	dc.Rectangle(&Rect);
   	dc.SelectObject(PtrOldBrush);
   	Brush.DeleteObject();
	/////////////////////////////
*/   	
			
}
void CStatCntl::ReCalcLayOut()
{
	CRect BoxRect;
	/////////////////////////////////////////
	BoxRect.left	= m_ptLeftTop.x;
	BoxRect.right	= BoxRect.left + m_nWidth; 
	BoxRect.top		= m_ptLeftTop.y;
	BoxRect.bottom	= BoxRect.top + m_nHeight;
	///////
	SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
}

void CStatCntl::OnLButtonDown(UINT nFlags, CPoint point)
{
	///////////////////////////////////////////////// 
	if (point.y <= 1)
	{
		m_bTrackMove = TRUE;
		m_ptMouse = point;
		SetCapture();
		ClientToScreen(&point);
		InvertTracker(point);
		m_ptLast = point;
	}
}

void CStatCntl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bTrackMove)
	{
		m_bTrackMove=FALSE;
		ReleaseCapture();
		InvertTracker(m_ptLast);
		ClientToScreen(&point);
		SetWindowPos(NULL, point.x-m_ptMouse.x, point.y-m_ptMouse.y,0,0,
				SWP_NOZORDER|SWP_NOSIZE);
		ShowWindow(SW_SHOW);
	}
} 

void CStatCntl::OnMouseMove(UINT nFlags, CPoint point)
{
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	HCURSOR hCursor;
	/////////////////////////////////////////////////////////////////// 
	if (m_bTrackMove)
	{
		ClientToScreen(&point);
		InvertTracker(m_ptLast);
		m_ptLast = point;
		InvertTracker(m_ptLast);
	}
	else
	{
		///////////////////
		switch(m_ControlID)
		{
//			case IDS_GEN_MESHMODE:
			case IDS_BLINESTAT:
			case IDS_AUTOACCEPTSTAT: 
			case IDS_SINGLESEGSTAT:	
			case IDS_SPAWNSTAT:
			case IDS_SNAPSTAT:
			case IDS_OPERSTAT:
				///
				pWnd->SetLastStatCntlHit(this);
				Invalidate();
				UpdateWindow();
				///
				hCursor = AfxGetApp()->LoadCursor(IDC_BUTTON);
				::SetCursor(hCursor);
				/////////////////////
//				pWnd->GetMouseMgr()->SetViewCursor(UPARROW);
				break;
			default:
				break;
		}
	} 
	///////////////
}

void CStatCntl::InvertTracker(CPoint point)
{
	CRect rectFrame;
	GetWindowRect(&rectFrame);
	CDC dc;
	dc.Attach(::GetDC(NULL));
	
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y, rectFrame.Width(),
			2, PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x+rectFrame.Width(), point.y-m_ptMouse.y,
			2, rectFrame.Height(), PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y+rectFrame.Height(),
			rectFrame.Width()+2, 2, PATINVERT);
	dc.PatBlt(point.x-m_ptMouse.x, point.y-m_ptMouse.y+2, 2,
			rectFrame.Height()-2, PATINVERT);
	::ReleaseDC(NULL,dc.Detach());
}

void CStatCntl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();	
//	CWnd::OnRButtonDown(nFlags, point);
}

void CStatCntl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CDrGrafFrame* pWnd	= (CDrGrafFrame*)AfxGetMainWnd();
	CString strCur;
	///////////////////////////////////////////////////////////////////
	ReleaseCapture();
	///////////////////
	switch(m_ControlID)
	{
	
//		case IDS_MODESTAT:
//			GetParent()->SendMessage(ID_OPTION_MODE,pWnd->GetCurrentMode());	// UserMessage
//			break;
		case IDS_OPERSTAT:
			if(pWnd->GetMouseMgr()->IsCurrentProcessDone())
				pWnd->GetOperBox()->ShowWindow((pWnd->GetOperBox()->GetStyle() & WS_VISIBLE) == 0);
			else
			{
				AfxMessageBox("Please First\nFinish the Current Process!!");
				return;
			}
			///
			strCur = "Please Select an Operation Type";
			pWnd->GetCurrStat()->SetText(strCur);
			pWnd->GetCurrStat()->Invalidate();
			pWnd->GetCurrStat()->UpdateWindow();
			///
			break;
		case IDS_BLINESTAT:
			GetParent()->SendMessage(WM_COMMAND,IDM_OPTION_BLINEON);
			break;
		case IDS_AUTOACCEPTSTAT: 
			GetParent()->SendMessage(WM_COMMAND,IDM_OPTION_AUTOACCEPTON);
			break;
		case IDS_SINGLESEGSTAT: 
			GetParent()->SendMessage(WM_COMMAND,IDM_OPTION_SINGLESEGON);
			break;
		case IDS_SPAWNSTAT:
			GetParent()->SendMessage(WM_COMMAND,IDM_OPTION_SPAWNON);
			break;
		case IDS_SNAPSTAT:
			GetParent()->SendMessage(WM_COMMAND,IDM_OPTION_SNAPON);
			break;
		default:
			CWnd::OnRButtonUp(nFlags, point);
	}
}

void CStatCntl::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	//////////////////////////
//	m_crBrColor	= m_crBrColorDfalt;
	Invalidate();
	UpdateWindow();
	
}

void CStatCntl::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	//////////////////////////
//	m_crBrColor		= CR_YELLOW;
	Invalidate();
	UpdateWindow();
	
}
//////////////////////////////////// end of module //////////////////////
