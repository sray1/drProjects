 // ELMouse.h : header file
//
#ifndef _MI_PSPN_H 
#define _MI_PSPN_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrPatch.h"
#include "MI_CSPN.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_PSPN : public CMI_CSPN
{
public:

	CMI_PSPN();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_PSPN)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	int		SpawnPatchShowingDlg(CDrPatch* pNewPatch,CDrPatch* pOldPatch,
										CDrObject* pContextObj,UINT nContextType); 
	int		SpawnPatchWithoutDlg(CDrPatch* pNewPatch,CDrPatch* pOldPatch,pMATRIX pXFMat,
									CString* pCid,CDrObject* pContextObj,UINT nContextType);
 	//////////////////////////////////////////////////////////////////////////////////
	int		FillSpawnedPatchDlgDataBase(CDrPatch* pDrPatch,CString& Cid,CString& ParentCid);
   				
		
protected:

	int		GetInfoFromDlg(CDrPatch* pNewPatch, CDrPatch* pOldPatch);
	int		SpawnPatch(pMATRIX pXFMat);
	int		SpawnListsInPatch(pMATRIX pXFMat);
	int		SpawnTriangleList(CString Cid, pMATRIX pXFMat);
	int		SpawnNodeListinPatch(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnNodeinPatch(CDrNode* pOldNode,CDrNode* pNewNode,pMATRIX pXFMat);
	int		SpawnCurveListInPatch(CDListMgr* pFillList, pMATRIX pXFMat);
	void	ReciprocatePatchNodes(CDListMgr* pList);
	void	ReciprocatePatchCurves(CDListMgr* pList);
	///////////////////////////////////////////////// COPY OFF
	int		SpawnPatchCopyOff(pMATRIX pXFMat);
	int		SpawnListsInPatchCopyOff(pMATRIX pXFMat);
	int		SpawnPatchListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat);
	


protected:
	
	//////////////////////

    
//Operations
public:

	~CMI_PSPN();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_PSPN)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
