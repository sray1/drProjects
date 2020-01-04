// Loft2.cpp : implementation file
//
///////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"
#include <Float.h>		// MSVC/INC for DBL_MAX,DBL_MIN

#include "Def_Objs.h"
//////////////////// 
#include "3dMath.h" 
#include "MsMath.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Def_MouseAct.h"
#include "DegElevate.h"
///////////////////// dialogMgr
#include "MPatMgr.h"
#include "dlg_LoftX.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "Str_BlendEnd.h"
#include "Str_CuPS.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "HitNet.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
#include "MC_Circle.h"
#include "MC_Parab.h"
/////////////////////
#include "PA_Sweep.h" 
#include "MP_Sweep.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#define MAGENTA		RGB(255,0,255)	// Jn. Curve Color
#define	new			DEBUG_NEW
#define	BUFF_SIZE	1024
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMP_Sweep,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMP_Sweep::CMP_Sweep()
{
}

CMP_Sweep::~CMP_Sweep()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
int CMP_Sweep::GoDoIt 
				(
					BOOL							bGenBCurve,
					int								nTwistType,
									// 1 = Given: Twist Distribution
									// 2 = Given: Twist Increments etc
					int								nScaleType,
									// 1 = Given: Scale Distribution
									// 2 = Given: Scale Increments etc
					//////////////////////////////////////////
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					//////////////////////////////////////////
					CDListMgr*						pNodeList,	// One record: Anchor Node
					//////////////////////////////////////////
					CDListMgr*						pCurveList,	// 1: XSection Curve
																// 2: Spine Curve
					CList<CURVELATCH,CURVELATCH>*	pLatchList,
					//////////////////////////////////////////
					CList<double,double>*			pTwistList,	// Distrib,if nTwistType = 1
					double							TwistMult,	// if nTwistType = 2 
					BOOL							bIncrement,
					double							TwistStart,
					//////////////////////////////////////////
					CList<double,double>*			pScaleList,	// Distrib,if nScaleType = 1
					double							ScaleMult,			// if nScaleType = 2 
					BOOL							bIncScale,
					double							ScaleStart,
					//////////////////////////////////////////////
					CView*							pView
				) 
{
	m_nTwistType	= nTwistType;
	m_nScaleType	= nScaleType;
	/////////////////////////////
	int i;
	POSITION pos;
	//////////////////////////////////////////////////////////
	int nResult = MA_OK;
	//////////////////////////
	if(!IsDataCompatible(pCurveList,pNodeList,pLatchList,pTwistList,m_nTwistType) )
		return MA_ERROR;
	//////////////////////////////////////////////////////////
	m_PatchID		= PatchID;
	m_pDrPatch		= pDrPatch;
	m_pDrPatch->SetObjectID(PatchID);
	/////////////////////////////////
	CDrCurve* pCurve;
	CURVELATCH cLatch;
	////////////////////////////////////////////////////////// S_dir: XSection Curve
	pCurve	= (CDrCurve*)pCurveList->GetHead();
	cLatch	= pLatchList->GetHead();
	//////////////////////////////////////////
	SetPatchDataFromCurve(pCurve,1/*nDir*/);
	////////////////////////////////////////// get Old 
	pWORLD pConBZ_S		= new WORLD[m_nMaxPatchCNodes_S];
	pDOUBLE pWtsBZ_S	= new double[m_nMaxPatchCNodes_S];
	///
	GetCNodeCoords_N_Wts_XSection(pCurve, cLatch, pConBZ_S, pWtsBZ_S);
	////////////////////////////////////////////////////////// T-dir: Spine Curve
	pCurve	= (CDrCurve*)pCurveList->GetTail();
	cLatch	= pLatchList->GetTail();
	//////////////////////////////////////////
	SetPatchDataFromCurve(pCurve,2/*nDir*/);
	////////////////////////////////////////////////////// CNs & Wts at Jn. Pts 
	int nConBZJn_T		= (m_bClosed_T)?m_nSegs_T:m_nSegs_T+1; 
	pWORLD pConBZ_T		= new WORLD[nConBZJn_T];
	pDOUBLE pWtsBZ_T	= new double[nConBZJn_T];
	///
	GetCNodeCoords_N_WtsAtJnPts_Spine(pCurve, cLatch, pConBZ_T, pWtsBZ_T);
	////////////////////////////////////////////////////////// T-dir: Tangents at Bez, Jn. Pts
	pWORLD pTanBZ_T		= new WORLD[m_nMaxPatchCNodes_T];
	///
	nResult = CreateTangentsAtJnPts_Spine(pCurve,cLatch,pTanBZ_T);
	////////////////////////////////////////////////////////// T-dir: Twist Info
	m_TwistMult		= TwistMult;
	m_bIncrement	= bIncrement;
	m_TwistStart	= TwistStart;
	////////////
	int nTwists		= pTwistList->GetCount();
	pDOUBLE pTwist	= new double[nTwists];
	for(i=0;i<nTwists;i++)
	{
		pos			= pTwistList->FindIndex(i);
		pTwist[i]	= pTwistList->GetAt(pos);
	}
	///
	TwistProcess(pTwist, nTwists,m_TwistMult,m_TwistStart,m_bIncrement);
	////////////////////////////////////////////////////////// T-dir: Scale Info
	m_ScaleMult		= ScaleMult;
	m_bIncScale		= bIncScale;
	m_ScaleStart	= ScaleStart;
	////////////
	int nScales		= pScaleList->GetCount();
	pDOUBLE pScale	= new double[nScales];
	for(i=0;i<nScales;i++)
	{
		pos			= pScaleList->FindIndex(i);
		pScale[i]	= pScaleList->GetAt(pos);
	}
	///
	ScaleProcess(pScale, nScales,m_ScaleMult,m_bIncScale,m_bIncrement);
    ////////////////////////////////////////////////////////// Anchor Node Coords.
	m_pFromIDNode	= (CDrNode*)(pNodeList->GetObject(0) );
	////////////////////////
    UnitAxisFromEndNodes(1);	// creates m_FromPt
	/////////////////////////////////////////////////////////////////////////////// Duct: Bez Jn CN Pts
	int nTotConsJn_T	= m_nMaxPatchCNodes_S*nConBZJn_T; 
	pWORLD pPatConsJn	= new WORLD[nTotConsJn_T];
	pDOUBLE pPatWtsJn	= new double[nTotConsJn_T];
	////////////////////////////////////////////////////////// 
	PatCNCoords_N_WtsAtJns(m_FromPt,
					pConBZ_S,pWtsBZ_S,m_nMaxPatchCNodes_S,
					pConBZ_T,pTanBZ_T,nConBZJn_T,
					pTwist,pScale,pPatConsJn,pPatWtsJn,nTotConsJn_T);
	/////////////////////////////////////////////////////////////////////////////// PostPatchData
	// Bez.Jn.Pts along Spine are Known; the interior BezPts. are obtained by Lofting
	// using SpineCurve as the Blending Curve for All CNodes of the XSectional Curve
	nResult = PostPatBezInfoUsingBlendingInfo(pDrPatch,pCurve/*SpineCurve*/,
					pPatConsJn,pPatWtsJn,m_nMaxPatchCNodes_S,nConBZJn_T/*nCurves*/,
					m_nMaxPatchCNodes_T);
	/////////////////// release memory
	delete [] pConBZ_S;
	delete [] pWtsBZ_S;
	delete [] pConBZ_T;
	delete [] pWtsBZ_T;
	delete [] pTanBZ_T;
	delete [] pTwist;
	delete [] pScale;
	delete [] pPatConsJn;
	delete [] pPatWtsJn;
	/////////////////////////////////////////////////////////////////////////////// Patch Bndry Curves
	CDListMgr						CurveList_U;
	CDListMgr*						pCurveList_U = &CurveList_U;
	pCurveList_U->RemoveAll();
	///
	CList<CURVELATCH,CURVELATCH>	LatchList_U;
	CList<CURVELATCH,CURVELATCH>*	pLatchList_U = &LatchList_U;
	///
	CDListMgr						CurveList_V;
	CDListMgr*						pCurveList_V = &CurveList_V;
	pCurveList_V->RemoveAll();
	///
	CList<CURVELATCH,CURVELATCH>	LatchList_V;
	CList<CURVELATCH,CURVELATCH>*	pLatchList_V = &LatchList_V;
	////////////////////////////////////////////////////////////////////////////// 
	// Distribute XSec & Spine Curves
	////////////////////////////////////////////////// XSection Curve
	pCurveList_U->InsertObject(pCurveList->GetHead());
	pLatchList_U->AddTail(pLatchList->GetHead());
	////////////////////////////////////////////////// Spine Curve
	pCurveList_V->InsertObject(pCurveList->GetTail());
	pLatchList_V->AddTail(pLatchList->GetTail());
	//////////////////////////////////
	m_PatchType	= PA_TENSOR;
	nResult = SetInfoForDataBase(pDrPatch,
					pCurveList_U,pCurveList_V,
					pLatchList_U,pLatchList_V,pTwistList,pScaleList);
	/////////////////////////////////////////////////////////////////////////////// Done
	pCurveList_U->RemoveAll();
	pCurveList_V->RemoveAll();
	pLatchList_U->RemoveAll();
	pLatchList_V->RemoveAll();
	////////////////////////////////////////////////////////////////////////////// Bndry Curves
	m_bGenBCur = bGenBCurve;
	if(bGenBCurve)
	{
		////////////////////////////////////////////////// Create LatticeCurves_U
														// at Bez. JnPts. Only
		pCurve = (CDrCurve*)pCurveList->GetHead(); //patterned after XSection Curve 
		nResult = LatticeCurves_U(pDrPatch,m_nOrder_T,m_bClosed_T,m_nSegs_T,
												m_nMaxPatchCNodes_S,pCurve);
		if(nResult == MA_ERROR)
			return nResult;
		////////////////////////////////////////////////// Create LatticeCurves_V
														// at Bez. JnPts. Only	
		pCurve = (CDrCurve*)pCurveList->GetTail(); //patterned after Spine Curve 
		nResult = LatticeCurves_V(pDrPatch,m_nOrder_S,m_bClosed_S,m_nSegs_S,
							m_nMaxPatchCNodes_S,m_nMaxPatchCNodes_T,pCurve);
		if(nResult == MA_ERROR)
			return nResult;
	}
	//////////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
BOOL CMP_Sweep::IsDataCompatible(CDListMgr* pCurveList,CDListMgr* pNodeList,
								CList<CURVELATCH,CURVELATCH>*	pLatchList,
								CList<double,double>* pTwistList,int nTwistType)
{
	////////////////////////////////////////////////// CurveID
	if(pCurveList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Sweep::IsDataCompatible\npCurveList->GetCount() != 2");
		return FALSE;
	}
	////////////////////////////////////////////////// Latch
	if(pLatchList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Sweep::IsDataCompatible\npLatchList->GetCount() != 2");
		return FALSE;
	}
	CDrCurve* pDrCurve	= (CDrCurve*)(pCurveList->GetObject(0) );
	////////////////////////////////////////////////// # of Twist Data
	if(nTwistType == 1)
	{
		CDrCurve* pSpineCurve	= (CDrCurve*)pCurveList->GetTail();
		CDListMgr* pCNList		= pSpineCurve->GetCNodeList();
		BOOL bClosed			= pSpineCurve->IsClosed_S();
		int	nBZSegs				= pSpineCurve->GetMaxBezSegments_S();
		int nMaxTwist			= (bClosed)?nBZSegs:nBZSegs+1; 
		/////////////
		if(pTwistList->GetCount() != nMaxTwist)
		{
			AfxMessageBox(
				"INTERNAL PROBLEM:\nCMP_Sweep::IsDataCompatible\npTwistList->GetCount() != nCNs");
			return FALSE;
		}
	}
	////////////////////////////////////////////////// FromNodeID & ToNodeID 
	if(pNodeList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Sweep::IsDataCompatible\npNodeList->GetCount() != 1");
		return FALSE;
	}
	///////////
	return TRUE;
}

int CMP_Sweep::TwistProcess(pDOUBLE pTwist, int nTwist, double dScaleMax, double dTwistStart,
																		BOOL bIncremental)
{
	int		i;
	////////////////////////////
	pDOUBLE p = pTwist;
	///////////////////////////////////////////////// Incremental
	if(bIncremental)
	{
		double dInc = dScaleMax; // could be +ve or -ve
		*p = dTwistStart;
		///////////
		for(i=1;i<nTwist;i++)
			*(p+i) = *(p+i-1) + dInc;
		/////////
		return MA_OK;
	}
	////////////
	return MA_OK;

}

int CMP_Sweep::ScaleProcess(pDOUBLE pTwist, int nTwist, double dScaleMax, double dTwistStart,
																		BOOL bIncremental)
{
	int		i;
	////////////////////////////
	pDOUBLE p = pTwist;
	///////////////////////////////////////////////// Incremental
	if(bIncremental)
	{
		double dInc = dScaleMax; // could be +ve or -ve
		*p = dTwistStart;
		///////////
		for(i=1;i<nTwist;i++)
			*(p+i) = *(p+i-1) + dInc;
		/////////
		return MA_OK;
	}
	////////////
	return MA_OK;

}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMP_Sweep::SetPatchDataFromCurve(CDrCurve* pCurve,int nDir)
{
	int i;
	pINT	pNum_t_T;
	pDOUBLE	pDis_t_T;
	///////
	if(nDir == 2)
	{
		pNum_t_T		= pCurve->GetNum_tPointer_S();
		pDis_t_T		= pCurve->GetDis_tPointer_S();
		///
		m_nSegs_T		= pCurve->GetMaxBezSegments_S();
		m_nOut_T		= (int)pCurve->GetLongOutPts();
		///
		if(pNum_t_T)
			m_pNum_t_T		= new int[m_nSegs_T];
		if(pDis_t_T)
			m_pDis_t_T		= new double[m_nOut_T];
	}
	/////////////
	switch(nDir)
	{
		case 1:
			m_bClosed_S			= pCurve->IsClosed_S();
//			m_nDim_S			= pCurve->GetnDim_S();
			m_nDim_S			= 4;	// ALWAYS Rational;
			m_nOrder_S			= pCurve->GetOrder_S();
			m_nMaxPatchCNodes_S	= pCurve->GetMaxCNodes_S();
			m_nSegs_S 			= pCurve->GetMaxBezSegments_S();
			m_CurveType_S		= pCurve->GetCurveType_S();
			///
			m_nOut_S			= (int)pCurve->GetLongOutPts();
			m_nMaxOSeg_S		= pCurve->GetOutSegUnif_S();
			m_bUnifOT_S			= pCurve->IsUniform_S();
			m_pNum_t_S			= pCurve->GetNum_tPointer_S();
			m_pDis_t_S			= pCurve->GetDis_tPointer_S();
			////////
			return MA_OK;

		case 2:
			m_bClosed_T			= pCurve->IsClosed_S();
//			m_nDim_T			= pCurve->GetnDim_S();
			m_nDim_T			= 4;	// ALWAYS Rational;
			m_nOrder_T			= pCurve->GetOrder_S();
			m_nMaxPatchCNodes_T	= pCurve->GetMaxCNodes_S();
			m_nSegs_T 			= pCurve->GetMaxBezSegments_S();
			m_CurveType_T		= pCurve->GetCurveType_S();
			///
			m_Ratio_T			= pCurve->GetRatio_S();
			m_nOut_T			= (int)pCurve->GetLongOutPts();
			m_nMaxOSeg_T		= pCurve->GetOutSegUnif_S();
			m_bUnifOT_T			= pCurve->IsUniform_S();
			//////////////////////////////////////////////////
			for (i=0;i<m_nSegs_T;i++)
			{
				if(pNum_t_T)
					m_pNum_t_T[i]		= pNum_t_T[i];
			}
			for (i=0;i<m_nOut_T;i++)
			{
				if(pDis_t_T)
					m_pDis_t_T[i]		= pDis_t_T[i];
			}
			////////
			return MA_OK;

		default:
			return MA_ERROR;
	}
}

int CMP_Sweep::GetCNodeCoords_N_Wts_XSection(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld)
{
	// Create CNs & Wts at All Control Nodes
	////////////////////////////////////////
	int nResult = MA_OK;
	////////////////////////////////////////////////////
	int			i=-1;
	CDrNode*	pCNode;
	CDListMgr* pList	= pCurve->GetCNodeList();
	pDOUBLE pWts		= pCurve->GetpWts_BZ_S();
	////////////////////////////////////////////////////////////////////////// tan_ALL at Jn. CNodes
	int	nLastCNIndex	= pCurve->GetCNodeList()->GetCount() - 1;
	/////////////////////////////////////////////////////////////// Coords 
	if(!pList->IsEmpty())
	{
		////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			i++;
			////
			pCNode	= (CDrNode*)pList->GetNextObject(pos);
			///////////////////////////////////////
			if(cLatch == CL_FORWARD)
			{
				pConOld[i] = *(pCNode->GetLocalPos());
				pWtsOld[i] = pWts[i];
			}
			else
			if(cLatch == CL_BACKWARD)
			{
				pConOld[nLastCNIndex - i] = *(pCNode->GetLocalPos());
				pWtsOld[nLastCNIndex - i] = pWts[i];
			}
			//////////////////////////////////
		}
	}
	/////////////
	return MA_OK;
}
//////////////////////////////////////////////////////////////////////////////////////
int CMP_Sweep::GetCNodeCoords_N_WtsAtJnPts_Spine(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld)
{
	// Create CNs & Wts at Jn. Control Nodes
	////////////////////////////////////////
	int nResult = MA_OK;
	////////////////////////////////////////////////////
	int			i=-1,index;
	CDrNode*	pCNode;
	double		pWtsJn;
	CDListMgr* pList	= pCurve->GetCNodeList();
	pDOUBLE pWts		= pCurve->GetpWts_BZ_S();
	////////////////////////////////////////////////////////////////////////// tan_ALL at Jn. CNodes
	BOOL		bClosed	= pCurve->IsClosed_S();
	int			nConBZ	= pCurve->GetCNodeList()->GetCount();
	int			nDegree	= pCurve->GetOrder_S()-1;
	int			nBezSeg	= pCurve->GetMaxBezSegments_S();
	///////////
	int			nLastJnIndex = (bClosed)?nBezSeg-1:nBezSeg;
	index = -1;
	/////////////////////////////////////////////////////////////// Coords 
	if(!pList->IsEmpty())
	{
		////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			i++;
			////
			pCNode	= (CDrNode*)pList->GetNextObject(pos);
			pWtsJn	= pWts[i];
			//
			if(i%nDegree !=0)
				continue;
			///////////////////////////////////////
			index++;
			if(cLatch == CL_FORWARD)
			{
				pConOld[index] = *(pCNode->GetLocalPos());
				pWtsOld[index] = pWtsJn;
			}
			else
			if(cLatch == CL_BACKWARD)
			{
				pConOld[nLastJnIndex - index] = *(pCNode->GetLocalPos());
				pWtsOld[nLastJnIndex - index] = pWtsJn;
			}
			//////////////////////////////////
		}
	}
	/////////
	return 0;
}

int CMP_Sweep::CreateTangentsAtJnPts_Spine(CDrCurve* pCurve,CURVELATCH cLatch,pWORLD pTangents)
{
	// Create Tangents at Jn. Control Nodes
	///////////////////////////////////////
	int nResult = MA_OK;
	////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	///////////////////////////////////////////////
	C3DMath		Math3D;
	CDrNode*	pCNode;
	WORLD		wNodeCoord;
	WORLD		tan;
	int			i=-1,index,nSavIndex;
	////////////////////////////////////////////////////////////////////////// tan_ALL at Jn. CNodes
	BOOL		bClosed	= pCurve->IsClosed_S();
	int			nConBZ	= pCurve->GetCNodeList()->GetCount();
	int			nDegree	= pCurve->GetOrder_S()-1;
	int			nBezSeg	= pCurve->GetMaxBezSegments_S();
	pDOUBLE		Knot	= pCurve->GetpKnots_S();
	///////////
	int			nLastJnIndex = (bClosed)?nBezSeg-1:nBezSeg;
	index = -1;
	///////////
	CDListMgr* pList = pCurve->GetCNodeList();
	for (POSITION pos = pList->GetHeadPosition();pos !=NULL;)
	{
		i++;
		pCNode	= (CDrNode*)(pList->GetNext(pos));
		//
		if(i%nDegree !=0)
			continue;
		/////////////////
		wNodeCoord	= *(pCNode->GetLocalPos());
		pCurve->Get_TangentAtaNode(wNodeCoord,tan,pHitNet->GetDblRatio());	// At Jn. Pt
		/////////////////////////////////////////// Scale by deltaKnot[i] = Knot[i+1]-Knot[i]
		index++;
		nSavIndex = index;
		if(index == nLastJnIndex)	// Last CN
			index--;
		/////////////////////////////////////
		double deltaKnot; 
		if(bClosed)
			deltaKnot = Knot[(index+1)%nConBZ]-Knot[index];
		else
			deltaKnot = Knot[index+1]-Knot[index];
		///
		Math3D.Scale3DPts(1./deltaKnot, &tan);
		/////////////////////////////////////////// save
		if(cLatch == CL_FORWARD)
			pTangents[nSavIndex] = tan;
		else
		if(cLatch == CL_BACKWARD)
			pTangents[nConBZ-1-nSavIndex] = tan;
		///////////////
	}
	/////////////
	return MA_OK;
}

int CMP_Sweep::PatCNCoords_N_WtsAtJns(WORLD wAnchorPt,pWORLD pConBZ_S,pDOUBLE pWtsBZ_S,int nConBZ_S,
						pWORLD pConBZ_T,pWORLD pTanBZ_T,int nConBZ_T,pDOUBLE pTwist,
						pDOUBLE pScale,pWORLD pPatCons,pDOUBLE pPatWts,int nTotOut)
{
	////////////////////////////////////////////// generate Patch Pts
	CPA_Sweep	PA_Sweep;		 	   	
	int nOutActual	= PA_Sweep.Sweep
			(
				wAnchorPt,		//	Anchor 3D Pt. for Xsec scale,twist etc
		    	nConBZ_S,		//	number of cross section points
		      	pConBZ_S,		//	cross section curve ControlPts
		      	pWtsBZ_S,		//	cross section Wts 
		   		nConBZ_T,		//	number of Spine points
		      	pConBZ_T,		//	Spine curve ControlPts
		      	pTanBZ_T,		//	Spine curve Tangents at ControlPts
		      	pTwist,			//	path Twist Factor distribution
		      	pScale,			//	path Scale Factor distribution
				pPatCons,		//	Output ControlPts
				pPatWts			//	Output Wts array
			);	  
	////////////////////////////	
	if(nOutActual != nConBZ_S*nConBZ_T)
		return -1;
	else 
		return 0;
												
}

int CMP_Sweep::PostPatBezInfoUsingBlendingInfo(CDrPatch* pPatch,CDrCurve* pSpineCurve,
												pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ,
																int nCurves,int nCon_T)
{
	// Blend Curve is the Spine Curve
	/////////////////////////////////
	// Curves in S-dir and Blend Curve in T-dir
	// So, Transpose & Correctly Post Bezier Info	
	/////////////////////////////////////////////////////////////////////////////// Spine Curve
	// Blend Curve Contains T-directional Info:
	//			CurveType
	//			IsClosed
	CList<int,int>* pElSegList	= pSpineCurve->GetElperSegList_S();
	CList<int,int> ElSegList_T;
	ElSegList_T.AddTail(pElSegList);
	//
	double Ratio_T				= pSpineCurve->GetRatio_S();
	BOOL bClosed_T				= pSpineCurve->IsClosed_S();						 
	BOOL nDegree_T				= pSpineCurve->GetOrder_S() - 1;						 
	//////////////////////////////////////////////////////// BlendEnd
	BLENDEND BlendEnd;
	//////////////////
	BlendEnd.m_BCL	= pSpineCurve->GetBCL_S();
	BlendEnd.m_BCR	= pSpineCurve->GetBCR_S();
	BlendEnd.m_TanL	= pSpineCurve->GetTanL_S();
	BlendEnd.m_TanR	= pSpineCurve->GetTanR_S();
	////////////////////////////////////////////////////////////////////////////////
	int i;
	CDListMgr	INodeList;
	CDListMgr	TemCNodeList;	// temporarily store Patch BezPts( may be undesirable
								// Order, to be corrected at the end of this routine
	//////////////////////////////////////////////////////// Wts
	int nCon_S;
	nCon_S					= nConBZ;
	///
//	nBezSeg_T				= (bClosed_T)?nCurves:nCurves-1;
//	nCon_T					= (bClosed_T)?(nDegree_T*nBezSeg_T):(nDegree_T*nBezSeg_T+1);
	pDOUBLE	pTemPatWts_BZ	= new double[nCon_S*nCon_T];
	CString PatchID			= pPatch->GetObjectID();
	//////////////////////////////////////////////////////// Loop Over Bez. Pts. on Curves
	for(i=0;i<nCon_S;i++)
	{
		//////////////////////////////////////////////////// Input Nodes 
		// Post temporarily Patch Bezier Junction CNodes as INodes
		// these will be deleted when temporary Curve in
		// GeneratePatchBezInfoFromBlendCurve SubRoutine is deleted
		// Similarly,pTemWts_DT
		///////////////////////
		INodeList.RemoveAll();
		TempPostPatBezJunctionPtsInINodeList(pConBZ,nConBZ,i,nCurves,&INodeList);
		//////////////////////////////////////////////////// Input Weight
		pDOUBLE	pTemWts_DT = new double[nCurves];		
		PackPatBezJunctionWtsInDataWtsArray(pWtsBZ,nConBZ,i,nCurves,pTemWts_DT);
		//////////////////////////////////////////////////// Now Generate
		GeneratePatchBezInfoFromSpineCurve(BlendEnd,pSpineCurve,&INodeList,
				pTemWts_DT,ElSegList_T,&TemCNodeList,pTemPatWts_BZ,Ratio_T,PatchID,nCon_T,i);
		///
	}
	////////////////////////////////////////////////////////////////////////// Post
	// Curve along S-direction, So Transpose
	{
		PostPatBezInfo(pPatch,TemCNodeList,pTemPatWts_BZ,nCon_S,nCon_T);
		////////////////////////////// now remove from TemporaryList
		TemCNodeList.RemoveAll();
		////////////////////////////// delete
		delete [] pTemPatWts_BZ;
	}
	//////////////
	return MA_OK;
}

int CMP_Sweep::PostPatBezInfo(CDrPatch* pPatch,CDListMgr& TemCNodeList,pDOUBLE pTemPatWts_BZ,
																		int nCon_S,int nCon_T)
{
	//////////////////////////////////////////////////////// Transpose BezPts & Wts to match UV dirs
	// REMEMBER: C,C++ SAVES ROWWISE
	////////////////////////////////
	// would like to save:
	//		v-dir(Col)
	//		00000<-nCon_T of them (Based on # of Curves)
	//  u-	11111 
	//	d	22222 
	//	i	33333 
	//	r	44444 
	//(row)	55555 
	//		66666 
	//		77777 
	//			^
	//			|
	//		   nCon_S of them 
	////////////////////////////////
	// but currently saved as:
	//		 v-dir(Col)
	//		01234567<-nCon_S of them for each lofted curve
	//  u-	01234567			|
	//	d	01234567			| 
	//	i	01234567			^ 
	//	r	01234567		# of Curves 
	//(row)		^
	//			|
	//		   nCon_T of them 
	////////////////////////////////////////////////
	int i,j,k=-1,index;
	CDListMgr* pCNodeList	= pPatch->GetCNodeList();
	pDOUBLE	pPatWts_BZ		= new double[nCon_S*nCon_T];
	CDrNode* pNode;
	double Wts;
	POSITION pos;
	/////////////////////
	for(j=0;j<nCon_T;j++)
	{
		for(i=0;i<nCon_S;i++)
		{
			k++;
			index	= i*nCon_T + j; 
			pos		= TemCNodeList.FindIndex(index);
			pNode	= (CDrNode*)TemCNodeList.GetAt(pos);
			Wts		= pTemPatWts_BZ[index]; 
			///////////////////////////////////////////////// Save BezPts
			pCNodeList->InsertObject(pNode);
			pPatWts_BZ[k] = Wts;
			///////
		}
	}
	///////////////////////////////////////////////////////// Save Wts
	pPatch->SetMemInWts(pPatWts_BZ);
	/////////////
	return MA_OK;

}
	
int CMP_Sweep::TempPostPatBezJunctionPtsInINodeList(pWORLD pConBZ,int nConBZ,int nCol,
												int nCurves,CDListMgr* pINodeList)
{
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
    CDrNode* 	pAddNode;
	int			s,index;
	///////////////////////////////////////
	for (s = 0; s<nCurves; s++)
	{
		index = s*nConBZ + nCol;	// nCol Bez.Pt of sth Curve
		//////////////////////////////////// Coords
		LocalPos = pConBZ[index];
	    //////////////////////////////////// Name
		CString* pNid = new CString;
		char* buf = pNid->GetBuffer(BUFF_SIZE);
	    sprintf(buf,"%s_%d%d","Temp",s,nCol);
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(*pNid,LEVEL_KIDDO,LocalPos,FALSE);	// Create DrNode
		delete pNid;
		/////////////
		if(!pAddNode)	// Create DrCNode
			return MA_ERROR;
		///////////////////////////////////// in Curve 	
		pINodeList->InsertObject(pAddNode); //CNodeList
	}
	/////////////////////////////////////////////////////////////////////	
	return MA_OK;
}
	
int CMP_Sweep::PackPatBezJunctionWtsInDataWtsArray(pDOUBLE pWtsBZ,int nConBZ,int nCol,
												int nCurves,pDOUBLE pTemWts_BZ)
{
	int			s,index;
	///////////////////////////////////////
	for (s = 0; s<nCurves; s++)
	{
		index = s*nConBZ + nCol;	// nCol Bez.Pt of sth Curve
		//////////////////////////////////// Wts
		pTemWts_BZ[s] = pWtsBZ[index]; 
	}
#ifdef _DEBUG					
	/////////////////////////////////////////// BEZIER Data Weights
	for (s = 0; s<nCurves; s++)
		double Wts = pTemWts_BZ[s];
#endif	 
	/////////////////////////////////////////////////////////////////////	
	return 0;
}

int CMP_Sweep::GeneratePatchBezInfoFromSpineCurve(
						BLENDEND BlendEnd,CDrCurve* pSpineCurve,CDListMgr* pINodeList,
						pDOUBLE pWts_DT,CList<int,int>& ElSegList,CDListMgr* pPatCNodeList,
						pDOUBLE pPatWts_BZ,double Ratio,CString& PatchID,int nCon_T,int nCol)
{
	// pINodeList contains already evaluated Bez Pts. of the data curves which
	// will now serve as INPUT for Blending Curve Generation whose Bez. Pts.
	// become Patch Bez Pts. for current column, nCol
	///////////////////////////////////////////////////////////////////////////
	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	int nActiveIndex;
	CDrCurve* pCurve;
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	////////////////////////////////////////////////////// Tempo. Add to DataBase, if not Existing
	CString		ID = "Blend";
	///////////////////////////////////////// delete & Add
	pList = pObjectMgr->GetObjectList(CURVE);
	nActiveIndex = pList->GetObjectIndex(CURVE, ID);
	if(nActiveIndex>=0)
	{
		pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
		pCurve = (CDrCurve*)NULL;
	}
	pCurve	= (CDrCurve*)(pObjectMgr->AddToDataBase(ID,nActiveIndex,CURVE));
	///////////////////////////////////////// Get rid of Old CNodes & INodes
	if(!(pCurve->GetCNodeList()->IsEmpty())  )
		pCurve->GetCNodeList()->RemoveAll();
	if(!(pCurve->GetINodeList()->IsEmpty())  )
		pCurve->GetINodeList()->RemoveAll();
	/////////////////////////////////////////////////////////////// Set CurveType and bClosed
	pCurve->SetCurveType_S(pSpineCurve->GetCurveType_S());
	pCurve->SetClosed_S(pSpineCurve->IsClosed_S());
	/////////////////////////////////////////////////////////////// End Conditions
	pCurve->SetBCL_S(BlendEnd.m_BCL);
	pCurve->SetBCR_S(BlendEnd.m_BCR);
	pCurve->SetTanL_S(BlendEnd.m_TanL);
	pCurve->SetTanR_S(BlendEnd.m_TanR);
	////////////////////////////////////
	pCurve->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// Fill Input Nodes
	pCurve->GetINodeList()->AddTail(pINodeList);	// copy
	/////////////////////////////////////////////////////////////// Fill Input Wts
	pCurve->SetWtType_S(WT_USER);	// UserType
	pCurve->SetpWts_DT_S(pWts_DT);	// copy will be deleted when
									// Curve is deleted
	///////////////////////////////////////////////////////
	pCurve->SetRatio_S(Ratio);
	pCurve->SetClosed_S(pSpineCurve->IsClosed_S());
	////////////////////////////////
	pCurve->SetnDim_S(4); // ALWAYS
	pCurve->SetOrder_S(pSpineCurve->GetOrder_S()); 
	/////////////////////////////////////////////////////////////// Using GangC
	CMI_GangC	GangC;
	CMC_Circle	MC_Circle;
	CMC_Parab	MC_Parabola;
	CDrNode*	pFromNode = NULL;
	CDrNode*	pToNode = NULL;
	/////////////////////////////
	CURVEPROC CurveType = pSpineCurve->GetCurveType_S(); 
	/////////////////
	switch(CurveType)
	{
		case CP_CIRCLE:	// Circle by NO3

			////////////////////////////////////
			pCurve = MC_Circle.CreateCircle(
								ID,pCurve,pINodeList,CP_CIRCLE,
								&ElSegList,CIRCLE_BY_NO3,0.0,120/*SegAngle*/,0.0,
								TRUE/*bArc*/,pFromNode,pToNode,FALSE/*bFinal*/);
			/////////////////
			break;
				
		case CP_PARABOLA:

			////////////////////////////////////
			pCurve = MC_Parabola.CreateParabola(
								ID,pCurve,pINodeList,CP_PARABOLA,
								&ElSegList,/*m_bAdvanceOn*/FALSE,FALSE/*bFinal*/);
			/////////////////
			break;
			
		default:

			GangC.SetNoDefault(TRUE); // BC etc.
			pCurve = GangC.CreateCurve(
								ID,pCurve,pINodeList,CurveType,
								&ElSegList,FALSE/*m_bAdvanceOn*/,FALSE/*bFinal*/);
			/////////////////
			if(!pCurve)
				return MA_ERROR;
			//////
			break;
	}
	////////////////////////////////////////////////// Copy & Transfer Bezier Pts
	Copy_N_TransferBezControlInfo(pCurve,pPatCNodeList,PatchID,nCol);
	////////////////////////////////////////////////// Copy & Transfer Bezier Pts
	Copy_N_TransferBezWeightInfo(pCurve,pPatWts_BZ,nCon_T,nCol);
	////////////////////////////////////////////////// Now get rid of it
	pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
	///////////////////////////////
	return 0;
}
	 
int CMP_Sweep::Copy_N_TransferBezControlInfo(CDrCurve* pCurve,CDListMgr* pPatCNodeList,
														CString& PatchID,int nCol)
{

	CDrGrafFrame* pWnd		= (CDrGrafFrame*)AfxGetMainWnd();
	/////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
    CDrNode* 	pAddNode;
	int s;
	POSITION	pos;
	/////////////////////////////////////////////////////////// Data
	int nMaxCurveCNodes_T		= pCurve->GetnCon_BZ_S();// should be equal to #Lofted Curves
	CDListMgr* pCurCNodeList	= pCurve->GetCNodeList();
	///////////////////////////////////////
	for (s = 0; s<nMaxCurveCNodes_T; s++)
	{
		//////////////////////////////////// Coords
		pos = pCurCNodeList->FindIndex(s);
		LocalPos = *((CDrNode*)pCurCNodeList->GetAt(pos))->GetLocalPos();
	    //////////////////////////////////// Name
		CString* pNid = new CString;
		char* buf = pNid->GetBuffer(BUFF_SIZE);
	    sprintf(buf,"%s_%d%d",PatchID,s,nCol);
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(*pNid,LEVEL_KIDDO,LocalPos,TRUE);	// Create DrCNode
		delete pNid;
		/////////////
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////// in Curve 	
		pPatCNodeList->InsertObject(pAddNode); //CNodeList
	}
#ifdef _DEBUG					
	/////////////////////////////////////////// BEZIER Control Nodes
	WORLD Local;
	int ntemp = pPatCNodeList->GetCount();
	pList = pPatCNodeList;
	////////////////////////////////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pList->GetNextObject(pos);
		/////////////////////////////////////////// ObjectInfo
		Local = *(pNode->GetLocalPos());
		//////////////////////////////////
		LocalPos = Local;
	}
#endif	 
	/////////////////////////////////////////////////////////////////////	
	return 0;
}

int CMP_Sweep::Copy_N_TransferBezWeightInfo(CDrCurve* pCurve,pDOUBLE pPatWts_BZ,int nCon_T,int nCol)
{
	pDOUBLE pWts	= pCurve->GetpWts_BZ_S(); 
	////////////////////////////////////////////////// Copy & Transfer Bezier Wts
	int i,j;
	for(i=0;i<nCon_T;i++)
	{
		j = nCol*nCon_T + i; 
		pPatWts_BZ[j]	= pWts[i];
	}
	///////////////////////////////
	return 0;
}
/*
int CMP_Sweep::PostPatCNodes_N_Wts(CDrPatch* pDrPatch,pWORLD pPatCons,pDOUBLE pPatWts,
															int nConBZ_S,int nConBZ_T)
{
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int i,j,k=-1,m;
	CDListMgr	TemList;
	CDrNode*	pNewNode;
	WORLD		wLocalPos;
	CString		PatchID = pDrPatch->GetObjectID();
	///////////////////
	for(i=0;i<nConBZ_T;i++)
	{
		///////
		for(j=0;j<nConBZ_S;j++)
		{
			k++;
			//////////////////////////////////// Name
			CString* pNid = new CString;
			char* buf = pNid->GetBuffer(BUFF_SIZE);
			sprintf(buf,"%s_%d_%d",PatchID,i,j);
			////////////////////////////////////////////////// Regular 
			wLocalPos = *(pPatCons + k);
			////////////////////////////////////////////////// Create & Save
			pNewNode = PostNode(*pNid,LEVEL_KIDDO,wLocalPos,TRUE);	// Create DrCNode
			delete pNid;
			//////////////////////////////////
			if(!pNewNode)	// Create DrCNode
				return MA_ERROR;
			///////////////////////////////////
			pDrPatch->GetCNodeList()->InsertObject(pNewNode);
		}
	}
	////////////////////////////////////////////////////////// save Wts
	pDrPatch->SetMemInWts(pPatWts);
	////////////
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 1
	{
		k = -1;
		///////
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		sprintf(buf,"CMP_Sweep::PatCNodes_N_Wts");
		AfxMessageBox(*str);
		///////////////////
		for(i=0;i<nConBZ_T;i++)
		{
			j = sprintf(buf,"CNode[Column_%d]\n",i);
			j += sprintf(buf + j,"Row#      X             Y            Z         Wt\n");
			//////////////////////
			for(m=0;m<nConBZ_S;m++)
			{
				k++;
				wLocalPos = *(pPatCons + k);
				///
				j += sprintf( buf + j, "%2d %7.2f %7.2f %7.2f %7.2f\n", m,
		   				wLocalPos.x,wLocalPos.y,wLocalPos.z,pPatWts[k] );

			}
			if(j>BUFF_SIZE)
			{
				sprintf( buf, "Increase buffer to %d",j);
				AfxMessageBox(*str);
				delete str;
				return -1;
			}	 
			AfxMessageBox(*str);
			///////////////////
		}
		delete str;
	}
#endif				
	////////////////////////////	
	return MA_OK;
}
*/
/////////////////////////////////////////////////////////////////////////////////////
int CMP_Sweep::SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CList<double,double>* pTwistList,	// Distrib,if nTwistType = 1
					CList<double,double>* pScaleList	// Distrib,if nTwistType = 1
)
{
	pDrObject->SetDirty(TRUE);
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)PATCH);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
	pDrObject->SetPatchProc(PP_SWEEP);
	pDrObject->SetPatchType(PA_TENSOR);
	pDrObject->SetPatSubType(PS_QUADRILAT);
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	//////////////////////////////////
	pDrObject->SetGenBCurve(m_bGenBCur);
	/////////////////////////////////////////////////////////////////// Info Based on nCurDir
	pDrObject->SetPrimaryDir(1);// 
	SetInfoForDataBase_1(pDrObject,	pCurveList_U,pCurveLatchList_U,
									pCurveList_V,pCurveLatchList_V,
									pTwistList,pScaleList);
	/////////////////////////////////////////////////////////
	m_nOut = (long)m_nOut_S * (long)m_nOut_T;
	pDrObject->SetLongOutPts(m_nOut);			// m_nOut	
	//////////////////////////////////////////////////
	// call to NumberOfPatches() Overrides:	//
	//		m_nOut_S,m_nOut_T,m_nOut				//
	////////////////////////////////////////////////// 
	int nOutTotal = pDrObject->NumberOfPatches();
	if(nOutTotal != (int)m_nOut)
	{
		AfxMessageBox("Internal Problem:\nCMP_Sweep::SetInfoForDataBase\nm_nOut Mismatch!");
		return MA_ERROR;
	}
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	pDrObject->Calc_3DBoundsLocal();
	///////
	return MA_OK;
}

void CMP_Sweep::SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CList<double,double>* pTwistList,	// Distrib,if nTwistType = 1
					CList<double,double>* pScaleList	// Distrib,if nScaleType = 1
)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CPrecision* pPrecision     	= (CPrecision*)pObjectMgr->GetSpecObject(PRECISION);
//	CScaleFactor* pScaleFactor 	= (CScaleFactor*)pObjectMgr->GetSpecObject(SCALEFACTOR);
	CMapFactor* pMapFactor     	= (CMapFactor*)pObjectMgr->GetSpecObject(MAPFACTOR); 
	//////////////////////////////////////////////////// Update Current DrObject
	long  lWorldBase  = pPrecision->GetWorldBase(); 
    double dWorldBase = (double)lWorldBase;
    ///////////////////////////////////////////
	double dMapFactor   = pMapFactor->GetMapFactor();
	////////////////////////////////////////////////////////// CurveList
	CDListMgr* pList; 
	POSITION pos;
	CDrCurve* pCurve;
	///////////////////////////////////////////////// U 
	pList = pDrObject->GetCurveList_U(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_U);
	pDrObject->GetCurveLatchList_U()->RemoveAll();
	pDrObject->GetCurveLatchList_U()->AddTail(pCurveLatchList_U);
	///////////////////////////////////////////////// V 
	pList = pDrObject->GetCurveList_V(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_V);
	pDrObject->GetCurveLatchList_V()->RemoveAll();
	pDrObject->GetCurveLatchList_V()->AddTail(pCurveLatchList_V);
	///////////////////////////////////////////////// Save:CurveList for Toplogy
	pList = pDrObject->GetCurveList();
	pList->AddTail(pCurveList_U);
	pList->AddTail(pCurveList_V);
	///////////////////////////////////////////////// Reciprocate:CurveList
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		/////////////////////////////////////////// does exist already?
		int index = pCurve->GetPatchList()->GetObjectIndex(pDrObject);
		if(index<0)
			pCurve->GetPatchList()->InsertObject(pDrObject);
	}
	////////////////////////////////////////////// Reciprocate fromID: Anchor Node
	m_pFromIDNode->GetPatchList()->InsertObject(pDrObject);
	pDrObject->SetFromIDNode_T(m_pFromIDNode);
	////////////////////////////////////////////// Type_1: n
	pDrObject->SetTwistType_T(m_nTwistType);
	pDrObject->SetScaleType_T(m_nScaleType);
	//
	if(m_nTwistType == 1)
		pDrObject->GetTwistList_T()->AddTail(pTwistList);
	//
	if(m_nScaleType == 1)
		pDrObject->GetScaleList_T()->AddTail(pScaleList);
	///////////////////////////////////////////////// Twist Multiplier
	pDrObject->SetIncTwist_T(m_bIncrement);
	pDrObject->SetTwistMult_T(m_TwistMult);
	pDrObject->SetTwistStart_T(m_TwistStart);
	///////////////////////////////////////////////// Scale Multiplier
	pDrObject->SetIncTwist_T(m_bIncScale);
	pDrObject->SetTwistMult_T(m_ScaleMult);
	pDrObject->SetTwistStart_T(m_ScaleStart);
	///////////////////////////////////////////////////////////////// All Other
	pDrObject->SetRatio_S(m_Ratio_S);					
	pDrObject->SetRatio_T(m_Ratio_T);					
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetUniform_T(m_bUnifOT_T);		// Output Distribution:
	pDrObject->SetOutSegUnif_S(m_nMaxOSeg_S); 	// for Old Compatibility
	pDrObject->SetOutSegUnif_T(m_nMaxOSeg_T); 	// for Old Compatibility
	pDrObject->SetMaxOutSeg_S(m_nMaxOSeg_S);	// Number of Output Segments
	pDrObject->SetMaxOutSeg_T(m_nMaxOSeg_T);	// Number of Output Segments
//?
	pDrObject->SetMaxOutPts_S(m_nOut_S);
	pDrObject->SetMaxOutPts_T(m_nOut_T);
	pDrObject->SetOut_S(m_nOut_S);
	pDrObject->SetOut_T(m_nOut_T);
	//////////////////////////////////////////
	pDrObject->SetCurveType_S(m_CurveType_S);
	pDrObject->SetCurveType_T(m_CurveType_T);
	pDrObject->SetMaxCNodes_S(m_nMaxPatchCNodes_S);
	pDrObject->SetMaxCNodes_T(m_nMaxPatchCNodes_T);
	///////////////////////////////////////////////////
//	pDrObject->SetSegmentCount_S(m_nSegs_S);	
//	pDrObject->SetSegmentCount_T(m_nSegs_T); 
	pDrObject->SetMaxBezSegments_S(m_nSegs_S);	
	pDrObject->SetMaxBezSegments_T(m_nSegs_T); 
	pDrObject->SetClosed_S(m_bClosed_S);
	pDrObject->SetClosed_T(m_bClosed_T);
	pDrObject->SetOut_S(m_nOut_S);	
	pDrObject->SetOut_T(m_nOut_T);
	pDrObject->SetOrder_S(m_nOrder_S);
	pDrObject->SetOrder_T(m_nOrder_T);
//	pDrObject->SetnDim_S(m_nDim_S);
//	pDrObject->SetnDim_T(m_nDim_T);
	pDrObject->SetnDim_S(4);	// ALWAYS RATIONAL
	pDrObject->SetnDim_T(4);	// ALWAYS RATIONAL
	///////////////////////////////////////////////////////// for now
	pDrObject->SetNum_tPointer_S(m_pNum_t_S);			// Number of Outputs for each Output Segment
	pDrObject->SetNum_tPointer_T(m_pNum_t_T);			// Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////
	pDrObject->SetDis_tPointer_S(m_pDis_t_S);			// s-distribution
	pDrObject->SetDis_tPointer_T(m_pDis_t_T);			// t-distribution
	//////////////////////////////////////////////////////////////////////
	pDrObject->SetGenBCurve(m_bGenBCur);
	////////////////
	return;
}
///////////////////////////////////////////////////////////////////////////////////////////
int CMP_Sweep::LatticeCurves_U(CDrPatch* pDrPatch,int nOrder_T,BOOL bClosed_T,int nSegBZ_T,
													int nConBZ_S,CDrCurve* pCurOriginal)
{
	/////////////////////
	// Create LatticeCurves_U at Bez. JnPts. Only
	/////////////////////////////////////////////
	// Hints: geteach set of Cnodes & Wts COL from pDrPatch and create a NURB Curve
	// with other similar properties as pCurveOriginal
	// Create New INodes
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	///////////////////
	int i;
	int nActiveIndex;
	CDrCurve* pCurve;
	CString	ID;
	CString PatchID = pDrPatch->GetObjectID();
	//
	int nDegree_S = pCurOriginal->GetOrder_S() - 1;
	int nDegree_T = nOrder_T - 1;
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	//////////////////////////////////////////////////////// Loop Over Bez. Pts. on Curves
	int nCurves = (bClosed_T)?nSegBZ_T:nSegBZ_T+1;
	for(i=0;i<nCurves;i++)
	{
		////////////////////////////////////////////////////// Add to DataBase
		pObjectMgr->SetObjInfoID(ID,CURVE);
//		ID += "_" + PatchID;
		///////////////////////////////////////// delete & Add
		pList = pObjectMgr->GetObjectList(CURVE);
		nActiveIndex = pList->GetObjectIndex(CURVE, ID);
		if(nActiveIndex>=0)
		{
			pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
			pCurve = (CDrCurve*)NULL;
		}
		pCurve	= (CDrCurve*)(pObjectMgr->AddToDataBase(ID,nActiveIndex,CURVE));
		////////////////////////
		pCurve->SetObjectID(ID);
		////////////////////////////////////
		pCurve->SetShow(FALSE);	// not quite ready
		//////////////////////////////////////////////////////////////////////// CNODES & WTS
		// Fill CNodeList w/ CNodes created from CNodes of Patch  Col
		CDListMgr* pCNodeList = pCurve->GetCNodeList();
		pCNodeList->RemoveAll();
		pDOUBLE pWts_DT = new double[nConBZ_S]; 
		//////////
		// CreateFillCNodeslist/Wts
		CreateFillCNodeList_N_Wts_S(pDrPatch,i,nDegree_T,nConBZ_S,pCNodeList,pWts_DT);
		//////////////////////////////////////////////////////// Setup Weights
//		ExtractWts_S(pDrPatch,i,nDegree_T,nConBZ_S,pWts_DT);
		// save
		pCurve->SetWtType_S(WT_AUTO);	// AutoType
		pCurve->SetpWts_BZ_S(pWts_DT);	// Rational Weights
										// copy will be deleted when
										// Curve is deleted
		///////////////////////////////////////// ReParametrize Bez Wts, in case
		ReParametrizeBezWeightsToStdForm(pCurve);
		///////////////////////////////////////////////////////////////////////// INODES 
		// Fill INodeList w/ INodes of XSection Curve
		CDListMgr INodeList;
		INodeList.RemoveAll();
		int nINode = pCurOriginal->GetINodeList()->GetCount(); // Original Curve Compatible
		// Create/Fill INodes as Input
		CreateFillINodeList_S(pDrPatch,i,nINode,nDegree_S,nDegree_T,nConBZ_S,&INodeList);
		pCurve->GetINodeList()->AddTail(&INodeList);	// copy
		///////////////////////////////////////////////////////////////////////// KNOTS
		CDListMgr* pINList = pCurve->GetINodeList();
		int nData = pINList->GetCount();
		pWORLD inData = new WORLD[nData];
		/////
		SetUpINodes(pINList,inData,nData);
		/////
		m_nKnots_S = pCurve->GetnKnots_S();
		pDOUBLE m_pKnot_S = new double[m_nKnots_S];	// will be deleted in DrCurve
		/////
		m_KnotType_S = KN_AUTO;	// chordlength
		SetupKnots(inData,m_KnotType_S,m_pKnot_S,m_nKnots_S);
		///////////////////////////////////////////////////// Save
		pCurve->SetpKnots_S(m_pKnot_S);	// pointer
		//////////////////////////////////////////
		delete [] inData;
		///////////////////////////////////////////////////////////////////////// END CONDS
		pCurve->SetBCL_S(pCurOriginal->GetBCL_S());
		pCurve->SetBCR_S(pCurOriginal->GetBCR_S());
		pCurve->SetTanL_S(pCurOriginal->GetTanL_S());
		pCurve->SetTanR_S(pCurOriginal->GetTanR_S());
		///////////////////////////////////////////////////////////////////////// ElSegList
		pCurve->GetElperSegList_S()->AddTail(pCurOriginal->GetElperSegList_S());
		///////////////////////////////////////////////////////////////////////// ALL OTHER
		SetDataFromCurve_Lattice(pCurOriginal);
		///////////////////////////////////////////////////////////////////////// FINALLY Save
		SetInfoDataBase_LatticeCurve(pCurve);
		///////////////////////////////////////////////////////////////////////// Change Color
		pCurve->SetPenInfo(0,MAGENTA,PS_SOLID);
		pCurve->SetShow(TRUE);
		/////////////////////////////////
//		pCurveList->InsertObject(pCurve);
	}
	//////////////
	return MA_OK;
}

int CMP_Sweep::CreateFillINodeList_S(CDrPatch* pDrPatch,int iCurve_U,int nINode_U,
					int nDegree_S,int nDegree_T,int nConBZ_S,CDListMgr* pINodeList)
{
	int nResult;
	//////////////////////////////////////
	CDListMgr* pCNList	= pDrPatch->GetCNodeList();
	CString PatchID		= pDrPatch->GetObjectID();
	//////////////////////
	nResult =  PackINodeList_S(PatchID,pCNList,iCurve_U,nINode_U,nDegree_S,nDegree_T,pINodeList,
																					nConBZ_S);
	////////////
	if(nResult == MA_ERROR)
		return MA_ERROR;
	//////////////
	return MA_OK;
}

int CMP_Sweep::PackINodeList_S(CString& PatchID,CDListMgr* pCNodeList,int iCurve_U,int nINode,
									 int nDeg_U,int nDeg_V,CDListMgr* pINodeList,int nConBZ_S)
{
	// Packs Jn. Pts. of CNodeList as INODES
	////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int			i,index,iCol;
	CDrNode*	pCNode;
	CDrNode*	pINode;
	WORLD		wLocalPos;
	CString		ID;
	CDrLabel*	pLabel;
	int			nNodeIndex,nLabelIndex;
	////////////////////////
	pINodeList->RemoveAll();
	////////////////////////
	iCol	= (iCurve_U * nDeg_V /*= iCol*/) * nConBZ_S;
	for(i=0;i<nINode;i++)
	{
		index	= iCol + i * nDeg_U; 
		pCNode	= (CDrNode*)pCNodeList->GetObject(index);
		/////
		if(pCNode)
		{
			//////////////////////////////// Create an INode
			pObjectMgr->SetObjInfoID(ID,INODE);
//			ID += "_" + PatchID;
			wLocalPos = *(pCNode->GetLocalPos());
			/////////////////////////// Create Anyway
			nNodeIndex = -12345;
			pINode = CreateNode(ID,pLabel,wLocalPos,FALSE/*Not CNode*/,TRUE,
									nNodeIndex,nLabelIndex,LEVEL_GRAPA);
			//////////////////////////////////
			if(!pINode)	// Create DrCNode
			return MA_ERROR;
			///////////////////////////////////
			pINodeList->InsertObject(pINode);
		}
	}
	/////////////
	return MA_OK;
}

int CMP_Sweep::CreateFillCNodeList_N_Wts_S(CDrPatch* pDrPatch,int iCurve_U,int nDegree_T,
									int nConBZ_S,CDListMgr* pCNodeList,pDOUBLE pWts)
{
	int nResult;
	//////////////////////////////////////
	CDListMgr* pPatCNList	= pDrPatch->GetCNodeList();
	pDOUBLE pPatWts			= pDrPatch->GetMemInWts();
	CString PatchID			= pDrPatch->GetObjectID();
	//////////////////////
	nResult =  PackCNodeList_N_Wts_S(PatchID,pPatCNList,pPatWts,iCurve_U,nDegree_T,nConBZ_S,
																	pCNodeList,pWts);
	////////////
	if(nResult == MA_ERROR)
		return MA_ERROR;
	//////////////
	return MA_OK;
}

int CMP_Sweep::PackCNodeList_N_Wts_S(CString& PatchID,CDListMgr* pPatCNodeList,pDOUBLE pPatWts,
				int iCurve_U,int nDeg_V,int nConBZ_S,CDListMgr* pCNodeList,pDOUBLE pWts)
{
	// Create All CNodes corresponding To XSec Curve
	// ( Extracted From Patch CNodes at Jn. Pts. along T-direction) 
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int			i,index,iCol;
	CDrNode*	pCNode;
	double		Wts;
	WORLD		wLocalPos;
	CDrNode*	pAddNode;
	////////////////////////
	pCNodeList->RemoveAll();
	////////////////////////
	iCol	= (iCurve_U * nDeg_V) * nConBZ_S;
	for(i=0;i<nConBZ_S;i++)
	{
		index = iCol + i;	// 
		pCNode	= (CDrNode*)pPatCNodeList->GetObject(index);
		Wts		= pPatWts[index];
		/////
		if(pCNode)
		{
			//////////////////////////////////// Coords
			wLocalPos = *(pCNode->GetLocalPos());
		    //////////////////////////////////// Name
			CString* pNid = new CString;
			char* buf = pNid->GetBuffer(BUFF_SIZE);
		    sprintf(buf,"%s_%d_%d","C",i,iCol);
			///////////////////////////////////// in THE List 
			pAddNode = PostNode(*pNid,LEVEL_KIDDO,wLocalPos,FALSE);	// Create DrNode
			delete pNid;
			/////////////
			if(!pAddNode)	// Create DrCNode
				return MA_ERROR;
			///////////////////////////////////// in Curve 	
			pCNodeList->InsertObject(pAddNode); //CNodeList
			/////////////////////////////////////////////// Save Wts
			pWts[i] = Wts;
		}
		else
			return MA_ERROR;
	}
	/////////////
	return MA_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////
int CMP_Sweep::LatticeCurves_V(CDrPatch* pDrPatch,int nOrder_S,BOOL bClosed_S,int nSegBZ_S,
										int nConBZ_S,int nConBZ_T,CDrCurve* pCurOriginal)
{
	/////////////////////
	// Create LatticeCurves_V at Bez. JnPts. Only
	/////////////////////////////////////////////
	// Hints: geteach set of Cnodes & Wts COL from pDrPatch and create a NURB Curve
	// with other similar properties as pCurveOriginal
	// Create New INodes
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	///////////////////
	int i;
	int nActiveIndex;
	CDrCurve* pCurve;
	CString	ID;
	CString PatchID = pDrPatch->GetObjectID();
	//
	int nDegree_T = pCurOriginal->GetOrder_S() - 1;
	int nDegree_S = nOrder_S - 1;
	///////////////////
	pObjectMgr->SetActiveObjectType(CURVE);
	//////////////////////////////////////////////////////// Loop Over Bez. Pts. on Curves
	int nCurves = (bClosed_S)?nSegBZ_S:nSegBZ_S+1;
	for(i=0;i<nCurves;i++)
	{
		////////////////////////////////////////////////////// Add to DataBase
		pObjectMgr->SetObjInfoID(ID,CURVE);
//		ID += "_" + PatchID;
		///////////////////////////////////////// delete & Add
		pList = pObjectMgr->GetObjectList(CURVE);
		nActiveIndex = pList->GetObjectIndex(CURVE, ID);
		if(nActiveIndex>=0)
		{
			pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
			pCurve = (CDrCurve*)NULL;
		}
		pCurve	= (CDrCurve*)(pObjectMgr->AddToDataBase(ID,nActiveIndex,CURVE));
		////////////////////////
		pCurve->SetObjectID(ID);
		////////////////////////////////////
		pCurve->SetShow(FALSE);	// not quite ready
		//////////////////////////////////////////////////////////////////////// CNODES & WTS
		// Fill CNodeList w/ CNodes created from CNodes of Patch  Row
		CDListMgr* pCNodeList = pCurve->GetCNodeList();
		pCNodeList->RemoveAll();
		pDOUBLE pWts_DT = new double[nConBZ_T]; 
		//////////
		// CreateFillCNodeslist/Wts
		CreateFillCNodeList_N_Wts_T(pDrPatch,i,nDegree_S,nConBZ_S,nConBZ_T,pCNodeList,pWts_DT);
		//////////////////////////////////////////////////////// Setup Weights
		// save
		pCurve->SetWtType_S(WT_AUTO);	// UserType
		pCurve->SetpWts_BZ_S(pWts_DT);	// Rational Weights
										// copy will be deleted when
										// Curve is deleted
		///////////////////////////////////////// ReParametrize Bez Wts, in case
		ReParametrizeBezWeightsToStdForm(pCurve);
		///////////////////////////////////////////////////////////////////////// INODES 
		// Fill INodeList w/ INodes of XSection Curve
		CDListMgr INodeList;
		INodeList.RemoveAll();
		int nINode = pCurOriginal->GetINodeList()->GetCount(); // Original Curve Compatible
		// Create/Fill INodes as Input
		CreateFillINodeList_T(pDrPatch,i,nINode,nDegree_S,nDegree_T,nConBZ_S,&INodeList);
		pCurve->GetINodeList()->AddTail(&INodeList);	// copy
		///////////////////////////////////////////////////////////////////////// KNOTS
		CDListMgr* pINList = pCurve->GetINodeList();
		int nData = pINList->GetCount();
		pWORLD inData = new WORLD[nData];
		/////
		SetUpINodes(pINList,inData,nData);
		/////
		m_nKnots_S = pCurve->GetnKnots_S();
		pDOUBLE m_pKnot_S = new double[m_nKnots_S];	// will be deleted in DrCurve
		/////
		m_KnotType_S = KN_AUTO;	// chordlength
		SetupKnots(inData,m_KnotType_S,m_pKnot_S,m_nKnots_S);
		///////////////////////////////////////////////////// Save
		pCurve->SetpKnots_S(m_pKnot_S);	// pointer
		//////////////////////////////////////////
		delete [] inData;
		///////////////////////////////////////////////////////////////////////// END CONDS
		pCurve->SetBCL_S(pCurOriginal->GetBCL_S());
		pCurve->SetBCR_S(pCurOriginal->GetBCR_S());
		pCurve->SetTanL_S(pCurOriginal->GetTanL_S());
		pCurve->SetTanR_S(pCurOriginal->GetTanR_S());
		///////////////////////////////////////////////////////////////////////// ElSegList
		pCurve->GetElperSegList_S()->AddTail(pCurOriginal->GetElperSegList_S());
		///////////////////////////////////////////////////////////////////////// ALL OTHER
		SetDataFromCurve_Lattice(pCurOriginal);
		///////////////////////////////////////////////////////////////////////// FINALLY Save
		SetInfoDataBase_LatticeCurve(pCurve);
		///////////////////////////////////////////////////////////////////////// Change Color
		pCurve->SetPenInfo(0,MAGENTA,PS_SOLID);
		pCurve->SetShow(TRUE);
		/////////////////////////////////
//		pCurveList->InsertObject(pCurve);
	}
	//////////////
	return MA_OK;
}

int CMP_Sweep::CreateFillCNodeList_N_Wts_T(CDrPatch* pDrPatch,int iCurve_V,int nDegree_S,
						int nConBZ_S,int nConBZ_T,CDListMgr* pCNodeList,pDOUBLE pWts)
{
	int nResult;
	//////////////////////////////////////
	CDListMgr* pPatCNList	= pDrPatch->GetCNodeList();
	pDOUBLE pPatWts			= pDrPatch->GetMemInWts();
	CString PatchID			= pDrPatch->GetObjectID();
	//////////////////////
	nResult =  PackCNodeList_N_Wts_T(PatchID,pPatCNList,pPatWts,iCurve_V,nDegree_S,
												nConBZ_S,nConBZ_T,pCNodeList,pWts);
	////////////
	if(nResult == MA_ERROR)
		return MA_ERROR;
	//////////////
	return MA_OK;
}

int CMP_Sweep::PackCNodeList_N_Wts_T(CString& PatchID,CDListMgr* pPatCNodeList,pDOUBLE pPatWts,
			int iCurve_V,int nDeg_U,int nConBZ_S,int nConBZ_T,CDListMgr* pCNodeList,pDOUBLE pWts)
{
	// Create All CNodes corresponding To XSec Curve
	// ( Extracted From Patch CNodes at Jn. Pts. along T-direction) 
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int			i,index,iRow;
	CDrNode*	pCNode;
	double		Wts;
	WORLD		wLocalPos;
	CDrNode*	pAddNode;
	////////////////////////
	pCNodeList->RemoveAll();
	////////////////////////
	iRow	= iCurve_V * nDeg_U /*= iRow*/;
	for(i=0;i<nConBZ_T;i++)
	{
		index	= iRow + i * nConBZ_S; 
		pCNode	= (CDrNode*)pPatCNodeList->GetObject(index);
		Wts		= pPatWts[index];
		/////
		if(pCNode)
		{
			//////////////////////////////////// Coords
			wLocalPos = *(pCNode->GetLocalPos());
		    //////////////////////////////////// Name
			CString* pNid = new CString;
			char* buf = pNid->GetBuffer(BUFF_SIZE);
		    sprintf(buf,"%s_%d_%d","C",i,iRow);
			///////////////////////////////////// in THE List 
			pAddNode = PostNode(*pNid,LEVEL_KIDDO,wLocalPos,FALSE);	// Create DrNode
			delete pNid;
			/////////////
			if(!pAddNode)	// Create DrCNode
				return MA_ERROR;
			///////////////////////////////////// in Curve 	
			pCNodeList->InsertObject(pAddNode); //CNodeList
			/////////////////////////////////////////////// Save Wts
			pWts[i] = Wts;
		}
		else
			return MA_ERROR;
	}
	/////////////
	return MA_OK;
}

int CMP_Sweep::CreateFillINodeList_T(CDrPatch* pDrPatch,int iCurve_V,int nINode_V/*BzJnPts_S*/,
					int nDegree_S,int nDegree_T,int nConBZ_S,CDListMgr* pINodeList)
{
	int nResult;
	//////////////////////////////////////
	CDListMgr* pCNList	= pDrPatch->GetCNodeList();
	CString PatchID		= pDrPatch->GetObjectID();
	//////////////////////
	nResult =  PackINodeList_T(PatchID,pCNList,iCurve_V,nINode_V,nDegree_S,nDegree_T,
																pINodeList,nConBZ_S);
	////////////
	if(nResult == MA_ERROR)
		return MA_ERROR;
	//////////////
	return MA_OK;
}

int CMP_Sweep::PackINodeList_T(CString& PatchID,CDListMgr* pCNodeList,int iCurve_V,int nINode_V,
							int nDeg_U,int nDeg_V,CDListMgr* pINodeList,int nConBZ_S)
{
	// Packs Jn. Pts. of CNodeList as INODES
	/////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int			i,index,iRow;
	CDrNode*	pCNode;
	CDrNode*	pINode;
	WORLD		wLocalPos;
	CString		ID;
	CDrLabel*	pLabel;
	int			nNodeIndex,nLabelIndex;
	////////////////////////
	pINodeList->RemoveAll();
	////////////////////////
	iRow	= iCurve_V * nDeg_U /*= iRow*/;
	for(i=0;i<nINode_V;i++)
	{
		index	= iRow + i * nDeg_V * nConBZ_S; 
		pCNode	= (CDrNode*)pCNodeList->GetObject(index);
		/////
		if(pCNode)
		{
			//////////////////////////////// Create an INode
			pObjectMgr->SetObjInfoID(ID,INODE);
//			ID += "_" + PatchID;
			wLocalPos = *(pCNode->GetLocalPos());
			/////////////////////////// Create Anyway
			nNodeIndex = -12345;
			pINode = CreateNode(ID,pLabel,wLocalPos,FALSE/*Not CNode*/,TRUE,
									nNodeIndex,nLabelIndex,LEVEL_GRAPA);
			//////////////////////////////////
			if(!pINode)	// Create DrCNode
			return MA_ERROR;
			///////////////////////////////////
			pINodeList->InsertObject(pINode);
		}
	}
	/////////////
	return MA_OK;
}
/////////////////////////////////////////////////////////////////////////////////////
int CMP_Sweep::SetDataFromCurve_Lattice(CDrCurve* pCurve)
{
	int i;
	pINT	pNum_t_S;
	pDOUBLE	pDis_t_S;
	/////////////
	m_bClosed_S			= pCurve->IsClosed_S();
//			m_nDim_S			= pCurve->GetnDim_S();
	m_nDim_S			= 4;					// ALWAYS Rational;
	m_nOrder_S			= pCurve->GetOrder_S();
	m_nMaxPatchCNodes_S	= pCurve->GetMaxCNodes_S();
	m_nSegs_S 			= pCurve->GetMaxBezSegments_S();
//			m_CurveType_S		= pCurve->GetCurveType_S();
	m_CurveType_S		= CP_NURB;				// ALWAYS
	///
	m_nOut_S			= (int)pCurve->GetLongOutPts();
	m_nMaxOSeg_S		= pCurve->GetOutSegUnif_S();
	m_bUnifOT_S			= pCurve->IsUniform_S();
	//////////////////////////////////////////////////
	pNum_t_S			= pCurve->GetNum_tPointer_S();
	pDis_t_S			= pCurve->GetDis_tPointer_S();
	///
	if(pNum_t_S)
		m_pNum_t_S		= new int[m_nSegs_S];
	if(pDis_t_S)
		m_pDis_t_S		= new double[m_nOut_S];
	///////
	for (i=0;i<m_nSegs_S;i++)
	{
		if(pNum_t_S)
			m_pNum_t_S[i]		= pNum_t_S[i];
	}
	for (i=0;i<m_nOut_S;i++)
	{
		if(pDis_t_S)
			m_pDis_t_S[i]		= pDis_t_S[i];
	}
	////////
	return MA_OK;
}

int CMP_Sweep::SetInfoDataBase_LatticeCurve(CDrCurve* pDrObject)
{
	///////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CDrPen*	pDrPen			= (CDrPen*)pObjectMgr->GetSpecObject(DRPEN);
	CLayer* pLayer			= (CLayer*)pObjectMgr->GetSpecObject(LAYER); 
	//////////////////////////////////////////////////// Update Current DrObject
    pDrObject->SetObjectType((int)CURVE);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
	pDrObject->SetCurveType_S(CP_NURB);
	////////////////////////////////////////////////////// 
	SetInfo_LatticeCurve(pDrObject);
	////////////////////////////////////////////////////////////////////////////////	
	pDrObject->SetPenInfo(pDrPen->GetWidth(),pDrPen->GetColor(),pDrPen->GetStyle());
	pDrObject->SetLayer(pLayer->GetCurrentLayer());
	////////////////////////////////////// LOCAL 3DBounds using
										// ConVexHull Property
	pDrObject->Calc_3DBoundsLocal();
	pDrObject->SetDirty(TRUE);
	///////
	return MA_OK;
}

void CMP_Sweep::SetInfo_LatticeCurve(CDrCurve* pDrObject)
{
	///////////////////////////////////////////////////////////////// All Other
	pDrObject->SetRatio_S(m_Ratio_S);					
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetMaxOutSeg_S(m_nMaxOSeg_S);	// Number of Output Segments
//?
	//////////////////////////////////////////
	pDrObject->SetCurveType_S(m_CurveType_S);
	pDrObject->SetMaxCNodes_S(m_nMaxPatchCNodes_S);
	pDrObject->SetMaxBezSegments_S(m_nSegs_S);	
	pDrObject->SetClosed_S(m_bClosed_S);
	pDrObject->SetOrder_S(m_nOrder_S);
	pDrObject->SetnDim_S(4);	// ALWAYS RATIONAL
	////////////////////////////////////////////////////////////////////// Mesh(Output)
	pDrObject->SetOutMethod_S(CO_HORNER);		// Output Method
	pDrObject->SetOutSegUnif_S(m_nMaxOSeg_S); 	// for Old Compatibility
	pDrObject->SetLongOutPts(m_nOut_S);
	pDrObject->SetMaxOutPts_S(m_nOut_S);
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetNum_tPointer_S(m_pNum_t_S);	// Number of Outputs for each Output Segment
	/////////////////////////////////////////
	pDrObject->SetDis_tPointer_S(m_pDis_t_S);	// s-distribution
    ////////////////////////////////////////////////////////////////////// Reciprocate 	
	CDListMgr* pINodeList = pDrObject->GetINodeList();
   /////////////////
	for (POSITION posI = pINodeList->GetHeadPosition( );posI !=NULL;)
	{
		////
		CDrNode* pDrNode = (CDrNode*)pINodeList->GetNextObject(posI);
		////////////////////////////////// save curve
		int index = (pDrNode->GetCurveList())->GetObjectIndex(pDrObject); // exists already?
		if(index>=0)
			continue;
		/////////////
		pDrNode->GetCurveList()->InsertObject(pDrObject);
	}
	////////////////////////////////////////////////////////////// interpolation
    int nData = pINodeList->GetCount();
	/////////
	pDrObject->SetData_S(nData);		// GIVEN: # of Data
	pDrObject->SetMaxINodes_S(nData);
	pDrObject->SetOrder_S(m_nOrder_S);				// k
	//////////////////////////////////////////////// Update	 
	m_nControls 	= nData + m_nOrder_S - 2;	        // L + k - 1 = nData + k - 2 = n + 1
	m_nCurveSeg 	= nData - 1;
	m_nMaxDistinct 	= nData;
	m_nMaxTotal		= nData + (2 * m_nOrder_S - 2);	// n + k + 1 = nData + (2k - 2)
	if(m_bClosed_S)
	{
		m_nCurveSeg++;
		m_nMaxDistinct++;
		m_nMaxTotal++;
	}
	////////////////////////////////////////////////////////
	pDrObject->SetnCon_BS_S(m_nControls);	// L + k - 1
											// = nData + k - 2
											// = n + 1 (B-Spline));
	pDrObject->SetnKnots_S(m_nMaxDistinct);
	pDrObject->SetnMKnots_S(m_nMaxTotal);
	////////////////////////////////////////
	int nCon_BZ	= (m_nOrder_S - 1) * m_nCurveSeg + 1;	// (k-1) * L + 1 , Open
	if(m_bClosed_S)
		nCon_BZ--; 		
	pDrObject->SetnCon_BZ_S(nCon_BZ); // = m_nMaxCurveCNodes(Eventually)
	/////////////////////////////////////
	return;
}
//////////////////////////////////////////////////////////////////////////////////////
void CMP_Sweep::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMP_Sweep:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMP_Sweep:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
