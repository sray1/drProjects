// CNodeRestPage.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "NodeRestPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeRestPage property page

IMPLEMENT_DYNCREATE(CNodeRestPage, CPropertyPage)

CNodeRestPage::CNodeRestPage() : CPropertyPage(CNodeRestPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeRestPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CNodeRestPage::~CNodeRestPage()
{
}

void CNodeRestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeRestPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeRestPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeRestPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeRestPage message handlers
