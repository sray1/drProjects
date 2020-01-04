// Cur_PDebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Cur_PDebugPage.h"
#include "Cur_PSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCur_PDebugPage property page

IMPLEMENT_DYNCREATE(CCur_PDebugPage, CPropertyPage)

CCur_PDebugPage::CCur_PDebugPage() : CPropertyPage(CCur_PDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CCur_PDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCur_PDebugPage::~CCur_PDebugPage()
{
}

void CCur_PDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCur_PDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCur_PDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCur_PDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCur_PDebugPage message handlers

BOOL CCur_PDebugPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
//	UpdateObjData(((CCur_PSheet*)GetParent())->GetstrItem());
	///////////
	return TRUE;
}
