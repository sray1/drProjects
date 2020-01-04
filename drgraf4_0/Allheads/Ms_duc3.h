 // mp_Duct.h : header file
//
#ifndef _MS_DUC3_H 
#define _MS_DUC3_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangS.h"
#include "DrSolid.h"
#include "DrPatch.h"
#include "DrCurve.h"
#include "Def_Type.h"                    
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMS_Duc3 : public CMI_GangS
{
public:

	CMS_Duc3();
//////////////////////////////////////
	DECLARE_SERIAL(CMS_Duc3)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

		int		GoDoIt 
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
				); 
    				
		
protected:


		BOOL	IsDataCompatible(CDListMgr* pNodeList,
					CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>*	pCLatchList,
					CDListMgr* pPatchList,CList<PATCHLATCH,PATCHLATCH>*	pPLatchList,
									CList<double,double>* pTwistList,int nTwistType);
		int		TwistProcess(pDOUBLE pTwist, int nTwist, double dScaleMax, double dTwistStart,
																		BOOL bIncremental);
		int		SetSolidDataFromPatch(CDrPatch* pPatch);
		int		GetPatCNodeCoords_N_Wts_XSection(CDrPatch* pPatch, PATCHLATCH pLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld);
		int		GetSolidInfoFromSpine_R(CDrCurve* pCurve);
		int		GetCNodeCoords_N_WtsAtJnPts_Spine(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld);
		int		CreateTangentsAtJnPts_Spine(CDrCurve* pCurve,CURVELATCH cLatch,pWORLD pTangents);
		int		SolCNCoords_N_WtsAtJns(WORLD wAnchorPt,pWORLD pPatConBZ_ST,pDOUBLE pPatWtsBZ_ST,
							int nPatConBZ_ST,pWORLD pConJnBZ_R,pWORLD pTanJnBZ_R,int nConJnBZ_R,
									pDOUBLE pTwist,pWORLD pSolCons,pDOUBLE pSolWts,int nTotOut);
		int		PostSolBezInfoUsingBlendingInfo(CDrSolid* pSolid,CDrCurve* pSpineCurve,
								pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ_S,int nConBZ_ST,
												int nPatches/*nConBZJn_R*/,int nConBZ_R);
		int		PostPatBezInfo(CDrSolid* pSolid,CDListMgr& TemCNodeList,pDOUBLE pTemSolWts_BZ,
															int nCon_S,int nCon_ST,int nCon_R);
		int		TempPostSolBezJunctionPtsInINodeList(pWORLD pConBZ,int nConBZ_ST,int nRowCol,
												int nPatches,CDListMgr* pINodeList);
		int		PackSolBezJunctionWtsInDataWtsArray(pDOUBLE pWtsBZ,int nConBZ_ST,int nRowCol,
												int nPatches,pDOUBLE pTemWts_BZ);
		int		GenerateSolidBezInfoFromSpineCurve(
						BLENDEND BlendEnd,CDrCurve* pSpineCurve,CDListMgr* pINodeList,
						pDOUBLE pWts_DT,CList<int,int>& ElSegList,CDListMgr* pSolCNodeList,
						pDOUBLE pSolWts_BZ,double Ratio,CString& SolidID,int nCon_R,int nRowCol);
		int		Copy_N_TransferBezControlInfo(CDrCurve* pCurve,CDListMgr* pSolCNodeList,
															CString& SolidID,int nRowCol);
		int		Copy_N_TransferBezWeightInfo(CDrCurve* pCurve,pDOUBLE pPatWts_BZ,int nCon_R,
																				int nRowCol);
		int		SetInfoForDataBase(CDrSolid* pDrObject,
					CDListMgr* pPatchList_U,CDListMgr* pCurveList_W,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_W,
					CList<double,double>* pTwistList	// Distrib,if nTwistType = 1
				);
		void	SetInfoForDataBase_1(CDrSolid* pDrObject,
					CDListMgr* pCurveList_W,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_W,
					CDListMgr* pPatchList_U,
					CList<PATCHLATCH,PATCHLATCH>* pCurveLatchList_U,
					CList<double,double>* pTwistList	// Distrib,if nTwistType = 1
				);
		          

protected:  
// Attributes

	////////////////////////
	BOOL		m_bIncrement;
	int			m_nTwistType;
	//////////////////////

	
//Operations
public:

	~CMS_Duc3();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMS_Duc3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
