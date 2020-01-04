// Mesh1DTopoPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh1DSheet.h"
////////////////////////
#include "Mesh1DTopoPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh1DTopoPage property page

IMPLEMENT_DYNCREATE(CMesh1DTopoPage, CPropertyPage)

CMesh1DTopoPage::CMesh1DTopoPage() : CPropertyPage(CMesh1DTopoPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh1DTopoPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh1DTopoPage::~CMesh1DTopoPage()
{
}

void CMesh1DTopoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh1DTopoPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh1DTopoPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh1DTopoPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh1DTopoPage message handlers
