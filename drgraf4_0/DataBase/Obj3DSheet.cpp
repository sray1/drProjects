// Obj3DSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"

#include "Obj3DSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObj3DSheet

IMPLEMENT_DYNAMIC(CObj3DSheet, CDrPropSheet)

CObj3DSheet::CObj3DSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pObj3DGeomPage	= new CObj3DGeomPage;
	m_pObj3DInputPage	= new CObj3DInputPage;
//	m_pObj3DLoadPage	= new CObj3DLoadPage;
//	m_pObj3DDispPage	= new CObj3DDispPage;
//	m_pObj3DRestPage	= new CObj3DRestPage;
//	m_pObj3DSuppPage	= new CObj3DSuppPage;
	m_pObj3DDebugPage	= new CObj3DDebugPage;
	//////////////////////////////////////
	AddPage(m_pObj3DGeomPage);
	AddPage(m_pObj3DInputPage);
//	AddPage(m_pObj3DLoadPage);
//	AddPage(m_pObj3DDispPage);
//	AddPage(m_pObj3DRestPage);
//	AddPage(m_pObj3DSuppPage);
	AddPage(m_pObj3DDebugPage);
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= OBJ3D_SHEET;
	m_uObjType		= OBJ3D;
	////////////////////////////
}

CObj3DSheet::CObj3DSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pObj3DGeomPage	= new CObj3DGeomPage;
	m_pObj3DInputPage	= new CObj3DInputPage;
//	m_pObj3DLoadPage	= new CObj3DLoadPage;
//	m_pObj3DDispPage	= new CObj3DDispPage;
//	m_pObj3DRestPage	= new CObj3DRestPage;
//	m_pObj3DSuppPage	= new CObj3DSuppPage;
	m_pObj3DDebugPage	= new CObj3DDebugPage;
	//////////////////////////////////////
	AddPage(m_pObj3DGeomPage);
	AddPage(m_pObj3DInputPage);
//	AddPage(m_pObj3DLoadPage);
//	AddPage(m_pObj3DDispPage);
//	AddPage(m_pObj3DRestPage);
//	AddPage(m_pObj3DSuppPage);
	AddPage(m_pObj3DDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= OBJ3D_SHEET;
	m_uObjType		= OBJ3D;
	////////////////////////////
}

int CObj3DSheet::UpdateSheet(CString& strItem)
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
	if(pActivePage == (CPropertyPage*)m_pObj3DGeomPage) 
		nResult = m_pObj3DGeomPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pObj3DInputPage) 
		nResult = m_pObj3DInputPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pObj3DDebugPage) 
		nResult = m_pObj3DDebugPage->UpdateObjData(strItem);
*/
	////////////////
	return nResult;
}

CObj3DSheet::~CObj3DSheet()
{
	delete m_pObj3DGeomPage;
	delete m_pObj3DInputPage;
//	delete m_pObj3DLoadPage;
//	delete m_pObj3DDispPage;
//	delete m_pObj3DRestPage;
//	delete m_pObj3DSuppPage;
	delete m_pObj3DDebugPage;
}


BEGIN_MESSAGE_MAP(CObj3DSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CObj3DSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObj3DSheet message handlers
