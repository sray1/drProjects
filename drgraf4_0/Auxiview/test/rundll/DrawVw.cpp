// DrawVw.cpp : implementation file
//

#include "stdafx.h"
#include "rundll.h"
#include "DrawVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawVw

IMPLEMENT_DYNCREATE(CDrawVw, CView)

CDrawVw::CDrawVw()
{
	m_bDrag = FALSE;
}

CDrawVw::~CDrawVw()
{
}


BEGIN_MESSAGE_MAP(CDrawVw, CView)
	//{{AFX_MSG_MAP(CDrawVw)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawVw drawing

void CDrawVw::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	CRect rect;
	CPen pen, *oldpen;
	CBrush br,*oldbr;

	pen.CreatePen(PS_SOLID,2,RGB(0,255,0));
	br.CreateSolidBrush(RGB(0,0,255));
	oldpen = pDC->SelectObject(&pen);
	oldbr = pDC->SelectObject(&br);
	GetClientRect(&rect);
	rect.InflateRect(-1,-1);
	pDC->Rectangle(&rect);
	pDC->SelectObject(oldpen);
	pen.DeleteObject();
	pDC->SelectObject(oldbr);
	br.DeleteObject();
	pen.CreatePen(PS_SOLID,2,RGB(255,255,0));
	oldpen = pDC->SelectObject(&pen);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawVw diagnostics

#ifdef _DEBUG
void CDrawVw::AssertValid() const
{
	CView::AssertValid();
}

void CDrawVw::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawVw message handlers

void CDrawVw::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	m_OldPt = point;
	m_NewPt = point;
	m_bDrag = TRUE;

	CView::OnLButtonDown(nFlags, point);
}

void CDrawVw::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	if (m_bDrag == TRUE)
		m_bDrag = FALSE;

	Invalidate();
	UpdateWindow();
	
	CClientDC dc(this);

	CRect oldRect(m_OldPt,m_NewPt);       // erase old focus rect.
	oldRect.NormalizeRect();
	dc.DrawFocusRect(&oldRect);

	CPen pen(PS_DASH, 1, RGB(255,255,255));	
	CPen *oldpen = dc.SelectObject(&pen);
	CRect rect(m_OldPt,point);
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	CBrush *oldbrush = dc.SelectObject(&brush);

	dc.Rectangle(&rect);

	dc.SelectObject(oldpen);
	dc.SelectObject(oldbrush);
	pen.DeleteObject();
	brush.DeleteObject();

	CView::OnLButtonUp(nFlags, point);

}

void CDrawVw::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDrag)
	{
		CClientDC dc(this);

		CRect oldRect(m_OldPt,m_NewPt), newRect(m_OldPt,point);
		oldRect.NormalizeRect();
		newRect.NormalizeRect();
		dc.DrawFocusRect(&oldRect);
		dc.DrawFocusRect(&newRect);

		m_NewPt = point;		// save current mouse location
	}		

	CView::OnMouseMove(nFlags, point);
}

void CDrawVw::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnRButtonDown(nFlags, point);
}

void CDrawVw::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CClientDC dc(this);
	CBitmap bitmap;
	BITMAP bm;
	CDC memDC;

	memDC.CreateCompatibleDC(&dc);

	bitmap.LoadBitmap(IDB_BITMAP1);
	bitmap.GetBitmap(&bm);
//	bitmap.CreateCompatibleBitmap(&memDC,bm.bmWidth,bm.bmHeight);

	memDC.SelectObject(&bitmap);

	dc.StretchBlt(point.x, point.y, 2 * bm.bmWidth, 2 * bm.bmHeight,
			  &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY); 

	bitmap.DeleteObject();

	CView::OnRButtonUp(nFlags, point);
}

int CDrawVw::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
