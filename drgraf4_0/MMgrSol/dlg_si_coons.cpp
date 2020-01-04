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
#include "Dlg_SI_Coons.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Coons dialog
IMPLEMENT_DYNCREATE(CDlg_SI_Coons, CSasePage)

CDlg_SI_Coons::CDlg_SI_Coons(): CSasePage()
{
}

CDlg_SI_Coons::CDlg_SI_Coons(CWnd* pMainWnd,SOLIDPROC SolProc)
				: CSasePage(pMainWnd,SolProc,CDlg_SI_Coons::IDD)
{
	//{{AFX_DATA_INIT(CDlg_SI_Coons)
	m_bGenBCurve = FALSE;
	m_bGenBPatch = FALSE;
	m_Orient_P = _T("");
	//}}AFX_DATA_INIT
}

CDlg_SI_Coons::~CDlg_SI_Coons()
{
}

void CDlg_SI_Coons::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SI_Coons)
	DDX_CBString(pDX, IDC_CID, m_SID);
	DDX_CBString(pDX, IDC_PID, m_PID);
	DDX_Check(pDX, IDC_GENBCURVE, m_bGenBCurve);
	DDX_Check(pDX, IDC_GENBPATCH, m_bGenBPatch);
	DDX_CBString(pDX, IDC_ORIENT_P, m_Orient_P);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_SI_Coons, CSasePage)
	//{{AFX_MSG_MAP(CDlg_SI_Coons)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_PID, OnSelchangePid)
	ON_CBN_SELCHANGE(IDC_SID, OnSelchangeSid)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMSol_DLL;
/////////////////////////////////////////////////////////////////////////////
// CDlg_SI_Coons message handlers
BOOL CDlg_SI_Coons::OnInitDialog()
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
		FillListAllString_Solid();   //  with Curves
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

void CDlg_SI_Coons::ResetDlg()
{
	////////////////////////////////////////// Headings
	GetDlgItem(IDC_ORIENT)->EnableWindow(TRUE);
 	((CComboBox*)GetDlgItem(IDC_ORIENT))->SetCurSel(0);//Backward=1/Forward=0
	/////////////////
	SetWindowText("Coons Solid: HexaHedral,PentaHedral or TetraHedral");
	GetDlgItem(IDC_CIDHEAD)->SetWindowText("Ist Patch");
	//////////////////////////////////////////// done automatically
	GetDlgItem(IDC_ORIENT)->EnableWindow(FALSE);
	//////////
	GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	GetDlgItem(IDC_SID)->EnableWindow(TRUE);
}

void CDlg_SI_Coons::OnSelchangeSid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_SI_Coons::OnSelchangePid() 
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

void CDlg_SI_Coons::OnUpdate()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_SOLIN,IDC_UPDATE);
	////////////////////////////////////////////////////
}

void CDlg_SI_Coons::OnCancel()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_SOLIN,IDD_CANCEL);
	////////////////////////////////////////////////////
//	CPropertyPage::OnCancel();
}
    
void CDlg_SI_Coons::FillListAllString_Patch()
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
    
void CDlg_SI_Coons::FillListAllString_Solid()
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

////////////////////////////////// end of module //////////////////////
