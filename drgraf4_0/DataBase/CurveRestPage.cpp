// CurveRestPage.cpp : implementation file
//

#include "stdafx.h"
#include "CurveSheet.h"
/////////////////////
#include "CurveRestPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveRestPage property page

IMPLEMENT_DYNCREATE(CCurveRestPage, CPropertyPage)

CCurveRestPage::CCurveRestPage() : CPropertyPage(CCurveRestPage::IDD)
{
	//{{AFX_DATA_INIT(CCurveRestPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCurveRestPage::~CCurveRestPage()
{
}

void CCurveRestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveRestPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurveRestPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCurveRestPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveRestPage message handlers

BOOL CCurveRestPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
//	UpdateObjData(((CCurveSheet*)GetParent())->GetstrItem());
	///////////
	return TRUE;
}
