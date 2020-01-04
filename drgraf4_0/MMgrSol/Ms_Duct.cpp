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
#include "PA_Duct.h" 
#include "MS_Duct.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#define MAGENTA		RGB(255,0,255)	// Jn. Curve Color
#define	new			DEBUG_NEW
#define BUFF_SIZE	1024
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMS_Duct,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMS_Duct::CMS_Duct()
{
}

CMS_Duct::~CMS_Duct()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
int CMS_Duct::GoDoIt 
				(
					BOOL							bGenBCurve,
					BOOL							bGenBPatch,
					int								nTwistType,
									// 1 = Given: Twist Distribution
									// 2 = Given: Twist Increments etc
					//////////////////////////////////////////
					CString&						SolidID,		
					CDrSolid*						pDrSolid,
					//////////////////////////////////////////
					CDListMgr*						pNodeList,	// ist record: pFromIDNode
																// 2nd record: pToIDNode
					//////////////////////////////////////////
					CDListMgr*						pCurveList,	// given Spine Curve
					CList<CURVELATCH,CURVELATCH>*	pCLatchList,
					//////////////////////////////////////////
					CDListMgr*						pPatchList,	// given Xsec. Patch always taken as UV-dir
																// and later switched,if needed,i.e.,
																// nCurDir = 2
					CList<PATCHLATCH,PATCHLATCH>*	pPLatchList,
					//////////////////////////////////////////
					CList<double,double>*			pTwistList,	// Distrib,if nTwistType = 1
					double							TwistMult,	// if nTwistType = 2 
					BOOL							bIncrement,
					double							TwistStart,
					//////////////////////////////////////////////
					CView*							pView
				) 
{
	m_bGenBCur		= bGenBCurve;
	m_bGenBPat		= bGenBPatch;
	m_nTwistType	= nTwistType;
	/////////////////////////////
	int i;
	POSITION pos;
	//////////////////////////////////////////////////////////
	int nResult = MA_OK;
	//////////////////////////
	if(!IsDataCompatible(pNodeList,pCurveList,pCLatchList,pPatchList,pPLatchList,
													pTwistList,m_nTwistType) )
		return MA_ERROR;
	//////////////////////////////////////////////////////////
	m_SolidID		= SolidID;
	m_pDrSolid		= pDrSolid;
	m_pDrSolid->SetObjectID(SolidID);
	////////////////////////////////////////////////////////// ST_dir:XSec
	CDrPatch* pPatch	= (CDrPatch*)pPatchList->GetHead();
	PATCHLATCH PLatch	= pPLatchList->GetHead();
	//////////////////////////////////////////
	SetSolidDataFromPatch(pPatch);
	////////////////////////////////////////// get Old 
	pWORLD pPatConBZ_ST = new WORLD[m_nMaxSolidCNodes_ST];
	pDOUBLE pPatWtsBZ_ST = new double[m_nMaxSolidCNodes_ST];
	///
	GetPatCNodeCoords_N_Wts_XSection(pPatch, PLatch, pPatConBZ_ST, pPatWtsBZ_ST);
	////////////////////////////////////////////////////////// R-dir: Spine Curve
	CDrCurve* pCurve	= (CDrCurve*)pCurveList->GetHead();
	CURVELATCH CLatch	= pCLatchList->GetHead();
	//////////////////////////////////////////
//	SetPatchDataFromCurve(pCurve,2/*nDir*/);
	GetSolidInfoFromSpine_R(pCurve);
	////////////////////////////////////////////////////// CNs & Wts at Jn. Pts 
	int nConBZJn_R		= (m_bClosed_R)?m_nSegs_R:m_nSegs_R+1; 
	pWORLD pConBZ_R		= new WORLD[nConBZJn_R];
	pDOUBLE pWtsBZ_R	= new double[nConBZJn_R];
	///
	GetCNodeCoords_N_WtsAtJnPts_Spine(pCurve, CLatch, pConBZ_R, pWtsBZ_R);
	////////////////////////////////////////////////////////// R-dir: Tangents at Bez, Jn. Pts
	pWORLD pTanBZ_R		= new WORLD[m_nMaxSolidCNodes_R];
	///
	nResult = CreateTangentsAtJnPts_Spine(pCurve,CLatch,pTanBZ_R);
	////////////////////////////////////////////////////////// R-dir: Twist Info
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
    ////////////////////////////////////////////////////////// Anchor Node Coords.
	m_pFromIDNode	= (CDrNode*)(pNodeList->GetObject(0) );
	////////////////////////
    UnitAxisFromEndNodes(1);	// creates m_FromPt
	/////////////////////////////////////////////////////////////////////////////// Duct: Bez Jn CN Pts
	int nTotConsJn_STR	= m_nMaxSolidCNodes_ST*nConBZJn_R; 
	pWORLD pSolConsJn	= new WORLD[nTotConsJn_STR];
	pDOUBLE pSolWtsJn	= new double[nTotConsJn_STR];
	////////////////////////////////////////////////////////// 
	SolCNCoords_N_WtsAtJns(m_FromPt,
					pPatConBZ_ST, pPatWtsBZ_ST,m_nMaxSolidCNodes_ST,
					pConBZ_R,pTanBZ_R,nConBZJn_R,
					pTwist,pSolConsJn,pSolWtsJn,nTotConsJn_STR);
	/////////////////////////////////////////////////////////////////////////////// PostSolidData
	// Bez.Jn.Pts along Spine are Known; the interior BezPts. are obtained by Lofting
	// using SpineCurve as the Blending Curve for All CNodes of the XSectional Patch
	nResult = PostSolBezInfoUsingBlendingInfo(pDrSolid,pCurve/*SpineCurve*/,
					pSolConsJn,pSolWtsJn,m_nMaxSolidCNodes_S,m_nMaxSolidCNodes_T,nConBZJn_R/*nCurves*/,
					m_nMaxSolidCNodes_R);
	/////////////////// release memory
	delete [] pPatConBZ_ST;
	delete [] pPatWtsBZ_ST;
	delete [] pConBZ_R;
	delete [] pWtsBZ_R;
	delete [] pTanBZ_R;
	delete [] pTwist;
	delete [] pSolConsJn;
	delete [] pSolWtsJn;
	/////////////////////////////////////////////////////////////////////////////// Patch Bndry Curves
	CDListMgr						CurveList_W;
	CDListMgr*						pCurveList_W = &CurveList_W;
	pCurveList_W->RemoveAll();
	///
	CList<CURVELATCH,CURVELATCH>	CLatchList_W;
	CList<CURVELATCH,CURVELATCH>*	pCLatchList_W = &CLatchList_W;
	///
	CDListMgr						PatchList_U;
	CDListMgr*						pPatchList_U = &PatchList_U;
	pPatchList_U->RemoveAll();
	///
	CList<PATCHLATCH,PATCHLATCH>	PLatchList_U;
	CList<PATCHLATCH,PATCHLATCH>*	pPLatchList_U = &PLatchList_U;
	////////////////////////////////////////////////////////////////////////////// 
	// Distribute XSec Patch & Spine Curve
	////////////////////////////////////////////////// XSection Patch
	pPatchList_U->InsertObject(pPatchList->GetHead());
	pPLatchList_U->AddTail(pPLatchList->GetHead());
	////////////////////////////////////////////////// Spine Curve
	pCurveList_W->InsertObject(pCurveList->GetHead());
	pCLatchList_W->AddTail(pCLatchList->GetHead());
	//////////////////////////////////
	m_SolidType	= SO_TENSOR;
	///////////////////////////////////////////////
	nResult = SetInfoForDataBase(pDrSolid,
					pPatchList_U,pCurveList_W,
					pPLatchList_U,pCLatchList_W,pTwistList);
	/////////////////////////////////////////////////////////////////////////////// Done
	pPatchList_U->RemoveAll();
	pCurveList_W->RemoveAll();
	pPLatchList_U->RemoveAll();
	pCLatchList_W->RemoveAll();
	////////////////////////////////////////////////////////////////////////////// Bndry Curves
/*
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
*/
	//////////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
BOOL CMS_Duct::IsDataCompatible(CDListMgr* pNodeList,
					CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>*	pCLatchList,
					CDListMgr* pPatchList,CList<PATCHLATCH,PATCHLATCH>*	pPLatchList,
									CList<double,double>* pTwistList,int nTwistType)
{
	////////////////////////////////////////////////// CurveID
	if(pCurveList->GetCount() != 1)	// Spine Curve
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Duct::IsDataCompatible\npCurveList->GetCount() != 1");
		return FALSE;
	}
	////////////////////////////////////////////////// Latch
	if(pCLatchList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Duct::IsDataCompatible\npCLatchList->GetCount() != 1");
		return FALSE;
	}
	////////////////////////////////////////////////// PatchID
	if(pPatchList->GetCount() != 1)	// XSec. Patch
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Duct::IsDataCompatible\npPatchList->GetCount() != 1");
		return FALSE;
	}
	////////////////////////////////////////////////// Latch
	if(pPLatchList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Duct::IsDataCompatible\npPLatchList->GetCount() != 1");
		return FALSE;
	}
	////////////////////////////////////////////////// # of Twist Data
	if(nTwistType == 1)
	{
		CDrCurve* pSpineCurve	= (CDrCurve*)pCurveList->GetHead();
		CDListMgr* pCNList		= pSpineCurve->GetCNodeList();
		BOOL bClosed			= pSpineCurve->IsClosed_S();
		int	nBZSegs				= pSpineCurve->GetMaxBezSegments_S();
		int nMaxTwist			= (bClosed)?nBZSegs:nBZSegs+1; 
		/////////////
		if(pTwistList->GetCount() != nMaxTwist)
		{
			AfxMessageBox(
				"INTERNAL PROBLEM:\nCMS_Duct::IsDataCompatible\npTwistList->GetCount() != nCNs");
			return FALSE;
		}
	}
	////////////////////////////////////////////////// Anchor Node 
	if(pNodeList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMS_Duct::IsDataCompatible\npNodeList->GetCount() != 1");
		return FALSE;
	}
	///////////
	return TRUE;
}

int CMS_Duct::TwistProcess(pDOUBLE pTwist, int nTwist, double dScaleMax, double dTwistStart,
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
int CMS_Duct::SetSolidDataFromPatch(CDrPatch* pPatch)
{
	int i;
	pINT	pNum_t_S;
	pDOUBLE	pDis_t_S;
	pINT	pNum_t_T;
	pDOUBLE	pDis_t_T;
	///////
	pNum_t_S				= pPatch->GetNum_tPointer_S();
	pDis_t_S				= pPatch->GetDis_tPointer_S();
	pNum_t_T				= pPatch->GetNum_tPointer_T();
	pDis_t_T				= pPatch->GetDis_tPointer_T();
	///
	m_nSegs_S				= pPatch->GetMaxBezSegments_S();
	m_nSegs_T				= pPatch->GetMaxBezSegments_T();
	m_nOut_S				= (int)pPatch->GetOut_S();
	m_nOut_T				= (int)pPatch->GetOut_T();
	m_nOut_ST				= pPatch->GetLongOutPts();
	/////////////////////////////////////////////////////////// Memory
	if(pNum_t_S)
		m_pNum_t_S			= new int[m_nSegs_S];
	if(pDis_t_S)
		m_pDis_t_S			= new double[m_nOut_S];
	if(pNum_t_T)
		m_pNum_t_T			= new int[m_nSegs_T];
	if(pDis_t_T)
		m_pDis_t_T			= new double[m_nOut_T];
   ////////////////////////////////////////////////////////////
//	m_pNum_t_Ex_S			= pPatch->GetNum_tPointer_Ex_S();
//	m_pNum_t_Ex_T			= pPatch->GetNum_tPointer_Ex_T();
	//////////////////////////////////////////////////
	for (i=0;i<m_nSegs_S;i++)
	{
		if(pNum_t_S)
			m_pNum_t_S[i]		= pNum_t_S[i];
	}
	for (i=0;i<m_nSegs_T;i++)
	{
		if(pNum_t_T)
			m_pNum_t_T[i]		= pNum_t_T[i];
	}
	//
	for (i=0;i<m_nOut_S;i++)
	{
		if(pDis_t_S)
			m_pDis_t_S[i]		= pDis_t_S[i];
	}
	for (i=0;i<m_nOut_T;i++)
	{
		if(pDis_t_T)
			m_pDis_t_T[i]		= pDis_t_T[i];
	}
	////////////////////
	m_Ratio_S				= pPatch->GetRatio_S();
	m_Ratio_T				= pPatch->GetRatio_T();
	m_nMaxOSeg_S			= pPatch->GetOutSegUnif_S();
	m_nMaxOSeg_T			= pPatch->GetOutSegUnif_T();
	m_bUnifOT_S				= pPatch->IsUniform_S();
	m_bUnifOT_T				= pPatch->IsUniform_T();
	/////////////////////////////////////////////////////////////	
//	m_nOut_SCon				= (int)m_nMaxPatchCNodes_S;
//	m_nOut_TCon				= (int)m_nMaxPatchCNodes_T;
	////////////////////////////////////////////////// FILL INFO
	m_nDim_S				= pPatch->GetnDim_S();
	m_nDim_T				= pPatch->GetnDim_T();
	m_CurveType_S			= pPatch->GetCurveType_S();
	m_CurveType_T			= pPatch->GetCurveType_T();
	m_nOrder_S				= pPatch->GetOrder_S();
	m_nOrder_T				= pPatch->GetOrder_T();
	///////////////////////////////////////////	
 	m_bClosed_S				= pPatch->IsClosed_S();	// X-Section
	m_bClosed_T				= pPatch->IsClosed_T();	// X-Section
//	m_nSegs_SCon			= m_nOut_SCon - 1;
//	m_nSegs_TCon			= m_nOut_TCon - 1;
	m_nMaxSolidCNodes_S 	= pPatch->GetMaxCNodes_S();
	m_nMaxSolidCNodes_T 	= pPatch->GetMaxCNodes_T();
	m_nMaxSolidCNodes_ST 	= m_nMaxSolidCNodes_S * m_nMaxSolidCNodes_T;
//	m_nOut_STCon			= (int)m_nMaxSolidCNodes_ST;
	////////////////////////////////////////////////////
//	m_pWts_BZ_ST			= pPatch->GetMemInWts();		
	//////////////////////////////
	m_PatSubType			= pPatch->GetPatSubType();
	if(m_PatSubType == PS_TRIANGLE)
		m_SolSubType		= SS_PENTA; 
	else
	if(m_PatSubType == PS_QUADRILAT)
		m_SolSubType		= SS_HEXA;	// 
	///
	return MA_OK;

}

int CMS_Duct::GetPatCNodeCoords_N_Wts_XSection(CDrPatch* pPatch, PATCHLATCH pLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld)
{
	CDListMgr* pList	= pPatch->GetCNodeList();
	pDOUBLE pWts		= pPatch->GetMemInWts();
	int nCon_BZ			= (pPatch->GetMaxCNodes_S())*(pPatch->GetMaxCNodes_T());
	int nCon_IndexMax	= nCon_BZ -1;
	/////////////////////////////////////////////////////////////// Coords 
	int j=-1;
	if(!pList->IsEmpty())
	{
		////////
		for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
		{
			CDrNode* pNode = (CDrNode*)pList->GetNextObject(pos);
			///////////////////////////////////////
			if(pLatch == PL_FIRST_FORWARD)
				pConOld[++j] = *(pNode->GetLocalPos());
			else	// todo in-between Latching
			if(pLatch == PL_FOURTH_BACKWARD)
				pConOld[nCon_IndexMax - (++j) ] = *(pNode->GetLocalPos());
			//////////////////////////////////
		}
	}
	/////////////////////////////////////////////////////////////// Wts
	for(j=0;j<nCon_BZ;j++)
	{
		if(pLatch == PL_FIRST_FORWARD)
			pWtsOld[j] = pWts[j];
		else	// todo in-between Latching
		if(pLatch == PL_FOURTH_BACKWARD)
			pWtsOld[nCon_IndexMax - j] = pWts[j];
	}
	/////////
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////
int CMS_Duct::GetSolidInfoFromSpine_R(CDrCurve* pCurve)
{
	int i;
	pINT	pNum_t_R;
	pDOUBLE	pDis_t_R;
	///////
	pNum_t_R		= pCurve->GetNum_tPointer_S();
	pDis_t_R		= pCurve->GetDis_tPointer_S();
	///
	m_nSegs_R		= pCurve->GetMaxBezSegments_S();
	m_nOut_R		= (int)pCurve->GetLongOutPts();
	///
	if(pNum_t_R)
		m_pNum_t_R		= new int[m_nSegs_T];
	if(pDis_t_R)
		m_pDis_t_R		= new double[m_nOut_T];
	/////////////
	m_bClosed_R			= pCurve->IsClosed_S();
//			m_nDim_T			= pCurve->GetnDim_S();
	m_nDim_R			= 4;	// ALWAYS Rational;
	m_nOrder_R			= pCurve->GetOrder_S();
	m_nMaxSolidCNodes_R	= pCurve->GetMaxCNodes_S();
	m_nSegs_R 			= pCurve->GetMaxBezSegments_S();
	m_CurveType_R		= pCurve->GetCurveType_S();
	///
	m_Ratio_R			= pCurve->GetRatio_S();
	m_nOut_R			= (int)pCurve->GetLongOutPts();
	m_nMaxOSeg_R		= pCurve->GetOutSegUnif_S();
	m_bUnifOT_R			= pCurve->IsUniform_S();
	//////////////////////////////////////////////////
	for (i=0;i<m_nSegs_R;i++)
	{
		if(pNum_t_R)
			m_pNum_t_R[i]		= pNum_t_R[i];
	}
	for (i=0;i<m_nOut_R;i++)
	{
		if(pDis_t_R)
			m_pDis_t_R[i]		= pDis_t_R[i];
	}
	////////
	return MA_OK;
}

int CMS_Duct::GetCNodeCoords_N_WtsAtJnPts_Spine(CDrCurve* pCurve, CURVELATCH cLatch, 
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

int CMS_Duct::CreateTangentsAtJnPts_Spine(CDrCurve* pCurve,CURVELATCH cLatch,pWORLD pTangents)
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

int CMS_Duct::SolCNCoords_N_WtsAtJns(WORLD wAnchorPt,pWORLD pPatConBZ_ST,pDOUBLE pPatWtsBZ_ST,
							int nPatConBZ_ST,pWORLD pConJnBZ_R,pWORLD pTanJnBZ_R,int nConJnBZ_R,
									pDOUBLE pTwist,pWORLD pSolCons,pDOUBLE pSolWts,int nTotOut)
{
	////////////////////////////////////////////// generate Patch Pts
	CPA_Duct	PA_Duct;		 	   	
	int nOutActual	= PA_Duct.Duct
			(
				wAnchorPt,			//	Anchor 3D Pt. for Xsec scale,twist etc
		    	nPatConBZ_ST,		//	number of cross section points
		      	pPatConBZ_ST,		//	cross section curve ControlPts
		      	pPatWtsBZ_ST,		//	cross section Wts 
		   		nConJnBZ_R,			//	number of Spine Jn points
		      	pConJnBZ_R,			//	Spine curve ControlJnPts
		      	pTanJnBZ_R,			//	Spine curve Tangents at JnControlPts
		      	pTwist,				//	path Twist Factor distribution
				pSolCons,			//	Output ControlPts
				pSolWts				//	Output Wts array
			);	  
	////////////////////////////	
	if(nOutActual != nPatConBZ_ST*nConJnBZ_R)
		return -1;
	else 
		return 0;
												
}

int CMS_Duct::PostSolBezInfoUsingBlendingInfo(CDrSolid* pSolid,CDrCurve* pSpineCurve,
								pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ_S,int nConBZ_T,
												int nPatches/*nConBZJn_R*/,int nConBZ_R)
{
	// Blend Curve is the Spine Curve
	/////////////////////////////////
	// Patches in ST-dir and Blend Curve in R-dir
	// So, Transpose & Correctly Post Bezier Info	
	/////////////////////////////////////////////////////////////////////////////// Spine Curve
	// Blend Curve Contains R-directional Info:
	//			CurveType
	//			IsClosed
	CList<int,int>* pElSegList	= pSpineCurve->GetElperSegList_S();
	CList<int,int> ElSegList_R;
	ElSegList_R.AddTail(pElSegList);
	//
	double Ratio_R				= pSpineCurve->GetRatio_S();
	BOOL bClosed_R				= pSpineCurve->IsClosed_S();						 
	BOOL nDegree_R				= pSpineCurve->GetOrder_S() - 1;						 
	//////////////////////////////////////////////////////// BlendEnd
	BLENDEND BlendEnd;
	//////////////////
	BlendEnd.m_BCL	= pSpineCurve->GetBCL_S();
	BlendEnd.m_BCR	= pSpineCurve->GetBCR_S();
	BlendEnd.m_TanL	= pSpineCurve->GetTanL_S();
	BlendEnd.m_TanR	= pSpineCurve->GetTanR_S();
	////////////////////////////////////////////////////////////////////////////////
	int i,j,m;
	CDListMgr	INodeList;
	CDListMgr	TemCNodeList;	// temporarily store Solid BezPts( may be undesirable
								// Order, to be corrected at the end of this routine
	//////////////////////////////////////////////////////// Wts
	int nCon_S,nCon_T,nCon_R,nCon_ST;
	nCon_S					= nConBZ_S;
	nCon_T					= nConBZ_T;
	nCon_R					= nConBZ_R;
	nCon_ST					= nCon_S*nCon_T;
	///
//	nBezSeg_T				= (bClosed_T)?nCurves:nCurves-1;
//	nCon_T					= (bClosed_T)?(nDegree_T*nBezSeg_T):(nDegree_T*nBezSeg_T+1);
	pDOUBLE	pTemSolWts_BZ	= new double[nCon_S*nCon_T*nCon_R];
	CString SolID			= pSolid->GetObjectID();
	//////////////////////////////////////////////////////// Loop Over Bez. Pts. on Patches
	for(j=0;j<nCon_T;j++)
	{
		for(i=0;i<nCon_S;i++)
		{
			m = i + j*nCon_S; 
			//////////////////////////////////////////////////// Input Nodes 
			// Post temporarily Solid Bezier Junction CNodes as INodes
			// these will be deleted when temporary Patch in
			// GenerateSolidBezInfoFromBlendCurve SubRoutine is deleted
			// Similarly,pTemWts_DT
			///////////////////////
			INodeList.RemoveAll();
			TempPostSolBezJunctionPtsInINodeList(pConBZ,nCon_ST,m,nPatches,&INodeList);
			//////////////////////////////////////////////////// Input Weight
			pDOUBLE	pTemWts_DT = new double[nPatches];		
			PackSolBezJunctionWtsInDataWtsArray(pWtsBZ,nCon_ST,m,nPatches,pTemWts_DT);
			//////////////////////////////////////////////////// Now Generate
			GenerateSolidBezInfoFromSpineCurve(BlendEnd,pSpineCurve,&INodeList,
				pTemWts_DT,ElSegList_R,&TemCNodeList,pTemSolWts_BZ,Ratio_R,SolID,nCon_R,m);
			///
		}
	}
	////////////////////////////////////////////////////////////////////////// Post
	// Patch along ST-direction, So Transpose
	{
		PostPatBezInfo(pSolid,TemCNodeList,pTemSolWts_BZ,nCon_S,nCon_T,nCon_R);
		////////////////////////////// now remove from TemporaryList
		TemCNodeList.RemoveAll();
		////////////////////////////// delete
		delete [] pTemSolWts_BZ;
	}
	//////////////
	return MA_OK;
}

int CMS_Duct::PostPatBezInfo(CDrSolid* pSolid,CDListMgr& TemCNodeList,pDOUBLE pTemSolWts_BZ,
															int nCon_S,int nCon_T,int nCon_R)
{
	// All the Comments below is to be seen as only ONE
	//				of nCon_R many Patch Planes
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
	int i,j,k,m=-1,index;
	CDListMgr* pCNodeList	= pSolid->GetCNodeList();
	pDOUBLE	pSolWts_BZ		= new double[nCon_S*nCon_T*nCon_R];
	CDrNode* pNode;
	double Wts;
	POSITION pos;
	/////////////////////
	for(k=0;k<nCon_R;k++)
	{
		for(j=0;j<nCon_T;j++)
		{
			for(i=0;i<nCon_S;i++)
			{
				m++;
				index	= (i + j*nCon_S) * nCon_R + k; 
				pos		= TemCNodeList.FindIndex(index);
				pNode	= (CDrNode*)TemCNodeList.GetAt(pos);
				Wts		= pTemSolWts_BZ[index]; 
				///////////////////////////////////////////////// Save BezPts
				pCNodeList->InsertObject(pNode);
				pSolWts_BZ[m] = Wts;
				///////
			}
		}
	}
	///////////////////////////////////////////////////////// Save Wts
	pSolid->SetMemInWts(pSolWts_BZ);
	/////////////
	return MA_OK;

}
	
int CMS_Duct::TempPostSolBezJunctionPtsInINodeList(pWORLD pConBZ,int nConBZ_ST,int nRowCol,
												int nPatches,CDListMgr* pINodeList)
{
    ///////////////////////////////////////////////////
	WORLD		LocalPos;
    CDrNode* 	pAddNode;
	int			s,index;
	///////////////////////////////////////
	for (s = 0; s<nPatches; s++)
	{
		index = s*nConBZ_ST + nRowCol;	// (nRow,nCol) Bez.Pt of sth Patch
		//////////////////////////////////// Coords
		LocalPos = pConBZ[index];
	    //////////////////////////////////// Name
		CString* pNid = new CString;
		char* buf = pNid->GetBuffer(BUFF_SIZE);
	    sprintf(buf,"%s_%d%d","Temp",s,nRowCol);
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
	
int CMS_Duct::PackSolBezJunctionWtsInDataWtsArray(pDOUBLE pWtsBZ,int nConBZ_ST,int nRowCol,
												int nPatches,pDOUBLE pTemWts_BZ)
{
	int			s,index;
	///////////////////////////////////////
	for (s = 0; s<nPatches; s++)
	{
		index = s*nConBZ_ST + nRowCol;	// nCol Bez.Pt of sth Curve
		//////////////////////////////////// Wts
		pTemWts_BZ[s] = pWtsBZ[index]; 
	}
#ifdef _DEBUG					
	/////////////////////////////////////////// BEZIER Data Weights
	for (s = 0; s<nPatches; s++)
		double Wts = pTemWts_BZ[s];
#endif	 
	/////////////////////////////////////////////////////////////////////	
	return 0;
}

int CMS_Duct::GenerateSolidBezInfoFromSpineCurve(
						BLENDEND BlendEnd,CDrCurve* pSpineCurve,CDListMgr* pINodeList,
						pDOUBLE pWts_DT,CList<int,int>& ElSegList,CDListMgr* pSolCNodeList,
						pDOUBLE pSolWts_BZ,double Ratio,CString& SolidID,int nCon_R,int nRowCol)
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
	Copy_N_TransferBezControlInfo(pCurve,pSolCNodeList,SolidID,nRowCol);
	////////////////////////////////////////////////// Copy & Transfer Bezier Pts
	Copy_N_TransferBezWeightInfo(pCurve,pSolWts_BZ,nCon_R,nRowCol);
	////////////////////////////////////////////////// Now get rid of it
	pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
	///////////////////////////////
	return 0;
}
	 
int CMS_Duct::Copy_N_TransferBezControlInfo(CDrCurve* pCurve,CDListMgr* pSolCNodeList,
											CString& SolidID,int nRowCol)
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
	int nMaxCurveCNodes_R		= pCurve->GetnCon_BZ_S();// should be equal to #nCon_R
	CDListMgr* pCurCNodeList	= pCurve->GetCNodeList();
	///////////////////////////////////////
	for (s = 0; s<nMaxCurveCNodes_R; s++)
	{
		//////////////////////////////////// Coords
		pos = pCurCNodeList->FindIndex(s);
		LocalPos = *((CDrNode*)pCurCNodeList->GetAt(pos))->GetLocalPos();
	    //////////////////////////////////// Name
		CString* pNid = new CString;
		char* buf = pNid->GetBuffer(BUFF_SIZE);
	    sprintf(buf,"%s_%d_%d",SolidID,s,nRowCol);
		///////////////////////////////////// in THE List 
		pAddNode = PostNode(*pNid,LEVEL_KIDDO,LocalPos,TRUE);	// Create DrCNode
		delete pNid;
		/////////////
		if(!pAddNode)	// Create DrCNode
			return -1;
		///////////////////////////////////// in Curve 	
		pSolCNodeList->InsertObject(pAddNode); //CNodeList
	}
#ifdef _DEBUG					
	/////////////////////////////////////////// BEZIER Control Nodes
	WORLD Local;
	int ntemp = pSolCNodeList->GetCount();
	pList = pSolCNodeList;
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

int CMS_Duct::Copy_N_TransferBezWeightInfo(CDrCurve* pCurve,pDOUBLE pPatWts_BZ,int nCon_R,int nRowCol)
{
	pDOUBLE pWts	= pCurve->GetpWts_BZ_S(); 
	////////////////////////////////////////////////// Copy & Transfer Bezier Wts
	int i,j;
	for(i=0;i<nCon_R;i++)
	{
		j = nRowCol*nCon_R + i; 
		pPatWts_BZ[j]	= pWts[i];
	}
	///////////////////////////////
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
int CMS_Duct::SetInfoForDataBase(CDrSolid* pDrObject,
					CDListMgr* pPatchList_U,CDListMgr* pCurveList_W,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_W,
					CList<double,double>* pTwistList	// Distrib,if nTwistType = 1
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
    pDrObject->SetObjectType((int)SOLID);
    pDrObject->SetElemType((int)GENR_OBJECT);          // globals
    pDrObject->SetLevelType((int)LEVEL_GRAPA);          // globals
	pDrObject->SetSolidProc(SP_DUCT);
	pDrObject->SetSolidType(SO_TENSOR);
	pDrObject->SetSolSubType(m_SolSubType);
    //////////////////////////////
	pDrObject->SetObjectID(m_SolidID);
	//////////////////////////////////
	pDrObject->SetGenBCurve(m_bGenBCur);
	pDrObject->SetGenBPatch(m_bGenBPat);
	/////////////////////////////////////////////////////////////////// Info Based on nCurDir
	pDrObject->SetPrimaryDir(1);// 
	SetInfoForDataBase_1(pDrObject,	pCurveList_W,pCurveLatchList_W,
									pPatchList_U,pPatchLatchList_U,
									pTwistList);
	/////////////////////////////////////////////////////////
	m_nOut = (long)m_nOut_S * (long)m_nOut_T * (long)m_nOut_R;
	pDrObject->SetLongOutPts(m_nOut);			// m_nOut	
	//////////////////////////////////////////////////
	// call to NumberOfPatches() Overrides:	//
	//		m_nOut_S,m_nOut_T,m_nOut				//
	////////////////////////////////////////////////// 
	int nOutTotal = pDrObject->NumberOfSolides();
	if(nOutTotal != (int)m_nOut)
	{
		AfxMessageBox("Internal Problem:\nCMS_Duct::SetInfoForDataBase\nm_nOut Mismatch!");
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

void CMS_Duct::SetInfoForDataBase_1(CDrSolid* pDrObject,
					CDListMgr* pCurveList_W,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_W,
					CDListMgr* pPatchList_U,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_U,
					CList<double,double>* pTwistList	// Distrib,if nTwistType = 1
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
	////////////////////////////////////////////////////////// PatchList
	CDListMgr* pList; 
	POSITION pos;
	CDrPatch* pPatch;
	CDrCurve* pCurve;
	///////////////////////////////////////////////// U 
	pList = pDrObject->GetPatchList_U(); 
	pList->RemoveAll();
	pList->AddTail(pPatchList_U);
	pDrObject->GetPatchLatchList_U()->RemoveAll();
	pDrObject->GetPatchLatchList_U()->AddTail(pPatchLatchList_U);
	///////////////////////////////////////////////// W 
	pList = pDrObject->GetCurveList_W(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_W);
	pDrObject->GetCurveLatchList_W()->RemoveAll();
	pDrObject->GetCurveLatchList_W()->AddTail(pCurveLatchList_W);
	///////////////////////////////////////////////// Save:PatchList for Toplogy
	pList = pDrObject->GetPatchList();
	pList->RemoveAll();
	pList->AddTail(pPatchList_U);
	///////////////////////////////////////////////// Reciprocate:PatchList
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pPatch 	= (CDrPatch*)pList->GetNextObject(pos);
		/////////////////////////////////////////// does exist already?
		int index = pPatch->GetSolidList()->GetObjectIndex(pDrObject);
		if(index<0)
			pPatch->GetSolidList()->InsertObject(pDrObject);
	}
	///////////////////////////////////////////////// Save:CurveList for Toplogy
	pList = pDrObject->GetCurveList();
	pList->RemoveAll();
	pList->AddTail(pCurveList_W);
	///////////////////////////////////////////////// Reciprocate:CurveList
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		/////////////////////////////////////////// does exist already?
		int index = pCurve->GetSolidList()->GetObjectIndex(pDrObject);
		if(index<0)
			pCurve->GetSolidList()->InsertObject(pDrObject);
	}
	////////////////////////////////////////////// Reciprocate fromID: Anchor Node
	m_pFromIDNode->GetSolidList()->InsertObject(pDrObject);
	pDrObject->SetFromIDNode_R(m_pFromIDNode);
	////////////////////////////////////////////// Type_1: n
	pDrObject->SetTwistType_R(m_nTwistType);
	//
	pDrObject->GetTwistList_R()->RemoveAll();
	if(m_nTwistType == 1)
		pDrObject->GetTwistList_R()->AddTail(pTwistList);
	///////////////////////////////////////////////// Twist Multiplier
	pDrObject->SetIncTwist_R(m_bIncrement);
	pDrObject->SetTwistMult_R(m_TwistMult);
	pDrObject->SetTwistStart_R(m_TwistStart);
	///////////////////////////////////////////////////////////////// All Other
	pDrObject->SetRatio_S(m_Ratio_S);					
	pDrObject->SetRatio_T(m_Ratio_T);					
	pDrObject->SetRatio_R(m_Ratio_R);					
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetUniform_T(m_bUnifOT_T);		// Output Distribution:
	pDrObject->SetUniform_R(m_bUnifOT_R);		// Output Distribution:
	pDrObject->SetOutSegUnif_S(m_nMaxOSeg_S); 	// for Old Compatibility
	pDrObject->SetOutSegUnif_T(m_nMaxOSeg_T); 	// for Old Compatibility
	pDrObject->SetOutSegUnif_R(m_nMaxOSeg_R); 	// for Old Compatibility
	pDrObject->SetMaxOutSeg_S(m_nMaxOSeg_S);	// Number of Output Segments
	pDrObject->SetMaxOutSeg_T(m_nMaxOSeg_T);	// Number of Output Segments
	pDrObject->SetMaxOutSeg_R(m_nMaxOSeg_R);	// Number of Output Segments
//?
	pDrObject->SetMaxOutPts_S(m_nOut_S);
	pDrObject->SetMaxOutPts_T(m_nOut_T);
	pDrObject->SetMaxOutPts_R(m_nOut_R);
	pDrObject->SetOut_S(m_nOut_S);
	pDrObject->SetOut_T(m_nOut_T);
	pDrObject->SetOut_R(m_nOut_R);
	//////////////////////////////////////////
	pDrObject->SetCurveType_S(m_CurveType_S);
	pDrObject->SetCurveType_T(m_CurveType_T);
	pDrObject->SetCurveType_R(m_CurveType_R);
	pDrObject->SetMaxCNodes_S(m_nMaxSolidCNodes_S);
	pDrObject->SetMaxCNodes_T(m_nMaxSolidCNodes_T);
	pDrObject->SetMaxCNodes_R(m_nMaxSolidCNodes_R);
	///////////////////////////////////////////////////
//	pDrObject->SetSegmentCount_S(m_nSegs_S);	
//	pDrObject->SetSegmentCount_T(m_nSegs_T); 
	pDrObject->SetMaxBezSegments_S(m_nSegs_S);	
	pDrObject->SetMaxBezSegments_T(m_nSegs_T); 
	pDrObject->SetMaxBezSegments_R(m_nSegs_R); 
	pDrObject->SetClosed_S(m_bClosed_S);
	pDrObject->SetClosed_T(m_bClosed_T);
	pDrObject->SetClosed_R(m_bClosed_R);
	pDrObject->SetOut_S(m_nOut_S);	
	pDrObject->SetOut_T(m_nOut_T);
	pDrObject->SetOut_R(m_nOut_R);
	pDrObject->SetOrder_S(m_nOrder_S);
	pDrObject->SetOrder_T(m_nOrder_T);
	pDrObject->SetOrder_R(m_nOrder_R);
//	pDrObject->SetnDim_S(m_nDim_S);
//	pDrObject->SetnDim_T(m_nDim_T);
	pDrObject->SetnDim_S(4);	// ALWAYS RATIONAL
	pDrObject->SetnDim_T(4);	// ALWAYS RATIONAL
	pDrObject->SetnDim_R(4);	// ALWAYS RATIONAL
	///////////////////////////////////////////////////////// for now
	pDrObject->SetNum_tPointer_S(m_pNum_t_S);			// Number of Outputs for each Output Segment
	pDrObject->SetNum_tPointer_T(m_pNum_t_T);			// Number of Outputs for each Output Segment
	pDrObject->SetNum_tPointer_R(m_pNum_t_R);			// Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////
	pDrObject->SetDis_tPointer_S(m_pDis_t_S);			// s-distribution
	pDrObject->SetDis_tPointer_T(m_pDis_t_T);			// t-distribution
	pDrObject->SetDis_tPointer_R(m_pDis_t_R);			// r-distribution
	//////////////////////////////////////////////////////////////////////
	pDrObject->SetGenBCurve(m_bGenBCur);
	pDrObject->SetGenBPatch(m_bGenBPat);
	////////////////
	return;
}
//////////////////////////////////////////////////////////////////////////////////////
void CMS_Duct::Serialize(CArchive& ar)
{

	CMI_GangS::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMS_Duct:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMS_Duct:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
