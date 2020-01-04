// SDlgMgr.h : header file
//
#ifndef _SDLGMGR_H
#define _SDLGMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
/////////////////////////////////////////////////////////////////////////////
// CSDlgMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CSDlgMgr : public CObject
{
// Construction
public:  
	CSDlgMgr();
//#undef AFX_DATA
//#define AFX_DATA

	DECLARE_SERIAL(CSDlgMgr)

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

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


//#undef AFX_DATA
//#define AFX_DATA
//////////////////////////////////////
#endif
