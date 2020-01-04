// EDl2Mgr.h : header file
//
#ifndef _CREODLGM_H
#define _CREODLGM_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrNode.h"
#include "DrCurve.h"
#include "DrPatch.h"
#include "DrSolid.h"
#include "DrObj3D.h"
/////////////////////////////////////////////////////////////////////////////
// CCreODlgM
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CCreODlgM : public CObject
{
// Construction
public:  
	CCreODlgM();
	DECLARE_SERIAL(CCreODlgM)
protected: 
public:
// Implementation 

public:

//	UINT		DoModal_ShowNodeToEdit(CDrNode* pDrNode, int nViewNumber);
	UINT		DoModal_Spawn_N(CDrNode* pDrNode,CDrNode* pParentNode,CString* pID,CString* pParentID);
	///////////////////////////////////////////////////////////////
	UINT		DoModal_Spawn_C(CDrCurve* pNewCurve,CString* pID,CString* pParentID);
	CDrCurve*	SpawnCurve(CString& Cid,CString& ParentCid, CURVEPROC cp);
	//////////////////////////////////////////////////////////////
	UINT		DoModal_Spawn_P(CDrPatch* pNewPatch,CString* pID,CString& ParentCid);
	CDrPatch*	SpawnPatch(CString& Cid,CString& ParentCid, PATCHPROC cp);
	//////////////////////////////////////////////////////////////
	UINT		DoModal_Spawn_S(CDrSolid* pNewSolid,CString* pID,CString& ParentCid);
//	UINT 		DoModal_Solid_Post(CString* pID);
	CDrSolid*	SpawnSolid(CString& Cid,CString& ParentCid, SOLIDPROC cp);
	////////////////////////////////////////////////////////////// Patch
	UINT		DoModal_Spawn_O(CDrObj3D* pNewObj3D,CString* pID,CString& ParentCid);
	CDrObj3D*	SpawnObj3D(CString& Cid,CString& ParentCid);
	//////////////////////////////////////////////////////////////
	UINT		DoModal_SymmetryType(SPAWNTYPE& SpnType);	// in IGen.h
	UINT		DoModal_RotationType(SPAWNTYPE& SpnType);	// in IGen.h



protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CCreODlgM();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CCreODlgM)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
