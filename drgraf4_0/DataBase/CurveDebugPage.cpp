// CurveDebugPage.cpp : implementation file
//

#include "stdafx.h"
/////////////////////
#include "Drgraf.h"
#include "Drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Mouse.h"
#include "CurveSheet.h"
/////////////////////
#include "CurveDebugPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
////////////////////////
#define	new DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////////////////////////////////////////////
// CCurveDebugPage property page

IMPLEMENT_DYNCREATE(CCurveDebugPage, CPropertyPage)

CCurveDebugPage::CCurveDebugPage() : CPropertyPage(CCurveDebugPage::IDD)
{
	//{{AFX_DATA_INIT(CCurveDebugPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCurveDebugPage::~CCurveDebugPage()
{
}

void CCurveDebugPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveDebugPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurveDebugPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCurveDebugPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveDebugPage message handlers

int CCurveDebugPage::UpdateObjData(CString& strItemID)
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
	if(pCurve)
	{
		UpdateInfo(pCurve);
		/////////////////
		UpdateData(FALSE);
		/////////////////
	}
	return 0;
}

int CCurveDebugPage::UpdateInfo(CDrCurve* pCurve)
{
	CMouse Mouse;
	/////////////
	CURVEPROC CurveProc = pCurve->GetCurveType_S();
	//////////////////////////////////////////////////////// Combos
	CDListMgr* pList;
	pList = pCurve->GetCNodeList();
	UpdateCombo(pList,IDC_CNODECOMBO);
	pList = pCurve->GetVNodeList();
	UpdateCombo(pList,IDC_ENODECOMBO);
	pList = pCurve->GetElemList();
	UpdateCombo(pList,IDC_ELEMCOMBO);
	int nCN_BZ = pCurve->GetnCon_BZ_S() ;
	pDOUBLE pBZWts	= pCurve->GetpWts_BZ_S(); 
	UpdateCombo_Double(pBZWts,nCN_BZ,IDC_BZWTSCOMBO);
	////////////////////////////////////////////////////////
	if(CurveProc == CP_CIRCLE)
		UpdateInfoCircle(pCurve);
	else
		UpdateInfoCurve(pCurve);
	/////////
	return 0;
}

int CCurveDebugPage::UpdateInfoCurve(CDrCurve* pCurve)
{
	CMouse Mouse;
	/////////////
	/////////////////
	return 0;
}

int CCurveDebugPage::UpdateInfoCircle(CDrCurve* pCurve)
{
	CMouse Mouse;
	/////////////
	/////////////////
	return 0;
}

int CCurveDebugPage::UpdateCombo(CDListMgr* pList, UINT DlgComboID)
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

int CCurveDebugPage::UpdateCombo_Double(pDOUBLE pData, int nData, UINT DlgComboID)
{
	if(nData<=0)
		return 0;
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(DlgComboID);
   	((CComboBox*)pWndCtrl)->ResetContent();	// Remove ALL  
	///
	for(int i=0;i<nData;i++)
	{
		double dData = pData[i];
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		sprintf(buf,"%f",dData);
		///
    	((CComboBox*)pWndCtrl)->AddString(*str);
		///
		delete str;
   	}
	///
//   	((CComboBox*)pWndCtrl)->SetCurSel(0);
	/////////////////
	return 0;
}

int CCurveDebugPage::UpdateCombo_Int(pINT pData, int nData, UINT DlgComboID)
{
	if(nData<=0)
		return 0;
	////////////////////////////////////////////////////////// 
	CWnd* pWndCtrl = GetDlgItem(DlgComboID);
   	((CComboBox*)pWndCtrl)->ResetContent();	// Remove ALL  
	///
	for(int i=0;i<nData;i++)
	{
		int nElem = pData[i];
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		sprintf(buf,"%d",nElem);
		///
    	((CComboBox*)pWndCtrl)->AddString(*str);
		///
		delete str;
   	}
	///
//   	((CComboBox*)pWndCtrl)->SetCurSel(0);
	/////////////////
	return 0;
}

BOOL CCurveDebugPage::OnSetActive() 
{
	if(!CPropertyPage::OnSetActive())
		return FALSE;
	///////////
	UpdateObjData(((CCurveSheet*)GetParent())->GetstrItem());
	////////////
	return TRUE;
}
