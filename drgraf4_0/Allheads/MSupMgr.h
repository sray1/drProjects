// EDl2Mgr.h : header file
//
#ifndef _MSUPMGR_H
#define _MSUPMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_Supp.h"
/////////////////////////////////////////////////////////////////////////////
// CMSupMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMSupMgr : public CObject
{
// Construction
public:  
	CMSupMgr();
	DECLARE_SERIAL(CMSupMgr)
protected: 
public:
// Implementation 

public:

	////////////////////////////////////////////////////////////// Support
	UINT	DoModal_Sup_JCType(JOINTCOORD& jcType);
	UINT	DoModal_SupToEdit(CDrLinSup* pSup);


protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMSupMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMSupMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
