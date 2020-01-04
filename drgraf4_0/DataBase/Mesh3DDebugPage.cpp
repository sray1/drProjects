// Mesh3DDebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh3DSheet.h"
////////////////////////
#include "Mesh3DDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh3DDebugPage property page

IMPLEMENT_DYNCREATE(CMesh3DDebugPage, CPropertyPage)

CMesh3DDebugPage::CMesh3DDebugPage() : CPropertyPage(CMesh3DDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh3DDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh3DDebugPage::~CMesh3DDebugPage()
{
}

void CMesh3DDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh3DDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh3DDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh3DDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh3DDebugPage message handlers

BOOL CMesh3DDebugPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh3DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
