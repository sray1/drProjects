// dlg_Swip.cpp : implementation file Patch Sweep
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
///////////////////// ElemObjs
#include "Def_IGen.h"
#include "DrCurve.h"
////////////////////
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"
#include "MPatRsrc.h"
#include "MSTLRsrc.h"

#include "dlg_StLC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_StLC dialog


CDlg_StLC::CDlg_StLC(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_StLC::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_StLC)
	m_CID			= _T("");
	m_bIncrement	= FALSE;
	m_Orient		= _T("");
	m_dScale		= 0.0;
	m_dStep			= 0.0;
	m_dStart		= 0.0;
	//}}AFX_DATA_INIT
}

void CDlg_StLC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_StLC)
	DDX_CBString(pDX, IDC_CID, m_CID);
	DDX_Check(pDX, IDC_INCREMENT, m_bIncrement);
	DDX_CBString(pDX, IDC_ORIENT, m_Orient);
	DDX_Text(pDX, IDC_SCALE, m_dScale);
	DDX_Text(pDX, IDC_STEP, m_dStep);
	DDX_Text(pDX, IDC_START, m_dStart);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_StLC, CDialog)
	//{{AFX_MSG_MAP(CDlg_StLC)
	ON_BN_CLICKED(IDC_INCREMENT, OnIncrement)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_INCREMENT, OnIncrement)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_StLC message handlers

BOOL CDlg_StLC::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	EnableControls();
	//////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	int nMaxCurves 	 = pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMaxCurves)
		FillListAllCurveIDs();   //  with Curves
	///////////////////////////////////////////////////////////////////
 	((CComboBox*)GetDlgItem(IDC_ORIENT))->SetCurSel(1);//Backward=0/Forward=1
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return TRUE;  // return TRUE  unless you set the focus to a control
	
}

void CDlg_StLC::EnableControls() 
{
	//////////////////
	if(m_bIncrement)
	{			
		GetDlgItem(IDC_CID)->EnableWindow(FALSE);
		GetDlgItem(IDC_ORIENT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCALEHEAD)->SetWindowText("");
		GetDlgItem(IDC_SCALEHEAD)->EnableWindow(FALSE);

		GetDlgItem(IDC_LINEARHEAD)->SetWindowText("Linear");
		GetDlgItem(IDC_STEPHEAD)->SetWindowText("Step");
		GetDlgItem(IDC_STEPHEAD)->EnableWindow(TRUE);
		GetDlgItem(IDC_STARTHEAD)->SetWindowText("Staring Value");
		GetDlgItem(IDC_STARTHEAD)->EnableWindow(TRUE);
	}
	else
	{			
		GetDlgItem(IDC_CID)->EnableWindow(TRUE);
		GetDlgItem(IDC_ORIENT)->EnableWindow(TRUE);
		GetDlgItem(IDC_SCALEHEAD)->SetWindowText("Scale");
		GetDlgItem(IDC_SCALEHEAD)->EnableWindow(TRUE);

		GetDlgItem(IDC_LINEARHEAD)->SetWindowText("");
		GetDlgItem(IDC_STEPHEAD)->SetWindowText("");
		GetDlgItem(IDC_STEPHEAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_STARTHEAD)->SetWindowText("");
		GetDlgItem(IDC_STARTHEAD)->EnableWindow(FALSE);
	}

}

void CDlg_StLC::OnIncrement() 
{
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    /////////////////////////////////////////////// 
	m_bIncrement	= !m_bIncrement;
	/////////////////////////
	EnableControls();
    ////////////////////
	UpdateData(FALSE);			//To Screen(FALSE)    
    /////////////////////////////////////////////// 
}

void CDlg_StLC::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////////////////////////////////////////////////////////// 
	int index;
//	CDrCurve* pDrCurve;
	/////////////
	if(!m_bIncrement)
	{
		index			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID,1);
		if(index<0)
		{
			AfxMessageBox(
				"No Distribution Curve!\nPlease Select One from the List");
			return;
		}
	}
	/*												FOLLOWING TODO: in Calling Routine
													AFTER Matching Curves Selected
	///////////////////////////////
	if(m_bIncrement)
		m_CID_Twist = m_CID_Spine; 
	if(m_bIncRad)
		m_CID_Radius = m_CID_Spine; 
	////////////////////////////// nOut_S must be same
	index			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Spine,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Spine Curve!\nPlease Select One from the List");
		return;
	}
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	pDrCurve		= (CDrCurve*)(pDListMgr->GetObject(index));
	int nOutSpine	= pDrCurve->GetMaxOutPts_S();
	////////////////////////////////////////////////////////////////////////// RADIUS
	index 			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Radius,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Radius Curve!\nPlease Select One from the List");
		return;
	}
	pDrCurve		= (CDrCurve*)(pDListMgr->GetObject(index));
	int nOutRadius	= pDrCurve->GetMaxOutPts_S();
	if(nOutSpine != nOutRadius)
	{
		AfxMessageBox(
		"Element MisMatch!\nSpine:\nNumber of Elements = %d\nRadius:\nNumber of Elements = %d",
			nOutSpine,nOutRadius);
		return;
	}
*/
	///////////////
	CDialog::OnOK();
}

void CDlg_StLC::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_StLC::FillListAllCurveIDs()
{
	// Fill Only with right CATEGORY given by m_Category and same Output points;
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(CURVE);//
	if (nMaxCurves<=0)
		return;
	//////////////////////////////////////////////
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == CURVE)
		{ 
			CDrCurve* pCurve = (CDrCurve*)pObject;
			////////////////
			if(pCurve->GetCategory() != m_Category)
				continue;
			/////////////
			int nOutCat	= pCurve->GetMaxOutPts_S();
			if(nOutCat != m_pDrCurve->GetMaxOutPts_S())
				continue;
			/////////////
			CString CID		 = pCurve->GetObjectID();
			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CID);
			((CComboBox*)(pWndCtrl))->AddString(CID);
			/////////////////////////////////
		}	   		     
   	}
	///////
} 
    
/*
void CDlg_StLC::SetInfoForDataBase(CDrPatch* pDrObject)
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
	pDrObject->SetCurveID(m_CID_Radius,3);
	/////////////////////////////////
	CURVELATCH m_Latch[4];
	int i;
	for(i=0;i<4;i++)
		m_Latch[i] = CL_FORWARD;
	if(m_Orient_1 == "BACKWARD")
		m_Latch[0] = CL_BACKWARD;
	if(m_Orient_2 == "BACKWARD")
		m_Latch[1] = CL_BACKWARD;
	if(m_Orient_3 == "BACKWARD")
		m_Latch[2] = CL_BACKWARD;
	if(m_Orient_4 == "BACKWARD")
		m_Latch[3] = CL_BACKWARD;
	for(i=0;i<4;i++)
		pDrObject->SetCurveLatch(m_Latch[i],i);
	////////////////////////////////////////// Reciprocate
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	int index;
	CDrCurve* pDrCurve;
	index 		= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Xsec,1);
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	index 		= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Spine,1);
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	index 		= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Twist,1);
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	index 		= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_Radius,1);
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	////////////////////////////////////////// Reciprocate
	pDrObject->SetFromID_T(m_CNID_Anchor); //used for AnchorID
	CDrNode* pDrNode;
	index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_CNID_Anchor,1);
	pDListMgr	= pObjectMgr->GetObjectList(NODE);
	pDrNode = (CDrNode*)(pDListMgr->GetObject(index));
	pDrNode->GetPatchList()->InsertObject(pDrObject);
	///////////////////////////////////////////////// Twist/Scale Multiplier
	pDrObject->SetIncTwist_T(m_bIncrement);
	pDrObject->SetIncScale_T(m_bIncRad);
	pDrObject->SetTwistMult_T(m_TwistMult);
	pDrObject->SetScaleMult_T(m_RadiusMult);
	pDrObject->SetTwistStart_T(m_TwistStart);
	pDrObject->SetScaleStart_T(m_RadStart);
	pDrObject->NumberOfElements(P_DUCT,1//int nElemType); // temp:1=LINE
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
*/
////////////////////////////////// end of module //////////////////////
