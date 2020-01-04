// CNodeDebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "NodeDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeDebugPage property page

IMPLEMENT_DYNCREATE(CNodeDebugPage, CPropertyPage)

CNodeDebugPage::CNodeDebugPage() : CPropertyPage(CNodeDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CNodeDebugPage::~CNodeDebugPage()
{
}

void CNodeDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeDebugPage message handlers
