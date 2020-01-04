// dlg_cpro.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrCurve.h"
#include "DrProf_C.h"
////////////////////
#include "CommRsrc.h"
#include "dlg_CPSI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CPSI dialog


CDlg_CPSI::CDlg_CPSI(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CPSI::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CPSI)
	m_CPro_ID 	= "";
	//}}AFX_DATA_INIT
}

void CDlg_CPSI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CPSI)
	DDX_Text(pDX, IDC_CID_PROF, m_CPro_ID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_CPSI, CDialog)
	//{{AFX_MSG_MAP(CDlg_CPSI)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_LBN_SELCHANGE(IDD_POOLLIST, OnSelchangePoollist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_CPSI message handlers

BOOL CDlg_CPSI::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	//structural
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	int nMax = m_pCurveList->GetCount();
	if(nMax)
		FillListAllString_Pool();   // only with Curves
	pDListMgr	= pObjectMgr->GetObjectList(C_PROFILE);
	nMax = pDListMgr->GetSpecificObjectCount(C_PROFILE);
	if(nMax)
		FillListAllString_Profile();   // only with C_Profiles
   	///////////////////////////////////
//	GetDlgItem(IDD_LATCHLIST)->EnableWindow(FALSE);		// Always Disabled
	///////////////////////////////////////////////////////////
	GetDlgItem(IDC_CID_PROF)->SetFocus();
	///////////////////////////////////////////////////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_CPSI::EmptyListAllString(UINT DlgID)
{
			 
	CWnd* pWndCtrl = GetDlgItem(DlgID);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 

void CDlg_CPSI::OnSelchangePoollist() 
{
	//////////////////////////////////////////////// Get Transformation Details	 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE) 
	////////////////////
	CListBox* pWndPul = (CListBox*)GetDlgItem(IDD_POOLLIST);
	int index = pWndPul->GetCurSel();
	if(index<0)
		return;
	/////////////
	CString	Cid;
	pWndPul->GetText(index,Cid);
	////////////////////////////
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	if((index= pDListMgr->GetObjectIndex(CURVE,Cid)) <0)
	{
		AfxMessageBox("Internal Problem:CDlg_CPro::OnAdd");
		return;
	}
	//////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectIndex(index);	// set Active Index									
	pObjectMgr->SetActiveObjectType(CURVE);	    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,index,CURVE);
	////////////////////////////////////////////////////////// 
	
}

void CDlg_CPSI::OnOK()
{
	// DONE
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
   	/////////////////////////////////////////////// Profile ID
   	if("" == m_CPro_ID)
   	{
   		AfxMessageBox("Please Select a Profile ID");
   		return;
   	}
	///////////////
	CDialog::OnOK();
}

void CDlg_CPSI::OnCancel()
{
	////////////////////
	CDialog::OnCancel();
}

void CDlg_CPSI::FillListAllString_Pool()
{
	// with CURVES
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////
	int nMax = m_pCurveList->GetCount();
    if(nMax<=0)
    	return;
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
	CString Nid;
	CDrObject* pObject;			       
	
	POSITION pos = m_pCurveList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)m_pCurveList->GetNextObject( pos);
		if( pObject->GetObjectType() == CURVE)
		{ 
			CDrCurve* pNode = (CDrCurve*)pObject;
			Nid = pNode->GetObjectID();
	    	((CListBox*)(pWndCtrl))->AddString(Nid);
		}			    
   	}
    
}
    
void CDlg_CPSI::FillListAllString_Profile()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(C_PROFILE);
	//////////////////////////////////////////////////////
	int nMax = pDListMgr->GetSpecificObjectCount(C_PROFILE);
    if(nMax<=0)
    	return;
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	CString Cid;
    //////////////////////////////////////////////////////////	
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == C_PROFILE)
		{ 
			CDrProf_C* pCurve = (CDrProf_C*)pObject;
			Cid   = pCurve->GetObjectID();
	    	((CListBox*)(pWndCtrl))->AddString(Cid);
		}			    
   	}
   	///////////////////////////////////
   	pWndCtrl->EnableWindow(FALSE);		// Always Disabled
   	////////
    
}

////////////////////////////////////// end of Module ///////////////////////////
