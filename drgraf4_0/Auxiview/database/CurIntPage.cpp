// CurIntPage.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "CurIntPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurIntPage property page

IMPLEMENT_DYNCREATE(CCurIntPage, CPropertyPage)

CCurIntPage::CCurIntPage() : CPropertyPage(CCurIntPage::IDD)
{
	//{{AFX_DATA_INIT(CCurIntPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCurIntPage::~CCurIntPage()
{
}

void CCurIntPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurIntPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurIntPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCurIntPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurIntPage message handlers
