 // mp_Loft2.h : header file
//
#ifndef _MP_LOFTX_H 
#define _MP_LOFTX_H 

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
//class AFX_EXT_CLASS CMP_LoftX : public CMI_GangP
class AFX_EXT_CLASS CMP_LoftX : public CMI_GangP
{
public:

	CMP_LoftX();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_LoftX)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:

		int		GoDoIt 
				(
					BOOL							bGenBCurve,
					//////////////////////////////////////////
					BOOL							bGordon,	// For DegreeElev of CurveList
					CDrCurve*						pBlendCurve_U,
					//////////////////////////////////////////////
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
				); 
		CDrCurve* CreateCurve(BLENDEND BlendEnd,CDrCurve* pBlendCurve,CDListMgr* pINodeList,
									CList<int,int>& ElSegList,double Ratio,CString& PatchID);

protected:
				
				

		int		DeleteCurveList_V(CDListMgr* pCurveList_V,
							CList<CURVELATCH,CURVELATCH>* pLatchList_V);
		BOOL	AreCurvesCompatible(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
					CDrCurve* pBlendCurve,BOOL bClosed,int& nDim_S,int& nTopDegree,int& nCon_BZ,
					CDrCurve* pBlendCurve_U,BOOL bGordon);
		BOOL	IsCompat_Closed(CDListMgr* pCurveList,BOOL& bClosed);
		int		PreProcessCurvesControlInfo(CDListMgr* pCurveList,int& nDim_S,int& nTopDegree);
		BOOL	IsRational(CDListMgr* pCurveList);
		int		GetTopDegree(CDListMgr* pCurveList);
		BOOL	IsCompat_NumberOfCNodes(CDListMgr* pCurveList,int nTopDegree,
													int& nCurveSeg,int& nConBZ);
		BOOL	IsCompat_OutputInfo(CDListMgr* pCurveList,
							CList<CURVELATCH,CURVELATCH>* pLatchList_U);
		////////////////////////////////////////////////////////////////////////////////////
//		int		CreateDataNodeList(CDListMgr* pNodeList,CDListMgr* pCurveList,
//														int& nNodes_U,int& nNodes_V);
		//////////////////////////////////////////////////////////////////////////////////// T-Direction
		int		LatticeCurves 
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
				);
		//////////////////////////////////////////////////////////////////////////////////// PreProcess
		int		CreateCurveList(CString& PatchID,CDListMgr* pNodeList,
							CDListMgr* pCurveList,CList<int,int>& ElSegList,double Ratio,
							CList<BLENDEND,BLENDEND>* pEndList,CDrCurve* pBlendCurve,
							int nNode,int nCurves,int& nConBZ,int& nBezSeg,int nDir);
		int		PackINodeList_2(CDListMgr* pNodeList,int iCurve,int nNode,
									 CDListMgr* pINodeList,int nMax);
		int		PackINodeList_TanNodeV(CDListMgr* pNodeList,int nNodeU,int nNodeV,
									 CDListMgr* pINodeList,BOOL bEndV_0);
		int		PackINodeList(CDListMgr* pNodeList,int iCurve,int nNode,CDListMgr* pINodeList);
		int		Do_Curve(CDrCurve* pCurve,CList<int,int>& ElSegList);
		/////////////////////////////////////////////////////////////////////////////////////
		int		CreateLatticePtWtList(pDOUBLE pWtsBZ,CList<double,double>& WtList,int nDegree,
									  int nConBZ, int nCurves, int nTotData);
		int		CreateCurveEndTanList(CDListMgr* pCurveList,CList<WORLD,WORLD>& EndTanList);
		int		CreateEndTanListForACurve(CDrCurve* pCurve,CList<WORLD,WORLD>& EndTanList);
		int		EstimateCornerTwists(CDListMgr* pNodeList,CList<double,double>* pWtList,
					CList<WORLD,WORLD>& EndTanList_U,CList<WORLD,WORLD>& EndTanList_V,
					int nNodes_U,int nNodes_V,PWMAT2 CornerTwist,TWIST TwistMethod);
		int		ExtendEndList_V(BOOL bClosed_U,int nDegree_U,
					CDListMgr* pCurveList_U,int nNodes_U,CDrCurve* pCurve_U0,CDrCurve* pCurve_UN,
					CList<int,int>& ElperSegList_U,CList<WORLD,WORLD>& EndTanList_V,
					PWMAT2 CornerTwist,CList<BLENDEND,BLENDEND>& EndListExt_V);
		int		CreateTempTanNodeList(CList<WORLD,WORLD>* pEndTanList,CDListMgr* pTanNodeList);
		int		PackBlendEndForTanCurve(PWMAT2 CornerTwist,BLENDEND& BlendEnd,BOOL bBegin);
		int		CreateTangentCurve(CDrCurve* pCurve,
							BLENDEND BlendEnd,CDrCurve* pBlendCurve,CDListMgr* pINodeList,
							pDOUBLE pKnots,CList<int,int>& ElSegList);
		int		SaveCNodeCoordsAsBCL_V(CDrCurve* pTanCurve,
							CList<BLENDEND,BLENDEND>& EndListExt_V);
		int		SaveCNodeCoordsAsBCR_V(CDrCurve* pTanCurve,
							CList<BLENDEND,BLENDEND>& EndListExt_V);
		/////////////////////////////////////////////////////////////////////////////////////
		int		Process_OutputInfo(CList<int,int>* pElperSegList,int nDegree,int nBezSeg,
								  double Ratio,BOOL& bUnifOT,int& nMaxOSeg,int& nOut);
		/////////////////////////////////////////////////////////////////////////////////////
		int		ProcessCurves(CDListMgr* pLoftCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
							 pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ,
							 int nCon_BZTot,int nDegree,int nDim);
		int		ProcessCurves_Loft(CDListMgr* pLoftCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
							 pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ,
							 int nCon_BZTot,int nDegree,int nDim);
		int		Elevate_PatCurves(CDListMgr* pLoftCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
											pWORLD pCon_BZ, pDOUBLE pWts_BZ,int nDegree, int nDim);
		int		GetCNodeCoords_N_Wts(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld);
		//////////////////////////////////////////////////////////////////////////////////////
		int		ExtendEndList_V_NonAdvanced(CList<BLENDEND,BLENDEND>* pEndList_V,int nConBZ_S,
										  CList<BLENDEND,BLENDEND>& EndListExt_V);
		int		PostPatBezInfoUsingBlendingInfo(
							CDrPatch* pPatch,CList<int,int>& ElSegList,
							CList<BLENDEND,BLENDEND>* pEndListExt,CDrCurve* pBlendCurve,
							double Ratio,pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ,
							int nCurves,int& nCon_T,int& nBezSeg_T,int nDir);
		int		PostPatBezInfo(CDrPatch* pPatch,CDListMgr& TemCNodeList,pDOUBLE pTemPatWts_BZ,
																		int nCon_S,int nCon_T);
		int		TempPostPatBezJunctionPtsInINodeList(pWORLD pConBZ,int nConBZ,int nCol,
												int nCurves,CDListMgr* pINodeList);
		int		PackPatBezJunctionWtsInDataWtsArray(pDOUBLE pWtsBZ,int nConBZ,int nCol,
												int nCurves,pDOUBLE pTemWts_BZ);
		int		GeneratePatchBezInfoFromBlendCurve(
						BLENDEND BlendEnd,CDrCurve* pBlendCurve,CDListMgr* pINodeList,
						pDOUBLE pWts_DT,CList<int,int>& ElSegList,CDListMgr* pPatCNodeList,
						pDOUBLE pPatWts_BZ,double Ratio,CString& PatchID,int nCon_T,int nCol);
		int		Copy_N_TransferBezControlInfo(CDrCurve* pCurve,CDListMgr* pPatCNodeList,
														CString& PatchID,int nCol);
		int		Copy_N_TransferBezWeightInfo(CDrCurve* pCurve,pDOUBLE pPatWts_BZ,int nCon_T,int nCol);
		//////////////////////////////////////////////////////////////////////////////////////
		int		SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CList<BLENDEND,BLENDEND>* pEndList_V,CDrCurve* pBlendCurve_V,
					int nCurDir);
		void	SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<BLENDEND,BLENDEND>* pEndList_V,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,CDrCurve* pBlendCurve_V);
		void	SetInfoForDataBase_2(CDrPatch* pDrObject,
					CList<BLENDEND,BLENDEND>* pEndList_U,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,CDrCurve* pBlendCurve_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V);
		          

protected: 
	

// Attributes
	BOOL		m_bGordon;

	
//Operations
public:

	~CMP_LoftX();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_LoftX)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
