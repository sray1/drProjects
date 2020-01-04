// Mesh1DSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"

#include "Mesh1DSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh1DSheet

IMPLEMENT_DYNAMIC(CMesh1DSheet, CDrPropSheet)

CMesh1DSheet::CMesh1DSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pMesh1DGeomPage	= new CMesh1DGeomPage;
	m_pMesh1DInputPage	= new CMesh1DInputPage;
	m_pMesh1DLoadPage	= new CMesh1DLoadPage;
	m_pMesh1DRestPage	= new CMesh1DRestPage;
	m_pMesh1DSuppPage	= new CMesh1DSuppPage;
	m_pMesh1DDebugPage	= new CMesh1DDebugPage;
	//////////////////////////////////////
	AddPage(m_pMesh1DGeomPage);
	AddPage(m_pMesh1DInputPage);
	AddPage(m_pMesh1DLoadPage);
	AddPage(m_pMesh1DRestPage);
	AddPage(m_pMesh1DSuppPage);
	AddPage(m_pMesh1DDebugPage);
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= MESH1D_SHEET;
	m_uObjType		= MESH1D;
	////////////////////////////
}

CMesh1DSheet::CMesh1DSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pMesh1DGeomPage	= new CMesh1DGeomPage;
	m_pMesh1DInputPage	= new CMesh1DInputPage;
	m_pMesh1DLoadPage	= new CMesh1DLoadPage;
	m_pMesh1DRestPage	= new CMesh1DRestPage;
	m_pMesh1DSuppPage	= new CMesh1DSuppPage;
	m_pMesh1DDebugPage	= new CMesh1DDebugPage;
	//////////////////////////////////////
	AddPage(m_pMesh1DGeomPage);
	AddPage(m_pMesh1DInputPage);
	AddPage(m_pMesh1DLoadPage);
	AddPage(m_pMesh1DRestPage);
	AddPage(m_pMesh1DSuppPage);
	AddPage(m_pMesh1DDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= MESH1D_SHEET;
	m_uObjType		= MESH1D;
	////////////////////////////
}

int CMesh1DSheet::UpdateSheet(CString& strItem)
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
	if(pActivePage == (CPropertyPage*)m_pMesh1DGeomPage) 
		nResult = m_pMesh1DGeomPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh1DInputPage) 
		nResult = m_pMesh1DInputPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh1DLoadPage) 
		nResult = m_pMesh1DLoadPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh1DRestPage) 
		nResult = m_pMesh1DRestPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh1DSuppPage) 
		nResult = m_pMesh1DSuppPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh1DDebugPage) 
		nResult = m_pMesh1DDebugPage->UpdateObjData(strItem);
*/
	////////////////
	return nResult;
}

CMesh1DSheet::~CMesh1DSheet()
{
	delete m_pMesh1DGeomPage;
	delete m_pMesh1DInputPage;
	delete m_pMesh1DLoadPage;
	delete m_pMesh1DRestPage;
	delete m_pMesh1DSuppPage;
	delete m_pMesh1DDebugPage;
}


BEGIN_MESSAGE_MAP(CMesh1DSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CMesh1DSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh1DSheet message handlers
