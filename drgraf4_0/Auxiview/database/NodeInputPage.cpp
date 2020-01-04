// CNodeInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "NodeInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeInputPage property page

IMPLEMENT_DYNCREATE(CNodeInputPage, CPropertyPage)

CNodeInputPage::CNodeInputPage() : CPropertyPage(CNodeInputPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CNodeInputPage::~CNodeInputPage()
{
}

void CNodeInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeInputPage message handlers
