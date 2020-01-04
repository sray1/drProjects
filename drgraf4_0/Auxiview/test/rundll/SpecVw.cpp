// SpecVw.cpp: implementation of the CSpecVw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "rundll.h"
#include "SpecVw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CSpecVw, CDrawVw)


CSpecVw::CSpecVw()
{

}

CSpecVw::~CSpecVw()
{

}


BEGIN_MESSAGE_MAP(CSpecVw, CDrawVw)
	//{{AFX_MSG_MAP(CSpecVw)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CSpecVw::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	CRect rect;
	CPen pen, *oldpen;
	CBrush br,*oldbr;

	pen.CreatePen(PS_SOLID,2,RGB(0,255,0));
	br.CreateSolidBrush(RGB(255,0,255));
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
// CSpecVw diagnostics

#ifdef _DEBUG
void CSpecVw::AssertValid() const
{
	CView::AssertValid();
}

void CSpecVw::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpecVw message handlers
