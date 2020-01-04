// EDl2Mgr.h : header file
//
#ifndef _MMS0MGR_H
#define _MMS0MGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
//#include "Def_CuPS.h"
#include "DrFE0D.h"
/////////////////////////////////////////////////////////////////////////////
// CMMs0Mgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMMs0Mgr : public CObject
{
// Construction
public:  
	CMMs0Mgr();
	DECLARE_SERIAL(CMMs0Mgr)
protected: 
public:
// Implementation 

public:

	UINT		DoModal_ShowNodeToEdit(CDrFE0D* pDrNode, int nViewNumber);
;	UINT		DoModal_Spawn_N(CDrFE0D* pDrNode,CDrFE0D* pParentNode,CString* pID,CString* pParentID);
;	UINT		DoModal_SymmetryType(SPAWNTYPE& SpnType);	// in IGen.h
	//////////////////////////////////////////////////////////////

protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMMs0Mgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMMs0Mgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
