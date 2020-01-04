// EDl2Mgr.h : header file
//
#ifndef _APPDLGMGR_H
#define _APPDLGMGR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

 
/////////////////////////////////////////////////////////////////////////////
// CAppDlgMgr
/////////////////////////////////////////////////////////////////////////////
class CAppDlgMgr : public CObject
{
// Construction
public:  
	CAppDlgMgr();
	DECLARE_SERIAL(CAppDlgMgr)
protected: 
public:
// Implementation 

public:

	int			DebugList_AddString(CString& strList);
	///////////////////////////////////////////////////////////////



protected:

	HINSTANCE 	SetResource();
	void 		RestoreResource(HINSTANCE hInstResourceClient);

public:
	virtual ~CAppDlgMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(CAppDlgMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

//#undef AFX_DATA
//#define AFX_DATA
////////////////////////////////////////////////////////
#endif
