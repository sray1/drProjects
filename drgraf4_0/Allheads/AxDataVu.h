// dataview.h : header file		Spectral Data

#ifndef _AXDATAVIEW_H			
#define _AXDATAVIEW_H
//
#include "drgradoc.h"
#include "rowview.h"
#define CARD_LEN		80
#define	CARD_NO_COL		CARD_LEN + 5
#define	CARD_NO_LEN		7
#define ROW_WIDTH   (CARD_NO_COL + CARD_NO_LEN)
/////////////////////////////////////////////////////////////////////////////
// CAxDataVu view

class CAxDataVu : public CRowView
{
	DECLARE_DYNCREATE(CAxDataVu)
protected:
	CAxDataVu();			// protected constructor used by dynamic creation

// Attributes
public:

	CDrGrafDoc* GetDocument()
		{
			ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrGrafDoc)));
			return (CDrGrafDoc*) m_pDocument;
		}

// Overrides of CView
	void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);

// Overrides of CRowView
	void GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight);
	int	 GetActiveRow();
	int  GetRowCount();
	void OnDrawRow(CDC* pDC, int nRowNo, int y, BOOL bSelected);
	void ChangeSelectionNextRow(BOOL bNext);
	void ChangeSelectionToRow(int nRow);


// Operations
public:


// Implementation
protected:

	
	virtual ~CAxDataVu();
//	virtual	void OnDraw(CDC* pDC);		// overridden to draw this view
//	virtual	void OnInitialUpdate();		// first time after construct

	// Generated message map functions
	//{{AFX_MSG(CAxDataVu)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
