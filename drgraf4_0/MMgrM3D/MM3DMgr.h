// EDl2Mgr.h : header file
//
#ifndef _MO3DMGR_H
#define _MO3DMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrObj3D.h"
/////////////////////////////////////////////////////////////////////////////
// CMO3DMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMO3DMgr : public CObject
{
// Construction
public:  
	CMO3DMgr();
	DECLARE_SERIAL(CMO3DMgr)
protected: 
public:
// Implementation 

public:

	////////////////////////////////////////////////////////////// Patch
	UINT	DoModal_Spawn_O(CDrObj3D* pNewObj3D,CString* pID,CString& ParentCid);
	//////////////////////////////////////////////////////////////
	CDrObj3D*	SpawnObj3D(CString& Cid,CString& ParentCid);


protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMO3DMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMO3DMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
