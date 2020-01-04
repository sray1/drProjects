// HistVw.cpp: implementation of the CHistVw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "rundll.h"
#include "HistVw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CHistVw, CDrawVw)


CHistVw::CHistVw()
{

}

CHistVw::~CHistVw()
{

}


BEGIN_MESSAGE_MAP(CHistVw, CDrawVw)
	//{{AFX_MSG_MAP(CHistVw)
		// NOTE - the ClassWizard will add and remove mapping macros here.

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CHistVw::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	// TODO: Add your specialized code here and/or call the base class
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
	
	CPen *pOldpen;
	pen.CreatePen(PS_SOLID,10,RGB(192,192,192));
	pOldpen = pDC->SelectObject(&pen);

	pDC->MoveTo(0,0);
	pDC->LineTo(50,50);

	pDC->SelectObject(pOldpen);
	pen.DeleteObject();

	
	
}


/////////////////////////////////////////////////////////////////////////////
// CHistVw diagnostics

#ifdef _DEBUG
void CHistVw::AssertValid() const
{
	CView::AssertValid();
}

void CHistVw::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistVw message handlers


void CHistVw::OnInitialUpdate() 
{

	CDrawVw::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

}

void CHistVw::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}
