// PatchSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"
///////////////////////
#include "PatchSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatchSheet

IMPLEMENT_DYNAMIC(CPatchSheet, CDrPropSheet)

CPatchSheet::CPatchSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pPatchGeomPage	= new CPatchGeomPage;
	m_pPatchInputPage	= new CPatchInputPage;
	m_pPatchLoadPage	= new CPatchLoadPage;
	m_pPatchRestPage	= new CPatchRestPage;
	m_pPatchSuppPage	= new CPatchSuppPage;
	m_pPatchDebugPage	= new CPatchDebugPage;
	//////////////////////////////////////
	AddPage(m_pPatchGeomPage);
	AddPage(m_pPatchInputPage);
	AddPage(m_pPatchLoadPage);
	AddPage(m_pPatchRestPage);
	AddPage(m_pPatchSuppPage);
	AddPage(m_pPatchDebugPage);
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= PATCH_SHEET;
	m_uObjType		= PATCH;
	////////////////////////////
}

CPatchSheet::CPatchSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pPatchGeomPage	= new CPatchGeomPage;
	m_pPatchInputPage	= new CPatchInputPage;
	m_pPatchLoadPage	= new CPatchLoadPage;
	m_pPatchRestPage	= new CPatchRestPage;
	m_pPatchSuppPage	= new CPatchSuppPage;
	m_pPatchDebugPage	= new CPatchDebugPage;
	//////////////////////////////////////
	AddPage(m_pPatchGeomPage);
	AddPage(m_pPatchInputPage);
	AddPage(m_pPatchLoadPage);
	AddPage(m_pPatchRestPage);
	AddPage(m_pPatchSuppPage);
	AddPage(m_pPatchDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= PATCH_SHEET;
	m_uObjType		= PATCH;
	////////////////////////////
}

int CPatchSheet::UpdateSheet(CString& strItem)
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
	if(pActivePage == (CPropertyPage*)m_pPatchGeomPage) 
		nResult = m_pPatchGeomPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pPatchInputPage) 
//		nResult = m_pPatchInputPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pPatchLoadPage) 
		nResult = m_pPatchLoadPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pPatchRestPage) 
//		nResult = m_pPatchRestPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pPatchSuppPage) 
		nResult = m_pPatchSuppPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pPatchDebugPage) 
//		nResult = m_pPatchDebugPage->UpdateObjData(strItem);
	////////////////
	return nResult;
}

CPatchSheet::~CPatchSheet()
{
	delete m_pPatchGeomPage;
	delete m_pPatchInputPage;
	delete m_pPatchLoadPage;
	delete m_pPatchRestPage;
	delete m_pPatchSuppPage;
	delete m_pPatchDebugPage;
}


BEGIN_MESSAGE_MAP(CPatchSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CPatchSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatchSheet message handlers
