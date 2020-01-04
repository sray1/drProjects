// CNodeGeomPage.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "NodeGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeGeomPage property page

IMPLEMENT_DYNCREATE(CNodeGeomPage, CPropertyPage)

CNodeGeomPage::CNodeGeomPage() : CPropertyPage(CNodeGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeGeomPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CNodeGeomPage::~CNodeGeomPage()
{
}

void CNodeGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeGeomPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeGeomPage message handlers
