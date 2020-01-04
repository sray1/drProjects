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
#include "MPatMgr.h"
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"
/////////////////////
#include "BasePage.h"
#include "Dlg_Torq.h"
#include "Dlg_Radius.h"

#include "Dlg_PI_Sweep.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
/////////////////////////////////////////////////////////////////////////////
// CDlg_PI_Sweep dialog
IMPLEMENT_DYNCREATE(CDlg_PI_Sweep, CBasePage)

CDlg_PI_Sweep::CDlg_PI_Sweep(): CBasePage()
{
}

CDlg_PI_Sweep::CDlg_PI_Sweep(CWnd* pMainWnd,PATCHPROC PatProc)
				: CBasePage(pMainWnd,PatProc,CDlg_PI_Sweep::IDD)
{
	//{{AFX_DATA_INIT(CDlg_PI_Sweep)
	m_dCoord	= 0.0;
	m_bTwist	= TRUE;
	m_TwistMult	= 1.0;
	//}}AFX_DATA_INIT
}

CDlg_PI_Sweep::~CDlg_PI_Sweep()
{
}

void CDlg_PI_Sweep::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PI_Sweep)
	DDX_CBString(pDX, IDC_PID, m_PID);
	DDX_CBString(pDX, IDC_CID, m_CID);
	DDX_CBString(pDX, IDC_NID, m_NID);
	DDX_CBString(pDX, IDC_ORIENT, m_Orient);
	DDX_Text(pDX, IDC_TWISTSTART, m_TwistStart);
	DDX_Text(pDX, IDC_TWISTMULT, m_TwistMult);
	DDV_MinMaxDouble(pDX, m_TwistMult, 0., 360.);
	DDX_Text(pDX, IDC_COORD, m_dCoord);
	DDV_MinMaxDouble(pDX, m_dCoord, 0., 1.e+031);
	DDX_Check(pDX, IDC_GENBCURVE, m_bGenBCurve);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_PI_Sweep, CBasePage)
	//{{AFX_MSG_MAP(CDlg_PI_Sweep)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_PID, OnSelchangePid)
	ON_CBN_SELCHANGE(IDC_CID, OnSelchangeCid)
	ON_CBN_SELCHANGE(IDC_NID, OnSelchangeNid)
	ON_BN_CLICKED(IDC_INCREMENT, OnIncrement)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_INCREMENT, OnIncrement)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_DISTRIB, OnDistrib)
	ON_BN_DOUBLECLICKED(IDC_DISTRIB, OnDistrib)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMPat_DLL;
/////////////////////////////////////////////////////////////////////////////
// CDlg_PI_Sweep message handlers
BOOL CDlg_PI_Sweep::OnInitDialog()
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
	pDListMgr 		= pObjectMgr->GetObjectList(CURVE);
	nMax			= pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMax)
		FillListAllString_Curve();   //  with Curves
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(NODE);
	nMax			= pDListMgr->GetSpecificObjectCount(NODE);
	if(nMax)
		FillListAllString_Node();   //  with Curves
	////////////////////////////////////////// Headings
	ResetDlg();
	////////////////////////////////////////// Focus
	CWnd* pWndCtrl = GetDlgItem(IDC_PID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_PI_Sweep::ResetDlg()
{
	////////////////////////////////////////// Headings
	GetDlgItem(IDC_ORIENT)->EnableWindow(TRUE);
 	((CComboBox*)GetDlgItem(IDC_ORIENT))->SetCurSel(0);//Backward=1/Forward=0
	/////////////////
	SetWindowText("Patch by Sweeping Cross-sectional Curve");
	GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. Curve");
	GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
	GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	GetDlgItem(IDC_CID)->EnableWindow(TRUE);
	GetDlgItem(IDC_NID)->EnableWindow(TRUE);
	//////
	GetDlgItem(IDC_OTHER)->SetWindowText("");
	GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
	//////
	((CButton*)GetDlgItem(IDC_INCREMENT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_DISTRIB))->SetCheck(FALSE);
	//////
//	CWnd* pCtl = GetDlgItem(IDC_TWISTGROUP); 
//	if(m_bTwist)
//	else
//		GetDlgItem(IDC_TWISTGROUP)->SetWindowText("Radial Scale");
	/////
	GetDlgItem(IDC_STARTHEAD)->SetWindowText("");
	GetDlgItem(IDC_TWISTSTART)->EnableWindow(FALSE);
	GetDlgItem(IDC_STEPHEAD)->SetWindowText("");
	GetDlgItem(IDC_TWISTMULT)->EnableWindow(FALSE);
	//////
}

void CDlg_PI_Sweep::OnSelchangePid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_PI_Sweep::OnSelchangeCid() 
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
	CDrCurve*	pDrCurve;
	/////////////////////////////////
	pWndCtrl = GetDlgItem(IDC_CID);
    int index = ((CComboBox*)(pWndCtrl))->GetCurSel();
	if(index>=0)
		((CComboBox*)(pWndCtrl))->GetLBText(index,Cid);
	else
		return;
	////////////
	index	= pObjectMgr->GetObjectIndexfromKey(CURVE,Cid,1);
	if(index>=0)
	{
		pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
		m_nMesh		= pDrCurve->GetMaxOutPts_S() - 1;
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_PI_Sweep::OnSelchangeNid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_PI_Sweep::OnUpdate()
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////////////////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_PATIN,IDC_UPDATE);
	////////////////////////////////////////////////////
}

void CDlg_PI_Sweep::OnCancel()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_PATIN,IDD_CANCEL);
	////////////////////////////////////////////////////
//	CPropertyPage::OnCancel();
}
    
void CDlg_PI_Sweep::FillListAllString_Patch()
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
    
void CDlg_PI_Sweep::FillListAllString_Curve()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_CID);
	//////////////////////////
	CString Cid;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(CURVE);
    if(nMaxCurves<=0)
    	return;
    //////////////////////////////////////////////////////////	
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == CURVE)
		{ 
			CDrCurve* pCurve = (CDrCurve*)pObject;
			Cid   = pCurve->GetObjectID();
	    	((CComboBox*)(pWndCtrl))->AddString(Cid);
		}			    
   	}
   	///////////////////////////////////
   	pWndCtrl->EnableWindow(FALSE);		// Always Disabled
   	////////
    
}

void CDlg_PI_Sweep::FillListAllString_Node()
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

void CDlg_PI_Sweep::OnIncrement() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////////////////////////////////
	m_bIncrement = TRUE;
	////////////////////
	if(m_bTwist)	// Twist
	{
//		GetDlgItem(IDC_TWISTGROUP)->SetWindowText("Twist");
		GetDlgItem(IDC_CID)->EnableWindow(FALSE);
		GetDlgItem(IDC_STARTHEAD)->SetWindowText("Twist Start");
		GetDlgItem(IDC_TWISTSTART)->EnableWindow(TRUE);
		GetDlgItem(IDC_STEPHEAD)->SetWindowText("Twist Step");
		GetDlgItem(IDC_TWISTMULT)->EnableWindow(TRUE);
	}
	else	// Radius
	{
//		GetDlgItem(IDC_TWISTGROUP)->SetWindowText("Radial Scale");
		GetDlgItem(IDC_CID)->EnableWindow(FALSE);
		GetDlgItem(IDC_STARTHEAD)->SetWindowText("Radial Start");
		GetDlgItem(IDC_TWISTSTART)->EnableWindow(TRUE);
		GetDlgItem(IDC_STEPHEAD)->SetWindowText("Radial Step");
		GetDlgItem(IDC_TWISTMULT)->EnableWindow(TRUE);
	}
    ////////////////////
	UpdateData(FALSE);			//To Screen(FALSE)    
    /////////////////////////////////////////////// 
}

void CDlg_PI_Sweep::OnDistrib() 
{
	int nResult;
	CMPatMgr MPatMgr;	// This will make current ResourceInstance active for the Dlgs
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////////////////////////////////
	m_bIncrement = FALSE;
	////////////////////
	GetDlgItem(IDC_STARTHEAD)->SetWindowText("");
	GetDlgItem(IDC_TWISTSTART)->EnableWindow(FALSE);
	GetDlgItem(IDC_STEPHEAD)->SetWindowText("");
	GetDlgItem(IDC_TWISTMULT)->EnableWindow(FALSE);
	//////////////////////////////////////////////////////////////
	if(m_bTwist)
	{
		///////////////////////////////////////		
		UINT nStatus = MPatMgr.DoModal_Patch_TwistFactors(m_pTwist,m_nMaxTwist,m_TwistMult);
		if(nStatus == IDOK)
		{
			///////////////////////////////////////////////m_TwistMult will be updated for DDX
			UpdateData(FALSE);			//To Screen(FALSE)    
			/////////////////////////////////////////////// 
			OnUpdate();
			///
		}
		else
		{
			nResult = AfxMessageBox(
				"Sweep Twist Info\nDo You want to CANCEL\nthe Current Procees?",MB_YESNO);
			///
			if(nResult == IDYES)
				OnCancel();
			///
		}
	}
	else	// Radius			
	{
		///////////////////////////////////////		
		UINT nStatus = MPatMgr.DoModal_Patch_RadiusFactors(m_pTwist,m_nMaxTwist,m_TwistMult);
		if(nStatus == IDOK)
		{
			///////////////////////////////////////////////m_TwistMult will be updated for DDX
			UpdateData(FALSE);			//To Screen(FALSE)    
			/////////////////////////////////////////////// 
			OnUpdate();
			///
		}
		else
		{
			nResult = AfxMessageBox(
				"Sweep Scale Info\nDo You want to CANCEL\nthe Current Procees?",MB_YESNO);
			///
			if(nResult == IDYES)
				OnCancel();
			///
		}
	}				
    ////////////////////
	UpdateData(FALSE);			//To Screen(FALSE)    
    /////////////////////////////////////////////// 
}
////////////////////////////////// end of module //////////////////////
