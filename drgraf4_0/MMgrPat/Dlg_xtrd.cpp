// dlg_xtrd.cpp : implementation file
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
#include "Def_Elem.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
#include "precison.h"
#include "mapfacto.h"
////////////////////
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"
#include "MPatRsrc.h"
#include "dlg_xtrd.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	1
/////////////////////////////////////////////////////////////////////////////
// CDlg_Xtrd dialog


CDlg_Xtrd::CDlg_Xtrd(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Xtrd::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Xtrd)
	m_FromID 	= "";
	m_ToID 		= "";
	m_dLen 		= 1.0;
	m_CurveID	= "";
	m_PatchID 	= "";
	m_nMesh 	= DEFAULT_UNIF;
	m_Ratio 	= 1;	//default
	m_Orient_1 = _T("");
	m_bFromCN = FALSE;
	m_bToCN = FALSE;
	//}}AFX_DATA_INIT
	m_bUnifOT 		= TRUE;
	/////////////////////// Memory
	m_pOSeg 		= NULL;
	m_pODis 		= NULL;
	//////////////////////////////////
	m_nType			= 1;	// default
	//////////////////////////////////
}

void CDlg_Xtrd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Xtrd)
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromID);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToID);
	DDX_Text(pDX, IDC_LEN, m_dLen);
	DDV_MinMaxDouble(pDX, m_dLen, 1.e-003, 99999999.);
	DDX_CBString(pDX, IDC_CURVE_ID, m_CurveID);
	DDX_Text(pDX, IDC_PID, m_PatchID);
	DDX_Text(pDX, IDC_ELOUT_SEG, m_nMesh);
	DDV_MinMaxInt(pDX, m_nMesh, 1, 9999);
	DDX_Text(pDX, IDC_ELOUT_RATIO, m_Ratio);
	DDX_CBString(pDX, IDC_ORIENT, m_Orient_1);
	DDX_Check(pDX, IDC_FROMNODECONTROL, m_bFromCN);
	DDX_Check(pDX, IDC_TONODECONTROL, m_bToCN);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Xtrd, CDialog)
	//{{AFX_MSG_MAP(CDlg_Xtrd)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Xtrd message handlers
BOOL CDlg_Xtrd::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	buttonOK.SubclassDlgItem(IDOK,this); 
	buttonCancel.SubclassDlgItem(IDCANCEL,this);
	buttonOK.SizeToContent();
	buttonCancel.SizeToContent();
	///////////////////////////////////////////////////////////////////
	CWnd* pWndCtrl;
	pWndCtrl = GetDlgItem(IDC_CURVE_ID);
//	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
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
	int nMax = pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMax)
		FillListAllCurveIDs();   //  with Curves
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	nMax = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMax)
		FillListAllNodeIDs();   //  with Nodes
	///////////////////////////////////////////////////////////////////
 	((CComboBox*)GetDlgItem(IDC_ORIENT))->SetCurSel(1);//Backward=0/Forward=1
	/////////////////
	pWndCtrl = GetDlgItem(IDC_PID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Xtrd::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	//	 Check first If Patch ID Selected
	if(m_PatchID == "")
   	{
   		AfxMessageBox("No Patch ID Selected\nPlease Select or Use Cancel");
   		return;
   	}
	//	 Check first If Curve Selected
	if(m_CurveID == "")
   	{
   		AfxMessageBox("No Curve to Extrude\nPlease Select or Use Cancel");
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

void CDlg_Xtrd::OnCancel()
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

void CDlg_Xtrd::FillListAllPatchIDs()
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

void CDlg_Xtrd::FillListAllCurveIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	pWndCtrl = GetDlgItem(IDC_CURVE_ID);
	//////////////////////////
	CString CID;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(CURVE);//	Curve Profile
	if (nMaxCurves<=0)
		return;
	////////////////////////////////////////////////////////////////	
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == CURVE)
		{ 
			CDrCurve* pCurve = (CDrCurve*)pObject;
   			CString CID		 = pCurve->GetObjectID();
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
		}	   		     
   	}
    
}    

void CDlg_Xtrd::FillListAllNodeIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	int nMaxNodes = pDListMgr->GetSpecificObjectCount(NODE);//
	if (nMaxNodes<=0)
		return;
	////////////////////////////////////////////////////////////	
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == NODE)
		{ 
			CDrNode* pCurve = (CDrNode*)pObject;
   			CString CID		= pCurve->GetNodeCard()->id;
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CNODE_FROM);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   			/////////////////////////////////
			pWndCtrl = GetDlgItem(IDC_CNODE_TO);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
   		    /////////////////////////////////
		}	   		     
   	}
    
}    

void CDlg_Xtrd::SetInfoForDataBase(CDrPatch* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*  pDListMgr;
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER);
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	/////////////////////////////////////////////////////////////	
    pDrObject->SetObjectType((int)PATCH);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_DADDY);          // globals
	pDrObject->SetPatchProc(PP_EXTRUDE);
	pDrObject->SetPatchType(PA_TENSOR);
	pDrObject->SetPatSubType(PS_QUADRILAT);
	pDrObject->SetOrder_T(2);					// k = LINEAR for extrusion
	pDrObject->SetCurveType_T(CP_LINEAR);					// k = LINEAR for extrusion
	pDrObject->SetnDim_T(4); //Rational for use in circle and later in Solid 
	pDrObject->SetClosed_T(FALSE);					// k = LINEAR for extrusion
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	pDrObject->SetCurveID(m_CurveID,0);
	/////////////////////////////////
	CURVELATCH m_Latch[1];
	int i;
	for(i=0;i<1;i++)
		m_Latch[i] = CL_FORWARD;
	if(m_Orient_1 == "BACKWARD")
		m_Latch[0] = CL_BACKWARD;
	for(i=0;i<1;i++)
		pDrObject->SetCurveLatch(m_Latch[i],i);
	/////////////////////////////////////////////////////////////////// Reciprocate
	pDrObject->GetCurveList()->RemoveAll();
	//////////////////////////////////////
	int index 	= pObjectMgr->GetObjectIndexfromKey(CURVE,m_CurveID,1);
	pDListMgr	= pObjectMgr->GetObjectList(CURVE);
	CDrCurve* pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	pDrCurve->GetPatchList()->InsertObject(pDrObject);
	pDrObject->GetCurveList()->InsertObject(pDrCurve);
	/////////////////////////////////////////////////////////////////// Type_1: fromID,ToID,dLen
	if(m_nType == 1)
	{
		pDrObject->SetExtruType_T(1);
		////////////////////////////////////////// Reciprocate
		CDrNode* pDrNode;
		if(m_bFromCN)
		{
			index	= pObjectMgr->GetObjectIndexfromKey(CNODE,m_FromID,1);
			pDListMgr	= pObjectMgr->GetObjectList(CNODE);
		}
		else
		{
			index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_FromID,1);
			pDListMgr	= pObjectMgr->GetObjectList(NODE);
		}
		///
		pDrNode = (CDrNode*)(pDListMgr->GetObject(index));
		pDrNode->GetPatchList()->InsertObject(pDrObject);
		pDrObject->SetFromIDNode_T(pDrNode);
		////////////////////
		if(m_bToCN)
		{
			index	= pObjectMgr->GetObjectIndexfromKey(CNODE,m_ToID,1);
			pDListMgr	= pObjectMgr->GetObjectList(CNODE);
		}
		else
		{
			index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_ToID,1);
			pDListMgr	= pObjectMgr->GetObjectList(NODE);
		}
		///
		pDrNode = (CDrNode*)(pDListMgr->GetObject(index));
		pDrNode->GetPatchList()->InsertObject(pDrObject);
		pDrObject->SetToIDNode_T(pDrNode);
		/////////////////////////////////////////// strip Scale Factor (World Coord)
		pObjectMgr->SCtoDS(&m_dLen);
		m_dLen *= (dWorldBase/dMapFactor);
		///////////////////////////////
		pDrObject->SetLength_T(m_dLen);
	}
	else
	/////////////////////////////////////////////////////////////////// Type_2: wLen
	if(m_nType == 2)
	{
		pDrObject->SetExtruType_T(2);
		/////////////////////////////////////////// strip Scale Factor (World Coord)
		pObjectMgr->SCtoDS(&m_wLen.x);
		pObjectMgr->SCtoDS(&m_wLen.y);
		pObjectMgr->SCtoDS(&m_wLen.z);
		m_wLen.x *= (dWorldBase/dMapFactor);
		m_wLen.y *= (dWorldBase/dMapFactor);
		m_wLen.z *= (dWorldBase/dMapFactor);
		///////////////////////////////
		pDrObject->SetWorldLength_T(m_wLen);
	}
	////////////////////////////////////////////////////////////////////
	pDrObject->NumberOfElements(P_EXTRUDE,1/*int nElemType*/); // temp:1=LINE
//	pDrObject->SetSegs(m_nSegs);
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
	pDrObject->SetSegmentCount_T(1); 	// for Old Compatibility per patch
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
