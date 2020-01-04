// EDl2Mgr.h : header file
//
#ifndef _MMS1MGR_H
#define _MMS1MGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_Elem.h"
#include "DrFE0D.h"
#include "DrMesh1D.h"
/////////////////////////////////////////////////////////////////////////////
// CMMs1Mgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMMs1Mgr : public CObject
{
// Construction
public:  
	CMMs1Mgr();
	DECLARE_SERIAL(CMMs1Mgr)
protected: 
public:
// Implementation 

public:

	UINT		DoModal_ShowMesh1DToEdit(CDrMesh1D* pDrMesh1D);
	//////////////////////////////////////////////////////////////
//	UINT		DoModal_Profile_1(CString* pID,int nHowMany);
	UINT		DoModal_Merge_1_ShowInfo(CString* pID,CDListMgr* pMesh1DList);  	//Profile
//	UINT		DoModal_Spawn_1(CDrMesh1D* pNewMesh1D,CString* pID,CString* pParentID);
	///////////////////////////////////////////////////////////////
//	CDrMesh1D*	SpawnMesh1D(CString& Cid,CString& ParentCid, CURVEPROC cp);

protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMMs1Mgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMMs1Mgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
