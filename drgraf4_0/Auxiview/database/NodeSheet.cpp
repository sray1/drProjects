// NodSheet.cpp : implementation file
//

#include "stdafx.h"
#include "database.h"
#include "NodeSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeSheet

IMPLEMENT_DYNAMIC(CNodeSheet, CPropertySheet)

CNodeSheet::CNodeSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pNodeGeomPage = new CNodeGeomPage;
	m_pNodeInputPage = new CNodeInputPage;
	m_pNodeLoadPage = new CNodeLoadPage;
	m_pNodeDispPage = new CNodeDispPage;
	m_pNodeRestPage = new CNodeRestPage;
	m_pNodeSuppPage = new CNodeSuppPage;
	m_pNodeDebugPage = new CNodeDebugPage;
}

CNodeSheet::CNodeSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pNodeGeomPage = new CNodeGeomPage;
	m_pNodeInputPage = new CNodeInputPage;
	m_pNodeLoadPage = new CNodeLoadPage;
	m_pNodeDispPage = new CNodeDispPage;
	m_pNodeRestPage = new CNodeRestPage;
	m_pNodeSuppPage = new CNodeSuppPage;
	m_pNodeDebugPage = new CNodeDebugPage;
	//////////////////////////////////////
	AddPage(m_pNodeGeomPage);
	AddPage(m_pNodeInputPage);
	AddPage(m_pNodeLoadPage);
	AddPage(m_pNodeDispPage);
	AddPage(m_pNodeRestPage);
	AddPage(m_pNodeSuppPage);
	AddPage(m_pNodeDebugPage);
	

}

CNodeSheet::CNodeSheet()
{
	m_pNodeGeomPage = new CNodeGeomPage;
	m_pNodeInputPage = new CNodeInputPage;
	m_pNodeLoadPage = new CNodeLoadPage;
	m_pNodeDispPage = new CNodeDispPage;
	m_pNodeRestPage = new CNodeRestPage;
	m_pNodeSuppPage = new CNodeSuppPage;
	m_pNodeDebugPage = new CNodeDebugPage;
	//////////////////////////////////////
	AddPage(m_pNodeGeomPage);
	AddPage(m_pNodeInputPage);
	AddPage(m_pNodeLoadPage);
	AddPage(m_pNodeDispPage);
	AddPage(m_pNodeRestPage);
	AddPage(m_pNodeSuppPage);
	AddPage(m_pNodeDebugPage);
}


CNodeSheet::~CNodeSheet()
{
	delete m_pNodeGeomPage;
	delete m_pNodeInputPage;
	delete m_pNodeLoadPage;
	delete m_pNodeDispPage;
	delete m_pNodeRestPage;
	delete m_pNodeSuppPage;
	delete m_pNodeDebugPage;
}


BEGIN_MESSAGE_MAP(CNodeSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CNodeSheet)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeSheet message handlers

int CNodeSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}

