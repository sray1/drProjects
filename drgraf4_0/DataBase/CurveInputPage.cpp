// CurveInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "CurveSheet.h"
/////////////////////
#include "CurveInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveInputPage property page

IMPLEMENT_DYNCREATE(CCurveInputPage, CPropertyPage)

CCurveInputPage::CCurveInputPage() : CPropertyPage(CCurveInputPage::IDD)
{
	//{{AFX_DATA_INIT(CCurveInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCurveInputPage::~CCurveInputPage()
{
}

void CCurveInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurveInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCurveInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveInputPage message handlers

BOOL CCurveInputPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
//	UpdateObjData(((CCurveSheet*)GetParent())->GetstrItem());
	///////////
	return TRUE;
}
