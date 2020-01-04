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
#include "MP_Xtrud.h" 

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
IMPLEMENT_SERIAL(CMP_Xtrud,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMP_Xtrud::CMP_Xtrud()
{
}

CMP_Xtrud::~CMP_Xtrud()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
int CMP_Xtrud::GoDoIt 
				(
					BOOL							bGenBCurve,
					int								nExtruType,
									// 1 = Given: Extrusion Direction Nodes
									// 2 = Given: 3 Lenths (wLen) to Extrude to
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
					WORLD							wLen_V,
					double							dLen_V,
					double							Ratio_V,
					//////////////////////////////////////////////
					CView*							pView
				) 
{
	m_nExtruType	= nExtruType;
	/////////////////////////////
	int i;
	//////////////////////////////////////////////////////////
	int nResult = MA_OK;
	//////////////////////////
	if(!IsDataCompatible(pCurveList,pNodeList,pLatchList,&ElperSegList_V
														,m_nExtruType) )
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
	if(nExtruType == 1)
	{
		m_dLen			= dLen_V;
		m_pFromIDNode	= (CDrNode*)(pNodeList->GetObject(0) );
		m_pToIDNode		= (CDrNode*)(pNodeList->GetObject(1) );
		///////////////////////////////////////// AxisVector from
    											// end nodes	
		UnitAxisFromEndNodes(0);
	}
	else
	if(nExtruType == 2)
	{
		m_wLen = wLen_V;
		///////////////////////////////////////// AxisVector from wLen
		m_dLen = UnitAxis_N_LenFromWorldLength();
	}
	///////
	ProceessLength_N_Axis(m_nExtruType,m_dLen,m_wLen);
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
	nResult = LatticeCurves_V(PatchID,pCon_BZ,ElperSegList_V,Ratio_V,m_vAxis,m_dLen,
						m_nMaxPatchCNodes_S/*Curves*/,pCurve,pCurveList_V);
	if(nResult == MA_ERROR)
		return nResult;
	///////////////////////////////////////////////////////////// do it again,see Comment Before
	SetPatchDataFromCurve(pCurve,1/*nDir*/);
	/////////////////////////////////////////////////////////////////////////////// PostPatchData
	PatCNodes_N_WtsFromCurves(pDrPatch,pCurveList_V,pCurveList,pWts_BZ);// need to multiply by Curve Wts
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
		nResult = PostProcessLatticeCurves_V(pCurveList_V,pLatchList_V,m_nOrder_S);
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
int CMP_Xtrud::ProceessLength_N_Axis(int nExtruType,double& dLen,WORLD& wLen)
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
	/////////////////////////////////////////////////////////////////// Type_1: fromID,ToID,dLen
	if(nExtruType == 1)
	{
		/////////////////////////////////////////// strip Scale Factor (World Coord)
		pObjectMgr->SCtoDS(&dLen);
		dLen *= (dWorldBase/dMapFactor);
	}
	else
	/////////////////////////////////////////////////////////////////// Type_2: wLen
	if(nExtruType == 2)
	{
		/////////////////////////////////////////// strip Scale Factor (World Coord)
		pObjectMgr->SCtoDS(&wLen.x);
		pObjectMgr->SCtoDS(&wLen.y);
		pObjectMgr->SCtoDS(&wLen.z);
		wLen.x *= (dWorldBase/dMapFactor);
		wLen.y *= (dWorldBase/dMapFactor);
		wLen.z *= (dWorldBase/dMapFactor);
	}
	/////////////
	return MA_OK;
}

BOOL CMP_Xtrud::IsDataCompatible(CDListMgr* pCurveList,CDListMgr* pNodeList,
								CList<CURVELATCH,CURVELATCH>*	pLatchList,
								CList<int,int>* pElperSegList,int nExtruType)
{
	////////////////////////////////////////////////// CurveID
	if(pCurveList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Xtrud::IsDataCompatible\npCurveList->GetCount() != 1");
		return FALSE;
	}
	////////////////////////////////////////////////// Latch
	if(pLatchList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Xtrud::IsDataCompatible\npLatchList->GetCount() != 1");
		return FALSE;
	}
	CDrCurve* pDrCurve	= (CDrCurve*)(pCurveList->GetObject(0) );
	////////////////////////////////////////////////// Mesh
	if(pElperSegList->GetCount() != 1)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Xtrud::IsDataCompatible\npElperSegList->GetCount() != 1");
		return FALSE;
	}
	////////////////////////////////////////////////// FromNodeID & ToNodeID 
	if((nExtruType == 1) && pNodeList->GetCount() != 2)
	{
		AfxMessageBox("INTERNAL PROBLEM:\nCMP_Xtrud::IsDataCompatible\npNodeList->GetCount() != 2");
		return FALSE;
	}
	///////////
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMP_Xtrud::SetPatchDataFromCurve(CDrCurve* pCurve,int nDir)
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
//////////////////////////////////////////////////////////////////////////////////// T-Direction
int CMP_Xtrud::LatticeCurves_V 
				(
					CString&						PatchID,		
					pWORLD&							pConBZ, 	
					//////////////////////////////////////////////
					CList<int,int>&					ElperSegList,
					double							Ratio,
					WORLD							wAxis,
					double							dLen,
					int								nCurves,		// nCNodes_U
					///////////////////////////////////////////////
					CDrCurve*						pCurOriginal,
					CDListMgr*						pCurveList		// CurveList_V
				) 
{
	///////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr	= pDoc->GetObjectMgr();
	CHitNet* pHitNet		= (CHitNet*)pObjectMgr->GetSpecObject(HITNET);
	//////////////////////////////////////////////////////////////////////
	int nResult = MA_OK;
	///////////////////////////////////////////////////////////////////////////////// U,S-direction
	nResult = CreateCurveList_V(PatchID,pConBZ,ElperSegList,pCurveList,pCurOriginal,
													Ratio,wAxis,dLen,nCurves);
	if(nResult == MA_ERROR)
	{
		AfxMessageBox("Internal ERROR\nCMP_Xtrud::LatticeCircles\nCreateCircleList Problem");
		return MA_ERROR;
	}
	////////////////
	CDrCurve* pCurve = (CDrCurve*)pCurveList->GetHead();
	nResult = SetPatchDataFromCurve(pCurve,2);
	///////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMP_Xtrud::CreateCurveList_V(CString& PatchID,pWORLD pConBZ,CList<int,int>& ElSegList,
					CDListMgr* pCurveList,CDrCurve* pCurOriginal,double Ratio,WORLD wAxis,
																double dLen,int nCurves)
{
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	CDListMgr*	pList;
	///////////////////
	int i;
	WORLD		wXtruPt;
	CDListMgr	NodeList;
	CList<int,int> TemElSegList;	// in MC_Circle ElSeglist get disturbed,so temporary
	//////////////////////////////////////////////////////// Loop Over Bez. Pts. on Curves
	for(i=0;i<nCurves;i++)
	{
		/////////////////////////
		NodeList.RemoveAll();
		TemElSegList.RemoveAll();
		TemElSegList.AddTail(&ElSegList);
		//////////////////////////////////////////////////// Extrude Ctrl Pt. 
		GetAPtByExtrusion(&(pConBZ[i]), wAxis, dLen, wXtruPt);
		//////////////////////////////////////////////////// Input 2 Nodes 
		CreatePackINodeForCurve(PatchID,pConBZ[i],&NodeList);
		CreatePackINodeForCurve(PatchID,wXtruPt,&NodeList);
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
		/////////////////////////////////////////////////////// Fill Input Nodes
		pCurve->GetINodeList()->AddTail(&NodeList);	// copy
		///////////////////////////////////////////////////////
		pCurve->SetRatio_S(Ratio);
		pCurve->SetClosed_S(FALSE);
		/////////////////////////////////////////////////////// Fill Data
		CURVEDATA CD;
		/////////////
		CD.ID			= ID;	
		CD.CurveType	= CP_LINEAR;
		CD.bFinal		= TRUE;
		CD.bAdvanceOn	= FALSE;
		///////////////////////
		CD.pNodeList	= &NodeList;	
		CD.pElSegList	= &TemElSegList;	
		//////////////////////////////////// Create
		int nResult = CreateCurveAnyType(pCurve,CD);	//MI_GangC
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

int CMP_Xtrud::GetAPtByExtrusion(pWORLD pDOld, WORLD dir, double depth, WORLD& wNew)
{

    /////////////////////
	wNew.x = pDOld->x + depth * (dir.x);
	wNew.y = pDOld->y + depth * (dir.y);
	wNew.z = pDOld->z + depth * (dir.z);
    /////
	return MA_OK;
}	

int CMP_Xtrud::CreatePackINodeForCurve(CString& PatchID,WORLD& wLocalPos,CDListMgr* pINodeList)
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

int CMP_Xtrud::PatCNodes_N_WtsFromCurves(CDrPatch* pDrPatch,CDListMgr* pCurveList_V,
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
			////////////////////////////////////////////////// Regular 
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
		sprintf(buf,"CMP_Xtrud::PatCNodes_N_WtsFromCircles");
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

int CMP_Xtrud::LatticeCurves_U(CDrPatch* pDrPatch,int nOrder_T,BOOL bClosed_T,int nSegBZ_T,
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

int CMP_Xtrud::CreateFillINodeList(CDrPatch* pDrPatch,int iCurve_U,int nINode_U,
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

int CMP_Xtrud::PackINodeList(CString& PatchID,CDListMgr* pCNodeList,int iCurve_U,int nINode,
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

int CMP_Xtrud::PostProcessLatticeCurves_V(CDListMgr* pCurveList_V,
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

int CMP_Xtrud::DeleteCurveList_V(CDListMgr* pCurveList_V,
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
int CMP_Xtrud::GetCNodeCoords_N_Wts(CDrCurve* pCurve, CURVELATCH cLatch, 
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
int CMP_Xtrud::SetInfoForDataBase(CDrPatch* pDrObject,
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
		AfxMessageBox("Internal Problem:\nCMP_Xtrud::SetInfoForDataBase\nm_nOut Mismatch!");
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

void CMP_Xtrud::SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V)
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
	////////////////////////////////////////////// Type_1: fromID,ToID,dLen
	pDrObject->SetExtruType_T(m_nExtruType);
	//
	if(m_nExtruType == 1)
	{
		////////////////////////////////////////// Reciprocate
		m_pFromIDNode->GetPatchList()->InsertObject(pDrObject);
		pDrObject->SetFromIDNode_T(m_pFromIDNode);
		///
		m_pToIDNode->GetPatchList()->InsertObject(pDrObject);
		pDrObject->SetToIDNode_T(m_pToIDNode);
		///////////////////////////////
	}
	else
	////////////////////////////////////////////// Type_2: wLen
	if(m_nExtruType == 2)
		pDrObject->SetWorldLength_T(m_wLen);
	////////////////////////////////////////
	pDrObject->SetLength_T(m_dLen);
	pDrObject->SetAxis_T(m_vAxis);
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
//////////////////////////////////////////////////////////////////////////////////////
void CMP_Xtrud::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMP_Xtrud:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMP_Xtrud:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
