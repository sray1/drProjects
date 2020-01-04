// Mesh2DSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"
////////////////////////
#include "Mesh2DSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh2DSheet

IMPLEMENT_DYNAMIC(CMesh2DSheet, CDrPropSheet)

CMesh2DSheet::CMesh2DSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pMesh2DGeomPage	= new CMesh2DGeomPage;
	m_pMesh2DInputPage	= new CMesh2DInputPage;
	m_pMesh2DLoadPage	= new CMesh2DLoadPage;
	m_pMesh2DRestPage	= new CMesh2DRestPage;
	m_pMesh2DSuppPage	= new CMesh2DSuppPage;
	m_pMesh2DDebugPage	= new CMesh2DDebugPage;
	//////////////////////////////////////
	AddPage(m_pMesh2DGeomPage);
	AddPage(m_pMesh2DInputPage);
	AddPage(m_pMesh2DLoadPage);
	AddPage(m_pMesh2DRestPage);
	AddPage(m_pMesh2DSuppPage);
	AddPage(m_pMesh2DDebugPage);
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= MESH2D_SHEET;
	m_uObjType		= MESH2D;
	////////////////////////////
}

CMesh2DSheet::CMesh2DSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pMesh2DGeomPage	= new CMesh2DGeomPage;
	m_pMesh2DInputPage	= new CMesh2DInputPage;
	m_pMesh2DLoadPage	= new CMesh2DLoadPage;
	m_pMesh2DRestPage	= new CMesh2DRestPage;
	m_pMesh2DSuppPage	= new CMesh2DSuppPage;
	m_pMesh2DDebugPage	= new CMesh2DDebugPage;
	//////////////////////////////////////
	AddPage(m_pMesh2DGeomPage);
	AddPage(m_pMesh2DInputPage);
	AddPage(m_pMesh2DLoadPage);
	AddPage(m_pMesh2DRestPage);
	AddPage(m_pMesh2DSuppPage);
	AddPage(m_pMesh2DDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= MESH2D_SHEET;
	m_uObjType		= MESH2D;
	////////////////////////////
}

int CMesh2DSheet::UpdateSheet(CString& strItem)
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
	if(pActivePage == (CPropertyPage*)m_pMesh2DGeomPage) 
		nResult = m_pMesh2DGeomPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh2DInputPage) 
		nResult = m_pMesh2DInputPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh2DLoadPage) 
		nResult = m_pMesh2DLoadPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh2DRestPage) 
		nResult = m_pMesh2DRestPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh2DSuppPage) 
		nResult = m_pMesh2DSuppPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh2DDebugPage) 
		nResult = m_pMesh2DDebugPage->UpdateObjData(strItem);
*/
	////////////////
	return nResult;
}

CMesh2DSheet::~CMesh2DSheet()
{
	delete m_pMesh2DGeomPage;
	delete m_pMesh2DInputPage;
	delete m_pMesh2DLoadPage;
	delete m_pMesh2DRestPage;
	delete m_pMesh2DSuppPage;
	delete m_pMesh2DDebugPage;
}


BEGIN_MESSAGE_MAP(CMesh2DSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CMesh2DSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh2DSheet message handlers
