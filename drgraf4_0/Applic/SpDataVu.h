// dataview.h : header file		Spectral Data

#ifndef _SPDATAVIEW_H			
#define _SPDATAVIEW_H
//
#include "AxDataVu.h"
/////////////////////////////////////////////////////////////////////////////
// CSpDataVu view

class CSpDataVu : public CAxDataVu
{
	DECLARE_DYNCREATE(CSpDataVu)
protected:
	CSpDataVu();			// protected constructor used by dynamic creation

// Attributes
public:



// Operations
public:


// Implementation
protected:

	
	virtual ~CSpDataVu();
//	virtual	void OnDraw(CDC* pDC);		// overridden to draw this view
//	virtual	void OnInitialUpdate();		// first time after construct

	// Generated message map functions
	//{{AFX_MSG(CSpDataVu)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
