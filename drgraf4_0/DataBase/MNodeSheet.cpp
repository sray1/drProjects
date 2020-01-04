// CNodSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"

#include "MNodeSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMNodeSheet

IMPLEMENT_DYNAMIC(CMNodeSheet, CNodeSheet)

CMNodeSheet::CMNodeSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CNodeSheet(nIDCaption, pParentWnd, iSelectPage)
{
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= MNODE_SHEET;
	m_uObjType		= MNODE;
	////////////////////////////
}

CMNodeSheet::CMNodeSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CNodeSheet(pszCaption, pParentWnd, iSelectPage)
{
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= MNODE_SHEET;
	m_uObjType		= MNODE;
	////////////////////////////
}

CMNodeSheet::CMNodeSheet()
{
	/////////////////////////////////////////
	SetTitle("CNode Properties");
	m_fsSheetType	= MNODE_SHEET;
	m_uObjType		= MNODE;
	////////////////////////////
}

int CMNodeSheet::UpdateSheet(CString& strItem)
{
	////////////////////////////
	if(strItem == "")
		return -1;
	///////////////////
	m_strItem	= strItem;
	m_bCNode	= FALSE;
	m_bMNode	= TRUE;
	////////////////////////
	int nResult = 0;
	////////////////////////////////
	CPropertyPage* pActivePage = GetActivePage( );
	///
	if(pActivePage == (CPropertyPage*)m_pNodeGeomPage) 
		nResult = m_pNodeGeomPage->UpdateMeshData(strItem,FALSE);	// bCNode
	if(pActivePage == (CPropertyPage*)m_pNodeInputPage) 
		nResult = m_pNodeInputPage->UpdateMeshData(strItem,FALSE);	// bCNode
	if(pActivePage == (CPropertyPage*)m_pNodeLoadPage) 
		nResult = m_pNodeLoadPage->UpdateMeshData(strItem,FALSE);	// bCNode
	if(pActivePage == (CPropertyPage*)m_pNodeRestPage) 
		nResult = m_pNodeRestPage->UpdateMeshData(strItem,FALSE);	// bCNode
	if(pActivePage == (CPropertyPage*)m_pNodeSuppPage) 
		nResult = m_pNodeSuppPage->UpdateMeshData(strItem,FALSE);	// bCNode
	if(pActivePage == (CPropertyPage*)m_pNodeDebugPage) 
		nResult = m_pNodeDebugPage->UpdateMeshData(strItem,FALSE);	// bCNode
	////////////////
	return nResult;
}

CMNodeSheet::~CMNodeSheet()
{
}


BEGIN_MESSAGE_MAP(CMNodeSheet, CNodeSheet)
	//{{AFX_MSG_MAP(CMNodeSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMNodeSheet message handlers

