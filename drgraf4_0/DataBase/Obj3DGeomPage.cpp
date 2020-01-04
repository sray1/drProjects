// Obj3DGeomPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Obj3DGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObj3DGeomPage property page

IMPLEMENT_DYNCREATE(CObj3DGeomPage, CPropertyPage)

CObj3DGeomPage::CObj3DGeomPage() : CPropertyPage(CObj3DGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CObj3DGeomPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CObj3DGeomPage::~CObj3DGeomPage()
{
}

void CObj3DGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObj3DGeomPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObj3DGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CObj3DGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObj3DGeomPage message handlers

BOOL CObj3DGeomPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
