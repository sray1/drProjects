 // mp_Loft2.h : header file
//
#ifndef _MP_GORDON_H 
#define _MP_GORDON_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include <afxtempl.h>	// CList
#include "MI_GangP.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DListMgr.h"
#include "Def_CuPS.h"                    
#include "Def_Type.h"
#include "Str_BlendEnd.h"
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMP_Gordon : public CMI_GangP
class AFX_EXT_CLASS CMP_Gordon : public CMI_GangP
{
public:

	CMP_Gordon();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_Gordon)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

int			GoDoIt 
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
				); 

protected:
				
				
	int			CheckDegreeElevation_PatchTP(CDrPatch* pDrPatch,int nTopDeg_U,int nTopDeg_V,
											 int& nCon_SNew,int& nCon_TNew);
	int			UpdateCN_N_Wts(CDListMgr* pCNList,pDOUBLE pWts,pWORLD pCon_BZ,pDOUBLE pWts_BZ,
																int nCon_SNew, int nCon_TNew);
	int			ElevatePat_S(CDListMgr* pCNList,pDOUBLE pWts,int nConOld,int nDegOld,int nSeg_BZ,
							pWORLD pCon_BZ, pDOUBLE pWts_BZ,int nElev, int nDim,int& nConTot);
	int			GetCNodeCoords_N_Wts_U(CDListMgr* pCNList,pDOUBLE pWts,pWORLD pConOld,pDOUBLE pWtsOld,
																			int nConBZ_U,int nCol);
	int			ElevatePat_T(CDListMgr* pCNList,pDOUBLE pWts,int nConOld,int nDegOld,int nSeg_BZ,
							pWORLD pCon_BZ, pDOUBLE pWts_BZ,int nElev, int nDim,int& nConTot);
	int			GetCNodeCoords_N_Wts_V(CDListMgr* pCNList,pDOUBLE pWts,pWORLD pConOld, pDOUBLE pWtsOld,
																int nConBZ_U,int nConBZ_V,int nRow);
	int			TransposeCons_N_Wts(pWORLD pCon_BZ,pDOUBLE pWts_BZ,int nRowTot,int nColTot);
	////////////////////////////////////////////////////////////////////////////////////////////////
	int			Combine(CDrPatch* pDrPatch,CDrPatch* pDrPatch_L1, 
						CDrPatch* pDrPatch_L2,CDrPatch* pDrPatch_TP,
									 int nCon_SNew,int nCon_TNew);
	////////////////////////////////////////////////////////////////////////////////////////////////
	int			CheckDegreeElevation(CDListMgr* pCurveList,CDrCurve* pBlendCurve,
							int& nBezSeg,int& nDim,int& nTopDegree,int& nCon_BZ);
	int			PreProcessCurvesControlInfo(CDListMgr* pCurveList,int& nDim,
																int& nTopDegree);
	BOOL		IsRational(CDListMgr* pCurveList);
	int			GetTopDegree(CDListMgr* pCurveList);
	BOOL		IsCompat_NumberOfCNodes(CDListMgr* pCurveList,int nTopDegree,
													int& nCurveSeg,int& nConBZ);
	int			LatticeCurvesInfo 
				(
					int								nDir,
					//////////////////////////////////////////////
					int								nBezSeg,
					int								nConBZ,
					int								nDim,
					int								nDegree,
					//////////////////////////////////////////////
					CList<int,int>&					ElperSegList,
					double							Ratio,
					CDListMgr*						pCurveList,	
					CDrCurve*						pBlendCurve
					///////////////////////////////////////////////
				); 
	int			SetInfoForDataBase(CDrPatch* pDrObject,
									CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
									CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
									CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
									CDrCurve* pBlendCurve_U,CDrCurve* pBlendCurve_V,
									CList<BLENDEND,BLENDEND>* pEndList_U,
									CList<BLENDEND,BLENDEND>* pEndList_V);
	void		SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,CDrCurve* pBlendCurve_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,CDrCurve* pBlendCurve_V,
					CList<BLENDEND,BLENDEND>* pEndList_U,
					CList<BLENDEND,BLENDEND>* pEndList_V);
		          

protected: 
	

// Attributes

	
//Operations
public:

	~CMP_Gordon();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_Gordon)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
