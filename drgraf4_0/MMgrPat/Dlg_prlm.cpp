// dlg_prlm.cpp : implementation file
//

#include "stdafx.h"
#include "math.h"

#include "3Dmath.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
//#include "elextern.h"
#include "DrNode.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "dlg_prlm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_PrLM dialog


CDlg_PrLM::CDlg_PrLM(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_PrLM::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_PrLM)
	m_RotX 		= 0;
	m_RotY 		= 0;
	m_RotZ 		= 0;
	m_TranX 	= 0;
	m_TranY 	= 0;
	m_TranZ 	= 0;
	m_TranPtID 	= "";
	m_RotPtID 	= "";
	m_FromID 	= "";
	m_ToID 		= "";
	//}}AFX_DATA_INIT
}

void CDlg_PrLM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PrLM)
	DDX_Text(pDX, IDC_ROT_X, m_RotX);
	DDV_MinMaxDouble(pDX, m_RotX, -360., 360.);
	DDX_Text(pDX, IDC_ROT_Y, m_RotY);
	DDV_MinMaxDouble(pDX, m_RotY, -360., 360.);
	DDX_Text(pDX, IDC_ROT_Z, m_RotZ);
	DDV_MinMaxDouble(pDX, m_RotZ, -360., 360.);
	DDX_Text(pDX, IDC_TRAN_X, m_TranX);
	DDX_Text(pDX, IDC_TRAN_Y, m_TranY);
	DDX_Text(pDX, IDC_TRAN_Z, m_TranZ);
	DDX_CBString(pDX, IDC_TRANPT, m_TranPtID);
	DDX_CBString(pDX, IDC_ROTPT, m_RotPtID);
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromID);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_PrLM, CDialog)
	//{{AFX_MSG_MAP(CDlg_PrLM)
	ON_CBN_SELCHANGE(IDC_TRANPT, OnSelchangeTranPt)
	ON_CBN_SELCHANGE(IDC_ROTPT, OnSelchangeRotPt)
	ON_CBN_EDITCHANGE(IDC_CNODE_FROM, OnEditchangeCnodeFrom)
	ON_CBN_EDITCHANGE(IDC_CNODE_TO, OnEditchangeCnodeTo)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDC_NO_ROT, OnNoRot)
	ON_BN_DOUBLECLICKED(IDC_NO_ROT, OnNoRot)
	ON_BN_CLICKED(IDC_NO_TRAN, OnNoTran)
	ON_BN_DOUBLECLICKED(IDC_NO_TRAN, OnNoTran)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_PrLM message handlers

BOOL CDlg_PrLM::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////////////////////////////
	FillListAllString(IDC_CNODE_FROM);   // 
	FillListAllString(IDC_CNODE_TO);   // 
	//////////////////////////////
//	if(m_bCurve_Ist)
//	{
		FillListAllString(IDC_TRANPT);   //
		FillListAllString(IDC_ROTPT);   //
		//////////////////////////////////////////// Radio Both False
		((CButton*)GetDlgItem(IDC_NO_TRAN))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_NO_ROT ))->SetCheck(FALSE);
		
//	}	
/*
	else
	{
	
		CComboBox* pWndCtrl;
		///////////////////////////////////////////////////////// Show & Disable
		pWndCtrl = (CComboBox*)GetDlgItem(IDC_TRANPT);
    	pWndCtrl->AddString(m_TranPtID);
    	pWndCtrl->SetCurSel(0);
    	OnSelchangeTranPt();
		pWndCtrl->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_Z)->EnableWindow(FALSE);
		//////////////////////////////////////////// Radio Trans False
		((CButton*)GetDlgItem(IDC_NO_TRAN))->SetCheck(FALSE);
		////////////////////////////////////////////
		GetDlgItem(IDC_NO_TRAN)->EnableWindow(FALSE);
		GetDlgItem(IDC_NO_ROT)->EnableWindow(FALSE);
		//////////////////////////////////////////// RotPt False
		pWndCtrl = (CComboBox*)GetDlgItem(IDC_ROTPT);
    	pWndCtrl->AddString(m_RotPtID);
    	pWndCtrl->SetCurSel(0);
    	OnSelchangeRotPt();
		pWndCtrl->EnableWindow(FALSE);
	}
*/		
	////////////////
	UpdateData(FALSE);
	//////////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_PrLM::OnNoRot()
{
		((CButton*)GetDlgItem(IDC_NO_ROT ))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_NO_TRAN))->SetCheck(FALSE);
		////////////////////
		CComboBox* pWndCtrl;
		///////////////////////////////////////////////////////// Disable Rotation
		pWndCtrl = (CComboBox*)GetDlgItem(IDC_ROTPT);
		pWndCtrl->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_Z)->EnableWindow(FALSE);
		///////////////////////////////////////////////////////// Enable Translation  
		pWndCtrl = (CComboBox*)GetDlgItem(IDC_TRANPT);
		pWndCtrl->EnableWindow(TRUE);
		GetDlgItem(IDC_TRAN_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_TRAN_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_TRAN_Z)->EnableWindow(TRUE);
}

void CDlg_PrLM::OnNoTran()
{
		((CButton*)GetDlgItem(IDC_NO_TRAN))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_NO_ROT ))->SetCheck(FALSE);
		////////////////////
		CComboBox* pWndCtrl;
		///////////////////////////////////////////////////////// Enable Rotation
		pWndCtrl = (CComboBox*)GetDlgItem(IDC_ROTPT); 
		pWndCtrl->EnableWindow(TRUE);
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(TRUE);
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(TRUE);
		GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
		///////////////////////////////////////////////////////// Disable Translation  
		pWndCtrl = (CComboBox*)GetDlgItem(IDC_TRANPT);
		pWndCtrl->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_Z)->EnableWindow(FALSE);
}

int CDlg_PrLM::FillListAllString(UINT DlgItemID)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(DlgItemID);
	CString Nid;
	///////////////////////// 
	if(pDListMgr)			// Allow All Nodes
	{
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			int nObjType = pObject->GetObjectType();
			if(nObjType != NODE)
				continue;
			////////////////	
			CDrNode* pNode = (CDrNode*)pObject;
   			Nid = pNode->GetObjectID();
	    	((CComboBox*)(pWndCtrl))->AddString(Nid);
	    	/////////////////////////////////////////
		}	 
	}			    
	//////////
	return 0; 
    
}

void CDlg_PrLM::OnSelchangeTranPt()
{
			 
	/////////////////
	UpdateData(TRUE);
	/////////////////
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////////	
	WORLD LocR;
	int index;
	CString Nid;
	//////////////
	if(pDListMgr)
	{	

		CWnd* pWndCtrl = GetDlgItem(IDC_TRANPT);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LMat/SelC");
			return;
		}
		////////////	
		CDrNode* pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		LocR 	= *(pNode->GetLocalPos());			    
		LocR.x /= (dWorldBase/dMapFactor);
		LocR.y /= (dWorldBase/dMapFactor);
		LocR.z /= (dWorldBase/dMapFactor);
		pObjectMgr->DStoSC(&LocR.x);
		pObjectMgr->DStoSC(&LocR.y);
		pObjectMgr->DStoSC(&LocR.z);
	}
	////////////////////////////////////// Fill Edits
	m_TranX 	= LocR.x;
	m_TranY 	= LocR.y;
	m_TranZ 	= LocR.z;
	m_TranPtID 	= Nid;
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
	
}

void CDlg_PrLM::OnSelchangeRotPt()
{
			 
	/////////////////
	UpdateData(TRUE);
	/////////////////
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	///////////////////////////////////////////////
	int index;
	CString Nid;
	//////////////
	if(pDListMgr)
	{	

		CWnd* pWndCtrl = GetDlgItem(IDC_ROTPT);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
	}        
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
	
}

void CDlg_PrLM::OnEditchangeCnodeFrom()
{
			 
	/////////////////
	UpdateData(TRUE);
	///////////////// 
	if( ("" == m_FromID) || ("" == m_ToID) )
		return;
	else
		SetRotAngles();	
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
		
}

void CDlg_PrLM::OnEditchangeCnodeTo()
{
			 
	/////////////////
	UpdateData(TRUE);
	///////////////// 
	if( ("" == m_FromID) || ("" == m_ToID) )
		return;
	else
		SetRotAngles();	
	//////////////////
	UpdateData(FALSE);	// update screen
	/////////////////////////////////////////////////////////
	
}

void CDlg_PrLM::SetRotAngles()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
	/////////////////////////////////////////////////	
	WORLD LocR_F,LocR_T,Axis;
	int index;
	//////////////
	if(pDListMgr)
	{
		CDrNode* pNode;	
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,m_FromID,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LMat/SelC");
			return;
		}
		////////////	
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		LocR_F 	= *(pNode->GetLocalPos());			    
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,m_ToID,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LMat/SelC");
			return;
		}
		////////////	
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		LocR_F 	= *(pNode->GetLocalPos());			    
	}
	///////////////////////////////////////////////////////// Find UnitAxis
	C3DMath Math3D;
	Math3D.Sub3DPts(&LocR_T, &LocR_F, &Axis);
	double r = Math3D.Len3DPts(&Axis);
	Math3D.Scale3DPts(r,&Axis);
	///////////////////////////////////////////////////////// Find Degrees and set
	double pi180 = 180./acos(-1.);
	m_RotX 	= acos(Axis.x) * pi180;
	m_RotY 	= acos(Axis.y) * pi180;
	m_RotZ 	= acos(Axis.z) * pi180;
	//////////////////
	return;
}

void CDlg_PrLM::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_PrLM::OnOK()
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(	(m_TranPtID	== "") && (m_RotPtID == "") )
	{
		AfxMessageBox(
			"Please Use Cancel to Exit!");
		///////					 
		return;	// do over				
	}
	////////////////
	CDialog::OnOK();
}
//////////////////////////////// end of module //////////////
