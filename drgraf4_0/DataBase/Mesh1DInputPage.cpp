// Mesh1DInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh1DSheet.h"
////////////////////////
#include "Mesh1DInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh1DInputPage property page

IMPLEMENT_DYNCREATE(CMesh1DInputPage, CPropertyPage)

CMesh1DInputPage::CMesh1DInputPage() : CPropertyPage(CMesh1DInputPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh1DInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh1DInputPage::~CMesh1DInputPage()
{
}

void CMesh1DInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh1DInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh1DInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh1DInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh1DInputPage message handlers
