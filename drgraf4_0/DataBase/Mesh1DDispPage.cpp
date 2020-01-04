// Mesh1DDispPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Mesh1DDispPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh1DDispPage property page

IMPLEMENT_DYNCREATE(CMesh1DDispPage, CPropertyPage)

CMesh1DDispPage::CMesh1DDispPage() : CPropertyPage(CMesh1DDispPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh1DDispPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh1DDispPage::~CMesh1DDispPage()
{
}

void CMesh1DDispPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh1DDispPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh1DDispPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh1DDispPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh1DDispPage message handlers

BOOL CMesh1DDispPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
