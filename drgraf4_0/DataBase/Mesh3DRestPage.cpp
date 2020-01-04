// Mesh3DRestPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh3DSheet.h"
////////////////////////
#include "Mesh3DRestPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh3DRestPage property page

IMPLEMENT_DYNCREATE(CMesh3DRestPage, CPropertyPage)

CMesh3DRestPage::CMesh3DRestPage() : CPropertyPage(CMesh3DRestPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh3DRestPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh3DRestPage::~CMesh3DRestPage()
{
}

void CMesh3DRestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh3DRestPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh3DRestPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh3DRestPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh3DRestPage message handlers

BOOL CMesh3DRestPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh3DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
