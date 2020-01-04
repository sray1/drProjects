// Mesh1DGeomPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh1DSheet.h"
////////////////////////
#include "Mesh1DGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh1DGeomPage property page

IMPLEMENT_DYNCREATE(CMesh1DGeomPage, CPropertyPage)

CMesh1DGeomPage::CMesh1DGeomPage() : CPropertyPage(CMesh1DGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh1DGeomPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh1DGeomPage::~CMesh1DGeomPage()
{
}

void CMesh1DGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh1DGeomPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh1DGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh1DGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh1DGeomPage message handlers

BOOL CMesh1DGeomPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh1DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
