// SuppSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Supp.h"
//////////////////////
#include "SuppSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuppSheet

IMPLEMENT_DYNAMIC(CSuppSheet, CDrPropSheet)

CSuppSheet::CSuppSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pSuppDefnPage		= new CSuppDefnPage;
	m_pSuppInputPage	= new CSuppInputPage;
	m_pSuppDebugPage	= new CSuppDebugPage;
	//////////////////////////////////////
	AddPage(m_pSuppDefnPage);
	AddPage(m_pSuppInputPage);
	AddPage(m_pSuppDebugPage);
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= SUPP_SHEET;
	m_uObjType		= LIN_SUPPORT;
	////////////////////////////
}

CSuppSheet::CSuppSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pSuppDefnPage		= new CSuppDefnPage;
	m_pSuppInputPage	= new CSuppInputPage;
	m_pSuppDebugPage	= new CSuppDebugPage;
	//////////////////////////////////////
	AddPage(m_pSuppDefnPage);
	AddPage(m_pSuppInputPage);
	AddPage(m_pSuppDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= SUPP_SHEET;
	m_uObjType		= LIN_SUPPORT;
	////////////////////////////
}

int CSuppSheet::UpdateSheet(CString& strItem)
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
	if(pActivePage == (CPropertyPage*)m_pSuppDefnPage) 
		nResult = m_pSuppDefnPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pSuppInputPage) 
//		nResult = m_pSuppInputPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pSuppDebugPage) 
//		nResult = m_pSuppDebugPage->UpdateObjData(strItem);
	////////////////
	return nResult;
}

CSuppSheet::~CSuppSheet()
{
	delete m_pSuppDefnPage;
	delete m_pSuppInputPage;
	delete m_pSuppDebugPage;
}


BEGIN_MESSAGE_MAP(CSuppSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CSuppSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuppSheet message handlers
