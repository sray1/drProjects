// CurveTopoPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "DrCurve.h"
#include "CurveSheet.h"
/////////////////////
#include "CurveTopoPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveTopoPage property page

IMPLEMENT_DYNCREATE(CCurveTopoPage, CPropertyPage)

CCurveTopoPage::CCurveTopoPage() : CPropertyPage(CCurveTopoPage::IDD)
{
	//{{AFX_DATA_INIT(CCurveTopoPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCurveTopoPage::~CCurveTopoPage()
{
}

void CCurveTopoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveTopoPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurveTopoPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCurveTopoPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveTopoPage message handlers

int CCurveTopoPage::UpdateObjData(CString& strItemID)
{
	if(strItemID == "")
		return -1;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetObjectList(CURVE);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(CURVE,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	CDrCurve* pCurve = (CDrCurve*)(pList->GetObject(index));
	///////////////////////
	if(pCurve)
	{
		UpdateCombo(pCurve->GetNodTopoList(),IDC_NODETOPOCOMBO);
		///
		UpdateCombo(pCurve->GetNodeList(),IDC_NODECOMBO);
		UpdateCombo(pCurve->GetCurveList(),IDC_CURVECOMBO);
		UpdateCombo(pCurve->GetPatchList(),IDC_PATCHCOMBO);
		UpdateCombo(pCurve->GetSolidList(),IDC_SOLIDCOMBO);
		UpdateCombo(pCurve->GetObj3DList(),IDC_OBJ3DCOMBO);
		UpdateCombo(pCurve->GetCProfList(),IDC_COR1DPROCOMBO);
		UpdateCombo(pCurve->GetMbjProfList(),IDC_MBJ3DPROCOMBO);
		UpdateCombo(pCurve->GetFE0DList(),IDC_MNODECOMBO);
		UpdateCombo(pCurve->GetMs1List(),IDC_MESH1DCOMBO);
		UpdateCombo(pCurve->GetMs2List(),IDC_MESH2DCOMBO);
		UpdateCombo(pCurve->GetMs3List(),IDC_MESH3DCOMBO);
		UpdateCombo(pCurve->GetMbj3DList(),IDC_MBJ3DCOMBO);
		UpdateCombo(pCurve->GetM2DProfList(),IDC_2DPROCOMBO);
		UpdateCombo(pCurve->GetM3DProfList(),IDC_3DPROCOMBO);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CCurveTopoPage::UpdateCombo(CDListMgr* pList, UINT DlgComboID)
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

BOOL CCurveTopoPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	UpdateObjData(((CCurveSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
