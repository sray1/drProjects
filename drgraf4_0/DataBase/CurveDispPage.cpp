// CurveDispPage.cpp : implementation file
//

#include "stdafx.h"
#include "CurveDispPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveDispPage property page

IMPLEMENT_DYNCREATE(CCurveDispPage, CPropertyPage)

CCurveDispPage::CCurveDispPage() : CPropertyPage(CCurveDispPage::IDD)
{
	//{{AFX_DATA_INIT(CCurveDispPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCurveDispPage::~CCurveDispPage()
{
}

void CCurveDispPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveDispPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurveDispPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCurveDispPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveDispPage message handlers

BOOL CCurveDispPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
