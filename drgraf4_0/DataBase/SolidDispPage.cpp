// SolidDispPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "SolidDispPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSolidDispPage property page

IMPLEMENT_DYNCREATE(CSolidDispPage, CPropertyPage)

CSolidDispPage::CSolidDispPage() : CPropertyPage(CSolidDispPage::IDD)
{
	//{{AFX_DATA_INIT(CSolidDispPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSolidDispPage::~CSolidDispPage()
{
}

void CSolidDispPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSolidDispPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSolidDispPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSolidDispPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSolidDispPage message handlers

BOOL CSolidDispPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
