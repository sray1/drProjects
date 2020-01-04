// Mbj3DInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Mbj3DSheet.h"
///////////////////////
#include "Mbj3DInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMbj3DInputPage property page

IMPLEMENT_DYNCREATE(CMbj3DInputPage, CPropertyPage)

CMbj3DInputPage::CMbj3DInputPage() : CPropertyPage(CMbj3DInputPage::IDD)
{
	//{{AFX_DATA_INIT(CMbj3DInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMbj3DInputPage::~CMbj3DInputPage()
{
}

void CMbj3DInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMbj3DInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMbj3DInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMbj3DInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMbj3DInputPage message handlers

BOOL CMbj3DInputPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMbj3DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
