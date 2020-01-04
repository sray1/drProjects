// PatchRestPage.cpp : implementation file
//

#include "stdafx.h"
#include "PatchSheet.h"
/////////////////////
#include "PatchRestPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatchRestPage property page

IMPLEMENT_DYNCREATE(CPatchRestPage, CPropertyPage)

CPatchRestPage::CPatchRestPage() : CPropertyPage(CPatchRestPage::IDD)
{
	//{{AFX_DATA_INIT(CPatchRestPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPatchRestPage::~CPatchRestPage()
{
}

void CPatchRestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPatchRestPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPatchRestPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPatchRestPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatchRestPage message handlers

BOOL CPatchRestPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CPatchSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
