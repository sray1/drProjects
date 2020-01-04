// NodeTopoPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "NodeSheet.h"
/////////////////////
#include "NodeTopoPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNodeTopoPage property page

IMPLEMENT_DYNCREATE(CNodeTopoPage, CPropertyPage)

CNodeTopoPage::CNodeTopoPage() : CPropertyPage(CNodeTopoPage::IDD)
{
	//{{AFX_DATA_INIT(CNodeTopoPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CNodeTopoPage::~CNodeTopoPage()
{
}

void CNodeTopoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNodeTopoPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNodeTopoPage, CPropertyPage)
	//{{AFX_MSG_MAP(CNodeTopoPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodeTopoPage message handlers

int CNodeTopoPage::UpdateObjData(CString& strItemID,BOOL bCNode)
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
	CDrNode* pNode = (CDrFE0D*)(pList->GetObject(index));
	m_pCurrentNode = (CDrNode*)pNode;
	///////////////////////
	if(pNode)
	{
		///
		UpdateCombo(pNode->GetNodeList(),IDC_NODECOMBO);
		UpdateCombo(pNode->GetCurveList(),IDC_CURVECOMBO);
		UpdateCombo(pNode->GetPatchList(),IDC_PATCHCOMBO);
		UpdateCombo(pNode->GetSolidList(),IDC_SOLIDCOMBO);
		UpdateCombo(pNode->GetObj3DList(),IDC_OBJ3DCOMBO);
		UpdateCombo(pNode->GetCProfList(),IDC_COR1DPROCOMBO);
		UpdateCombo(pNode->GetMbjProfList(),IDC_MBJ3DPROCOMBO);
		UpdateCombo(pNode->GetFE0DList(),IDC_MNODECOMBO);
		UpdateCombo(pNode->GetMs1List(),IDC_MESH1DCOMBO);
		UpdateCombo(pNode->GetMs2List(),IDC_MESH2DCOMBO);
		UpdateCombo(pNode->GetMs3List(),IDC_MESH3DCOMBO);
		UpdateCombo(pNode->GetMbj3DList(),IDC_MBJ3DCOMBO);
		UpdateCombo(pNode->GetM2DProfList(),IDC_2DPROCOMBO);
		UpdateCombo(pNode->GetM3DProfList(),IDC_3DPROCOMBO);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CNodeTopoPage::UpdateMeshData(CString& strItemID,BOOL bCNode)
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
	m_pCurrentFE0D = pNode;
	m_pCurrentNode = (CDrNode*)pNode;
	///////////////////////
	if(pNode)
	{
		///
		UpdateCombo(pNode->GetNodeList(),IDC_NODECOMBO);
		UpdateCombo(pNode->GetCurveList(),IDC_CURVECOMBO);
		UpdateCombo(pNode->GetPatchList(),IDC_PATCHCOMBO);
		UpdateCombo(pNode->GetSolidList(),IDC_SOLIDCOMBO);
		UpdateCombo(pNode->GetObj3DList(),IDC_OBJ3DCOMBO);
		UpdateCombo(pNode->GetCProfList(),IDC_COR1DPROCOMBO);
		UpdateCombo(pNode->GetMbjProfList(),IDC_MBJ3DPROCOMBO);
		UpdateCombo(pNode->GetFE0DList(),IDC_MNODECOMBO);
		UpdateCombo(pNode->GetMs1List(),IDC_MESH1DCOMBO);
		UpdateCombo(pNode->GetMs2List(),IDC_MESH2DCOMBO);
		UpdateCombo(pNode->GetMs3List(),IDC_MESH3DCOMBO);
		UpdateCombo(pNode->GetMbj3DList(),IDC_MBJ3DCOMBO);
		UpdateCombo(pNode->GetM2DProfList(),IDC_2DPROCOMBO);
		UpdateCombo(pNode->GetM3DProfList(),IDC_3DPROCOMBO);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}


int CNodeTopoPage::UpdateCombo(CDListMgr* pList, UINT DlgComboID)
{
	if(pList->IsEmpty())
		return 0;
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(DlgComboID);
   	((CComboBox*)pWndCtrl)->ResetContent();	// Remove ALL  
	CDrObject* pObject;			       
	POSITION pos;
	///	
	pos = pList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pList->GetNextObject( pos);
    	((CComboBox*)pWndCtrl)->AddString(pObject->GetObjectID());	// Show ALL  
   	}
	///
   	((CComboBox*)pWndCtrl)->SetCurSel(0);
	/////////////////
	return 0;
}

BOOL CNodeTopoPage::OnSetActive() 
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
