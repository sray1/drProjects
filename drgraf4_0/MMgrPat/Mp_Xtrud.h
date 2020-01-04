 // mp_Loft2.h : header file
//
#ifndef _MP_XTRUD_H 
#define _MP_XTRUD_H 

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
//class AFX_EXT_CLASS CMP_Xtrud : public CMI_GangP
class AFX_EXT_CLASS CMP_Xtrud : public CMI_GangP
{
public:

	CMP_Xtrud();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_Xtrud)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:


		int		GoDoIt 
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
				); 

protected:
				
				
		int		ProceessLength_N_Axis(int nExtruType,double& dLen,WORLD& wLen);
		BOOL	IsDataCompatible(CDListMgr* pCurveList,CDListMgr* pNodeList,
								CList<CURVELATCH,CURVELATCH>*	pLatchList,
								CList<int,int>* pElperSegList,int nExtruType);
		int		SetPatchDataFromCurve(CDrCurve* pCurve,int nDir);
		int		LatticeCurves_V 
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
				); 
		int		CreateCurveList_V(CString& PatchID,pWORLD pConBZ,CList<int,int>& ElSegList,
					CDListMgr* pCurveList,CDrCurve* pCurOriginal,double Ratio,WORLD wAxis,
																double dLen,int nCurves);
		int		GetAPtByExtrusion(pWORLD pDOld, WORLD dir, double depth, WORLD& wNew);
		int		CreatePackINodeForCurve(CString& PatchID,WORLD& wLocalPos,CDListMgr* pINodeList);
		int		PatCNodes_N_WtsFromCurves(CDrPatch* pDrPatch,CDListMgr* pCurveList_V,
													CDListMgr* pCurveList,pDOUBLE pWts_BZ);
		int		LatticeCurves_U(CDrPatch* pDrPatch,int nOrder_T,BOOL bClosed_T,int nSegBZ_T,
							int nConBZ_S,CDrCurve* pCurOriginal,CDListMgr* pCurveList);
		int		CreateFillINodeList(CDrPatch* pDrPatch,int iCurve_U,int nINode_U,
								int nDegree_S,int nDegree_T,int nConBZ_S,CDListMgr* pINodeList);
		int		PackINodeList(CString& PatchID,CDListMgr* pCNodeList,int iCurve_U,int nINode,
									 int nDeg_U,int nDeg_V,CDListMgr* pINodeList,int nConBZ_S);
		int		PostProcessLatticeCurves_V(CDListMgr* pCurveList_V,
							CList<CURVELATCH,CURVELATCH>* pLatchList_V,int nOrder_S);
		int		DeleteCurveList_V(CDListMgr* pCurveList_V,
							CList<CURVELATCH,CURVELATCH>* pLatchList_V);
		int		GetCNodeCoords_N_Wts(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld);
		int		SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V);
		void	SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V);

		          

protected: 
	

// Attributes
	//////////////////////
	
//Operations
public:

	~CMP_Xtrud();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_Xtrud)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
