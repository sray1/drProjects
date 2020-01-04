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
#include "DrNode.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "CMgrRsrc.h"
#include "Dlg_LSym.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_LSym dialog


CDlg_LSym::CDlg_LSym(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_LSym::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_LSym)
	m_RotPtID	= _T("");
	m_FromID	= "";
	m_ToID		= "";
	//}}AFX_DATA_INIT
	
}


void CDlg_LSym::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_LSym)
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromID);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToID);
	DDX_CBString(pDX, IDC_ROTPT, m_RotPtID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_LSym, CDialog)
	//{{AFX_MSG_MAP(CDlg_LSym)
	ON_CBN_SELCHANGE(IDC_CNODE_FROM, OnSelchangeCnodeFrom)
	ON_CBN_SELCHANGE(IDC_CNODE_TO, OnSelchangeCnodeTo)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_CBN_SELCHANGE(IDC_ROTPT, OnSelchangeRotpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_LSym message handlers

BOOL CDlg_LSym::OnInitDialog()
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
	////////////////////////////////////////
	FillListAllString(IDC_ROTPT,IstID);   // 
	m_RotPtID 	= IstID;
	pWndCtrl 	= GetDlgItem(IDC_ROTPT);
	((CComboBox*)pWndCtrl)->SetCurSel(0);
	////////////////////////////////////////
	FillListAllString(IDC_CNODE_FROM,IstID);   // 
	m_FromID 	= IstID;
	////////////////////////////////////////
	FillListAllString(IDC_CNODE_TO,IstID);   // 
	m_ToID 		= IstID;
	////////////////////////////////////////
	GetDlgItem(IDC_ROTPT)->SetFocus();
	////////////////
	UpdateData(FALSE);
	//////////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_LSym::OnSelchangeCnodeFrom() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	int index = ((CComboBox*)GetDlgItem(IDC_CNODE_FROM))->GetCurSel();
	if(index>=0)
		((CComboBox*)GetDlgItem(IDC_CNODE_FROM))->GetLBText(index,m_FromID);
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

void CDlg_LSym::OnSelchangeCnodeTo() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	int index = ((CComboBox*)GetDlgItem(IDC_CNODE_TO))->GetCurSel();
	if(index>=0)
		((CComboBox*)GetDlgItem(IDC_CNODE_TO))->GetLBText(index,m_ToID);
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}

void CDlg_LSym::OnSelchangeRotpt() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	//////////////////
	UpdateData(FALSE);	// update screen
	//////////////////
}
int CDlg_LSym::FillListAllString(UINT DlgItemID,CString& IstID)
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

void CDlg_LSym::OnCancel()
{
	/////////////////////////////////////////////////// Save
	m_bInstanced	= FALSE;
	m_pMatObj		= NULL;
	///////////////////////////////
	CDialog::OnCancel();
}

void CDlg_LSym::OnOK()
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_RotPtID == "")
   	{
   		AfxMessageBox("Please Select a Point(NodeID) on the Plane");
 		GetDlgItem(IDC_ROTPT)->SetFocus();
  		return;
   	}
	/////////////////////////////////////// SetUp Local Matrix
	MATRIX Mat;
	pMATRIX pM = &Mat;
	//////////////////
	SetUpLocalm(pM);
	////////////////////////////////////////////////////////// New MatObj
	m_pMatObj = new CMatObj;
	/////////////////////////////////////////////////// Save
	m_pMatObj->SetXformType(XT_SYMMETRIC);
	m_pMatObj->SetMatrix(pM);
	///////////////////////////
	m_bInstanced = TRUE;
	m_pMatObj->SetInstanced_Prof(TRUE);
	m_pMatObj->SetFromID(m_FromID);
	m_pMatObj->SetToID(m_ToID);
	m_pMatObj->SetRotPtID(m_RotPtID);
	////////////////////////////////
	CDialog::OnOK();
}

void CDlg_LSym::GetUnitNormal(pWORLD pNormal) 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_FromID == "")
   	{
   		AfxMessageBox("Please Select a Point(NodeID) to define the Normal");
 		GetDlgItem(IDC_CNODE_FROM)->SetFocus();
  		return;
   	}
	if(m_ToID == "")
   	{
   		AfxMessageBox("Please Select a Point(NodeID) to define the Normal");
 		GetDlgItem(IDC_CNODE_TO)->SetFocus();
  		return;
   	}
	if(m_FromID == m_ToID)
   	{
   		AfxMessageBox("Normal Undefined!\nSelect distinct Nodes");
		GetDlgItem(IDC_CNODE_FROM)->SetFocus();
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
	////////////////////////////////////// Find Unit Axis
	Math3D.Sub3DPts(&LocTo, &LocFrom, pNormal);
	Math3D.Normalize(pNormal,pNormal);
	///////////////
	return;	
}

void CDlg_LSym::SetUpLocalm(pMATRIX pM)
{
	////////////////////////////////////////////////////////////
	//	PLANE: Ax+By+Cz+D=0  or r.N = p
	//
	//		Given:
	//			r = (x,y,z) = Radius Vector (Pt. on the Plane)
	//			N = (A,B,C) = Normal
	//			p = -D		= Distance of the Plane from a
	//							parallel plane thro' Origin
	//		Find:
	//	Local Matrix:
	//	
	//			Ra'	= [I - 2*n*nTrans]Ra + (2*p)n
	//
	//
	//	LOCAL MATRIX: in Homogeneous Coords
	//
	//			1-2*(A**2)		 -2*A*B		 -2*A*C		|	2*p*A
	//			 -2*A*B  		1-2*(B**2)	 -2*B*C		|	2*p*B
	//			 -2*A*C  		 -2*B*C		1-2*(C**2)	|	2*p*C
	//			-------------------------------------------------
	//				0				0			0		|     1	
	//	
	////////////////////////////////////////////////////////////// 			 
	C3DMath	Math3D;
	CXForm	XForm;
	//////////////////////////////////////////////// Get Transformation Details	 
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	////////////////////////////////////////Point on the Plane
	WORLD LocR;
	int index;
	/////////////////////////////////////////////
	index = pDListMgr->GetObjectIndex(NODE,m_RotPtID);
	if(index<0)			// Center is Origin
	{
		LocR.x = 0.0;
		LocR.y = 0.0;
		LocR.z = 0.0;
	}
	else
	{	
		////////////	
		CDrNode* pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////
		LocR = *(pNode->GetLocalPos());
	}				    
	////////////////////////////////////////Unit Normal to the Plane
	WORLD Normal;
	GetUnitNormal(&Normal);
	//////////////////////////////////////// p = rdotn
	double p = Math3D.Dot3DPts(&LocR,&Normal);
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	XForm.Reflect(pM,Normal,p);
	///////////////////////////////
	return;
}

//////////////////////////////// end of module //////////////
