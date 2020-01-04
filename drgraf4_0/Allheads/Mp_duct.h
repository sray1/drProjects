 // mp_Duct.h : header file
//
#ifndef _MP_DUCT_H 
#define _MP_DUCT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangP.h"
#include "DrPatch.h"
#include "Def_Type.h"                    
#include "Str_BlendEnd.h"
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMP_Duct : public CMI_GangP
class AFX_EXT_CLASS CMP_Duct : public CMI_GangP
{
public:

	CMP_Duct();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_Duct)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

	int			GoDoIt 
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
				); 

 				
		
protected:


	BOOL		IsDataCompatible(CDListMgr* pCurveList,CDListMgr* pNodeList,
								CList<CURVELATCH,CURVELATCH>*	pLatchList,
								CList<double,double>* pTwistList,int nTwistType);
	int			TwistProcess(pDOUBLE pTwist, int nTwist, double dScaleMax, 
												double dTwistStart, BOOL bIncremental);
	int			SetPatchDataFromCurve(CDrCurve* pCurve,int nDir);
	int			GetCNodeCoords_N_Wts_XSection(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld);
	int			GetCNodeCoords_N_WtsAtJnPts_Spine(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld);
	int			CreateTangentsAtJnPts_Spine(CDrCurve* pCurve,CURVELATCH cLatch,pWORLD pTangents);
	int			PatCNCoords_N_WtsAtJns(WORLD wAnchorPt,pWORLD pConBZ_S,pDOUBLE pWtsBZ_S,int nConBZ_S,
						pWORLD pConBZ_T,pWORLD pTanBZ_T,int nConBZ_T,pDOUBLE pTwist,
						pWORLD pPatCons,pDOUBLE pPatWts,int nTotOut);
//	int			PostPatCNodes_N_Wts(CDrPatch* pDrPatch,pWORLD pPatCons,pDOUBLE pPatWts,
//															int nConBZ_S,int nConBZ_T);
	////////////////
	int			PostPatBezInfoUsingBlendingInfo(CDrPatch* pPatch,CDrCurve* pSpineCurve,
												pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ,
																int nCurves,int nCon_T);
	int			PostPatBezInfo(CDrPatch* pPatch,CDListMgr& TemCNodeList,pDOUBLE pTemPatWts_BZ,
																		int nCon_S,int nCon_T);
	int			TempPostPatBezJunctionPtsInINodeList(pWORLD pConBZ,int nConBZ,int nCol,
												int nCurves,CDListMgr* pINodeList);
	int			PackPatBezJunctionWtsInDataWtsArray(pDOUBLE pWtsBZ,int nConBZ,int nCol,
												int nCurves,pDOUBLE pTemWts_BZ);
	int			GeneratePatchBezInfoFromSpineCurve(
						BLENDEND BlendEnd,CDrCurve* pSpineCurve,CDListMgr* pINodeList,
						pDOUBLE pWts_DT,CList<int,int>& ElSegList,CDListMgr* pPatCNodeList,
						pDOUBLE pPatWts_BZ,double Ratio,CString& PatchID,int nCon_T,int nCol);
	int			Copy_N_TransferBezControlInfo(CDrCurve* pCurve,CDListMgr* pPatCNodeList,
														CString& PatchID,int nCol);
	int			Copy_N_TransferBezWeightInfo(CDrCurve* pCurve,pDOUBLE pPatWts_BZ,int nCon_T,int nCol);
	////////////////
	int			SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CList<double,double>* pTwistList	// Distrib,if nTwistType = 1
				);
	void		SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CList<double,double>* pTwistList	// Distrib,if nTwistType = 1
				);
	////////////////
	int			LatticeCurves_U(CDrPatch* pDrPatch,int nOrder_T,BOOL bClosed_T,int nSegBZ_T,
														int nConBZ_S,CDrCurve* pCurOriginal);
	int			CreateFillINodeList_S(CDrPatch* pDrPatch,int iCurve_U,int nINode_U,
								int nDegree_S,int nDegree_T,int nConBZ_S,CDListMgr* pINodeList);
	int			PackINodeList_S(CString& PatchID,CDListMgr* pCNodeList,int iCurve_U,int nINode,
									 int nDeg_U,int nDeg_V,CDListMgr* pINodeList,int nConBZ_S);
//	int			ExtractWts_S(CDrPatch* pDrPatch,int iCurve_U,int nDegree_T,int nConBZ_S,
//																	pDOUBLE pWts);
	int			CreateFillCNodeList_N_Wts_S(CDrPatch* pDrPatch,int iCurve_U,int nDegree_T,
									int nConBZ_S,CDListMgr* pCNodeList,pDOUBLE pWts);
	int			PackCNodeList_N_Wts_S(CString& PatchID,CDListMgr* pPatCNodeList,pDOUBLE pPatWts,
				int iCurve_U,int nDeg_V,int nConBZ_S,CDListMgr* pCNodeList,pDOUBLE pWts);
	///
	int			LatticeCurves_V(CDrPatch* pDrPatch,int nOrder_S,BOOL bClosed_S,int nSegBZ_S,
											int nConBZ_S,int nConBZ_T,CDrCurve* pCurOriginal);
	int			CreateFillCNodeList_N_Wts_T(CDrPatch* pDrPatch,int iCurve_V,int nDegree_S,
						int nConBZ_S,int nConBZ_T,CDListMgr* pCNodeList,pDOUBLE pWts);
	int			PackCNodeList_N_Wts_T(CString& PatchID,CDListMgr* pPatCNodeList,pDOUBLE pPatWts,
					int iCurve_V,int nDeg_U,int nConBZ_S,int nConBZ_T,CDListMgr* pCNodeList,pDOUBLE pWts);
	int			CreateFillINodeList_T(CDrPatch* pDrPatch,int iCurve_V,int nINode_V/*BzJnPts_S*/,
					int nDegree_S,int nDegree_T,int nConBZ_S,CDListMgr* pINodeList);
	int			PackINodeList_T(CString& PatchID,CDListMgr* pCNodeList,int iCurve_V,int nINode_V,
							int nDeg_U,int nDeg_V,CDListMgr* pINodeList,int nConBZ_S);
	////////////
	int			SetDataFromCurve_Lattice(CDrCurve* pCurve);
	int			SetInfoDataBase_LatticeCurve(CDrCurve* pDrObject);
	void		SetInfo_LatticeCurve(CDrCurve* pDrObject);
		          

protected:  
// Attributes

	////////////////////////
	BOOL		m_bIncrement;
	int			m_nTwistType;
	//////////////////////

//Operations
public:

	~CMP_Duct();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_Duct)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
