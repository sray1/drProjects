 // mp_Loft2.h : header file
//
#ifndef _MP_ROTAT_H 
#define _MP_ROTAT_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include <afxtempl.h>	// CList
#include "MI_GangP.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DListMgr.h"
#include "Def_CuPS.h"                    
#include "Def_Type.h"                    
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMP_Rotat : public CMI_GangP
class AFX_EXT_CLASS CMP_Rotat : public CMI_GangP
{
public:

	CMP_Rotat();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_Rotat)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:


	int			GoDoIt 
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
				); 


protected:
				
				
	BOOL		IsDataCompatible(CDListMgr* pCurveList,CDListMgr* pNodeList,
								CList<CURVELATCH,CURVELATCH>*	pLatchList,
								CList<int,int>* pElperSegList);
	int			SetPatchDataFromCurve(CDrCurve* pCurve,int nDir);
	int			LatticeCircles 
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
				); 
	int			CreateCircleList(CString& PatchID,pWORLD pConBZ,CList<int,int>& ElSegList,
							CDListMgr* pCurveList,double Ratio,double dAngle,int nCurves);
	int			CreatePackINodeForCircle(CString& PatchID,WORLD& wLocalPos,
																CDListMgr* pINodeList);
	int			PatCNodes_N_WtsFromCircles(CDrPatch* pDrPatch,CDListMgr* pCurveList_V,
													CDListMgr* pCurveList,pDOUBLE pWts_BZ);
	int			LatticeCurves_U(CDrPatch* pDrPatch,int nOrder_T,BOOL bClosed_T,int nSegBZ_T,
							int nConBZ_S,CDrCurve* pCurOriginal,CDListMgr* pCurveList);
	int			CreateFillINodeList(CDrPatch* pDrPatch,int iCurve_U,int nINode_U,
							int nDegree_S,int nDegree_T,int nConBZ_S,CDListMgr* pINodeList);
	int			PackINodeList(CString& PatchID,CDListMgr* pCNodeList,int iCurve_U,int nINode,
									 int nDeg_U,int nDeg_V,CDListMgr* pINodeList,int nConBZ_S);
	int			PostProcessLatticeCircles_V(CDListMgr* pCurveList_V,
							CList<CURVELATCH,CURVELATCH>* pLatchList_V,int nOrder_S);
	int			DeleteCurveList_V(CDListMgr* pCurveList_V,
							CList<CURVELATCH,CURVELATCH>* pLatchList_V);
	int			GetCNodeCoords_N_Wts(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld);
	int			SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V);
	void		SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V);

		          

protected: 
	

// Attributes
	//////////////////////
	pDOUBLE		m_pDis_Ang_T;
	BOOL		m_bAxis;
	int			m_nAxis;
	BOOL		m_bNegative;
	//////////////////////// Degenerate Case:Axis Intersecting Original Curve
	BOOL		m_bDegen[2];
	int			m_nDegen[2];
	
//Operations
public:

	~CMP_Rotat();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_Rotat)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
