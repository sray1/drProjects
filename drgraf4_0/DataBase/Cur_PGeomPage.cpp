// Cur_PGeomPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
#include "ObjMgr.h"
#include "DListMgr.h"
#include "DrProf_C.h"
#include "Cur_PSheet.h"
/////////////////////
#include "Cur_PGeomPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCur_PGeomPage property page

IMPLEMENT_DYNCREATE(CCur_PGeomPage, CPropertyPage)

CCur_PGeomPage::CCur_PGeomPage() : CPropertyPage(CCur_PGeomPage::IDD)
{
	//{{AFX_DATA_INIT(CCur_PGeomPage)
	m_Cur_P_ID = _T("");
	m_Curve_ID = _T("");
	//}}AFX_DATA_INIT
}

CCur_PGeomPage::~CCur_PGeomPage()
{
}

void CCur_PGeomPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCur_PGeomPage)
	DDX_Text(pDX, IDD_CUR_P_ID, m_Cur_P_ID);
	DDX_Text(pDX, IDD_CURVE_ID, m_Curve_ID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCur_PGeomPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCur_PGeomPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCur_PGeomPage message handlers

int CCur_PGeomPage::UpdateObjData(CString& strItemID)
{
	if(strItemID == "")
		return -1;
	////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pList		= pObjectMgr->GetObjectList(C_PROFILE);
	////////////////////////////////////////////////////////// 
	if(pList->GetCount()<=0)
		return 0;
	/////////////////////////////////////////
	int index = pList->GetObjectIndex(C_PROFILE,strItemID);	// ONLY for DrObject
	if(index<0)
		return 0;
	/////////////////////////////////////////
	CDrProf_C* pCur_P = (CDrProf_C*)(pList->GetObject(index));
	if(pCur_P)
	{
		m_Cur_P_ID = pCur_P->GetObjectID();
		m_Curve_ID = (pCur_P->GetCurve())->GetObjectID();
		CDListMgr* pList = pCur_P->GetCurveList();	// curves
 		UpdateList(pList,IDD_CPOOLLIST);
		GetDlgItem(IDD_CPOOLLIST)->EnableWindow(FALSE);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CCur_PGeomPage::UpdateList(CDListMgr* pList, UINT DlgListID)
{
	if(pList->IsEmpty())
		return 0;
	//////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(DlgListID);
   	((CListBox*)pWndCtrl)->ResetContent();	// Remove ALL  
	CDrObject* pObject;			       
	POSITION pos;
	///	
	pos = pList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pList->GetNextObject( pos);
    	((CListBox*)pWndCtrl)->AddString(pObject->GetObjectID());	// Show ALL  
   	}
	/////////////////
	return 0;
}

BOOL CCur_PGeomPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	UpdateObjData(((CCur_PSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
