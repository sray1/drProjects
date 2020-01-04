// SuppInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "SuppSheet.h"
/////////////////////
#include "SuppInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuppInputPage property page

IMPLEMENT_DYNCREATE(CSuppInputPage, CPropertyPage)

CSuppInputPage::CSuppInputPage() : CPropertyPage(CSuppInputPage::IDD)
{
	//{{AFX_DATA_INIT(CSuppInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSuppInputPage::~CSuppInputPage()
{
}

void CSuppInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuppInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuppInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSuppInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuppInputPage message handlers

BOOL CSuppInputPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CSuppSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
