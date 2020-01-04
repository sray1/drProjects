// EDl2Mgr.h : header file
//
#ifndef _MMS2MGR_H
#define _MMs2MGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
//#include "Def_CuPS.h"
#include "DrMesh2D.h"
/////////////////////////////////////////////////////////////////////////////
// CMMs2Mgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMMs2Mgr : public CObject
{
// Construction
public:  
	CMMs2Mgr();
	DECLARE_SERIAL(CMMs2Mgr)
protected: 
public:
// Implementation 

public:

	int		ShowMesh2DToEdit(CDrMesh2D* pDrMesh2D);
	////////////////////////////////////////////////////////////// Mesh2D
	UINT	DoModal_Merge_2_ShowInfo(CString* pID,CDListMgr* pMesh2DList);  	//Profile
//082898	UINT	DoModal_Spawn_2(CDrMesh2D* pNewMesh2D,CString* pID,CString& ParentCid);
//	UINT 	DoModal_Mesh2D_Post(CString* pID);
	//////////////////////////////////////////////////////////////
//082898	CDrMesh2D*	SpawnMesh2D(CString& Cid,CString& ParentCid);


protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMMs2Mgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMMs2Mgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
