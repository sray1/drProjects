// Mesh3DDispPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Mesh3DDispPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh3DDispPage property page

IMPLEMENT_DYNCREATE(CMesh3DDispPage, CPropertyPage)

CMesh3DDispPage::CMesh3DDispPage() : CPropertyPage(CMesh3DDispPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh3DDispPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh3DDispPage::~CMesh3DDispPage()
{
}

void CMesh3DDispPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh3DDispPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh3DDispPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh3DDispPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh3DDispPage message handlers

BOOL CMesh3DDispPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
