// DrListVu.cpp: implementation of the CDrListVu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "database.h"
#include <afxcview.h>
#include "DrListVu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CDrListVu, CListView)


CDrListVu::CDrListVu()
{

}

CDrListVu::~CDrListVu()
{

}


BEGIN_MESSAGE_MAP(CDrListVu, CListView)
	//{{AFX_MSG_MAP(CDrListVu)
		// NOTE - the ClassWizard will add and remove mapping macros here.

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDrListVu::OnDraw(CDC* pDC) 
{
	
}


/////////////////////////////////////////////////////////////////////////////
// CDrListVu diagnostics

#ifdef _DEBUG
void CDrListVu::AssertValid() const
{
	CView::AssertValid();
}

void CDrListVu::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrListVu message handlers


void CDrListVu::OnInitialUpdate() 
{

	
	// TODO: Add your specialized code here and/or call the base class

}

void CDrListVu::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}
