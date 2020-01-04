// Dlg_SI_Tensor.cpp : implementation file
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
#include "DrPatch.h"
#include "DrSolid.h"
////////////////////
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"
#include "MPatRsrc.h"
//////////////////////////
#include "SasePage.h"
#include "Dlg_SI_Tensor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Tensor dialog
IMPLEMENT_DYNCREATE(CDlg_SI_Tensor, CSasePage)

CDlg_SI_Tensor::CDlg_SI_Tensor(): CSasePage()
{
}
CDlg_SI_Tensor::CDlg_SI_Tensor(CWnd* pMainWnd,SOLIDPROC SolProc)
					: CSasePage(pMainWnd,SolProc,CDlg_SI_Tensor::IDD)
{
	//{{AFX_DATA_INIT(CDlg_SI_Tensor)
	m_bClosed	= FALSE;
	m_dCoord	= 0.0;
	m_SegAngle 	= 120;		// Default
	m_bAutoSeg 	= TRUE;
	m_Ratio_V	= 1.0;
	m_bAdvanced = FALSE;
	m_bGenBCurve = FALSE;
	m_bGenBPatch = FALSE;
	m_Ratio_W	 = 1.0;
	//}}AFX_DATA_INIT
}

CDlg_SI_Tensor::~CDlg_SI_Tensor()
{
}

void CDlg_SI_Tensor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SI_Tensor)
	DDX_CBString(pDX, IDC_SID, m_SID);
	DDX_CBString(pDX, IDC_NID, m_NID);
	DDX_Text(pDX, IDC_ELEMS, m_nMesh);
	DDV_MinMaxInt(pDX, m_nMesh, 1, 9999);
	DDX_Text(pDX, IDC_RATIO, m_Ratio);
	DDX_Check(pDX, IDC_CLOSED, m_bClosed);
	DDX_Text(pDX, IDC_COORD, m_dCoord);
	DDV_MinMaxDouble(pDX, m_dCoord, 0., 1.e+031);
	DDX_Text(pDX, IDC_SEGANGLE, m_SegAngle);
	DDV_MinMaxDouble(pDX, m_SegAngle, 45., 120.);
	DDX_Check(pDX, IDC_AUTOSEG, m_bAutoSeg);
	DDX_Text(pDX, IDC_RATIOV, m_Ratio_V);
	DDX_Text(pDX, IDC_ELEMSV, m_nMesh_V);
	DDX_Check(pDX, IDC_ADVANCED, m_bAdvanced);
	DDX_Check(pDX, IDC_GENBCURVE, m_bGenBCurve);
	DDX_Check(pDX, IDC_GENBPATCH, m_bGenBPatch);
	DDX_Text(pDX, IDC_ELEMSW, m_nMesh_W);
	DDX_Text(pDX, IDC_RATIOW, m_Ratio_W);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_SI_Tensor, CSasePage)
	//{{AFX_MSG_MAP(CDlg_SI_Tensor)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_SID, OnSelchangeSid)
	ON_CBN_SELCHANGE(IDC_NID, OnSelchangeNid)
	ON_BN_CLICKED(IDC_CLOSED, OnClosed)
	ON_BN_CLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_EN_KILLFOCUS(IDC_SEGANGLE, OnKillfocusSegAngle)
	ON_BN_DOUBLECLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_CLOSED, OnClosed)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Tensor message handlers
BOOL CDlg_SI_Tensor::OnInitDialog()
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
		FillListAllString_Solid();   //  with Patches
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

void CDlg_SI_Tensor::ResetDlg()
{
	/////////////////
	SetWindowText("Solid by Tensor Product");
	GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node");
	GetDlgItem(IDC_SID)->EnableWindow(TRUE);
	GetDlgItem(IDC_NID)->EnableWindow(TRUE);
	//////
	GetDlgItem(IDC_OTHER)->SetWindowText("Z");
	GetDlgItem(IDC_COORD)->EnableWindow(TRUE);
	//////
	((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);
	GetDlgItem(IDC_CLOSED)->EnableWindow(TRUE);
	//////
	GetDlgItem(IDC_ELEMS)->EnableWindow(TRUE);
	GetDlgItem(IDC_RATIO)->EnableWindow(TRUE);
//	GetDlgItem(IDC_ELEMSV)->EnableWindow(TRUE);
//	GetDlgItem(IDC_RATIOV)->EnableWindow(TRUE);
	//////
	((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(TRUE);
	GetDlgItem(IDC_AUTOSEG)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("Seg Angle");
	GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
	///////
}

void CDlg_SI_Tensor::OnSelchangeSid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_SI_Tensor::OnSelchangeNid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_SI_Tensor::OnUpdate()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_SOLIN,IDC_UPDATE);
	////////////////////////////////////////////////////
}

void CDlg_SI_Tensor::OnCancel()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_SOLIN,IDD_CANCEL);
	////////////////////////////////////////////////////
//	CPropertyPage::OnCancel();
}
    
void CDlg_SI_Tensor::FillListAllString_Solid()
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
    
void CDlg_SI_Tensor::FillListAllString_Node()
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

void CDlg_SI_Tensor::OnClosed()
{
	//////////////////////////////////////////////// Update	 
//   	m_bClosed 	= !m_bClosed;
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
	////////////////////////////////////////// Select
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
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_SI_Tensor::OnAutoSeg()
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

void CDlg_SI_Tensor::OnKillfocusSegAngle()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
}

void CDlg_SI_Tensor::OnAdvanced() 
{
	
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(!m_bAdvanced)
		return;
	////////////////////////////// Tangent End Data
	
}
////////////////////////////////// end of module //////////////////////
