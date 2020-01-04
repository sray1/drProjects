// SolidGeomPage.cpp : implementation file
//

#include "stdafx.h"
#include "SolidSheet.h"
/////////////////////
#include "SolidGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSolidGeomPage property page

IMPLEMENT_DYNCREATE(CSolidGeomPage, CPropertyPage)

CSolidGeomPage::CSolidGeomPage() : CPropertyPage(CSolidGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CSolidGeomPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSolidGeomPage::~CSolidGeomPage()
{
}

void CSolidGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSolidGeomPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSolidGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSolidGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSolidGeomPage message handlers

BOOL CSolidGeomPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
//	UpdateObjData(((CSolidSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
