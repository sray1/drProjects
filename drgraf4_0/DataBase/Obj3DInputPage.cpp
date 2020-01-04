// Obj3DInputPage.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Obj3DInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObj3DInputPage property page

IMPLEMENT_DYNCREATE(CObj3DInputPage, CPropertyPage)

CObj3DInputPage::CObj3DInputPage() : CPropertyPage(CObj3DInputPage::IDD)
{
	//{{AFX_DATA_INIT(CObj3DInputPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CObj3DInputPage::~CObj3DInputPage()
{
}

void CObj3DInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObj3DInputPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObj3DInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CObj3DInputPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObj3DInputPage message handlers

BOOL CObj3DInputPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
