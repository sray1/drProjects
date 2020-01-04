//Dlg_LMTR.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include <float.h>		// DBL_MIN

#include "3DMath.h"
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
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "MNodRsrc.h"
#include "Dlg_LMR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_LMR dialog


CDlg_LMR::CDlg_LMR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_LMR::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_LMR)
	m_RotX 		= 0;
	m_RotY 		= 0;
	m_RotZ 		= 0;
	m_RotPtID 	= "";
	m_bAngleIn	= TRUE;
	m_FromID	= "";
	m_ToID		= "";
	m_bTangent	= FALSE;
	//}}AFX_DATA_INIT
}


void CDlg_LMR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_LMR)
	DDX_Text(pDX, IDC_ROT_X, m_RotX);
	DDV_MinMaxDouble(pDX, m_RotX, -360., 360.);
	DDX_Text(pDX, IDC_ROT_Y, m_RotY);
	DDV_MinMaxDouble(pDX, m_RotY, -360., 360.);
	DDX_Text(pDX, IDC_ROT_Z, m_RotZ);
	DDV_MinMaxDouble(pDX, m_RotZ, -360., 360.);
	DDX_CBString(pDX, IDC_ROTPT, m_RotPtID);
	DDX_Check(pDX, IDC_ANGLE_INPUT, m_bAngleIn);
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromID);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToID);
	DDX_Check(pDX, IDC_TANGENT, m_bTangent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_LMR, CDialog)
	//{{AFX_MSG_MAP(CDlg_LMR)
	ON_BN_CLICKED(IDC_ANGLE_INPUT, OnAngleInput)
	ON_CBN_SELCHANGE(IDC_CNODE_FROM, OnSelchangeCnodeFrom)
	ON_CBN_SELCHANGE(IDC_CNODE_TO, OnSelchangeCnodeTo)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDC_ANGLE_INPUT, OnAngleInput)
	ON_BN_CLICKED(IDC_TANGENT, OnTangent)
	ON_BN_DOUBLECLICKED(IDC_TANGENT, OnTangent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_LMR message handlers

BOOL CDlg_LMR::OnInitDialog()
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
	//////////////
//	FillListAllString(IDC_ROTPT,IstID);   // 
//	m_RotPtID 	= IstID;
	pWndCtrl 	= GetDlgItem(IDC_ROTPT);
	((CComboBox*)(pWndCtrl))->AddString(m_RotPtID);
	////////////////////////////////////////
	FillListAllString(IDC_CNODE_FROM,IstID);   // 
	pWndCtrl 	= GetDlgItem(IDC_CNODE_FROM);
	m_FromID 	= IstID;
	////////////////////////////////////////
	FillListAllString(IDC_CNODE_TO,IstID);   // 
	pWndCtrl 	= GetDlgItem(IDC_CNODE_TO);
	m_ToID 		= IstID;
	////////////////////////////////////////
	if(m_FromID == m_ToID)
		m_bAngleIn	= TRUE;
	else
		m_bAngleIn	= FALSE;
	////////////////////////
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
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(FALSE);
		///////////////////////////
	}
	else
	{
		/////////////////////////// Enable
		GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_Z)->EnableWindow(FALSE);
		/////////////////////////// Disable
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(TRUE);
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(TRUE);
		///////////////////////////
		ShowRotations();
	}
	//////////////////////////////////////////////// ALWAYS
	GetDlgItem(IDC_ROTPT)->EnableWindow(FALSE);
	//////////////////////////////////////////////// FOR FUTURE RELEASE
	GetDlgItem(IDC_TANGENT)->EnableWindow(FALSE);
	////////////////
	UpdateData(FALSE);
	//////////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_LMR::OnTangent() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlg_LMR::OnAngleInput() 
{
	/////////////////
	UpdateData(TRUE);
	////////////////////////
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
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(FALSE);
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(FALSE);
		///////////////////////////
	}
	else
	{
		/////////////////////////// Enable
		GetDlgItem(IDC_ROT_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_ROT_Z)->EnableWindow(FALSE);
		/////////////////////////// Disable
		GetDlgItem(IDC_CNODE_FROM)->EnableWindow(TRUE);
		GetDlgItem(IDC_CNODE_TO)->EnableWindow(TRUE);
		///////////////////////////
		ShowRotations();
	}
	//////////////////
	UpdateData(FALSE);
	//////////////////
	
}

void CDlg_LMR::OnSelchangeCnodeFrom() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	int index = ((CComboBox*)GetDlgItem(IDC_CNODE_FROM))->GetCurSel();
	if(index>=0)
		((CComboBox*)GetDlgItem(IDC_CNODE_FROM))->GetLBText(index,m_FromID);
	//////////////////
	ShowRotations();
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

void CDlg_LMR::OnSelchangeCnodeTo() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	int index = ((CComboBox*)GetDlgItem(IDC_CNODE_TO))->GetCurSel();
	if(index>=0)
		((CComboBox*)GetDlgItem(IDC_CNODE_TO))->GetLBText(index,m_ToID);
	//////////////////
	ShowRotations();
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

int CDlg_LMR::FillListAllString(UINT DlgItemID,CString& IstID)
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(DlgItemID);
	CString Nid;
	BOOL bGotStr = FALSE;
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

void CDlg_LMR::ShowRotations() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_FromID == m_ToID)
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
	C3DMath	Math3D;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	/////////////////////////////////////////////////	
	double One80byPi = 180./acos(-1.0);
	///////////////////////////////////
	WORLD LocFrom,LocTo;
	int index;
	CString Nid;
	//////////////
	if(pDListMgr)
	{	

		CWnd* pWndCtrl;
		CDrNode* pNode;
		///////////////
		pWndCtrl = GetDlgItem(IDC_CNODE_FROM);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LMat/SelC");
			return;
		}
		////////////	
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		LocFrom 	= *(pNode->GetLocalPos());			    
		///////////////
		pWndCtrl = GetDlgItem(IDC_CNODE_TO);
   		index = ((CComboBox*)pWndCtrl)->GetCurSel();
    	((CComboBox*)pWndCtrl)->GetLBText(index,Nid); 
        //////////
   		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LMat/SelC");
			return;
		}
		////////////	
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		LocTo 	= *(pNode->GetLocalPos());			    
	}
	////////////////////////////////////// Find Angles
	WORLD Angles;
	Math3D.Sub3DPts(&LocTo,&LocFrom,&Angles);
	double dLen = Math3D.Len3DPts(&Angles);
	if(fabs(dLen)<DBL_MIN)
	{
		///////////////////
		m_RotX 		= 0;
		m_RotY 		= 0;
		m_RotZ 		= 0;
		//////////////////
		return;
	}
	////////////////
	Math3D.Normalize(&Angles,&Angles);
	///////////////////
	m_RotX 		= acos(Angles.x) * One80byPi;
	m_RotY 		= acos(Angles.y) * One80byPi;
	m_RotZ 		= acos(Angles.z) * One80byPi;
	////////////////
	return;	
}

void CDlg_LMR::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_LMR::OnOK()
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	CDialog::OnOK();
}
//////////////////////////////// end of module //////////////
