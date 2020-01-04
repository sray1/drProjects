// PatchDispPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "PatchDispPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatchDispPage property page

IMPLEMENT_DYNCREATE(CPatchDispPage, CPropertyPage)

CPatchDispPage::CPatchDispPage() : CPropertyPage(CPatchDispPage::IDD)
{
	//{{AFX_DATA_INIT(CPatchDispPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPatchDispPage::~CPatchDispPage()
{
}

void CPatchDispPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPatchDispPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPatchDispPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPatchDispPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatchDispPage message handlers

BOOL CPatchDispPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
