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
#include "Def_Elem.h"
#include "DrMesh1D.h"
#include "DrProf_1.h"
////////////////////
#include "CommRsrc.h"
#include "dlg_1Mrg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_1Mrg dialog


CDlg_1Mrg::CDlg_1Mrg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_1Mrg::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_1Mrg)
	m_CPro_ID 	= "";
	//}}AFX_DATA_INIT
}

void CDlg_1Mrg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_1Mrg)
	DDX_Text(pDX, IDC_CID_PROF, m_CPro_ID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_1Mrg, CDialog)
	//{{AFX_MSG_MAP(CDlg_1Mrg)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_LBN_SELCHANGE(IDD_POOLLIST, OnSelchangePoollist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_1Mrg message handlers

BOOL CDlg_1Mrg::OnInitDialog()
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
	int nMax = m_pMesh1DList->GetCount();
	if(nMax)
		FillListAllString_Pool();   // only with Mesh1Ds
	pDListMgr	= pObjectMgr->GetObjectList(M1_PROFILE);
	nMax = pDListMgr->GetSpecificObjectCount(M1_PROFILE);
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

void CDlg_1Mrg::EmptyListAllString(UINT DlgID)
{
			 
	CWnd* pWndCtrl = GetDlgItem(DlgID);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
} 

void CDlg_1Mrg::OnSelchangePoollist() 
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
	pDListMgr	= pObjectMgr->GetObjectList(MESH1D);
	if((index= pDListMgr->GetObjectIndex(MESH1D,Cid)) <0)
	{
		AfxMessageBox("Internal Problem:CDlg_1Mrg::OnSelchangePoollist");
		return;
	}
	//////////////////////////////////////////////////////////
	pObjectMgr->SetActiveObjectIndex(index);	// set Active Index									
	pObjectMgr->SetActiveObjectType(MESH1D);	    // set Active Type									
	pObjectMgr->UpdateAllViewsWithActiveIndex(NULL,index,MESH1D);
	////////////////////////////////////////////////////////// 
	
}

void CDlg_1Mrg::OnOK()
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

void CDlg_1Mrg::OnCancel()
{
	////////////////////
	CDialog::OnCancel();
}

void CDlg_1Mrg::FillListAllString_Pool()
{
	// with MESH1DS
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////////////////////////////////////
	int nMax = m_pMesh1DList->GetCount();
    if(nMax<=0)
    	return;
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
	CString Nid;
	CDrObject* pObject;			       
	
	POSITION pos = m_pMesh1DList->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)m_pMesh1DList->GetNextObject( pos);
		if( pObject->GetObjectType() == MESH1D)
		{ 
			CDrMesh1D* pNode = (CDrMesh1D*)pObject;
			Nid = pNode->GetObjectID();
	    	((CListBox*)(pWndCtrl))->AddString(Nid);
		}			    
   	}
    
}
    
void CDlg_1Mrg::FillListAllString_Profile()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(M1_PROFILE);
	//////////////////////////////////////////////////////
	int nMax = pDListMgr->GetSpecificObjectCount(M1_PROFILE);
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
		if( pObject->GetObjectType() == M1_PROFILE)
		{ 
			CDrProf_1* pMesh1D = (CDrProf_1*)pObject;
			Cid   = pMesh1D->GetObjectID();
	    	((CListBox*)(pWndCtrl))->AddString(Cid);
		}			    
   	}
   	///////////////////////////////////
   	pWndCtrl->EnableWindow(FALSE);		// Always Disabled
   	////////
    
}

////////////////////////////////////// end of Module ///////////////////////////
