// PatchTopoPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "DrSolid.h"
#include "PatchSheet.h"
/////////////////////
#include "PatchTopoPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatchTopoPage property page

IMPLEMENT_DYNCREATE(CPatchTopoPage, CPropertyPage)

CPatchTopoPage::CPatchTopoPage() : CPropertyPage(CPatchTopoPage::IDD)
{
	//{{AFX_DATA_INIT(CPatchTopoPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPatchTopoPage::~CPatchTopoPage()
{
}

void CPatchTopoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPatchTopoPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPatchTopoPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPatchTopoPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatchTopoPage message handlers

int CPatchTopoPage::UpdateObjData(CString& strItemID)
{
	if(strItemID == "")
		return -1;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetObjectList(PATCH);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(PATCH,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	CDrPatch* pObject = (CDrPatch*)(pList->GetObject(index));
	///////////////////////
	if(pObject)
	{
		UpdateCombo(pObject->GetNodTopoList(),IDC_NODETOPOCOMBO);
		///
		UpdateCombo(pObject->GetNodeList(),IDC_NODECOMBO);
		UpdateCombo(pObject->GetCurveList(),IDC_PATCHCOMBO);
		UpdateCombo(pObject->GetPatchList(),IDC_PATCHCOMBO);
		UpdateCombo(pObject->GetSolidList(),IDC_PATCHCOMBO);
		UpdateCombo(pObject->GetObj3DList(),IDC_OBJ3DCOMBO);
		UpdateCombo(pObject->GetCProfList(),IDC_COR1DPROCOMBO);
		UpdateCombo(pObject->GetMbjProfList(),IDC_MBJ3DPROCOMBO);
		UpdateCombo(pObject->GetFE0DList(),IDC_MNODECOMBO);
		UpdateCombo(pObject->GetMs1List(),IDC_MESH1DCOMBO);
		UpdateCombo(pObject->GetMs2List(),IDC_MESH2DCOMBO);
		UpdateCombo(pObject->GetMs3List(),IDC_MESH3DCOMBO);
		UpdateCombo(pObject->GetMbj3DList(),IDC_MBJ3DCOMBO);
		UpdateCombo(pObject->GetM2DProfList(),IDC_2DPROCOMBO);
		UpdateCombo(pObject->GetM3DProfList(),IDC_3DPROCOMBO);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CPatchTopoPage::UpdateCombo(CDListMgr* pList, UINT DlgComboID)
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

BOOL CPatchTopoPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	UpdateObjData(((CPatchSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
