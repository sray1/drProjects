// EDl2Mgr.h : header file
//
#ifndef _MMS3MGR_H
#define _MMS3MGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Def_CuPS.h"
#include "DrSolid.h"
/////////////////////////////////////////////////////////////////////////////
// CMMs3Mgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMMs3Mgr : public CObject
{
// Construction
public:  
	CMMs3Mgr();
	DECLARE_SERIAL(CMMs3Mgr)
protected: 
public:
// Implementation 

public:

	////////////////////////////////////////////////////////////// Patch
//	UINT 	DoModal_Solid_Post(CString* pID);
	//////////////////////////////////////////////////////////////


protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMMs3Mgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMMs3Mgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
