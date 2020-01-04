// Cur_PSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"

#include "Cur_PSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCur_PSheet

IMPLEMENT_DYNAMIC(CCur_PSheet, CDrPropSheet)

CCur_PSheet::CCur_PSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pCur_PGeomPage	= new CCur_PGeomPage;
	m_pCur_PInputPage	= new CCur_PInputPage;
	m_pCur_PLoadPage	= new CCur_PLoadPage;
	m_pCur_PRestPage	= new CCur_PRestPage;
	m_pCur_PSuppPage	= new CCur_PSuppPage;
	m_pCur_PDebugPage	= new CCur_PDebugPage;
	/////////////////////////////////////////
//	SetTitle(nIDCaption);	
	m_fsSheetType	= CUR_P_SHEET;
	m_uObjType		= C_PROFILE;
	////////////////////////////
}

CCur_PSheet::CCur_PSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pCur_PGeomPage	= new CCur_PGeomPage;
	m_pCur_PInputPage	= new CCur_PInputPage;
	m_pCur_PLoadPage	= new CCur_PLoadPage;
	m_pCur_PRestPage	= new CCur_PRestPage;
	m_pCur_PSuppPage	= new CCur_PSuppPage;
	m_pCur_PDebugPage	= new CCur_PDebugPage;
	//////////////////////////////////////
	AddPage(m_pCur_PGeomPage);
	AddPage(m_pCur_PInputPage);
	AddPage(m_pCur_PLoadPage);
	AddPage(m_pCur_PRestPage);
	AddPage(m_pCur_PSuppPage);
	AddPage(m_pCur_PDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= CUR_P_SHEET;
	m_uObjType		= C_PROFILE;
	////////////////////////////
}

int CCur_PSheet::UpdateSheet(CString& strItem)
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
	if(pActivePage == (CPropertyPage*)m_pCur_PGeomPage) 
		nResult = m_pCur_PGeomPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pCur_PInputPage) 
//		nResult = m_pCur_PInputPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pCur_PLoadPage) 
		nResult = m_pCur_PLoadPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pCur_PRestPage) 
//		nResult = m_pCur_PRestPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pCur_PSuppPage) 
		nResult = m_pCur_PSuppPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pCur_PDebugPage) 
//		nResult = m_pCur_PDebugPage->UpdateObjData(strItem);
	////////////////
	return nResult;
}

CCur_PSheet::~CCur_PSheet()
{
	delete m_pCur_PGeomPage;
	delete m_pCur_PInputPage;
	delete m_pCur_PLoadPage;
	delete m_pCur_PRestPage;
	delete m_pCur_PSuppPage;
	delete m_pCur_PDebugPage;
}


BEGIN_MESSAGE_MAP(CCur_PSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CCur_PSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCur_PSheet message handlers
