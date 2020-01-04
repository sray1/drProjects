// Mbj3DDebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Mbj3DSheet.h"
///////////////////////
#include "Mbj3DDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMbj3DDebugPage property page

IMPLEMENT_DYNCREATE(CMbj3DDebugPage, CPropertyPage)

CMbj3DDebugPage::CMbj3DDebugPage() : CPropertyPage(CMbj3DDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CMbj3DDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMbj3DDebugPage::~CMbj3DDebugPage()
{
}

void CMbj3DDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMbj3DDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMbj3DDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMbj3DDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMbj3DDebugPage message handlers

BOOL CMbj3DDebugPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMbj3DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
