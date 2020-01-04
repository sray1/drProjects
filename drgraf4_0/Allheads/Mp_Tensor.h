 // mp_Loft2.h : header file
//
#ifndef _MP_TENSOR_H 
#define _MP_TENSOR_H 

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
//class AFX_EXT_CLASS CMP_Tensor : public CMI_GangP
class AFX_EXT_CLASS CMP_Tensor : public CMI_GangP
{
public:

	CMP_Tensor();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_Tensor)
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
					BOOL							bAdvanced,	// tangents/twist BC
					//////////////////////////////////////////
					CString&						PatchID,		
					CDrPatch*						pDrPatch,
					CDListMgr*						pNodeList,
					//////////////////////////////////////////////
					PWMAT2							pCornerTwist,// it is full,if TW_USER
					TWIST							TwistMethod,
					//////////////////////////////////////////////
					int								n_Nodes_U,
					CList<int,int>&					ElperSegList_U,
					double							Ratio_U,
					CDrCurve*						pBlendCurve_U,
					CList<BLENDEND,BLENDEND>*		pEndList_U,	// if(bClosed_U or Linear_U,Circle_U,
																// parabola_U) EndList_U Empty
					//////////////////////////////////////////////
					int								n_Nodes_V,
					CList<int,int>&					ElperSegList_V,
					double							Ratio_V,
					CDrCurve*						pBlendCurve_V,
					CList<BLENDEND,BLENDEND>*		pEndList_V,	// if(bClosed_V or Linear_V,Circle_V,
																// parabola_V) EndList_V Empty
					//////////////////////////////////////////////
					CView*							pView
				); 

protected:
				
				
	////////////////////////////////////////////////////////////////////////////////////////////////
	int			DeleteCurveList(CDListMgr* pCurveList,
							CList<CURVELATCH,CURVELATCH>* pLatchList);
	int			LatticeCurves 
				(
					int								nDir,
					CString&						PatchID,		
					CDListMgr*						pNodeList,		// Lattice
					int								nCurves,		// = nNode_V
					//////////////////////////////////////////////
					int								nNodes,
					CList<int,int>&					ElperSegList,
					double							Ratio,
					CDListMgr*						pCurveList,	
					CList<CURVELATCH,CURVELATCH>*	pLatchList,
					CList<BLENDEND,BLENDEND>*		pEndList,		// Given Curves End Conds in U-dir
																		// or BlendCurve End Conds in U-dir
																		// as many as n_Nodes_V
					CDrCurve*						pBlendCurve,
					///////////////////////////////////////////////
					pWORLD&							pCon_BZ, 	
					pDOUBLE&						pWts_BZ,
					int&							nBezSeg,
					int&							nConBZ,
					BOOL							bCreate
				); 
	int			CreateCurveList(CString& PatchID,CDListMgr* pNodeList,
							CDListMgr* pCurveList,CList<int,int>& ElSegList,double Ratio,
							CList<BLENDEND,BLENDEND>* pEndList,CDrCurve* pBlendCurve,
							int nNode,int nCurves,int& nConBZ,int& nBezSeg,int nDir);
	int			PackINodeList_2(CDListMgr* pNodeList,int iCurve,int nNode,
									 CDListMgr* pINodeList,int nMax);
	int			PackINodeList(CDListMgr* pNodeList,int iCurve,int nNode,CDListMgr* pINodeList);
	CDrCurve*	CreateCurve(BLENDEND BlendEnd,CDrCurve* pBlendCurve,CDListMgr* pINodeList,
								CList<int,int>& ElSegList,double Ratio,CString& PatchID);
	int			Do_Curve(CDrCurve* pCurve,CList<int,int>& ElSegList);
	int			CreateLatticePtWtList(pDOUBLE pWtsBZ,CList<double,double>& WtList,int nDegree,
									  int nConBZ, int nCurves, int nTotData);
	int			CreateCurveEndTanList(CDListMgr* pCurveList,CList<WORLD,WORLD>& EndTanList);
	int			CreateEndTanListForACurve(CDrCurve* pCurve,CList<WORLD,WORLD>& EndTanList);
	int			PackINodeList_TanNodeV(CDListMgr* pNodeList,int nNodeU,int nNodeV,
									 CDListMgr* pINodeList,BOOL bEndV_0);
	int			EstimateCornerTwists(CDListMgr* pNodeList,CList<double,double>* pWtList,
					CList<WORLD,WORLD>& EndTanList_U,CList<WORLD,WORLD>& EndTanList_V,
					int n_Nodes_U,int n_Nodes_V,PWMAT2 CornerTwist,TWIST TwistMethod);
	int			ExtendEndList_V(
					CDListMgr* pCurveList_U,int n_Nodes_U,CDrCurve* pBlendCurve_U,
					CList<int,int>& ElperSegList_U,CList<WORLD,WORLD>& EndTanList_V,
					PWMAT2 CornerTwist,CList<BLENDEND,BLENDEND>& EndListExt_V
							  );
	int			PackBlendEndForTanCurve(PWMAT2 CornerTwist,BLENDEND& BlendEnd,BOOL bBegin);
	int			CreateTempTanNodeList(CList<WORLD,WORLD>* pEndTanList,CDListMgr* pTanNodeList);
	int			CreateTangentCurve(CDrCurve* pCurve,
							BLENDEND BlendEnd,CDrCurve* pBlendCurve,CDListMgr* pINodeList,
							pDOUBLE pKnots,CList<int,int>& ElSegList);
	int			SaveCNodeCoordsAsBCL_V(CDrCurve* pTanCurve,
							CList<BLENDEND,BLENDEND>& EndListExt_V);
	int			SaveCNodeCoordsAsBCR_V(CDrCurve* pTanCurve,
							CList<BLENDEND,BLENDEND>& EndListExt_V);
	int			Process_OutputInfo(CList<int,int>* pElperSegList,int nDegree,int nBezSeg,
								  double Ratio,BOOL& bUnifOT,int& nMaxOSeg,int& nOut);
	int			ProcessCurves(CDListMgr* pLoftCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
							 pWORLD pCon_BZ,pDOUBLE pWts_BZ,int nCon_BZ,
							 int nCon_BZTot,int nDegree,int nDim);
	int			GetCNodeCoords_N_Wts(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld);
	int			ExtendEndList_V_NonAdvanced(CList<BLENDEND,BLENDEND>* pEndList_V,int nConBZ_S,
										  CList<BLENDEND,BLENDEND>& EndListExt_V);
	int			PostPatBezInfoUsingBlendingInfo(
							CDrPatch* pPatch,CList<int,int>& ElSegList,
							CList<BLENDEND,BLENDEND>* pEndListExt,CDrCurve* pBlendCurve,
							double Ratio,pWORLD pCon_BZ,pDOUBLE pWts_BZ,int nCon_BZ,
							int nCurves,int& nCon_T,int& nBezSeg_T,int nDir);
	int			PostPatBezInfo(CDrPatch* pPatch,CDListMgr& TemCNodeList,pDOUBLE pTemPatWts_BZ,
																	int nCon_S,int nCon_T);
	int			TempPostPatBezJunctionPtsInINodeList(pWORLD pCon_BZ,int nConBZ,int nCol,
												int nCurves,CDListMgr* pINodeList);
	int			PackPatBezJunctionWtsInDataWtsArray(pDOUBLE pWts_BZ,int nConBZ,int nCol,
												int nCurves,pDOUBLE pTemWts_BZ);
	int			GeneratePatchBezInfoFromBlendCurve(
						BLENDEND BlendEnd,CDrCurve* pBlendCurve,CDListMgr* pINodeList,
						pDOUBLE pWts_DT,CList<int,int>& ElSegList,CDListMgr* pPatCNodeList,
						pDOUBLE pPatWts_BZ,double Ratio,CString& PatchID,int nCon_T,int nCol);
	int			Copy_N_TransferBezControlInfo(CDrCurve* pCurve,CDListMgr* pPatCNodeList,
														CString& PatchID,int nCol);
	int			Copy_N_TransferBezWeightInfo(CDrCurve* pCurve,pDOUBLE pPatWts_BZ,int nCon_T,int nCol);
	int			SetInfoForDataBase(CDrPatch* pDrObject,
									CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
									CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
									CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
									CDrCurve* pBlendCurve_U,CDrCurve* pBlendCurve_V,
									CDListMgr* pNodeList,
									CList<BLENDEND,BLENDEND>* pEndList_U,
									CList<BLENDEND,BLENDEND>* pEndList_V);
	void		SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,CDrCurve* pBlendCurve_U,
					CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,CDrCurve* pBlendCurve_V,
					CDListMgr* pNodeList,
					CList<BLENDEND,BLENDEND>* pEndList_U,
					CList<BLENDEND,BLENDEND>* pEndList_V);
	void		SetInfoForDataBase_2(CDrPatch* pDrObject,CDListMgr* pCurveList,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList,CDrCurve* pBlendCurve);
		          

protected: 
	

// Attributes
	////////////////////////
	pWORLD		pCon_BZ_S; 	
	pDOUBLE		pWts_BZ_S;
	pWORLD		pCon_BZ_T; 	
	pDOUBLE		pWts_BZ_T;

	
//Operations
public:

	~CMP_Tensor();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_Tensor)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
