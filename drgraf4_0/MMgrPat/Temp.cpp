// Loft2.cpp : implementation file
//
///////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"

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
#include "PA_Duct.h" 
#include "MP_Duct.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#define MAGENTA		RGB(255,0,255)	// Jn. Curve Color
#define BUFF_SIZE	1024
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMP_Duct,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMP_Duct::CMP_Duct()
{
}

CMP_Duct::~CMP_Duct()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
int CMP_Duct::GoDoIt 
				(
					BOOL							bGenBCurve,
					int								nDuctType,
									// 1 = Given: Twist Distribution
									// 2 = Given: Twist Increments etc
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
					CList<double,double>*			pTwistList,	// Distrib,if nDuctType = 1
					double							TwistMult,	// if nDuctType = 2 
					BOOL							bIncrement,
					double							TwistStart,
					//////////////////////////////////////////////
					CView*							pView
				) 
{
	m_nDuctType	= nDuctType;
	/////////////////////////////
	int i;
	POSITION pos;
	//////////////////////////////////////////////////////////
	int nResult = MA_OK;
	//////////////////////////
	if(!IsDataCompatible(pCurveList,pNodeList,pLatchList,pTwistList,
														,m_nDuctType) )
		return MA_ERROR;
	//////////////////////////////////////////////////////////
	m_PatchID		= PatchID;
	m_pDrPatch		= pDrPatch;
	m_pDrPatch->SetObjectID(PatchID);
	/////////////////////////////////
	CDrCurve* pCurve;
	CURVELATCH cLatch;
	////////////////////////////////////////////////////////// S_dir: XSection Curve
	CDrCurve* pCurve	= (CDrCurve*)pCurveList->GetHead();
	CURVELATCH cLatch	= pLatchList->GetHead();
	//////////////////////////////////////////
	SetPatchDataFromCurve(pCurve,1/*nDir*/);
	////////////////////////////////////////// get Old 
	pWORLD pConBZ_S		= new WORLD[m_nMaxPatchCNodes_S];
	pDOUBLE pWtsBZ_S	= new double[m_nMaxPatchCNodes_S];
	///
	GetCNodeCoords_N_Wts(pCurve, cLatch, pConBZ_S, pWtsBZ_S);
	////////////////////////////////////////////////////////// T-dir: Spine Curve
	CDrCurve* pCurve	= (CDrCurve*)pCurveList->GetTail();
	CURVELATCH cLatch	= pLatchList->GetTail();
	//////////////////////////////////////////
	SetPatchDataFromCurve(pCurve,2/*nDir*/);
	////////////////////////////////////////// get Old 
	pWORLD pConBZ_T		= new WORLD[m_nMaxPatchCNodes_T];
	pDOUBLE pWtsBZ_T	= new double[m_nMaxPatchCNodes_T];
	///
	GetCNodeCoords_N_Wts(pCurve, cLatch, pConBZ_T, pWtsBZ_T);
	////////////////////////////////////////////////////////// T-dir: Tangents
	pWORLD pTanBZ_T		= new WORLD[m_nMaxPatchCNodes_T];
	///
	nResult = CreateTangents_Spine(pCurve,cLatch,pTanBZ_T)
	GetTangents(pCurve, cLatch, pTanBZ_T);
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
		pTwist[i]	= pTwistList->GetAT(pos);
	}
	///
	TwistProcess(pTwist, m_nMaxPatchCNodes_T, m_TwistMult, m_bIncTwist);
    ////////////////////////////////////////////////////////// Anchor Node Coords.
	m_pFromIDNode	= (CDrNode*)(pNodeList->GetObject(0) );
	////////////////////////
    UnitAxisFromEndNodes(1);	// creates m_FromPt
	/////////////////////////////////////////////////////////////////////////////// Duct
	int nTotCons	= m_nMaxPatchCNodes_S*m_nMaxPatchCNodes_T;
	pWORLD pPatCons = new WORLD[nTotCons];
	pDOUBLE pPatWts	= new double[nTotCons];
	///////
	PatCNCoords_N_Wts(m_FromPt,pConBZ_S,pWtsBZ_S,nConBZ_S,pConBZ_T,pTanBZ_T,nConBZ_T,
					pDOUBLE pTwist,pWORLD pPatCons,pDOUBLE pPatWts,nTotOut);
	/////////////////////////////////////////////////////////////////////////////// PostPatchData
	PostPatCNodes_N_Wts(pDrPatch,pPatCons,pPatWts,nConBZ_S,pConBZ_T);
	/////////////////// release memory
	delete [] pConBZ_S;
	delete [] pWtsBZ_S;
	delete [] pConBZ_T;
	delete [] pWtsBZ_T;
	delete [] pTanBZ_T;
	delete [] pTwist;
	delete [] pPatCons;
//	delete [] pPatWts;	// done in Patch
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
	/////////////////////////////////////////////////////////////
	m_bGenBCur = bGenBCurve;
	if(bGenBCurve)
	{
		///////////////////////////////////////////////
		for(i=0;i<m_nMaxPatchCNodes_T/*nCurves_U*/;i++)
			LatchList_U.AddTail(CL_FORWARD);
		////////////////////////////////////////////////// Create LatticeCurves_U
														// at Bez. JnPts. Only
		pCurve = (CDrCurve*)pCurveList->GetHead(); //patterned after XSection Curve 
		nResult = LatticeCurves_U(pDrPatch,m_nOrder_T,m_bClosed_T,m_nSegs_T,
									m_nMaxPatchCNodes_S,pCurve,pCurveList_U);
		if(nResult == MA_ERROR)
			return nResult;
		///////////////////////////////////////////////
		for(i=0;i<m_nMaxPatchCNodes_S/*nCurves_V*/;i++)
			LatchList_V.AddTail(CL_FORWARD);
		////////////////////////////////////////////////// Create LatticeCurves_V
														// at Bez. JnPts. Only	
		pCurve = (CDrCurve*)pCurveList->GetTail(); //patterned after Spine Curve 
		nResult = LatticeCurves_V(pDrPatch,m_nOrder_T,m_bClosed_T,m_nSegs_T,
									m_nMaxPatchCNodes_T,pCurve,pCurveList_V);
		if(nResult == MA_ERROR)
			return nResult;
	}
	else
	{
		////////////////////////////////////////////////// XSection Curve
		pCurveList_U->InsertObject(pCurveList->GetHead());
		pLatchList_U->AddTail(pLatchList->GetHead());
		////////////////////////////////////////////////// Spine Curve
		pCurveList_V->InsertObject(pCurveList->GetTail());
		pLatchList_V->AddTail(pLatchList->GetTail());
	}
	//////////////////////////////////
	m_PatchType	= PA_TENSOR;
	nResult = SetInfoForDataBase(pDrPatch,bGenBCurve,
					pCurveList_U,pCurveList_V,
					pLatchList_U,pLatchList_V,pTwistList);
	/////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
BOOL CMP_Duct::IsDataCompatible(CDListMgr* pCurveList,CDListMgr* pNodeList,
								CList<CURVELATCH,CURVELATCH>*	pLatchList,
								CList<double,double>* pTwistList,int nDuctType)
{
	////////////////////////////////////////////////// CurveID
	if(pCurveList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Duct::IsDataCompatible\npCurveList->GetCount() != 2");
		return FALSE;
	}
	////////////////////////////////////////////////// Latch
	if(pLatchList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Duct::IsDataCompatible\npLatchList->GetCount() != 2");
		return FALSE;
	}
	CDrCurve* pDrCurve	= (CDrCurve*)(pCurveList->GetObject(0) );
	////////////////////////////////////////////////// # of Twist Data
	if(nDuctType == 1)
	{
		CDrCurve* pCurSpine = (CDrCurve*)pCurveList->GetTail();
		CDListMgr* pCNList	= pCurSpine->GetCNodeList();
		int nCNs			= pCNList->GetCount();
		if(pTwistList->GetCount() != nCNs)
		{
			AfxMessageBox(
				"INTERNAL PROBLEM:\nCMP_Duct::IsDataCompatible\npTwistList->GetCount() != nCNs");
			return FALSE;
		}
	}
	////////////////////////////////////////////////// FromNodeID & ToNodeID 
	if(pNodeList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Duct::IsDataCompatible\npNodeList->GetCount() != 1");
		return FALSE;
	}
	///////////
	return TRUE;
}

int CMP_Duct::TwistProcess(pDOUBLE pTwist, int nTwist, double dScaleMax, double dTwistStart,
																		BOOL bIncremental)
{
	/////////////////////////////////////////////
	int		i;
	////////////////////////////
	pDOUBLE p = pTwist;
	///////////////////////////////////////////////// No Twist
	if(dScaleMax == 0.0)
	{
		///////////
		for(i=0;i<nTwist;i++)
			*(p+i) = 0.0;
		/////////
		return 0;
	}
	///////////////////////////////////////////////// Incremental
	if(bIncremental)
	{
		double dInc = dScaleMax; // could be +ve or -ve
		*p = dTwistStart;
		///////////
		for(i=1;i<nTwist;i++)
			*(p+i) = *(p+i-1) + dInc;
		/////////
		return 0;
	}
	///////////////////////////////////////////////// Maximum
	double	yMaxP;
	double	yMaxN;
	double	val;
	/////////////////
	yMaxP =  -DBL_MAX;
	yMaxN =   DBL_MAX;
	//////////////////////////////// Brackets
	for (i=0;i<nTwist;i++)
	{
		val = *(p+i);
		///////////////////// y
		if(val>=0)
		{
			if(val>yMaxP)
				yMaxP = val;
		}
		else
		{
			if(val<yMaxN)
				yMaxN = val;
		}
	}
	////////////////////
	if(yMaxP == -DBL_MAX)
		yMaxP = 0.0;
	if(yMaxN == DBL_MAX)
		yMaxN = 0.0;
	///////////////////////////
	double Scale;
	double diff = yMaxP - yMaxN;
	if(diff == 0.0)
		Scale = 0.0;
	else
		Scale = ScaleMax/diff;
	//////////////////////////////// Scale
	// change value 
	///////////
	for(i=0;i<nTwist;i++)
		*(p+i) *= Scale;
	////////////
	return 0;

}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMP_Duct::SetPatchDataFromCurve(CDrCurve* pCurve,int nDir)
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
		m_nSegs_T		= pCurve->GetMaxCubicCurves(); // misleading name!
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
			m_nSegs_S 			= pCurve->GetMaxCubicCurves(); // misleading name!
			m_CurveType_S		= pCurve->GetCurveType_S();
			///
			m_nOut_S			= (int)pCurve->GetLongOutPts();
			m_nMaxOSeg_S		= pCurve->GetSegmentCount_S();
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
			m_nSegs_T 			= pCurve->GetMaxCubicCurves(); // misleading name!
			m_CurveType_T		= pCurve->GetCurveType_S();
			///
			m_Ratio_T			= pCurve->GetRatio_S();
			m_nOut_T			= (int)pCurve->GetLongOutPts();
			m_nMaxOSeg_T		= pCurve->GetSegmentCount_S();
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

int CMP_Duct::GetCNodeCoords_N_Wts(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld)
{
	CDListMgr* pList	= pCurve->GetCNodeList();
	pDOUBLE pWts		= pCurve->GetpWts_BZ_S();
	int nCon_BZ			= pCurve->GetMaxCNodes_S();
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
			if(cLatch == CL_FORWARD)
				pConOld[++j] = *(pNode->GetLocalPos());
			else
			if(cLatch == CL_BACKWARD)
				pConOld[nCon_IndexMax - (++j) ] = *(pNode->GetLocalPos());
			//////////////////////////////////
		}
	}
	/////////////////////////////////////////////////////////////// Wts
	for(j=0;j<nCon_BZ;j++)
	{
		if(cLatch == CL_FORWARD)
			pWtsOld[j] = pWts[j];
		else
		if(cLatch == CL_BACKWARD)
			pWtsOld[nCon_IndexMax - j] = pWts[j];
	}
	/////////
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////
int CMP_Duct::CreateTangents_Spine(CDrCurve* pCurve,CURVELATCH cLatch,pWORLD pTangents)
{
	// Create Tangents at Control Nodes
	///////////////////////////////////
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
	int			index;
	////////////////////////////////////////////////////////////////////////// tan_ALL at CNodes
	int			nConBZ = pCurve->GetCNodeList()->GetCount(); 
	index = -1;
	///////////
	for (POSITION pos = pCurve->GetCNodeList()->GetHeadPosition();pos !=NULL;)
	{
		pCNode		= (CDrNode*)(pCurve->GetCNodeList()->GetNext(pos));
		wNodeCoord	= *(pCNode->GetLocalPos());
		pCurve->Get_TangentAtaNode(wNodeCoord,tan,pHitNet->GetDblRatio());
		/////////////////////////////////////////// Scale by deltaKnot[i] = Knot[i+1]-Knot[i]
		index++;
		pDOUBLE Knot = pCurve->GetpKnots_S();	
		double deltaKnot = Knot[index+1]-Knot[index]; 
		Math3D.Scale3DPts(1./deltaKnot, &tan);
		/////////////////////////////////////////// save
		if(cLatch == CL_FORWARD)
			pTangents[index] = tan;
		else
		if(cLatch == CL_BACKWARD)
			pTangents[nConBZ-1-index] = tan;
		///////////////

	}
	/////////////
	return MA_OK;
}

int CMP_Duct::PatCNCoords_N_Wts(	WORLD wAnchorPt,	
									pWORLD pConBZ_S,pDOUBLE pWtsBZ_S,int nConBZ_S,
									pWORLD pConBZ_T,pWORLD pTanBZ_T,int nConBZ_T,pDOUBLE pTwist,
									pWORLD pPatCons,pDOUBLE pPatWts,int nTotOut)
{
	////////////////////////////////////////////// generate Patch Pts
	CPA_Duct	PA_Duct;		 	   	
	int nOutActual	= PA_Duct.Duct
			(
				wAnchorPt,		//	Anchor 3D Pt. for Xsec scale,twist etc
		    	nConBZ_S,		//	number of cross section points
		      	pConBZ_S,		//	cross section curve ControlPts
		      	pWtsBZ_S,		//	cross section Wts 
		   		nConBZ_T,		//	number of Spine points
		      	pConBZ_T,		//	Spine curve ControlPts
		      	pTanBZ_T,		//	Spine curve Tangents at ControlPts
		      	pTwist,			//	path Twist Factor distribution
				pPatCons,		//	Output ControlPts
				pPatWts			//	Output Wts array
			);	  
	////////////////////////////	
	if(nOutActual != nOut)
		return -1;
	else 
		return 0;
												
}

int CMP_Duct::PostPatCNodes_N_Wts(CDrPatch* pDrPatch,pWORLD pPatCons,pDOUBLE pPatWts,
															int nConBZ_S,int nConBZ_T)
{
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int i,j,k=-1,m,nNodes_V,nCurves,nTotal;
	CDListMgr	TemList;
	CDrCurve*	pCurve;
	CDListMgr*	pCNList;
	CDrNode*	pCNode;
	CDrNode*	pNewNode;
	pDOUBLE		pWtsCur;
	double		WtsOriginal;
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
		sprintf(buf,"CMP_Duct::PatCNodes_N_Wts");
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
///////////////////////////////////////////////////////////////////////////////////////////
int CMP_Duct::LatticeCurves_U(CDrPatch* pDrPatch,int nOrder_T,BOOL bClosed_T,int nSegBZ_T,
							int nConBZ_S,CDrCurve* pCurOriginal,CDListMgr* pCurveList)
{
	CMI_GangC	MI_GangC;
	/////////////////////
	// Create LatticeCurves_U at Bez. JnPts. Only
	/////////////////////////////////////////////
	// Hints: geteach set of Cnodes COL from pDrPatch and create a Curve
	// with other similar properties as pCurveOriginal except
	// Create New INodes from Jn. Pt. CNodes  and 
	// Fill CNodeList from ALL CNodes
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
		///////////////////////////////////////// Get rid of CNodes & INodes
		pCurve->GetCNodeList()->RemoveAll();
		pCurve->GetINodeList()->RemoveAll();
		/////////////////////////////////////////////////////// 
		// Fill NodeList w/ INodes created from Jn.Pt CNodes of Patch
		CDListMgr INodeList;
		int nINode = pCurOriginal->GetINodeList()->GetCount(); // Original Curve Compatible
		//////////
		int nDegree_S = pCurOriginal->GetOrder_S() - 1;
		int nDegree_T = nOrder_T - 1;
		CreateFillINodeList_S(pDrPatch,i,nINode,nDegree_S,nDegree_T,nConBZ_S,&INodeList);
		/////////////////////////////////////////////////////////////// Fill Input Nodes
		pCurve->GetINodeList()->AddTail(&INodeList);	// copy
		/////////////////////////////////////////////////////// Fill Data
		CURVEDATA CD;
		/////////////
		CD.ID			= ID;	
		CD.CurveType	= pCurOriginal->GetCurveType_S();
		CD.CircType		= pCurOriginal->GetCircleType();
		CD.bFinal		= TRUE;
		CD.bAdvanceOn	= FALSE;
		///////////////////////
		CD.pNodeList	= &INodeList;	
		CD.pElSegList	= pCurOriginal->GetElperSegList();	
		///////////////////////
 		CD.pFromNode	= pCurOriginal->GetFromIDNode_S();  //
 		CD.pToNode		= pCurOriginal->GetToIDNode_S();  //
		CD.bAxis		= pCurOriginal->IsAxisInput();
		CD.nAxis		= pCurOriginal->GetAxis();
		CD.bNegative	= pCurOriginal->IsNegative();
		CD.dAng			= pCurOriginal->GetTheta_S();
		CD.SegAngle		= pCurOriginal->GetSegAngle_S();
		CD.dRadius		= pCurOriginal->GetRadius_S();
		CD.bArc			= pCurOriginal->IsArcType();
		//////////////////////////////////// Create
		int nResult = MI_GangC.CreateCurveAnyType(pCurve,CD);
		///////////
		if(nResult == MA_ERROR)
		{
			pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
			return MA_ERROR;
		}
		//////////////////////////////////////////////////// Save
		if(pCurve)
		{
			///////////////////////////////////////// ReParametrize Bez Wts, in case
			ReParametrizeBezWeightsToStdForm(pCurve);
			///////////////////////////////////////// Change Color
			pCurve->SetPenInfo(0,MAGENTA,PS_SOLID);
			pCurve->SetShow(TRUE);
			/////////////////////////////////
			pCurveList->InsertObject(pCurve);
		}
	}
	//////////////
	return MA_OK;
}

int CMP_Duct::CreateFillINodeList_S(CDrPatch* pDrPatch,int iCurve_U,int nINode_U,
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

int CMP_Duct::PackINodeList_S(CString& PatchID,CDListMgr* pCNodeList,int iCurve_U,int nINode,
									 int nDeg_U,int nDeg_V,CDListMgr* pINodeList,int nConBZ_S)
{
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int			i,index,nBeg;
	CDrNode*	pCNode;
	CDrNode*	pINode;
	WORLD		wLocalPos;
	CString		ID;
	CDrLabel*	pLabel;
	int			nNodeIndex,nLabelIndex;
	////////////////////////
	pINodeList->RemoveAll();
	////////////////////////
	nBeg	= (iCurve_U * nDeg_V /*= iCol*/) * nConBZ_S;
	for(i=0;i<nINode;i++)
	{
		index	= nBeg + i * nDeg_U; 
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
///////////////////////////////////////////////////////////////////////////////////////////
int CMP_Duct::LatticeCurves_V(CDrPatch* pDrPatch,int nOrder_T,BOOL bClosed_T,int nSegBZ_T,
							int nConBZ_S,CDrCurve* pCurOriginal,CDListMgr* pCurveList)
{
	CMI_GangC	MI_GangC;
	/////////////////////
	// Create LatticeCurves_V at Bez. JnPts. Only
	/////////////////////////////////////////////
	// Hints: geteach set of Cnodes ROW from pDrPatch and create a Curve
	// with other similar properties as pCurveOriginal except
	// Create New INodes from Jn. Pt. CNodes  and 
	// Fill CNodeList from ALL CNodes
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
		///////////////////////////////////////// Get rid of CNodes & INodes
		pCurve->GetCNodeList()->RemoveAll();
		pCurve->GetINodeList()->RemoveAll();
		/////////////////////////////////////////////////////// 
		// Fill NodeList w/ INodes created from Jn.Pt CNodes of Patch
		CDListMgr INodeList;
		int nINode = pCurOriginal->GetINodeList()->GetCount(); // Original Curve Compatible
		//////////
		int nDegree_S = pCurOriginal->GetOrder_S() - 1;
		int nDegree_T = nOrder_T - 1;
		CreateFillINodeList_T(pDrPatch,i,nINode,nDegree_S,nDegree_T,nConBZ_S,&INodeList);
		/////////////////////////////////////////////////////////////// Fill Input Nodes
		pCurve->GetINodeList()->AddTail(&INodeList);	// copy
		/////////////////////////////////////////////////////// Fill Data
		CURVEDATA CD;
		/////////////
		CD.ID			= ID;	
		CD.CurveType	= pCurOriginal->GetCurveType_S();
		CD.CircType		= pCurOriginal->GetCircleType();
		CD.bFinal		= TRUE;
		CD.bAdvanceOn	= FALSE;
		///////////////////////
		CD.pNodeList	= &INodeList;	
		CD.pElSegList	= pCurOriginal->GetElperSegList();	
		///////////////////////
 		CD.pFromNode	= pCurOriginal->GetFromIDNode_S();  //
 		CD.pToNode		= pCurOriginal->GetToIDNode_S();  //
		CD.bAxis		= pCurOriginal->IsAxisInput();
		CD.nAxis		= pCurOriginal->GetAxis();
		CD.bNegative	= pCurOriginal->IsNegative();
		CD.dAng			= pCurOriginal->GetTheta_S();
		CD.SegAngle		= pCurOriginal->GetSegAngle_S();
		CD.dRadius		= pCurOriginal->GetRadius_S();
		CD.bArc			= pCurOriginal->IsArcType();
		//////////////////////////////////// Create
		int nResult = MI_GangC.CreateCurveAnyType(pCurve,CD);
		///////////
		if(nResult == MA_ERROR)
		{
			pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
			return MA_ERROR;
		}
		//////////////////////////////////////////////////// Save
		if(pCurve)
		{
			///////////////////////////////////////// ReParametrize Bez Wts, in case
			ReParametrizeBezWeightsToStdForm(pCurve);
			///////////////////////////////////////// Change Color
			pCurve->SetPenInfo(0,MAGENTA,PS_SOLID);
			pCurve->SetShow(TRUE);
			/////////////////////////////////
			pCurveList->InsertObject(pCurve);
		}
	}
	//////////////
	return MA_OK;
}

int CMP_Duct::CreateFillINodeList_T(CDrPatch* pDrPatch,int iCurve_V,int nINode_V/*BzJnPts*/,
					int nDegree_S,int nDegree_T,int nConBZ_S,CDListMgr* pINodeList)
{
	int nResult;
	//////////////////////////////////////
	CDListMgr* pCNList	= pDrPatch->GetCNodeList();
	CString PatchID		= pDrPatch->GetObjectID();
	//////////////////////
	nResult =  PackINodeList_T(PatchID,pCNList,iCurve_V,nINode_V,
						nDegree_S,nDegree_T,pINodeList,nConBZ_S);
	////////////
	if(nResult == MA_ERROR)
		return MA_ERROR;
	//////////////
	return MA_OK;
}

int CMP_Duct::PackINodeList_T(CString& PatchID,CDListMgr* pCNodeList,int iCurve_V,int nINode_V,
							int nDeg_U,int nDeg_V,CDListMgr* pINodeList,int nConBZ_S)
{
	// Get CNodes of iCurve_V Row at Bez. Jn. Pts
	/////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int			i,index,nBeg;
	CDrNode*	pCNode;
	CDrNode*	pINode;
	WORLD		wLocalPos;
	CString		ID;
	CDrLabel*	pLabel;
	int			nNodeIndex,nLabelIndex;
	////////////////////////
	pINodeList->RemoveAll();
	////////////////////////
	nBeg	= iCurve_V * nDeg_U /*= iRow*/;
	for(i=0;i<nINode_V;i++)
	{
		index	= nBeg + i * nDeg_V * nConBZ_S; 
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
int CMP_Duct::SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CList<double,double>* pTwistList	// Distrib,if nDuctType = 1
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
	pDrObject->SetPatchProc(PP_EXTRUDE);
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
									pTwistList);
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
		AfxMessageBox("Internal Problem:\nCMI_GangP::InsertMeshInfo\nm_nOut Mismatch!");
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

void CMP_Duct::SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CList<double,double>* pTwistList	// Distrib,if nDuctType = 1
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
	///////////////////////////////////////////////// Reciprocate
	pList = pDrObject->GetCurveList(); 
	///
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
	pDrObject->SetDuctType_T(m_nDuctType);
	//
	if(m_nDuctType == 1)
		pDrObject->GetTwistList_T()->AddTail(pTwistList);
	///////////////////////////////////////////////// Twist Multiplier
	pDrObject->SetIncTwist_T(m_bIncrement);
	pDrObject->SetTwistMult_T(m_TwistMult);
	pDrObject->SetTwistStart_T(m_TwistStart);
	///////////////////////////////////////////////////////////////// All Other
	pDrObject->SetRatio_S(m_Ratio_S);					
	pDrObject->SetRatio_T(m_Ratio_T);					
	pDrObject->SetUniform_S(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetUniform_T(m_bUnifOT_T);		// Output Distribution:
	pDrObject->SetSegmentCount_S(m_nMaxOSeg_S); 	// for Old Compatibility
	pDrObject->SetSegmentCount_T(m_nMaxOSeg_T); 	// for Old Compatibility
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
	pDrObject->SetSegmentCount_S(m_nSegs_S);	
	pDrObject->SetSegmentCount_T(m_nSegs_T); 
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
//////////////////////////////////////////////////////////////////////////////////////
void CMP_Duct::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMP_Duct:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMP_Duct:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
