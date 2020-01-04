// StalInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "StalSheet.h"
//////////////////////
#include "StalInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStalInputPage property page

IMPLEMENT_DYNCREATE(CStalInputPage, CPropertyPage)

CStalInputPage::CStalInputPage() : CPropertyPage(CStalInputPage::IDD)
{
	//{{AFX_DATA_INIT(CStalInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CStalInputPage::~CStalInputPage()
{
}

void CStalInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStalInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStalInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CStalInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStalInputPage message handlers

BOOL CStalInputPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CStalSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
