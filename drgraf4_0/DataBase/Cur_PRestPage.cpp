// Cur_PRestPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Cur_PRestPage.h"
#include "Cur_PSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCur_PRestPage property page

IMPLEMENT_DYNCREATE(CCur_PRestPage, CPropertyPage)

CCur_PRestPage::CCur_PRestPage() : CPropertyPage(CCur_PRestPage::IDD)
{
	//{{AFX_DATA_INIT(CCur_PRestPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCur_PRestPage::~CCur_PRestPage()
{
}

void CCur_PRestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCur_PRestPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCur_PRestPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCur_PRestPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCur_PRestPage message handlers

BOOL CCur_PRestPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
//	UpdateObjData(((CCur_PSheet*)GetParent())->GetstrItem());
	///////////
	return TRUE;
}
