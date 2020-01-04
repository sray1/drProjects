// dataview.h : header file

#ifndef _MSDATAVIEW_H
#define _MSDATAVIEW_H
//
#include "drgradoc.h"
#include "rowview.h"
#define CARD_LEN		80
#define	CARD_NO_COL		CARD_LEN + 5
#define	CARD_NO_LEN		7
#define ROW_WIDTH   (CARD_NO_COL + CARD_NO_LEN)
/////////////////////////////////////////////////////////////////////////////
// CMsDataVu view

class CMsDataVu : public CRowView
{
	DECLARE_DYNCREATE(CMsDataVu)
protected:
	CMsDataVu();			// protected constructor used by dynamic creation

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

	
	virtual ~CMsDataVu();
//	virtual	void OnDraw(CDC* pDC);		// overridden to draw this view
//	virtual	void OnInitialUpdate();		// first time after construct

	// Generated message map functions
	//{{AFX_MSG(CMsDataVu)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
