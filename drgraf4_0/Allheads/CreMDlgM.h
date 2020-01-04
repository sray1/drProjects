// EDl2Mgr.h : header file
//
#ifndef _CREMDLGM_H
#define _CREMDLGM_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrFE0D.h"
#include "DrMesh1D.h"
#include "DrMesh2D.h"
#include "DrMesh3D.h"
#include "DrMbj3D.h"
/////////////////////////////////////////////////////////////////////////////
// CCreMDlgM
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CCreMDlgM : public CObject
{
// Construction
public:  
	CCreMDlgM();
	DECLARE_SERIAL(CCreMDlgM)
protected: 
public:
// Implementation 

public:

//	UINT		DoModal_ShowNodeToEdit(CDrFE0D* pDrNode, int nViewNumber);
	UINT		DoModal_Spawn_N(CDrFE0D* pDrNode,CDrFE0D* pParentNode,CString* pID,CString* pParentID);
	///////////////////////////////////////////////////////////////
	UINT		DoModal_Spawn_C(CDrMesh1D* pNewCurve,CString* pID,CString* pParentID);
	CDrMesh1D*	SpawnCurve(CString& Cid,CString& ParentCid, CURVEPROC cp);
	//////////////////////////////////////////////////////////////
	UINT		DoModal_Spawn_P(CDrMesh2D* pNewPatch,CString* pID,CString& ParentCid);
	CDrMesh2D*	SpawnPatch(CString& Cid,CString& ParentCid, PATCHPROC cp);
	//////////////////////////////////////////////////////////////
	UINT		DoModal_Spawn_S(CDrMesh3D* pNewSolid,CString* pID,CString& ParentCid);
//	UINT 		DoModal_Solid_Post(CString* pID);
	CDrMesh3D*	SpawnSolid(CString& Cid,CString& ParentCid, SOLIDPROC cp);
	////////////////////////////////////////////////////////////// Patch
	UINT		DoModal_Spawn_O(CDrMbj3D* pNewObj3D,CString* pID,CString& ParentCid);
	CDrMbj3D*	SpawnObj3D(CString& Cid,CString& ParentCid);
	//////////////////////////////////////////////////////////////
	UINT		DoModal_SymmetryType(SPAWNTYPE& SpnType);	// in IGen.h
	UINT		DoModal_RotationType(SPAWNTYPE& SpnType);	// in IGen.h



protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CCreMDlgM();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CCreMDlgM)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
