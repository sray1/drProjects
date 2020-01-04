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
#include "DrSolid.h"
////////////////////
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"
#include "MPatRsrc.h"
/////////////////////
#include "SasePage.h"
#include "Dlg_SI_Loft.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Loft dialog
IMPLEMENT_DYNCREATE(CDlg_SI_Loft, CSasePage)

CDlg_SI_Loft::CDlg_SI_Loft(): CSasePage()
{
}

CDlg_SI_Loft::CDlg_SI_Loft(CWnd* pMainWnd,SOLIDPROC SolProc)
				: CSasePage(pMainWnd,SolProc,CDlg_SI_Loft::IDD)
{
	//{{AFX_DATA_INIT(CDlg_SI_Loft)
	m_bClosed	= FALSE;
	m_SegAngle 	= 120;		// Default
	m_bAutoSeg 	= TRUE;
	m_bAdvanced = FALSE;
	m_bGenBCurve = FALSE;
	m_bGenBPatch = FALSE;
	m_nMesh		= 1;
	//}}AFX_DATA_INIT
}

CDlg_SI_Loft::~CDlg_SI_Loft()
{
}

void CDlg_SI_Loft::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SI_Loft)
	DDX_CBString(pDX, IDC_PID, m_PID);
	DDX_CBString(pDX, IDC_SID, m_SID);
	DDX_Text(pDX, IDC_ELEMS, m_nMesh);
	DDV_MinMaxInt(pDX, m_nMesh, 1, 9999);
	DDX_Text(pDX, IDC_RATIO, m_Ratio);
	DDX_CBString(pDX, IDC_ORIENT_P, m_Orient_P);
	DDX_Check(pDX, IDC_CLOSED, m_bClosed);
	DDX_Text(pDX, IDC_SEGANGLE, m_SegAngle);
	DDV_MinMaxDouble(pDX, m_SegAngle, 45., 120.);
	DDX_Check(pDX, IDC_AUTOSEG, m_bAutoSeg);
	DDX_Check(pDX, IDC_ADVANCED, m_bAdvanced);
	DDX_Check(pDX, IDC_GENBCURVE, m_bGenBCurve);
	DDX_Check(pDX, IDC_GENBPATCH, m_bGenBPatch);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_SI_Loft, CSasePage)
	//{{AFX_MSG_MAP(CDlg_SI_Loft)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_PID, OnSelchangePid)
	ON_CBN_SELCHANGE(IDC_SID, OnSelchangeSid)
	ON_BN_CLICKED(IDC_CLOSED, OnClosed)
	ON_BN_CLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_EN_KILLFOCUS(IDC_SEGANGLE, OnKillfocusSegAngle)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_CLOSED, OnClosed)
	ON_BN_DOUBLECLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMSol_DLL;
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Loft message handlers
BOOL CDlg_SI_Loft::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	int nMax;
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(PATCH);
	nMax			= pDListMgr->GetSpecificObjectCount(PATCH);
	if(nMax)
		FillListAllString_Patch();   //  with Patches
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(SOLID);
	nMax			= pDListMgr->GetSpecificObjectCount(SOLID);
	if(nMax)
		FillListAllString_Solid();   //  with Solids
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

void CDlg_SI_Loft::ResetDlg()
{
	////////////////////////////////////////// Headings
	GetDlgItem(IDC_ORIENT_P)->EnableWindow(TRUE);
 	((CComboBox*)GetDlgItem(IDC_ORIENT_P))->SetCurSel(0);//Backward=1/Forward=0
	/////////////////
	SetWindowText("Solid by Lofting Patches");
	GetDlgItem(IDC_CIDHEAD)->SetWindowText("Begin Patch");
	GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	GetDlgItem(IDC_SID)->EnableWindow(TRUE);
	//////
	GetDlgItem(IDC_ELEMS)->EnableWindow(TRUE);
	GetDlgItem(IDC_RATIO)->EnableWindow(TRUE);
	//////
	((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);
	GetDlgItem(IDC_CLOSED)->EnableWindow(TRUE);
	//////
//			((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);// based on 2 curves or more
//			GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
	//////
	((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(TRUE);
	GetDlgItem(IDC_AUTOSEG)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("Seg Angle");
	GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
}

void CDlg_SI_Loft::OnSelchangeSid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_SI_Loft::OnSelchangePid() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
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

void CDlg_SI_Loft::OnUpdate()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_SOLIN,IDC_UPDATE);
	////////////////////////////////////////////////////
}

void CDlg_SI_Loft::OnCancel()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_SOLIN,IDD_CANCEL);
	////////////////////////////////////////////////////
//	CPropertyPage::OnCancel();
}
    
void CDlg_SI_Loft::FillListAllString_Patch()
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
    
void CDlg_SI_Loft::FillListAllString_Solid()
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

void CDlg_SI_Loft::OnClosed()
{
	//////////////////////////////////////////////// Update	 
//   	m_bClosed 	= !m_bClosed;
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
	////////////////////////////////////////// Select
/*
	if(m_bClosed)
	{
		m_dLen = 360.;
		GetDlgItem(IDC_LEN)->EnableWindow(FALSE);
	}
	else
	{
		if(m_SolProc == PP_ROTATE)
		{	
			GetDlgItem(IDC_LEN)->EnableWindow(TRUE);
		}		
	}
*/
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_SI_Loft::OnAutoSeg()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bAutoSeg)
		GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
	else	
		GetDlgItem(IDC_SEGANGLE)->EnableWindow(TRUE);
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_SI_Loft::OnKillfocusSegAngle()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
}

void CDlg_SI_Loft::OnAdvanced() 
{
	
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(!m_bAdvanced)
		return;
	////////////////////////////// Tangent End Data
	
}
////////////////////////////////// end of module //////////////////////
