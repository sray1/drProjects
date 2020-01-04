// dboxevw.h : interface of the CDBoxEBoxView class
//
/////////////////////////////////////////////////////////////////////////////

class CDBoxEBoxView : public CView
{
protected: // create from serialization only
	CDBoxEBoxView();
	DECLARE_DYNCREATE(CDBoxEBoxView)

// Attributes
public:
	CDBoxEBoxDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CDBoxEBoxView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDBoxEBoxView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in dboxevw.cpp
inline CDBoxEBoxDoc* CDBoxEBoxView::GetDocument()
   { return (CDBoxEBoxDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
