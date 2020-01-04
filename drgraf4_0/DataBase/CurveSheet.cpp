// NodSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"

#include "CurveSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveSheet

IMPLEMENT_DYNAMIC(CCurveSheet, CDrPropSheet)

CCurveSheet::CCurveSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pCurveGeomPage = new CCurveGeomPage;
	m_pCurveInputPage = new CCurveInputPage;
	m_pCurveLoadPage = new CCurveLoadPage;
	m_pCurveRestPage = new CCurveRestPage;
	m_pCurveSuppPage = new CCurveSuppPage;
	m_pCurveDebugPage = new CCurveDebugPage;
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= CURVE_SHEET;
	m_uObjType		= CURVE;
	////////////////////////////
}

CCurveSheet::CCurveSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pCurveGeomPage = new CCurveGeomPage;
	m_pCurveInputPage = new CCurveInputPage;
	m_pCurveLoadPage = new CCurveLoadPage;
	m_pCurveRestPage = new CCurveRestPage;
	m_pCurveSuppPage = new CCurveSuppPage;
	m_pCurveDebugPage = new CCurveDebugPage;
	//////////////////////////////////////
	AddPage(m_pCurveGeomPage);
	AddPage(m_pCurveInputPage);
	AddPage(m_pCurveLoadPage);
	AddPage(m_pCurveRestPage);
	AddPage(m_pCurveSuppPage);
	AddPage(m_pCurveDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= CURVE_SHEET;
	m_uObjType		= CURVE;
	////////////////////////////
}

CCurveSheet::CCurveSheet()
{
	m_pCurveGeomPage = new CCurveGeomPage;
	m_pCurveInputPage = new CCurveInputPage;
	m_pCurveLoadPage = new CCurveLoadPage;
	m_pCurveRestPage = new CCurveRestPage;
	m_pCurveSuppPage = new CCurveSuppPage;
	m_pCurveDebugPage = new CCurveDebugPage;
	//////////////////////////////////////
	AddPage(m_pCurveGeomPage);
	AddPage(m_pCurveInputPage);
	AddPage(m_pCurveLoadPage);
	AddPage(m_pCurveRestPage);
	AddPage(m_pCurveSuppPage);
	AddPage(m_pCurveDebugPage);
	/////////////////////////////////////////
	SetTitle("Curve Properties");
	m_fsSheetType	= CURVE_SHEET;
	m_uObjType		= CURVE;
	////////////////////////////
}

int CCurveSheet::UpdateSheet(CString& strItem)
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
	if(pActivePage == (CPropertyPage*)m_pCurveGeomPage) 
		nResult = m_pCurveGeomPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pCurveInputPage) 
//		nResult = m_pCurveInputPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pCurveLoadPage) 
		nResult = m_pCurveLoadPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pCurveRestPage) 
//		nResult = m_pCurveRestPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pCurveSuppPage) 
		nResult = m_pCurveSuppPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pCurveDebugPage) 
		nResult = m_pCurveDebugPage->UpdateObjData(strItem);
	////////////////
	return nResult;
}

CCurveSheet::~CCurveSheet()
{
	delete m_pCurveGeomPage;
	delete m_pCurveInputPage;
	delete m_pCurveLoadPage;
	delete m_pCurveRestPage;
	delete m_pCurveSuppPage;
	delete m_pCurveDebugPage;
}


BEGIN_MESSAGE_MAP(CCurveSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CCurveSheet)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveSheet message handlers

int CCurveSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDrPropSheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}

