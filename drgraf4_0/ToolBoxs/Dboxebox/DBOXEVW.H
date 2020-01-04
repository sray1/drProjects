// dboxevw.h : interface of the CDBoxEBoxView class
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// toolboxes
#include "elembox.h"
#include "drawbox.h"          
///////////////////////////////////////////////

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
	////////////////////////////////////////////////
    CElemBox* 	GetElemBox(){return &m_wndElemBox;};
    CSize		GetSizeElemBox(){return m_szElemBox;};
    void		SetSizeElemBox(CSize szBox){m_szElemBox = szBox;};

    CDrawBox* 	GetDrawBox(){return &m_wndDrawBox;};
    CSize		GetSizeDrawBox(){return m_szDrawBox;};
    void		SetSizeDrawBox(CSize szBox){m_szDrawBox = szBox;};
    //////////////////////////////////////////////////////////////

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	/////////////////////////
	CElemBox	m_wndElemBox;
	CSize		m_szElemBox;

	CDrawBox	m_wndDrawBox;
	CSize		m_szDrawBox;
    /////////////////////////
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
