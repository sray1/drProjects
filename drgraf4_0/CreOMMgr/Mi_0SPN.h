 // ELMouse.h : header file
//
#ifndef _MI_0SPN_H 
#define _MI_0SPN_H 


//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

                    
#include "DrFE0D.h"
#include "DrMesh1D.h"
#include "DrMesh2D.h"
#include "DrMesh3D.h"
#include "DrMbj3D.h"
/////////////////////////////////////////////////////////////////////////////
// CMouse view
//////////////////////////////////////////////////////
class AFX_EXT_CLASS CMI_0SPN : public CObject
{
public:

	CMI_0SPN();
//////////////////////////////////////
	DECLARE_SERIAL(CMI_0SPN)
//////////////////////////////////////



// Attributes 

// Operations
public:

// Implementation
public:
 
	int				SpawnNodeShowingDlg(CDrFE0D* pNewNode,CDrFE0D* pOldNode,
											CDrObject* pContextObj,UINT nContextType); 
	int				SpawnNodeWithoutDlg(CDrFE0D* pNewNode,CDrFE0D* pOldNode,pMATRIX pXFMat,
										CString* pCid,BOOL bCNode,CDrObject* pContextObj,UINT nContextType);
	//////////////////////////////////////////////////////////////////////////////////
	int				FillSpawnedNodeDlgDataBase(CDrFE0D* pDrNode,CString& Cid,
											CDrFE0D* pParentNode,CString& ParentCid);
	///////////////////////////////////////////////////////////////////// for Direct spawning access
	int				TransformNodeCoords(CDrFE0D* pNode, pMATRIX pXFMat);
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
	int				SpawnNodeCopyOff(CDrFE0D* pParentNode, pMATRIX pXFMat, BOOL bCNode);

	

		
protected:

	int				SpawnNode(pMATRIX pXFMat);
	int				GetInfoFromDlg(CDrFE0D* pNewNode, CDrFE0D* pOldNode);
	

protected:

	
	CDrMbj3D*	m_pDrObj3D;
	CDrMesh3D*	m_pDrSolid;
	CDrMesh2D*	m_pDrPatch;
	CDrMesh1D*	m_pDrCurve;
	CDrFE0D*	m_pDrNode;
	////////////////////////////////////////////////////// Needed for Naming
	CDrObject*	m_pParObj;		// Parent Object
	CDrFE0D*	m_pContextNod;		// Parent Object
	CDrMesh1D*	m_pContextCur;		// Parent Object
	CDrMesh2D*	m_pContextPat;		// Parent Object
	CDrMesh3D*	m_pContextSol;		// Parent Object
	CDrMbj3D*	m_pContextO3D;		// Parent Object
	////////////////////////////////////////////////////// Copy OFF Spawning
	CDListMgr*	m_pNDoneList;
	CDListMgr*	m_pCDoneList;
	CDListMgr*	m_pPDoneList;
	CDListMgr*	m_pSDoneList;
	CDListMgr*	m_pODoneList;

    
//Operations
public:

	~CMI_0SPN();
	virtual void Serialize(CArchive& ar);
/*
	// Generated message map functions

	//{{AFX_MSG(CMI_0SPN)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
