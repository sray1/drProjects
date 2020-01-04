// CurGeomPage.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "CurGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurGeomPage property page

IMPLEMENT_DYNCREATE(CCurGeomPage, CPropertyPage)

CCurGeomPage::CCurGeomPage() : CPropertyPage(CCurGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CCurGeomPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCurGeomPage::~CCurGeomPage()
{
}

void CCurGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurGeomPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCurGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurGeomPage message handlers
