// SolidRestPage.cpp : implementation file
//

#include "stdafx.h"
#include "SolidSheet.h"
/////////////////////
#include "SolidRestPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSolidRestPage property page

IMPLEMENT_DYNCREATE(CSolidRestPage, CPropertyPage)

CSolidRestPage::CSolidRestPage() : CPropertyPage(CSolidRestPage::IDD)
{
	//{{AFX_DATA_INIT(CSolidRestPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSolidRestPage::~CSolidRestPage()
{
}

void CSolidRestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSolidRestPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSolidRestPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSolidRestPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSolidRestPage message handlers

BOOL CSolidRestPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CSolidSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
