// Mbj3DGeomPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Mbj3DSheet.h"
///////////////////////
#include "Mbj3DGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMbj3DGeomPage property page

IMPLEMENT_DYNCREATE(CMbj3DGeomPage, CPropertyPage)

CMbj3DGeomPage::CMbj3DGeomPage() : CPropertyPage(CMbj3DGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CMbj3DGeomPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMbj3DGeomPage::~CMbj3DGeomPage()
{
}

void CMbj3DGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMbj3DGeomPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMbj3DGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMbj3DGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMbj3DGeomPage message handlers

BOOL CMbj3DGeomPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CMbj3DSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
