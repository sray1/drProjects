// CNodeSuppPage.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "NodeSuppPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeSuppPage property page

IMPLEMENT_DYNCREATE(CNodeSuppPage, CPropertyPage)

CNodeSuppPage::CNodeSuppPage() : CPropertyPage(CNodeSuppPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeSuppPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CNodeSuppPage::~CNodeSuppPage()
{
}

void CNodeSuppPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeSuppPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeSuppPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeSuppPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeSuppPage message handlers
