// Mesh2DTopoPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Mesh2DTopoPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh2DTopoPage property page

IMPLEMENT_DYNCREATE(CMesh2DTopoPage, CPropertyPage)

CMesh2DTopoPage::CMesh2DTopoPage() : CPropertyPage(CMesh2DTopoPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh2DTopoPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh2DTopoPage::~CMesh2DTopoPage()
{
}

void CMesh2DTopoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh2DTopoPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh2DTopoPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh2DTopoPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh2DTopoPage message handlers

BOOL CMesh2DTopoPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
