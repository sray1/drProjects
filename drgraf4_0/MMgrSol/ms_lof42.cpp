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
#include "dlg_SLof.h"
#include "MSolMgr.h"
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
//#include "PA_Loft2.h"
 
#include "MS_Lof42.h" 

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
IMPLEMENT_SERIAL(CMS_Lof42,CMI_GangS,1)
/////////////////////////////////////////////////////////////////////////////
CMS_Lof42::CMS_Lof42()
{
	m_PatSubType = PS_QUADRILAT;
	m_SolSubType = SS_HEXA;
}

CMS_Lof42::~CMS_Lof42()
{
}

int CMS_Lof42::SetInfoBase
				(
					CString&						SolidID,		
					CDrSolid*						pDrSolid,
					CDListMgr*						pPatchList,
					CList<PATCHLATCH,PATCHLATCH>*	pLatchList,
					CList<int,int>*					pElperSegList,
					double							Ratio,
					CView*							pView
				) 
{
	int index;
	////////////////////////////////////////////////////////// Dialog Info(Don't Display Dlg)
	CDlg_Loft_S Dlg;
	Dlg.m_SubType	= PS_QUADRILAT;
	////////////////////////////////////////////////// SolidID
	Dlg.m_PatchID	= SolidID;
	////////////////////////////////////////////////// PatchID
	if(pPatchList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Lof32::SetInfoBase\npPatchList->GetCount() != 1");
		return -1;
	}
	CDrPatch* pDrPatch	= (CDrPatch*)(pPatchList->GetObject(0) );
	///////////////////////////////// Detach (It is Reciprocated in SetInfoBase of Dlg)
	index				= pDrPatch->GetSolidList()->GetObjectIndex(pDrSolid);
	if(index>=0)
		pDrPatch->GetSolidList()->RemoveObject(index);
	///
	Dlg.m_CID_1	= pDrPatch->GetObjectID();
	///////////
	pDrPatch	= (CDrPatch*)(pPatchList->GetObject(1) );
	///////////////////////////////// Detach (It is Reciprocated in SetInfoBase of Dlg)
	index				= pDrPatch->GetSolidList()->GetObjectIndex(pDrSolid);
	if(index>=0)
		pDrPatch->GetSolidList()->RemoveObject(index);
	///
	Dlg.m_CID_2	= pDrPatch->GetObjectID();
	///////////
/*
	////////////////////////////////////////////////// Latch Edge No
	if(pLatchList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Xtrud::SetInfoBase\npLatchList->GetCount() != 1");
		return -1;
	}
	Dlg.m_Orient_1	= pLatchList->GetHead();
*/
	////////////////////////////////////////////////// Mesh
	if(pElperSegList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Xtrud::SetInfoBase\npElperSegList->GetCount() != 1");
		return -1;
	}
	Dlg.m_nMesh		= pElperSegList->GetHead();
	Dlg.m_Ratio		= Ratio;
	////////////////////////////////////////////////// Fill Info
	Dlg.SetInfoForDataBase(pDrSolid);
	////////////////////////////////////////////////// Do It
	int nResult = GoDoIt(pDrSolid);
	//////////////
	if(nResult<0)
		return -1;
	/////////////////////
	return 0;		 
}

int CMS_Lof42::GoDoIt(CDrSolid* pDrSolid) 
{

	//////////////////////////////////////////////////////////
	GetInfo(pDrSolid);
	m_pDrSolid = pDrSolid;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrSolid->GetCNodeList();	
	///////                    				// ControlNode Mesh
	Loft();
	////////////////////////
	m_SolidType = SO_TENSOR;
	////////////////////////
	if(InsertMeshInfo_Solid(FALSE)<0)		
		return -1;
	/////////////////////
	return 0;
}

CDrSolid* CMS_Lof42::GoDoIt() 
{
	//////////////////////////////////////////////////////////
	m_pDrSolid 		= GetInfo();       // PGen Dialog
	if(!m_pDrSolid)		// cancel
		return (CDrSolid*)NULL;
	//////////////////////////////////	
	m_pCNodeList 	= m_pDrSolid->GetCNodeList();	
	///////                    				// ControlNode Mesh
	Loft();
	////////////////////////
	m_SolidType = SO_TENSOR;
	////////////////////////
	if(InsertMeshInfo_Solid(FALSE)<0)		// WE HAVE CHANGED TO FALSE
											// TO SAVE ALL CONTROL NODES
		return (CDrSolid*)NULL;
	/////////////////////
	return m_pDrSolid;
}			

CDrSolid* CMS_Lof42::GetInfo()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CDListMgr* pDListMgr 	= pObjectMgr->GetObjectList(SOLID);
	//////////////////////////////////////////////////////////////////
	CMSolMgr 	MSolMgr;
	CMSolMgr* 	pMSolMgr = &MSolMgr;
	CString		Cid;
	int 		index;
	///////////////////////////////////////////////////
	if (pMSolMgr->DoModal_Solid_Loft(&Cid,PS_QUADRILAT) == IDCANCEL)
			return (CDrSolid*)NULL;
    /////////////////////////////////////////////////////// update
	m_CurrentSolidID 	= Cid;
	index 				= pObjectMgr->
							GetObjectIndexfromKey(SOLID,Cid,1);
	if(index>=0)
	{						
		CDrSolid* pDrSolid	= (CDrSolid*)(pDListMgr->GetObject(index));
   		//////////////////////////////
		m_SolidProc		= pDrSolid->GetSolidProc();
		m_pNum_t_R		= pDrSolid->GetNum_tPointer_R();
		m_pDis_t_R		= pDrSolid->GetDis_tPointer_R();
		m_CurveID_S[0]	= pDrSolid->GetPatchID(0);
		m_CurveID_S[1]	= pDrSolid->GetPatchID(1);
		////////////////////////////////////////////////
		m_nSegs_R		= pDrSolid->GetMaxBezSegments_R();	//segs in Extrusion dirn
		m_Ratio			= pDrSolid->GetRatio_R();
		m_bUnifOT		= pDrSolid->IsUniform_R();
		m_nOut_R		= pDrSolid->GetMaxOutPts_R();
		m_nOrder_R		= pDrSolid->GetOrder_R();
		m_CurveType_R	= pDrSolid->GetCurveType_R();
		m_nDim_R		= pDrSolid->GetnDim_R();
		m_bClosed_R		= pDrSolid->IsClosed_R();					// for Extrusion
		///////////////////////////////////////// Bezier Linear
		if(m_bUnifOT)
			m_nOut_RCon	= 2;// Only One Patch in T-dir
		else
//4/26/96			m_nOut_RCon	= pDrSolid->GetMaxOutSeg_R()+1;	// Number of Output Segments
			m_nOut_RCon	= m_nSegs_R+1;	// Number of Output Segments
		/////////////////////////////////////
		m_nSegs_RCon		= m_nOut_RCon - 1;
		m_nMaxSolidCNodes_R = m_nOut_RCon;
		////////////////
		return pDrSolid;
	}
	else
		return (CDrSolid*)NULL;
}			

int CMS_Lof42::GetInfo(CDrSolid* pDrSolid)
{
	//////////////////////////////
	m_SolidProc		= pDrSolid->GetSolidProc();
	m_pNum_t_R		= pDrSolid->GetNum_tPointer_R();
	m_pDis_t_R		= pDrSolid->GetDis_tPointer_R();
	m_CurveID_S[0]	= pDrSolid->GetPatchID(0);
	m_CurveID_S[1]	= pDrSolid->GetPatchID(1);
	////////////////////////////////////////////////
	m_nSegs_R		= pDrSolid->GetMaxBezSegments_R();	//segs in Extrusion dirn
	m_Ratio			= pDrSolid->GetRatio_R();
	m_bUnifOT		= pDrSolid->IsUniform_R();
	m_nOut_R		= pDrSolid->GetMaxOutPts_R();
	m_nOrder_R		= pDrSolid->GetOrder_R();
	m_CurveType_R	= pDrSolid->GetCurveType_R();
	m_nDim_R		= pDrSolid->GetnDim_R();
	m_bClosed_R		= pDrSolid->IsClosed_R();					// for Extrusion
	///////////////////////////////////////// Bezier Linear
	if(m_bUnifOT)
		m_nOut_RCon	= 2;// Only One Patch in T-dir
	else
//4/26/96			m_nOut_RCon	= pDrSolid->GetMaxOutSeg_R()+1;	// Number of Output Segments
		m_nOut_RCon	= m_nSegs_R+1;	// Number of Output Segments
	/////////////////////////////////////
	m_nSegs_RCon		= m_nOut_RCon - 1;
	m_nMaxSolidCNodes_R = m_nOut_RCon;
	////////////////
	return 0;
}			

int CMS_Lof42::Loft()
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
	CDListMgr* 	pDListMgr;
	//////////////////////////////////////////////////////////////////
	CDrPatch*	pDrPatch;
	int			index,nResult,nOut_ST;
	CString		PatchID;
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
   	PatchID = m_CurveID_S[0];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(PATCH,PatchID,1);
	if(index<0)
	{
		AfxMessageBox("CMS_Lof42::Loft\nPatchIndex Failure!");
		return -1;
	}
	/////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
	if(!pDrPatch)
		return -1;
	////////////////////////////////////// Set Curve Info	
	GetInfo_Patch(pDrPatch);
	/////////////////////////////////////////// PreProcess
	nResult = Pre_ST_Direction(pDrPatch, 0, m_nOut_ST);
	if(nResult<0)
		return -1;
	/////////////////////////////////////////// Reset S-Con
	Patch_ST_Process();
	///////////////////////////////////////////////////////////////// SpinePath: T-dir
   	PatchID = m_CurveID_S[1];
	//////////////////////////////////////// get Curve Info	
	index	= pObjectMgr->
					GetObjectIndexfromKey(PATCH,PatchID,1);
	if(index<0)
	{
		AfxMessageBox("CMS_Lof42::Loft\nPatchIndex Failure!");
		return -1;
	}
	/////////////////////////////////////////////
	pDListMgr 	= pObjectMgr->GetObjectList(PATCH);
	pDrPatch	= (CDrPatch*)(pDListMgr->GetObject(index));
	if(!pDrPatch)
		return -1;
//	////////////////////////////////////// Set Curve Info	
//	GetInfo_Curve(pDrCurve);
	/////////////////////////////////////////// PreProcess
	nOut_ST	= pDrPatch->GetOut_S() * pDrPatch->GetOut_T();
	if(nOut_ST != m_nOut_ST)
	{
		AfxMessageBox("CMP_Loft2::Loft2\nPatch1 & Patch2 MisMatch\nnOut != m_nOut_ST");
		return -1;
	}
	nResult = Pre_ST_Direction(pDrPatch, 1, m_nOut_ST);
	if(nResult<0)
		return -1;
	////////////////////////////////// Save PatchInfo
	m_nOut				= (((long)m_nOut_ST)*((long)m_nOut_R) );				
	m_nOutCon			= (((long)m_nOut_STCon)*((long)m_nOut_RCon) );				
	m_nMaxSolidCNodes	= (int)m_nOutCon;
	/////////////////////////////////////////// Memory OutPts 
	m_pOut		= FixMem(m_nOutCon);
	m_pOutWts	= FixMemD(m_nOutCon);
	if( !m_pOut || !m_pOutWts )
	{
		AfxMessageBox("CMS_Lof42::Loft\nFixMem Failure!");
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

int CMS_Lof42::Pre_ST_Direction(CDrPatch* pDrPatch,int i, int nOut_S)
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
	FillMeshNodesPatch(pDrPatch, m_pIn_S[i], m_pInWts_S[i] );
	///////////////
	return 0;

}

int CMS_Lof42::Patch_ST_Process()
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
	m_nMaxSolidCNodes_S = m_nOut_SCon;
	/////////
	m_pNum_t_S			= new int[m_nSegs_SCon];
	m_pDis_t_S			= new double[m_nSegs_SCon+1];
	for (i=0;i<m_nSegs_SCon;i++)
	{
		m_pNum_t_S[i]	= 1;
		m_pDis_t_S[i]	= 0.0;
	}
	/////////////////////
	m_pDis_t_S[m_nSegs_SCon] = 1.;
	////////////////////////////////////// LINEAR BEZIER in T-direction
	m_nSegs_T			= 1;	// ALWAYS
	m_nOrder_T			= 2;	// ALWAYS
	m_CurveType_T		= CP_LINEAR;
	m_nOut_TCon			= m_nOut_T;
	m_nSegs_TCon		= m_nOut_TCon - 1;
	///////////
	if(m_bClosed_T)
	{
		m_nOut_TCon--;
	}
	/////////////////////////////////////
	m_nMaxSolidCNodes_T = m_nOut_TCon;
	/////////
	m_pNum_t_T			= new int[m_nSegs_TCon];
	m_pDis_t_T			= new double[m_nSegs_TCon+1];
	for (i=0;i<m_nSegs_TCon;i++)
	{
		m_pNum_t_T[i]	= 1;
		m_pDis_t_T[i]	= 0.0;
	}
	/////////////////////
	m_pDis_t_T[m_nSegs_TCon] = 1.;
	////////////////////////////////// Total ST Controls
	m_nMaxSolidCNodes_ST 	= m_nMaxSolidCNodes_S * m_nMaxSolidCNodes_T;
	m_nOut_STCon			= (int)m_nMaxSolidCNodes_ST;
	////////////
	return 0;
}

int CMS_Lof42::GenerateCNodes()
{
	/////////////////////////////////////////////////////////
	//		RATIO business TAKEN CARE OF IN DLG_SXTR
	//			SO MAKE RATIO = 1
	////////////////////////////////////////////// 
	double ratio	= 1.0;
	/////////////////////
	int nOut		= (int)m_nOutCon;  // for now
/*
	////////////////////////////////////////////// generate Patch Pts
	CPA_Loft2	PA_Loft2;
	int nOutActual	= PA_Loft2.LoftCurves_2
			(
				(short)m_nSegs_RCon,//	subdivision value (interior spaces)
				ratio,				//  Output Last/Ist ratio in T_Direction
				(short)m_nOut_STCon,//	number of input data points
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
*/
		return 0;
												
}

void CMS_Lof42::Serialize(CArchive& ar)
{

	CMI_GangS::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMS_Lof42:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMS_Lof42:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
