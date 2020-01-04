 // ELMouse.h : header file
//
#ifndef _MI_2SPN_H 
#define _MI_2SPN_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrMesh2D.h"
#include "MI_1SPN.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_2SPN : public CMI_1SPN
{
public:

	CMI_2SPN();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_2SPN)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	int		SpawnPatchShowingDlg(CDrMesh2D* pNewPatch,CDrMesh2D* pOldPatch,
										CDrObject* pContextObj,UINT nContextType); 
	int		SpawnPatchWithoutDlg(CDrMesh2D* pNewPatch,CDrMesh2D* pOldPatch,pMATRIX pXFMat,
									CString* pCid,CDrObject* pContextObj,UINT nContextType);
 	//////////////////////////////////////////////////////////////////////////////////
	int		FillSpawnedPatchDlgDataBase(CDrMesh2D* pDrPatch,CString& Cid,CString& ParentCid);
   				
		
protected:

	int		GetInfoFromDlg(CDrMesh2D* pNewPatch, CDrMesh2D* pOldPatch);
	int		SpawnPatch(CDrMesh2D* pOldMESH2D, pMATRIX pXFMat);
	int		SpawnNodeListinPatch(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode);
//	int		SpawnCurveListInPatch(CDListMgr* pFillList, pMATRIX pXFMat);
	///////////////////////////////////////////////// COPY OFF
	int		SpawnPatchCopyOff(pMATRIX pXFMat);
	int		SpawnPatchListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnFE2DListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat);
	///////////////////////////////////////////////// COPY OFF
	void	ReciprocatePatchNodes(CDListMgr* pList);
	


protected:
	
	//////////////////////

    
//Operations
public:

	~CMI_2SPN();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_2SPN)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
