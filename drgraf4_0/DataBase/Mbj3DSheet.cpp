// Mbj3DSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"

#include "Mbj3DSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMbj3DSheet

IMPLEMENT_DYNAMIC(CMbj3DSheet, CDrPropSheet)

CMbj3DSheet::CMbj3DSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pMbj3DGeomPage	= new CMbj3DGeomPage;
	m_pMbj3DInputPage	= new CMbj3DInputPage;
//	m_pMbj3DLoadPage	= new CMbj3DLoadPage;
//	m_pMbj3DDispPage	= new CMbj3DDispPage;
//	m_pMbj3DRestPage	= new CMbj3DRestPage;
//	m_pMbj3DSuppPage	= new CMbj3DSuppPage;
	m_pMbj3DDebugPage	= new CMbj3DDebugPage;
	//////////////////////////////////////
	AddPage(m_pMbj3DGeomPage);
	AddPage(m_pMbj3DInputPage);
//	AddPage(m_pMbj3DLoadPage);
//	AddPage(m_pMbj3DDispPage);
//	AddPage(m_pMbj3DRestPage);
//	AddPage(m_pMbj3DSuppPage);
	AddPage(m_pMbj3DDebugPage);
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= MBJ3D_SHEET;
	m_uObjType		= MBJ3D;
	////////////////////////////
}

CMbj3DSheet::CMbj3DSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pMbj3DGeomPage	= new CMbj3DGeomPage;
	m_pMbj3DInputPage	= new CMbj3DInputPage;
//	m_pMbj3DLoadPage	= new CMbj3DLoadPage;
//	m_pMbj3DDispPage	= new CMbj3DDispPage;
//	m_pMbj3DRestPage	= new CMbj3DRestPage;
//	m_pMbj3DSuppPage	= new CMbj3DSuppPage;
	m_pMbj3DDebugPage	= new CMbj3DDebugPage;
	//////////////////////////////////////
	AddPage(m_pMbj3DGeomPage);
	AddPage(m_pMbj3DInputPage);
//	AddPage(m_pMbj3DLoadPage);
//	AddPage(m_pMbj3DDispPage);
//	AddPage(m_pMbj3DRestPage);
//	AddPage(m_pMbj3DSuppPage);
	AddPage(m_pMbj3DDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= MBJ3D_SHEET;
	m_uObjType		= MBJ3D;
	////////////////////////////
}

int CMbj3DSheet::UpdateSheet(CString& strItem)
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
//	if(pActivePage == (CPropertyPage*)m_pMbj3DGeomPage) 
//		nResult = m_pMbj3DGeomPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pMbj3DInputPage) 
//		nResult = m_pMbj3DInputPage->UpdateObjData(strItem);
//	if(pActivePage == (CPropertyPage*)m_pMbj3DDebugPage) 
//		nResult = m_pMbj3DDebugPage->UpdateObjData(strItem);
	////////////////
	return nResult;
}

CMbj3DSheet::~CMbj3DSheet()
{
	delete m_pMbj3DGeomPage;
	delete m_pMbj3DInputPage;
//	delete m_pMbj3DLoadPage;
//	delete m_pMbj3DDispPage;
//	delete m_pMbj3DRestPage;
//	delete m_pMbj3DSuppPage;
	delete m_pMbj3DDebugPage;
}


BEGIN_MESSAGE_MAP(CMbj3DSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CMbj3DSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMbj3DSheet message handlers
