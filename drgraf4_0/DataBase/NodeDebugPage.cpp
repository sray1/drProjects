// CNodeDebugPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "Drgraf.h"
#include "Drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
/////////////////////
#include "DrNode.h"
#include "DrFE0D.h"
#include "NodeSheet.h"
/////////////////////
#include "NodeDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeDebugPage property page

IMPLEMENT_DYNCREATE(CNodeDebugPage, CPropertyPage)

CNodeDebugPage::CNodeDebugPage() : CPropertyPage(CNodeDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeDebugPage)
	m_LocalPos_X = 0.0;
	m_LocalPos_Y = 0.0;
	m_LocalPos_Z = 0.0;
	m_Pt_X = 0;
	m_Pt_Y = 0;
	m_Normal2D_X = 0;
	m_Normal2D_Y = 0;
	m_NormalWorld_X = 0.0;
	m_NormalWorld_Y = 0.0;
	m_NormalWorld_Z = 0.0;
	m_EyePosX = 0.0;
	m_EyePosY = 0.0;
	m_EyePosZ = 0.0;
	m_ScreenPos3DX = 0.0;
	m_ScreenPos3DY = 0.0;
	m_ScreenPos3DZ = 0.0;
	m_WorldPosX = 0.0;
	m_WorldPosY = 0.0;
	m_WorldPosZ = 0.0;
	//}}AFX_DATA_INIT
}

CNodeDebugPage::~CNodeDebugPage()
{
}

void CNodeDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeDebugPage)
	DDX_Text(pDX, IDC_LOCALPOSX, m_LocalPos_X);
	DDX_Text(pDX, IDC_LOCALPOSY, m_LocalPos_Y);
	DDX_Text(pDX, IDC_LOCALPOSZ, m_LocalPos_Z);
	DDX_Text(pDX, IDC_M_PTX, m_Pt_X);
	DDX_Text(pDX, IDC_M_PTY, m_Pt_Y);
	DDX_Text(pDX, IDC_NORMAL2DX, m_Normal2D_X);
	DDX_Text(pDX, IDC_NORMAL2DY, m_Normal2D_Y);
	DDX_Text(pDX, IDC_NORMALWORLDX, m_NormalWorld_X);
	DDX_Text(pDX, IDC_NORMALWORLDY, m_NormalWorld_Y);
	DDX_Text(pDX, IDC_NORMALWORLDZ, m_NormalWorld_Z);
	DDX_Text(pDX, IDC_EYEPOSX, m_EyePosX);
	DDX_Text(pDX, IDC_EYEPOSY, m_EyePosY);
	DDX_Text(pDX, IDC_EYEPOSZ, m_EyePosZ);
	DDX_Text(pDX, IDC_SCREENPOS3DX, m_ScreenPos3DX);
	DDX_Text(pDX, IDC_SCREENPOS3DY, m_ScreenPos3DY);
	DDX_Text(pDX, IDC_SCREENPOS3DZ, m_ScreenPos3DZ);
	DDX_Text(pDX, IDC_WORLDPOSX, m_WorldPosX);
	DDX_Text(pDX, IDC_WORLDPOSY, m_WorldPosY);
	DDX_Text(pDX, IDC_WORLDPOSZ, m_WorldPosZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeDebugPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeDebugPage message handlers

BOOL CNodeDebugPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CNodeDebugPage::UpdateObjData(CString& strItemID,BOOL bCNode)
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
		UpdateInfo(pNode);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CNodeDebugPage::UpdateMeshData(CString& strItemID,BOOL bCNode)
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
		UpdateInfo((CDrNode*)pNode);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CNodeDebugPage::UpdateInfo(CDrNode* pNode)
{
	////////////////////////////////////////////////////////////////////////////////
	m_LocalPos_X	= (pNode->GetLocalPos())->x;
	m_LocalPos_Y	= (pNode->GetLocalPos())->y;
	m_LocalPos_Z	= (pNode->GetLocalPos())->z;
	m_WorldPosX		= (pNode->GetWorldPos())->x;
	m_WorldPosY		= (pNode->GetWorldPos())->y;
	m_WorldPosZ		= (pNode->GetWorldPos())->z;
	m_EyePosX		= (pNode->GetEyePos())->x;
	m_EyePosY		= (pNode->GetEyePos())->y;
	m_EyePosZ		= (pNode->GetEyePos())->z;
	m_ScreenPos3DX	= (pNode->GetScreenPos3D())->x;
	m_ScreenPos3DY	= (pNode->GetScreenPos3D())->y;
	m_ScreenPos3DZ	= (pNode->GetScreenPos3D())->z;
	m_Pt_X			= (pNode->GetScreenPos2D())->x;
	m_Pt_Y			= (pNode->GetScreenPos2D())->y;
	m_NormalWorld_X = (pNode->GetNormalWorld())->x;
	m_NormalWorld_Y = (pNode->GetNormalWorld())->y;
	m_NormalWorld_Z = (pNode->GetNormalWorld())->z;
	m_Normal2D_X	= (pNode->GetNormalScreen2D())->x;
	m_Normal2D_Y	= (pNode->GetNormalScreen2D())->y;
	/////////////////
	return 0;
}

BOOL CNodeDebugPage::OnSetActive() 
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
