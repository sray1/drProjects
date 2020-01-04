// Cur_P_Topo.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Cur_PTopoPage.h"
#include "Cur_PSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCur_PTopoPage property page

IMPLEMENT_DYNCREATE(CCur_PTopoPage, CPropertyPage)

CCur_PTopoPage::CCur_PTopoPage() : CPropertyPage(CCur_PTopoPage::IDD)
{
	//{{AFX_DATA_INIT(CCur_PTopoPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCur_PTopoPage::~CCur_PTopoPage()
{
}

void CCur_PTopoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCur_PTopoPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCur_PTopoPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCur_PTopoPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCur_PTopoPage message handlers

BOOL CCur_PTopoPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
//	UpdateObjData(((CCur_PSheet*)GetParent())->GetstrItem());
	///////////
	return TRUE;
}
