// drawbox.h : header file
//
#ifndef _DLG_UNIT_H_
#define _DLG_UNIT_H_  

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA



#include "sdlgrsrc.h"
/////////////////////////////////////////////////////////////////////////////
// CDrawUnit dialog
/////////////////////////////////////////////////////////////////////////////
class AFX_EXT_CLASS CDrawUnit : public CDialog
{
// Construction
public:
	CDrawUnit(CWnd* pParent = NULL);	// standard constructor
	void OnUnit();
protected: 
	CBitmapButton buttonOK,buttonCancel;
public:
// Dialog Data
	//{{AFX_DATA(CDrawUnit)
	enum { IDD = IDD_UNIT };
	CString	m_szDrawUnit;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
	// Generated message map functions
	//{{AFX_MSG(CDrawUnit)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif

