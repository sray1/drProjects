// EDl2Mgr.h : header file
//
#ifndef _MNODMGR_H
#define _MNODMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrNode.h"
/////////////////////////////////////////////////////////////////////////////
// CMNodMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMNodMgr : public CObject
{
// Construction
public:  
	CMNodMgr();
	DECLARE_SERIAL(CMNodMgr)
protected: 
public:
// Implementation 

public:

	UINT		DoModal_ShowNodeToEdit(CDrNode* pDrNode, int nViewNumber);
//	UINT		DoModal_Spawn_N(CDrNode* pDrNode,CDrNode* pParentNode,CString* pID,CString* pParentID);
//	UINT		DoModal_SymmetryType(SPAWNTYPE& SpnType);	// in IGen.h
	//////////////////////////////////////////////////////////////

protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMNodMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMNodMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
