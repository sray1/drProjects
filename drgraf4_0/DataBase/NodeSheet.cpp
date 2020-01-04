// NodSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"
//////////////////////
#include "NodeSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeSheet

IMPLEMENT_DYNAMIC(CNodeSheet, CDrPropSheet)

CNodeSheet::CNodeSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pNodeGeomPage = new CNodeGeomPage;
	m_pNodeInputPage = new CNodeInputPage;
	m_pNodeLoadPage = new CNodeLoadPage;
	m_pNodeRestPage = new CNodeRestPage;
	m_pNodeSuppPage = new CNodeSuppPage;
	m_pNodeDebugPage = new CNodeDebugPage;
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= NODE_SHEET;
	m_uObjType		= NODE;
	////////////////////////////
}

CNodeSheet::CNodeSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pNodeGeomPage = new CNodeGeomPage;
	m_pNodeInputPage = new CNodeInputPage;
	m_pNodeLoadPage = new CNodeLoadPage;
	m_pNodeRestPage = new CNodeRestPage;
	m_pNodeSuppPage = new CNodeSuppPage;
	m_pNodeDebugPage = new CNodeDebugPage;
	//////////////////////////////////////
	AddPage(m_pNodeGeomPage);
	AddPage(m_pNodeInputPage);
	AddPage(m_pNodeLoadPage);
	AddPage(m_pNodeRestPage);
	AddPage(m_pNodeSuppPage);
	AddPage(m_pNodeDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= NODE_SHEET;
	m_uObjType		= NODE;
	////////////////////////////
}

CNodeSheet::CNodeSheet()
{
	m_pNodeGeomPage = new CNodeGeomPage;
	m_pNodeInputPage = new CNodeInputPage;
	m_pNodeLoadPage = new CNodeLoadPage;
	m_pNodeRestPage = new CNodeRestPage;
	m_pNodeSuppPage = new CNodeSuppPage;
	m_pNodeDebugPage = new CNodeDebugPage;
	//////////////////////////////////////
	AddPage(m_pNodeGeomPage);
	AddPage(m_pNodeInputPage);
	AddPage(m_pNodeLoadPage);
	AddPage(m_pNodeRestPage);
	AddPage(m_pNodeSuppPage);
	AddPage(m_pNodeDebugPage);
	/////////////////////////////////////////
	SetTitle("Node Properties");
	m_fsSheetType	= NODE_SHEET;
	m_uObjType		= NODE;
	////////////////////////////
}

int CNodeSheet::UpdateSheet(CString& strItem)
{
	////////////////////////////
	if(strItem == "")
		return -1;
	///////////////////
	m_strItem	= strItem;
	m_bCNode	= FALSE;
	m_bMNode	= FALSE;
	////////////////////////
	int nResult = 0;
	////////////////////////////////
	CPropertyPage* pActivePage = GetActivePage( );
//	pActivePage->UpdateObjData(strItem,FALSE);;
	///
	if(pActivePage == (CPropertyPage*)m_pNodeGeomPage) 
		nResult = m_pNodeGeomPage->UpdateObjData(strItem,FALSE);	// bCNode
	if(pActivePage == (CPropertyPage*)m_pNodeInputPage) 
		nResult = m_pNodeInputPage->UpdateObjData(strItem,FALSE);	// bCNode
	if(pActivePage == (CPropertyPage*)m_pNodeLoadPage) 
		nResult = m_pNodeLoadPage->UpdateObjData(strItem,FALSE);	// bCNode
	if(pActivePage == (CPropertyPage*)m_pNodeRestPage) 
		nResult = m_pNodeRestPage->UpdateObjData(strItem,FALSE);	// bCNode
	if(pActivePage == (CPropertyPage*)m_pNodeSuppPage) 
		nResult = m_pNodeSuppPage->UpdateObjData(strItem,FALSE);	// bCNode
	if(pActivePage == (CPropertyPage*)m_pNodeDebugPage) 
		nResult = m_pNodeDebugPage->UpdateObjData(strItem,FALSE);	// bCNode
	////////////////
	return nResult;
}

CNodeSheet::~CNodeSheet()
{
	delete m_pNodeGeomPage;
	delete m_pNodeInputPage;
	delete m_pNodeLoadPage;
	delete m_pNodeRestPage;
	delete m_pNodeSuppPage;
	delete m_pNodeDebugPage;
}


BEGIN_MESSAGE_MAP(CNodeSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CNodeSheet)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeSheet message handlers

int CNodeSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDrPropSheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}

