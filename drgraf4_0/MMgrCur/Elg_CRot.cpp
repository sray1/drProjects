// Dlg_Circ.cpp : implementation file
//

#include "stdafx.h"

#include "3DMath.h"
#include "XForm.h"

//#include "EDlgMgr.h"

#include "Def_Lims.h"
#include "Def_Objs.h"
#include "Def_CuPS.h"
/////////////////////
#include "drgraf.h"
#include "drgradoc.h" 
/////////////////////
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// IGenObjs
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
////////////////////
#include "MNodRsrc.h"
#include "Elg_CRot.h"	// Circle Interpolate Rational: Rightbutton

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////
#define	new DEBUG_NEW
////////////////////////////////
#define DEFAULT_UNIF	5
/////////////////////////////////////////////////////////////////////////////
// CElg_CRot dialog


CElg_CRot::CElg_CRot(CWnd* pParent /*=NULL*/)
	: CDialog(CElg_CRot::IDD, pParent)
{
	buttonOK.LoadBitmaps("Image1Up","Image1Down","Image1Focus");
	buttonCancel.LoadBitmaps("Image2Up","Image2Down","Image2Focus");
	//{{AFX_DATA_INIT(CElg_CRot)
	m_dAng 		= 90.0;
	m_FromID 	= "";
	m_ToID 		= "";
	m_NodeID 	= "";
	m_Ratio 	= 1;
	m_nMesh 	= DEFAULT_UNIF;
	m_CurveID 	= "";
	m_SegAngle = 120;
	m_bAutoSeg = TRUE;
	//}}AFX_DATA_INIT
//	m_SegAngle 	= 120;		// Default
	m_bUnifOT 	= TRUE;
	/////////////////////// Memory
	m_pOSeg 	= NULL;
	///////////////////////
}

void CElg_CRot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElg_CRot)
	DDX_Text(pDX, IDC_ANG_END, m_dAng);
	DDX_CBString(pDX, IDC_CNODE_FROM, m_FromID);
	DDX_CBString(pDX, IDC_CNODE_TO, m_ToID);
	DDX_CBString(pDX, IDC_CURVE_ID, m_NodeID);
	DDX_Text(pDX, IDC_ELOUT_RATIO, m_Ratio);
	DDX_Text(pDX, IDC_ELOUT_SEG, m_nMesh);
	DDX_Text(pDX, IDC_CID, m_CurveID);
	DDX_Text(pDX, IDC_SEGANGLE, m_SegAngle);
	DDV_MinMaxInt(pDX, m_SegAngle, 45, 120);
	DDX_Check(pDX, IDC_AUTOSEG, m_bAutoSeg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CElg_CRot, CDialog)
	//{{AFX_MSG_MAP(CElg_CRot)
	ON_BN_DOUBLECLICKED(IDOK, OnOK)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_BN_DOUBLECLICKED(IDC_AUTOSEG, OnAutoSeg)
	ON_EN_KILLFOCUS(IDC_SEGANGLE, OnKillfocusSegAngle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CElg_CRot message handlers
BOOL CElg_CRot::OnInitDialog()
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
/*	
	pWndCtrl = GetDlgItem(IDC_CNODE_FROM);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN); 
	pWndCtrl = GetDlgItem(IDC_CNODE_TO);
	((CComboBox*)pWndCtrl)->LimitText(ID_LEN);
*/
	///////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr;
	///////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	int nMax = pDListMgr->GetSpecificObjectCount(CURVE);
	if(nMax)
		FillListAllCurveIDs();   //  with Curves
	pDListMgr 	= pObjectMgr->GetObjectList(NODE);
	nMax = pDListMgr->GetSpecificObjectCount(NODE);
	if(nMax)
		FillListAllNodeIDs();   //  with Nodes
	/////////////////
	pWndCtrl = GetDlgItem(IDC_CID);
	pWndCtrl->SetFocus();
    ////////////////////
	UpdateData(FALSE);			//Update Screen(FALSE)    
    ///////////////////	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CElg_CRot::OnAutoSeg()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
	if(m_bAutoSeg)
		GetDlgItem(IDC_SEGANGLE)->EnableWindow(FALSE);
	else	
		GetDlgItem(IDC_SEGANGLE)->EnableWindow(TRUE);
    ////////////////////
	UpdateData(FALSE);		    //TO Screen(FALSE)    
    ///////////////////	
}

void CElg_CRot::OnKillfocusSegAngle()
{
    ////////////////////
	UpdateData(TRUE);		    //FROM Screen(TRUE)    
    ///////////////////	
}

void CElg_CRot::OnOK()
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
    ////////////////////
	UpdateData(TRUE);			//FROM Screen(TRUE)    
    ///////////////////	
    /////////////////////////////////////////////// Curve ID
   	if("" == m_CurveID)
   	{
   		AfxMessageBox("Please Select a Circle ID");
   		return;
   	}
	/////////////////////////////////////////////// Check
	double dAng = m_dAng;
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
/*
	else
	{
		if(m_nMesh<2)
		AfxMessageBox("Need atleast 2 Elements!");
		/////////////////
		CWnd* pWndCtrl = GetDlgItem(IDC_ELOUT_SEG);
		pWndCtrl->SetFocus();
		/////////////////////
		return;
	}
*/
	/////////////////////////////////////////////////////////////////  ADD
	int nActiveIndex;
    CDrCurve* pAdd 	= (CDrCurve*)(pObjectMgr->AddToDataBase(nActiveIndex,CURVE));
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

void CElg_CRot::OnCancel()
{
	if(m_pOSeg)
	{
		delete [] m_pOSeg;
		m_pOSeg = NULL;
	}	
	////////////////////
	m_CurveID = "";
	////////////////////
	CDialog::OnCancel();
}

void CElg_CRot::FillListAllCurveIDs()
{
			 
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	///////////////////////////////////////////////
	CWnd* pWndCtrl = GetDlgItem(IDD_LIST);
	//////////////////////////
	CString CID;
	
	int nMaxCurves = pDListMgr->GetSpecificObjectCount(CURVE);//
	if (nMaxCurves<=0)
		return;
    //////////////////////////////////////////////////////////	
	CDrObject* 	pObject;			        
	
	POSITION pos = pDListMgr->GetFirstObjectPos();
	for (;pos !=NULL;)
	{
		pObject = (CDrObject*)pDListMgr->GetNextObject( pos);
		if(pObject->GetObjectType() == CURVE)
		{ 
			CDrCurve* pCurve = (CDrCurve*)pObject;
   			CString CID		 = pCurve->GetObjectID();
   		    ((CListBox*)(pWndCtrl))->AddString(CID);
		}	   		     
   	}
   	///////////////////////////////////
   	pWndCtrl->EnableWindow(FALSE);		// Always Disabled
   	////////
    
}    

void CElg_CRot::FillListAllNodeIDs()
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
			pWndCtrl = GetDlgItem(IDC_CURVE_ID);
   		    ((CComboBox*)(pWndCtrl))->AddString(CID);
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

int CElg_CRot::SetInfoForDataBase(CDrCurve* pDrObject)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr*	pINodeList	= pDrObject->GetINodeList();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
    //////////////////
	int i,nData,index;  
	CString Nid;
	CDrNode* pDrNode;
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)CURVE);
    pDrObject->SetElemType((int)GENR_OBJECT);          	// globals
    pDrObject->SetLevelType((int)LEVEL_UNCLE);          // globals
    //////////////////////////////
	pDrObject->SetnDim_S(4); //Rational for use in circle and later in Solid 
//	pDrObject->SetClosed_T(FALSE); // done later
    //////////////////////////////
	pDrObject->SetObjectID(m_CurveID);	
    ////////////////////////////////////////////////////////////////////	
    nData = 1;		// only One Input Control Data
    /////////////////
	CDListMgr*  pDListMgr	= pObjectMgr->GetObjectList(NODE);
	for (i=0;i<nData;i++)
	{
		//////////////////////////////////
		index = pObjectMgr->GetObjectIndexfromKey(NODE,m_NodeID,1);// actually NodeID
		if(index>=0)
		{
			pDrNode = (CDrNode*)(pDListMgr->GetObject(index));
			pINodeList->InsertObject(pDrNode);
			////////////////////////////////// save curve
			pDrNode->GetCurveList()->InsertObject(pDrObject);
		}
	}
	//////////
	pDrObject->SetInputType(1);		// 
	//////////////////////////////////
	pDrObject->SetMaxINodes_S(nData);	// 
	////////////////////////////////////////// Reciprocate
	pDrObject->SetFromID_S(m_FromID);
	pDrObject->SetToID_S(m_ToID);
	/////////////////////////////
	index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_FromID,1);
	pDrNode = (CDrNode*)(pDListMgr->GetObject(index));
	pDrNode->GetCurveList()->InsertObject(pDrObject);
	index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_ToID,1);
	pDrNode = (CDrNode*)(pDListMgr->GetObject(index));
	pDrNode->GetCurveList()->InsertObject(pDrObject);
	////////////////////////////////////////////////////////////// interpolation
	int nOrder = 3;// k = 3 for Circle
	pDrObject->SetOrder_S(nOrder);				
	pDrObject->SetCurveType_S(CP_CIRCLE);
	pDrObject->SetSegAngle_S(m_SegAngle);
	///////////////////////////////////////////////////////////////////
	int nDim	= 4;			// Homogeneous(Rational)
	pDrObject->SetnDim_S(nDim);
	///////////////////////////////////////////////////////////// ReDistribute 
	pDrObject->SetOutMethod_S(CO_HORNER);		// Output Method
	/////////////////////////////////////
	if(m_Ratio == 1.0)		
		m_bUnifOT = TRUE;
	else			
		m_bUnifOT = FALSE;
	//////////////////////	
	pDrObject->SetRatio_S(m_Ratio);					
	pDrObject->SetUniform_S(m_bUnifOT);		// Output Distribution:
	///////////////////////////////////////// save
	// if
	//		 Uniform:
	//			 	make As Many Segment of Control Nodes
	//				as Close to SegAng(Default=120) with total of m_nMesh Output segment
	//				in all of them i.e.,
	//				nSegs = #of Bezier Quadratic CurveSegs in S-direction
	//				saved as pDrObject->SetSegmentCount_S(nSegs)
	//				variable Angles are stored in m_pODis;
	//				m_pONum containing Number of Mesh for each CurveSeg
	//		 NonUniform:
	//			 	make m_nMesh Segments of Control Nodes
	//				with 1 Output segment in each, i.e.,
	//				m_nMesh many CurveSeg in S-direction
	//				nSegs = m_nMesh = #of Bezier Quadratic CurveSegs in S-direction
	//				saved as pDrObject->SetSegmentCount_S(nSegs)
	//				Total Angle is stored in m_pODis[0];
	//				m_pONum[0] containing Number of Mesh for the Patch
	/////////////////////////////////////////////////////////////////////
	BOOL bClosed;
	if(m_dAng<0.)
		m_dAng = 0.;
	if(m_dAng>360.)
		m_dAng = 360.;
	double dAng = m_dAng;
	//////////////////////////////// Closed ?
	if(dAng == 360)
		bClosed = TRUE;
	else
		bClosed = FALSE;
	//////////
	pDrObject->SetTheta_S(m_dAng);		
	pDrObject->SetClosed_S(bClosed);
	////////////////////////////////
	int nSegs;
	//////////////////////////////////////////////////////// Uniform
	if(m_bUnifOT)						// Uniform
	{
		// Max Angle for each Patch Segment = 120;
		// for stability
		////////////////////////////////////////// <=m_SegAngle:One Curve 
		if(dAng<= m_SegAngle)
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
		////////////////////////////////////////// >m_SegAngle:Many Curves 
		else
		{
			int		nTimes,nMesh,nRem,i;
			double	dAngInc,dSegAng;
			////////////////
			dAngInc	= dAng/m_nMesh; // assume dAngInc ALWAYS <=120
			if(dAngInc>120)
			{
				AfxMessageBox("Error:\nToo Few Number of Elements!");
				/////////////////////
				return -1;
			}
			nTimes	= (int)(m_SegAngle/dAngInc);
			dSegAng	= nTimes * dAngInc;	// get biggest possible angle<=m_SegAngle
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
		// NOTE:	allows Unequal Generation
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
			double angle = x + i * a;
			/////////////////////////
			if(angle>120)
			{
				AfxMessageBox("Error:\nToo Few Number of Elements!");
				/////////////////////
				return -1;
			}
			///////////////////
			m_pODis[i] = angle;
			///////////////////
		}
	}
	/////////////////////
	pDrObject->SetMaxOutSeg_S(m_nMesh);		// Total Number of Output Segments
	pDrObject->SetSegmentCount_S(nSegs); 	// # of Curves ( B-Spline Segs)
	//////////////////////////////////////////		 
	pDrObject->SetNum_tPointer_S(m_pOSeg);	// Number of Outputs for
											// each Curve Segment
	pDrObject->SetNum_tPointer_Ex_S(m_pOSeg);	// Number of Outputs for
												// each Curve Segment
	pDrObject->SetDis_AngPointer_S(m_pODis);// Number of Angles for
											// Bezier Control Pts. Generation
    ////////////////////////////////////////////// Total Evaluation Pts
	int nOut = m_nMesh + 1;
	///////////////////////
	pDrObject->SetMaxOutPts_S(nOut);
	pDrObject->SetLongOutPts((long)nOut);
	////////////////////////////////////////////////////////////////
	int nCon_BZ	= (nOrder - 1) * nSegs + 1;	// (k-1) * L + 1 , Open
	if(bClosed)
		nCon_BZ--; 		
	pDrObject->SetnCon_BZ_S(nCon_BZ); // = m_nMaxCurveCNodes(Eventually)
	////////////////////////////////////////////////////////////////////// Mesh(Output)
	nData			= nSegs + 1;
	//////////////////////////////////////////////// Update	 
	pDrObject->SetData_S(nData);		// Generated: # of Data
	pDrObject->SetData_Ex_S(nData);		// Adjusted# of Data for Conics(Circle) 
	////////////////////////////
	int		nControls,nCurveSeg,nMaxDistinct,nMaxTotal;
	///////////////////////////////////////////////////
	nControls 	= nData + nOrder - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	nCurveSeg 	= nData - 1;					// L
	nMaxDistinct 	= nData;
	nMaxTotal		= nData + (2 * nOrder - 2);	// n + k + 1 = nData + (2k - 2)
	if(bClosed)
	{
		nCurveSeg++;
		nMaxDistinct++;
		nMaxTotal++;
	}
    ////////////////////
	pDrObject->SetpWts_DT_S((pDOUBLE)NULL);	// pointer
	/////////////	
	pDrObject->SetpKnots_S((pDOUBLE)NULL);	// pointer
	//////////////////////////////
	pDrObject->SetnCon_BS_S(nControls);	// L + k - 1
											// = nData + k - 2
											// = n + 1 (B-Spline));
	pDrObject->SetnKnots_S(nMaxDistinct);
	pDrObject->SetnMKnots_S(nMaxTotal);
	////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	//////////////////
	return 0;
	
} 
////////////////////////////////// end of module //////////////////////
/* 
int CElg_CRot::SetInfoForDataBase_Ex(CDrCurve* pDrCurve, double theta, WORLD AxPt)
{

	CDListMgr* pINodeList	= pDrCurve->GetINodeList();
	pWORLD pData	 		= NULL;
	pWORLD pDat_Ex 			= NULL;
    ///////////////////////////////////////////////////////// Memory
	pData 	= new WORLD[pDrCurve->GetData_S()];
	if(!pData)
	{
		AfxMessageBox("ERROR:Memory Failure!\nCElg_CRot::SetInfoForDataBase_Ex_1");
		return -1;
	}
	////////////////////////////////////////////// Set Data
	if(SetUpINodes(pINodeList,pData,pDrCurve->GetData_S())<0)
		return -1;
	///////////////////////////////////////////////////////// Radius, Center and Normal
	WORLD Center, Normal;
	double Radius;
	Calc_CandR(pData,&Center, &Radius, Normal,AxPt);
	UnitAxisFromEndNodes(pWORLD pNormal);
	//////////////////////////////////////////// save
	pDrCurve->SetCenter_S(Center);
	pDrCurve->SetNormal_S(Normal);
	pDrCurve->SetRadius_S(Radius);
	////////////////////////////////////////////////////////// Central Angles
	pDOUBLE pAngOld = new double[3];
	//////////////////////////////////////////// save
	pDrCurve->SetTheta_S(theta);
	///////////////////////////////////////////////////////// # of Spline & Bezier Controls
	int nSeg_DT = 2;
	if(m_bClosed)
		nSeg_DT++;
	////////////////////////////////////////////// estimate Max Segments based on Mesh
	pINT MeshOld	= pDrCurve->GetNum_tPointer_S();	// Number of Outputs for
														// each Curve Segment
	int nSegEst=0,i;
	for(i=0;i<nSeg_DT;i++)
		nSegEst += MeshOld[i];
	pINT   MeshNew	= new int[nSegEst]; // 
	pDOUBLE AngNew	= new double[nSegEst]; // 
	/////////////////////////////////////		
	int nConBZ, nConBS;
	double 	SegAng 	= pDrCurve->GetSegAngle_S();
	int nSeg_Ex = NumberOfDataAndCons( pAngOld, MeshOld, SegAng, m_bClosed,
									   AngNew, MeshNew, &nConBZ, &nConBS);
	delete [] pAngOld;
	//////////////////////////////////////////// save
	pDrCurve->SetnCon_BS_S(nConBS);
	pDrCurve->SetnCon_BZ_S(nConBZ);
	///////////////////////////////////////////////////////// Check Mesh Info 
	int nOut	= pDrCurve->GetMaxOutPts_S();
	int nMesh 	= 0;
	for(i=0;i<nSeg_Ex;i++)
		nMesh += MeshNew[i];
	////////////////////////
	if(nOut != (nMesh+1) )
	{
		AfxMessageBox("Internal Problem:nMesh != nOut\nCElg_CRot::SetInfoForDataBase_Ex");
		return -1;
	}
	////////////////////////////////////////////// save
	BOOL bExpanded = FALSE;
	if(nSeg_Ex != nSeg_DT)
		bExpanded		= TRUE;
	///////////////////////////
	int nDat_Ex;
	nDat_Ex = nSeg_Ex + 1;
	if(m_bClosed)
		nDat_Ex--;
	////////////////////////
	pDrCurve->SetData_Ex_S(nDat_Ex);
	pDrCurve->SetExpanded_S(bExpanded);		// update
	pDrCurve->SetMaxCubicCurves(nSeg_Ex);	// update
	//////////////////////////////////////////		 
	pDrCurve->SetNum_tPointer_Ex_S(MeshNew);	// New Number of Outputs for
												// each Curve Segment
	pDrCurve->SetMaxOutSeg_S(nSeg_Ex);			// Number of Output Segments
												// = nData - 1 = L = m_nCurveSeg
 	///////////////////////////////////////////// Adjust Data as nSegAng degree segment
 	pDat_Ex	= new WORLD[nDat_Ex];
	if(!pDat_Ex )
	{
		AfxMessageBox("ERROR:Memory Failure!\nCElg_CRot::SetInfoForDataBase_Ex_3");
		return -1;
	}
	/////////////////
	int nDat_Ex_Actual = GenerateNewPtsOnCircle(pData, AngNew, Center, Normal, 
											pDat_Ex, nSeg_Ex, m_bClosed);
	if(nDat_Ex_Actual != nDat_Ex )
	{
		AfxMessageBox("Internal Problem:\nCElg_CRot::SetInfoForDataBase_Ex_4");
		return -1;
	}
	delete [] AngNew; // 
	//////////////////////////////////////////// save
	Fill_NodeList_Ex(pDrCurve, pDat_Ex, nDat_Ex);
	//////////////////////////////////////////// Now ReleaseMemory
	if(pData)
	{
		delete [] pData;
		pData = NULL;
	}	
	if(pDat_Ex) 
	{
		delete [] pDat_Ex;
		pDat_Ex = NULL;
	}
	////////////////////////
	return 0;
}

int CElg_CRot::SetInfoForDataBase_Ex_TOT(CDrCurve* pDrCurve, double theta, WORLD AxPt)
{

	CDListMgr* pINodeList	= pDrCurve->GetINodeList();
	pWORLD pData	 		= NULL;
	pWORLD pDat_Ex 			= NULL;
    ///////////////////////////////////////////////////////// Memory
	pData 	= new WORLD[pDrCurve->GetData_S()];
	if(!pData)
	{
		AfxMessageBox("ERROR:Memory Failure!\nCElg_CRot::SetInfoForDataBase_Ex_1");
		return -1;
	}
	////////////////////////////////////////////// Set Data
	if(SetUpINodes(pINodeList,pData,pDrCurve->GetData_S())<0)
		return -1;
	///////////////////////////////////////////////////////// Radius, Center and Normal
	WORLD Center, Normal;
	double Radius;
	Calc_CandR(pData,&Center, &Radius, Normal,AxPt);
	UnitAxisFromEndNodes(pWORLD pNormal);
	//////////////////////////////////////////// save
	pDrCurve->SetCenter_S(Center);
	pDrCurve->SetRadius_S(Radius);
	pDrCurve->SetNormal_S(Normal);
	////////////////////////////////////////////////////////// Central Angles
	pDrCurve->SetTheta_S(theta);
	///////////////////////////////////////////////////////// # of Spline & Bezier Controls
	int nSeg_DT = 2;
	if(m_bClosed)
		nSeg_DT++;
	////////////////////////////////////////////// estimate Max Segments based on Mesh
	pINT   MeshNew	= new int[m_nUnifTOT]; // 
	pDOUBLE AngNew	= new double[m_nUnifTOT]; // 
	/////////////////////////////////////		
	int nConBZ, nConBS;
	double 	SegAng 	= pDrCurve->GetSegAngle_S();
	int nSeg_Ex = NumberOfDataAndCons_TOT( theta, m_nUnifTOT, SegAng, m_bClosed,
									   AngNew, MeshNew, &nConBZ, &nConBS);
	if(nSeg_Ex<1)
	{
		AfxMessageBox("Internal Problem:nSeg_Ex<1\nCElg_CRot::SetInfoForDataBase_Ex_TOT");
		return -1;
	}
	//////////////////////////////////////////// save
	pDrCurve->SetnCon_BS_S(nConBS);
	pDrCurve->SetnCon_BZ_S(nConBZ);
	///////////////////////////////////////////////////////// Check Mesh Info 
	int nOut	= pDrCurve->GetMaxOutPts_S();
	int nMesh 	= 0;
	for(int i=0;i<nSeg_Ex;i++)
		nMesh += MeshNew[i];
	////////////////////////
	if(nOut != (nMesh+1) )
	{
		AfxMessageBox("Internal Problem:nMesh != nOut\nCElg_CRot::SetInfoForDataBase_Ex_TOT");
		return -1;
	}
	////////////////////////////////////////////// save
	BOOL bExpanded = FALSE;
	if(nSeg_Ex != nSeg_DT)
		bExpanded		= TRUE;
	///////////////////////////
	int nDat_Ex;
	nDat_Ex = nSeg_Ex + 1;
	if(m_bClosed)
		nDat_Ex--;
	////////////////////////
	pDrCurve->SetData_Ex_S(nDat_Ex);
	pDrCurve->SetExpanded_S(bExpanded);		// update
	pDrCurve->SetMaxCubicCurves(nSeg_Ex);	// update
	//////////////////////////////////////////		 
	pDrCurve->SetNum_tPointer_Ex_S(MeshNew);	// New Number of Outputs for
												// each Curve Segment
	pDrCurve->SetMaxOutSeg_S(nSeg_Ex);			// Number of Output Segments
												// = nData - 1 = L = m_nCurveSeg
 	///////////////////////////////////////////// Adjust Data as nSegAng degree segment
 	pDat_Ex	= new WORLD[nDat_Ex];
	if(!pDat_Ex )
	{
		AfxMessageBox("ERROR:Memory Failure!\nCElg_CRot::SetInfoForDataBase_Ex_3");
		return -1;
	}
	/////////////////
	int nDat_Ex_Actual = GenerateNewPtsOnCircle(pData, AngNew, Center, Normal, 
											pDat_Ex, nSeg_Ex, m_bClosed);
	if(nDat_Ex_Actual != nDat_Ex )
	{
		AfxMessageBox("Internal Problem:\nCElg_CRot::SetInfoForDataBase_Ex_4");
		return -1;
	}
	delete [] AngNew; // 
	//////////////////////////////////////////// save
	Fill_NodeList_Ex(pDrCurve, pDat_Ex, nDat_Ex);
	//////////////////////////////////////////// Now ReleaseMemory
	if(pData)
	{
		delete [] pData;
		pData = NULL;
	}	
	if(pDat_Ex) 
	{
		delete [] pDat_Ex;
		pDat_Ex = NULL;
	}
	////////////////////////
	return 0;
}

int CElg_CRot::GenerateNewPtsOnCircle
									( 	pWORLD pData, pDOUBLE Angles,
										WORLD Center, WORLD Normal,  
										pWORLD pDat_Ex, int nSeg_Ex, BOOL bClosed 
									)
{

	WORLD DNew,DOld;
	int i,nIndex=0;
	/////////////////////////// start with Ist One
	DOld.x = pData.x;
	DOld.y = pData.y;
	DOld.z = pData.z;
	pDat_Ex[nIndex].x = DOld.x;
	pDat_Ex[nIndex].y = DOld.y;
	pDat_Ex[nIndex].z = DOld.z; 
	////////////////////////////////////////// Loop
	double dAng;
	//////////////////////
	int nMax = nSeg_Ex;
	if(bClosed)			// last one ends in Ist one
		nMax--;
	///////////		
	for(i=0;i<nMax;i++)
	{
		dAng = Angles[i];
		////////////////
		GetAPtByRotation(&DOld, Center, Normal, dAng, &DNew);
		////////////////////////////////////////////////// save
		nIndex++;
		pDat_Ex[nIndex].x = DNew.x;
		pDat_Ex[nIndex].y = DNew.y;
		pDat_Ex[nIndex].z = DNew.z;
		////////////////////////////////////////////////// reset
		DOld.x = DNew.x;
		DOld.y = DNew.y;
		DOld.z = DNew.z;
		////////////////
	}	
	//////////////
	return (nIndex+1);	// total Expanded
	
}		 										
	
int CElg_CRot::GetAPtByRotation(pWORLD DOld, WORLD Center, WORLD Normal, double dAng,
									 pWORLD DNew) 
{
	
	DNew->x = DOld->x;
	DNew->y = DOld->y;
	DNew->z = DOld->z;
	////////////////////////////////////////////////////////////////// 
	C3DMath	Math3D;
	CXForm	XForm(TRUE);	// Parallel
	///////////////////////////////////////
	MATRIX Rot;
	pMATRIX pRot = &Rot;  
	Math3D.GetIdentityMATRIX(pRot);
	//////////////////////////////////////// Translate Center & DOld to Origin
	XForm.Translate(pRot, -Center.x, -Center.y, -Center.z, XF_REPLACE);	
	//////////////////////////////////////// 	
	XForm.Transform(DNew, DNew, pRot);	  
	//////////////////////////////////////////////////////////// Generate by rotation
	WORLD Origin = {0.0,0.0,0.0};
	double rAng = .0174533 * dAng; // pi/180 
	////////////
	Math3D.GetIdentityMATRIX(pRot);
	XForm.RotateAboutLineMATRIX(pRot, &Origin, &Normal,rAng,XF_REPLACE);
	XForm.Transform(DNew, DNew, pRot);
	//////////////////////////////////////////////////////////// Translate Data Back: New Pt
	Math3D.GetIdentityMATRIX(pRot);
	XForm.Translate(pRot, Center.x, Center.y, Center.z, XF_REPLACE);
	XForm.Transform(DNew, DNew, pRot);
	/////////	
	return 0;
}	

int CElg_CRot::Calc_CandR(pWORLD pData,pWORLD pCenter, pDOUBLE Radius, WORLD Normal,WORLD AxPt)
{
	///////////////////////////////////////////////////////
	// given:
	//		Data	= a Pt. on the Current Circle
	//		Normal	= to the Plane of the circle
	//		AxPt	= a Pt on the Normal
	// Now
	//		RadVec	= the vector from Data to Center
	//				= RadVecA - RadVecD;
	// where
	//		RadVecD	= the perpendicular vector from Data to Normal
	//				= Data - (Data.dot.Normal)Normal
	//		RadVecA	= the perpendicular vector from AxPt to Normal 
	//				= AxPt - (AxPt.dot.Normal)Normal
	//
	// and		
	//		Center	= rData + RadVec;
	//		Radius	= ||RadVec||
	////////////////////////////////////////////////////////
	C3DMath	Math3D;
	//////////////////////////////////////// RadVec
	WORLD	RadVec,RadVecD,RadVecA,temp;
	double	dotn;
	///////////////////
	dotn	= Math3D.Dot3DPts(pData,&Normal);
	temp.x	= Normal.x;
	temp.y	= Normal.y;
	temp.z	= Normal.z;
	Math3D.Scale3DPts(dotn,&temp);
	Math3D.Sub3DPts(pData, &temp, &RadVecD);
	///////////////////
	dotn	= Math3D.Dot3DPts(&AxPt,&Normal);
	temp.x	= Normal.x;
	temp.y	= Normal.y;
	temp.z	= Normal.z;
	Math3D.Scale3DPts(dotn,&temp);
	Math3D.Sub3DPts(&AxPt, &RadVecD, &RadVecA);
	/////////////////////////////////////////// Radius Vec
	Math3D.Sub3DPts(&RadVecA, &temp, &RadVec);
	/////////////////////////////////////////// Radius
	*Radius = Math3D.Len3DPts(&RadVec); 
	/////////////////////////////////////////// Center
	Math3D.Add3DPts(pData, &RadVec, pCenter);
	/////////
	return 0;

}

int CElg_CRot::Fill_NodeList_Ex(CDrCurve* pDrCurve, pWORLD pDat_Ex, int nDat_Ex)
{

	/////////////////////////////////////////////////////////////////// FillUp 
	WORLD		LocalPos;
	CString		Nid,CurveID;
	int			nChLen;
	char		buf[20];
    CDrNode* 	pAddNode;
	int s,t =0,j;
	/////////////////////////////////////////////////////////// Data
	CurveID					= pDrCurve->GetObjectID();
	CDListMgr* pENodeList	= pDrCurve->GetENodeList();
	///////////////////////////////////////////// Name
	nChLen	= CurveID.GetLength();
	if(nChLen>NAME_LEN-2)
		nChLen = NAME_LEN-2;
	//////////////////////////////////////////////////////////// Bezier	
	for (s = 0; s<nDat_Ex; s++)
	{
		///////////////////////////////////////// CREATE
		Nid	= "E_";	
		Nid	+= CurveID.Left(nChLen);
	    //////////////////////////////////// Name
	    sprintf(buf,"%d%d",s,t);
	    Nid += buf; 
		////////////////////////////////////
		j = t * nDat_Ex + s;
		////////////////////////////		
		LocalPos.x	= (pDat_Ex+j)->x;
		LocalPos.y	= (pDat_Ex+j)->y;
		LocalPos.z	= (pDat_Ex+j)->z;
		///////////////////////////////////// in THE List
		CEDlgMgr  EDlgMgr; 
		pAddNode = EDlgMgr.CreateNode(Nid,LocalPos,FALSE);
		//////////////////////////////////////////////
//		pAddNode = PostNode(Nid,LocalPos,FALSE);	// Create DrNode
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////// Expanded Data List
		pENodeList->InsertObject(pAddNode); //ENodeList
		//////////////////////////////////////// Reciprocate
		pAddNode->GetCurveList()->InsertObject(pDrCurve);
		////////
	}
	//////////////////////////////////////////// Expanded Data List Count
	pDrCurve->SetMaxENodes_S(nDat_Ex);
	//////////////////////////////////	
	return 0;
}

int CElg_CRot::NumberOfDataAndCons_TOT( double theta, int nSegTot, double SegAng, BOOL bClosed, 
									pDOUBLE AngNew, pINT MeshNew, pINT nConBZ, pINT nConBS)
{
    
    int		index=-1;
    double  TotAng;
	//////////////////////////////////////////////
	TotAng		= theta;
	if(bClosed)
		TotAng = 360.;
	///////////////////
	double incAng = TotAng/nSegTot;	
	/////////////////// Adjust SegAng to match Mesh
	int    numSeg = (int)(SegAng/incAng);
	if(numSeg<1)
		numSeg = 1;
	double SegAngNew = numSeg * incAng;
	int jLup			= nSegTot/numSeg;
	for(int j=0;j<jLup;j++)
	{
		index++;
		AngNew[index] = SegAngNew;
		MeshNew[index]= numSeg;
	}
	////////////////////////////// remainder
	int jRem		= nSegTot%numSeg;
	if(jRem)
	{
		index++;
		AngNew[index] = TotAng - SegAngNew;
		MeshNew[index]= jRem;
	}
	////////////////////////
	int nBezSeg = index + 1;
	//////////////////////////////////////////// Full Circle
	if(bClosed)
	{
		*nConBZ	= 2*nBezSeg;	// 2*L
		*nConBS	= nBezSeg + 1;	// (L+Order(=3)-1= L+2) then -1 for Closed
	}	
	else
	{	
		*nConBZ	= 2*nBezSeg + 1;	// 2*L + 1
		*nConBS	= nBezSeg + 2;	// (L+Order(=3)-1= L+2) 
	}
	////////////////	
	return nBezSeg;
}


int CElg_CRot::NumberOfDataAndCons( pDOUBLE AngOld, pINT MeshOld, double SegAng, BOOL bClosed, 
									pDOUBLE AngNew, pINT MeshNew, pINT nConBZ, pINT nConBS)
{
    
    int		nBezSeg,index=-1;
	//////////////////////////////////////////////
	int nLup = 2,i;
	if(bClosed)
		nLup++;
	///////////////////	
	for(i=0;i<nLup;i++)
	{
		double AOld = AngOld[i];
		/////////////////
		if(SegAng>AOld)
		{
			index++;
			AngNew[index] = AOld;
			MeshNew[index]= MeshOld[i];
		}
		else
		{
			int    numSeg,jLup;
			double SegAngNew;
			///////////////////////////	
			int MOld = MeshOld[i];
			/////////////////// Adjust SegAng to match Mesh
			double incAng 		= AOld/MOld;
			////////////////////////////////////////// Angle too Big & Too Few Mesh!
			if(incAng>SegAng)
			{
				incAng		= SegAng;
				numSeg		= (int)(AOld/incAng);
				SegAngNew 	= SegAng;
				jLup		= numSeg;
				/////////////////////
				for(int j=0;j<jLup;j++)
				{
					index++;
					AngNew[index] = SegAngNew;
					MeshNew[index]= numSeg;
				}
				////////////////////////////// remainder
				double angTot = jLup * SegAng;
				if(angTot<AOld)
				{
					index++;
					AngNew[index] = AOld - angTot;
					MeshNew[index]= 1;			// one more
				}
			}
			////////////////////////////////////////// Angle too Big BUT Mesh Tolerable!
			else
			{
				numSeg 		= (int)(SegAng/incAng);
				SegAngNew 	= numSeg * incAng;
				jLup		= MOld/numSeg;
				for(int j=0;j<jLup;j++)
				{
					index++;
					AngNew[index] = SegAngNew;
					MeshNew[index]= numSeg;
				}
				////////////////////////////// remainder
				int jRem		= MOld%numSeg;
				if(jRem)
				{
					index++;
					AngNew[index] = AOld - SegAngNew;
					MeshNew[index]= jRem;
				}
			}
			////////////////////////////////////////////
		}		
	}
	////////////////////
	nBezSeg = index + 1;	 
	//////////////////////////////////////////// Full Circle
	if(bClosed)
	{
		*nConBZ	= 2*nBezSeg;	// 2*L
		*nConBS	= nBezSeg + 1;	// (L+Order(=3)-1= L+2) then -1 for Closed
	}	
	else
	{	
		*nConBZ	= 2*nBezSeg + 1;	// 2*L + 1
		*nConBS	= nBezSeg + 2;	// (L+Order(=3)-1= L+2) 
	}
	////////////////	
	return nBezSeg;
}

void CElg_CRot::UnitAxisFromEndNodes(pWORLD pNormal)
{
	///////////////
	C3DMath	Math3D;
	//////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList();
    /////////////////
	int 		index;
	CDrNode* 	pDrNode;
	////////////////////////////////////////////////////// FromNode
	index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_FromID,1);
	if(index>=0)
		pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
	else
		AfxMessageBox("CMI_GangP::UnitAxisFromEndNodes");	
   	///////////////////////////////////////////// get Raw Pt.
   	m_FromPt = *(pDrNode->GetLocalPos());
	////////////////////////////////////////////////////// ToNode
	index	= pObjectMgr->GetObjectIndexfromKey(NODE,m_ToID,1);
	pDrNode	= (CDrNode*)(pDListMgr->GetObject(index));
   	///////////////////////////////////////////// get Raw Pt.
  	m_ToPt = *(pDrNode->GetLocalPos());
	///////////////////////////////////////////// Vector
	Math3D.Sub3DPts(&m_ToPt, &m_FromPt, pNormal);
	Math3D.Normalize(pNormal,pNormal);
	///////////////
	return;
}

*/
///////////////////

//
