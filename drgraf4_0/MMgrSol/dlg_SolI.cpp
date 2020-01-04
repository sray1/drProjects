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

#include "dlg_SolI.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	5
/////////////////////////////////////////////////////////////////////////////
// CDlg_SolI dialog


CDlg_SolI::CDlg_SolI(CWnd* pWnd,SOLIDPROC SolProc)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_SolI)
	m_SegAngle 	= 120;		// Default
	m_bAutoSeg 	= TRUE;
	m_dLen		= 0.0;
	m_bIncrement= FALSE;
	m_bTwist	= TRUE;
	m_dCoord	= 0.0;
	//}}AFX_DATA_INIT
	///////////////////////
	m_pWnd 		= pWnd;
	m_SolProc	= SolProc;
}

void CDlg_SolI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SolI)
	DDX_CBString(pDX, IDC_PID, m_PID);
	DDX_CBString(pDX, IDC_CID, m_CID);
	DDX_CBString(pDX, IDC_NID, m_NID);
	DDX_Text(pDX, IDC_ELEMS, m_nMesh);
	DDV_MinMaxInt(pDX, m_nMesh, 1, 9999);
	DDX_Text(pDX, IDC_RATIO, m_Ratio);
	DDX_CBString(pDX, IDC_ORIENT, m_Orient);
	DDX_Check(pDX, IDC_CLOSED, m_bClosed);
	DDX_Check(pDX, IDC_INCREMENT, m_bIncrement);
	DDX_Text(pDX, IDC_TWISTSTART, m_TwistStart);
	DDX_Text(pDX, IDC_TWISTMULT, m_TwistMult);
	DDV_MinMaxDouble(pDX, m_TwistMult, 0., 360.);
	DDX_Text(pDX, IDC_SEGANGLE, m_SegAngle);
	DDV_MinMaxDouble(pDX, m_SegAngle, 45., 120.);
	DDX_Check(pDX, IDC_AUTOSEG, m_bAutoSeg);
	DDX_Text(pDX, IDC_LEN, m_dLen);
	DDX_Text(pDX, IDC_COORD, m_dCoord);
	DDV_MinMaxDouble(pDX, m_dCoord, 0., 1.e+031);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_SolI, CDialog)
	//{{AFX_MSG_MAP(CDlg_SolI)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_PID, OnSelchangePid)
	ON_CBN_SELCHANGE(IDC_CID, OnSelchangeCid)
	ON_CBN_SELCHANGE(IDC_NID, OnSelchangeNid)
	ON_BN_CLICKED(IDC_CLOSED, OnClosed)
	ON_BN_CLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_EN_KILLFOCUS(IDC_SEGANGLE, OnKillfocusSegAngle)
	ON_BN_CLICKED(IDC_INCREMENT, OnIncrement)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_CLOSED, OnClosed)
	ON_BN_DOUBLECLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_BN_DOUBLECLICKED(IDC_INCREMENT, OnIncrement)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMSol_DLL;

BOOL CDlg_SolI::Create ()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMSol_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	/////////////////////////////////////////////////////////////
	bOk = CDialog::Create(CDlg_SolI::IDD);
	///////////////////////////////////////
#ifdef _AFXDLL
//	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
#endif
	//////////////////
	return bOk;
}

/////////////////////////////////////////////////////////////////////////////
// CDlg_SolI message handlers
BOOL CDlg_SolI::OnInitDialog()
{
	CDialog::OnInitDialog();
	
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
	/////////////////////////////////////////////// Do it When Needed
/*
	pDListMgr 		= pObjectMgr->GetObjectList(CURVE);
	nMax			= pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMax)
		FillListAllString_Curve();   //  with Curves
*/
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(NODE);
	nMax			= pDListMgr->GetSpecificObjectCount(CURVE);
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

void CDlg_SolI::ResetDlg()
{
	m_bCurve = FALSE;
	////////////////////////////////////////// Headings
	GetDlgItem(IDC_ORIENT)->EnableWindow(TRUE);
 	((CComboBox*)GetDlgItem(IDC_ORIENT))->SetCurSel(0);//Backward=1/Forward=0
	/////////////////
	switch(m_SolProc)
	{
		case SP_EXTRUDE:
			SetWindowText("Solid by EXTRUSION");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Extrn. Patch");
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("Dirn. Node From");
			GetDlgItem(IDC_LENHEAD)->SetWindowText("Length");
			GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			//////
			GetDlgItem(IDC_LENHEAD)->SetWindowText("Length");
			GetDlgItem(IDC_LEN)->EnableWindow(TRUE);
			//////
			GetDlgItem(IDC_OTHER)->SetWindowText("");
			GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_INCREMENT))->SetCheck(FALSE);
			GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTHEAD)->SetWindowText("");
			GetDlgItem(IDC_TWISTSTART)->EnableWindow(FALSE);
			GetDlgItem(IDC_STEPHEAD)->SetWindowText("");
			GetDlgItem(IDC_TWISTMULT)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);
			GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(FALSE);
			GetDlgItem(IDC_AUTOSEG)->EnableWindow(FALSE);
			GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("");
			GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
			break;
		case SP_ROTATE:
			SetWindowText("Solid by ROTATION");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Rotnl. Patch");
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("Axis Node From");
			GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			//////
			GetDlgItem(IDC_LENHEAD)->SetWindowText("Angle");
			GetDlgItem(IDC_LEN)->EnableWindow(TRUE);
			//////
			GetDlgItem(IDC_OTHER)->SetWindowText("");
			GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_INCREMENT))->SetCheck(FALSE);
			GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTHEAD)->SetWindowText("");
			GetDlgItem(IDC_TWISTSTART)->EnableWindow(FALSE);
			GetDlgItem(IDC_STEPHEAD)->SetWindowText("");
			GetDlgItem(IDC_TWISTMULT)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);
//			GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(TRUE);
			GetDlgItem(IDC_AUTOSEG)->EnableWindow(TRUE);
			GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("Seg Angle");
			GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
			break;
		case SP_LOFT2:
			SetWindowText("Solid by Lofting 2 Patchs");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Begin Patch");
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			//////
			GetDlgItem(IDC_LENHEAD)->SetWindowText("");
			GetDlgItem(IDC_LEN)->EnableWindow(FALSE);
			//////
			GetDlgItem(IDC_OTHER)->SetWindowText("");
			GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
			//////
			GetDlgItem(IDC_ELEMS)->EnableWindow(TRUE);
			GetDlgItem(IDC_RATIO)->EnableWindow(TRUE);
			//////
			((CButton*)GetDlgItem(IDC_INCREMENT))->SetCheck(FALSE);
			GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTHEAD)->SetWindowText("");
			GetDlgItem(IDC_TWISTSTART)->EnableWindow(FALSE);
			GetDlgItem(IDC_STEPHEAD)->SetWindowText("");
			GetDlgItem(IDC_TWISTMULT)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);
			GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(FALSE);
			GetDlgItem(IDC_AUTOSEG)->EnableWindow(FALSE);
			GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("");
			GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
			break;
		case SP_COONS:
			SetWindowText("Coons Solid: TetraHedral or HexaHedral");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Ist Patch");
			GetDlgItem(IDC_ORIENT)->EnableWindow(FALSE);
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("");
			GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			//////
			GetDlgItem(IDC_LENHEAD)->SetWindowText("");
			GetDlgItem(IDC_LEN)->EnableWindow(FALSE);
			//////
			GetDlgItem(IDC_OTHER)->SetWindowText("");
			GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
			//////
			GetDlgItem(IDC_ELEMS)->EnableWindow(FALSE);
			GetDlgItem(IDC_RATIO)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_INCREMENT))->SetCheck(FALSE);
			GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTHEAD)->SetWindowText("");
			GetDlgItem(IDC_TWISTSTART)->EnableWindow(FALSE);
			GetDlgItem(IDC_STEPHEAD)->SetWindowText("");
			GetDlgItem(IDC_TWISTMULT)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);
			GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(FALSE);
			GetDlgItem(IDC_AUTOSEG)->EnableWindow(FALSE);
			GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("");
			GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
			break;
		case SP_DUCT:
			SetWindowText("Solid by Ducting Cross-sectional Patch");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. Patch");
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
			GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			//////
			GetDlgItem(IDC_LENHEAD)->SetWindowText("");
			GetDlgItem(IDC_LEN)->EnableWindow(FALSE);
			//////
			GetDlgItem(IDC_OTHER)->SetWindowText("");
			GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
			//////
			GetDlgItem(IDC_ELEMS)->EnableWindow(FALSE);
			GetDlgItem(IDC_RATIO)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_INCREMENT))->SetCheck(FALSE);
//			GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
			if(m_bIncrement)
			{
				GetDlgItem(IDC_STARTHEAD)->SetWindowText("Twist Start");
				GetDlgItem(IDC_TWISTSTART)->EnableWindow(TRUE);
				GetDlgItem(IDC_STEPHEAD)->SetWindowText("Twist Step");
				GetDlgItem(IDC_TWISTMULT)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_STARTHEAD)->SetWindowText("");
				GetDlgItem(IDC_TWISTSTART)->EnableWindow(FALSE);
				GetDlgItem(IDC_STEPHEAD)->SetWindowText("Twist Max");
				GetDlgItem(IDC_TWISTMULT)->EnableWindow(TRUE);
			}
			//////
			((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);
			GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(FALSE);
			GetDlgItem(IDC_AUTOSEG)->EnableWindow(FALSE);
			GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("");
			GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
			break;
		case SP_SWEEP:
			SetWindowText("Solid by Sweeping Cross-sectional Patch");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. Patch");
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("Anchor Node");
			GetDlgItem(IDC_PID)->EnableWindow(TRUE);
			GetDlgItem(IDC_CID)->EnableWindow(TRUE);
			GetDlgItem(IDC_NID)->EnableWindow(TRUE);
			//////
			GetDlgItem(IDC_LENHEAD)->SetWindowText("");
			GetDlgItem(IDC_LEN)->EnableWindow(FALSE);
			//////
			GetDlgItem(IDC_OTHER)->SetWindowText("");
			GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
			//////
			GetDlgItem(IDC_ELEMS)->EnableWindow(FALSE);
			GetDlgItem(IDC_RATIO)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_INCREMENT))->SetCheck(FALSE);
//			GetDlgItem(IDC_INCREMENT)->EnableWindow(FALSE);
			if(m_bIncrement)
			{
				if(m_bTwist)
				{
					GetDlgItem(IDC_STARTHEAD)->SetWindowText("Twist Start");
					GetDlgItem(IDC_TWISTSTART)->EnableWindow(TRUE);
					GetDlgItem(IDC_STEPHEAD)->SetWindowText("Twist Step");
					GetDlgItem(IDC_TWISTMULT)->EnableWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_STARTHEAD)->SetWindowText("Radial Start");
					GetDlgItem(IDC_TWISTSTART)->EnableWindow(TRUE);
					GetDlgItem(IDC_STEPHEAD)->SetWindowText("Radial Step");
					GetDlgItem(IDC_TWISTMULT)->EnableWindow(FALSE);
				}
			}
			else
			{
				GetDlgItem(IDC_STARTHEAD)->SetWindowText("");
				GetDlgItem(IDC_TWISTSTART)->EnableWindow(FALSE);
				if(m_bTwist)
					GetDlgItem(IDC_STEPHEAD)->SetWindowText("Twist Max");
				else
					GetDlgItem(IDC_STEPHEAD)->SetWindowText("Radial Max");
				GetDlgItem(IDC_TWISTMULT)->EnableWindow(TRUE);
			}
			//////
			((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);
			GetDlgItem(IDC_CLOSED)->EnableWindow(FALSE);
			//////
			((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(FALSE);
			GetDlgItem(IDC_AUTOSEG)->EnableWindow(FALSE);
			GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("");
			GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
			break;
		default:
			break;
	}
}

void CDlg_SolI::OnSelchangePid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_SolI::OnSelchangeCid() 
{
	if(!m_bCurve)
		return;
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

void CDlg_SolI::OnSelchangeNid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_SolI::OnUpdate()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_SOLIN,IDC_UPDATE);
	////////////////////////////////////////////////////
}

void CDlg_SolI::OnCancel()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_SOLIN,IDD_CANCEL);
	////////////////////////////////////////////////////
//	CDialog::OnCancel();
}
    
void CDlg_SolI::FillListAllString_Solid()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_PID);
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
			CDrSolid* pCurve = (CDrSolid*)pObject;
			Cid   = pCurve->GetObjectID();
	    	((CComboBox*)(pWndCtrl))->AddString(Cid);
		}			    
   	}
   	///////////////////////////////////
   	pWndCtrl->EnableWindow(FALSE);		// Always Disabled
   	////////
    
}
    
void CDlg_SolI::FillListAllString_Patch()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_CID);
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
    
void CDlg_SolI::FillListAllString_Curve()
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

void CDlg_SolI::FillListAllString_Node()
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

void CDlg_SolI::OnClosed()
{
    ////////////////////
//	UpdateData(TRUE);		    //FROM Screen(TRUE)    
	//////////////////////////////////////////////// Update	 
   	m_bClosed 	= !m_bClosed;
	////////////////////////////////////////// Select
	if(m_bClosed)
	{
		m_dLen = 360.;
		GetDlgItem(IDC_LEN)->EnableWindow(FALSE);
	}
	else
	{
		if(m_SolProc == SP_ROTATE)
		{	
			GetDlgItem(IDC_LEN)->EnableWindow(TRUE);
		}		
	}
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_SolI::OnAutoSeg()
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

void CDlg_SolI::OnKillfocusSegAngle()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
}

void CDlg_SolI::OnIncrement() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    /////////////////////////////////////////////// 
	if(m_bIncrement)
	{
//		GetDlgItem(IDC_CID_TWIST)->EnableWindow(FALSE);
		if(m_bTwist)
		{
			GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTHEAD)->SetWindowText("Twist Start");
			GetDlgItem(IDC_TWISTSTART)->EnableWindow(TRUE);
			GetDlgItem(IDC_STEPHEAD)->SetWindowText("Twist Step");
			GetDlgItem(IDC_TWISTMULT)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_CID)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTHEAD)->SetWindowText("Radial Start");
			GetDlgItem(IDC_TWISTSTART)->EnableWindow(TRUE);
			GetDlgItem(IDC_STEPHEAD)->SetWindowText("Radial Step");
			GetDlgItem(IDC_TWISTMULT)->EnableWindow(TRUE);
		}
	}
	else
	{
//		GetDlgItem(IDC_CID_TWIST)->EnableWindow(TRUE);
		GetDlgItem(IDC_CID)->EnableWindow(TRUE);
		GetDlgItem(IDC_STARTHEAD)->SetWindowText("");
		GetDlgItem(IDC_TWISTSTART)->EnableWindow(FALSE);
		if(m_bTwist)
			GetDlgItem(IDC_STEPHEAD)->SetWindowText("Twist Max");
		else
			GetDlgItem(IDC_STEPHEAD)->SetWindowText("Radial Max");
		GetDlgItem(IDC_TWISTMULT)->EnableWindow(TRUE);
	}
    ////////////////////
	UpdateData(FALSE);			//To Screen(FALSE)    
    /////////////////////////////////////////////// 
}
////////////////////////////////// end of module //////////////////////
