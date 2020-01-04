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
/////////////////////
#include "BasePage.h"
#include "dlg_PatI.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
/////////////////////////////////////////////////////////////////////////////
// CDlg_PatI dialog
IMPLEMENT_DYNCREATE(CDlg_PatI, CBasePage)

CDlg_PatI::CDlg_PatI(): CBasePage()
{
}

CDlg_PatI::CDlg_PatI(CWnd* pMainWnd,PATCHPROC PatProc)
				: CBasePage(pMainWnd,PatProc,CDlg_PatI::IDD)
{
	//{{AFX_DATA_INIT(CDlg_PI_Tensor)
	m_SegAngle 	= 120;		// Default
	m_bAutoSeg 	= TRUE;
	m_dLen		= 0.0;
	m_bIncrement= FALSE;
	m_bTwist	= TRUE;
	m_dCoord	= 0.0;
	m_bClosed	= FALSE;
	//}}AFX_DATA_INIT
}

CDlg_PatI::~CDlg_PatI()
{
}

void CDlg_PatI::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PatI)
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

BEGIN_MESSAGE_MAP(CDlg_PatI, CBasePage)
	//{{AFX_MSG_MAP(CDlg_PatI)
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
extern AFX_EXTENSION_MODULE NEAR extensionMPat_DLL;
/////////////////////////////////////////////////////////////////////////////
// CDlg_PatI message handlers
BOOL CDlg_PatI::OnInitDialog()
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

void CDlg_PatI::ResetDlg()
{
	////////////////////////////////////////// Headings
	GetDlgItem(IDC_ORIENT)->EnableWindow(TRUE);
 	((CComboBox*)GetDlgItem(IDC_ORIENT))->SetCurSel(0);//Backward=1/Forward=0
	/////////////////
	switch(m_PatProc)
	{
		case PP_EXTRUDE:
			SetWindowText("Patch by EXTRUSION");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Extrn. Curve");
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
			GetDlgItem(IDC_ELEMS)->EnableWindow(TRUE);
			GetDlgItem(IDC_RATIO)->EnableWindow(TRUE);
			//////
			((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(FALSE);
			GetDlgItem(IDC_AUTOSEG)->EnableWindow(FALSE);
			GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("");
			GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
			break;
		case PP_ROTATE:
			SetWindowText("Patch by ROTATION");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Rotnl. Curve");
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
			GetDlgItem(IDC_CLOSED)->EnableWindow(TRUE);
			//////
			GetDlgItem(IDC_ELEMS)->EnableWindow(TRUE);
			GetDlgItem(IDC_RATIO)->EnableWindow(TRUE);
			//////
			((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(TRUE);
			GetDlgItem(IDC_AUTOSEG)->EnableWindow(TRUE);
			GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("Seg Angle");
			GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
			break;
		case PP_LOFT2:
			SetWindowText("Patch by Lofting 2 Curves");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Begin Curve");
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
		case PP_COONS:
			SetWindowText("Coons Patch: Triangular or Quadrilateral");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Ist Curve");
			//////////////////////////////////////////// done automatically
			GetDlgItem(IDC_ORIENT)->EnableWindow(FALSE);
			//////////
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
		case PP_DUCT:
			SetWindowText("Patch by Ducting Cross-sectional Curve");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. Curve");
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
		case PP_SWEEP:
			SetWindowText("Patch by Sweeping Cross-sectional Curve");
			GetDlgItem(IDC_CIDHEAD)->SetWindowText("Xsec. Curve");
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

void CDlg_PatI::OnSelchangePid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_PatI::OnSelchangeCid() 
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

void CDlg_PatI::OnSelchangeNid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_PatI::OnUpdate()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_PATIN,IDC_UPDATE);
	////////////////////////////////////////////////////
}

void CDlg_PatI::OnCancel()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_PATIN,IDD_CANCEL);
	////////////////////////////////////////////////////
//	CPropertyPage::OnCancel();
}
    
void CDlg_PatI::FillListAllString_Patch()
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
    
void CDlg_PatI::FillListAllString_Curve()
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

void CDlg_PatI::FillListAllString_Node()
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

void CDlg_PatI::OnClosed()
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
		if(m_PatProc == PP_ROTATE)
		{	
			GetDlgItem(IDC_LEN)->EnableWindow(TRUE);
		}		
	}
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_PatI::OnAutoSeg()
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

void CDlg_PatI::OnKillfocusSegAngle()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
}

void CDlg_PatI::OnIncrement() 
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
