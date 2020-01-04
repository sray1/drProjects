// dlg_PatI.cpp : implementation file
//

#include "stdafx.h"

#include "3DMath.h"

#include "UserMsg.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
#include "Def_Mous.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
////////////////////
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"
#include "MPatRsrc.h"
/////////////////////
#include "SasePage.h"
#include "XtruLens.h"
#include "Dlg_SI_Xtrude.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Xtrude dialog
IMPLEMENT_DYNCREATE(CDlg_SI_Xtrude, CSasePage)

CDlg_SI_Xtrude::CDlg_SI_Xtrude(): CSasePage()
{
}

CDlg_SI_Xtrude::CDlg_SI_Xtrude(CWnd* pMainWnd,SOLIDPROC SolProc)
				: CSasePage(pMainWnd,SolProc,CDlg_SI_Xtrude::IDD)
{
	//{{AFX_DATA_INIT(CDlg_SI_Xtrude)
	m_nMesh		= 1;
	m_dLen		= 0.0;
	m_dCoord	= 0.0;
	m_Orient_P = _T("");
	//}}AFX_DATA_INIT
	m_nExtruType= 1;
}

CDlg_SI_Xtrude::~CDlg_SI_Xtrude()
{
}

void CDlg_SI_Xtrude::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SI_Xtrude)
	DDX_CBString(pDX, IDC_SID, m_SID);
	DDX_CBString(pDX, IDC_PID, m_PID);
	DDX_CBString(pDX, IDC_NID, m_NID);
	DDX_Text(pDX, IDC_ELEMS, m_nMesh);
	DDV_MinMaxInt(pDX, m_nMesh, 1, 9999);
	DDX_Text(pDX, IDC_RATIO, m_Ratio);
	DDX_Text(pDX, IDC_LEN, m_dLen);
	DDX_Text(pDX, IDC_COORD, m_dCoord);
	DDV_MinMaxDouble(pDX, m_dCoord, 0., 1.e+031);
	DDX_Check(pDX, IDC_GENBCURVE, m_bGenBCurve);
	DDX_Check(pDX, IDC_GENBPATCH, m_bGenBPatch);
	DDX_CBString(pDX, IDC_ORIENT_P, m_Orient_P);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_SI_Xtrude, CSasePage)
	//{{AFX_MSG_MAP(CDlg_SI_Xtrude)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_SID, OnSelchangeSid)
	ON_CBN_SELCHANGE(IDC_PID, OnSelchangePid)
	ON_CBN_SELCHANGE(IDC_NID, OnSelchangeNid)
	ON_BN_CLICKED(IDC_GENBPATCH, OnGenBPatch)
	ON_BN_CLICKED(IDC_GENBCURVE, OnGenBCurve)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_EXTRU_1, OnExtru1)
	ON_BN_DOUBLECLICKED(IDC_EXTRU_1, OnExtru1)
	ON_BN_CLICKED(IDC_EXTRU_2, OnExtru2)
	ON_BN_DOUBLECLICKED(IDC_EXTRU_2, OnExtru2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMSol_DLL;
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Xtrude message handlers
BOOL CDlg_SI_Xtrude::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	int nMax;
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(SOLID);
	nMax			= pDListMgr->GetSpecificObjectCount(SOLID);
	if(nMax)
		FillListAllString_Solid();   //  with Solids
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(PATCH);
	nMax			= pDListMgr->GetSpecificObjectCount(PATCH);
	if(nMax)
		FillListAllString_Patch();   //  with Patches
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(NODE);
	nMax			= pDListMgr->GetSpecificObjectCount(NODE);
	if(nMax)
		FillListAllString_Node();   //  with Curves
	////////////////////////////////////////// Headings
	ResetDlg();
	////////////////////////////////////////// Focus
	CWnd* pWndCtrl = GetDlgItem(IDC_SID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_SI_Xtrude::ResetDlg()
{
	////////////////////////////////////////// Headings
	GetDlgItem(IDC_ORIENT_P)->EnableWindow(TRUE);
 	((CComboBox*)GetDlgItem(IDC_ORIENT_P))->SetCurSel(0);//Backward=1/Forward=0
	/////////////////
	SetWindowText("Solid by EXTRUSION");
	GetDlgItem(IDC_PIDHEAD)->SetWindowText("Extrn. Patch");
	GetDlgItem(IDC_NIDHEAD)->SetWindowText("Dirn. Node From");
	GetDlgItem(IDC_LENHEAD)->SetWindowText("Length");
	GetDlgItem(IDC_SID)->EnableWindow(TRUE);
	GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	GetDlgItem(IDC_NID)->EnableWindow(TRUE);
	//////
	GetDlgItem(IDC_LENHEAD)->SetWindowText("Length");
	GetDlgItem(IDC_LEN)->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_EXTRU_1))->SetCheck(TRUE);
	//////
	GetDlgItem(IDC_OTHER)->SetWindowText("");
	GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
	//////
	GetDlgItem(IDC_ELEMS)->EnableWindow(TRUE);
	GetDlgItem(IDC_RATIO)->EnableWindow(TRUE);
}

void CDlg_SI_Xtrude::OnExtru1() 
{
	m_nExtruType= 1;
	//////
	GetDlgItem(IDC_LENHEAD)->SetWindowText("Length");
	GetDlgItem(IDC_LEN)->EnableWindow(TRUE);
	//////
}

void CDlg_SI_Xtrude::OnExtru2() 
{
	m_nExtruType= 2;
	//////
	GetDlgItem(IDC_LENHEAD)->SetWindowText("");
	GetDlgItem(IDC_LEN)->EnableWindow(FALSE);
	/////////////////////////////////////////// Open DialogBox
	CXtruLens Dlg;
	if(Dlg.DoModal() == IDOK)
	{
		m_wLen.x = Dlg.m_Xtru_X;
		m_wLen.y = Dlg.m_Xtru_Y;
		m_wLen.z = Dlg.m_Xtru_Z;
	}
	else
		m_nExtruType= 1;
	////////
}

void CDlg_SI_Xtrude::OnGenBCurve() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_SI_Xtrude::OnGenBPatch() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_SI_Xtrude::OnSelchangeSid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_SI_Xtrude::OnSelchangePid() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CWnd*		pWndCtrl;
	CString		Cid;
	CDrPatch*	pDrPatch;
	/////////////////////////////////
	pWndCtrl = GetDlgItem(IDC_PID);
    int index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	if(index>=0)
		((CComboBox*)(pWndCtrl))->GetLBText(index,Cid);
	else
		return;
	////////////
	index	= pObjectMgr->GetObjectIndexfromKey(PATCH,Cid,1);
	if(index>=0)
	{
		pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
		m_nMesh		= pDrPatch->GetMaxOutPts_S() - 1;
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_SI_Xtrude::OnSelchangeNid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_SI_Xtrude::OnUpdate()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_SOLIN,IDC_UPDATE);
	////////////////////////////////////////////////////
}

void CDlg_SI_Xtrude::OnCancel()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_SOLIN,IDD_CANCEL);
	////////////////////////////////////////////////////
//	CPropertyPage::OnCancel();
}
    
void CDlg_SI_Xtrude::FillListAllString_Patch()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_PID);
	//////////////////////////
	CString Cid;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(PATCH);
    if(nMaxCurves<=0)
    	return;
    //////////////////////////////////////////////////////////	
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == PATCH)
		{ 
			CDrPatch* pCurve = (CDrPatch*)pObject;
			Cid   = pCurve->GetObjectID();
	    	((CComboBox*)(pWndCtrl))->AddString(Cid);
		}			    
   	}
   	///////////////////////////////////
   	pWndCtrl->EnableWindow(FALSE);		// Always Disabled
   	////////
    
}
    
void CDlg_SI_Xtrude::FillListAllString_Solid()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_SID);
	//////////////////////////
	CString Cid;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(SOLID);
    if(nMaxCurves<=0)
    	return;
    //////////////////////////////////////////////////////////	
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == SOLID)
		{ 
			CDrSolid* pSolid = (CDrSolid*)pObject;
			Cid   = pSolid->GetObjectID();
	    	((CComboBox*)(pWndCtrl))->AddString(Cid);
		}			    
   	}
   	///////////////////////////////////
   	pWndCtrl->EnableWindow(FALSE);		// Always Disabled
   	////////
    
}

void CDlg_SI_Xtrude::FillListAllString_Node()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_NID);
	CString Nid;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);
    if(nMaxNodes>0)
    {
		CDrObject* pObject;			       
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if( pObject->GetObjectType() == NODE)
			{ 
				CDrNode* pNode = (CDrNode*)pObject;
				if(!((pNode->GetNodeCard())->bnid_c))             // Only with Data Nodes
				{
	   				Nid   = (pNode->GetNodeCard())->id;
			    	((CComboBox*)(pWndCtrl))->AddString(Nid);
			    }	 
			}			    
    	}
	} 
    
}
////////////////////////////////// end of module //////////////////////
