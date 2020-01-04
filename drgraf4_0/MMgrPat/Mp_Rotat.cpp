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
#include "MC_Circle.h"
/////////////////////
#include "MP_Rotat.h" 

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
IMPLEMENT_SERIAL(CMP_Rotat,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMP_Rotat::CMP_Rotat()
{
	m_bDegen[0] = FALSE;
	m_bDegen[1] = FALSE;
	//
	m_nDegen[0] = -1;
	m_nDegen[1] = -1;
}

CMP_Rotat::~CMP_Rotat()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
int CMP_Rotat::GoDoIt 
				(
					BOOL							bGenBCurve,
					//////////////////////////////////////////
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					//////////////////////////////////////////
					CDListMgr*						pNodeList,	// ist record: pFromIDNode
																// 2nd record: pToIDNode
					//////////////////////////////////////////
					CDListMgr*						pCurveList,	// given Curves always taken as U-dir
																// and later switched,if needed,i.e.,
																// nCurDir = 2
					CList<CURVELATCH,CURVELATCH>*	pLatchList,
					//////////////////////////////////////////
					CList<int,int>&					ElperSegList_V, // ist record: elem/seg
																	// 2nd record: #of BezSeg
					double							dAngle_V,
					double							Ratio_V,
					BOOL							bAxis,
					int								nAxis,
					BOOL							bNegative,
					//////////////////////////////////////////////
					CView*							pView
				) 
{
	int i;
	//////////////////////////////////////////////////////////
	int nResult = MA_OK;
	/////////////////////
	if(!IsDataCompatible(pCurveList,pNodeList,pLatchList,&ElperSegList_V) )
		return MA_ERROR;
	//////////////////////////////////////////////////////////
	m_PatchID		= PatchID;
	m_pDrPatch		= pDrPatch;
	m_pDrPatch->SetObjectID(PatchID);
	////////////////////////////////////////////////////////// S_dir
	CDrCurve* pCurve	= (CDrCurve*)pCurveList->GetHead();
	CURVELATCH cLatch	= pLatchList->GetHead();
	//////////////////////////////////////////
	// do this one all the way down again
	// because when Curve_V are created
	// all data with _S are disturbed
	SetPatchDataFromCurve(pCurve,1/*nDir*/);
	////////////////////////////////////////// get Old 
	pWORLD pCon_BZ = new WORLD[m_nMaxPatchCNodes_S];
	pDOUBLE pWts_BZ = new double[m_nMaxPatchCNodes_S];
	///
	GetCNodeCoords_N_Wts(pCurve, cLatch, pCon_BZ, pWts_BZ);
	////////////////////////////////////////////////////////// T-dir
	m_pFromIDNode	= (CDrNode*)(pNodeList->GetObject(0) );
	m_pToIDNode		= (CDrNode*)(pNodeList->GetObject(1) );
	m_bAxis			= bAxis;
	m_nAxis			= nAxis;
	m_bNegative		= bNegative;
	m_dAng_2		= dAngle_V;
	///////////////////////////////////////////////////////////////////////////////// T-direction
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
	nResult = LatticeCircles(PatchID,pCon_BZ,ElperSegList_V,Ratio_V,dAngle_V,
									m_nMaxPatchCNodes_S/*Curves*/,pCurveList_V);
	if(nResult == MA_ERROR)
		return nResult;
	///////////////////////////////////////////////////////////// do it again,see Comment Before
	SetPatchDataFromCurve(pCurve,1/*nDir*/);
	/////////////////////////////////////////////////////////////////////////////// PostPatchData
	PatCNodes_N_WtsFromCircles(pDrPatch,pCurveList_V,pCurveList,pWts_BZ);// need to multiply by Curve Wts
	/////////////////////////////////////////////////////////////////////////////// Patch Bndry Curves
	m_bGenBCur = bGenBCurve;
	if(bGenBCurve)
	{
		///////////////////////////////////////////////
		for(i=0;i<m_nMaxPatchCNodes_T/*nCurves_U*/;i++)
			LatchList_U.AddTail(CL_FORWARD);
		////////////////////////////////////////////////// Create LatticeCurves_U
														// at Bez. JnPts. Only	
		nResult = LatticeCurves_U(pDrPatch,m_nOrder_T,m_bClosed_T,m_nSegs_T,
									m_nMaxPatchCNodes_S,pCurve,pCurveList_U);
		if(nResult == MA_ERROR)
			return nResult;
		////////////////////////////////////////////////// Keep LatticeCircles_V 
														// at Bez. JnPts. Only
		for(i=0;i<m_nMaxPatchCNodes_S/*nCurves_V*/;i++)
			LatchList_V.AddTail(CL_FORWARD);
		nResult = PostProcessLatticeCircles_V(pCurveList_V,pLatchList_V,m_nOrder_S);
		if(nResult == MA_ERROR)
			return nResult;
	}
	else	// delete CurveList_V;
		DeleteCurveList_V(pCurveList_V,pLatchList_V);
	/////////////////////////////////////////////////////// Extracted Curves are Independent
															// of Patch
	pCurveList_U->RemoveAll();
	pCurveList_V->RemoveAll();
	/////////////////////////////////////////////////////// put Original Curve in CurveList_U
	pCurveList_U->AddTail(pCurveList);
	//////////////////////////////////
	m_PatchType	= PA_TENSOR;
	///////////////////////////////////////////////
	pDrPatch->GetElperSegList_T()->RemoveAll();
	pDrPatch->GetElperSegList_T()->AddTail(&ElperSegList_V);	// save for later editing etc
	////////////////
	nResult = SetInfoForDataBase(pDrPatch,pCurveList_U,pCurveList_V,
					pLatchList_U,pLatchList_V);
	/////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
BOOL CMP_Rotat::IsDataCompatible(CDListMgr* pCurveList,CDListMgr* pNodeList,
								CList<CURVELATCH,CURVELATCH>*	pLatchList,
								CList<int,int>* pElperSegList)
{
	////////////////////////////////////////////////// CurveID
	if(pCurveList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Rotat::IsDataCompatible\npCurveList->GetCount() != 1");
		return FALSE;
	}
	////////////////////////////////////////////////// Latch
	if(pLatchList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Rotat::IsDataCompatible\npLatchList->GetCount() != 1");
		return FALSE;
	}
	CDrCurve* pDrCurve	= (CDrCurve*)(pCurveList->GetObject(0) );
	////////////////////////////////////////////////// Mesh
	// ist record: elem/seg
	// 2nd record: #of BezSeg
	if(pElperSegList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Rotat::IsDataCompatible\npElperSegList->GetCount() != 2");
		return FALSE;
	}
	////////////////////////////////////////////////// FromNodeID & ToNodeID 
	if(pNodeList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Rotat::IsDataCompatible\npNodeList->GetCount() != 2");
		return FALSE;
	}
	///////////
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMP_Rotat::SetPatchDataFromCurve(CDrCurve* pCurve,int nDir)
{
	int i;
	pINT	pNum_t_T;
	pDOUBLE	pDis_t_T;
	pDOUBLE	pDis_Ang_T;
	///////
	if(nDir == 2)
	{
		pNum_t_T		= pCurve->GetNum_tPointer_S();
		pDis_t_T		= pCurve->GetDis_tPointer_S();
		pDis_Ang_T		= pCurve->GetDis_AngPointer_S();
		///
		m_nSegs_T		= pCurve->GetMaxBezSegments_S();
		m_nOut_T		= (int)pCurve->GetLongOutPts();
		///
		if(pNum_t_T)
			m_pNum_t_T		= new int[m_nSegs_T];
		if(pDis_t_T)
			m_pDis_t_T		= new double[m_nOut_T];
		if(pDis_Ang_T)
			m_pDis_Ang_T	= new double[m_nSegs_T];
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
				if(pDis_Ang_T)
					m_pDis_Ang_T[i]		= pDis_Ang_T[i];
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
//////////////////////////////////////////////////////////////////////////////////// T-Direction
int CMP_Rotat::LatticeCircles 
				(
					CString&						PatchID,		
					pWORLD&							pConBZ, 	
					//////////////////////////////////////////////
					CList<int,int>&					ElperSegList,
					double							Ratio,
					double							Angle,
					int								nCurves,		// nCNodes_U
					///////////////////////////////////////////////
					CDListMgr*						pCurveList		// CurveList_V
				) 
{
	CMsMath MsMath;
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	//////////////////////////////////////////////////////////////////////
	int nResult = MA_OK;
	//
	double dCoLin = pHitNet->GetCoLinear();
	///////////////////////////////////////
	pWORLD pwx0;
	pWORLD pwx1;
	pWORLD pwx2;
	///////////////////////////////////////////////////////////////////////////////// Degenerate Pts
	pwx0	= m_pFromIDNode->GetLocalPos();
	pwx1	= m_pToIDNode->GetLocalPos();
	//
	int i,j=0;
	BOOL bDG;
	for(i=0;i<nCurves;i++)
	{
		pwx2	= &(pConBZ[i]);
		bDG		= MsMath.IsCoLinear(pwx0,pwx1,pwx2,dCoLin);
		///
		if(bDG)
		{
			m_bDegen[j] = TRUE;
			m_nDegen[j] = i;
			///
			j++;
		}
	}
	///////////////////////////////////////////////////////////////////////////////// U,S-direction
	nResult = CreateCircleList(PatchID,pConBZ,ElperSegList,pCurveList,
													Ratio,Angle,nCurves);
	if(nResult == MA_ERROR)
	{
		AfxMessageBox("Internal ERROR\nCMP_Rotat::LatticeCircles\nCreateCircleList Problem");
		return MA_ERROR;
	}
	////////////////
	CDrCurve* pCurve = (CDrCurve*)pCurveList->GetHead();
	nResult = SetPatchDataFromCurve(pCurve,2);
	///////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMP_Rotat::CreateCircleList(CString& PatchID,pWORLD pConBZ,CList<int,int>& ElSegList,
								CDListMgr* pCurveList,double Ratio,double dAngle,int nCurves)
{
	CMC_Circle	MC_Circle;
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	///////////////////
	int i;
	CDListMgr	NodeList;
	CList<int,int> TemElSegList;	// in MC_Circle ElSeglist get disturbed,so temporary
	//////////////////////////////////////////////////////// Loop Over Bez. Pts. on Curves
	for(i=0;i<nCurves;i++)
	{
		if	(
				( m_bDegen[0] && (i	== m_nDegen[0]) )  || 
				( m_bDegen[1] && (i	== m_nDegen[1]) )
			)
			continue;
		/////////////////////////
		NodeList.RemoveAll();
		TemElSegList.RemoveAll();
		//////////////////////////////////////////////////// Input Nodes 
		CreatePackINodeForCircle(PatchID,pConBZ[i],&NodeList);
		////////////////////////////////////////////////////// Add to DataBase, if not Existing
		int nActiveIndex;
		CDrCurve* pCurve;
		///////////////////
		pObjectMgr->SetActiveObjectType(CURVE);
		////////////////////////////////////////////////////// Add to DataBase
		CString	ID;
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
		///////////////////////////////////////// Get rid of Old CNodes & INodes
		if(!(pCurve->GetCNodeList()->IsEmpty())  )
			pCurve->GetCNodeList()->RemoveAll();
		if(!(pCurve->GetINodeList()->IsEmpty())  )
			pCurve->GetINodeList()->RemoveAll();
		//////////////////////////////////////////////////////// Fill Input Nodes
		CDListMgr* pINodeList = pCurve->GetINodeList();
		pINodeList->AddTail(&NodeList);	// copy
		///////////////////////////////////////////////////////
		pCurve->SetRatio_S(Ratio);
		if(dAngle >= 360.)
			pCurve->SetClosed_S(TRUE);
		else
			pCurve->SetClosed_S(FALSE);
		//////////////////////////////////// if Axis Input
		MC_Circle.SetAxisInput(m_bAxis);
		MC_Circle.SetAxis(m_nAxis);
		MC_Circle.SetNegative(m_bNegative);
		//////////////////////////////////////////////////// Now Generate
		TemElSegList.AddTail(&ElSegList);
		pCurve = MC_Circle.CreateCircle(
								ID,pCurve,&NodeList,CP_CIRCLE,&TemElSegList,
								CIRCLE_BY_ROT,dAngle,120/*m_SegAngle*/,0.0/*m_dRadius*/,
								FALSE/*m_bArc*/,m_pFromIDNode,m_pToIDNode,TRUE/*bFinal*/);
		/////////////////
		if(!pCurve)
		{
			pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
			return MA_ERROR;
		}
		//////////////////////////////////////////////////// Save
		if(pCurve)
			pCurveList->InsertObject(pCurve);
	}
	//////////////
	return MA_OK;
}

int CMP_Rotat::CreatePackINodeForCircle(CString& PatchID,WORLD& wLocalPos,CDListMgr* pINodeList)
{
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	CDrNode*	pINode;
	CString		ID;
	CDrLabel*	pLabel;
	int			nNodeIndex,nLabelIndex;
	//////////////////////////////// Create an INode
	pObjectMgr->SetObjInfoID(ID,INODE);
//	ID += "_" + PatchID;
	/////////////////////////// Create Anyway
	nNodeIndex = -12345;
	pINode = CreateNode(ID,pLabel,wLocalPos,FALSE/*Not CNode*/,TRUE,
							nNodeIndex,nLabelIndex,LEVEL_GRAPA);
	//////////////////////////////////
	if(!pINode)	// Create DrNode
	return MA_ERROR;
	///////////////////////////////////
	pINodeList->InsertObject(pINode);
	/////////////
	return MA_OK;
}

int CMP_Rotat::PatCNodes_N_WtsFromCircles(CDrPatch* pDrPatch,CDListMgr* pCurveList_V,
													CDListMgr* pCurveList,pDOUBLE pWts_BZ)
{
	// need to multiply by Curve Wts
	// because the circles are in Std. Form
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
	////////////////////////////////////////////////////////// CNodes & Wts
	pCurve	= (CDrCurve*)pCurveList_V->GetHead();
	pCNList	= pCurve->GetCNodeList();
	nNodes_V= pCNList->GetCount(); 
	///////////////////////////////////
	nCurves = pCurveList_V->GetCount();
	if(m_bDegen[0])
		nCurves++;
	if(m_bDegen[1])
		nCurves++;
	///////////////////////////////////
	nTotal	= nNodes_V * nCurves;
	///////////////////
	pDOUBLE		pWts = new double[nTotal];  	
	//
	for(i=0;i<nNodes_V;i++)
	{
		m = -1;
		///////
		for(j=0;j<nCurves;j++)
		{
			k++;
			////
			WtsOriginal = pWts_BZ[j];
			//////////////////////////////////// Name
			CString* pNid = new CString;
			char* buf = pNid->GetBuffer(BUFF_SIZE);
			sprintf(buf,"%s_%d_%d",PatchID,j,i);
			////////////////////////////////////////////////// Degenerate:1
			if( m_bDegen[0] && (j == m_nDegen[0]) )
			{
				////
				pCurve	= (CDrCurve*)pCurveList->GetObject(0);
				pCNList	= pCurve->GetCNodeList();
				pCNode	= (CDrNode*)pCNList->GetObject(j);
				if(pCNode)
				{
					pDrPatch->GetCNodeList()->InsertObject(pCNode);
					////////////////////////////////////////////////// Wts
					pWtsCur	= pCurve->GetpWts_BZ_S();
					pWts[k]	= pWtsCur[j];
				}
				else
					return MA_ERROR;
				///////////
				continue;
			}
			////////////////////////////////////////////////// Degenerate:2
			else
			if( m_bDegen[1] && (j == m_nDegen[1]) )
			{
				////
				pCurve	= (CDrCurve*)pCurveList->GetObject(0);
				pCNList	= pCurve->GetCNodeList();
				pCNode	= (CDrNode*)pCNList->GetObject(j);
				if(pCNode)
				{
					pDrPatch->GetCNodeList()->InsertObject(pCNode);
					////////////////////////////////////////////////// Wts
					pWtsCur	= pCurve->GetpWts_BZ_S();
					pWts[k]	= pWtsCur[j];
				}
				else
					return MA_ERROR;
				///////////
				continue;
			}
			////////////////////////////////////////////////// Regular 
			else
			{
				m++;
				////
				pCurve	= (CDrCurve*)pCurveList_V->GetObject(m);
				pCNList	= pCurve->GetCNodeList();
				pCNode	= (CDrNode*)pCNList->GetObject(i);
				if(pCNode)
					wLocalPos = *(pCNode->GetLocalPos());
				else
					return MA_ERROR;
				////////////////////////////////////////////////// Create & Save
				pNewNode = PostNode(*pNid,LEVEL_KIDDO,wLocalPos,TRUE);	// Create DrCNode
				delete pNid;
				//////////////////////////////////
				if(!pNewNode)	// Create DrCNode
					return MA_ERROR;
				///////////////////////////////////
				pDrPatch->GetCNodeList()->InsertObject(pNewNode);
				////////////////////////////////////////////////// Wts
				pWtsCur	= pCurve->GetpWts_BZ_S();
				pWts[k]	= pWtsCur[i] * WtsOriginal;
			}
		}
	}
	////////////////////////////////////////////////////////// save Wts
	pDrPatch->SetMemInWts(pWts);
	////////////
	//////////////////////////////////////////////////// View Matrices
#ifdef _DEBUG
	///////////////////////////////////////
	if(1 != 1 ) // iDLL = 12 , Module = 1
	{
		k = -1;
		///////
		pCNList	= pDrPatch->GetCNodeList();
		pWtsCur = pDrPatch->GetMemInWts();
		///////////////////
		CString* str = new CString;
		char* buf = str->GetBuffer(BUFF_SIZE);
		////////////////////
		sprintf(buf,"CMP_Rotat::PatCNodes_N_WtsFromCircles");
		AfxMessageBox(*str);
		///////////////////
		for(i=0;i<nNodes_V;i++)
		{
			j = sprintf(buf,"CNode[Column_%d]\n",i);
			j += sprintf(buf + j,"Row#      X             Y            Z         Wt\n");
			//////////////////////
			for(m=0;m<nCurves;m++)
			{
				k++;
				pCNode	= (CDrNode*)pCNList->GetObject(k);
				if(pCNode)
					wLocalPos = *(pCNode->GetLocalPos());
				
				///
				j += sprintf( buf + j, "%2d %7.2f %7.2f %7.2f %7.2f\n", m,
		   				wLocalPos.x,wLocalPos.y,wLocalPos.z,pWtsCur[k] );

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

int CMP_Rotat::LatticeCurves_U(CDrPatch* pDrPatch,int nOrder_T,BOOL bClosed_T,int nSegBZ_T,
							int nConBZ_S,CDrCurve* pCurOriginal,CDListMgr* pCurveList)
{
	CMI_GangC	MI_GangC;
	/////////////////////
	// Create LatticeCurves_U at Bez. JnPts. Only
	/////////////////////////////////////////////
	// Hints: geteach set of Cnodes Col from pDrPatch and create a Curve
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
		CreateFillINodeList(pDrPatch,i,nINode,nDegree_S,nDegree_T,nConBZ_S,&INodeList);
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
		CD.pElSegList	= pCurOriginal->GetElperSegList_S();	
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

int CMP_Rotat::CreateFillINodeList(CDrPatch* pDrPatch,int iCurve_U,int nINode_U,
								int nDegree_S,int nDegree_T,int nConBZ_S,CDListMgr* pINodeList)
{
	int nResult;
	//////////////////////////////////////
	CDListMgr* pCNList	= pDrPatch->GetCNodeList();
	CString PatchID		= pDrPatch->GetObjectID();
	//////////////////////
	nResult =  PackINodeList(PatchID,pCNList,iCurve_U,nINode_U,nDegree_S,nDegree_T,pINodeList,
																					nConBZ_S);
	////////////
	if(nResult == MA_ERROR)
		return MA_ERROR;
	//////////////
	return MA_OK;
}

int CMP_Rotat::PackINodeList(CString& PatchID,CDListMgr* pCNodeList,int iCurve_U,int nINode,
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

int CMP_Rotat::PostProcessLatticeCircles_V(CDListMgr* pCurveList_V,
							CList<CURVELATCH,CURVELATCH>* pLatchList_V,int nOrder_S)
{
	if(pCurveList_V->IsEmpty())
		return MA_ERROR;
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pCurList	= pObjectMgr->GetObjectList(CURVE);
	///////////////////
	CDrCurve*	pCurve;
	CURVELATCH	Latch;
	POSITION	pos;
	int			i,nDeg_U,nCurves,nCurveIndex;
	CDListMgr	TemCurList;
	///
	TemCurList.AddTail(pCurveList_V);
	pCurveList_V->RemoveAll();
	/////////////////////////
	CList<CURVELATCH,CURVELATCH> TemLatList;
	TemLatList.AddTail(pLatchList_V);
	pLatchList_V->RemoveAll();
	////////////////////////
	nCurves = TemCurList.GetCount();
	nDeg_U	= nOrder_S - 1;
	//////////////////////
	for(i=0;i<nCurves;i++)
	{
		pCurve	= (CDrCurve*)TemCurList.GetObject(i);
		pos		= TemLatList.FindIndex(i);
		Latch	= TemLatList.GetAt(pos);	
		///////////////////
		if((i%nDeg_U) == 0)	// Jn. Curves
		{	
			///////////////////////////////////////// ReParametrize Bez Wts, in case
			ReParametrizeBezWeightsToStdForm(pCurve);
			///////////////////////////////////////// Change Color
			pCurve->SetPenInfo(0,MAGENTA,PS_SOLID);
			pCurve->SetShow(TRUE);
			////////////////////////////////// insert
			pCurveList_V->InsertObject(pCurve);
			pLatchList_V->AddTail(Latch);
		}
		else	// delete the Curve
		{
			nCurveIndex = pCurList->GetObjectIndex(pCurve);
			if(nCurveIndex>=0)
				pObjectMgr->DeleteFromDataBase(nCurveIndex, CURVE);
		}
		/////
	}
	////////////
	return MA_OK;
}

int CMP_Rotat::DeleteCurveList_V(CDListMgr* pCurveList_V,
							CList<CURVELATCH,CURVELATCH>* pLatchList_V)
{
	if(pCurveList_V->IsEmpty())
		return MA_OK;
	//////////////////////////
	pLatchList_V->RemoveAll();
	//////////////////////////////////////////// MI_GangP
	return DeleteCurves_LockStock(pCurveList_V);
	////////////
}
/////////////////////////////////////////////////////////////////////////////////////
int CMP_Rotat::GetCNodeCoords_N_Wts(CDrCurve* pCurve, CURVELATCH cLatch, 
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
int CMP_Rotat::SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V)
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
	pDrObject->SetPatchProc(PP_ROTATE);
	pDrObject->SetPatchType(PA_TENSOR);
	pDrObject->SetPatSubType(PS_QUADRILAT);
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	//////////////////////////////////
	pDrObject->SetGenBCurve(m_bGenBCur);
	/////////////////////////////////////////////////////////////////// Info Based on nCurDir
	pDrObject->SetPrimaryDir(1);// 
	SetInfoForDataBase_1(pDrObject,	pCurveList_U,pCurveLatchList_U,
										pCurveList_V,pCurveLatchList_V);
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
		AfxMessageBox("Internal Problem:\nCMP_Rotat::SetInfoForDataBase\nm_nOut Mismatch!");
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

void CMP_Rotat::SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V)
{
	////////////////////////////////////////////////////////// CurveList
	CDListMgr* pList; 
	POSITION pos;
	CDrCurve* pCurve;
	///////////////////////////////////////////////// 
	pList = pDrObject->GetCurveList_U(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_U);
	pDrObject->GetCurveLatchList_U()->RemoveAll();
	pDrObject->GetCurveLatchList_U()->AddTail(pCurveLatchList_U);
	///////////////////////////////////////////////// Reciprocate
	pList = pDrObject->GetCurveList(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_U);
	///
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		/////////////////////////////////////////// does exist already?
		int index = pCurve->GetPatchList()->GetObjectIndex(pDrObject);
		if(index<0)
			pCurve->GetPatchList()->InsertObject(pDrObject);
	}
	///////////////////////////////////////////////// 
/*
	pList = pDrObject->GetCurveList_V(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList_V);
	/////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		///////////////////////// ReParametrize Bez Wts, in case
		ReParametrizeBezWeightsToStdForm(pCurve);
		////////////////////////////////// Change Color for IsoCurves
		pCurve->SetPenInfo(0,MAGENTA,PS_SOLID);
		pCurve->SetShow(TRUE);
		/////////////////////////////////////////// does exist already?
		int index = pCurve->GetPatchList()->GetObjectIndex(pDrObject);
		if(index<0)
			pCurve->GetPatchList()->InsertObject(pDrObject);
	}
	/////////////////////////////////////////////////////////////////
//	pDrObject->SetBlendCurve_U(pBlendCurve_U);
	pDrObject->GetCurveLatchList_V()->RemoveAll();
	pDrObject->GetCurveLatchList_V()->AddTail(pCurveLatchList_V);
//	pDrObject->SetBlendCurve_V(pBlendCurve_V);
*/
	////////////////////
	m_pFromIDNode->GetPatchList()->InsertObject(pDrObject);
	pDrObject->SetFromIDNode_T(m_pFromIDNode);
	///
	m_pToIDNode->GetPatchList()->InsertObject(pDrObject);
	pDrObject->SetToIDNode_T(m_pToIDNode);
	///////////////////////////////////////////////////////////////// Rotation
	pDrObject->SetAxisInput_T(m_bAxis);	// Set if Axis Input
	pDrObject->SetAxisType_T(m_nAxis);		// 1=X/2=Y/3=Z
	pDrObject->SetNegative_T(m_bNegative);
	pDrObject->SetCircleType_T(CIRCLE_BY_ROT);
	pDrObject->SetAng_2_T(m_dAng_2);
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
	pDrObject->SetDis_AngPointer_T(m_pDis_Ang_T);		// Distribution of angles 
	////////////////
	return;
}
//////////////////////////////////////////////////////////////////////////////////////
void CMP_Rotat::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMP_Rotat:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMP_Rotat:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
