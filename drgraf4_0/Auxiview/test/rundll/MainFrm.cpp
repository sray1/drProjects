// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "rundll.h"
#include "rundllDoc.h"
#include "def_usr.h"
#include "splitter.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_MESSAGE(UM_OPEN_FRAME,OnOpenFrame)
	ON_MESSAGE(UM_ANIMATE_BM,OnAnimateBM)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bFirst = TRUE;	
	m_BMSrc.LoadBitmap(IDB_BITMAP1);
	m_BMSave.LoadBitmap(IDB_BITMAP1);   // make BMSave same size as BMSrc
}

CMainFrame::~CMainFrame()
{
	m_BMSrc.DeleteObject();
	m_BMSave.DeleteObject();   
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	RecalcLayout();

// Create Button
	CRect rect(0,0,0,0);

	ASSERT(m_MyButton.Create(WS_CHILD | WS_VISIBLE, rect, this, IDC_MYBUTTON));
	GetClientRect(&rect);
	int xext = rect.Width();
	int yext = rect.Height();
	int margin = 200;    // space between slider control & edge of client area
	int l_len = 150; // length of long edge of slider control    
	int s_len = 30; // length of short edge of slider control
	m_MyButton.SetWindowPos(&wndTop, (xext - l_len)/2, yext - s_len - margin,
								l_len, s_len, (UINT)NULL);
	m_MyButton.SetWindowText("Open Frame");

// Create Animate Button

	ASSERT(m_AnimBut.Create(WS_CHILD | WS_VISIBLE, rect, this, IDC_ANIMBUT));
	GetClientRect(&rect);
	m_AnimBut.SetWindowPos(&wndTop, (xext - l_len)/2, yext - s_len - 2*margin,
								l_len, s_len, (UINT)NULL);
	m_AnimBut.SetWindowText("Animate");



// Create slider controls
	m_wndHSlider.Create(TBS_HORZ | TBS_AUTOTICKS, rect, this, IDC_HSLIDER);
	m_wndVSlider.Create(TBS_VERT | TBS_AUTOTICKS, rect, this, IDC_VSLIDER);
	m_wndHSlider.SetRange(0,20);
	m_wndVSlider.SetRange(0,20);

	margin = 30;    // space between slider control & edge of client area
	l_len = 150; // length of long edge of slider control    
	s_len = 30; // length of short edge of slider control
	m_wndHSlider.SetWindowPos(&wndTop, (xext - l_len)/2, yext - s_len - margin,
								l_len, s_len, (UINT)NULL);
	m_wndVSlider.SetWindowPos(&wndTop, xext - s_len - margin, (yext - l_len)/2,
								s_len, l_len, (UINT)NULL);

	m_HSliderPos = 10;
	m_VSliderPos = 10;
	m_HSliderOldPos = 10;
	m_VSliderOldPos = 10;
	m_wndHSlider.SetPos(m_HSliderPos);
	m_wndVSlider.SetPos(m_VSliderPos);

	m_wndHSlider.ShowWindow(TRUE);
	m_wndVSlider.ShowWindow(TRUE);

//	MoveBitMap();
	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if ((CSliderCtrl*)pScrollBar == &m_wndVSlider)
	{

/***
		int nCurrentPos;
		////////////////

		switch(nSBCode)
		{
			case TB_LINEUP:
//				nCurrentPos = nPos;
				m_VSliderOldPos = m_VSliderPos;
				m_VSliderPos--;
				MoveBitMap();
				return;
			case TB_LINEDOWN:
//				nCurrentPos = nPos;
				m_VSliderOldPos = m_VSliderPos;
				m_VSliderPos++;
				MoveBitMap();
				return;
			case TB_BOTTOM:
//				nCurrentPos = nPos;
				return;
			case TB_ENDTRACK:
//				nCurrentPos = nPos;
				break;
			case TB_PAGEUP:
//				nCurrentPos = nPos;
				return;
			case TB_PAGEDOWN:
//				nCurrentPos = nPos;
				return;
			case TB_TOP:
//				nCurrentPos = nPos;
				return;
			case TB_THUMBPOSITION:
				nCurrentPos = nPos;
				break;
			case TB_THUMBTRACK:
				nCurrentPos = nPos;
				break;
			default:
				nCurrentPos = nPos;
				break;
		}

		m_VSliderOldPos = m_VSliderPos;
		m_VSliderPos = nCurrentPos;
		MoveBitMap();
***/

// No matter what the message is, perform the following steps:
//	1. check if slider position has changed
//  2. if yes, save old position & invalidate client area
	
		int newpos = m_wndVSlider.GetPos();
		if (m_VSliderPos != newpos)
		{
			m_HSliderOldPos = m_HSliderPos;
			m_VSliderOldPos = m_VSliderPos;
			m_VSliderPos = newpos;
			MoveBitMap();
		}

	}
	else
		CMDIFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMainFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if ((CSliderCtrl*)pScrollBar == &m_wndHSlider)
	{
		int newpos = m_wndHSlider.GetPos();
		if (m_HSliderPos != newpos)
		{
			// update new position
			m_HSliderOldPos = m_HSliderPos;
			m_VSliderOldPos = m_VSliderPos;
			m_HSliderPos	= newpos;
			MoveBitMap();
			
		}
	}
	else
		CMDIFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMainFrame::MoveBitMap() 
{
	CClientDC dc(this); // device context for painting
	BITMAP BM;
	
//	InvalidateRect(NULL,FALSE);
//	UpdateWindow();

//	UpdateWindow();
	//////////////////////////////
	// load bitmap & place into DC
	m_BMSrc.GetBitmap(&BM);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	CRect rect;
	int x,y;
	GetClientRect(&rect);
	dc.DPtoLP(&rect);
	int HSliderMax = m_wndHSlider.GetRangeMax();
	int VSliderMax = m_wndVSlider.GetRangeMax();

	// restore old bitmap
	if (m_bFirst)
		m_bFirst = FALSE;
	else
	{
		ASSERT(m_HSliderSavePos == m_HSliderOldPos);
		ASSERT(m_VSliderSavePos == m_VSliderOldPos);

		MemDC.SelectObject(m_BMSave);
		x = (int)( (double)rect.Width() * 
			       ((double)m_HSliderOldPos / (double)HSliderMax) );
		y = (int)( (double)rect.Height() * 
				   ((double)m_VSliderOldPos / (double)VSliderMax) );
		dc.BitBlt( x, y, BM.bmWidth, BM.bmHeight, &MemDC, 0, 0, SRCCOPY);
	}

	// save screen at new bitmap location
	m_HSliderSavePos = m_HSliderPos;          // DEBUGGING
	m_VSliderSavePos = m_VSliderPos;          // DEBUGGING

	MemDC.SelectObject(m_BMSave);
	x = (int)( (double)rect.Width() * 
			   ((double)m_HSliderPos / (double)HSliderMax) );
	y = (int)( (double)rect.Height() * 
			   ((double)m_VSliderPos / (double)VSliderMax) );
	MemDC.BitBlt( 0, 0, BM.bmWidth, BM.bmHeight, &dc, x, y, SRCCOPY);

	// draw new bitmap
	MemDC.SelectObject(m_BMSrc);
	dc.BitBlt( x, y, BM.bmWidth, BM.bmHeight, &MemDC, 0, 0, MERGECOPY);


}


afx_msg long CMainFrame::OnOpenFrame(UINT wParam, UINT lParam)
{

	CWinApp *pApp = AfxGetApp();
	POSITION pos = pApp->GetFirstDocTemplatePosition();
	CDocTemplate *pTemp = pApp->GetNextDocTemplate(pos);
	CRundllDoc *pDoc = new CRundllDoc;
	pTemp->AddDocument(pDoc);
	CSplitterFrame *pFrame = (CSplitterFrame*)(pTemp->CreateNewFrame(pDoc,NULL));
//	pFrame->ShowWindow(TRUE);

	pFrame->InitialUpdateFrame(pDoc,TRUE);
	//////////
	return 0L;
}

afx_msg long CMainFrame::OnAnimateBM(UINT wParam, UINT lParam)
{
	//////////////////////////////////////
	AnimateBitMap_Horizontal();
	//////////
	return 0L;
}


void CMainFrame::AnimateBitMap_Horizontal() 
{
	int HSliderMax = m_wndHSlider.GetRangeMax();
	for(int i=0;i<3*HSliderMax;i++)
	{
		int newpos = m_wndHSlider.GetPos();
		newpos++;// onestep ahead
		if(newpos == HSliderMax)
			newpos = 0;	
		if (m_HSliderPos != newpos)
		{
			// update new position
			m_HSliderOldPos = m_HSliderPos;
			m_HSliderPos	= newpos;
			MoveBitMap();
			m_wndHSlider.SetPos(m_HSliderPos);
		}
		/////////////////////////////////////////// delay
		for(long j=0;j<3500000;j++)
			;	// do nothing
	}
}

