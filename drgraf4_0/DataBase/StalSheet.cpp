// StalSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_StaL.h"
//////////////////////
#include "StalSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStalSheet

IMPLEMENT_DYNAMIC(CStalSheet, CDrPropSheet)

CStalSheet::CStalSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pStalDefnPage		= new CStalDefnPage;
	m_pStalInputPage	= new CStalInputPage;
	m_pStalDebugPage	= new CStalDebugPage;
	//////////////////////////////////////
	AddPage(m_pStalDefnPage);
	AddPage(m_pStalInputPage);
	AddPage(m_pStalDebugPage);
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= STAL_SHEET;
	m_uObjType		= STATICLOAD;
	////////////////////////////
}

CStalSheet::CStalSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pStalDefnPage		= new CStalDefnPage;
	m_pStalInputPage	= new CStalInputPage;
	m_pStalDebugPage	= new CStalDebugPage;
	//////////////////////////////////////
	AddPage(m_pStalDefnPage);
	AddPage(m_pStalInputPage);
	AddPage(m_pStalDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= STAL_SHEET;
	m_uObjType		= STATICLOAD;
	////////////////////////////
}

int CStalSheet::UpdateSheet(CString& strItem)
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
	if(pActivePage == (CPropertyPage*)m_pStalDefnPage) 
		nResult = m_pStalDefnPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pStalInputPage) 
//		nResult = m_pStalInputPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pStalDebugPage) 
//		nResult = m_pStalDebugPage->UpdateObjData(strItem);
	////////////////
	return nResult;
}

CStalSheet::~CStalSheet()
{
	delete m_pStalDefnPage;
	delete m_pStalInputPage;
	delete m_pStalDebugPage;
}


BEGIN_MESSAGE_MAP(CStalSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CStalSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStalSheet message handlers
