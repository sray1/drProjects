 // mp_Loft2.h : header file
//
#ifndef _MS_ROTA3_H 
#define _MS_ROTA3_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include <afxtempl.h>	// CList
#include "MI_GangS.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DListMgr.h"
#include "Def_CuPS.h"                    
#include "Def_Type.h"                    
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMS_Rota3 : public CMI_GangS
{
public:

	CMS_Rota3();
//////////////////////////////////////
	DECLARE_SERIAL(CMS_Rota3)
//////////////////////////////////////


// Attributes 

// Operations
public:

// Implementation
public:


	int			GoDoIt 
				(
					BOOL							bGenBCurve,
					BOOL							bGenBPatch,
					//////////////////////////////////////////
					CString&						SolidID,		
					CDrSolid*						pDrSolid,
					//////////////////////////////////////////
					CDListMgr*						pNodeList,	// ist record: pFromIDNode
																// 2nd record: pToIDNode
					//////////////////////////////////////////
					CDListMgr*						pPatchList,	// given Curves always taken as U-dir
																// and later switched,if needed,i.e.,
																// nCurDir = 2
					CList<PATCHLATCH,PATCHLATCH>*	pLatchList,
					//////////////////////////////////////////
					CList<int,int>&					ElperSegList_W, // ist record: elem/seg
																	// 2nd record: #of BezSeg
					double							dAngle_W,
					double							Ratio_W,
					BOOL							bAxis,
					int								nAxis,
					BOOL							bNegative,
					//////////////////////////////////////////////
					CView*							pView
				); 


protected:
				
				
	int			ProceessCoordAxis(int nAxis,BOOL bNeg);
	BOOL		IsDataCompatible(CDListMgr* pPatchList,CDListMgr* pNodeList,
								CList<PATCHLATCH,PATCHLATCH>*	pLatchList,
								CList<int,int>* pElperSegList,BOOL bAxis);
	int			SetSolidDataFromPatch(CDrPatch* pPatch);
	int			RevolveCNs_N_WtsOfPatch(
					pWORLD				pPatConBZ, 	
					pDOUBLE				pPatWtsBZ, 	
					int					nPatConBZ,
					//////////////////////////////////////////////
					BOOL				bClosed,
					int					nSegBZ,//	# of Quadratic Bezier Segments
					pDOUBLE				pDis,	//	Angle Distribution for each Bez Patch in degrees
														//		(not cumulative)
					WORLD				wAxis,	//	unit direction vector of rotation axis
					WORLD				AxisPt, //  a pt. on the rotation vector
					//////////////////////////////////////////////
					pWORLD				pSolConBZ, 	
					pDOUBLE				pSolWtsBZ, 	
					int					nSolConBZ
				);
	int			PostSolCNodes_N_Wts(CDrSolid* pDrSolid,pWORLD pConBZ,pDOUBLE pWts_BZ,
											int nConBZ_S,int nConBZ_ST,int nConBZ_R);
	int			GetPatCNodeCoords_N_Wts(CDrPatch* pPatch, PATCHLATCH cLatch, 
												pWORLD pConOld, pDOUBLE pWtsOld);
	int			GetSolidInfo_R(CList<int,int>* pElperSegList,double Ratio,double dAng);
	int			SetInfoForDataBase(CDrSolid* pDrObject,
					CDListMgr* pPatchList_U,CDListMgr* pPatchList_V,CDListMgr* pPatchList_W,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_U,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_V,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_W);
	void		SetInfoForDataBase_1(CDrSolid* pDrObject,
					CDListMgr* pPatchList_U,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_U,
					CDListMgr* pPatchList_V,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_V,
					CDListMgr* pPatchList_W,
					CList<PATCHLATCH,PATCHLATCH>* pPatchLatchList_W);

		          

protected: 
	

// Attributes
	//////////////////////
	
//Operations
public:

	~CMS_Rota3();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMS_Rota3)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
