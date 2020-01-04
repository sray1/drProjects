// Mesh1DDebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh1DSheet.h"
////////////////////////
#include "Mesh1DDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh1DDebugPage property page

IMPLEMENT_DYNCREATE(CMesh1DDebugPage, CPropertyPage)

CMesh1DDebugPage::CMesh1DDebugPage() : CPropertyPage(CMesh1DDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh1DDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh1DDebugPage::~CMesh1DDebugPage()
{
}

void CMesh1DDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh1DDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh1DDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh1DDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh1DDebugPage message handlers

BOOL CMesh1DDebugPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh1DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
