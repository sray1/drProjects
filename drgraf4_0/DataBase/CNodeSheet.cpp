// CNodSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"

#include "CNodeSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCNodeSheet

IMPLEMENT_DYNAMIC(CCNodeSheet, CNodeSheet)

CCNodeSheet::CCNodeSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CNodeSheet(nIDCaption, pParentWnd, iSelectPage)
{
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= CNODE_SHEET;
	m_uObjType		= CNODE;
	////////////////////////////
}

CCNodeSheet::CCNodeSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CNodeSheet(pszCaption, pParentWnd, iSelectPage)
{
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= CNODE_SHEET;
	m_uObjType		= CNODE;
	////////////////////////////
}

CCNodeSheet::CCNodeSheet()
{
	/////////////////////////////////////////
	SetTitle("CNode Properties");
	m_fsSheetType	= CNODE_SHEET;
	m_uObjType		= CNODE;
	////////////////////////////
}

int CCNodeSheet::UpdateSheet(CString& strItem)
{
	////////////////////////////
	if(strItem == "")
		return -1;
	///////////////////
	m_strItem = strItem;
	////////////////////////
	int nResult = 0;
	////////////////////////////////
	CPropertyPage* pActivePage = GetActivePage( );
	///
	if(pActivePage == (CPropertyPage*)m_pNodeGeomPage) 
		nResult = m_pNodeGeomPage->UpdateObjData(strItem,TRUE);	// bCNode 
	if(pActivePage == (CPropertyPage*)m_pNodeInputPage) 
		nResult = m_pNodeInputPage->UpdateObjData(strItem,TRUE);	// bCNode 
	if(pActivePage == (CPropertyPage*)m_pNodeLoadPage) 
		nResult = m_pNodeLoadPage->UpdateObjData(strItem,TRUE);	// bCNode 
	if(pActivePage == (CPropertyPage*)m_pNodeRestPage) 
		nResult = m_pNodeRestPage->UpdateObjData(strItem,TRUE);	// bCNode 
	if(pActivePage == (CPropertyPage*)m_pNodeSuppPage) 
		nResult = m_pNodeSuppPage->UpdateObjData(strItem,TRUE);	// bCNode 
	if(pActivePage == (CPropertyPage*)m_pNodeDebugPage) 
		nResult = m_pNodeDebugPage->UpdateObjData(strItem,TRUE);	// bCNode 
	////////////////
	return nResult;
}

CCNodeSheet::~CCNodeSheet()
{
}


BEGIN_MESSAGE_MAP(CCNodeSheet, CNodeSheet)
	//{{AFX_MSG_MAP(CCNodeSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCNodeSheet message handlers

