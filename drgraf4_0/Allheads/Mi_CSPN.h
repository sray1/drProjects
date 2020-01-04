 // ELMouse.h : header file
//
#ifndef _MI_CSPN_H 
#define _MI_CSPN_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrCurve.h"
#include "MI_NSPN.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_CSPN : public CMI_NSPN
{
public:

	CMI_CSPN();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_CSPN)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	int		SpawnCurveShowingDlg(CDrCurve* pNewCurve,CDrCurve* pOldCurve,
											CDrObject* pContextObj,UINT nContextType); 
	int		SpawnCurveWithoutDlg(CDrCurve* pNewCurve,CDrCurve* pOldCurve,pMATRIX pXFMat,
										CString* pCid,CDrObject* pContextObj,UINT nContextType);
	//////////////////////////////////////////////////////////////////////////////////
	int		FillSpawnedCurveDlgDataBase(CDrCurve* pDrCurve,CString& Cid,CString& ParentCid);
    				
		
protected:

	int		GetInfoFromDlg(CDrCurve* pNewCurve, CDrCurve* pOldCurve);
	int		SpawnCurve(pMATRIX pXFMat);
	int		SpawnListsInCurve(pMATRIX pXFMat);
	int		SpawnCNodeListinCurve(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnNodeListinCurve(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnNodeinCurve(CDrNode* pOldNode,CDrNode* pNewNode,pMATRIX pXFMat);
	/////////////////////////////////////////////////////////////////////////////////
	int		SpawnCurveCopyOff(pMATRIX pXFMat);
	int		SpawnCurveListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat);
	////////////////////////////////////////////////
	void	ReciprocateCurveNodes(CDListMgr* pList);

	

protected:
	
	//////////////////////

    
//Operations
public:

	~CMI_CSPN();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_CSPN)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
