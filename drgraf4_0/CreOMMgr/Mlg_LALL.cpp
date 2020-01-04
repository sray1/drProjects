// Dlg_LALL.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include <float.h>		// DBL_MIN

#include "3DMath.h"
#include "XForm.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "DListMgr.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrFE0D.h"
#include "DrMesh2D.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "CreMRsrc.h"
#include "Mlg_LALL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMlg_LALL dialog


CMlg_LALL::CMlg_LALL(CWnd* pParent /*=NULL*/)
	: CDialog(CMlg_LALL::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CMlg_LALL)
	m_RotX 		= 0;
	m_RotY 		= 0;
	m_RotZ 		= 0;
	m_TranX 	= 0;
	m_TranY 	= 0;
	m_TranZ 	= 0;
	m_TranPtID 	= "";
	m_bAngleIn	= TRUE;
	m_bCoordIn	= TRUE;
	m_ScaleX	= 1.0;
	m_ScaleY	= 1.0;
	m_ScaleZ	= 1.0;
	m_RotPtID	= _T("");
	m_ShearX	= 0.0;
	m_ShearY	= 0.0;
	m_ShearZ	= 0.0;
	m_FromID_R	= _T("");
	m_FromID_T	= _T("");
	m_ToID_R	= _T("");
	m_ToID_T	= _T("");
	m_bOrigin	= FALSE;
	//}}AFX_DATA_INIT
	m_bNoRot	= FALSE;
	m_bNoScale	= FALSE;
	m_bNoShear	= FALSE;
	m_bNoTran	= FALSE;
	////////////
	m_strUnit	= _T("");
	
}


void CMlg_LALL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMlg_LALL)
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
	DDX_Check(pDX, IDC_ANGLE_INPUT, m_bAngleIn);
	DDX_Check(pDX, IDC_COORD_INPUT, m_bCoordIn);
	DDX_Text(pDX, IDC_SCALE_X, m_ScaleX);
	DDV_MinMaxDouble(pDX, m_ScaleX, 0., 999999.);
	DDX_Text(pDX, IDC_SCALE_Y, m_ScaleY);
	DDV_MinMaxDouble(pDX, m_ScaleY, 0., 999999.);
	DDX_Text(pDX, IDC_SCALE_Z, m_ScaleZ);
	DDX_CBString(pDX, IDC_ROTPT, m_RotPtID);
	DDX_Text(pDX, IDC_SHEAR_X2, m_ShearX);
	DDV_MinMaxDouble(pDX, m_ShearX, 0., 999999.);
	DDX_Text(pDX, IDC_SHEAR_Y2, m_ShearY);
	DDV_MinMaxDouble(pDX, m_ShearY, 0., 999999.);
	DDX_Text(pDX, IDC_SHEAR_Z2, m_ShearZ);
	DDV_MinMaxDouble(pDX, m_ShearZ, 0., 999999.);
	DDX_CBString(pDX, IDC_CNODE_FROM_R, m_FromID_R);
	DDX_CBString(pDX, IDC_CNODE_FROM_T, m_FromID_T);
	DDX_CBString(pDX, IDC_CNODE_TO_R, m_ToID_R);
	DDX_CBString(pDX, IDC_CNODE_TO_T, m_ToID_T);
	DDX_Check(pDX, IDC_DIRCOS, m_bOrigin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMlg_LALL, CDialog)
	//{{AFX_MSG_MAP(CMlg_LALL)
	ON_CBN_SELCHANGE(IDC_TRANPT, OnSelchangeTranPt)
	ON_BN_CLICKED(IDC_ANGLE_INPUT, OnAngleInput)
	ON_CBN_SELCHANGE(IDC_CNODE_FROM_R, OnSelchangeCnodeFrom_R)
	ON_CBN_SELCHANGE(IDC_CNODE_TO_R, OnSelchangeCnodeTo_R)
	ON_CBN_SELCHANGE(IDC_CNODE_FROM_T, OnSelchangeCnodeFrom_T)
	ON_CBN_SELCHANGE(IDC_CNODE_TO_T, OnSelchangeCnodeTo_T)
	ON_BN_CLICKED(IDC_COORD_INPUT, OnCoordInput)
	ON_CBN_SELCHANGE(IDC_ROTPT, OnSelchangeRotpt)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDC_ANGLE_INPUT, OnAngleInput)
	ON_BN_DOUBLECLICKED(IDC_COORD_INPUT, OnCoordInput)
	ON_BN_CLICKED(IDC_DIRCOS, OnOrigin)
	ON_BN_DOUBLECLICKED(IDC_DIRCOS, OnOrigin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMlg_LALL message handlers

BOOL CMlg_LALL::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////////////////////////////
	CString IstID;
	CWnd* pWndCtrl;
	///////////////////////////////////////// 
	FillListAllString(IDC_ROTPT,IstID);   //
	m_RotPtID 	= IstID;
	pWndCtrl 	= GetDlgItem(IDC_ROTPT);
	((CComboBox*)pWndCtrl)->SetCurSel(0);
	//////////////
	FillListAllString(IDC_TRANPT,IstID);   //
	m_TranPtID 	= IstID;
	OnSelchangeTranPt();
	////////////////////////////////////////
	FillListAllString(IDC_CNODE_FROM_R,IstID);   // 
	m_FromID_R 	= IstID;
	////////////////////////////////////////
	FillListAllString(IDC_CNODE_TO_R,IstID);   // 
	m_ToID_R 		= IstID;
	////////////////////////////////////////
	FillListAllString(IDC_CNODE_FROM_T,IstID);   // 
	m_FromID_T 	= IstID;
	////////////////////////////////////////
	FillListAllString(IDC_CNODE_TO_T,IstID);   // 
	m_ToID_T 		= IstID;
	////////////////////////////////////////
	if(m_FromID_R == m_ToID_R)
		m_bAngleIn	= TRUE;
	else
		m_bAngleIn	= FALSE;
	//
	if(m_FromID_T == m_ToID_T)
		m_bAngleIn	= TRUE;
	else
		m_bAngleIn	= FALSE;
	////////////////////////
	if(!m_bNoRot)								// YES Rotation
	{
		if(m_bAngleIn)				// Angle Input
		{
			///////////////////
			m_RotX 		= 0;
			m_RotY 		= 0;
			m_RotZ 		= 0;
			/////////////////////////// Enable
			GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
			GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
			GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
			/////////////////////////// Disable
			GetDlgItem(IDC_CNODE_FROM_R)->EnableWindow(FALSE);
			GetDlgItem(IDC_CNODE_TO_R)->EnableWindow(FALSE);
			GetDlgItem(IDC_CNODE_FROM_T)->EnableWindow(FALSE);
			GetDlgItem(IDC_CNODE_TO_T)->EnableWindow(FALSE);
			///////////////////////////
		}
		else
		{
			/////////////////////////// Enable
			GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
			GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
			GetDlgItem(IDC_ROT_Z)->EnableWindow(FALSE);
			/////////////////////////// Disable
			GetDlgItem(IDC_CNODE_FROM_R)->EnableWindow(TRUE);
			GetDlgItem(IDC_CNODE_TO_R)->EnableWindow(TRUE);
			GetDlgItem(IDC_CNODE_FROM_T)->EnableWindow(TRUE);
			GetDlgItem(IDC_CNODE_TO_T)->EnableWindow(TRUE);
			///////////////////////////
			ShowRotations();
		}
	}
	else											// NO Rotation
	{
		/////////////////////////// Disable
		GetDlgItem(IDC_ANGLE_INPUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_Z)->EnableWindow(FALSE);
		/////////////////////////// Disable
		GetDlgItem(IDC_CNODE_FROM_R)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_TO_R)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_FROM_T)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_TO_T)->EnableWindow(FALSE);
		///////////////////////////
	}
	////////////////////////
	if(!m_bNoTran)								// YES Translation
	{
		if(m_bCoordIn)				// Coord Input
		{
			///////////////////
			m_TranX		= 0;
			m_TranY 	= 0;
			m_TranZ 	= 0;
			m_TranPtID	= "";
			/////////////////////////// Enable
			GetDlgItem(IDC_TRANPT)->EnableWindow(FALSE);
			GetDlgItem(IDC_TRAN_X)->EnableWindow(TRUE);
			GetDlgItem(IDC_TRAN_Y)->EnableWindow(TRUE);
			GetDlgItem(IDC_TRAN_Z)->EnableWindow(TRUE);
			///////////////////////////
		}
		else
		{
			GetDlgItem(IDC_TRANPT)->EnableWindow(TRUE);
			/////////////////////////// Disable
			GetDlgItem(IDC_TRAN_X)->EnableWindow(FALSE);
			GetDlgItem(IDC_TRAN_Y)->EnableWindow(FALSE);
			GetDlgItem(IDC_TRAN_Z)->EnableWindow(FALSE);
			///////////////////
			ShowTranslations();
		}
	}
	else											// NO Translation
	{
		/////////////////////////// Disable
		GetDlgItem(IDC_COORD_INPUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRANPT)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_Z)->EnableWindow(FALSE);
		///////////////////////////
	}
	////////////////////////
	if(!m_bNoShear)								// YES Shear
	{
		/////////////////////////// Enable
		GetDlgItem(IDC_SHEAR_X2)->EnableWindow(TRUE);
		GetDlgItem(IDC_SHEAR_Y2)->EnableWindow(TRUE);
		GetDlgItem(IDC_SHEAR_Z2)->EnableWindow(TRUE);
		///////////////////////////
	}
	else										// No Shear
	{
		/////////////////////////// Disable
		GetDlgItem(IDC_SHEAR_X2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SHEAR_Y2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SHEAR_Z2)->EnableWindow(FALSE);
		///////////////////////////
	}
	////////////////////////
	if(!m_bNoScale)								// YES Scale
	{
		/////////////////////////// Enable
		GetDlgItem(IDC_SCALE_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_SCALE_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_SCALE_Z)->EnableWindow(TRUE);
		///////////////////////////
	}
	else										// No Scale
	{
		/////////////////////////// Disable
		GetDlgItem(IDC_SCALE_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCALE_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCALE_Z)->EnableWindow(FALSE);
		///////////////////////////
	}
	//////////////////////////////////////////////// ALWAYS
//	GetDlgItem(IDC_ROTPT)->EnableWindow(FALSE);
	//////////////////////////////////////////////// FOR FUTURE RELEASE
//	GetDlgItem(IDC_TANGENT)->EnableWindow(FALSE);
	////////////////
	UpdateData(FALSE);
	//////////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMlg_LALL::OnOrigin() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_bOrigin)
	{
		GetDlgItem(IDC_ROTPT)->EnableWindow(FALSE);
		///
		m_RotPtID = "Origin";
	}
	else
	{
		GetDlgItem(IDC_ROTPT)->EnableWindow(TRUE);
		///
		CWnd* pWndCtrl;
		pWndCtrl 	= GetDlgItem(IDC_ROTPT);
		((CComboBox*)pWndCtrl)->SetCurSel(0);
		///////////////////////////////////////// 
		((CComboBox*)pWndCtrl)->GetLBText(0,m_RotPtID);
	}
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CMlg_LALL::OnAngleInput() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_bAngleIn)				// Angle Input
	{
		///////////////////
		m_RotX 		= 0;
		m_RotY 		= 0;
		m_RotZ 		= 0;
		/////////////////////////// Enable
		GetDlgItem(IDC_ROT_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_ROT_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_ROT_Z)->EnableWindow(TRUE);
		/////////////////////////// Disable
		GetDlgItem(IDC_CNODE_FROM_R)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_TO_R)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_FROM_T)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_TO_T)->EnableWindow(FALSE);
		///////////////////////////
	}
	else
	{
		/////////////////////////// Disable
		GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_Z)->EnableWindow(FALSE);
		/////////////////////////// Enable
		GetDlgItem(IDC_CNODE_FROM_R)->EnableWindow(TRUE);
		GetDlgItem(IDC_CNODE_TO_R)->EnableWindow(TRUE);
		GetDlgItem(IDC_CNODE_FROM_T)->EnableWindow(TRUE);
		GetDlgItem(IDC_CNODE_TO_T)->EnableWindow(TRUE);
		///////////////////////////
 		CWnd* pWndCtrl = GetDlgItem(IDC_CNODE_FROM);
  		((CComboBox*)pWndCtrl)->SetCurSel(0);
		///////////////////
		ShowRotations();
	}
	//////////////////
	UpdateData(FALSE);
	//////////////////
}

void CMlg_LALL::OnCoordInput() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_bCoordIn)				// Coord Input
	{
		///////////////////
		m_TranX		= 0;
		m_TranY 	= 0;
		m_TranZ 	= 0;
		m_TranPtID	= "";
		/////////////////////////// Enable
		GetDlgItem(IDC_TRANPT)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_TRAN_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_TRAN_Z)->EnableWindow(TRUE);
		///////////////////////////
	}
	else
	{
		GetDlgItem(IDC_TRANPT)->EnableWindow(TRUE);
		/////////////////////////// Disable
		GetDlgItem(IDC_TRAN_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_TRAN_Z)->EnableWindow(FALSE);
		///////////////////////////
 		CWnd* pWndCtrl = GetDlgItem(IDC_TRANPT);
  		((CComboBox*)pWndCtrl)->SetCurSel(0);
		///////////////////
		ShowTranslations();
	}
	//////////////////
	UpdateData(FALSE);
	//////////////////
}

void CMlg_LALL::OnSelchangeCnodeFrom_R() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	int index = ((CComboBox*)GetDlgItem(IDC_CNODE_FROM_R))->GetCurSel();
	if(index>=0)
		((CComboBox*)GetDlgItem(IDC_CNODE_FROM_R))->GetLBText(index,m_FromID_R);
	//////////////////
	ShowRotations();
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

void CMlg_LALL::OnSelchangeCnodeTo_R() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	int index = ((CComboBox*)GetDlgItem(IDC_CNODE_TO_R))->GetCurSel();
	if(index>=0)
		((CComboBox*)GetDlgItem(IDC_CNODE_TO_R))->GetLBText(index,m_ToID_R);
	//////////////////
	ShowRotations();
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

void CMlg_LALL::OnSelchangeCnodeFrom_T() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	int index = ((CComboBox*)GetDlgItem(IDC_CNODE_FROM_T))->GetCurSel();
	if(index>=0)
		((CComboBox*)GetDlgItem(IDC_CNODE_FROM_T))->GetLBText(index,m_FromID_T);
	//////////////////
	ShowRotations();
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

void CMlg_LALL::OnSelchangeCnodeTo_T() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	int index = ((CComboBox*)GetDlgItem(IDC_CNODE_TO_T))->GetCurSel();
	if(index>=0)
		((CComboBox*)GetDlgItem(IDC_CNODE_TO_T))->GetLBText(index,m_ToID_T);
	//////////////////
	ShowRotations();
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

void CMlg_LALL::OnSelchangeRotpt() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

void CMlg_LALL::OnSelchangeTranPt()
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	ShowTranslations();
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

int CMlg_LALL::FillListAllString(UINT DlgItemID,CString& IstID)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(DlgItemID);
	CString Nid;
	BOOL bGotStr = FALSE;
	///////////////////////// 
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	if(pDListMgr)			// Allow All Nodes
	{
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			CDrObject* pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			int nObjType = pObject->GetObjectType();
			if(nObjType != FE0D)
				continue;
			////////////////	
			CDrFE0D* pNode = (CDrFE0D*)pObject;
   			Nid = pNode->GetObjectID();
	    	((CComboBox*)(pWndCtrl))->AddString(Nid);
	    	if(!bGotStr)
	    	{
	    		IstID = Nid;
	    		bGotStr !=bGotStr;
	    	}	
	    	/////////////////////////////////////////
		}	 
	}			    
	//////////
	return 0; 
    
}

void CMlg_LALL::ShowRotations() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(!m_bAngleIn)
	{
		if((m_FromID_R == m_ToID_R) || (m_FromID_T == m_ToID_T))
		{
			///////////////////
			m_RotX 		= 0;
			m_RotY 		= 0;
			m_RotZ 		= 0;
			//////////////////
			UpdateData(FALSE);
			//////////////////
			return;
		}
		////////////////////////////////////////////// Calc Rot
		SetCoords_Ref_N_Target();
		CalcRotationFromFromTo();
	}
	//////////////////////////
	return;
}

void CMlg_LALL::SetCoords_Ref_N_Target() 
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////////	
	int index;
	CString Nid;
	//////////////
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	if(pDListMgr)
	{	

		CWnd* pWndCtrl;
		CDrFE0D* pNode;
		///////////////////////////////////////////////////////////// Reference
		pWndCtrl = GetDlgItem(IDC_CNODE_FROM_R);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(FE0D,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:\nCDlg_LALL::SetCoords_Ref_N_Target()\nIDC_CNODE_FROM_R");
			return;
		}
		////////////	
		pNode = (CDrFE0D*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		m_wFrom_R = *(pNode->GetLocalPos());			    
		///////////////
		pWndCtrl = GetDlgItem(IDC_CNODE_TO_R);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(FE0D,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:\nCDlg_LALL::SetCoords_Ref_N_Target()\nIDC_CNODE_To_R");
			return;
		}
		////////////	
		pNode = (CDrFE0D*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		m_wTo_R	= *(pNode->GetLocalPos());			    
		///////////////////////////////////////////////////////////// Target
		pWndCtrl = GetDlgItem(IDC_CNODE_FROM_T);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(FE0D,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:\nCDlg_LALL::SetCoords_Ref_N_Target()\nIDC_CNODE_FROM_T");
			return;
		}
		////////////	
		pNode = (CDrFE0D*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		m_wFrom_T = *(pNode->GetLocalPos());			    
		///////////////
		pWndCtrl = GetDlgItem(IDC_CNODE_TO_T);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(FE0D,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:\nCDlg_LALL::SetCoords_Ref_N_Target()\nIDC_CNODE_To_T");
			return;
		}
		////////////	
		pNode = (CDrFE0D*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		m_wTo_T	= *(pNode->GetLocalPos());			    
	}
	////////////////
	return;	
}

int CMlg_LALL::CalcRotationFromFromTo() 
{
	/////////////////
	C3DMath	Math3D;
	CXForm	XForm;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////
//	WORLD LocFrom,LocTo;
	////////////////////////////////////// Find Angles
	WORLD Angle_R,Angle_T;
	Math3D.Sub3DPts(&m_wTo_R,&m_wFrom_R,&Angle_R);
	Math3D.Sub3DPts(&m_wTo_T,&m_wFrom_T,&Angle_T);

/*

	///////////////////////////////////////////////////////////////
	//					Matrix in Short way, But 
	//					do not fit SetUpLocalM
	//					demand of 3 Angles
	///////////////////////////////////////////////////////////////
	////////////////////////////////////////////// Matrices
	MATRIX M_R,M_T;
	pMATRIX pM_R = &M_R;
	pMATRIX pM_T = &M_T;
	//
	Math3D.GetIdentityMatrix(pM_R);
	Math3D.GetIdentityMatrix(pM_T);
	////////////////////////////////////////////// Reference to Z-Axis
	XForm.RotateToNewZMATRIX(&Angle_R, pM_R,XF_REPLACE); // to Reference as NewZ
	Math3D.TransposeMATRIX(pM_R);	// NewZ as Reference
	////////////////////////////////////////////// Z-Axis to Target
	XForm.RotateToNewZMATRIX(&Angle_T, pM_T,XF_REPLACE);
	////////////////
	Math3D.F_MultMATRIX(pM_T,pM_R,&m_MAT);
	/////////
*/
	/////////////////////////////////////////////////	
	double One80byPi = 180./acos(-1.0);
	//////////////////////////////////////////
	Math3D.Normalize(&Angle_R,&Angle_R);
	Math3D.Normalize(&Angle_T,&Angle_T);
	///////////////////////////////////////////////////////////////
	//					Angles in Long way 
	//					to fit SetUpLocalM
	//					demand of 3 Angles
	///////////////////////////////////////////////////////////////
	MATRIX Mat;
	pMATRIX pM = &Mat;
	double dRx,dRy,dRz;
	WORLD Proj_R,Proj_T,wDir;
	///////////////////////////////////// RotY
	Proj_R.y	= 0.0;
	Proj_R.x	= Angle_R.x;
	Proj_R.z	= Angle_R.z;
	//
	Proj_T.y	= 0.0;
	Proj_T.x	= Angle_T.x;
	Proj_T.z	= Angle_T.z;
	Math3D.Normalize(&Proj_R,&Proj_R);
	Math3D.Normalize(&Proj_T,&Proj_T);
	wDir.y		= Math3D.Dot3DPts(&Proj_R,&Proj_T);
	///////////////////
	dRy = acos(wDir.y) * One80byPi;
	////////////////
	Math3D.GetIdentityMATRIX(pM);
	XForm.Rotate_Y(pM, dRy, XF_REPLACE );
	XForm.Transform(&Angle_R, &Angle_R, pM);
	Math3D.Normalize(&Angle_R,&Angle_R);
	///////////////////////////////////// RotX
	Proj_R.x	= 0.0;
	Proj_R.y	= Angle_R.y;
	Proj_R.z	= Angle_R.z;
	//
	Proj_T.x	= 0.0;
	Proj_T.y	= Angle_T.y;
	Proj_T.z	= Angle_T.z;
	Math3D.Normalize(&Proj_R,&Proj_R);
	Math3D.Normalize(&Proj_T,&Proj_T);
	wDir.x		= Math3D.Dot3DPts(&Proj_R,&Proj_T);
	///////////////////
	dRx = acos(wDir.x) * One80byPi;
	////////////////
	Math3D.GetIdentityMATRIX(pM);
	XForm.Rotate_X(pM, dRx, XF_REPLACE );
	XForm.Transform(&Angle_R, &Angle_R, pM);
	Math3D.Normalize(&Angle_R,&Angle_R);
	///////////////////////////////////// RotZ
	Proj_R.z	= 0.0;
	Proj_R.x	= Angle_R.x;
	Proj_R.y	= Angle_R.y;
	//
	Proj_T.z	= 0.0;
	Proj_T.x	= Angle_T.x;
	Proj_T.y	= Angle_T.y;
	Math3D.Normalize(&Proj_R,&Proj_R);
	Math3D.Normalize(&Proj_T,&Proj_T);
	wDir.z		= Math3D.Dot3DPts(&Proj_R,&Proj_T);
	///////////////////
	dRz = acos(wDir.z) * One80byPi;
	///////////////////////////////////// Angle in Degrees
	m_RotX = dRx;
	m_RotY = dRy;
	m_RotZ = dRz;
//	CalcRotationFromDirCos(wDir); 
	////////////////
	return 0;	
}

void CMlg_LALL::ShowTranslations() 
{
	if(m_TranPtID == "")
		return;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
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
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
	if(pDListMgr)
	{	

		CWnd* pWndCtrl = GetDlgItem(IDC_TRANPT);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(FE0D,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LMat/SelC");
			return;
		}
		////////////	
		CDrFE0D* pNode = (CDrFE0D*)pDListMgr->GetObject(index);
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
	return;	
}

void CMlg_LALL::OnCancel()
{
	/////////////////////////////////////////////////// Save
	m_bInstanced	= FALSE;
	m_pMatObj		= NULL;
	///////////////////////////////
	CDialog::OnCancel();
}

void CMlg_LALL::OnOK()
{
	//////////////////////////////////////////////// Get Transformation Details	 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_bOrigin)
	{
		m_RotPtID = "";
		m_wRotPt.x = 0.0;
		m_wRotPt.y = 0.0;
		m_wRotPt.z = 0.0;
	}
	else
	if(m_RotPtID == "")
   	{
   		AfxMessageBox("Please Select a Rotate_About Node ID");
		///
		CWnd* pWndCtrl;
		pWndCtrl 	= GetDlgItem(IDC_ROTPT);
		((CComboBox*)pWndCtrl)->SetCurSel(0);
		((CComboBox*)pWndCtrl)->SetFocus();
		///////////////////////////////////////// 
   		return;
   	}
	else
	{
		CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(FE0D);
		int index = pDListMgr->GetObjectIndex(FE0D,m_RotPtID);
		if(index<0)			// Center is Origin
		{
			m_wRotPt.x = 0.0;
			m_wRotPt.y = 0.0;
			m_wRotPt.z = 0.0;
		}
		else
		{	
			////////////	
			CDrFE0D* pNode = (CDrFE0D*)pDListMgr->GetObject(index);
			//////////
			m_wRotPt = *(pNode->GetLocalPos());
		}				    
	}
	/////////////////////////////////////// SetUp Local Matrix
	MATRIX Mat;
	pMATRIX pM = &Mat;
	//////////////////
	SetUpLocalm(pM);
	///////////////////////////////// Compact
	WORLD wRot,wTran,wScale,wShear;
	/////
	wRot.x		= m_RotX;
	wRot.y		= m_RotY;
	wRot.z		= m_RotZ;
	/////////////////
	wTran.x		= m_TranX;
	wTran.y		= m_TranY;
	wTran.z		= m_TranZ;
	/////////////////
	wScale.x	= m_ScaleX;
	wScale.y	= m_ScaleY;
	wScale.z	= m_ScaleZ;
	/////////////////
	wShear.x	= m_ShearX;
	wShear.y	= m_ShearY;
	wShear.z	= m_ShearZ;
	////////////////////////////////////////////////////////// New MatObj
	m_pMatObj = new CMatObj;
	/////////////////////////////////////////////////// Save
	m_pMatObj->SetXformType(XT_XFORMS);
	m_pMatObj->SetCreOp(COP_SPAWN);
	m_pMatObj->SetMatrix(pM);
	///////////////////////////
	m_bInstanced = TRUE;
	m_pMatObj->SetInstanced_Prof(TRUE);
	/////////////////////////////////// Grab Node
	m_pMatObj->SetRotPtID(m_RotPtID);	
	m_pMatObj->SetRotPt(m_wRotPt);	
	///////////////////////////////////////////// Translation
	m_pMatObj->SetTranPtID(m_TranPtID);	//To Tran
	m_pMatObj->SetTranslation(wTran);
	m_pMatObj->SetCoordIn(m_bCoordIn);
	///////////////////////////////////////////// Rotation
	m_pMatObj->SetAngleIn(m_bAngleIn);
	m_pMatObj->SetDirCos(m_bOrigin);
	m_pMatObj->SetFromID(m_FromID_R);
	m_pMatObj->SetFromPt(m_wFrom_R);
	m_pMatObj->SetToID(m_ToID_R);
	m_pMatObj->SetToPt(m_wTo_R);			// same as m_wTran
	m_pMatObj->SetRotation(wRot);
	///////////////////////////////////////////// Scale
	m_pMatObj->SetScale(wScale);
	///////////////////////////////////////////// SHear
	m_pMatObj->SetShear(wShear);
	/////////////////////////////////////////////
	m_pMatObj->SetNoRot(m_bNoRot);
	m_pMatObj->SetNoTran(m_bNoTran);
	m_pMatObj->SetNoScale(m_bNoScale);
	m_pMatObj->SetNoShear(m_bNoTran);
	////////////////////////////////
	CDialog::OnOK();
}

void CMlg_LALL::SetUpLocalm(pMATRIX pM)
{
	///////////////////////////////////////////////////// 			 
	C3DMath	Math3D;
	CXForm	XForm;
	//////////////////////////////////////////////// Get Transformation Details	 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////// strip Scale Factor (World Coord)
	pObjectMgr->SCtoDS(&m_TranX);
	m_TranX *= (dWorldBase/dMapFactor);
	pObjectMgr->SCtoDS(&m_TranY);
	m_TranY *= (dWorldBase/dMapFactor);
	pObjectMgr->SCtoDS(&m_TranZ);
	m_TranZ *= (dWorldBase/dMapFactor);
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	MATRIX TM;			// to translate by CenterPT
	pMATRIX pTM = &TM;
	Math3D.GetIdentityMATRIX(pTM);
	///////////////////////////////////////////////////////// Rotation
	XForm.Translate(pTM,-m_wRotPt.x,-m_wRotPt.y,-m_wRotPt.z,XF_REPLACE);
	/////////////////////////////////////
	XForm.ComposeLocalMATRIX(pM,
							m_RotX,		m_RotY,		m_RotZ,
							m_ScaleX,	m_ScaleY,	m_ScaleZ, 
							m_ShearX,	m_ShearY,	m_ShearZ, 
							m_TranX,	m_TranY,	m_TranZ	);
	////////////////////////////////////////////////////
	Math3D.F_MultMATRIX(pM,pTM,pM);
	///////////////////////////////
	return;
}

//////////////////////////////// end of module //////////////
