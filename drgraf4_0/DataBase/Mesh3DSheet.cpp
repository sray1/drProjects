// Mesh3DSheet.cpp : implementation file
//

#include "stdafx.h"

#include "Def_IGen.h"
#include "Def_Elem.h"
////////////////////////
#include "Mesh3DSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMesh3DSheet

IMPLEMENT_DYNAMIC(CMesh3DSheet, CDrPropSheet)

CMesh3DSheet::CMesh3DSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pMesh3DGeomPage	= new CMesh3DGeomPage;
	m_pMesh3DInputPage	= new CMesh3DInputPage;
	m_pMesh3DLoadPage	= new CMesh3DLoadPage;
	m_pMesh3DRestPage	= new CMesh3DRestPage;
	m_pMesh3DSuppPage	= new CMesh3DSuppPage;
	m_pMesh3DDebugPage	= new CMesh3DDebugPage;
	//////////////////////////////////////
	AddPage(m_pMesh3DGeomPage);
	AddPage(m_pMesh3DInputPage);
	AddPage(m_pMesh3DLoadPage);
	AddPage(m_pMesh3DRestPage);
	AddPage(m_pMesh3DSuppPage);
	AddPage(m_pMesh3DDebugPage);
	/////////////////////////////////////////
//	SetTitle(pszCaption);
	m_fsSheetType	= MESH3D_SHEET;
	m_uObjType		= MESH3D;
	////////////////////////////
}

CMesh3DSheet::CMesh3DSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CDrPropSheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pMesh3DGeomPage	= new CMesh3DGeomPage;
	m_pMesh3DInputPage	= new CMesh3DInputPage;
	m_pMesh3DLoadPage	= new CMesh3DLoadPage;
	m_pMesh3DRestPage	= new CMesh3DRestPage;
	m_pMesh3DSuppPage	= new CMesh3DSuppPage;
	m_pMesh3DDebugPage	= new CMesh3DDebugPage;
	//////////////////////////////////////
	AddPage(m_pMesh3DGeomPage);
	AddPage(m_pMesh3DInputPage);
	AddPage(m_pMesh3DLoadPage);
	AddPage(m_pMesh3DRestPage);
	AddPage(m_pMesh3DSuppPage);
	AddPage(m_pMesh3DDebugPage);
	/////////////////////////////////////////
	SetTitle(pszCaption);
	m_fsSheetType	= MESH3D_SHEET;
	m_uObjType		= MESH3D;
	////////////////////////////
}

int CMesh3DSheet::UpdateSheet(CString& strItem)
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
	if(pActivePage == (CPropertyPage*)m_pMesh3DGeomPage) 
		nResult = m_pMesh3DGeomPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh3DInputPage) 
		nResult = m_pMesh3DInputPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh3DLoadPage) 
		nResult = m_pMesh3DLoadPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh3DRestPage) 
		nResult = m_pMesh3DRestPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh3DSuppPage) 
		nResult = m_pMesh3DSuppPage->UpdateObjData(strItem);
	if(pActivePage == (CPropertyPage*)m_pMesh3DDebugPage) 
		nResult = m_pMesh3DDebugPage->UpdateObjData(strItem);
*/
	////////////////
	return nResult;
}

CMesh3DSheet::~CMesh3DSheet()
{
	delete m_pMesh3DGeomPage;
	delete m_pMesh3DInputPage;
	delete m_pMesh3DLoadPage;
	delete m_pMesh3DRestPage;
	delete m_pMesh3DSuppPage;
	delete m_pMesh3DDebugPage;
}


BEGIN_MESSAGE_MAP(CMesh3DSheet, CDrPropSheet)
	//{{AFX_MSG_MAP(CMesh3DSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMesh3DSheet message handlers
