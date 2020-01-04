// Mesh2DDispPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Mesh2DDispPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh2DDispPage property page

IMPLEMENT_DYNCREATE(CMesh2DDispPage, CPropertyPage)

CMesh2DDispPage::CMesh2DDispPage() : CPropertyPage(CMesh2DDispPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh2DDispPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh2DDispPage::~CMesh2DDispPage()
{
}

void CMesh2DDispPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh2DDispPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh2DDispPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh2DDispPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh2DDispPage message handlers

BOOL CMesh2DDispPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
