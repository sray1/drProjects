// CNodeGeomPage.cpp : implementation file
//

#include "stdafx.h"

#include "Drgraf.h"
#include "Drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Mouse.h"
/////////////////////
#include "DrNode.h"
#include "DrFE0D.h"
#include "NodeSheet.h"
/////////////////////
#include "NodeGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CNodeGeomPage property page

IMPLEMENT_DYNCREATE(CNodeGeomPage, CPropertyPage)

CNodeGeomPage::CNodeGeomPage() : CPropertyPage(CNodeGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeGeomPage)
	m_X = 0.0;
	m_Y = 0.0;
	m_Z = 0.0;
	m_ID = _T("");
	m_strType = _T("Input Node");
	//}}AFX_DATA_INIT
}

CNodeGeomPage::~CNodeGeomPage()
{
}

void CNodeGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeGeomPage)
	DDX_Text(pDX, IDD_NODE_DX, m_X);
	DDX_Text(pDX, IDD_NODE_DY, m_Y);
	DDX_Text(pDX, IDD_NODE_DZ, m_Z);
	DDX_Text(pDX, IDD_NODE_ID, m_ID);
	DDX_Text(pDX, IDD_NODE_TYPE, m_strType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeGeomPage message handlers

int CNodeGeomPage::UpdateObjData(CString& strItemID,BOOL bCNode)
{
	if(strItemID == "")
		return -1;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetNodeList_NodeContext((bCNode)?CNODE:NODE);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(NODE,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	CDrNode* pNode = (CDrNode*)(pList->GetObject(index));
	if(pNode)
	{
		m_ID = strItemID;
		m_strType = (bCNode)?"Control Node":"Input Node";
		UpdateInfo(pNode);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CNodeGeomPage::UpdateMeshData(CString& strItemID,BOOL bCNode)
{
	if(strItemID == "")
		return -1;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetNodeList_NodeContext((bCNode)?MCNODE:MNODE);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(FE0D,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	CDrFE0D* pNode = (CDrFE0D*)(pList->GetObject(index));
	if(pNode)
	{
		m_ID = strItemID;
		m_strType = (bCNode)?"Mesh Control Node":"Mesh Node";
		UpdateInfo((CDrNode*)pNode);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CNodeGeomPage::UpdateInfo(CDrNode* pNode)
{
	CMouse Mouse;
	////////////
    WORLD wLocalPos = *(pNode->GetLocalPos());
	Mouse.WORtoWOP(&wLocalPos,&wLocalPos);
	////////////////////////////////////////////////////////// 
    m_X 		= wLocalPos.x;
    m_Y 		= wLocalPos.y;
    m_Z 		= wLocalPos.z;
	/////////////////
	return 0;
}

BOOL CNodeGeomPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	if(((CNodeSheet*)GetParent())->IsMNode())
		UpdateMeshData(	((CNodeSheet*)GetParent())->GetstrItem(),
						((CNodeSheet*)GetParent())->IsCNode()
						);
	else
		UpdateObjData(	((CNodeSheet*)GetParent())->GetstrItem(),
						((CNodeSheet*)GetParent())->IsCNode()
						);
	////////////
	return TRUE;
}
