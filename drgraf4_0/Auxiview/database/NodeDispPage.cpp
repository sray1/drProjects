// CNodeDispPage.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "NodeDispPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeDispPage property page

IMPLEMENT_DYNCREATE(CNodeDispPage, CPropertyPage)

CNodeDispPage::CNodeDispPage() : CPropertyPage(CNodeDispPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeDispPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CNodeDispPage::~CNodeDispPage()
{
}

void CNodeDispPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeDispPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeDispPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeDispPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeDispPage message handlers
