// SuppDebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "SuppSheet.h"
/////////////////////
#include "SuppDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuppDebugPage property page

IMPLEMENT_DYNCREATE(CSuppDebugPage, CPropertyPage)

CSuppDebugPage::CSuppDebugPage() : CPropertyPage(CSuppDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CSuppDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSuppDebugPage::~CSuppDebugPage()
{
}

void CSuppDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuppDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuppDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSuppDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuppDebugPage message handlers

BOOL CSuppDebugPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CSuppSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
