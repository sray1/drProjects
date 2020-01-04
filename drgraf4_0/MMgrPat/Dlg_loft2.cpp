// dlg_loft.cpp : implementation file
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
#include "MCurRsrc.h"
#include "dlg_loft2.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	1

/////////////////////////////////////////////////////////////////////////////
// CDlg_Loft2 dialog


CDlg_Loft2::CDlg_Loft2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Loft2::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Loft2)
	m_PatchID 	= "";
	m_nMesh 	= DEFAULT_UNIF;
	m_Ratio 	= 1;	//default
	m_CID_1 	= "";
	m_CID_2 	= "";
	m_Orient_1 = _T("");
	m_Orient_2 = _T("");
	//}}AFX_DATA_INIT
	m_bUnifOT 		= TRUE;
	/////////////////////// Memory
	m_pOSeg 		= NULL;
	m_pODis 		= NULL;
	///////////////////////
}

void CDlg_Loft2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Loft2)
	DDX_Text(pDX, IDC_PID, m_PatchID);
	DDX_Text(pDX, IDC_ELOUT_SEG, m_nMesh);
	DDV_MinMaxInt(pDX, m_nMesh, 1, 9999);
	DDX_Text(pDX, IDC_ELOUT_RATIO, m_Ratio);
	DDX_CBString(pDX, IDC_CID_1, m_CID_1);
	DDX_CBString(pDX, IDC_CID_2, m_CID_2);
	DDX_CBString(pDX, IDC_ORIENT_1, m_Orient_1);
	DDX_CBString(pDX, IDC_ORIENT_2, m_Orient_2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Loft2, CDialog)
	//{{AFX_MSG_MAP(CDlg_Loft2)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Loft2 message handlers
BOOL CDlg_Loft2::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	CWnd* pWndCtrl;
	pWndCtrl = GetDlgItem(IDC_CID_1);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
	pWndCtrl = GetDlgItem(IDC_CID_2);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
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
	/////////////////
	pWndCtrl = GetDlgItem(IDC_PID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Loft2::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
    ///////////////////////////////////////////////////////////////////////// Check T-dir Compatibility
	int index;
	CDrCurve* pDrCurve;
	////////////////////////////// nOut_S must be same
	index			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_1,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Beginning Curve!\nPlease Select One from the List");
		return;
	}
	pDListMgr		= pObjectMgr->GetObjectList(CURVE);
	pDrCurve		= (CDrCurve*)(pDListMgr->GetObject(index));
	int nOut1		= pDrCurve->GetMaxOutPts_S();
	BOOL bClosed1	= pDrCurve->IsClosed_S();
	////////////////////////////////////////////////////////////////////////// Curve2
	index 			= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CID_2,1);
	if(index<0)
	{
		AfxMessageBox(
		"No Ending Curve!\nPlease Select One from the List");
		return;
	}
	pDListMgr		= pObjectMgr->GetObjectList(CURVE);
	pDrCurve		= (CDrCurve*)(pDListMgr->GetObject(index));
	int nOut2		= pDrCurve->GetMaxOutPts_S();
	BOOL bClosed2	= pDrCurve->IsClosed_S();
	////////////////////////////////////// Both must have same nOut_S
	if(nOut1 != nOut2)
	{
		CString str;
		LPTSTR buf = str.GetBuffer( 200 );
		wsprintf(buf,"Curve MisMatch!\nBOTH CURVES MUST HAVE SAME NUMBER OF ELEMENTS\nBeginning:\n\tNumber of Elements = %d\nEnding:\n\tNumber of Elements = %d",
			nOut1,nOut2);
		AfxMessageBox(str);
		str.ReleaseBuffer();
		return;
	}
	////////////////////////////////////// Both must be closed or open
	if(bClosed1 != bClosed2)
	{
		CString str,str1,str2;
		str1 = (bClosed1)?"CLOSED":"OPEN";
		str2 = (bClosed2)?"CLOSED":"OPEN";
		LPTSTR buf = str.GetBuffer( 200 );
		wsprintf(buf,"Curve MisMatch!\nBOTH CURVES SHOULD BE EITHER OPEN OR CLOSED\nBeginning: %s\nEnding: %s",
			str1,str2);
		AfxMessageBox(str);
		str.ReleaseBuffer();
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

void CDlg_Loft2::OnCancel()
{
	if(m_pOSeg)
	{
		delete [] m_pOSeg;
		m_pOSeg = NULL;
	}	
	if(m_pODis)
	{
		delete [] m_pODis;
		m_pODis = NULL;
	}	
	////////////////////
	m_PatchID = "";
	////////////////////
	CDialog::OnCancel();
}

void CDlg_Loft2::FillListAllPatchIDs()
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

void CDlg_Loft2::FillListAllCurveIDs()
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
			}	   		     
    	}
	} 
    
}    

void CDlg_Loft2::SetInfoForDataBase(CDrPatch* pDrObject)
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
	pDrObject->SetPatchProc(PP_LOFT2);
	pDrObject->SetPatchType(PA_TENSOR);
	pDrObject->SetPatSubType(PS_QUADRILAT);
	pDrObject->SetOrder_T(2);					// k = LINEAR for extrusion
	pDrObject->SetCurveType_T(CP_LINEAR);					// k = LINEAR for extrusion
	pDrObject->SetnDim_T(4); //Rational for use in circle and later in Solid 
	pDrObject->SetClosed_T(FALSE);					// k = LINEAR for extrusion
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	pDrObject->SetCurveID(m_CID_1,0);
	pDrObject->SetCurveID(m_CID_2,1);
	/////////////////////////////////
	CURVELATCH m_Latch[2];
	int i;
	for(i=0;i<2;i++)
		m_Latch[i] = CL_FORWARD;
	if(m_Orient_1 == "BACKWARD")
		m_Latch[0] = CL_BACKWARD;
	if(m_Orient_2 == "BACKWARD")
		m_Latch[1] = CL_BACKWARD;
	for(i=0;i<2;i++)
		pDrObject->SetCurveLatch(m_Latch[i],i);
	///////////////////////////////////////////////////////////////// Reciprocate
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
	/////////////////////////////////////////////////
//	pDrObject->SetSegs(m_nSegs);
//	pDrObject->SetPatchType(PA_DUCT);
	pDrObject->NumberOfElements(P_DUCT,1/*int nElemType*/); // temp:1=LINE
	//////////////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetOutMethod_T(PA_HORNER);		// Output Method
	///////////////////////////////////////////////////////////// ReDistribute 
	if(m_Ratio == 1.0)
		m_bUnifOT = TRUE;
	else			
		m_bUnifOT = FALSE;
	//////////////////////	
	pDrObject->SetRatio_T(m_Ratio);					
	pDrObject->SetUniform_T(m_bUnifOT);		// Output Distribution:
	///////////////////////////////////////// save
	//			 	in Inter_C1: make One Segment of Control Nodes
	//				with m_nMesh Output segment in it, i.e.,
	//				1 Segment in T-direction
	/////////////////////////////////////////////////////////////////////
	m_pOSeg = new int[1];
	m_pODis = new double[m_nMesh+1];
	/////////////////////
	m_pOSeg[0] = m_nMesh;
	/////////////////////
	if(m_bUnifOT)			// Uniform and OK
	{
		///////////////////////////////
		double delt;
		delt	= 1.0/m_nMesh;
		////////////////
		m_pODis[0] = 0.;
		////////////////
		for (i=1;i<=m_nMesh;i++)
		{
			m_pODis[i] = m_pODis[i-1] + delt;
		}
		/////////////////////
	}
	else								// NonUniform
	{
		/////////////////////////////////////////////////////////
		// NOTE:	allows Unequal Generation
		//		# of Segments = n + 1			= nSegs 
		//		SPACEs between pts. are:
		//			x, x+a, x+2a, x+3a, ..., x+na
		//		with
		//			x = 2/(segs*(ratio+1))
		//			a = (x*(ratio-1))/(segs-1)
		//
		//////////////////////////////////////////////////////////
		double x	= 2./(m_nMesh * (m_Ratio + 1));
		double a	= (m_nMesh == 1)?0.:(x * (m_Ratio-1))/(m_nMesh-1);
		//////////////////////////// save
		int i;
		//////
		m_pODis[0] = 0.;
		////////////////
		for (i=0;i<m_nMesh;i++)
		{
			///////////////////
			m_pODis[i+1] = m_pODis[i] + x + i * a;
			///////////////////
		}
	}
	//////////////////////////////////////////		 
	pDrObject->SetMaxOutSeg_T(m_nMesh);	// Number of Output Segments
//	pDrObject->SetSegmentCount_T(1); 	// for Old Compatibility per patch
	pDrObject->SetNum_tPointer_T(m_pOSeg);	// Number of Outputs for
												// each Curve Segment
	pDrObject->SetDis_tPointer_T(m_pODis);	// Number of Outputs for
												// each Curve Segment
	////////////////////////////////////////////// Total Evaluation Pts
	int nOut = m_nMesh + 1;
	///////////////////////
	pDrObject->SetMaxOutPts_T(nOut);
	pDrObject->SetOut_T(nOut);
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////// end of module //////////////////////
