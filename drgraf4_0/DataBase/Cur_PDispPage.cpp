// Cur_PDisp.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Cur_PDispPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCur_PDispPage property page

IMPLEMENT_DYNCREATE(CCur_PDispPage, CPropertyPage)

CCur_PDispPage::CCur_PDispPage() : CPropertyPage(CCur_PDispPage::IDD)
{
	//{{AFX_DATA_INIT(CCur_PDispPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCur_PDispPage::~CCur_PDispPage()
{
}

void CCur_PDispPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCur_PDispPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCur_PDispPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCur_PDispPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCur_PDispPage message handlers

BOOL CCur_PDispPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
