 // ELMouse.h : header file
//
#ifndef _MI_1SPN_H 
#define _MI_1SPN_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrMesh1D.h"
#include "MI_0SPN.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_1SPN : public CMI_0SPN
{
public:

	CMI_1SPN();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_1SPN)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	int		SpawnCurveShowingDlg(CDrMesh1D* pNewCurve,CDrMesh1D* pOldCurve,
											CDrObject* pContextObj,UINT nContextType); 
	int		SpawnCurveWithoutDlg(CDrMesh1D* pNewCurve,CDrMesh1D* pOldCurve,pMATRIX pXFMat,
										CString* pCid,CDrObject* pContextObj,UINT nContextType);
	//////////////////////////////////////////////////////////////////////////////////
	int		FillSpawnedCurveDlgDataBase(CDrMesh1D* pDrCurve,CString& Cid,CString& ParentCid);
    				
		
protected:

	int		GetInfoFromDlg(CDrMesh1D* pNewCurve, CDrMesh1D* pOldCurve);
	int		SpawnCurve(CDrMesh1D* pOldMESH1D, pMATRIX pXFMat);
	int		SpawnNodeListinCurve(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode);
//	int		SpawnFE1DListinCurve(CDListMgr* pFillList, pMATRIX pXFMat);
	/////////////////////////////////////////////////////////////////////////////////
	int		SpawnCurveCopyOff(pMATRIX pXFMat);
	int		SpawnCurveListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnFE1DListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat);
	////////////////////////////////////////////////
	void	ReciprocateCurveNodes(CDListMgr* pList);

	

protected:
	
	//////////////////////

    
//Operations
public:

	~CMI_1SPN();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_1SPN)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
