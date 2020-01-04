// dlg_loft.cpp : implementation file
//

#include "stdafx.h"

#include "3DMath.h"

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
#include "dlg_CoP3.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	1

/////////////////////////////////////////////////////////////////////////////
// CDlg_CoP3 dialog


CDlg_CoP3::CDlg_CoP3(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CoP3::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_CoP3)
	m_PatchID 	= "";
	m_CID_1 	= "";
	m_CID_2 	= "";
	m_CID_3 	= "";
	m_TotEl_1 = 0;
	m_TotEl_2 = 0;
	m_TotEl_3 = 0;
	m_Orient_1 = _T("");
	m_Orient_2 = _T("");
	m_Orient_3 = _T("");
	//}}AFX_DATA_INIT
	m_bUnifOT 		= TRUE;
	/////////////////////// Memory
	m_pOSeg 		= NULL;
	///////////////////////
}

void CDlg_CoP3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CoP3)
	DDX_Text(pDX, IDC_PID, m_PatchID);
	DDX_CBString(pDX, IDC_CID_1, m_CID_1);
	DDX_CBString(pDX, IDC_CID_2, m_CID_2);
	DDX_CBString(pDX, IDC_CID_3, m_CID_3);
	DDX_Text(pDX, IDC_TOTEL_1, m_TotEl_1);
	DDX_Text(pDX, IDC_TOTEL_2, m_TotEl_2);
	DDX_Text(pDX, IDC_TOTEL_3, m_TotEl_3);
	DDX_CBString(pDX, IDC_ORIENT_1, m_Orient_1);
	DDX_CBString(pDX, IDC_ORIENT_2, m_Orient_2);
	DDX_CBString(pDX, IDC_ORIENT_3, m_Orient_3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_CoP3, CDialog)
	//{{AFX_MSG_MAP(CDlg_CoP3)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_CBN_SELCHANGE(IDC_CID_1, OnSelchangeCid1)
	ON_CBN_SELCHANGE(IDC_CID_2, OnSelchangeCid2)
	ON_CBN_SELCHANGE(IDC_CID_3, OnSelchangeCid3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_CoP3 message handlers
BOOL CDlg_CoP3::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	CWnd* pWndCtrl;
/*
	pWndCtrl = GetDlgItem(IDC_CID_1);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
	pWndCtrl = GetDlgItem(IDC_CID_2);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
*/
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	int nMaxPatches	 = pDListMgr->GetSpecificObjectCount(PATCH);
	if(nMaxPatches)
		FillListAllPatchIDs();   //  with Patches
	///////////////////////////////////////////////
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	int nMaxCurves 	 = pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMaxCurves)
		FillListAllCurveIDs();   //  with Curves
	///////////////////////////////////////////////////////////////////
 	((CComboBox*)GetDlgItem(IDC_ORIENT_1))->SetCurSel(1);//Backward=0/Forward=1
 	((CComboBox*)GetDlgItem(IDC_ORIENT_2))->SetCurSel(1);//Backward=0/Forward=1
 	((CComboBox*)GetDlgItem(IDC_ORIENT_3))->SetCurSel(1);//Backward=0/Forward=1
	/////////////////
	pWndCtrl = GetDlgItem(IDC_PID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_CoP3::OnSelchangeCid1() 
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
	pWndCtrl = GetDlgItem(IDC_CID_1);
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
		m_TotEl_1	= pDrCurve->GetMaxOutPts_S() - 1;
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_CoP3::OnSelchangeCid2() 
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
	pWndCtrl = GetDlgItem(IDC_CID_2);
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
		m_TotEl_2	= pDrCurve->GetMaxOutPts_S() - 1;
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_CoP3::OnSelchangeCid3() 
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
	pWndCtrl = GetDlgItem(IDC_CID_3);
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
		m_TotEl_3	= pDrCurve->GetMaxOutPts_S() - 1;
	}
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
}

void CDlg_CoP3::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	BOOL bClosed;
	int nOut1,nOut2;
	int index;
	CDrCurve* pDrCurve1;
	CDrCurve* pDrCurve2;
	CDrCurve* pDrCurve3;
    ///////////////////////////////////////////////////////////////////////// Check Compatibility
	////////////////////////////// nOut_S must be same
	index			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_1,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Valid Curve_1!\nPlease Select One from the List");
		return;
	}
	pDrCurve1	= (CDrCurve*)(pDListMgr->GetObject(index));
	nOut1		= pDrCurve1->GetMaxOutPts_S();
	bClosed		= pDrCurve1->IsClosed_S();
	////////////////////////////////////// All must be OPEN
	if(bClosed)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"%s Curve MUST BE OPEN",m_CID_1);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
	////////////////////////////////////////////////////////////////////////// Curve3
	index 			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_3,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Valid Curve_3!\nPlease Select One from the List");
		return;
	}
	pDrCurve3		= (CDrCurve*)(pDListMgr->GetObject(index));
	nOut2			= pDrCurve3->GetMaxOutPts_S();
	bClosed			= pDrCurve3->IsClosed_S();
	////////////////////////////////////// All must be OPEN
	if(bClosed)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"%s Curve MUST BE OPEN",m_CID_3);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
	////////////////////////////////////// ALL must have same nOut_S
	if(nOut1 != nOut2)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"Curve MisMatch!\nBOTH CURVES MUST HAVE SAME NUMBER OF ELEMENTS\nCURVE_1:\n\tNumber of Elements = %d\nCURVE_3:\n\tNumber of Elements = %d",
			nOut1-1,nOut2-1);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
	///////////////////////////////////////////////////////////////////////// Curve2
	index			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_2,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Valid Curve_2!\nPlease Select One from the List");
		return;
	}
	pDrCurve2		= (CDrCurve*)(pDListMgr->GetObject(index));
	nOut1			= pDrCurve2->GetMaxOutPts_S();
	bClosed			= pDrCurve2->IsClosed_S();
	////////////////////////////////////// All must be OPEN
	if(bClosed)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"%s Curve MUST BE OPEN",m_CID_2);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
	////////////////////////////////////// Both must have same nOut_S
	if(nOut1 != nOut2)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"Curve MisMatch!\nBOTH CURVES MUST HAVE SAME NUMBER OF ELEMENTS\nCURVE_2:\n\tNumber of Elements = %d\nCURVE_3:\n\tNumber of Elements = %d",
			nOut1-1,nOut2-1);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
	///////////////////////////////////////////////////////////////// Check CONNECTIVITY
	C3DMath Math3D;
	///////////////
	CDListMgr*	pINList;
	WORLD		LocalPosB1,LocalPosE1,LocalPosB2,LocalPosE2,
				LocalPosB3,LocalPosE3,
				LocalPosB;
	CDrNode*	pNode_Beg;
	CDrNode*	pNode_End;
	//////////////////////////////////////////////////////// Curve 1
 	pINList		= pDrCurve1->GetINodeList(); 
	pNode_Beg	= (CDrNode*)pINList->GetHead();
	pNode_End	= (CDrNode*)pINList->GetTail();
	////////////////////////////
	if(m_Orient_1 == "BACKWARD")
	{
		pNode_Beg	= (CDrNode*)pINList->GetTail();
		pNode_End	= (CDrNode*)pINList->GetHead();
	}
	/////////////
	LocalPosB1 = *(pNode_Beg->GetLocalPos());
	LocalPosE1 = *(pNode_End->GetLocalPos());
	//////////////////////////////////////////////////////// Curve 2
 	pINList		= pDrCurve2->GetINodeList(); 
	pNode_Beg	= (CDrNode*)pINList->GetHead();
	pNode_End	= (CDrNode*)pINList->GetTail();
	////////////////////////////
	if(m_Orient_2 == "BACKWARD")
	{
		pNode_Beg	= (CDrNode*)pINList->GetTail();
		pNode_End	= (CDrNode*)pINList->GetHead();
	}
	/////////////
	LocalPosB2 = *(pNode_Beg->GetLocalPos());
	LocalPosE2 = *(pNode_End->GetLocalPos());
	//////////////////////////////////////////////////////// Curve 3
 	pINList		= pDrCurve3->GetINodeList(); 
	pNode_Beg	= (CDrNode*)pINList->GetHead();
	pNode_End	= (CDrNode*)pINList->GetTail();
	////////////////////////////
	if(m_Orient_3 == "BACKWARD")
	{
		pNode_Beg	= (CDrNode*)pINList->GetTail();
		pNode_End	= (CDrNode*)pINList->GetHead();
	}
	/////////////
	LocalPosB3 = *(pNode_Beg->GetLocalPos());
	LocalPosE3 = *(pNode_End->GetLocalPos());
	//////////////////////////////////////////////////////// Do Check
	BOOL bDisJoint = TRUE;
	double dLen;
	//////////////////////
	Math3D.Sub3DPts(&LocalPosB1,&LocalPosE3,&LocalPosB);
	dLen = sqrt(fabs(Math3D.Len3DPts(&LocalPosB1)) * fabs(Math3D.Len3DPts(&LocalPosE3)) ); 
	if( fabs(Math3D.Len3DPts(&LocalPosB)/dLen) < .01)	// 1%
		bDisJoint = FALSE;
	if(bDisJoint)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"ComPatibility Problem!\nCurve_3(End) & Curve_1(Begin) DisJoint!\nCURVES MUST MEET");
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
	//////////////////////
	Math3D.Sub3DPts(&LocalPosB2,&LocalPosE1,&LocalPosB);
	dLen = sqrt(fabs(Math3D.Len3DPts(&LocalPosB2)) * fabs(Math3D.Len3DPts(&LocalPosE1)) ); 
	if( fabs(Math3D.Len3DPts(&LocalPosB)/dLen) < .01)	// 1%
		bDisJoint = FALSE;
	if(bDisJoint)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"ComPatibility Problem!\nCurve_1(End) & Curve_2(Begin) DisJoint!\nCURVES MUST MEET");
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
	//////////////////////
	Math3D.Sub3DPts(&LocalPosB3,&LocalPosE2,&LocalPosB);
	dLen = sqrt(fabs(Math3D.Len3DPts(&LocalPosB3)) * fabs(Math3D.Len3DPts(&LocalPosE2)) ); 
	if( fabs(Math3D.Len3DPts(&LocalPosB)/dLen) < .01)	// 1%
		bDisJoint = FALSE;
	if(bDisJoint)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		sprintf(buf,"ComPatibility Problem!\nCurve_2(End) & Curve_3(Begin) DisJoint!\nCURVES MUST MEET");
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
	/////////////////////////////////////////////////////////////////  VALID:ADD
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

void CDlg_CoP3::OnCancel()
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg_CoP3::FillListAllPatchIDs()
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

void CDlg_CoP3::FillListAllCurveIDs()
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
				pWndCtrl = GetDlgItem(IDC_CID_1);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDC_CID_2);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDC_CID_3);
	   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
	   		    /////////////////////////////////
			}	   		     
    	}
	} 
    
}    

void CDlg_CoP3::SetInfoForDataBase(CDrPatch* pDrObject)
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
	pDrObject->SetPatchProc(PP_COONSTRI);
	pDrObject->SetPatchType(PA_COONS);
	pDrObject->SetPatSubType(PS_TRIANGLE);
	pDrObject->SetOrder_S(2);							// k = LINEAR for Loft
	pDrObject->SetOrder_T(2);							// k = LINEAR for Loft
	pDrObject->SetCurveType_T(CP_LINEAR);				// k = LINEAR for Loft
	pDrObject->SetnDim_S(4); //Rational for use in circle and later in Solid 
	pDrObject->SetnDim_T(4); //Rational for use in circle and later in Solid 
	pDrObject->SetClosed_S(FALSE);						// k = LINEAR for Loft
	pDrObject->SetClosed_T(FALSE);						// k = LINEAR for Loft
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	pDrObject->SetCurveID(m_CID_1,0);
	pDrObject->SetCurveID(m_CID_2,1);
	pDrObject->SetCurveID(m_CID_3,2);
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
	////////////////////////////////////////////////////////////////////// Reciprocate
	pDrObject->GetCurveList()->RemoveAll();
	//////////////////////////////////////
	int index;
	CDrCurve* pDrCurve;
	index 		= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_1,1);
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	///////////////////////////////////////
	index 		= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_2,1);
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	///////////////////////////////////////
	index 		= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_3,1);
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	/////////////////////////////////////////////////
//	pDrObject->SetSegs(m_nSegs);
//	pDrObject->SetPatchType(PA_DUCT);
	pDrObject->NumberOfElements(P_DUCT,1/*int nElemType*/); // temp:1=LINE
	//////////////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetOutMethod_T(PA_HORNER);		// Output Method
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////// end of module //////////////////////
