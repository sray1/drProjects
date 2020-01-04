 // mp_Loft2.h : header file
//
#ifndef _MS_XTRUD_H 
#define _MS_XTRUD_H 

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
class AFX_EXT_CLASS CMS_Xtrud : public CMI_GangS
{
public:

	CMS_Xtrud();
//////////////////////////////////////
	DECLARE_SERIAL(CMS_Xtrud)
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
					int								nExtruType,
									// 1 = Given: Extrusion Direction Nodes
									// 2 = Given: 3 Lenths (wLen) to Extrude to
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
					WORLD							wLen_W,
					double							dLen_W,
					double							Ratio_W,
					//////////////////////////////////////////////
					CView*							pView
				); 


protected:
				
				
	int			ProceessLength_N_Axis(int nExtruType,double& dLen,WORLD& wLen);
	BOOL		IsDataCompatible(CDListMgr* pPatchList,CDListMgr* pNodeList,
								CList<PATCHLATCH,PATCHLATCH>*	pLatchList,
								CList<int,int>* pElperSegList,int nExtruType);
	int			SetSolidDataFromPatch(CDrPatch* pPatch);
	int			ExtrudeCNs_N_WtsOfPatch
				(
					pWORLD							pPatConBZ, 	
					pDOUBLE							pPatWtsBZ, 	
					int								nPatConBZ,
					//////////////////////////////////////////////
					WORLD							wAxis,
					double							dLen,
					pWORLD							pSolConBZ, 	
					pDOUBLE							pSolWtsBZ, 	
					int								nSolConBZ
				);
	int			PostSolCNodes_N_Wts(CDrSolid* pDrSolid,pWORLD pConBZ,pDOUBLE pWts_BZ,
											int nConBZ_S,int nConBZ_T,int nConBZ_R);
	int			GetPatCNodeCoords_N_Wts(CDrPatch* pPatch, PATCHLATCH cLatch, 
									pWORLD pConOld, pDOUBLE pWtsOld);
	int			GetSolidInfo_R(CList<int,int>* pElperSegList,double Ratio);
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

	~CMS_Xtrud();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMS_Xtrud)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
