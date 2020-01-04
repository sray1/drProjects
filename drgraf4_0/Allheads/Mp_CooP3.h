 // mp_Loft2.h : header file
//
#ifndef _MP_COOP3_H 
#define _MP_COOP3_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "MI_GangP.h"
#include "DrPatch.h"
#include "Def_Type.h"                    
//////////////////////////////////////////////////////
//class AFX_EXT_CLASS CMP_CooP3 : public CMI_GangP
class AFX_EXT_CLASS CMP_CooP3 : public CMI_GangP
{
public:

	CMP_CooP3();
//////////////////////////////////////
	DECLARE_SERIAL(CMP_CooP3)
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
					CDListMgr* pCurveList_V,CList<CURVELATCH,CURVELATCH>* pLatchList_V,
					CDListMgr* pCurveList_W,CList<CURVELATCH,CURVELATCH>* pLatchList_W);
	BOOL		AreCurvesCompatible(CDListMgr* pCurveList,CList<CURVELATCH,CURVELATCH>* pLatchList,
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
	int			GenerateCNodes(pWORLD pConBZ,pDOUBLE pWtsBZ,int nConBZ_S,
								pWORLD pPatCons,pDOUBLE pPatWts,int nTotOut);
	int			CreateSavePatCNodes_N_Wts(CDrPatch* pDrPatch,pWORLD pConBZ,pDOUBLE pWts_BZ,
																				int nCN_S);
	int			GeneratePatchBndryCurves();
	int			SetInfoForDataBase(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CDListMgr* pCurveList_V,CDListMgr* pCurveList_W,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CList<CURVELATCH,CURVELATCH>* pCurveLatchList_W);
	void		SetInfoForDataBase_1(CDrPatch* pDrObject,
					CDListMgr* pCurveList_U,CList<CURVELATCH,CURVELATCH>* pCurveLatchList_U,
					CDListMgr* pCurveList_V,CList<CURVELATCH,CURVELATCH>* pCurveLatchList_V,
					CDListMgr* pCurveList_W,CList<CURVELATCH,CURVELATCH>* pCurveLatchList_W);

	

protected:  
// Attributes


//Operations
public:

	~CMP_CooP3();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMP_CooP3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
