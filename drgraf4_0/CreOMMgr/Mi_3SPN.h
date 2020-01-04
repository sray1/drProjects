 // ELMouse.h : header file
//
#ifndef _MI_3SPN_H 
#define _MI_3SPN_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrMesh3D.h"
#include "MI_2SPN.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_3SPN : public CMI_2SPN
{
public:

	CMI_3SPN();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_3SPN)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	int		SpawnSolidShowingDlg(CDrMesh3D* pNewSolid,CDrMesh3D* pOldSolid,
										CDrObject* pContextObj,UINT nContextType); 
	int		SpawnSolidWithoutDlg(CDrMesh3D* pNewSolid,CDrMesh3D* pOldSolid,pMATRIX pXFMat,
									CString* pCid,CDrObject* pContextObj,UINT nContextType);
 	//////////////////////////////////////////////////////////////////////////////////
	int		FillSpawnedSolidDlgDataBase(CDrMesh3D* pDrSolid,CString& Cid,CString& ParentCid);
   				
		
protected:

	int		GetInfoFromDlg(CDrMesh3D* pNewSolid, CDrMesh3D* pOldSolid);
	int		SpawnSolid(CDrMesh3D* pOldMESH2D, pMATRIX pXFMat);
	int		SpawnNodeListinSolid(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode);
//	int		SpawnCurveListInSolid(CDListMgr* pFillList, pMATRIX pXFMat);
	///////////////////////////////////////////////// COPY OFF
	int		SpawnSolidCopyOff(pMATRIX pXFMat);
	int		SpawnSolidListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnFE3DListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat);
	///////////////////////////////////////////////// COPY OFF
	void	ReciprocateSolidNodes(CDListMgr* pList);
	


protected:
	
	//////////////////////

    
//Operations
public:

	~CMI_3SPN();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_3SPN)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
