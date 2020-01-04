 // ELMouse.h : header file
//
#ifndef _MI_OSPN_H 
#define _MI_OSPN_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrObj3D.h"
#include "MI_SSPN.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_OSPN : public CMI_SSPN
{
public:

	CMI_OSPN();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_OSPN)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	void	SetpDrObj3D(CDrObj3D* p){m_pDrObj3D = p;};	// because of Obj3DList in Obj3D
	//////////
	int		SpawnObj3DShowingDlg(CDrObj3D* pNewObj3D,CDrObj3D* pOldObj3D,
										CDrObject* pContextObj,UINT nContextType); 
	int		SpawnObj3DWithoutDlg(CDrObj3D* pNewObj3D,CDrObj3D* pOldObj3D,pMATRIX pXFMat,
									CString* pCid,CDrObject* pContextObj,UINT nContextType);
 	//////////////////////////////////////////////////////////////////////////////////
	int		FillSpawnedObj3DDlgDataBase(CDrObj3D* pDrObj3D,CString& Cid,CString& ParentCid);
   				
		
protected:

	int		GetInfoFromDlg(CDrObj3D* pNewObj3D, CDrObj3D* pOldObj3D);
	int		SpawnObj3D(pMATRIX pXFMat);
	int		SpawnListsInObj3D(pMATRIX pXFMat);
	int		SpawnNodeListinObj3D(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnNodeinObj3D(CDrNode* pOldNode,CDrNode* pNewNode,pMATRIX pXFMat);
	int		SpawnCurveListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnPatchListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnSolidListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat);
	int		SpawnObj3DListInObj3D(CDListMgr* pFillList, pMATRIX pXFMat);
	void	ReciprocateObj3DNodes(CDListMgr* pList);
	void	ReciprocateObj3DCurves(CDListMgr* pList);
	void	ReciprocateObj3DPatches(CDListMgr* pList);
	void	ReciprocateObj3DSolids(CDListMgr* pList);
	void	ReciprocateObj3DObj3Ds(CDListMgr* pList);
	///////////////////////////////////////////////// COPY OFF
	int		SpawnObj3DCopyOff(pMATRIX pXFMat);
	int		SpawnListsInObj3DCopyOff(pMATRIX pXFMat);
	int		SpawnObj3DListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat);
//	int		SpawnCurveListInObj3DCopyOff(CDListMgr* pFillList, pMATRIX pXFMat);
//	int		SpawnNodeListinObj3DCopyOff(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode);
//	int		SpawnNodeinObj3DCopyOff(CDrNode* pParentNode, pMATRIX pXFMat, BOOL bCNode);

	


protected:
	
	//////////////////////

    
//Operations
public:

	~CMI_OSPN();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_OSPN)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
