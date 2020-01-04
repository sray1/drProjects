// Mesh3DGeomPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh3DSheet.h"
////////////////////////
#include "Mesh3DGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh3DGeomPage property page

IMPLEMENT_DYNCREATE(CMesh3DGeomPage, CPropertyPage)

CMesh3DGeomPage::CMesh3DGeomPage() : CPropertyPage(CMesh3DGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh3DGeomPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh3DGeomPage::~CMesh3DGeomPage()
{
}

void CMesh3DGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh3DGeomPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh3DGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh3DGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh3DGeomPage message handlers

BOOL CMesh3DGeomPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh3DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
