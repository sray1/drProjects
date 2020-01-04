// CDrPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "DrPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrPropSheet

IMPLEMENT_DYNAMIC(CDrPropSheet, CPropertySheet)

CDrPropSheet::CDrPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CDrPropSheet::CDrPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CDrPropSheet::CDrPropSheet()
{
}

CDrPropSheet::~CDrPropSheet()
{
}


BEGIN_MESSAGE_MAP(CDrPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CDrPropSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrPropSheet message handlers
