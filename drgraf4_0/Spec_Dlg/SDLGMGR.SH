// SDlgMgr.h : header file
//
#ifndef _SDLGMGR_H
#define _SDLGMGR_H
 
//#include "globals.h"
/////////////////////////////////////////////////////////////////////////////
// CSDlgMgr
/////////////////////////////////////////////////////////////////////////////
class CSDlgMgr : public CObject
{
// Construction
public:  
	CSDlgMgr();
	DECLARE_SERIAL(CSDlgMgr)
protected: 
public:
// Implementation 

public:

	////////////////////////////////////////////////////////////////////// 
	UINT DoModal_SpecObjs(UINT nObjType);
	///////////////////////							

public:
	virtual ~CSDlgMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CSDlgMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#endif
