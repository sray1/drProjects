
// dlg_rotp.cpp : implementation file
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
#include "dlg_Srot.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	5
/////////////////////////////////////////////////////////////////////////////
// CDlg_RotP_S dialog


CDlg_RotP_S::CDlg_RotP_S(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_RotP_S::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CDlg_RotP_S)
	m_dAng_2 	= 90.0;
	m_FromID 	= "";
	m_ToID 		= "";
	m_CurveID 	= "";
	m_Ratio 	= 1;
	m_nMesh 	= DEFAULT_UNIF;
	m_PatchID 	= "";
	m_bFromCN = FALSE;
	m_bToCN = FALSE;
	//}}AFX_DATA_INIT
	m_dAng_1 	= 0.0;
	m_bUnifOT 	= TRUE;
	/////////////////////// Memory
	m_pOSeg 	= NULL;
	///////////////////////
}

void CDlg_RotP_S::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_RotP_S)
	DDX_Text(pDX, IDC_ANG_END, m_dAng_2);
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromID);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToID);
	DDX_CBString(pDX, IDC_CURVE_ID, m_CurveID);
	DDX_Text(pDX, IDC_ELOUT_RATIO, m_Ratio);
	DDX_Text(pDX, IDC_ELOUT_SEG, m_nMesh);
	DDX_Text(pDX, IDC_PID, m_PatchID);
	DDX_Check(pDX, IDC_FROMNODECONTROL, m_bFromCN);
	DDX_Check(pDX, IDC_TONODECONTROL, m_bToCN);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_RotP_S, CDialog)
	//{{AFX_MSG_MAP(CDlg_RotP_S)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg_RotP_S message handlers
BOOL CDlg_RotP_S::OnInitDialog()
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
	pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	int nMax = pDListMgr->GetSpecificObjectCount(SOLID);
	if(nMax)
		FillListAllSolidIDs();   //  with Curves
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

void CDlg_RotP_S::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
	//	 Check first If Solid ID Selected
	if(m_PatchID == "")
   	{
   		AfxMessageBox("No Solid ID Selected\nPlease Select or Use Cancel");
   		return;
   	}
	//	 Check first If Patch Selected
	if(m_CurveID == "")
   	{
   		AfxMessageBox("No Patch Selected\nPlease Select or Use Cancel");
   		return;
   	}
	/////////////////////////////////////////////// Check
	double dAng = m_dAng_2;
	if(dAng >=360)
	{
		if(m_nMesh<3)
		{
			AfxMessageBox("Need atleast 3 Elements!");
			/////////////////
			CWnd* pWndCtrl = GetDlgItem(IDC_ELOUT_SEG);
			pWndCtrl->SetFocus();
			/////////////////////
			return;
		}
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

void CDlg_RotP_S::OnCancel()
{
	if(m_pOSeg)
	{
		delete [] m_pOSeg;
		m_pOSeg = NULL;
	}	
	////////////////////
	m_PatchID = "";
	////////////////////
	CDialog::OnCancel();
}

void CDlg_RotP_S::FillListAllSolidIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	//////////////////////////
	CString CID;
	
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

void CDlg_RotP_S::FillListAllPatchIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	///////////////////////////////////////////////
	CWnd* pWndCtrl;
	pWndCtrl = GetDlgItem(IDC_CURVE_ID);
	//////////////////////////
	CString CID;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(PATCH);//
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

void CDlg_RotP_S::FillListAllNodeIDs()
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

void CDlg_RotP_S::SetInfoForDataBase(CDrSolid* pDrObject)
{

	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*  pDListMgr;
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)SOLID);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
	pDrObject->SetSolidProc(SP_ROTATE);
	pDrObject->SetSolidType(SO_TENSOR);
	////////////////////////////////////////// SubType
	if(m_SubType == PS_TRIANGLE)
		pDrObject->SetSolSubType(SS_PENTA);	//
	else
	if(m_SubType == PS_QUADRILAT)
		pDrObject->SetSolSubType(SS_HEXA);	//
	//////////////////////////////////////////
	pDrObject->SetOrder_R(3);					// k = Quadratic for rotation
	pDrObject->SetCurveType_R(CP_CIRCLE);					// k = LINEAR for extrusion
	pDrObject->SetnDim_R(4); //Rational for use in circle and later in Solid 
//	pDrObject->SetClosed_R(FALSE); // done later
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
	/////////////////////////////////////////////////
	pDrObject->SetAng_1_R(m_dAng_1);
	pDrObject->SetAng_2_R(m_dAng_2);
	pDrObject->NumberOfElements(S_ROTATE,1/*int nElemType*/); // temp:1=LINE
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
	// if
	//		 Uniform:
	//			 	in MP_Rotate: make As Many Segment of Control Nodes
	//				as Close to 120 with total of m_nMesh Output segment
	//				in all of them i.e.,
	//				nSegs = #of Bezier Quadratic patches in T-direction
	//				saved as pDrObject->SetSegmentCount_R(nSegs)
	//				variable Angles are stored in m_pODis;
	//				m_pONum containing Number of Mesh for each Patch
	//		 NonUniform:
	//			 	in MP_Rotate: make m_nMesh Segments of Control Nodes
	//				with 1 Output segment in each, i.e.,
	//				m_nMesh many patch in T-direction
	//				nSegs = 1 = #of Bezier Quadratic patches in T-direction
	//				saved as pDrObject->SetSegmentCount_R(nSegs)
	//				Total Angle is stored in m_pODis[0];
	//				m_pONum[0] containing Number of Mesh for the Patch
	/////////////////////////////////////////////////////////////////////
	BOOL bClosed;
	if(m_dAng_1<0.)
		m_dAng_1 = 0.;
	if(m_dAng_2>360.)
		m_dAng_2 = 360.;
	double dAng = m_dAng_2 - m_dAng_1;
	//////////////////////////////////
	if(dAng == 360)
		bClosed = TRUE;
	else
		bClosed = FALSE;
	pDrObject->SetClosed_R(bClosed);
	////////////////////////////////
	int nSegs;
	//////////////////////////////////////////////////////// Uniform
	if(m_bUnifOT)						// Uniform
	{
		// Max Angle for each Patch Segment = 120;
		// for stability
		////////////////////////////////////////// <=120:One Patch 
		if(dAng<= 120)
		{
			nSegs = 1;
			//////////////////////////// Memory
			m_pOSeg = new int[nSegs];
			m_pODis = new double[nSegs];
			//////////////////////////// save
			m_pOSeg[0] = m_nMesh;
			m_pODis[0] = dAng;
			/////////////////////
		}
		////////////////////////////////////////// >120:Many Patches 
		else
		{
			int		nTimes,nMesh,nRem,i;
			double	dAngInc,dSegAng;
			////////////////
			dAngInc	= dAng/m_nMesh; // assume dAngInc ALWAYS <=120
			nTimes	= (int)(120./dAngInc);
			dSegAng	= nTimes * dAngInc;	// get biggest possible angle<=120
			nSegs	= (int)(dAng/dSegAng);
			nMesh	= nSegs*nTimes;
			nRem	= m_nMesh%nMesh;
			////
			if(nRem)
				nSegs++;
			//////////////////////////// Memory
			m_pOSeg = new int[nSegs];
			m_pODis = new double[nSegs];
			//////////////////////////// save
			for(i=0;i<nSegs;i++)
			{
				///////////////
				m_pOSeg[i] = nTimes;
				m_pODis[i] = dSegAng;
				/////////////////////
			}
			//////////////////////////// adjust  the Last one
			if(nRem)
			{
				int nSeg1 = nSegs -1;
				/////////////////////
				m_pOSeg[nSeg1] = m_nMesh	- nTimes * nSeg1;
				m_pODis[nSeg1] = dAng		- dSegAng* nSeg1;
				/////////////////////
			}
		}
	}
	//////////////////////////////////////////////////////// NonUniform
	else
	{
		nSegs = m_nMesh;
		//////////////////////////// Memory
		m_pOSeg = new int[nSegs];
		m_pODis = new double[nSegs];
		/////////////////////////////////////////////////////////
		// NOTE:	allows Unequal Extrusion
		//		# of Segments = n + 1			= nSegs 
		//		SPACEs between pts. are:
		//			x, x+a, x+2a, x+3a, ..., x+na
		//		with
		//			x = (2*theta)/(segs*(ratio+1))
		//			a = (x*(ratio-1))/(segs-1)
		//
		//////////////////////////////////////////////////////////
		double x	= (2 * dAng)/(nSegs * (m_Ratio + 1));
		double a	= (nSegs == 1)?0.:(x * (m_Ratio-1))/(nSegs-1);
		//////////////////////////// save
		int i;
		//////
		for (i=0;i<nSegs;i++)
		{
			m_pOSeg[i] = 1;	// one Element in each
			m_pODis[i] = x + i * a;
			///////////////////////
		}
	}
	/////////////////////
	pDrObject->SetMaxOutSeg_R(m_nMesh);		// Total Number of Output Segments
	pDrObject->SetMaxBezSegments_R(nSegs); 	// # of Patches in Rotation dirn
	//////////////////////////////////////////		 
	pDrObject->SetNum_tPointer_R(m_pOSeg);	// Number of Outputs for
											// each Curve Segment
	pDrObject->SetDis_AngPointer_R(m_pODis);// Number of Angles for
											// Bezier Control Pts. Generation
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
