// Loft2.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"

#include "Def_Objs.h"
//////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h"
///////////////////// dialogMgr
#include "MPatMgr.h"
#include "dlg_Loft2.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
#include "PA_Loft2.h"
 
#include "MP_Loft2.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MIN_CNODES_CURVE	4
#define MIN_CNODES_PATCH	16
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMP_Loft2,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMP_Loft2::CMP_Loft2()
{
}

CMP_Loft2::~CMP_Loft2()
{
}

int CMP_Loft2::SetInfoBase
				(
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					CDListMgr*						pCurveList,
					CList<CURVELATCH,CURVELATCH>*	pLatchList,
					CList<int,int>*					pElperSegList,
					double							Ratio,
					CView*							pView
				) 
{
	int index;
	CDrCurve*	pDrCurve;
	////////////////////////////////////////////////////////// Dialog Info(Don't Display Dlg)
	CDlg_Loft2 Dlg;
	////////////////////////////////////////////////// PatchID
	Dlg.m_PatchID	= PatchID;
	////////////////////////////////////////////////// CurveID
	if(pCurveList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Loft2::SetInfoBase\npCurveList->GetCount() != 2");
		return -1;
	}
	pDrCurve	= (CDrCurve*)(pCurveList->GetObject(0) );
	///////////////////////////////// Detach (It is Reciprocated in SetInfoBase of Dlg)
	index				= pDrCurve->GetPatchList()->GetObjectIndex(pDrPatch);
	if(index>=0)
		pDrCurve->GetPatchList()->RemoveObject(index);
	///
	Dlg.m_CID_1	= pDrCurve->GetObjectID();
	pDrCurve	= (CDrCurve*)(pCurveList->GetObject(1) );
	///////////////////////////////// Detach (It is Reciprocated in SetInfoBase of Dlg)
	index				= pDrCurve->GetPatchList()->GetObjectIndex(pDrPatch);
	if(index>=0)
		pDrCurve->GetPatchList()->RemoveObject(index);
	///
	Dlg.m_CID_2	= pDrCurve->GetObjectID();
	////////////////////////////////////////////////// Latch
	if(pLatchList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Loft2::SetInfoBase\npLatchList->GetCount() != 2");
		return -1;
	}
	////////////////////////////////////////////////// Latch
	Dlg.m_Orient_1 = "FORWARD";
	if(pLatchList->GetHead() == CL_BACKWARD)
		Dlg.m_Orient_1 = "BACKWARD";
	///////
	Dlg.m_Orient_2 = "FORWARD";
	if(pLatchList->GetTail() == CL_BACKWARD)
		Dlg.m_Orient_2 = "BACKWARD";
	////////////////////////////////////////////////// Mesh
	if(pElperSegList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Loft2::SetInfoBase\npElperSegList->GetCount() != 1");
		return -1;
	}
	Dlg.m_nMesh		= pElperSegList->GetHead();
	Dlg.m_Ratio		= Ratio;
	////////////////////////////////////////////////// Fill Info
	Dlg.SetInfoForDataBase(pDrPatch);
	////////////////////////////////////////////////// Do It
	int nResult = GoDoIt(pDrPatch);
	//////////////
	if(nResult<0)
		return -1;
	/////////////////////
	return 0;		 
}

int CMP_Loft2::GoDoIt(CDrPatch* pDrPatch) 
{

	//////////////////////////////////////////////////////////
	GetInfo(pDrPatch);
	m_pDrPatch = pDrPatch;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrPatch->GetCNodeList();	
	///////                    				// ControlNode Mesh
	Loft();
	////////////////////////
	m_PatchType = PA_TENSOR;
	////////////////////////
	if(InsertMeshInfo(FALSE)<0)
		return -1;
	/////////////////////
	return 0;
}

CDrPatch* CMP_Loft2::GoDoIt() 
{
	//////////////////////////////////////////////////////////
	m_pDrPatch 		= GetInfo();       // PGen Dialog
	if(!m_pDrPatch)		// cancel
		return (CDrPatch*)NULL;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrPatch->GetCNodeList();	
	///////                    				// ControlNode Mesh
	Loft();
	////////////////////////
	m_PatchType = PA_TENSOR;
	////////////////////////
	if(InsertMeshInfo(FALSE)<0)		// WE HAVE CHANGED TO FALSE
									// TO SAVE ALL CONTROL NODES
		return (CDrPatch*)NULL;
	/////////////////////
	return m_pDrPatch;
}			

CDrPatch* CMP_Loft2::GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	//////////////////////////////////////////////////////////////////
	CMPatMgr 	MPatMgr;
	CMPatMgr* 	pMPatMgr = &MPatMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
	if (pMPatMgr->DoModal_Patch_Loft(&Cid,4) == IDCANCEL)
			return (CDrPatch*)NULL;
    /////////////////////////////////////////////////////// update
	m_CurrentPatchID 	= Cid;
	index 				= pObjectMgr->
							GetObjectIndexfromKey(PATCH,Cid,1);
	if(index>=0)
	{						
		CDrPatch* pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
   		//////////////////////////////
		m_PatchProc		= pDrPatch->GetPatchProc();
		m_pNum_t_T		= pDrPatch->GetNum_tPointer_T();
		m_pDis_t_T		= pDrPatch->GetDis_tPointer_T();
		m_CurveID_S[0]	= pDrPatch->GetCurveID(0);
		m_CurveID_S[1]	= pDrPatch->GetCurveID(1);
		/////////
		m_CuLatch[0]	= pDrPatch->GetCurveLatch(0);
		m_CuLatch[1]	= pDrPatch->GetCurveLatch(1);
		////////////
		m_nSegs_T		= pDrPatch->GetMaxBezSegments_T();	//segs in Extrusion dirn
		m_Ratio			= pDrPatch->GetRatio_T();
		m_bUnifOT		= pDrPatch->IsUniform_T();
		m_nOut_T		= pDrPatch->GetMaxOutPts_T();;
		m_nOrder_T		= pDrPatch->GetOrder_T();
		m_CurveType_T	= pDrPatch->GetCurveType_T();;
		m_nDim_T		= pDrPatch->GetnDim_T();
		m_bClosed_T		= pDrPatch->IsClosed_T();					// for Extrusion
		///////////////////////////////////////// Bezier Linear
		if(m_bUnifOT)
			m_nOut_TCon	= 2;// Only One Patch in T-dir
		else
//4/26/96			m_nOut_TCon	= pDrPatch->GetMaxOutSeg_T()+1;	// Number of Output Segments
			m_nOut_TCon	= m_nSegs_T+1;	// Number of Output Segments
		/////////////////////////////////////
		m_nSegs_TCon		= m_nOut_TCon - 1;
		m_nMaxPatchCNodes_T = m_nOut_TCon;
		////////////////
		return pDrPatch;
	}
	else
		return (CDrPatch*)NULL;
}			


int CMP_Loft2::GetInfo(CDrPatch* pDrPatch)
{
	//////////////////////////////
	m_PatchProc		= pDrPatch->GetPatchProc();
	m_pNum_t_T		= pDrPatch->GetNum_tPointer_T();
	m_pDis_t_T		= pDrPatch->GetDis_tPointer_T();
	m_CurveID_S[0]	= pDrPatch->GetCurveID(0);
	m_CurveID_S[1]	= pDrPatch->GetCurveID(1);
	/////////
	m_CuLatch[0]	= pDrPatch->GetCurveLatch(0);
	m_CuLatch[1]	= pDrPatch->GetCurveLatch(1);
	////////////
	m_nSegs_T		= pDrPatch->GetMaxBezSegments_T();	//segs in Extrusion dirn
	m_Ratio			= pDrPatch->GetRatio_T();
	m_bUnifOT		= pDrPatch->IsUniform_T();
	m_nOut_T		= pDrPatch->GetMaxOutPts_T();;
	m_nOrder_T		= pDrPatch->GetOrder_T();
	m_CurveType_T	= pDrPatch->GetCurveType_T();;
	m_nDim_T		= pDrPatch->GetnDim_T();
	m_bClosed_T		= pDrPatch->IsClosed_T();					// for Extrusion
	///////////////////////////////////////// Bezier Linear
	if(m_bUnifOT)
		m_nOut_TCon	= 2;// Only One Patch in T-dir
	else
//4/26/96			m_nOut_TCon	= pDrPatch->GetMaxOutSeg_T()+1;	// Number of Output Segments
		m_nOut_TCon	= m_nSegs_T+1;	// Number of Output Segments
	/////////////////////////////////////
	m_nSegs_TCon		= m_nOut_TCon - 1;
	m_nMaxPatchCNodes_T = m_nOut_TCon;
	////////////////
	return 0;
}			

int CMP_Loft2::Loft()
{
	//////////////////////////////////////////////////////////////////////////////////
	//	LOFTING_2 is LINEAR interpolation of GENERATED NODES, NOT of CONTROL NODES	//
	//	of the curves in T-Direction. So, all generated nodes of SPINE curve will	//
	//	be saved as CNodes of the patch in T-Direction and eventually the PATCH		//
	//  will be generated by LINEAR interpolation in T- direction,					//
	//					IRRESPECTIVE of CURVETYPE of SPINE							// 												//
	//	THIS INEFFICIENCY is needed for Finite Element Data Generation wherein		//
	//		Total Tally of Generated Nodes are important , Not of Control Nodes		//
	//////////////////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* 	pDListMgr 	= pObjectMgr->GetObjectList(CURVE);
	//////////////////////////////////////////////////////////////////
	CDrCurve*	pDrCurve;
	int			index,nResult,nOut;
	CString		CurveID;
	///////////////////////// 
	if(m_pOut != NULL)
	{
		FreeMem(m_pOut);
		m_pOut = NULL;
	}	
	if(m_pOutWts != NULL)
	{
		FreeMemD(m_pOutWts);
		m_pOutWts = NULL;
	}	
	///////////////////////////////////////////////////////////////// XSection: S-dir
   	CurveID = m_CurveID_S[0];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);

	if(index<0)
		return -1;
	/////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	if(!pDrCurve)
		return -1;
	////////////////////////////////////// Set Curve Info	
	GetInfo_Curve(pDrCurve);
	/////////////////////////////////////////// PreProcess
	nResult = Pre_S_Direction(pDrCurve, 0, m_nOut_S);
	if(nResult<0)
		return -1;
	/////////////////////////////////////////// Reset S-Con
	Curve_S_Process();
	///////////////////////////////////////////////////////////////// SpinePath: T-dir
   	CurveID = m_CurveID_S[1];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(CURVE,CurveID,1);

	if(index<0)
		return -1;
	/////////////////////////////////////////////
	pDrCurve	= (CDrCurve*)(pDListMgr->GetObject(index));
	if(!pDrCurve)
		return -1;
//	////////////////////////////////////// Set Curve Info	
//	GetInfo_Curve(pDrCurve);
	/////////////////////////////////////////// PreProcess
	nOut	= pDrCurve->GetMaxOutPts_S();
	if(nOut != m_nOut_S)
	{
		AfxMessageBox("CMP_Loft2::Loft2\nCurve1 & Curve2 MisMatch\nnOut != m_nOut_S");
		return -1;
	}
	nResult = Pre_S_Direction(pDrCurve, 1, m_nOut_S);
	if(nResult<0)
		return -1;
	////////////////////////////////// Save PatchInfo
	m_nOut				= (((long)m_nOut_S)*((long)m_nOut_T) );				
	m_nOutCon			= (((long)m_nOut_SCon)*((long)m_nOut_TCon) );				
	m_nMaxPatchCNodes	= (int)m_nOutCon;
	/////////////////////////////////////////// Memory OutPts 
	m_pOut		= FixMem(m_nOutCon);
	m_pOutWts	= FixMemD(m_nOutCon);
	if( !m_pOut || !m_pOutWts )
	{
		AfxMessageBox("CMP_Loft2::Loft\nFixMem Failure!");
		return -1;
	}
	///////////////////////////////////////// Go Loft 
	nResult = GenerateCNodes();
	///////////////////////////////////////// Free InputCNodeMems
	int i;
	//////
    for(i=0;i<4;i++)
    {
    	if(m_pIn_S[i])
    	{
			FreeMem(m_pIn_S[i]);
			m_pIn_S[i] = NULL;
		}	
    	if(m_pInWts_S[i])
    	{
			FreeMemD(m_pInWts_S[i]);
			m_pInWts_S[i] = NULL;
		}	
	}	
	///////////////////////////////////////////////////////////// 
	if(nResult<0)	
		return -1;
	else	
		return 0;
	/////////////			 
}			

int CMP_Loft2::Pre_S_Direction(CDrCurve* pDrCurve,int i, int nOut_S)
{

	/////////////////////////////////////////////// Memory OutPts 
	m_pIn_S[i]		= FixMem(nOut_S);
	m_pInWts_S[i]	= FixMemD(nOut_S);
	if( !m_pIn_S[i] || !m_pInWts_S[i] )
	{
		AfxMessageBox("CMP_Duct::Duct\nFixMem Failure!");
		return -1;
	}
	/////////////////////////////////////////////// Generate Curve
	m_bBack = FALSE;
	if(m_CuLatch[i] == CL_BACKWARD)
		m_bBack = TRUE;
	FillMeshNodesCurve(pDrCurve, m_pIn_S[i], m_pInWts_S[i], nOut_S);
	///////////////
	return 0;

}

int CMP_Loft2::Curve_S_Process()
{
	int i;
	////////////////////////////////////// LINEAR BEZIER in S-direction
	m_nSegs_S			= 1;	// ALWAYS
	m_nOrder_S			= 2;	// ALWAYS
	m_CurveType_S		= CP_LINEAR;
	m_nOut_SCon			= m_nOut_S;
	m_nSegs_SCon		= m_nOut_SCon - 1;
	///////////
	if(m_bClosed_S)
	{
		m_nOut_SCon--;
	}
	/////////////////////////////////////
	m_nMaxPatchCNodes_S = m_nOut_SCon;
	/////////
	m_pNum_t_S			= new int[m_nSegs_SCon];
	for (i=0;i<m_nSegs_SCon;i++)
		m_pNum_t_S[i] = 1;
	////////////////////
	return 0;
}

int CMP_Loft2::GenerateCNodes()
{

	/////////////////////////////////////////////////////////
	//		RATIO business TAKEN CARE OF IN DLG_LOFT2
	//			SO MAKE RATIO = 1
	////////////////////////////////////////////// 
	double ratio	= 1.0;
	/////////////////////
	int nOut		= (int)m_nOutCon;  // for now
	////////////////////////////////////////////// generate Patch Pts
	CPA_Loft2	PA_Loft2;
	int nOutActual	= PA_Loft2.LoftCurves_2
			(
				(short)m_nSegs_TCon,//	subdivision value (interior spaces)
				ratio,					//  Output Last/Ist ratio in T_Direction
				(short)m_nOut_SCon,	//	number of input data points
				m_pIn_S[0],			//	input Start curve ControlPts
		      	m_pInWts_S[0],		//	cross section Wts 
				m_pIn_S[1],			//	input End curve ControlPts
		      	m_pInWts_S[1],		//	cross section Wts 
				m_pOut,				//	Output ControlPts array
				m_pOutWts			//	Output Wts array
			);	  
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else
		return 0;
												
}

void CMP_Loft2::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMP_Loft2:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMP_Loft2:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
