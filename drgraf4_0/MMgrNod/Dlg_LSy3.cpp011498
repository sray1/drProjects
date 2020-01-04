// Dlg_LSy3.cpp : implementation file
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
#include "CommRsrc.h"
#include "Dlg_LSy3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_LSy3 dialog


CDlg_LSy3::CDlg_LSy3(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_LSy3::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_LSy3)
	//}}AFX_DATA_INIT
	
}


void CDlg_LSy3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_LSy3)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_LSy3, CDialog)
	//{{AFX_MSG_MAP(CDlg_LSy3)
	ON_BN_CLICKED(IDD_ADD, OnAdd)
	ON_BN_CLICKED(IDD_DEL, OnDel)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_LBN_DBLCLK(IDD_POOLLIST, OnAdd)
	ON_BN_DOUBLECLICKED(IDD_ADD, OnAdd)
	ON_BN_DOUBLECLICKED(IDD_DEL, OnDel)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_LSy3 message handlers

BOOL CDlg_LSy3::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	//////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///////////////////////////////////////////////
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMaxNodes)
		FillListAllString_Pool();   // with C/Nodes
	////////////////////////////////////////
	GetDlgItem(IDD_POOLLIST)->SetFocus();
	////////////////
	UpdateData(FALSE);
	//////////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlg_LSy3::OnDel()
{
	//delete current selection from SelectList	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
   	if(index>=0)
		((CListBox*)(pWndCtrl))->DeleteString(index); 
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_LSy3::OnAdd()
{
	// Add Current selction of POOLLIST to SELECTLIST	
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    /////////////////////////////////////////////////// Only 3 Nodes Required for Circle
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int nData 		= ((CListBox*)(pWndCtrl))->GetCount();
    if(nData >=3)	// 
	{
		AfxMessageBox("You may Select Exactly 3 Nodes\nTo Define a Plane !");
		return; 
	}
	////////////////////////////////////////////////	
	pWndCtrl = GetDlgItem(IDD_POOLLIST);
   	int index = ((CListBox*)pWndCtrl)->GetCurSel();
   	if(index>=0)
   	{
		CString CNid;
		((CListBox*)(pWndCtrl))->GetText(index,CNid);
		////////////////////////////////////// 
		pWndCtrl = GetDlgItem(IDD_SELECTLIST);
		if( (((CListBox*)(pWndCtrl))->FindString(-1,CNid) ) >=0)     // already selected:
			return;                                                  // Distinct Data Only
		((CListBox*)(pWndCtrl))->AddString(CNid);
	}
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CDlg_LSy3::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	/////////////////////////////////
	//	 Check first If Adequate Number of DataNodes: AtLeast 2
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
   	int nCount = ((CListBox*)pWndCtrl)->GetCount();
   	/////////////////////////////////////////////// Minimum Required
   	int nMinCNode = 3; // m_nHowMany = 3
   	////////////////////////	
   	if(nCount != nMinCNode)
   	{
   		CString str;
   		char buf[100];
   		sprintf(buf,"Exact No. of Data Nodes Required = %d\
   					\nNo. of Data Nodes Selected = %d",nMinCNode,nCount	);
   		AfxMessageBox(str = buf);
   		return;
   	}
	/////////////////////////////////////////////////	
	CString Nid[3];
	///////////////
	for(int i=0;i<3;i++)
	{
		((CListBox*)pWndCtrl)->GetText(i,Nid[i]);
		///////////////
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
	m_pMatObj->SetFromID(Nid[0]);		// Ist
	m_pMatObj->SetToID(Nid[1]);			// 2nd
	m_pMatObj->SetRotPtID(Nid[2]);		// 3rd
	////////////////////////////////
	CDialog::OnOK();
}

void CDlg_LSy3::OnCancel()
{
	/////////////////////////////////////////////////// Save
	m_bInstanced	= FALSE;
	m_pMatObj		= NULL;
	////////////////////
	CDialog::OnCancel();
}

void CDlg_LSy3::FillListAllString_Pool()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_POOLLIST);
	CString Nid;
	
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);
    if(nMaxNodes<=0)
		return;
	/////////////////
	CDrObject* pObject;			       
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if( pObject->GetObjectType() == NODE)
		{ 
			CDrNode* pNode = (CDrNode*)pObject;
			Nid   = (pNode->GetNodeCard())->id;
	    	((CListBox*)(pWndCtrl))->AddString(Nid);
		}			    
   	}
} 
    
void CDlg_LSy3::EmptyListAllString()
{
			 
	CWnd* pWndCtrl = GetDlgItem(IDD_SELECTLIST);
    int i,nMaxListItems;  
    
    nMaxListItems = ((CListBox*)(pWndCtrl))->GetCount();
	if( nMaxListItems ) 
		for (i=0;i<nMaxListItems;i++)
		((CListBox*)(pWndCtrl))->DeleteString(0); 
    
}
    
void CDlg_LSy3::GetUnitNormal(pWORLD pNormal) 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	C3DMath	Math3D;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	/////////////////////////////////////////////////	
	WORLD	Loc[3];
	WORLD	a;
	WORLD	b;
	int index;
	CString Nid;
	//////////////
	CListBox* pWndCtrl = (CListBox*)GetDlgItem(IDD_SELECTLIST);
	CDrNode* pNode;
	///////////////
	for(int i=0;i<3;i++)
	{
		pWndCtrl->GetText(i,Nid);
	    //////////
		if((index= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1)) <0)
		{
			AfxMessageBox("Internal Problem:Dlg_LSy3\nGetUnitNormal");
			return;
		}
		////////////	
		pNode = (CDrNode*)pDListMgr->GetObject(index);
		//////////////////////////////// scale etc
		Loc[i] 	= *(pNode->GetLocalPos());			    
		///////////////
	}
	////////////////////////////////////// Find Unit Normal
	Math3D.Sub3DPts(&(Loc[1]), &(Loc[0]), &a);
	Math3D.Sub3DPts(&(Loc[2]), &(Loc[0]), &b);
	Math3D.Cross3DPts(&a,&b,pNormal);
	Math3D.Normalize(pNormal,pNormal);
	///////////////
	return;	
}

void CDlg_LSy3::SetUpLocalm(pMATRIX pM)
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
	CString Nid;
	int index;
	/////////////////////////////////////////////
	CListBox* pWndCtrl = (CListBox*)GetDlgItem(IDD_SELECTLIST);
	CDrNode* pNode;
	///////////////
	pWndCtrl->GetText(0,Nid);	// Choose Ist one
    //////////
	if((index= pObjectMgr->GetObjectIndexfromKey(NODE,Nid,1)) <0)
	{
		AfxMessageBox("Internal Problem:Dlg_LSy3\nSetUpLocalm");
		return;
	}
	////////////	
	pNode = (CDrNode*)pDListMgr->GetObject(index);
	//////////////////////////////// scale etc
	LocR 	= *(pNode->GetLocalPos());			    
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
