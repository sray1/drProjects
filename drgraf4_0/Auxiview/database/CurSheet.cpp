// CurSheet.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "CurSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurSheet

IMPLEMENT_DYNAMIC(CCurSheet, CPropertySheet)

CCurSheet::CCurSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pCurGeomPage = new CCurGeomPage;
	m_pCurIntPage = new CCurIntPage;
}

CCurSheet::CCurSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pCurGeomPage = new CCurGeomPage;
	m_pCurIntPage = new CCurIntPage;
	AddPage(m_pCurGeomPage);
	AddPage(m_pCurIntPage);
	

}

CCurSheet::CCurSheet()
{
	m_pCurGeomPage = new CCurGeomPage;
	m_pCurIntPage = new CCurIntPage;
	AddPage(m_pCurGeomPage);
	AddPage(m_pCurIntPage);
	

}


CCurSheet::~CCurSheet()
{
	delete m_pCurGeomPage;
	delete m_pCurIntPage;
}


BEGIN_MESSAGE_MAP(CCurSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CCurSheet)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurSheet message handlers

int CCurSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}

