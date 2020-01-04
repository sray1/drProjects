// Mesh2DRestPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh2DSheet.h"
////////////////////////
#include "Mesh2DRestPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh2DRestPage property page

IMPLEMENT_DYNCREATE(CMesh2DRestPage, CPropertyPage)

CMesh2DRestPage::CMesh2DRestPage() : CPropertyPage(CMesh2DRestPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh2DRestPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh2DRestPage::~CMesh2DRestPage()
{
}

void CMesh2DRestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh2DRestPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh2DRestPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh2DRestPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh2DRestPage message handlers

BOOL CMesh2DRestPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh2DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
