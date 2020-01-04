// CNodSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"

#include "MCNodeSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMCNodeSheet

IMPLEMENT_DYNAMIC(CMCNodeSheet, CNodeSheet)

CMCNodeSheet::CMCNodeSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CNodeSheet(nIDCaption, pParentWnd, iSelectPage)
{
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= MCNODE_SHEET;
	m_uObjType		= MCNODE;
	////////////////////////////
}

CMCNodeSheet::CMCNodeSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CNodeSheet(pszCaption, pParentWnd, iSelectPage)
{
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= MCNODE_SHEET;
	m_uObjType		= MCNODE;
	////////////////////////////
}

CMCNodeSheet::CMCNodeSheet()
{
	/////////////////////////////////////////
	SetTitle("CNode Properties");
	m_fsSheetType	= MCNODE_SHEET;
	m_uObjType		= MCNODE;
	////////////////////////////
}

int CMCNodeSheet::UpdateSheet(CString& strItem)
{
	////////////////////////////
	if(strItem == "")
		return -1;
	///////////////////
	m_strItem	= strItem;
	m_bCNode	= TRUE;
	m_bMNode	= TRUE;
	////////////////////////
	int nResult = 0;
	////////////////////////////////
	nResult = m_pNodeGeomPage->UpdateMeshData(strItem,TRUE);	// bCNode 
	nResult = m_pNodeInputPage->UpdateMeshData(strItem,TRUE);	// bCNode 
	nResult = m_pNodeLoadPage->UpdateMeshData(strItem,TRUE);	// bCNode 
	nResult = m_pNodeRestPage->UpdateMeshData(strItem,TRUE);	// bCNode 
	nResult = m_pNodeSuppPage->UpdateMeshData(strItem,TRUE);	// bCNode 
	nResult = m_pNodeDebugPage->UpdateMeshData(strItem,TRUE);	// bCNode 
	////////////////
	return nResult;
}

CMCNodeSheet::~CMCNodeSheet()
{
}


BEGIN_MESSAGE_MAP(CMCNodeSheet, CNodeSheet)
	//{{AFX_MSG_MAP(CMCNodeSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMCNodeSheet message handlers

