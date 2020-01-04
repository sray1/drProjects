// SolidDebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "SolidSheet.h"
/////////////////////
#include "SolidDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSolidDebugPage property page

IMPLEMENT_DYNCREATE(CSolidDebugPage, CPropertyPage)

CSolidDebugPage::CSolidDebugPage() : CPropertyPage(CSolidDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CSolidDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSolidDebugPage::~CSolidDebugPage()
{
}

void CSolidDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSolidDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSolidDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSolidDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSolidDebugPage message handlers

BOOL CSolidDebugPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CSolidSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
