// menudraw.h : header file
//
#include "mainview.h"
/////////////////////////////////////////////////////////////////////////////
// CMenuDraw window

class CMenuDraw : public CMainView
{
// Construction
public:
	CMenuDraw();

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CMenuDraw();

protected:
	// Generated message map functions
	//{{AFX_MSG(CMenuDraw)
	afx_msg void OnDrawAxis();
	afx_msg void OnUpdateDrawAxis(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
