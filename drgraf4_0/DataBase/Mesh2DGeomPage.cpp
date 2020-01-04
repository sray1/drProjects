// Mesh2DGeomPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh2DSheet.h"
////////////////////////
#include "Mesh2DGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh2DGeomPage property page

IMPLEMENT_DYNCREATE(CMesh2DGeomPage, CPropertyPage)

CMesh2DGeomPage::CMesh2DGeomPage() : CPropertyPage(CMesh2DGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh2DGeomPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh2DGeomPage::~CMesh2DGeomPage()
{
}

void CMesh2DGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh2DGeomPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh2DGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh2DGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh2DGeomPage message handlers

BOOL CMesh2DGeomPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh2DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
