 // mp_Loft2.h : header file
//
#ifndef _MP_COOP4_H 
#define _MP_COOP4_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangP.h"
#include "DrPatch.h"
#include "Def_Type.h"                    
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMP_CooP4 : public CMI_GangP
class AFX_EXT_CLASS CMP_CooP4 : public CMI_GangP
{
public:

	CMP_CooP4();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_CooP4)
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
					CDListMgr*						pCurveList,
					CList<CURVELATCH,CURVELATCH>*	pLatchList
				); 

    				
		
protected:

	int			FillCurve_N_LatchLists(
					CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
					CDListMgr* pCurveList_U,CList<CURVELATCH,CURVELATCH>* pLatchList_U,
					CDListMgr* pCurveList_V,CList<CURVELATCH,CURVELATCH>* pLatchList_V);
	BOOL		AreCurvesCompatible_U(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
											BOOL bClosed,int& nDim_S,int& nTopDegree,int& nCon_BZ);
	BOOL		AreCurvesCompatible_V(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
											BOOL bClosed,int& nDim_S,int& nTopDegree,int& nCon_BZ);
	BOOL		IsCompat_Closed(CDListMgr* pCurveList,BOOL& bClosed);
	int			PreProcessCurvesControlInfo(CDListMgr* pCurveList,int& nDim_S,int& nTopDegree);
	BOOL		IsRational(CDListMgr* pCurveList);
	int			GetTopDegree(CDListMgr* pCurveList);
	BOOL		IsCompat_NumberOfCNodes(CDListMgr* pCurveList,int nTopDegree,
													int& nCurveSeg,int& nConBZ);
	BOOL		IsCompat_OutputInfo(CDListMgr* pCurveList,
						CList<CURVELATCH,CURVELATCH>* pLatchList);
				/////////////////////////////////////////////////////////////////////////
	int			ProcessCurves(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
							 pWORLD pCon_BZ,pDOUBLE pWts_BZ,int nCon_BZ,
							 int nCon_BZTot,int nDegree,int nDim);
	int			Elevate_PatCurves(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
										pWORLD pCon_BZ, pDOUBLE pWts_BZ,int nDegree, int nDim);
	int			GetCNodeCoords_N_Wts(CDrCurve* pCurve, CURVELATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld);
	int			DoNetCoons(
					pWORLD pConBZ_S,pDOUBLE pWtsBZ_S,int nConBZ_S,
					pWORLD pConBZ_T,pDOUBLE pWtsBZ_T,int nConBZ_T,
					pWORLD pPatCons,pDOUBLE pPatWts,int nTotOut);
	int			CreateSavePatCNodes_N_Wts(CDrPatch* pDrPatch,pWORLD pConBZ,pDOUBLE pWts_BZ,
																	int nCN_S,int nCN_T);
	int			SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V);
	void		SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CDListMgr* pCurveList_V,CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V);
	///////////////////////////////////////////////////////////////////////////////////////////
	int			LatticeCurves_U(CDrPatch* pDrPatch,int nOrder_T,BOOL bClosed_T,int nSegBZ_T,
											int nConBZ_S,CDrCurve* pCurOriginal);
	int			CreateFillINodeList_S(CDrPatch* pDrPatch,int iCurve_U,int nINode_U,
								int nDegree_S,int nDegree_T,int nConBZ_S,CDListMgr* pINodeList);
	int			PackINodeList_S(CString& PatchID,CDListMgr* pCNodeList,int iCurve_U,int nINode,
								int nDeg_U,int nDeg_V,CDListMgr* pINodeList,int nConBZ_S);
	int			CreateFillCNodeList_N_Wts_S(CDrPatch* pDrPatch,int iCurve_U,int nDegree_T,
								int nConBZ_S,CDListMgr* pCNodeList,pDOUBLE pWts);
	int			PackCNodeList_N_Wts_S(CString& PatchID,CDListMgr* pPatCNodeList,pDOUBLE pPatWts,
								int iCurve_U,int nDeg_V,int nConBZ_S,CDListMgr* pCNodeList,
																				pDOUBLE pWts);
	int			LatticeCurves_V(CDrPatch* pDrPatch,int nOrder_S,BOOL bClosed_S,int nSegBZ_S,
								int nConBZ_S,int nConBZ_T,CDrCurve* pCurOriginal);
	int			CreateFillCNodeList_N_Wts_T(CDrPatch* pDrPatch,int iCurve_V,int nDegree_S,
								int nConBZ_S,int nConBZ_T,CDListMgr* pCNodeList,pDOUBLE pWts);
	int			PackCNodeList_N_Wts_T(CString& PatchID,CDListMgr* pPatCNodeList,pDOUBLE pPatWts,
								int iCurve_V,int nDeg_U,int nConBZ_S,int nConBZ_T,
															CDListMgr* pCNodeList,pDOUBLE pWts);
	int			CreateFillINodeList_T(CDrPatch* pDrPatch,int iCurve_V,int nINode_V/*BzJnPts_S*/,
								int nDegree_S,int nDegree_T,int nConBZ_S,CDListMgr* pINodeList);
	int			PackINodeList_T(CString& PatchID,CDListMgr* pCNodeList,int iCurve_V,int nINode_V,
							int nDeg_U,int nDeg_V,CDListMgr* pINodeList,int nConBZ_S);
	int			SetDataFromCurve_Lattice(CDrCurve* pCurve);
	int			SetInfoDataBase_LatticeCurve(CDrCurve* pDrObject);
	void		SetInfo_LatticeCurve(CDrCurve* pDrObject);
//////////////////////////////////////////////////////////////////////////////////////

	

protected:  
// Attributes


//Operations
public:

	~CMP_CooP4();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_CooP4)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
