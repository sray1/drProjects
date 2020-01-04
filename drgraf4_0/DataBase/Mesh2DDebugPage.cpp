// Mesh2DDebugPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh2DSheet.h"
////////////////////////
#include "Mesh2DDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh2DDebugPage property page

IMPLEMENT_DYNCREATE(CMesh2DDebugPage, CPropertyPage)

CMesh2DDebugPage::CMesh2DDebugPage() : CPropertyPage(CMesh2DDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh2DDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh2DDebugPage::~CMesh2DDebugPage()
{
}

void CMesh2DDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh2DDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh2DDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh2DDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh2DDebugPage message handlers

BOOL CMesh2DDebugPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh2DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
