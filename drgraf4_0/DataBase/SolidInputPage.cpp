// SolidInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "SolidSheet.h"
/////////////////////
#include "SolidInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSolidInputPage property page

IMPLEMENT_DYNCREATE(CSolidInputPage, CPropertyPage)

CSolidInputPage::CSolidInputPage() : CPropertyPage(CSolidInputPage::IDD)
{
	//{{AFX_DATA_INIT(CSolidInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSolidInputPage::~CSolidInputPage()
{
}

void CSolidInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSolidInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSolidInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSolidInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSolidInputPage message handlers

BOOL CSolidInputPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CSolidSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
