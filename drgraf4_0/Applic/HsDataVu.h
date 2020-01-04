// dataview.h : header file		Spectral Data

#ifndef _HSDATAVIEW_H			
#define _HSDATAVIEW_H
//
#include "AxDataVu.h"
/////////////////////////////////////////////////////////////////////////////
// CHsDataVu view

class CHsDataVu : public CAxDataVu
{
	DECLARE_DYNCREATE(CHsDataVu)
protected:
	CHsDataVu();			// protected constructor used by dynamic creation

// Attributes
public:



// Operations
public:


// Implementation
protected:

	
	virtual ~CHsDataVu();
//	virtual	void OnDraw(CDC* pDC);		// overridden to draw this view
//	virtual	void OnInitialUpdate();		// first time after construct

	// Generated message map functions
	//{{AFX_MSG(CHsDataVu)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
