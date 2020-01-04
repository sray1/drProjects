// Mesh2DInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh2DSheet.h"
////////////////////////
#include "Mesh2DInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh2DInputPage property page

IMPLEMENT_DYNCREATE(CMesh2DInputPage, CPropertyPage)

CMesh2DInputPage::CMesh2DInputPage() : CPropertyPage(CMesh2DInputPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh2DInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh2DInputPage::~CMesh2DInputPage()
{
}

void CMesh2DInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh2DInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh2DInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh2DInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh2DInputPage message handlers

BOOL CMesh2DInputPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh2DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
