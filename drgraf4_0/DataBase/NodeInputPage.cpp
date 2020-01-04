// CNodeInputPage.cpp : implementation file
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
#include "NodeSheet.h"
/////////////////////
#include "NodeInputPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeInputPage property page

IMPLEMENT_DYNCREATE(CNodeInputPage, CPropertyPage)

CNodeInputPage::CNodeInputPage() : CPropertyPage(CNodeInputPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeInputPage)
	m_bCN_From = FALSE;
	m_FromID = _T("");
	m_bCN_Ref = FALSE;
	m_RefID = _T("");
	m_bCNTo = FALSE;
	m_ToID = _T("");
	m_X = 0.0;
	m_Y = 0.0;
	m_Z = 0.0;
	m_Length = 0.0;
	m_ID = _T("");
	m_bCN_MN = FALSE;
	//}}AFX_DATA_INIT
}

CNodeInputPage::~CNodeInputPage()
{
}

void CNodeInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeInputPage)
	DDX_Check(pDX, IDC_FROM_IS_CN, m_bCN_From);
	DDX_Text(pDX, IDC_FROMID, m_FromID);
	DDX_Check(pDX, IDC_REF_IS_CN, m_bCN_Ref);
	DDX_Text(pDX, IDC_REFNODEID, m_RefID);
	DDX_Check(pDX, IDC_TO_IS_CN, m_bCNTo);
	DDX_Text(pDX, IDC_TOID, m_ToID);
	DDX_Text(pDX, IDD_COORD_DX, m_X);
	DDX_Text(pDX, IDD_COORD_DY, m_Y);
	DDX_Text(pDX, IDD_COORD_DZ, m_Z);
	DDX_Text(pDX, IDD_LENGTH, m_Length);
	DDX_Text(pDX, IDD_NODE_ID, m_ID);
	DDX_Check(pDX, IDC_NODE_IS_CN_MN, m_bCN_MN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeInputPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeInputPage message handlers

BOOL CNodeInputPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_FROM_IS_CN)->EnableWindow(FALSE);
	GetDlgItem(IDC_TO_IS_CN)->EnableWindow(FALSE);
	GetDlgItem(IDC_REF_IS_CN)->EnableWindow(FALSE);
	GetDlgItem(IDC_NODE_IS_CN_MN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DIRECTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
	//////////////////////////////////	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CNodeInputPage::UpdateObjData(CString& strItemID,BOOL bCNode)
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
//		m_strType = (bCNode)?"Control Node":"Input Node";
		UpdateInfo(pNode);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CNodeInputPage::UpdateMeshData(CString& strItemID,BOOL bCNode)
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
//		m_strType = (bCNode)?"Mesh Control Node":"Mesh Node";
		UpdateInfo((CDrNode*)pNode);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CNodeInputPage::UpdateInfo(CDrNode* pNode)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR);
	////////////////////////////////////////////////////////////////////////////////
	m_ID		= pNode->GetObjectID();
	m_bCN_MN	= pNode->IsControlNode();
	////////////////////////////////////
	BOOL bCoord	= pNode->GetInputMode();
	///
	if(bCoord)
	{
		m_X			= pNode->GetDelta()->x;
		m_Y			= pNode->GetDelta()->y;
		m_Z			= pNode->GetDelta()->z;
		////////////////////////////////////////////////////////// 
		LONG  lWorldBase  = pPrecision->GetWorldBase(); 
	  	double dWorldBase = (double)lWorldBase; 
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
	}
	else
	{
		m_RefID		= (pNode->GetNodeCard())->nid_r;
		m_bCN_Ref	= pNode->IsRefCN();
		m_FromID	= pNode->GetFromID();
		m_bCN_From	= pNode->IsFromCN();
		m_ToID		= pNode->GetToID();
		m_bCNTo		= pNode->IsToCN();
		m_Length	= pNode->GetLength();
	}
	/////////////////
	return 0;
}

BOOL CNodeInputPage::OnSetActive() 
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
