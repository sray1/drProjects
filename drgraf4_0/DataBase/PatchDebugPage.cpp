// PatchDebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "PatchSheet.h"
/////////////////////
#include "PatchDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatchDebugPage property page

IMPLEMENT_DYNCREATE(CPatchDebugPage, CPropertyPage)

CPatchDebugPage::CPatchDebugPage() : CPropertyPage(CPatchDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CPatchDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPatchDebugPage::~CPatchDebugPage()
{
}

void CPatchDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPatchDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPatchDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPatchDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatchDebugPage message handlers

BOOL CPatchDebugPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CPatchSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
