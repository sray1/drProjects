// Obj3DDebugPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "Drgraf.h"
#include "Drgradoc.h"
#include "DListMgr.h"
/////////////////////
#include "Def_IGen.h"
#include "Def_Elem.h"
#include "DrNode.h"
#include "DrFE0D.h"

#include "Obj3DDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObj3DDebugPage property page

IMPLEMENT_DYNCREATE(CObj3DDebugPage, CPropertyPage)

CObj3DDebugPage::CObj3DDebugPage() : CPropertyPage(CObj3DDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CObj3DDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CObj3DDebugPage::~CObj3DDebugPage()
{
}

void CObj3DDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObj3DDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObj3DDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CObj3DDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObj3DDebugPage message handlers

int CObj3DDebugPage::UpdateObjData(CString& strItemID,BOOL bCNode)
{
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
//		m_ID = strItemID;
//		m_strType = (bCNode)?"Control Node":"Input Node";
//		UpdateCoords(pNode);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CObj3DDebugPage::UpdateMeshData(CString& strItemID,BOOL bCNode)
{
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
//		m_ID = strItemID;
//		m_strType = (bCNode)?"Mesh Control Node":"Mesh Node";
//		UpdateCoords((CDrNode*)pNode);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}
/*
int CNodeDebugPage::UpdateCoords(CDrNode* pNode)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////////// 
	LONG  lWorldBase  = pPrecision->GetWorldBase(); 
   	double dWorldBase = (double)lWorldBase; 
    m_X 		= ((double)(pNode->GetLocalPos()->x))/dWorldBase;
    m_Y 		= ((double)(pNode->GetLocalPos()->y))/dWorldBase;
    m_Z 		= ((double)(pNode->GetLocalPos()->z))/dWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	///////////////////////////////////////////
	m_X 		*= dMapFactor;
	m_Y 		*= dMapFactor;
    m_Z 		*= dMapFactor;
    //////////////////////// World Coord
	pObjectMgr->DStoSC(&m_X);
	pObjectMgr->DStoSC(&m_Y);
	pObjectMgr->DStoSC(&m_Z);
	/////////////////
	return 0;
}
*/
BOOL CObj3DDebugPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnSetActive();
}
