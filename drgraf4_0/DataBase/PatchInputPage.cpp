// PatchInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "PatchSheet.h"
/////////////////////
#include "PatchInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatchInputPage property page

IMPLEMENT_DYNCREATE(CPatchInputPage, CPropertyPage)

CPatchInputPage::CPatchInputPage() : CPropertyPage(CPatchInputPage::IDD)
{
	//{{AFX_DATA_INIT(CPatchInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPatchInputPage::~CPatchInputPage()
{
}

void CPatchInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPatchInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPatchInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPatchInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatchInputPage message handlers

BOOL CPatchInputPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CPatchSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
