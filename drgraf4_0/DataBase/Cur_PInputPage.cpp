// Cur_PInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Cur_PInputPage.h"
#include "Cur_PSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCur_PInputPage property page

IMPLEMENT_DYNCREATE(CCur_PInputPage, CPropertyPage)

CCur_PInputPage::CCur_PInputPage() : CPropertyPage(CCur_PInputPage::IDD)
{
	//{{AFX_DATA_INIT(CCur_PInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCur_PInputPage::~CCur_PInputPage()
{
}

void CCur_PInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCur_PInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCur_PInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCur_PInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCur_PInputPage message handlers

BOOL CCur_PInputPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
//	UpdateObjData(((CCur_PSheet*)GetParent())->GetstrItem());
	///////////
	return TRUE;
}
