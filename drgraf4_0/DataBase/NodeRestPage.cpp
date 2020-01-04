// CNodeRestPage.cpp : implementation file
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
#include "NodeRestPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeRestPage property page

IMPLEMENT_DYNCREATE(CNodeRestPage, CPropertyPage)

CNodeRestPage::CNodeRestPage() : CPropertyPage(CNodeRestPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeRestPage)
	m_bRelease = FALSE;
	m_bXR = FALSE;
	m_bX = FALSE;
	m_bY = FALSE;
	m_bYR = FALSE;
	m_bZ = FALSE;
	m_bZR = FALSE;
	//}}AFX_DATA_INIT
}

CNodeRestPage::~CNodeRestPage()
{
}

void CNodeRestPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeRestPage)
	DDX_Check(pDX, IDC_RELEASE, m_bRelease);
	DDX_Check(pDX, IDC_DOFXR, m_bXR);
	DDX_Check(pDX, IDC_DOFX, m_bX);
	DDX_Check(pDX, IDC_DOFY, m_bY);
	DDX_Check(pDX, IDC_DOFYR, m_bYR);
	DDX_Check(pDX, IDC_DOFZ, m_bZ);
	DDX_Check(pDX, IDC_DOFZR, m_bZR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeRestPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeRestPage)
	ON_BN_CLICKED(IDC_RELEASE, OnRelease)
	ON_BN_DOUBLECLICKED(IDC_RELEASE, OnRelease)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeRestPage message handlers

BOOL CNodeRestPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_DOFX)->EnableWindow(FALSE);
	GetDlgItem(IDC_DOFXR)->EnableWindow(FALSE);
	GetDlgItem(IDC_DOFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_DOFYR)->EnableWindow(FALSE);
	GetDlgItem(IDC_DOFZ)->EnableWindow(FALSE);
	GetDlgItem(IDC_DOFZR)->EnableWindow(FALSE);
	///////////////////////////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CNodeRestPage::UpdateObjData(CString& strItemID,BOOL bCNode)
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

int CNodeRestPage::UpdateMeshData(CString& strItemID,BOOL bCNode)
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

int CNodeRestPage::UpdateInfo(CDrNode* pNode)
{
	///////////////////////////////
	// todo
	// create releaseclass:
	//	add createbase variable
	// create Constraintclass:
	//	add createbase variable	etc.
	////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	////////////////////////////////////////////////////////// 
	m_bXR	= FALSE;
	m_bX	= FALSE;
	m_bY	= FALSE;
	m_bYR	= FALSE;
	m_bZ	= FALSE;
	m_bZR	= FALSE;
	/////////////////
	return 0;
}

void CNodeRestPage::OnRelease() 
{
	if(m_bRelease)
		GetDlgItem(IDC_NODECOMBO)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_NODECOMBO)->EnableWindow(FALSE);
}

BOOL CNodeRestPage::OnSetActive() 
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
