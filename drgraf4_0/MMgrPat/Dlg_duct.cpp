// dlg_duct.cpp : implementation file
//

#include "stdafx.h"

#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// cards
#include "Def_Card.h"
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "CommRsrc.h"
#include "MPatRsrc.h"
#include "dlg_duct.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Duct dialog


CDlg_Duct::CDlg_Duct(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Duct::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Duct)
	m_CID_Spine		= "";
	m_CID_Twist		= "";
	m_CID_Xsec		= "";
	m_PatchID		= "";
	m_CNID_Anchor	= "";
	m_TwistMult		= 360.0;
	m_bIncrement	= TRUE;
	m_TwistStart	= 0.0;
	m_Orient_1 = _T("");
	m_Orient_2 = _T("");
	m_Orient_3 = _T("");
	m_bCNode = FALSE;
	//}}AFX_DATA_INIT
}

void CDlg_Duct::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Duct)
	DDX_CBString(pDX, IDC_CID_SPINE, m_CID_Spine);
	DDX_CBString(pDX, IDC_CID_TWIST, m_CID_Twist);
	DDX_CBString(pDX, IDC_CID_XSEC, m_CID_Xsec);
	DDX_Text(pDX, IDC_PID, m_PatchID);
	DDX_CBString(pDX, IDC_CNID_DANCHOR, m_CNID_Anchor);
	DDX_Text(pDX, IDC_TWISTMULT, m_TwistMult);
	DDV_MinMaxDouble(pDX, m_TwistMult, 0., 360.);
	DDX_Check(pDX, IDC_INCREMENT, m_bIncrement);
	DDX_Text(pDX, IDC_TWISTSTART, m_TwistStart);
	DDX_CBString(pDX, IDC_ORIENT_XSEC, m_Orient_1);
	DDX_CBString(pDX, IDC_ORIENT_SPINE, m_Orient_2);
	DDX_CBString(pDX, IDC_ORIENT_TWIST, m_Orient_3);
	DDX_Check(pDX, IDC_CONTROLNODE, m_bCNode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Duct, CDialog)
	//{{AFX_MSG_MAP(CDlg_Duct)
	ON_BN_CLICKED(IDC_INCREMENT, OnIncrement)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_INCREMENT, OnIncrement)
	ON_BN_CLICKED(IDC_CONTROLNODE, OnControlNode)
	ON_BN_DOUBLECLICKED(IDC_CONTROLNODE, OnControlNode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Duct message handlers

BOOL CDlg_Duct::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	CWnd* pWndCtrl;
	pWndCtrl = GetDlgItem(IDC_CID_XSEC);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
	pWndCtrl = GetDlgItem(IDC_CID_SPINE);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
	pWndCtrl = GetDlgItem(IDC_CID_TWIST);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
    /////////////////////////////////////////////// 
	if(m_bIncrement)
	{			
		pWndCtrl = GetDlgItem(IDC_CID_TWIST);
		pWndCtrl->EnableWindow(FALSE);
	}
	else
	{			
		pWndCtrl = GetDlgItem(IDC_CID_TWIST);
		pWndCtrl->EnableWindow(TRUE);
	}
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	int nMaxPatches	 = pDListMgr->GetSpecificObjectCount(PATCH);
	if(nMaxPatches)
		FillListAllPatchIDs();   //  with Patches
	///////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	int nMaxCurves 	 = pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMaxCurves)
		FillListAllCurveIDs();   //  with Curves
	///////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	int nMaxNodes 	 = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMaxNodes)
		FillListAllString();   // with All Nodes
	///////////////////////////////////////////////////////////////////
 	((CComboBox*)GetDlgItem(IDC_ORIENT_XSEC))->SetCurSel(1);//Backward=0/Forward=1
 	((CComboBox*)GetDlgItem(IDC_ORIENT_SPINE))->SetCurSel(1);//Backward=0/Forward=1
 	((CComboBox*)GetDlgItem(IDC_ORIENT_TWIST))->SetCurSel(1);//Backward=0/Forward=1
	/////////////////
	pWndCtrl = GetDlgItem(IDC_PID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
	
}

void CDlg_Duct::OnControlNode() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    /////////////////////////////////////////////// 
	m_bCNode = !m_bCNode;
    ////////////////////
	UpdateData(FALSE);			//To Screen(FALSE)    
    /////////////////////////////////////////////// 
	
}

void CDlg_Duct::OnIncrement() 
{
	CWnd* pWndCtrl;
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    /////////////////////////////////////////////// 
	m_bIncrement	= !m_bIncrement;
	////////////////////////////////
	if(m_bIncrement)
	{			
		pWndCtrl = GetDlgItem(IDC_CID_TWIST);
		pWndCtrl->EnableWindow(FALSE);
	}
	else
	{			
		pWndCtrl = GetDlgItem(IDC_CID_TWIST);
		pWndCtrl->EnableWindow(TRUE);
	}
    ////////////////////
	UpdateData(FALSE);			//To Screen(FALSE)    
    /////////////////////////////////////////////// 
}

void CDlg_Duct::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////////////////////////////////////////////////////////// Check T-dir Compatibility
	int index;
	CDrCurve* pDrCurve;
	/////////////
	index			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Xsec,1);
	if(index<0)
	{
		AfxMessageBox(
		"No CrossSection Curve!\nPlease Select One from the List");
		return;
	}
	///////////////////////////////
	if(m_bIncrement)
		m_CID_Twist = m_CID_Spine; 
	////////////////////////////// nOut_S must be same
	index			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Spine,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Spine Curve!\nPlease Select One from the List");
		return;
	}
	pDListMgr		= pObjectMgr->GetObjectList(CURVE);
	pDrCurve		= (CDrCurve*)(pDListMgr->GetObject(index));
	int nOutSpine	= pDrCurve->GetMaxOutPts_S();
	////////////////////////////////////////////////////////////////////////// TWIST
	index 			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Twist,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Twist Curve!\nPlease Select One from the List");
		return;
	}
	pDrCurve		= (CDrCurve*)(pDListMgr->GetObject(index));
	int nOutTwist	= pDrCurve->GetMaxOutPts_S();
	if(nOutSpine != nOutTwist)
	{
		AfxMessageBox(
		"Element MisMatch!\nSpine:\nNumber of Elements = %d\nTwist:\nNumber of Elements = %d",
			nOutSpine,nOutTwist);
		return;
	}
	/////////////////////////////////////////////////////////////////  ADD
	int nActiveIndex;
    CDrPatch* pAdd 	= (CDrPatch*)(pObjectMgr->AddToDataBase(nActiveIndex,PATCH));
    SetInfoForDataBase(pAdd);
	/////////////////////////////////////////////////////////
	// Temporarily: Hide from drawing by View which will otherwise
	// 					access The list 
	//	and find pDrCurve which IS NOT  YET INTERPOLATED
	/////////////////////////////////////////////////////////
	pAdd->SetShow(FALSE);
	///////////////
	CDialog::OnOK();
}

void CDlg_Duct::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_Duct::FillListAllString()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	//////////////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDC_CNID_DANCHOR);
	CString Nid;
	
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
				CDrNode* pNode	= (CDrNode*)pObject;
   				Nid				= (pNode->GetNodeCard())->id;
		    	((CComboBox*)(pWndCtrl))->AddString(Nid);
			}			    
    	}
	} 
    
}

void CDlg_Duct::FillListAllPatchIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(PATCH);//
	if (nMaxCurves<=0)
		return;
    if(nMaxCurves)
    {
		CDrObject* 	pObject;			        
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if(pObject->GetObjectType() == PATCH)
			{ 
				CDrCurve* pCurve = (CDrCurve*)pObject;
	   			CString CID		 = pCurve->GetObjectID();
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDD_LIST);
	   		    ((CListBox*)(pWndCtrl))->AddString(CID);
			}	   		     
    	}
	} 
    
}    

void CDlg_Duct::FillListAllCurveIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(CURVE);//
	if (nMaxCurves<=0)
		return;
    if(nMaxCurves)
    {
		CDrObject* 	pObject;			        
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if(pObject->GetObjectType() == CURVE)
			{ 
				CDrCurve* pCurve = (CDrCurve*)pObject;
	   			CString CID		 = pCurve->GetObjectID();
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDC_CID_XSEC);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDC_CID_SPINE);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
	   		    /////////////////////////////////
				pWndCtrl = GetDlgItem(IDC_CID_TWIST);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
	   		    /////////////////////////////////
			}	   		     
    	}
	} 
    
}    

void CDlg_Duct::SetInfoForDataBase(CDrPatch* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*  pDListMgr;
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)PATCH);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_DADDY);          // globals
	pDrObject->SetPatchProc(PP_DUCT);
	pDrObject->SetPatchType(PA_TENSOR);
	pDrObject->SetPatSubType(PS_QUADRILAT);
	////////////////////////////////////////////////////////////
	pDrObject->SetOutMethod_T(PA_HORNER);		// Output Method
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	pDrObject->SetCurveID(m_CID_Xsec,0);
	pDrObject->SetCurveID(m_CID_Spine,1);
	pDrObject->SetCurveID(m_CID_Twist,2);
	/////////////////////////////////
	CURVELATCH m_Latch[3];
	int i;
	for(i=0;i<3;i++)
		m_Latch[i] = CL_FORWARD;
	if(m_Orient_1 == "BACKWARD")
		m_Latch[0] = CL_BACKWARD;
	if(m_Orient_2 == "BACKWARD")
		m_Latch[1] = CL_BACKWARD;
	if(m_Orient_3 == "BACKWARD")
		m_Latch[2] = CL_BACKWARD;
	for(i=0;i<3;i++)
		pDrObject->SetCurveLatch(m_Latch[i],i);
	//////////////////////////////////////////////////////////////////// Reciprocate
	pDrObject->GetCurveList()->RemoveAll();
	//////////////////////////////////////
	int index;
	CDrCurve* pDrCurve;
	index 		= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Xsec,1);
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	///////////////////////////////////////
	index 		= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Spine,1);
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	///////////////////////////////////////
	index 		= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Twist,1);
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	////////////////////////////////////////// Reciprocate
	CDrNode* pDrNode;
	if(m_bCNode)
	{
		index	= pObjectMgr->GetObjectIndexfromKey(CNODE,m_CNID_Anchor,1);
		pDListMgr	= pObjectMgr->GetObjectList(CNODE);
	}
	else
	{
		index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_CNID_Anchor,1);
		pDListMgr	= pObjectMgr->GetObjectList(NODE);
	}
	///
	pDrNode = (CDrNode*)(pDListMgr->GetObject(index));
	pDrNode->GetPatchList()->InsertObject(pDrObject);
	pDrObject->SetFromIDNode_T(pDrNode); //used for AnchorID
	///////////////////////////////////////////////// Twist Multiplier
	pDrObject->SetIncTwist_T(m_bIncrement);
	pDrObject->SetTwistMult_T(m_TwistMult);
	pDrObject->SetTwistStart_T(m_TwistStart);
	pDrObject->NumberOfElements(P_DUCT,1/*int nElemType*/); // temp:1=LINE
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////// end of module //////////////////////
