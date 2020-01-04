 // ELMouse.h : header file
//
#ifndef _MI_NSPN_H 
#define _MI_NSPN_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DrSolid.h"
#include "DrObj3D.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_NSPN : public CObject
{
public:

	CMI_NSPN();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_NSPN)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	int				SpawnNodeShowingDlg(CDrNode* pNewNode,CDrNode* pOldNode,
											CDrObject* pContextObj,UINT nContextType); 
	int				SpawnNodeWithoutDlg(CDrNode* pNewNode,CDrNode* pOldNode,pMATRIX pXFMat,
										CString* pCid,BOOL bCNode,CDrObject* pContextObj,UINT nContextType);
	//////////////////////////////////////////////////////////////////////////////////
	int				FillSpawnedNodeDlgDataBase(CDrNode* pDrNode,CString& Cid,
											CDrNode* pParentNode,CString& ParentCid);
	///////////////////////////////////////////////////////////////////// for Direct spawning access
	int				TransformNodeCoords(CDrNode* pNode, pMATRIX pXFMat);
	///////////////////////////////////////////////////////////////////// Copy OFF Spawning
	CDListMgr*		GetNDoneList(){return m_pNDoneList;};
	void			SetNDoneList(CDListMgr* pList){m_pNDoneList = pList;};
	CDListMgr*		GetCDoneList(){return m_pCDoneList;};
	void			SetCDoneList(CDListMgr* pList){m_pCDoneList = pList;};
	CDListMgr*		GetPDoneList(){return m_pPDoneList;};
	void			SetPDoneList(CDListMgr* pList){m_pPDoneList = pList;};
	CDListMgr*		GetSDoneList(){return m_pSDoneList;};
	void			SetSDoneList(CDListMgr* pList){m_pSDoneList = pList;};
	CDListMgr*		GetODoneList(){return m_pODoneList;};
	void			SetODoneList(CDListMgr* pList){m_pODoneList = pList;};
	///
	int				SpawnNodeListCopyOff(CDListMgr* pFillList, pMATRIX pXFMat, BOOL bCNode);
	int				SpawnNodeCopyOff(CDrNode* pParentNode, pMATRIX pXFMat, BOOL bCNode);

	

		
protected:

	CDrNode*		SimilarNode_AddToDataBase(CDrNode* pOldNode,int& nActiveIndex);
	int				SimilarNode_DeleteFromDataBase(int& nActiveIndex,BOOL bCNode);
	int				SpawnNode(pMATRIX pXFMat);
	int				GetInfoFromDlg(CDrNode* pNewNode, CDrNode* pOldNode);
	

protected:

	
	CDrObj3D*	m_pDrObj3D;
	CDrSolid*	m_pDrSolid;
	CDrPatch*	m_pDrPatch;
	CDrCurve*	m_pDrCurve;
	CDrNode*	m_pDrNode;
	////////////////////////////////////////////////////// Needed for Naming
	CDrObject*	m_pParObj;		// Parent Object
	CDrNode*	m_pContextNod;		// Parent Object
	CDrCurve*	m_pContextCur;		// Parent Object
	CDrPatch*	m_pContextPat;		// Parent Object
	CDrSolid*	m_pContextSol;		// Parent Object
	CDrObj3D*	m_pContextO3D;		// Parent Object
	////////////////////////////////////////////////////// Copy OFF Spawning
	CDListMgr*	m_pNDoneList;
	CDListMgr*	m_pCDoneList;
	CDListMgr*	m_pPDoneList;
	CDListMgr*	m_pSDoneList;
	CDListMgr*	m_pODoneList;

    
//Operations
public:

	~CMI_NSPN();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_NSPN)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
