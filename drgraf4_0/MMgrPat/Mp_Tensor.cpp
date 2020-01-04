///////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"

#include "Def_Objs.h"
//////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "DListMgr.h"
#include "Def_MouseAct.h"
///////////////////// dialogMgr
#include "MPatMgr.h"
#include "dlg_LoftX.h"
///////////////////// elements
#include "Def_IGen.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "Str_BlendEnd.h"
///////////////////// SpecObjs
#include "Def_Spec.h"
#include "drpen.h"
#include "Layer.h"
/////////////////////
#include "MC_Circle.h"
#include "MC_Parab.h"
/////////////////////
#include "Twist.h" 
#include "MP_Tensor.h" 

#define MAGENTA		RGB(255,0,255)	// Jn. Curve Color
#define	new			DEBUG_NEW
#define	BUFF_SIZE	1024

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define BUFF_SIZE	1024
/////////////////////////////////////
#define wEQL(a,b)	((a).x ==(b).x) && ((a).y ==(b).y) \
					&& ((a).z ==(b).z)  
////////////////////////////////////
IMPLEMENT_SERIAL(CMP_Tensor,CMI_GangP,1)
/////////////////////////////////////////////////////////////////////////////
CMP_Tensor::CMP_Tensor()
{
}

CMP_Tensor::~CMP_Tensor()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////
//		WE CHOSE TO TREAT UNIVARIATE IN U-DIR FIRST FOLLOWED BY
//					UNIVARIATE IN V-DIR.
//		meaning 
//			NODELIST MUST HAVE NODES IN U-DIR ORDER ie FIRST
//			Nodes_U-many NODES,SECOND... Nodes_V-may times
//		///////////////////////////////////////////////////////		 
//		Thus,
//			EndList_V Needs to be Extended to to Create
//			univariate V-curves at NON-LATTICE Bezier
//			Interior Pts. of U-Curves.
//		This in turn may need
//			Estimation of Twist at Surface 4 Corners which
//			along with LATTICE EndInfo_V can estimate
//			NON-LATTICE V-Curves using same BlendingCurve_V						
//////////////////////////////////////////////////////////////////////////////////////////////
//			pEndList_U		=	EndInfo of Lattice Pts Along U
//			pEndList_V		=	EndInfo of Lattice Pts Along V
//////////////////////////////////////////////////////////////////////////////////////////////
int CMP_Tensor::GoDoIt 
				(
					BOOL							bGenBCurve,
					//////////////////////////////////////////
					BOOL							bAdvanced,	// tangents/twist BC
					//////////////////////////////////////////
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					CDListMgr*						pNodeList,
					//////////////////////////////////////////////
					PWMAT2							pCornerTwist,// it is full,if TW_USER
					TWIST							TwistMethod,
					//////////////////////////////////////////////
					int								nNodes_U,
					CList<int,int>&					ElperSegList_U,
					double							Ratio_U,
					CDrCurve*						pBlendCurve_U,
					CList<BLENDEND,BLENDEND>*		pEndList_U,	// if(bClosed_U or Linear_U,Circle_U,
																// parabola_U) EndList_U Empty
					//////////////////////////////////////////////
					int								nNodes_V,
					CList<int,int>&					ElperSegList_V,
					double							Ratio_V,
					CDrCurve*						pBlendCurve_V,
					CList<BLENDEND,BLENDEND>*		pEndList_V,	// if(bClosed_V or Linear_V,Circle_V,
																// parabola_V) EndList_V Empty
					//////////////////////////////////////////////
					CView*							pView
				) 
{
	int i,j;
	/////////////////////////////////////////////////////////////
	CDListMgr						CurveList_U;
	CDListMgr*						pCurveList_U = &CurveList_U;
	CDListMgr						CurveList_V;
	CDListMgr*						pCurveList_V = &CurveList_V;
	///
	pCurveList_U->RemoveAll();
	pCurveList_V->RemoveAll();
	///////////
	CList<CURVELATCH,CURVELATCH>	LatchList_U;
	CList<CURVELATCH,CURVELATCH>*	pLatchList_U = &LatchList_U;
	CList<CURVELATCH,CURVELATCH>	LatchList_V;
	CList<CURVELATCH,CURVELATCH>*	pLatchList_V = &LatchList_V;
	CList<CURVELATCH,CURVELATCH> LatchList;
	for(i=0;i<nNodes_V/*nCurves_U*/;i++)
		LatchList_U.AddTail(CL_FORWARD);
	for(i=0;i<nNodes_U/*nCurves_V*/;i++)
		LatchList_V.AddTail(CL_FORWARD);
	/////////////////////////////////////////////////////////////
	int nResult = MA_OK;
	///////////////////////
	m_PatchID	= PatchID;
	m_pDrPatch	= pDrPatch;
	//////////////////////////////////////
	int nTotData	= nNodes_U * nNodes_V;
	//////////////////////////////////////
	int		nConBZ_S,nBezSeg_S,nConBZ_T,nBezSeg_T;
	pWORLD	pConBZ_S; 	
	pWORLD	pConBZ_T; 	
	pDOUBLE	pWtsBZ_S;
	pDOUBLE	pWtsBZ_T;
	/////////////////
//	Stand Alone OR NOT Part of Gordon: Create Lattice Curves
	/////////////////////////////////////////////////////////////////////////// U,S-direction
	nResult = LatticeCurves(1,PatchID,pNodeList,nNodes_V/*Curves*/,nNodes_U,ElperSegList_U,
			Ratio_U,pCurveList_U,pLatchList_U,pEndList_U,pBlendCurve_U,pConBZ_S,pWtsBZ_S,
			nBezSeg_S,nConBZ_S,TRUE/*bCreate*/);
	if(nResult == MA_ERROR)
		return nResult;
	/////////////////////////////////////////////////////////////////////////// V,T-direction
	nResult = LatticeCurves(2,PatchID,pNodeList,nNodes_U/*Curves*/,nNodes_V,ElperSegList_V,
			Ratio_V,pCurveList_V,pLatchList_V,pEndList_V,pBlendCurve_V,pConBZ_T,pWtsBZ_T,
			nBezSeg_T,nConBZ_T,TRUE/*bCreate*/);
	if(nResult == MA_ERROR)
		return nResult;
	/////////////////////// don't need really
	delete  [] pConBZ_T; 	
	delete  [] pWtsBZ_T;
	/////////////////////////////////////////////////////////////////////////////// EndInfo at Lattice
																				 // Along T-dir
		// If NOT CLOSED & If Blending is BSLINE:
		//			need to Generate TangentRibbon_V at
		//			2 Ends of CurveList_V: 
		// For this, we need Tangent_V at 2 End Lattice pts &
		//			Twist for 4 Corners: U0V0,UNV0,U0VM, & UNVM
		// For Adini Twist Estimate,we need Tangents at Lattice Pts.
		//		U0V0,U0V1,U1V0,U1V1;					Corner_U0V0
		//		UNV0,UNV1,U(N-1)V0,U(N-1)V1;			Corner_UNV0
		//		U0VM,U1VM,U0V(M-1),U1V(M-1);			Corner_U0VM
		//		UNVM,UNV(M-1),U(N-1)VM,U(N-1)V(M-1);	Corner_UNVM
		///////////////////////////////////////////////////////////
		// So, for Adini Twist:
		//		for Each Curve in both direction,we create
		//		4 Tangents i.e., 2 for each End
		///////////////////////////////////////////////////////////
		// So, for Spline Twist: NOT IMPLEMENTED YET
		//		for Each Curve in both direction,we NEED
		//		ALL Tangents at Lattice Pts
	/////////////////////////////////////////////////////////////////////////////
	CList<double,double> WtList_S;
	CList<WORLD,WORLD> EndTanList_U,EndTanList_V; 
	CList<BLENDEND,BLENDEND> EndListExt_V;

	///////////////////////
/*
	if(		(	!pBlendCurve_V->IsClosed_S())		&& 
			(	(pBlendCurve_V->GetCurveType_S() == CP_BSPLINE) ||
				(pBlendCurve_V->GetCurveType_S() == CP_NURB)
			)
*/
	if(bAdvanced)	
	{
	///////////////////////////////////////////////////////////////////////// WtList
	//	We will use u-directional Curve Wts. to make WtList order-compatible 
	//	with NodeList, both of which are then sent to and utilized in same 
	//	fashion by CornerTwist Estimation Routines
	/////////////////////////////////////////////////////////////////////////
		int nDegree_S = m_nOrder_S -1;
		nResult = CreateLatticePtWtList(pWtsBZ_S,WtList_S,nDegree_S,
								nConBZ_S,nNodes_V/*nCurves_U*/,nTotData);
		/////////////////////////////////////////////////////////////////// EndTan_U 
		// at this time EndTanList contains 4 data ( 2 ends+ 2 penultimate)
		// for each curve to assist computation of Twist; however, ultimately
		// we only need 2 end data for each curve for Tangent Ribbon generation 
		nResult = CreateCurveEndTanList(pCurveList_U,EndTanList_U);
		if(nResult == MA_ERROR)
			return nResult;
		/////////////////////////////////////////////////////////////////// EndTan_V 
		// at this time EndTanList contains 4 data ( 2 ends+ 2 penultimate)
		// for each curve to assist computation of Twist; however, ultimately
		// we only need 2 end data for each curve for Tangent Ribbon generation 
		nResult = CreateCurveEndTanList(pCurveList_V,EndTanList_V);
		if(nResult == MA_ERROR)
			return nResult;
		/////////////////////////////////////////////////////////////////// Corner Twists
		m_TwistMethod_T = TwistMethod;
		if(TwistMethod == TW_USER)
		{
			m_pCornerTwist_T = new WORLD[2][2];	// it is full,if TW_USER
			for(i=0;i<2;i++)
				for(j=0;j<2;j++)
					m_pCornerTwist_T[i][j] = pCornerTwist[i][j];
		}
		else
			m_pCornerTwist_T = NULL;
		////////
		nResult = EstimateCornerTwists(pNodeList,&WtList_S,EndTanList_U,
					EndTanList_V,nNodes_U,nNodes_V,pCornerTwist,TwistMethod);
		/////////////////////////////////////////////////////////////////// Extended End Cond.
																		 //	for Bez. IntPts
		nResult = ExtendEndList_V(
					pCurveList_U,nNodes_U,pBlendCurve_U,ElperSegList_U,
					EndTanList_V,pCornerTwist,EndListExt_V);
	}
	else	// copy
		ExtendEndList_V_NonAdvanced(pEndList_V,nConBZ_S,EndListExt_V);
	///////////////////////////////////////////////////////////////////////////////
	//		FINALLY, WE'VE ALL THE INFO TO GENERATE THE PATCH !!!
	/////////////////////////////////////////////////////////////////////////////// BezCurves 
																				 // in T-dir 
	PostPatBezInfoUsingBlendingInfo(pDrPatch,ElperSegList_V,&EndListExt_V,
				pBlendCurve_V,Ratio_V,pConBZ_S,pWtsBZ_S,nConBZ_S,nNodes_V/*nCurves*/,
				nConBZ_T,nBezSeg_T,1);
	///////////////////// don't need anymore
	delete  [] pConBZ_S; 	
	delete  [] pWtsBZ_S;
	/////////////////////////////////////////////////////////////////////////////// Patch Bndry Curves
	m_bGenBCur = bGenBCurve;
	if(!bGenBCurve)
	{
		DeleteCurveList(pCurveList_U,pLatchList_U);
//		while(!pCurveList_U->IsEmpty())
//			delete pCurveList_U->RemoveHead();
		/////////
		DeleteCurveList(pCurveList_V,pLatchList_V);	// deletes also INodes
		///
		pCurveList_U->RemoveAll();
		pLatchList_U->RemoveAll();
		pCurveList_V->RemoveAll();
		pLatchList_V->RemoveAll();
	}
	////////////////////////////////////////////////////////// Post OtherInfo
	m_PatchType		= PA_TENSOR;
	m_bAdvancedEnd_T = bAdvanced; 
	///////////////////////////////////////////////
	pDrPatch->GetElperSegList_S()->RemoveAll();
	pDrPatch->GetElperSegList_T()->RemoveAll();
	pDrPatch->GetElperSegList_S()->AddTail(&ElperSegList_U);	// save for later editing etc
	pDrPatch->GetElperSegList_T()->AddTail(&ElperSegList_V);	// save for later editing etc
	////////////////
	m_nNodes_S	= nNodes_U;	// for Tensor Product
	m_nNodes_T	= nNodes_V;
	nResult = SetInfoForDataBase(pDrPatch,pCurveList_U,pCurveList_V,
						pLatchList_U,pLatchList_V,pBlendCurve_U,pBlendCurve_V,
						pNodeList,pEndList_U,pEndList_V);
	/////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// S-Direction
int CMP_Tensor::LatticeCurves 
				(
					int								nDir,
					CString&						PatchID,		
					CDListMgr*						pNodeList,		// Lattice
					int								nCurves,		// nNodes_U or nNodes_V
					//////////////////////////////////////////////
					int								nNodes,
					CList<int,int>&					ElperSegList,
					double							Ratio,
					CDListMgr*						pCurveList,	
					CList<CURVELATCH,CURVELATCH>*	pLatchList,
					CList<BLENDEND,BLENDEND>*		pEndList,		// Given Curves End Conds in U-dir
																		// or BlendCurve End Conds in U-dir
																		// as many as nNodes_V
					CDrCurve*						pBlendCurve,
					///////////////////////////////////////////////
					pWORLD&							pConBZ, 	
					pDOUBLE&						pWtsBZ,
					int&							nBezSeg,
					int&							nConBZ,
					BOOL							bCreate
				) 
{
	int nResult = MA_OK;
	///////////////////////////////////////////////////////////////////////////////// U,S-direction
//	if(bCreate)	// ALWAYS CREATE:032299
		nResult = CreateCurveList(PatchID,pNodeList,pCurveList,ElperSegList,Ratio,
							pEndList,pBlendCurve,nNodes,nCurves,nConBZ,nBezSeg,nDir);
/*
	else	// Part of Gordon:Already Known & Compatible,so any one will do
	{
		nBezSeg = ((CDrCurve*)pCurveList->GetHead())->GetMaxCubicCurves();
		nConBZ	= ((CDrCurve*)pCurveList->GetHead())->GetMaxCNodes_S();
	}
*/	
	/////////////////////////
	int		nDim,nDegree,nMaxOSeg,nOut;
	BOOL	bUnifOT;
	/////////
	nDim	= pBlendCurve->GetnDim_S(); 
	nDegree	= pBlendCurve->GetOrder_S() - 1;
	/////
	Process_OutputInfo(&ElperSegList,nDegree,nBezSeg,Ratio,bUnifOT,nMaxOSeg,nOut);
	////////////////////////////////////////////////////// Info
	if(nDir == 1)	// S-dir
	{
		m_nOrder_S			= nDegree + 1;
		m_bClosed_S			= pBlendCurve->IsClosed_S();
		m_nDim_S			= nDim;
		m_CurveType_S		= pBlendCurve->GetCurveType_S();
		m_nSegs_S			= nBezSeg;				
		m_nMaxPatchCNodes_S	= nConBZ;
		m_nOut_S			= nOut;
		m_nMaxOSeg_S		= nMaxOSeg;
		m_bUnifOT_S			= bUnifOT;
		m_pNum_t_S			= m_pOSeg;
		m_pDis_t_S			= m_pODis;
	}
	else
	if(nDir == 2)	// T-dir
	{
		m_nOrder_T			= nDegree + 1;
		m_bClosed_T			= pBlendCurve->IsClosed_S();
		m_nDim_T			= nDim;
		m_CurveType_T		= pBlendCurve->GetCurveType_S();
		m_nSegs_T			= nBezSeg;				
		m_nMaxPatchCNodes_T	= nConBZ;
		m_nOut_T			= nOut;
		m_nMaxOSeg_T		= nMaxOSeg;
		m_bUnifOT_T			= bUnifOT;
		m_pNum_t_T			= m_pOSeg;
		m_pDis_t_T			= m_pODis;
	}
	////////////////////////////////////////////////////////// Get Lattice Curves BezPts & Wts
//	int nCurves		= pCurveList->GetCount(); 
	int nCon_BZTot	= nConBZ * nCurves;
	///////////////////////////////////////// Memory
	pConBZ = new WORLD [nCon_BZTot]; 	
	pWtsBZ = new double[nCon_BZTot];
	/////////////////////////////////////////
	int nTopDegree	= nDegree; 
	//////////////////////////////////////////////////////
	nResult = ProcessCurves(pCurveList,pLatchList,pConBZ,pWtsBZ,nConBZ,
											nCon_BZTot,nTopDegree,nDim);
	///////////////////////
	return nResult;
}
//////////////////////////////////////////////////////////////////////////////////// PreProcess
int CMP_Tensor::CreateCurveList(CString& PatchID,CDListMgr* pNodeList,
							CDListMgr* pCurveList,CList<int,int>& ElSegList,double Ratio,
							CList<BLENDEND,BLENDEND>* pEndList,CDrCurve* pBlendCurve,
							int nNode,int nCurves,int& nConBZ,int& nBezSeg,int nDir)
{
	///////////////////////////////////////////////////////////
	int i,nDegree;
	CDListMgr	INodeList;
	POSITION	pos;
	BLENDEND	BlendEnd;
	CDrCurve*	pCurve;
	CURVEPROC CurveType;
	BOOL bClosed;						 
	//////////////////////////////////////////////////////// BlendInfo
	bClosed		= pBlendCurve->IsClosed_S();						 
	nDegree		= pBlendCurve->GetOrder_S() - 1;
	CurveType	= pBlendCurve->GetCurveType_S();
	//////////////////////////////////////////////////////// Bez
	nBezSeg					= (bClosed)?nNode:nNode-1;
	nConBZ					= (bClosed)?(nDegree*nBezSeg):(nDegree*nBezSeg+1);
	//////////////////////////////////////////////////////// Loop Over Bez. Pts. on Curves
	for(i=0;i<nCurves;i++)
	{
/*
		if(	bClosed ||						// pEndList Empty
			(CurveType == CP_LINEAR)	||	// upto order 2 
			(CurveType == CP_CIRCLE)	|| 
			(CurveType == CP_PARABOLA)	||
			(CurveType == CP_ELLIPSE)
		)
		{
			BlendEnd.m_BCL	= BC_AUTO;
			BlendEnd.m_BCR	= BC_AUTO;
		}
		else
		{
*/
			pos			= pEndList->FindIndex(i); 
			BlendEnd	= pEndList->GetAt(pos);
/*
		}
*/
		//////////////////////////////////////////////////// Input Nodes 
		INodeList.RemoveAll();
		if(nDir == 1)
			PackINodeList(pNodeList,i,nNode,&INodeList);
		else
		if(nDir == 2)
			PackINodeList_2(pNodeList,i,nNode,&INodeList,nCurves/*nMax*/);
		//////////////////////////////////////////////////// Now Generate
		pCurve = CreateCurve(BlendEnd,pBlendCurve,&INodeList,
												ElSegList,Ratio,PatchID);
		//////////////////////////////////////////////////// Save
		if(pCurve)
			pCurveList->InsertObject(pCurve);
	}
	//////////////
	return MA_OK;
}

int CMP_Tensor::PackINodeList_2(CDListMgr* pNodeList,int iCurve,int nNode,
									 CDListMgr* pINodeList,int nMax)
{
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int			i,index;
	CDrNode*	pINode;
	WORLD		wLocalPos;
	CString		ID;
	CDrLabel*	pLabel;
	int			nNodeIndex,nLabelIndex;
	POSITION	pos;
	CDrNode*	pNode;
	////////////////////////
	pINodeList->RemoveAll();
	////////////////////////
	for(i=0;i<nNode;i++)
	{
		index	= i*nMax + iCurve; 
		pos		= pNodeList->FindIndex(index);
		pNode	= (CDrNode*)pNodeList->GetAt(pos);
		/////
		if(pNode)
		{
			//////////////////////////////// Create an INode
			pObjectMgr->SetObjInfoID(ID,INODE);
//			ID += "_G";
			wLocalPos = *(pNode->GetLocalPos());
			/////////////////////////// Create Anyway
			nNodeIndex = -12345;
			pINode = CreateNode(ID,pLabel,wLocalPos,FALSE/*Not CNode*/,TRUE,
									nNodeIndex,nLabelIndex,LEVEL_GRAPA);
			//////////////////////////////////
			if(!pINode)	// Create DrNode
			return MA_ERROR;
			///////////////////////////////////
			pINodeList->InsertObject(pINode);
		}
		else
			return MA_ERROR;
	}
	/////////////
	return MA_OK;
}

int CMP_Tensor::PackINodeList_TanNodeV(CDListMgr* pNodeList,int nNodeU,int nNodeV,
									 CDListMgr* pINodeList,BOOL bEndV_0)
{
	int i,index;
	POSITION pos;
	CDrNode* pNode;
	////////////////
	for(i=0;i<nNodeU;i++)
	{
		index	= (bEndV_0)?i*nNodeV:(i+1)*nNodeV - 1; 
		pos		= pNodeList->FindIndex(index);
		pNode	= (CDrNode*)pNodeList->GetAt(pos);
		/////
		if(pNode)
			pINodeList->InsertObject(pNode);
		else
			return MA_ERROR;
	}
	/////////////
	return MA_OK;
}

int CMP_Tensor::PackINodeList(CDListMgr* pNodeList,int iCurve,int nNode,CDListMgr* pINodeList)
{
	//////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr(); 
	///////////////////
	int			i,nBeg,nEnd;
	CDrNode*	pINode;
	WORLD		wLocalPos;
	CString		ID;
	CDrLabel*	pLabel;
	int			nNodeIndex,nLabelIndex;
	POSITION	pos;
	CDrNode*	pNode;
	////////////////////////
	pINodeList->RemoveAll();
	////////////////////////
	nBeg = iCurve * nNode;
	nEnd = nBeg + nNode;
	////////////////////////
	for(i=nBeg;i<nEnd;i++)
	{
		pos		= pNodeList->FindIndex(i);
		pNode	= (CDrNode*)pNodeList->GetAt(pos);
		/////
		if(pNode)
		{
			//////////////////////////////// Create an INode
			pObjectMgr->SetObjInfoID(ID,INODE);
//			ID += "_G";
			wLocalPos = *(pNode->GetLocalPos());
			/////////////////////////// Create Anyway
			nNodeIndex = -12345;
			pINode = CreateNode(ID,pLabel,wLocalPos,FALSE/*Not CNode*/,TRUE,
									nNodeIndex,nLabelIndex,LEVEL_GRAPA);
			//////////////////////////////////
			if(!pINode)	// Create DrNode
			return MA_ERROR;
			///////////////////////////////////
			pINodeList->InsertObject(pINode);
		}
		else
			return MA_ERROR;
	}
	/////////////
	return MA_OK;
}

CDrCurve* CMP_Tensor::CreateCurve(BLENDEND BlendEnd,CDrCurve* pBlendCurve,CDListMgr* pINodeList,
									CList<int,int>& ElSegList,double Ratio,CString& PatchID)
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
	////////////////////////////////////////////////////// Add to DataBase
	CString	ID;
	pObjectMgr->SetObjInfoID(ID,CURVE);
//	ID += "_" + PatchID;
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
	/////////////////////////////////////////////////////////////// Clone Info
	pCurve->SetObjectInfo(pBlendCurve);
	/////////////////////////////////////////////////////////////// End Conditions
	pCurve->SetBCL_S(BlendEnd.m_BCL);
	pCurve->SetBCR_S(BlendEnd.m_BCR);
	pCurve->SetTanL_S(BlendEnd.m_TanL);
	pCurve->SetTanR_S(BlendEnd.m_TanR);
	pCurve->SetWtType_S(WT_UNIFORM);	// UNIFORM
	////////////////////////////////////
	pCurve->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// Fill Input Nodes
	pCurve->GetINodeList()->AddTail(pINodeList);	// copy
	///////////////////////////////////////////////////////
	pCurve->SetRatio_S(Ratio);
	pCurve->SetClosed_S(pBlendCurve->IsClosed_S());
	pCurve->SetCurveType_S(pBlendCurve->GetCurveType_S()); 
	pCurve->SetObjectID(ID);
	/////////////////////////////////////////////////////////////// Do it
	int nResult = Do_Curve(pCurve,ElSegList);
	////////////
	if(nResult == MA_ERROR)
		return (CDrCurve*)NULL;
	else
		return pCurve;
}

int CMP_Tensor::Do_Curve(CDrCurve* pCurve,CList<int,int>& ElSegList)
{
	CDListMgr* pINodeList	= pCurve->GetINodeList();
	CString ID				= pCurve->GetObjectID();
	CURVEPROC CurveType		= pCurve->GetCurveType_S(); 
	/////////////////////////////////////////////////////////////// Using GangC
	CMI_GangC	GangC;
	CMC_Circle	MC_Circle;
	CMC_Parab	MC_Parabola;
	CDrNode*	pFromNode = NULL;
	CDrNode*	pToNode = NULL;
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
	///////////////////////////////
	return MA_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////
int CMP_Tensor::CreateLatticePtWtList(pDOUBLE pWtsBZ,CList<double,double>& WtList,int nDegree,
									  int nConBZ, int nCurves, int nTotData)
{
	// nTotData = nNodes_U * nNodes_V = Total Lattice Pts
	/////////////////////////////////////////////////////////////////////////
	//	We will use u-directional Curve Wts. to make WtList order-compatible 
	//	with NodeList, both of which are then sent to and utilized in same 
	//	fashion by CornerTwist Estimation Routines
	/////////////////////////////////////////////////////////////////////////
	int		i,j,k;
	double	Wt;
	for (i=0;i<nCurves;i++)
	{
		for (j=0;j<nConBZ;j += nDegree)	// only lattice Pt Wts. needed
		{
			k	= i*nConBZ + j;
			Wt	= *(pWtsBZ + k);
			////////////////////
			WtList.AddTail(Wt);
		}
	}
	////////////////////////////////// Check
	if(WtList.GetCount() != nTotData)
	{
		AfxMessageBox(
			"Internal ERROR\nCMP_Tensor::CreateLatticePtWtList\nWtList->GetCount() != nTotData");
		return MA_ERROR;
	}
	/////////////
	return MA_OK;
}

int CMP_Tensor::CreateCurveEndTanList(CDListMgr* pCurveList,CList<WORLD,WORLD>& EndTanList)
{
	int nResult = MA_OK;
	//////////////////////////////////////////////////////////////////////			
	int	nConBZ;
	////////////////
	nConBZ = pCurveList->GetCount();
	if(nConBZ<2)
		return MA_ERROR;
	////////////////////////////////////////////////////////////////////////// LOOP
	for (POSITION pos = pCurveList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve = (CDrCurve*)pCurveList->GetNextObject(pos);
		if(!pCurve)
			return FALSE;
   	 	///////////////////////////////////////////// DoIt
		nResult = CreateEndTanListForACurve(pCurve,EndTanList);
	}
	/////////////
	return MA_OK;
}

int CMP_Tensor::CreateEndTanListForACurve(CDrCurve* pCurve,CList<WORLD,WORLD>& EndTanList)
{
	// Create Tangents at Jn. Control Nodes
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
	int			i=-1,index;
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
		pCNode		= (CDrNode*)(pList->GetNext(pos));
		//
		if(i%nDegree !=0)
			continue;
		/////////////////
		wNodeCoord	= *(pCNode->GetLocalPos());
		pCurve->Get_TangentAtaNode(wNodeCoord,tan,pHitNet->GetDblRatio());	// At Jn. Pt
		WORtoWOP_WORLD(tan);	// deScale internal rep(MI_GangC)
		////
/*
		/////////////////////////////////////////// Scale by deltaKnot[i] = Knot[i+1]-Knot[i]
		index++;
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
*/
		/////////////////////////////////////////// save
		EndTanList.AddTail(tan);
	}
	/////////////
	return MA_OK;
}

int CMP_Tensor::EstimateCornerTwists(CDListMgr* pNodeList,CList<double,double>* pWtList,
					CList<WORLD,WORLD>& EndTanList_U,CList<WORLD,WORLD>& EndTanList_V,
					int nNodes_U,int nNodes_V,PWMAT2 CornerTwist,TWIST TwistMethod)
{
	int nResult = MA_OK;
	////////////////////////////////////////////////////
	CTwist	Twist;
	////////////////////////
	switch (TwistMethod)
	{
		case TW_AUTO:	// fall through
		case TW_BESSEL:
			Twist.Bessel(pNodeList,pWtList,nNodes_U,nNodes_V,CornerTwist);
			break;
		case TW_ZERO:
			Twist.Zero(CornerTwist);
			break;
		case TW_ADINI:
			Twist.Adini(pNodeList,pWtList,nNodes_U,nNodes_V,CornerTwist,EndTanList_U,EndTanList_V);
			break;
		case TW_SPLINE:
			Twist.Spline(pNodeList,pWtList,nNodes_U,nNodes_V,CornerTwist,EndTanList_U,EndTanList_V);
			break;
		case TW_ENERGY:
			Twist.Energy(pNodeList,pWtList,nNodes_U,nNodes_V,CornerTwist);
			break;
		case TW_USER:
			break;		// nothing to do
		default:
			return MA_ERROR;
	}
	/////////////
	return MA_OK;
}

int CMP_Tensor::ExtendEndList_V(
					CDListMgr* pCurveList_U,int nNodes_U,CDrCurve* pBlendCurve_U,
					CList<int,int>& ElperSegList_U,CList<WORLD,WORLD>& EndTanList_V,
					PWMAT2 CornerTwist,CList<BLENDEND,BLENDEND>& EndListExt_V
							  )
{
	// at this time EndTanList contains 4 data ( 2 ends + 2 penultimates)
	// for each curve to assist computation of Twist; however, ultimately
	// we only need 2 end data for each curve for Tangent Ribbon generation 
	///////////////////////////////////////////////////////////////////////
	int nResult = MA_OK;
	////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr  = pDoc->GetObjectMgr();
	///////////////////////////////////////////////
	CString		ID = "TEMPTAN";
	CDrCurve*	pTanCurve;
	int			nActiveIndex;
	CDListMgr	INodeList,TanNodeList;
	BLENDEND	BlendEnd;
	CDrCurve*	pCurve;
	pDOUBLE		pKnots;
	///////////////////////////////////////////
	int nNodes_V	= pCurveList_U->GetCount(); 
	///////////////////////////////////////////////////////////////////////////////////////// BlendInfo
	BOOL bClosed	= pBlendCurve_U->IsClosed_S();						 
	BOOL nDegree	= pBlendCurve_U->GetOrder_S() - 1;						 
	//////////////////////////////////////////////////////// Bez
	int nBezSeg		= (bClosed)?nNodes_U:nNodes_U-1;
	int nConBZ		= (bClosed)?(nDegree*nBezSeg):(nDegree*nBezSeg+1);
	////////////////////////////////////////////////////////// Convert Tangents to Temp Nodes
	CreateTempTanNodeList(&EndTanList_V,&TanNodeList);
	///////////////////////////////////////////////////////////////////////////////////////// EndV_0
	pCurve			= (CDrCurve*)pCurveList_U->GetHead();
	////////////////////////////////////////////////////// Set Knots
	pKnots			= pCurve->GetpKnots_S();
	////////////////////////////////////////////////////// TempNodes_V as INodes
	PackINodeList_TanNodeV(&TanNodeList,nNodes_U,nNodes_V,&INodeList,TRUE);	// TRUE = EndV_0
	////////////////////////////////////////////////////// Set Twist_00 & Twist_M0 as BlendEnd
	PackBlendEndForTanCurve(CornerTwist,BlendEnd,TRUE/*bBegin*/);
	////////////////////////////////////////////////////// Create Temporary Tangent Curve
	pTanCurve		= (CDrCurve*)(pObjectMgr->AddToDataBase(ID,nActiveIndex,CURVE));
	pTanCurve->SetShow(FALSE);
	////////////////////////////////////////////////////// Create
	nResult			= CreateTangentCurve(pTanCurve,BlendEnd,pBlendCurve_U,
									&INodeList,pKnots,ElperSegList_U);
	if(nResult == MA_ERROR)
		return nResult;
	////////////////////////////////////////////////////// Save ControlNodes as Tangent Cond.
	SaveCNodeCoordsAsBCL_V(pTanCurve,EndListExt_V);
	////////////////////////////////////////////////////// Delete TanCurve from DataBase
	pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
	////////////////////////////////////////////////////// GetRidOf TanNode from List
//	while(!TanNodeList.IsEmpty())
//		delete TanNodeList.RemoveHead(); 	// 
	///////////////////////////////////////////////////////////////////////////////////////// EndV_N
	pCurve			= (CDrCurve*)pCurveList_U->GetTail();
	////////////////////////////////////////////////////// Set Knots
	pKnots			= pCurve->GetpKnots_S();
	////////////////////////////////////////////////////// PackTangent_V as INodes
	PackINodeList_TanNodeV(&TanNodeList,nNodes_U,nNodes_V,&INodeList,FALSE);	// FALSE = EndV_N
	////////////////////////////////////////////////////// Set Twist_M0 & Twist_MN as BlendEnd
	PackBlendEndForTanCurve(CornerTwist,BlendEnd,FALSE/*bBegin*/);
	////////////////////////////////////////////////////// Create Temporary Tangent Curve
	pTanCurve		= (CDrCurve*)(pObjectMgr->AddToDataBase(ID,nActiveIndex,CURVE));
	pTanCurve->SetShow(FALSE);
	////////////////////////////////////////////////////// Create
	nResult			= CreateTangentCurve(pTanCurve,BlendEnd,pBlendCurve_U,
									&INodeList,pKnots,ElperSegList_U);
	if(nResult == MA_ERROR)
		return nResult;
	////////////////////////////////////////////////////// Save ControlNodes as Tangent Cond.
	SaveCNodeCoordsAsBCR_V(pTanCurve,EndListExt_V);
	////////////////////////////////////////////////////// Delete TanCurve from DataBase
	pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
	////////////////////////////////////////////////////// GetRidOf TanNode from List
	while(!TanNodeList.IsEmpty())
		delete TanNodeList.RemoveHead(); 	// 
	///////////////
	return MA_OK;
}

int CMP_Tensor::CreateTempTanNodeList(CList<WORLD,WORLD>* pEndTanList,CDListMgr* pTanNodeList)
{
	int nResult = MA_OK;
	int s = -1;
	////////////////////
	for (POSITION pos = pEndTanList->GetHeadPosition();pos !=NULL;)
	{
		WORLD wCoord = pEndTanList->GetNext(pos);
		s++;
		/////////////////////////////////////////
		CString* pNid = new CString;
		char* buf = pNid->GetBuffer(BUFF_SIZE);
	    sprintf(buf,"%s_%d","TempNode",s);
		///////////////////////////////////////// in THE List 
		CDrNode* pAddNode = PostNode(*pNid,LEVEL_KIDDO,wCoord,FALSE);	// Create DrNode
		delete pNid;
		//////////////
		if(!pAddNode)	// 
			return MA_ERROR;
		////////////////////////////////////////  	
		pTanNodeList->InsertObject(pAddNode); //TanNodeList 
	}
	//////////////
	return MA_OK;
}
	
int CMP_Tensor::PackBlendEndForTanCurve(PWMAT2 CornerTwist,BLENDEND& BlendEnd,BOOL bBegin)
{
	if(bBegin)	// Twist_00 & Twist_M0
	{
		////////////////////////////////////////////////// End_0 = Curve_0
		BlendEnd.m_BCL	= BC_TANGENT;
		BlendEnd.m_BCR	= BC_TANGENT;
		/////////////////////////////
		BlendEnd.m_TanL.v[0] = CornerTwist[0][0].x;
		BlendEnd.m_TanL.v[1] = CornerTwist[0][0].y;
		BlendEnd.m_TanL.v[2] = CornerTwist[0][0].z;
		BlendEnd.m_TanL.v[3] = 0;
		/////////////////////////////
		BlendEnd.m_TanR.v[0] = CornerTwist[1][0].x;
		BlendEnd.m_TanR.v[1] = CornerTwist[1][0].y;
		BlendEnd.m_TanR.v[2] = CornerTwist[1][0].z;
		BlendEnd.m_TanR.v[3] = 0;
		///////////////////////
	}
	else		// Twist_0N & Twist_MN
	{
		////////////////////////////////////////////////// End_M = Curve_N
		BlendEnd.m_BCL	= BC_TANGENT;
		BlendEnd.m_BCR	= BC_TANGENT;
		/////////////////////////////
		BlendEnd.m_TanL.v[0] = CornerTwist[0][0].x;
		BlendEnd.m_TanL.v[1] = CornerTwist[0][0].y;
		BlendEnd.m_TanL.v[2] = CornerTwist[0][0].z;
		BlendEnd.m_TanL.v[3] = 0;
		/////////////////////////////
		BlendEnd.m_TanR.v[0] = CornerTwist[1][0].x;
		BlendEnd.m_TanR.v[1] = CornerTwist[1][0].y;
		BlendEnd.m_TanR.v[2] = CornerTwist[1][0].z;
		BlendEnd.m_TanR.v[3] = 0;
		///////////////////////
	}
	/////////////
	return MA_OK;
}

int CMP_Tensor::CreateTangentCurve(CDrCurve* pCurve,
							BLENDEND BlendEnd,CDrCurve* pBlendCurve,CDListMgr* pINodeList,
							pDOUBLE pKnots,CList<int,int>& ElSegList)
{
	int nResult = MA_OK;
	////////////////////
	// pINodeList contains already evaluated Tangents as Bez Pts. and
	// BlendEnd contains Twists
	///////////////////////////////////////// Get rid of Old CNodes & INodes
	if(!(pCurve->GetCNodeList()->IsEmpty())  )
		pCurve->GetCNodeList()->RemoveAll();
	if(!(pCurve->GetINodeList()->IsEmpty())  )
		pCurve->GetINodeList()->RemoveAll();
	/////////////////////////////////////////////////////////////// Clone Info
	pCurve->SetObjectInfo(pBlendCurve);
	/////////////////////////////////////////////////////////////// Knots
	pCurve->SetpKnots_S(pKnots);
	pCurve->SetKnotType_S(KN_USER);
	/////////////////////////////////////////////////////////////// End Conditions
	pCurve->SetBCL_S(BlendEnd.m_BCL);
	pCurve->SetBCR_S(BlendEnd.m_BCR);
	pCurve->SetTanL_S(BlendEnd.m_TanL);
	pCurve->SetTanR_S(BlendEnd.m_TanR);
	pCurve->SetWtType_S(WT_UNIFORM);	// UNIFORM
	////////////////////////////////////
	pCurve->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// Fill Input Nodes
	pCurve->GetINodeList()->AddTail(pINodeList);	// copy
	///////////////////////////////////////////////////////
	pCurve->SetRatio_S(1.0);
	pCurve->SetClosed_S(pBlendCurve->IsClosed_S());
	pCurve->SetCurveType_S(pBlendCurve->GetCurveType_S()); 
//	pCurve->SetObjectID(ID);
	/////////////////////////////////////////////////////////////// Do it
	nResult = Do_Curve(pCurve,ElSegList);
	////////////
	return nResult;
}

int CMP_Tensor::SaveCNodeCoordsAsBCL_V(CDrCurve* pTanCurve,
							CList<BLENDEND,BLENDEND>& EndListExt_V)
{
	// ADD to EndListExt_V
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
	/////////////////////////////////////////////////	
	BLENDEND	BlendEnd;
	WORLD		wCCoord;
	CDListMgr* pList = pTanCurve->GetCNodeList();
	/////////////////////
	EndListExt_V.RemoveAll();
	////////////////////////////////
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pCNode 	= (CDrNode*)pList->GetNextObject(pos);
		/////////////////////////////////////////// ObjectInfo
		wCCoord	= *(pCNode->GetLocalPos());
		///
		wCCoord.x /= (dWorldBase/dMapFactor);
		wCCoord.y /= (dWorldBase/dMapFactor);
		wCCoord.z /= (dWorldBase/dMapFactor);
		pObjectMgr->SCtoDS(&wCCoord.x);
		pObjectMgr->SCtoDS(&wCCoord.y);
		pObjectMgr->SCtoDS(&wCCoord.z);
		//////////////////////////////////////////////////
		BlendEnd.m_BCL	= BC_TANGENT;
		/////////////////////////////
		BlendEnd.m_TanL.v[0] = wCCoord.x;
		BlendEnd.m_TanL.v[1] = wCCoord.y;
		BlendEnd.m_TanL.v[2] = wCCoord.z;
		BlendEnd.m_TanL.v[3] = 0;
		////////////////////////////////////////////////// Save
		EndListExt_V.AddTail(BlendEnd);
	}
	/////////////
	return MA_OK;
}	

int CMP_Tensor::SaveCNodeCoordsAsBCR_V(CDrCurve* pTanCurve,
							CList<BLENDEND,BLENDEND>& EndListExt_V)
{
	// UPDATE EndListExt_V
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
	/////////////////////////////////////////////////	
	CList<BLENDEND,BLENDEND> TempList;
	POSITION	pos;
	POSITION	posBlend;
	BLENDEND	BlendEnd;
	WORLD		wCCoord;
	///////////////////////
	TempList.RemoveAll();
	TempList.AddTail(&EndListExt_V);
	EndListExt_V.RemoveAll();
	/////////////////////////
	CDListMgr* pList = pTanCurve->GetCNodeList();
	////////////////////////////////
	for (pos = pList->GetFirstObjectPos(),
		posBlend = TempList.GetHeadPosition();pos !=NULL;)
	{
		CDrNode* pCNode 	= (CDrNode*)pList->GetNextObject(pos);
		BlendEnd			= TempList.GetNext(posBlend);
		/////////////////////////////////////////// ObjectInfo
		wCCoord	= *(pCNode->GetLocalPos());
		///
		wCCoord.x /= (dWorldBase/dMapFactor);
		wCCoord.y /= (dWorldBase/dMapFactor);
		wCCoord.z /= (dWorldBase/dMapFactor);
		pObjectMgr->SCtoDS(&wCCoord.x);
		pObjectMgr->SCtoDS(&wCCoord.y);
		pObjectMgr->SCtoDS(&wCCoord.z);
		//////////////////////////////////////////////////
		BlendEnd.m_BCR	= BC_TANGENT;
		/////////////////////////////
		BlendEnd.m_TanR.v[0] = wCCoord.x;
		BlendEnd.m_TanR.v[1] = wCCoord.y;
		BlendEnd.m_TanR.v[2] = wCCoord.z;
		BlendEnd.m_TanR.v[3] = 0;
		////////////////////////////////////////////////// Save
		EndListExt_V.AddTail(BlendEnd);
	}
	///////////////////////
	TempList.RemoveAll();
	/////////////
	return MA_OK;
}	
	
int CMP_Tensor::Process_OutputInfo(CList<int,int>* pElperSegList,int nDegree,int nBezSeg,
								  double Ratio,BOOL& bUnifOT,int& nMaxOSeg,int& nOut)
{
	////////////////////////////////////////////////////////////////////////// 
	int i;
	//////////////////////////////////////////////////////////////////////////
	//	NOTE:
	//
	//		If single Segment & Linear:
	//			Allow RATIO of First to Last, etc.
	///////////////////////////////////////////////////////////// Linear/Single Segment
	int nOrder = nDegree + 1; 
	////////////////////
	if (nOrder == 2 && nBezSeg == 1)
	{
		/////////////////////
		if(Ratio == 1.0)		
			bUnifOT = TRUE;
		else			
			bUnifOT = FALSE;
		/////////////////////
		nMaxOSeg 	= pElperSegList->GetHead();
		///////////////////////////////////////// save
		//			 	in Inter_C1: make One Segment of Control Nodes
		//				with m_nMaxOSeg Output segment in it, i.e.,
		//				1 Segment in S-direction
		/////////////////////////////////////////////////////////////////////
		int i;
		//////
		m_pOSeg = new int[1];
		/////////////////////
		m_pOSeg[0] = nMaxOSeg;
		/////////////////////
		if(bUnifOT)			// Uniform and OK
		{
			m_pODis = new double[nMaxOSeg+1];
			///////////////////////////////
			double delt;
			delt	= 1.0/nMaxOSeg;
			////////////////
			m_pODis[0] = 0.;
			////////////////
			for (i=1;i<=nMaxOSeg;i++)
			{
				m_pODis[i] = m_pODis[i-1] + delt;
			}
			/////////////////////
		}
		else								// NonUniform
		{
			m_pODis = new double[nMaxOSeg+1];
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
			double x	= 2./(nMaxOSeg * (Ratio + 1));
			double a	= (nMaxOSeg == 1)?0.:(x * (Ratio-1))/(nMaxOSeg-1);
			//////////////////////////// save
			int i;
			//////
			m_pODis[0] = 0.;
			////////////////
			for (i=0;i<nMaxOSeg;i++)
			{
				///////////////////
				m_pODis[i+1] = m_pODis[i] + x + i * a;
				///////////////////
			}
		}
		////////////////////////////////////////////// Total Evaluation Pts
		nOut = nMaxOSeg + 1;
		///////////////////////
	}	
	///////////////////////////////////////////////////////////////// Other Cases
	else															
	{
		///////////////////////////////////////////// Check if Uniform
		bUnifOT = TRUE;
		int nElems,nElemsPrev;
		///////////////////////////// go over the list
		i = -1;
		for (POSITION posI = pElperSegList->GetHeadPosition( );posI !=NULL;)
		{
			i++;
			////
			nElems = pElperSegList->GetNext(posI); 
			if(!i)
				nElemsPrev = nElems;
    		///////////////////////////////
			if(nElemsPrev != nElems)
			{
				bUnifOT = FALSE;
				break;
			}
		}
		///////////////////////////////////////
		m_pOSeg = new int[nBezSeg];
		///////////////////////////////////////// save for Uniform
		if(bUnifOT)
		{
			nMaxOSeg 	= pElperSegList->GetHead();
			///////////////////////////////////////
			for (i=0;i<nBezSeg;i++)
			{
				m_pOSeg[i] = nMaxOSeg;
			}
		}
		///////////////////////////////////////// save for NonUniform
		else
		{
			i = -1;
			for (POSITION posI = pElperSegList->GetHeadPosition( );posI !=NULL;)
			{
				i++;
				////
				m_pOSeg[i] = pElperSegList->GetNext(posI);
			}
		}
		////////////////////////////////////////////// Total Evaluation Pts
		nOut = 0;	// formal parameter
	
		for (i=0;i<nBezSeg;i++)
			nOut += *(m_pOSeg+i);
		nOut++;
	}
	////////////////
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////
int CMP_Tensor::ProcessCurves(CDListMgr* pLoftCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
							 pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ,
							 int nCon_BZTot,int nDegree,int nDim)
{
	int			m,nConTot=0,nBegNew=0;
	POSITION	posCurve,posLatch; 
	//////////////////////////////////
	CDListMgr*	pCurveList = pLoftCurveList;	// Curves to Loft
	//////////////////////////////////////////////////////////// Controls
	for (	posCurve = pCurveList->GetFirstObjectPos(),
			posLatch = pLatchList->GetHeadPosition();posCurve !=NULL;)
	{
		CDrCurve* pCurve	= (CDrCurve*)pCurveList->GetNext(posCurve);
		CURVELATCH cLatch	= pLatchList->GetNext(posLatch); 
		/////////
		if(!pCurve)
			continue;
		/////////////////////////////////////// GetControl Nodes
		int nConOld	= pCurve->GetMaxCNodes_S();
   		////////////////////////////////////////// memory	
		pWORLD pConOld 	= new WORLD [nConOld];
		pDOUBLE pWtsOld	= new double[nConOld];
		////////////////////////////////////////// get Old 
		GetCNodeCoords_N_Wts(pCurve, cLatch, pConOld, pWtsOld);
		/////////////////////////////////////// save
		for(m=0;m<nConOld;m++)	
		{
			nConTot++;
			///////////////
			pConBZ[nBegNew+m].x = pConOld[m].x; 	
			pConBZ[nBegNew+m].y = pConOld[m].y; 	
			pConBZ[nBegNew+m].z = pConOld[m].z; 	
			pWtsBZ[nBegNew+m]   = pWtsOld[m]; 	
			///////////////////////////////////
		}
		nBegNew += nConOld;									
   		////////////////////////////////////////// Free memory
		delete [] pConOld;
		delete [] pWtsOld;
		////////////////////////////////////////// 
	}
	//////////////////
	if(nConTot == nCon_BZTot)
		return MA_OK;
	else
	{
		AfxMessageBox("Internal ERROR\nCMP_Tensor::ProcessCurves\nnConTot != nCon_BZTot!");
		return MA_ERROR;
	}
}

int CMP_Tensor::GetCNodeCoords_N_Wts(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld)
{
	CDListMgr* pList	= pCurve->GetCNodeList();
	pDOUBLE pWts		= pCurve->GetpWts_BZ_S();
	int nConBZ			= pCurve->GetMaxCNodes_S();
	int nCon_IndexMax	= nConBZ -1;
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
	for(j=0;j<nConBZ;j++)
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
int CMP_Tensor::ExtendEndList_V_NonAdvanced(CList<BLENDEND,BLENDEND>* pEndList_V,int nConBZ_S,
										  CList<BLENDEND,BLENDEND>& EndListExt_V)
{
	// copy nConBZ_S times
	EndListExt_V.AddTail(pEndList_V);
	/////////////////////////////////
	int nCount	= EndListExt_V.GetCount();
	int nRem	= nConBZ_S - nCount;
	if(nRem<=0)
		return MA_OK;
	/////////////////
	BLENDEND blendEnd = pEndList_V->GetHead(); 
	for(int i=0;i<nRem;i++)
		EndListExt_V.AddTail(blendEnd);	
	/////////////////////////////
	return MA_OK;
}

int CMP_Tensor::PostPatBezInfoUsingBlendingInfo(
							CDrPatch* pPatch,CList<int,int>& ElSegList,
							CList<BLENDEND,BLENDEND>* pEndListExt,CDrCurve* pBlendCurve,
							double Ratio,pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ,
							int nCurves,int& nCon_T,int& nBezSeg_T,int nDir)
{
	// First,	assume Curves in S-dir and Blend Curve in T-dir
	// Then,	Based on nDir, Correctly Post Bezier Info	
	///////////////////////////////////////////////////////////
	// Blend Curve Contains T-directional Info:
	//			CurveType
	//			IsClosed
	///////////////////////////////////////////////////////////
	int i;
	CDListMgr	INodeList;
	CDListMgr	TemCNodeList;	// temporarily store Patch BezPts( may be undesirable
								// Order, to be corrected at the end of this routine
	//////////////////////////////////////////////////////// BlendInfo
	BOOL bClosed_T = pBlendCurve->IsClosed_S();						 
	BOOL nDegree_T = pBlendCurve->GetOrder_S() - 1;						 
	//////////////////////////////////////////////////////// Wts
	int nCon_S;
	nCon_S					= nConBZ;
	///
	nBezSeg_T				= (bClosed_T)?nCurves:nCurves-1;
	nCon_T					= (bClosed_T)?(nDegree_T*nBezSeg_T):(nDegree_T*nBezSeg_T+1);
	pDOUBLE	pTemPatWts_BZ	= new double[nCon_S*nCon_T];
	CString PatchID			= pPatch->GetObjectID();
	//////////////////////////////////////////////////////// Loop Over Bez. Pts. on Curves
	for(i=0;i<nCon_S;i++)
	{
		POSITION pos		= pEndListExt->FindIndex(i); 
		BLENDEND BlendEnd	= pEndListExt->GetAt(pos);
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
		GeneratePatchBezInfoFromBlendCurve(BlendEnd,pBlendCurve,&INodeList,
				pTemWts_DT,ElSegList,&TemCNodeList,pTemPatWts_BZ,Ratio,PatchID,nCon_T,i);
		///
	}
	////////////////////////////////////////////////////////////////////////// Post
	if(nDir == 2) // Curve along T-direction
	{
		///////////////////////////////////////////////// Save Control Pts
		(pPatch->GetCNodeList())->AddTail(&TemCNodeList);
		TemCNodeList.RemoveAll();
		///////////////////////////////////////////////// Save Wts
		pPatch->SetMemInWts(pTemPatWts_BZ);
		/////////////
	}
	else
	if(nDir == 1) // Curve along S-direction, So Transpose
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

int CMP_Tensor::PostPatBezInfo(CDrPatch* pPatch,CDListMgr& TemCNodeList,pDOUBLE pTemPatWts_BZ,
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
	
int CMP_Tensor::TempPostPatBezJunctionPtsInINodeList(pWORLD pConBZ,int nConBZ,int nCol,
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
	
int CMP_Tensor::PackPatBezJunctionWtsInDataWtsArray(pDOUBLE pWtsBZ,int nConBZ,int nCol,
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

int CMP_Tensor::GeneratePatchBezInfoFromBlendCurve(
						BLENDEND BlendEnd,CDrCurve* pBlendCurve,CDListMgr* pINodeList,
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
	/////////////////////////////////////////////////////////////// Clone Info
	pCurve->SetObjectInfo(pBlendCurve);
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
	pCurve->SetClosed_S(pBlendCurve->IsClosed_S());
	/////////////////////////////////////////////////////////////// Using GangC
	CMI_GangC	GangC;
	CMC_Circle	MC_Circle;
	CMC_Parab	MC_Parabola;
	CDrNode*	pFromNode = NULL;
	CDrNode*	pToNode = NULL;
	/////////////////////////////
	CURVEPROC CurveType = pBlendCurve->GetCurveType_S(); 
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
	 
int CMP_Tensor::Copy_N_TransferBezControlInfo(CDrCurve* pCurve,CDListMgr* pPatCNodeList,
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

int CMP_Tensor::Copy_N_TransferBezWeightInfo(CDrCurve* pCurve,pDOUBLE pPatWts_BZ,int nCon_T,int nCol)
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

int CMP_Tensor::DeleteCurveList(CDListMgr* pCurveList,
							CList<CURVELATCH,CURVELATCH>* pLatchList)
{
	if(pCurveList->IsEmpty())
		return MA_OK;
	//////////////////////////
	pLatchList->RemoveAll();
	//////////////////////////////////////////// MI_GangP
	return DeleteCurves_LockStock(pCurveList);
	////////////
}
//////////////////////////////////////////////////////////////////////////////////////
int CMP_Tensor::SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CDrCurve* pBlendCurve_U,CDrCurve* pBlendCurve_V,
					CDListMgr* pNodeList,
					CList<BLENDEND,BLENDEND>* pEndList_U,
					CList<BLENDEND,BLENDEND>* pEndList_V)
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
	pDrObject->SetPatchProc(PP_TENSOR);
	pDrObject->SetPatchType(PA_TENSOR);
	pDrObject->SetPatSubType(PS_QUADRILAT);
    //////////////////////////////
	pDrObject->SetObjectID(m_PatchID);
	//////////////////////////////////
	pDrObject->SetGenBCurve(m_bGenBCur);
	///////////////////////////////////////////////////////////////////
	pDrObject->SetPrimaryDir(1);// normal direction U dir is U dir
	SetInfoForDataBase_1(pDrObject,	pCurveList_U,pCurveLatchList_U,pBlendCurve_U,
									pCurveList_V,pCurveLatchList_V,pBlendCurve_V,
									pNodeList,pEndList_U,pEndList_V);
//	SetInfoForDataBase_2(pDrObject,pCurveList_V,pCurveLatchList_V,pBlendCurve_V);
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
		AfxMessageBox("Internal Problem:\nCMP_Tensor::SetInfoForDataBase\nm_nOut Mismatch!");
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

void CMP_Tensor::SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,CDrCurve* pBlendCurve_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,CDrCurve* pBlendCurve_V,
					CDListMgr* pNodeList,
					CList<BLENDEND,BLENDEND>* pEndList_U,
					CList<BLENDEND,BLENDEND>* pEndList_V)
{
	CDListMgr* pList; 
	POSITION pos;
	////////////////////////////////////////////////////////// NodeList
	pDrObject->SetNodes_S(m_nNodes_S);					
	pDrObject->SetNodes_T(m_nNodes_T);
	//////////////////////////////////
	pList = pDrObject->GetINodeList(); 
	pList->RemoveAll();
	pList->AddTail(pNodeList);
	////////////////////////////////////////////////// Reciprocate
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrNode* pNode 	= (CDrNode*)pList->GetNextObject(pos);
		/////////////////////////////////////////// does exist already?
		int index = pNode->GetPatchList()->GetObjectIndex(pDrObject);
		if(index<0)
			pNode->GetPatchList()->InsertObject(pDrObject);
	}
	////////////////////////////////////////////////////////// EndList
	pDrObject->SetAdvancedEnd_V(m_bAdvancedEnd_T);
//	if(m_bAdvancedEnd_T)
//	{
		pDrObject->GetEndList_U()->RemoveAll();
		pDrObject->GetEndList_U()->AddTail(pEndList_U);
		pDrObject->GetEndList_V()->RemoveAll();
		pDrObject->GetEndList_V()->AddTail(pEndList_V);
//	}
	////////////////////////////////////////////////////////// CurveList
	CDrCurve* pCurve;
	///////////////////////////////////////////////// Reparametrize
	pList = pCurveList_U; 
	/////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		///////////////////////// ReParametrize Bez Wts, in case
		ReParametrizeBezWeightsToStdForm(pCurve);
		////////////////////////////////// Change Color for IsoCurves
		pCurve->SetPenInfo(0,RGB(255,0,255),PS_SOLID);
		pCurve->SetShow(TRUE);
	}
	///////////////////////////////////////////////// Reparametrize
	pList = pCurveList_V; 
	/////
	for (pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		///////////////////////// ReParametrize Bez Wts, in case
		ReParametrizeBezWeightsToStdForm(pCurve);
		////////////////////////////////// Change Color for IsoCurves
		pCurve->SetPenInfo(0,RGB(255,0,255),PS_SOLID);
		pCurve->SetShow(TRUE);
	}
	/////////////////////////////////////////////////////////////////
/*
	pDrObject->GetCurveLatchList_U()->RemoveAll();
	pDrObject->GetCurveLatchList_U()->AddTail(pCurveLatchList_U);
	pDrObject->GetCurveLatchList_V()->RemoveAll();
	pDrObject->GetCurveLatchList_V()->AddTail(pCurveLatchList_V);
*/
	pDrObject->SetBlendCurve_U(pBlendCurve_U);
	pDrObject->SetBlendCurve_V(pBlendCurve_V);
	///////////////////////////////////////////////////////////////// All Other
	pDrObject->SetAdvancedEnd_V(m_bAdvancedEnd_T);
	pDrObject->SetTwistMethod_V(m_TwistMethod_T);
	pDrObject->SetCornerTwist_V(m_pCornerTwist_T);// it is full,if TW_USER
	/////////
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
	////////////////
	return;
}
 
void CMP_Tensor::SetInfoForDataBase_2(CDrPatch* pDrObject,CDListMgr* pCurveList,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList,CDrCurve* pBlendCurve)
{
	////////////////////////////////////////////////////////// CurveList
	CDListMgr* pList = pDrObject->GetCurveList_V(); 
	pList->RemoveAll();
	pList->AddTail(pCurveList);
	///////////////////////////////////////////////// Reciprocate/Reparametrize
	for (POSITION pos = pList->GetFirstObjectPos();pos !=NULL;)
	{
		CDrCurve* pCurve 	= (CDrCurve*)pList->GetNextObject(pos);
		///////////////////////// ReParametrize Bez Wts, in case
		ReParametrizeBezWeightsToStdForm(pCurve);
		////////////////////////////////// Change Color for IsoCurves
		pCurve->SetPenInfo(0,RGB(255,0,255),PS_SOLID);
		pCurve->SetShow(TRUE);
		/////////////////////////////////////////// does exist already?
		int index = pCurve->GetPatchList()->GetObjectIndex(pDrObject);
		if(index<0)
			pCurve->GetPatchList()->InsertObject(pDrObject);
	}
	/////////////////////////////////////////////////////////////////
	pDrObject->GetCurveLatchList_V()->RemoveAll();
	pDrObject->GetCurveLatchList_V()->AddTail(pCurveLatchList);
	pDrObject->SetBlendCurve_V(pBlendCurve);
	///////////////////////////////////////////////////////////////// All Other
	pDrObject->SetRatio_S(m_Ratio_T);					
	pDrObject->SetRatio_T(m_Ratio_S);					
	pDrObject->SetUniform_S(m_bUnifOT_T);		// Output Distribution:
	pDrObject->SetUniform_T(m_bUnifOT_S);		// Output Distribution:
	pDrObject->SetOutSegUnif_S(m_nMaxOSeg_T); 	// for Old Compatibility
	pDrObject->SetOutSegUnif_T(m_nMaxOSeg_S); 	// for Old Compatibility
	pDrObject->SetMaxOutSeg_S(m_nMaxOSeg_T);	// Number of Output Segments
	pDrObject->SetMaxOutSeg_T(m_nMaxOSeg_S);	// Number of Output Segments
	pDrObject->SetMaxOutPts_S(m_nOut_T);
	pDrObject->SetMaxOutPts_T(m_nOut_S);
	pDrObject->SetOut_S(m_nOut_T);
	pDrObject->SetOut_T(m_nOut_S);
	//////////////////////////////////////////
	pDrObject->SetCurveType_S(m_CurveType_T);
	pDrObject->SetCurveType_T(m_CurveType_S);
	pDrObject->SetMaxCNodes_S(m_nMaxPatchCNodes_T);
	pDrObject->SetMaxCNodes_T(m_nMaxPatchCNodes_S);
	///////////////////////////////////////////////////
//	pDrObject->SetSegmentCount_S(m_nSegs_T);	
//	pDrObject->SetSegmentCount_T(m_nSegs_S); 
	pDrObject->SetMaxBezSegments_S(m_nSegs_T);	
	pDrObject->SetMaxBezSegments_T(m_nSegs_S); 
	pDrObject->SetClosed_S(m_bClosed_T);
	pDrObject->SetClosed_T(m_bClosed_S);
	pDrObject->SetOut_S(m_nOut_T);	
	pDrObject->SetOut_T(m_nOut_S);
	pDrObject->SetOrder_S(m_nOrder_T);
	pDrObject->SetOrder_T(m_nOrder_S);
//	pDrObject->SetnDim_S(m_nDim_T);
//	pDrObject->SetnDim_T(m_nDim_S);
	pDrObject->SetnDim_S(4);	// ALWAYS RATIONAL
	pDrObject->SetnDim_T(4);	// ALWAYS RATIONAL
	///////////////////////////////////////////////////////// for now
	pDrObject->SetNum_tPointer_S(m_pOSeg_T);			// Number of Outputs for each Output Segment
	pDrObject->SetNum_tPointer_T(m_pOSeg_S);			// Number of Outputs for each Output Segment
	//////////////////////////////////////////////////////////////////////
	pDrObject->SetDis_tPointer_S(m_pODis_T);			// s-distribution
	pDrObject->SetDis_tPointer_T(m_pODis_S);			// t-distribution
	////////////////
	return;
}

void CMP_Tensor::Serialize(CArchive& ar)
{

	CMI_GangP::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" CMP_Tensor:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" CMP_Tensor:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
	//////////////////
}
///////////////////////////////// end of module ///////////////////
