// CMesh1DRestPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mesh1DSheet.h"
////////////////////////
#include "Mesh1DRestPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh1DRestPage property page

IMPLEMENT_DYNCREATE(CMesh1DRestPage, CPropertyPage)

CMesh1DRestPage::CMesh1DRestPage() : CPropertyPage(CMesh1DRestPage::IDD)
{
	//{{AFX_DATA_INIT(CMesh1DRestPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMesh1DRestPage::~CMesh1DRestPage()
{
}

void CMesh1DRestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMesh1DRestPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMesh1DRestPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMesh1DRestPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh1DRestPage message handlers

BOOL CMesh1DRestPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMesh1DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
