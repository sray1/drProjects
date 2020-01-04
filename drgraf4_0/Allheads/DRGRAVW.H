// drgravw.h : interface of the CDrGrafView class
//
/////////////////////////////////////////////////////////////////////////////

class CDrgrafCntrItem;

class CDrGrafView : public CScrollView
{
protected: // create from serialization only
	CDrGrafView();
	DECLARE_DYNCREATE(CDrGrafView)

// Attributes
public:
	CDrGrafDoc* GetDocument();
	// m_pSelection holds the selection to the current CDrgrafCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CDrgrafCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CDrgrafCntrItem* m_pSelection;

// Operations
public:

// Implementation
public:
	virtual ~CDrGrafView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate(); // called first time after construct

	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// OLE Container support
	virtual BOOL IsSelected(const CObject* pDocItem) const;

// Generated message map functions
protected:
	//{{AFX_MSG(CDrGrafView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEdit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in drgravw.cpp
inline CDrGrafDoc* CDrGrafView::GetDocument()
   { return (CDrGrafDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
