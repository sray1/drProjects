// CNodeLoadPage.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "NodeLoadPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeLoadPage property page

IMPLEMENT_DYNCREATE(CNodeLoadPage, CPropertyPage)

CNodeLoadPage::CNodeLoadPage() : CPropertyPage(CNodeLoadPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeLoadPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CNodeLoadPage::~CNodeLoadPage()
{
}

void CNodeLoadPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeLoadPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeLoadPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeLoadPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeLoadPage message handlers
