// 3DlgMgr.h : header file
//
#ifndef _3DLGMGR_H
#define _3DLGMGR_H 

/////////////////////////////////////////////////////////////////////////////
// C3DlgMgr
/////////////////////////////////////////////////////////////////////////////
class C3DlgMgr : public CObject
{
// Construction
public:  
	C3DlgMgr();
	DECLARE_SERIAL(C3DlgMgr)
protected: 
public:
// Implementation 

public:

	////////////////////////////////////////////////////////////////////// 
	UINT 	DoModal_EyePosition();
	///////////////////////							

public:
	virtual ~C3DlgMgr();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
/*
	// Generated message map functions
	//{{AFX_MSG(C3DlgMgr)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
*/
};

#endif
