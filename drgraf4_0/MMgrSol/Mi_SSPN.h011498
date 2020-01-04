 // ELMouse.h : header file
//
#ifndef _MI_SSPN_H 
#define _MI_SSPN_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrSolid.h"
#include "MI_PSPN.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_SSPN : public CMI_PSPN
{
public:

	CMI_SSPN();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_SSPN)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	int		SpawnSolidShowingDlg(CDrSolid* pNewSolid,CDrSolid* pOldSolid,
										CDrObject* pContextObj,UINT nContextType); 
	int		SpawnSolidWithoutDlg(CDrSolid* pNewSolid,CDrSolid* pOldSolid,pMATRIX pXFMat,
									CString* pCid,CDrObject* pContextObj,UINT nContextType);
 	//////////////////////////////////////////////////////////////////////////////////
	int		FillSpawnedSolidDlgDataBase(CDrSolid* pDrSolid,CString& Cid,CString& ParentCid);
   				
		
protected:

	int		GetInfoFromDlg(CDrSolid* pNewSolid, CDrSolid* pOldSolid);
	int		SpawnSolid(pMATRIX pXFMat);
	int		SpawnListsInSolid(pMATRIX pXFMat);
	int		SpawnTetraList(CString Cid, pMATRIX pXFMat);
	int		SpawnPentaList(CString Cid, pMATRIX pXFMat);
	int		SpawnHexaList(CString Cid, pMATRIX pXFMat);
	int		SpawnNodeListinSolid(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode);
	int		SpawnCurveListInSolid(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnPatchListInSolid(CDListMgr* pFillList, pMATRIX pXFMat);
	void	ReciprocateSolidNodes(CDListMgr* pList);
	void	ReciprocateSolidCurves(CDListMgr* pList);
	void	ReciprocateSolidPatches(CDListMgr* pList);

	


protected:
	
	CDrSolid*	m_pDrSolid;
	//////////////////////

    
//Operations
public:

	~CMI_SSPN();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_SSPN)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
