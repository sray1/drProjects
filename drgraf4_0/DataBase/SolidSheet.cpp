// SolidSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"

#include "SolidSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSolidSheet

IMPLEMENT_DYNAMIC(CSolidSheet, CDrPropSheet)

CSolidSheet::CSolidSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pSolidGeomPage	= new CSolidGeomPage;
	m_pSolidInputPage	= new CSolidInputPage;
	m_pSolidLoadPage	= new CSolidLoadPage;
	m_pSolidRestPage	= new CSolidRestPage;
	m_pSolidSuppPage	= new CSolidSuppPage;
	m_pSolidDebugPage	= new CSolidDebugPage;
	//////////////////////////////////////
	AddPage(m_pSolidGeomPage);
	AddPage(m_pSolidInputPage);
	AddPage(m_pSolidLoadPage);
	AddPage(m_pSolidRestPage);
	AddPage(m_pSolidSuppPage);
	AddPage(m_pSolidDebugPage);
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= SOLID_SHEET;
	m_uObjType		= SOLID;
	////////////////////////////
}

CSolidSheet::CSolidSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pSolidGeomPage	= new CSolidGeomPage;
	m_pSolidInputPage	= new CSolidInputPage;
	m_pSolidLoadPage	= new CSolidLoadPage;
	m_pSolidRestPage	= new CSolidRestPage;
	m_pSolidSuppPage	= new CSolidSuppPage;
	m_pSolidDebugPage	= new CSolidDebugPage;
	//////////////////////////////////////
	AddPage(m_pSolidGeomPage);
	AddPage(m_pSolidInputPage);
	AddPage(m_pSolidLoadPage);
	AddPage(m_pSolidRestPage);
	AddPage(m_pSolidSuppPage);
	AddPage(m_pSolidDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= SOLID_SHEET;
	m_uObjType		= SOLID;
	////////////////////////////
}

int CSolidSheet::UpdateSheet(CString& strItem)
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
/*
	if(pActivePage == (CPropertyPage*)m_pSolidGeomPage) 
		nResult = m_pSolidGeomPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pSolidInputPage) 
		nResult = m_pSolidInputPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pSolidLoadPage) 
		nResult = m_pSolidLoadPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pSolidRestPage) 
		nResult = m_pSolidRestPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pSolidSuppPage) 
		nResult = m_pSolidSuppPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pSolidDebugPage) 
		nResult = m_pSolidDebugPage->UpdateObjData(strItem);
*/
	////////////////
	return nResult;
}

CSolidSheet::~CSolidSheet()
{
	delete m_pSolidGeomPage;
	delete m_pSolidInputPage;
	delete m_pSolidLoadPage;
	delete m_pSolidRestPage;
	delete m_pSolidSuppPage;
	delete m_pSolidDebugPage;
}


BEGIN_MESSAGE_MAP(CSolidSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CSolidSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSolidSheet message handlers
