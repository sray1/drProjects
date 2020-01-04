// Mouse.cpp : implementation file
//


#include "stdafx.h"
#include "math.h"
#include "XForm.h"

#include "Def_Objs.h"
//////////////////// 
#include "3dMath.h" 

#include "drgraf.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
#include "NewObjs.h"
#include "DListMgr.h" 
#include "Def_MouseAct.h"
///////////////////// dialogMgr
#include "MPatMgr.h"
#include "dlg_xtrd.h"
///////////////////// elements
#include "Def_IGen.h"
/////////////////////
#include "MP_Xtrud.h" 
#include "MP_Rotat.h" 
#include "MP_Duct.h" 
#include "MP_Sweep.h" 
//#include "MP_Loft2.h"
#include "MP_LoftX.h"
#include "MP_Tensor.h"
#include "MP_Gordon.h"
#include "MP_CooP4.h"
#include "MP_CooP3.h"
//////////////////////
#include "MC_Circle.h" 
#include "MI_CSPN.h" 
#include "MI_Pat_I.h" 

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
IMPLEMENT_SERIAL(CMI_Pat_I,CMI_Cur_I,1)
/////////////////////////////////////////////////////////////////////////////
CMI_Pat_I::CMI_Pat_I()
{
}

CMI_Pat_I::~CMI_Pat_I()
{
/*
	if(m_pOut != NULL)
	{
		FreeMem(m_pOut);
		m_pOut = NULL;
	}
*/	   
}

int CMI_Pat_I::LBDownInit_PInsert(UINT nType) 
{
//	m_bDirtyPatch		= FALSE;
	return 0;
}

int CMI_Pat_I::LBUpInit_PInsert(enum CURVEPROC kind) 
{
	return 0;
}

int CMI_Pat_I::RBUpDuctInsert
				(
					BOOL							bGenBCurve,
					int								nTwistType,
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
					CList<double,double>*			pTwistList,	// Distrib,if nTwistType = 1
					double							TwistMult,	// if nTwistType = 2 
					BOOL							bIncrement,
					double							TwistStart,
					//////////////////////////////////////////////
					CView*							pView
				) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	int			nResult;
	////////////////////////////////////////////////// Do It
	CMP_Duct	MP_Duct;
	nResult = MP_Duct.GoDoIt(	bGenBCurve,nTwistType,PatchID,pDrPatch,pNodeList,
								pCurveList,pLatchList,pTwistList,TwistMult,bIncrement,
								TwistStart,pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////
	m_pDrPatch = pDrPatch;
	m_pDrPatch->SetDirty(TRUE);
 	///////////////////////////////////////////////////////// show Patch
	pObjectMgr->ShowObject_On_Off(m_pDrPatch,PATCH,TRUE);;
	/////////////////////
	return 0;		 
}			

int CMI_Pat_I::RBUpSweepInsert 
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

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	int			nResult;
	////////////////////////////////////////////////// Do It
	CMP_Sweep	MP_Sweep;
	nResult = MP_Sweep.GoDoIt(	bGenBCurve,nTwistType,nScaleType,PatchID,pDrPatch,pNodeList,
								pCurveList,pLatchList,pTwistList,TwistMult,bIncrement,
								TwistStart,pScaleList,ScaleMult,bIncScale,
								ScaleStart,pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////
	m_pDrPatch = pDrPatch;
	m_pDrPatch->SetDirty(TRUE);
 	///////////////////////////////////////////////////////// show Patch
	pObjectMgr->ShowObject_On_Off(m_pDrPatch,PATCH,TRUE);;
	/////////////////////
	return 0;		 
}			

int CMI_Pat_I::RBUpTensorInsert
				( 
					BOOL							bGenBCurve,
					//////////////////////////////////////////
					BOOL							bAdvanced,
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

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	int			nResult;
	////////////////////////////////////////////////// Fill Info
	CMP_Tensor	MP_Tensor;
	nResult = MP_Tensor.GoDoIt(bGenBCurve,bAdvanced,PatchID,pDrPatch,pNodeList,
		pCornerTwist,TwistMethod,
		nNodes_U,ElperSegList_U,Ratio_U,pBlendCurve_U,pEndList_U,
		nNodes_V,ElperSegList_V,Ratio_V,pBlendCurve_V,pEndList_V,
		pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////
	m_pDrPatch = pDrPatch;
	m_pDrPatch->SetDirty(TRUE);
 	///////////////////////////////////////////////////////// show Patch
	pObjectMgr->ShowObject_On_Off(m_pDrPatch,PATCH,TRUE);;
	/////////////////////
	return 0;		 
}

int CMI_Pat_I::RBUpGordonInsert
				( 
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
					CDListMgr*						pCurveList_U,
					CList<CURVELATCH,CURVELATCH>*	pLatchList_U,
					CList<int,int>&					ElperSegList_U,
					double							Ratio_U,
					CDrCurve*						pBlendCurve_U,
					CList<BLENDEND,BLENDEND>*		pEndList_U,	// if(bClosed_U or Linear_U,Circle_U,
																// parabola_U) EndList_U Empty
					//////////////////////////////////////////////
					int								nNodes_V,
					CDListMgr*						pCurveList_V,
					CList<CURVELATCH,CURVELATCH>*	pLatchList_V,
					CList<int,int>&					ElperSegList_V,
					double							Ratio_V,
					CDrCurve*						pBlendCurve_V,
					CList<BLENDEND,BLENDEND>*		pEndList_V,	// if(bClosed_V or Linear_V,Circle_V,
																// parabola_V) EndList_V Empty
					//////////////////////////////////////////////
					CView*							pView
				) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	int			nResult;
	////////////////////////////////////////////////// Fill Info
	CMP_Gordon	MP_Gordon;
	nResult = MP_Gordon.GoDoIt(bAdvanced,PatchID,pDrPatch,pNodeList,
		pCornerTwist,TwistMethod,
		nNodes_U,pCurveList_U,pLatchList_U,ElperSegList_U,Ratio_U,pBlendCurve_U,pEndList_U,
		nNodes_V,pCurveList_V,pLatchList_V,ElperSegList_V,Ratio_V,pBlendCurve_V,pEndList_V,
		pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////
	m_pDrPatch = pDrPatch;
	m_pDrPatch->SetDirty(TRUE);
 	///////////////////////////////////////////////////////// show Patch
	pObjectMgr->ShowObject_On_Off(m_pDrPatch,PATCH,TRUE);;
	/////////////////////
	return 0;		 
}

int CMI_Pat_I::RBUpLoftXInsert
				( 
					BOOL							bGenBCurve,
					//////////////////////////////////////////
					CDrCurve*						pBlendCurve_U,
					BOOL							bAdvanced,	// tangents/twist BC
					PWMAT2							pCornerTwist,// it is full,if TW_USER
					TWIST							TwistMethod,
					//////////////////////////////////////////////
					int								nCurDir,	// Curve Direction:1=U/2=V
					//////////////////////////////////////////
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					//////////////////////////////////////////
					int								nNodes_U,
					int								nNodes_V,
					CDListMgr*						pNodeList,
					//////////////////////////////////////////
					CDListMgr*						pCurveList_U,	// given Curves always taken as U-dir
																// and later switched,if needed,i.e.,
																// nCurDir = 2
					CList<CURVELATCH,CURVELATCH>*	pLatchList_U,
					//////////////////////////////////////////
					CList<int,int>&					ElperSegList_V,
					CDrCurve*						pBlendCurve_V,
					double							Ratio_V,
					CList<BLENDEND,BLENDEND>*		pEndList_V,	// if(bClosed_V or Linear_V,Circle_V,
																// parabola_V) EndList_V Empty
					//////////////////////////////////////////////
					CView*							pView
				) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	int			nResult;
	////////////////////////////////////////////////// Fill Info
	CMP_LoftX	MP_LoftX;
	nResult = MP_LoftX.GoDoIt(bGenBCurve,FALSE/*NOT Gordon*/,pBlendCurve_U,bAdvanced,
								pCornerTwist,TwistMethod,nCurDir,PatchID,pDrPatch,
								nNodes_U,nNodes_V,pNodeList,
								pCurveList_U,pLatchList_U,ElperSegList_V,pBlendCurve_V,
								Ratio_V,pEndList_V,pView);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////
	m_pDrPatch = pDrPatch;
	m_pDrPatch->SetDirty(TRUE);
 	///////////////////////////////////////////////////////// show Patch
	pObjectMgr->ShowObject_On_Off(m_pDrPatch,PATCH,TRUE);;
	/////////////////////
	return 0;		 
}

int CMI_Pat_I::RBUpLoft2Insert
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

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	int			nResult;
	////////////////////////////////////////////////// Fill Info
//	CMP_Loft2	MP_Loft2;
//	nResult = MP_Loft2.SetInfoBase(PatchID,pDrPatch,pCurveList,pLatchList,
//							pElperSegList,Ratio,pView);
	//////////////
	if(nResult<0)
		return -1;
	////////////////////////////////////////////////// Do It
//	nResult = MP_Loft2.GoDoIt(pDrPatch);
	//////////////
	if(nResult<0)
		return -1;
	//////////////////////
	m_pDrPatch = pDrPatch;
	m_pDrPatch->SetDirty(TRUE);
 	///////////////////////////////////////////////////////// show Patch
	pObjectMgr->ShowObject_On_Off(m_pDrPatch,PATCH,TRUE);;
	/////////////////////
	return 0;		 
}
			
int CMI_Pat_I::RBUpCoonInsert
						(
							BOOL							bGenBCurve,
							PATCHPROC						ppKind, 
							CString&						PatchID,		
							CDrPatch*						pDrPatch,
							CDListMgr*						pCurveList,
							CList<CURVELATCH,CURVELATCH>*	pLatchList,
							CView*							pView
						) 
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	////////////////////////// Triangular Patch
	if(ppKind == PP_COONSTRI)
	{
		CMP_CooP3	MP_CoonP;
		/////////////////////
		int nResult = MP_CoonP.GoDoIt(bGenBCurve,PatchID,pDrPatch,pCurveList,pLatchList);
		//////////////
		if(nResult<0)
			return -1;
	}
	else
	////////////////////////// Quadrilateral Patch
	if(ppKind == PP_COONSQUAD)
	{	
		CMP_CooP4	MP_CooP4;
		/////////
		int nResult = MP_CooP4.GoDoIt(bGenBCurve,PatchID,pDrPatch,pCurveList,pLatchList);
		//////////////
		if(nResult<0)
			return -1;
	}
	//////////////////////
	m_pDrPatch = pDrPatch;
	m_pDrPatch->SetDirty(TRUE);
 	///////////////////////////////////////////////////////// show Patch
	pObjectMgr->ShowObject_On_Off(m_pDrPatch,PATCH,TRUE);;
	/////////////////////
	return 0;		 
}			

int CMI_Pat_I::RBUpRotateInsert 
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

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	int			nResult;
	////////////////////////////////////////////////// Do It
	CMP_Rotat MP_Rotat;	 
	nResult = MP_Rotat.GoDoIt(bGenBCurve,PatchID,pDrPatch,pNodeList,pCurveList,
							pLatchList,ElperSegList_V,dAngle_V,Ratio_V,
							bAxis,nAxis,bNegative,pView);
	//////////////
	if(nResult == MA_ERROR)
		return nResult;
	///////////////////////////////////
	m_pDrPatch = pDrPatch;
	m_pDrPatch->SetDirty(TRUE);
 	///////////////////////////////////////////////////////// show Patch
	pObjectMgr->ShowObject_On_Off(m_pDrPatch,PATCH,TRUE);;
	/////////////////////
	return 0;		 
}			

int CMI_Pat_I::RBUpExtrudeInsert
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

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	int			nResult;
	////////////////////////////////////////////////// Fill Info
	CMP_Xtrud	MP_Xtrud;
	nResult = MP_Xtrud.GoDoIt(bGenBCurve,nExtruType,PatchID,pDrPatch,pNodeList,
							pCurveList,pLatchList,ElperSegList_V,wLen_V,dLen_V,Ratio_V,
							pView);
	//////////////
	if(nResult == MA_ERROR)
		return nResult;
	///////////////////////////////////
	m_pDrPatch = pDrPatch;
	m_pDrPatch->SetDirty(TRUE);
 	///////////////////////////////////////////////////////// show Patch
	pObjectMgr->ShowObject_On_Off(m_pDrPatch,PATCH,TRUE);;
	/////////////////////
	return 0;		 
}
/*
int CMI_Pat_I::Generate_BndryCurves_EXTRUDE(CDrPatch* pDrPatch,
					CList<int,int>*	pElperSegList,double Ratio)
{
	int nResult;
	///////////////////////////////////////////////////////////// dir U
	nResult = GenExtrusionCurve_U(pDrPatch);
	//
	if(nResult<0)
		return MA_ERROR;
	///////////////////////////////////////////////////////////// dir V
	BOOL bClosed = pDrPatch->IsClosed_S();
	//
	if(!bClosed)
		nResult = GenExtrusionCurve_V(pDrPatch,pElperSegList,Ratio);
	if(nResult<0)
		return MA_ERROR;
	/////////////
	return MA_OK;
}

int CMI_Pat_I::GenExtrusionCurve_U(CDrPatch* pDrPatch)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	int			nResult,index;
	/////////////////////
	CDListMgr* pCurList		= pDrPatch->GetCurveList();
	CDrCurve* pParentCurve	= (CDrCurve*)pCurList->GetHead();	// Extrusion Curve
	///
	index = pDrPatch->GetCurveList_U()->GetObjectIndex(pParentCurve);
	if(index<0) // Not yet
		pDrPatch->GetCurveList_U()->InsertObject(pParentCurve);
	///////////////////////////////////////////////////////////// Spawn Curve_U
	pObjectMgr->SetActiveObjectType(CURVE);
	////////////////////////////////////////////////////////////////////////////// Add to DataBase
	int nActiveIndex;
	///////////////
	CDrCurve* pSpawnedCurve	= (CDrCurve*)(pObjectMgr->AddToDataBase(nActiveIndex,CURVE));
	pSpawnedCurve->SetShow(FALSE);	// not quite ready
	/////////////////////////////////////////////////////////////// Using CMI_CSPN
	CMI_CSPN MI_CSPN;
	///
	MATRIX	XFMat;
	C3DMath	Math3D;
	Math3D.GetIdentityMATRIX(&XFMat);
	//
	SetUpLocalM_Extrusion(pDrPatch->GetCNodeList(),&XFMat);
	//
	CString	SpawnID;
	pObjectMgr->SetObjInfoID(SpawnID,CURVE);
	SpawnID += "_IG";
	////
	nResult = MI_CSPN.SpawnCurveWithoutDlg(pSpawnedCurve,pParentCurve,&XFMat,&SpawnID,
												pParentCurve,CURVE); 
	if(nResult<0)
	{
		////////////////////////// Delete
		pObjectMgr->DeleteFromDataBase(nActiveIndex, CURVE);
		pSpawnedCurve	= NULL;
		//////////////////////////
		return nResult;//
	}
	else
	{
		index = pDrPatch->GetCurveList_U()->GetObjectIndex(pSpawnedCurve);
		if(index<0) // Not yet
			pDrPatch->GetCurveList_U()->InsertObject(pSpawnedCurve);
		////////////////////////////// Reciprocate
		index = pSpawnedCurve->GetPatchList()->GetObjectIndex(pDrPatch);
		if(index<0) // Not yet
			pSpawnedCurve->GetPatchList()->InsertObject(pDrPatch);
		////////////////////////////// For TopoList
		pCurList->InsertObject(pSpawnedCurve);
	}
	/////////////////////////////////////////////////////////// Control RectBound
	pSpawnedCurve->Calc_3DBoundsLocal();											
	/////////////////////////////////////	
	pSpawnedCurve->SetDirty(TRUE);
	pSpawnedCurve->SetShow(TRUE);
	////////////////////////////////////////////////////////// Save
	pObjectMgr->ShowObject_On_Off(pSpawnedCurve,CURVE,TRUE);
	/////////////
	return MA_OK;
}

int CMI_Pat_I::GenExtrusionCurve_V(CDrPatch* pDrPatch,
					CList<int,int>*	pElperSegList,double Ratio)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument(); 
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	int			index;
	CDrCurve*	pSpawnedCurve;
	CMP_LoftX	MP_LoftX;
	///////////////////////////////////////////////
	CDListMgr* pCurList		= pDrPatch->GetCurveList();
	CDListMgr* pCurList_U	= pDrPatch->GetCurveList_U();
	CDrCurve* pCurve_1U		= (CDrCurve*)pCurList_U->GetObject(0);
	if(!pCurve_1U)
		return MA_ERROR;
	CDrCurve* pCurve_2U		= (CDrCurve*)pCurList_U->GetObject(1);
	if(!pCurve_2U)
		return MA_ERROR;
	////////////////////
	CDListMgr* pNodList_1U	= pCurve_1U->GetINodeList(); 
	CDListMgr* pNodList_2U	= pCurve_2U->GetINodeList(); 
	///////////////////////////////////////////////////////////// Create Curve_V
	CDrCurve BlendCurve;
	BlendCurve.SetOrder_S(2);	// Linear
	BlendCurve.SetCurveType_S(CP_LINEAR);
	BlendCurve.SetnDim_S(3);
	////////////////////////
	BLENDEND BlendEnd;
	BlendEnd.m_BCL = BC_AUTO;
	BlendEnd.m_BCR = BC_AUTO;
	//////////////////////////////////////////////
	CList<int,int> ElSegList;
	ElSegList.RemoveAll();
	ElSegList.AddTail(pElperSegList);
	////////////////////
	CDListMgr INodeList;
	CString patchID = pDrPatch->GetObjectID(); 
	////////////////////////////////////////////////////////////////////// Curve_1
	INodeList.RemoveAll();
	INodeList.InsertObject(pNodList_1U->GetHead());
	INodeList.InsertObject(pNodList_2U->GetHead());
	//////////
	pSpawnedCurve = MP_LoftX.CreateCurve(BlendEnd,&BlendCurve,&INodeList,
									ElSegList,Ratio,patchID);
	if(!pSpawnedCurve)
		return MA_ERROR;//
	else
	{
		index = pDrPatch->GetCurveList_V()->GetObjectIndex(pSpawnedCurve);
		if(index<0) // Not yet
			pDrPatch->GetCurveList_V()->InsertObject(pSpawnedCurve);
		////////////////////////////// Reciprocate
		index = pSpawnedCurve->GetPatchList()->GetObjectIndex(pDrPatch);
		if(index<0) // Not yet
			pSpawnedCurve->GetPatchList()->InsertObject(pDrPatch);
		////////////////////////////// For TopoList
		pCurList->InsertObject(pSpawnedCurve);
	}
	/////////////////////////////////////////////////////////// Control RectBound
	pSpawnedCurve->Calc_3DBoundsLocal();											
	/////////////////////////////////////	
	pSpawnedCurve->SetDirty(TRUE);
	pSpawnedCurve->SetShow(TRUE);
	////////////////////////////////////////////////////////// Save
	pObjectMgr->ShowObject_On_Off(pSpawnedCurve,CURVE,TRUE);
	////////////////////////////////////////////////////////////////////// Curve_2
	INodeList.RemoveAll();
	INodeList.InsertObject(pNodList_1U->GetTail());
	INodeList.InsertObject(pNodList_2U->GetTail());
	//////////
	pSpawnedCurve = MP_LoftX.CreateCurve(BlendEnd,&BlendCurve,&INodeList,
									ElSegList,Ratio,patchID);
	if(!pSpawnedCurve)
		return MA_ERROR;//
	else
	{
		index = pDrPatch->GetCurveList_V()->GetObjectIndex(pSpawnedCurve);
		if(index<0) // Not yet
			pDrPatch->GetCurveList_V()->InsertObject(pSpawnedCurve);
		////////////////////////////// Reciprocate
		index = pSpawnedCurve->GetPatchList()->GetObjectIndex(pDrPatch);
		if(index<0) // Not yet
			pSpawnedCurve->GetPatchList()->InsertObject(pDrPatch);
		////////////////////////////// For TopoList
		pCurList->InsertObject(pSpawnedCurve);
	}
	/////////////////////////////////////////////////////////// Control RectBound
	pSpawnedCurve->Calc_3DBoundsLocal();											
	/////////////////////////////////////	
	pSpawnedCurve->SetDirty(TRUE);
	pSpawnedCurve->SetShow(TRUE);
	////////////////////////////////////////////////////////// Save
	pObjectMgr->ShowObject_On_Off(pSpawnedCurve,CURVE,TRUE);
	/////////////
	return MA_OK;
}

int CMI_Pat_I::SetUpLocalM_Extrusion(CDListMgr* pCNList,pMATRIX pM)
{
	// get first CNode of each of the 2 Extrusion lines
	int nCount	= pCNList->GetCount();
	if(nCount<2)
		return MA_ERROR;
	int index	= nCount/2;
	if(index*2 != nCount) // not Even
		return MA_ERROR;
	/////////////////////////////////
	CDrNode* pNode;
	pNode		= (CDrNode*)pCNList->GetObject(0);
	WORLD w0	= *(pNode->GetLocalPos());
	pNode		= (CDrNode*)pCNList->GetObject(index);
	WORLD w1	= *(pNode->GetLocalPos());
	///////////////////////////////////////////////////// 			 
	C3DMath	Math3D;
	CXForm	XForm;
	////////////////////////////////////////Translation
	WORLD wTran;
	Math3D.Sub3DPts(&w1,&w0,&wTran);
//	WOPtoWOR(&wTran,&wTran);	// World
	/////////////////////////////////////////////////////////
	//					 set up Local Matrix 
	/////////////////////////////////////////////////////////
	XForm.Translate(pM,wTran.x,wTran.y,wTran.z,XF_REPLACE);
	////////////////////////////////////////////////////
	return MA_OK;
}

*/
////////////////////////////////////////////////////////////
void CMI_Pat_I::Serialize(CArchive& ar)
{

	CMI_Cur_I::Serialize( ar);              // must call base class Serializer
	/////////////////////////
	////////////////////////////
	if (ar.IsStoring())
	{
		TRACE(" MI_PAT_I:    Storing\n");	
		
 			/////////////////////////////////////////////////
 			//////////////////////////////

	}
	else
	{
		TRACE(" MI_PAT_I:    Loading\n");	

			/////////////////////////////////////////////////
 		//////////////////////////////
	
	}        
}

///////////////////////////////////// end of Module //////////////////////		


