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
#include "Dlg_PI_Revolv.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
/////////////////////////////////////////////////////////////////////////////
// CDlg_PI_Revolv dialog
IMPLEMENT_DYNCREATE(CDlg_PI_Revolv, CBasePage)

CDlg_PI_Revolv::CDlg_PI_Revolv(): CBasePage()
{
}

CDlg_PI_Revolv::CDlg_PI_Revolv(CWnd* pMainWnd,PATCHPROC PatProc)
				: CBasePage(pMainWnd,PatProc,CDlg_PI_Revolv::IDD)
{
	//{{AFX_DATA_INIT(CDlg_PI_Revolv)
	m_bClosed	= FALSE;
	m_dCoord	= 0.0;
	m_nTotElems = 1;
	m_nMesh		= 1;
	m_dAngSpec	= 90.0;
	//}}AFX_DATA_INIT
	m_SegAngle 	= 120;		// Default
	m_bAutoSeg 	= TRUE;
}

CDlg_PI_Revolv::~CDlg_PI_Revolv()
{
}

void CDlg_PI_Revolv::DoDataExchange(CDataExchange* pDX)
{
	CBasePage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PI_Revolv)
	DDX_CBString(pDX, IDC_PID, m_PID);
	DDX_CBString(pDX, IDC_CID, m_CID);
	DDX_CBString(pDX, IDC_NID, m_NID);
	DDX_Text(pDX, IDC_ELEMS, m_nMesh);
	DDV_MinMaxInt(pDX, m_nMesh, 1, 9999);
	DDX_Text(pDX, IDC_RATIO, m_Ratio);
	DDX_CBString(pDX, IDC_ORIENT, m_Orient);
	DDX_Check(pDX, IDC_CLOSED, m_bClosed);
	DDX_Text(pDX, IDC_COORD, m_dCoord);
	DDV_MinMaxDouble(pDX, m_dCoord, 0., 1.e+031);
	DDX_Check(pDX, IDC_GENBCURVE, m_bGenBCurve);
	DDX_Check(pDX, IDC_AXIS, m_bAxis);
	DDX_Check(pDX, IDC_NEGATIVE, m_bNegative);
	DDX_Text(pDX, IDC_TOTELEMS, m_nTotElems);
	DDX_Text(pDX, IDC_ANG_END, m_dAngSpec);
	//}}AFX_DATA_MAP
//	DDX_Text(pDX, IDC_ELEMS, m_nElemPerSeg);
}

BEGIN_MESSAGE_MAP(CDlg_PI_Revolv, CBasePage)
	//{{AFX_MSG_MAP(CDlg_PI_Revolv)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_PID, OnSelchangePid)
	ON_CBN_SELCHANGE(IDC_CID, OnSelchangeCid)
	ON_BN_CLICKED(IDC_CLOSED, OnClosed)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_EN_KILLFOCUS(IDC_COORD, OnKillfocusCoord)
	ON_BN_CLICKED(IDC_AXIS_Z, OnAxisZ)
	ON_BN_CLICKED(IDC_AXIS_X, OnAxisX)
	ON_BN_CLICKED(IDC_AXIS_Y, OnAxisY)
	ON_BN_CLICKED(IDC_AXIS, OnAxis)
	ON_BN_CLICKED(IDC_NEGATIVE, OnNegative)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_CLOSED, OnClosed)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_GENBCURVE, OnGenBCurve)
	ON_BN_DOUBLECLICKED(IDC_AXIS_Z, OnAxisZ)
	ON_BN_DOUBLECLICKED(IDC_AXIS_X, OnAxisX)
	ON_BN_DOUBLECLICKED(IDC_AXIS_Y, OnAxisY)
	ON_BN_DOUBLECLICKED(IDC_AXIS, OnAxis)
	ON_BN_DOUBLECLICKED(IDC_NEGATIVE, OnNegative)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMPat_DLL;
/////////////////////////////////////////////////////////////////////////////
// CDlg_PI_Revolv message handlers
BOOL CDlg_PI_Revolv::OnInitDialog()
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

void CDlg_PI_Revolv::ResetDlg()
{
	////////////////////////////////////////// Headings
	GetDlgItem(IDC_ORIENT)->EnableWindow(TRUE);
 	((CComboBox*)GetDlgItem(IDC_ORIENT))->SetCurSel(0);//Backward=1/Forward=0
	/////////////////
	SetWindowText("Patch by ROTATION");
	GetDlgItem(IDC_CIDHEAD)->SetWindowText("Rotnl. Curve");
	GetDlgItem(IDC_NIDHEAD)->SetWindowText("Axis Node From");
	GetDlgItem(IDC_PID)->EnableWindow(TRUE);
	GetDlgItem(IDC_CID)->EnableWindow(TRUE);
	GetDlgItem(IDC_NID)->EnableWindow(TRUE);
	//////
	GetDlgItem(IDC_TOTELEMHEAD)->SetWindowText("Bezier\nSegments");
	GetDlgItem(IDC_TOTELEMS)->EnableWindow(TRUE);
	//////
	GetDlgItem(IDC_HEAD_ANGORRAD)->SetWindowText("Rot.Angle");
	GetDlgItem(IDC_ANG_END)->EnableWindow(TRUE);
	//////
	GetDlgItem(IDC_OTHER)->SetWindowText("");
	GetDlgItem(IDC_COORD)->EnableWindow(FALSE);
	//////
	((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);
	GetDlgItem(IDC_CLOSED)->EnableWindow(TRUE);
	//////
	GetDlgItem(IDC_ELEMS)->EnableWindow(TRUE);
	GetDlgItem(IDC_RATIO)->EnableWindow(TRUE);
	//////
//	((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(TRUE);
//	GetDlgItem(IDC_AUTOSEG)->EnableWindow(TRUE);
//	GetDlgItem(IDC_SEGANGHEAD)->SetWindowText("Seg Angle");
//	GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
}


void CDlg_PI_Revolv::OnGenBCurve() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_PI_Revolv::OnSelchangePid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_PI_Revolv::OnSelchangeCid() 
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

void CDlg_PI_Revolv::OnCancel()
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_PATIN,IDD_CANCEL);
	////////////////////////////////////////////////////
//	CPropertyPage::OnCancel();
}
    
void CDlg_PI_Revolv::FillListAllString_Patch()
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
    
void CDlg_PI_Revolv::FillListAllString_Curve()
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

void CDlg_PI_Revolv::FillListAllString_Node()
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

void CDlg_PI_Revolv::OnClosed()
{
	//////////////////////////////////////////////// Update	 
//   	m_bClosed 	= !m_bClosed;
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
	////////////////////////////////////////// Select
	GetDlgItem(IDC_TOTELEMS)->EnableWindow(TRUE);
	if(m_bClosed)
	{
		GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);
		m_dAngSpec = 360.;
	}
	else
		GetDlgItem(IDC_ANG_END)->EnableWindow(TRUE);
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_PI_Revolv::OnUpdate() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_nTotElems<1)
	{
		AfxMessageBox(
			"INVALID DATA:\nFor Circle\nAtleast 1 Bezier Segment\nShould be Specified!");
		GetDlgItem(IDC_TOTELEMS)->EnableWindow(TRUE);
		GetDlgItem(IDC_TOTELEMS)->SetFocus();
		/////////////////
		UpdateData(FALSE);
		/////////////////
		return;
	}
	////////////////////////////////
	if(m_bClosed)
	{
		if(m_nTotElems<3)
		{
			AfxMessageBox(
				"INVALID DATA:\nFor Closed Circle\nAtleast 3 Bezier Segments\nShould be Specified!");
			GetDlgItem(IDC_TOTELEMS)->EnableWindow(TRUE);
			GetDlgItem(IDC_TOTELEMS)->SetFocus();
			/////////////////
			UpdateData(FALSE);
			/////////////////
			return;
		}
	}
	else
	if(m_nMesh<1)
	{
		AfxMessageBox("INVALID DATA:\nFor Open Circle\nAtleast 1 Element Should be Specified!");
		GetDlgItem(IDC_ELEMS)->EnableWindow(TRUE);
		GetDlgItem(IDC_ELEMS)->SetFocus();
		/////////////////
		UpdateData(FALSE);
		/////////////////
		return;
	}
	/////////////////
	UpdateData(FALSE);
	/////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_PATIN,IDC_UPDATE);
}

void CDlg_PI_Revolv::OnAxis() 
{
	UpdateData(TRUE);
	/////////////////
//	m_bAxis = !m_bAxis;
	///
	if(m_bAxis)
	{
		GetDlgItem(IDC_AXIS_X)->SetWindowText("X");
		GetDlgItem(IDC_AXIS_Y)->SetWindowText("Y");
		GetDlgItem(IDC_AXIS_Z)->SetWindowText("Z");
		GetDlgItem(IDC_NEGATIVE)->SetWindowText("Negative");
		GetDlgItem(IDC_AXIS_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_AXIS_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_AXIS_Z)->EnableWindow(TRUE);
		GetDlgItem(IDC_NEGATIVE)->EnableWindow(TRUE);
		///
	}
	else
	{
		GetDlgItem(IDC_AXIS_X)->SetWindowText("");
		GetDlgItem(IDC_AXIS_Y)->SetWindowText("");
		GetDlgItem(IDC_AXIS_Z)->SetWindowText("");
		GetDlgItem(IDC_NEGATIVE)->SetWindowText("");
		GetDlgItem(IDC_AXIS_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_AXIS_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_AXIS_Z)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEGATIVE)->EnableWindow(FALSE);
		///
	}
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_PI_Revolv::OnAxisX() 
{
	m_nAxis = 1;
}

void CDlg_PI_Revolv::OnAxisY() 
{
	m_nAxis = 2;
}

void CDlg_PI_Revolv::OnAxisZ() 
{
	m_nAxis = 3;
}

void CDlg_PI_Revolv::OnNegative() 
{
	UpdateData(TRUE);
	/////////////////
//	m_bNegative = !m_bNegative;
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_PI_Revolv::OnKillfocusCoord() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_PATIN,IDC_COORD);
}
/////////////////////////// end of module //////////////
