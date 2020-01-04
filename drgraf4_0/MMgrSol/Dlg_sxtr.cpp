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
#include "dlg_Sxtr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	1
/////////////////////////////////////////////////////////////////////////////
// CDlg_Xtrd_S dialog


CDlg_Xtrd_S::CDlg_Xtrd_S(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Xtrd_S::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_Xtrd_S)
	m_FromID 	= "";
	m_ToID 		= "";
	m_dLen 		= 1.0;
	m_CurveID	= "";
	m_PatchID 	= "";
	m_nMesh 	= DEFAULT_UNIF;
	m_Ratio 	= 1;	//default
	m_bFromCN = FALSE;
	m_bToCN = FALSE;
	//}}AFX_DATA_INIT
	m_bUnifOT 		= TRUE;
	/////////////////////// Memory
	m_pOSeg 		= NULL;
	m_pODis			= NULL;
	//////////////////////////////////
	m_nType			= 1;	// default
	//////////////////////////////////
}

void CDlg_Xtrd_S::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Xtrd_S)
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromID);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToID);
	DDX_Text(pDX, IDC_LEN, m_dLen);
	DDV_MinMaxDouble(pDX, m_dLen, 1.e-003, 99999999.);
	DDX_CBString(pDX, IDC_CURVE_ID, m_CurveID);
	DDX_Text(pDX, IDC_PID, m_PatchID);
	DDX_Text(pDX, IDC_ELOUT_SEG, m_nMesh);
	DDV_MinMaxInt(pDX, m_nMesh, 1, 9999);
	DDX_Text(pDX, IDC_ELOUT_RATIO, m_Ratio);
	DDX_Check(pDX, IDC_FROMNODECONTROL, m_bFromCN);
	DDX_Check(pDX, IDC_TONODECONTROL, m_bToCN);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Xtrd_S, CDialog)
	//{{AFX_MSG_MAP(CDlg_Xtrd_S)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_Xtrd_S message handlers
BOOL CDlg_Xtrd_S::OnInitDialog()
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
	int nMax	 = pDListMgr->GetSpecificObjectCount(PATCH);
	if(nMax)
		FillListAllPatchIDs();   //  with Patches
	///////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	nMax		= pDListMgr->GetSpecificObjectCount(SOLID);
	if(nMax)
		FillListAllSolidIDs();   //  with Solids
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	nMax = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMax)
		FillListAllNodeIDs();   //  with Nodes
	/////////////////
	pWndCtrl = GetDlgItem(IDC_PID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CDlg_Xtrd_S::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	//	 Check first If Curve Selected
	if(m_CurveID == "")
   	{
   		AfxMessageBox("No Curve Selected\nPlease Select or Use Cancel");
   		return;
   	}
	/////////////////////////////////////////////////////////////////  ADD
	int nActiveIndex;
    CDrSolid* pAdd 	= (CDrSolid*)(pObjectMgr->AddToDataBase(nActiveIndex,SOLID));
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

void CDlg_Xtrd_S::OnCancel()
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

void CDlg_Xtrd_S::FillListAllSolidIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(SOLID);//
	if (nMaxCurves<=0)
		return;
    if(nMaxCurves)
    {
		CDrObject* 	pObject;			        
	
		POSITION pos = pDListMgr->GetFirstObjectPos();
		for (;pos !=NULL;)
		{
			pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
			if(pObject->GetObjectType() == SOLID)
			{ 
				CDrSolid* pCurve = (CDrSolid*)pObject;
	   			CString CID		 = pCurve->GetObjectID();
	   			/////////////////////////////////
				pWndCtrl = GetDlgItem(IDD_LIST);
	   		    ((CListBox*)(pWndCtrl))->AddString(CID);
			}	   		     
    	}
	} 
    
}    

void CDlg_Xtrd_S::FillListAllPatchIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	pWndCtrl = GetDlgItem(IDC_CURVE_ID);
	//////////////////////////
	CString CID;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(PATCH);//	Curve Profile
	if (nMaxCurves<=0)
		return;
	////////////////////////////////////////////////////////////////	
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == PATCH)
		{ 
			CDrPatch* pCurve = (CDrPatch*)pObject;
			if(pCurve->GetPatSubType() == m_SubType)		// make sure Right Stuff!!
			{
   				CString CID		 = pCurve->GetObjectID();
   				((CComboBox*)(pWndCtrl))->AddString(CID);
			}
		}	   		     
   	}
    
}    

void CDlg_Xtrd_S::FillListAllNodeIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(NODE);
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

void CDlg_Xtrd_S::SetInfoForDataBase(CDrSolid* pDrObject)
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
    pDrObject->SetObjectType((int)SOLID);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
	pDrObject->SetSolidProc(SP_EXTRUDE);
	pDrObject->SetSolidType(SO_TENSOR);
	////////////////////////////////////////// SubType
	if(m_SubType == PS_TRIANGLE)
		pDrObject->SetSolSubType(SS_PENTA);	//
	else
	if(m_SubType == PS_QUADRILAT)
		pDrObject->SetSolSubType(SS_HEXA);	// 
	//////////////////////////////////////////
	pDrObject->SetOrder_R(2);					// k = LINEAR for extrusion
	pDrObject->SetCurveType_R(CP_LINEAR);					// k = LINEAR for extrusion
	pDrObject->SetnDim_R(4); //Rational for use in circle and later in Solid 
	pDrObject->SetClosed_R(FALSE);					// k = LINEAR for extrusion
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	pDrObject->SetPatchID(m_CurveID,0);
	////////////////////////////////////////// Reciprocate
	pDrObject->GetPatchList()->RemoveAll();
	//////////////////////////////////////
	int index 	= pObjectMgr->GetObjectIndexfromKey(PATCH,m_CurveID,1);
	pDListMgr	= pObjectMgr->GetObjectList(PATCH);
	CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
	pDrPatch->GetSolidList()->InsertObject(pDrObject);
	pDrObject->GetPatchList()->InsertObject(pDrPatch);
	/////////////////////////////////////////////////////////////////// Type_1: fromID,ToID,dLen
	if(m_nType == 1)
	{
		pDrObject->SetExtruType_R(1);
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
		pDrNode->GetSolidList()->InsertObject(pDrObject);
		pDrObject->SetFromIDNode_R(pDrNode);
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
		pDrNode->GetSolidList()->InsertObject(pDrObject);
		pDrObject->SetToIDNode_R(pDrNode);
		/////////////////////////////////////////// strip Scale Factor (World Coord)
		pObjectMgr->SCtoDS(&m_dLen);
		m_dLen *= (dWorldBase/dMapFactor);
		///////////////////////////////
		pDrObject->SetLength_R(m_dLen);
	}
	else
	/////////////////////////////////////////////////////////////////// Type_2: wLen
	if(m_nType == 2)
	{
		pDrObject->SetExtruType_R(2);
		/////////////////////////////////////////// strip Scale Factor (World Coord)
		pObjectMgr->SCtoDS(&m_wLen.x);
		pObjectMgr->SCtoDS(&m_wLen.y);
		pObjectMgr->SCtoDS(&m_wLen.z);
		m_wLen.x *= (dWorldBase/dMapFactor);
		m_wLen.y *= (dWorldBase/dMapFactor);
		m_wLen.z *= (dWorldBase/dMapFactor);
		///////////////////////////////
		pDrObject->SetWorldLength_R(m_wLen);
	}
	////////////////////////////////////////////////////////////////////
	pDrObject->NumberOfElements(S_EXTRUDE,1/*int nElemType*/); // temp:1=LINE
	//////////////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetOutMethod_R(SO_HORNER);		// Output Method
	///////////////////////////////////////////////////////////// ReDistribute 
	if(m_Ratio == 1.0)
		m_bUnifOT = TRUE;
	else			
		m_bUnifOT = FALSE;
	//////////////////////	
	pDrObject->SetRatio_R(m_Ratio);					
	pDrObject->SetUniform_R(m_bUnifOT);		// Output Distribution:
	///////////////////////////////////////// save
	//			 	in Inter_C1: make One Segment of Control Nodes
	//				with m_nMesh Output segment in it, i.e.,
	//				1 Segment in T-direction
	/////////////////////////////////////////////////////////////////////
	int i;
	//////
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
	pDrObject->SetMaxOutSeg_R(m_nMesh);	// Number of Output Segments
	pDrObject->SetOutSegUnif_R(1); 	// for Old Compatibility per patch
	pDrObject->SetNum_tPointer_R(m_pOSeg);	// Number of Outputs for
												// each Curve Segment
	pDrObject->SetDis_tPointer_R(m_pODis);	// Number of Outputs for
												// each Curve Segment
	////////////////////////////////////////////// Total Evaluation Pts
	int nOut = m_nMesh + 1;
	///////////////////////
	pDrObject->SetMaxOutPts_R(nOut);
	pDrObject->SetOut_R(nOut);
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return;
	
} 
////////////////////////////////// end of module //////////////////////
