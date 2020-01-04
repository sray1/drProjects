// StalDebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "StalSheet.h"
//////////////////////
#include "StalDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStalDebugPage property page

IMPLEMENT_DYNCREATE(CStalDebugPage, CPropertyPage)

CStalDebugPage::CStalDebugPage() : CPropertyPage(CStalDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CStalDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CStalDebugPage::~CStalDebugPage()
{
}

void CStalDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStalDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStalDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CStalDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStalDebugPage message handlers

BOOL CStalDebugPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CStalSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
