// EDl2Mgr.h : header file
//
#ifndef _MSTLMGR_H
#define _MSTLMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
#include "Def_Type.h"
#include "Str_StaL.h"
/////////////////////////////////////////////////////////////////////////////
// CMStLMgr
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CMStLMgr : public CObject
{
// Construction
public:  
	CMStLMgr();
	DECLARE_SERIAL(CMStLMgr)
protected: 
public:
// Implementation 

public:
// Implementation 

public:

	////////////////////////////////////////////////////////////// Value 
	UINT	DoModal_Value_In(CString& heading,pDOUBLE pValue,int nCompo,STALPROC StaLProc);
	UINT	DoModal_ManyValue_In(CString& Nid, pDOUBLE dValu,BOOL* bKode,STALPROC StaLProc);


protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CMStLMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CMStLMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
