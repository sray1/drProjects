// Dlg_CurI.cpp : implementation file similar to Old:Dlg_Crc2.cpp
//	Circle by 3 Nodes
//

#include "stdafx.h"

//#include "Def_Lims.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"

#include "MCurDll.h"
#include "UserMsg.h"

#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "Dlg_CrcI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	2
#define DEFAULT_CLOSED	3
/////////////////////////////////////////////////////////////////////////////
// CDlg_CrcI dialog


CDlg_CrcI::CDlg_CrcI(CWnd* pWnd,CIRCLETYPE	CircType)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_CrcI)
	m_Ratio 	= 1;
	m_dCoord	= 0.0;
	m_bAxis		= FALSE;
	m_bNegative = FALSE;
	m_bUniform	= TRUE;
	m_nTotElems = 0;
	m_nElemPerSeg = 0;
	m_dRadius	= 0.0;
	m_dAngSpec	= 0.0;
	m_SegAngle 	= 120;		// Default
	m_bAutoSeg 	= TRUE;
	//}}AFX_DATA_INIT
	m_pWnd 		= pWnd;
	m_bArc		= TRUE;
	m_bClosed	= FALSE;
	m_CircType	= CircType;
//	m_nAxis		= 0; // default no Axis Chosen

}


void CDlg_CrcI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CrcI)
	DDX_Text(pDX, IDC_SEGANGLE, m_SegAngle);
	DDV_MinMaxDouble(pDX, m_SegAngle, 45., 120.);
	DDX_Check(pDX, IDC_AUTOSEG, m_bAutoSeg);
	DDX_CBString(pDX, IDC_CID, m_CurveID);
	DDX_CBString(pDX, IDC_NID, m_NID);
	DDX_Text(pDX, IDC_RATIO, m_Ratio);
	DDV_MinMaxDouble(pDX, m_Ratio, 0.1, 9999.);
	DDX_Text(pDX, IDC_COORD, m_dCoord);
	DDX_Check(pDX, IDC_AXIS, m_bAxis);
	DDX_Check(pDX, IDC_NEGATIVE, m_bNegative);
	DDX_Check(pDX, IDC_UNIFORM, m_bUniform);
	DDX_Text(pDX, IDC_TOTELEMS, m_nTotElems);
	DDX_Text(pDX, IDC_ELEMS, m_nElemPerSeg);
	DDX_Text(pDX, IDC_RADIUS, m_dRadius);
	DDX_Text(pDX, IDC_ANG_END, m_dAngSpec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_CrcI, CDialog)
	//{{AFX_MSG_MAP(CDlg_CrcI)
	ON_CBN_SELCHANGE(IDC_CID, OnSelchangeCid)
	ON_CBN_SELCHANGE(IDC_NID, OnSelchangeNid)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_CLOSED, OnClosed)
	ON_BN_CLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_EN_KILLFOCUS(IDC_SEGANGLE, OnKillfocusSegAngle)
	ON_BN_CLICKED(IDC_ANGSPEC, OnAngspec)
	ON_BN_CLICKED(IDC_ARC, OnArc)
	ON_EN_KILLFOCUS(IDC_COORD, OnKillfocusCoord)
	ON_BN_CLICKED(IDC_AXIS_Z, OnAxisZ)
	ON_BN_CLICKED(IDC_AXIS_X, OnAxisX)
	ON_BN_CLICKED(IDC_AXIS_Y, OnAxisY)
	ON_BN_CLICKED(IDC_AXIS, OnAxis)
	ON_BN_CLICKED(IDC_NEGATIVE, OnNegative)
	ON_BN_DOUBLECLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_CLOSED, OnClosed)
	ON_BN_DOUBLECLICKED(IDC_ANGSPEC, OnAngspec)
	ON_BN_DOUBLECLICKED(IDC_ARC, OnArc)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_AXIS_Z, OnAxisZ)
	ON_BN_DOUBLECLICKED(IDC_AXIS_X, OnAxisX)
	ON_BN_DOUBLECLICKED(IDC_AXIS_Y, OnAxisY)
	ON_BN_DOUBLECLICKED(IDC_AXIS, OnAxis)
	ON_BN_DOUBLECLICKED(IDC_NEGATIVE, OnNegative)
	ON_BN_CLICKED(IDC_UNIFORM, OnUniform)
	ON_BN_DOUBLECLICKED(IDC_UNIFORM, OnUniform)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMCur_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_CrcI message handlers

BOOL CDlg_CrcI::OnInitDialog()
{
	CDialog::OnInitDialog();
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr 		= pObjectMgr->GetObjectList(NODE);
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMaxNodes)
		FillListAllString_Node();   // only with Nodes
	pDListMgr 		= pObjectMgr->GetObjectList(CURVE);
	int nMaxCurves 	 = pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMaxCurves)
		FillListAllString_Curve();   // only with Curves
	//////////////////////////////////////////////////// Set Uniform Option
	m_bUniform	= TRUE;
	((CButton*)GetDlgItem(IDC_UNIFORM))->SetCheck(TRUE);
	GetDlgItem(IDC_RATIO)->EnableWindow(FALSE);	
	//////////////////////////////////////////////////// Disable SegAngle
	GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);	
	//////////////////////////////////////////////////// Set ARC Option
	m_bArc = TRUE;
	////////////////////////////////////////// Select
	((CButton*)GetDlgItem(IDC_ARC))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_ANGSPEC))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_CLOSED))->SetCheck(FALSE);
	/////////
	GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);
	GetDlgItem(IDC_TOTELEMS)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEAD_ANGORRAD)->SetWindowText("");
	GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);
	////////////////////////////////////////// Headings
	GetDlgItem(IDC_AXIS)->EnableWindow(FALSE);
	GetDlgItem(IDC_AXIS_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_AXIS_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_AXIS_Z)->EnableWindow(FALSE);
	GetDlgItem(IDC_NEGATIVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TOTELEMHEAD)->SetWindowText("LastSegment\nElems");
	//////////////////
	switch(m_CircType)
	{
		case CIRCLE_BY_ROT:
			SetWindowText("CIRCLE by Rotation of a Node ( Angles in Degrees)");
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node_Rot");
			GetDlgItem(IDC_ANG_END)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEAD_ANGORRAD)->SetWindowText("Rot.Angle");
			GetDlgItem(IDC_ANGSPEC)->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_ANGSPEC))->SetCheck(TRUE);
			///
			m_bArc = FALSE;
			GetDlgItem(IDC_ARC)->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_ARC))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_AUTOSEG))->SetCheck(FALSE);
			GetDlgItem(IDC_AUTOSEG)->EnableWindow(FALSE);
//			GetDlgItem(IDC_ELEMS)->EnableWindow(FALSE);
			/////////////////////////////////////////////
			GetDlgItem(IDC_TOTELEMHEAD)->SetWindowText("Bezier\nSegments");
			GetDlgItem(IDC_TOTELEMS)->EnableWindow(TRUE);
			GetDlgItem(IDC_AXIS)->EnableWindow(TRUE);
			/////
			break;
		case CIRCLE_BY_NO3:
			SetWindowText("CIRCLE from 3 Nodes on Circumference (Angles in Degrees)");
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("Ist Node");
			break;
		case CIRCLE_BY_2N_TI:
			SetWindowText("CIRCLE by 2 End Nodes & TI");
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node_I");
			break;
		case CIRCLE_BY_2N_CC:
			SetWindowText("CIRCLE by 2 End Nodes & Center(CC)");
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("Node_I");
			break;
		case CIRCLE_BY_2CN_TI_R:
			SetWindowText("CIRCLE by 2 CNodes on Tangents & TI and Radius");
			GetDlgItem(IDC_NIDHEAD)->SetWindowText("CNode_A");
			GetDlgItem(IDC_RADIUS)->EnableWindow(TRUE);
			break;
		default:
			break;
	}
	////////////////////////////////////////// Focus
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_CrcI::Create ()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMCur_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	/////////////////////////////////////////////////////////////
	bOk = CDialog::Create(CDlg_CrcI::IDD);
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

void CDlg_CrcI::OnSelchangeCid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_CrcI::OnSelchangeNid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_CrcI::FillListAllString_Node()
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
    
void CDlg_CrcI::FillListAllString_Curve()
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
    
void CDlg_CrcI::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}

void CDlg_CrcI::OnClosed()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
	//////////////////////////////////////////////// Update	 
  	m_bClosed	= TRUE;
	m_bArc		= FALSE;
	////////////////////////////////////////// Select
	GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);
	m_dAngSpec = 360.;
	GetDlgItem(IDC_TOTELEMS)->EnableWindow(TRUE);
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CrcI::OnAngspec() 
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
	//////////////////////////////////////////////// Update	 
	m_bClosed	= FALSE;
	m_bArc		= FALSE;
	////////////////////////////////////////// Select
	GetDlgItem(IDC_ANG_END)->EnableWindow(TRUE);
	if(m_CircType != CIRCLE_BY_ROT)
		GetDlgItem(IDC_HEAD_ANGORRAD)->SetWindowText("Arc Angle");
	else
		GetDlgItem(IDC_HEAD_ANGORRAD)->SetWindowText("Rot.Angle");
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CrcI::OnArc() 
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
	//////////////////////////////////////////////// Update	 
	m_bArc		= TRUE;
	m_bClosed	= FALSE;
	////////////////////////////////////////// Select
	GetDlgItem(IDC_ANG_END)->EnableWindow(FALSE);	
	GetDlgItem(IDC_HEAD_ANGORRAD)->SetWindowText("");
	GetDlgItem(IDC_TOTELEMS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TOTELEMHEAD)->SetWindowText("");
//
	GetDlgItem(IDC_ELEMS)->EnableWindow(TRUE);
   	////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_CrcI::OnAutoSeg()
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

void CDlg_CrcI::OnKillfocusSegAngle()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
}

void CDlg_CrcI::OnCancel() 
{
	////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_CRCIN,IDD_CANCEL);
	////////////////////////////////////////////////////
}

void CDlg_CrcI::OnUpdate() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_CircType == CIRCLE_BY_ROT)
	{
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
	}
	////////////////////////////////
	if(m_bClosed)
	{
		if(m_nTotElems<3)
		{
			AfxMessageBox(
				"INVALID DATA:\nFor Closed Circle\nAtleast 3 Elements\nShould be Specified!");
			GetDlgItem(IDC_TOTELEMS)->EnableWindow(TRUE);
			GetDlgItem(IDC_TOTELEMS)->SetFocus();
			/////////////////
			UpdateData(FALSE);
			/////////////////
			return;
		}
	}
	else
	if(m_nElemPerSeg<1)
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
		m_pWnd->SendMessage(ID_UPDATE_CRCIN,IDC_UPDATE);
}

void CDlg_CrcI::OnKillfocusCoord() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_CRCIN,IDC_COORD);
}

void CDlg_CrcI::OnAxis() 
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

void CDlg_CrcI::OnAxisX() 
{
	m_nAxis = 1;
}

void CDlg_CrcI::OnAxisY() 
{
	m_nAxis = 2;
}

void CDlg_CrcI::OnAxisZ() 
{
	m_nAxis = 3;
}

void CDlg_CrcI::OnNegative() 
{
	UpdateData(TRUE);
	/////////////////
//	m_bNegative = !m_bNegative;
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_CrcI::OnUniform() 
{
	UpdateData(TRUE);
	/////////////////
	if(m_bUniform)
		GetDlgItem(IDC_RATIO)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_RATIO)->EnableWindow(TRUE);
	/////////////////
	UpdateData(FALSE);
	/////////////////
}
/////////////////////////// end of module //////////////
