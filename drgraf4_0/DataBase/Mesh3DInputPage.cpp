// Mesh3DInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh3DSheet.h"
////////////////////////
#include "Mesh3DInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh3DInputPage property page

IMPLEMENT_DYNCREATE(CMesh3DInputPage, CPropertyPage)

CMesh3DInputPage::CMesh3DInputPage() : CPropertyPage(CMesh3DInputPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh3DInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh3DInputPage::~CMesh3DInputPage()
{
}

void CMesh3DInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh3DInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh3DInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh3DInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh3DInputPage message handlers

BOOL CMesh3DInputPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh3DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
