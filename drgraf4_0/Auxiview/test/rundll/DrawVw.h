#if !defined(AFX_DRAWVW_H__B72ECA65_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_DRAWVW_H__B72ECA65_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DrawVw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawVw view

class CDrawVw : public CView
{
protected:
	CDrawVw();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDrawVw)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawVw)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDrawVw();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL m_bDrag;
	CPoint m_OldPt,m_NewPt;

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawVw)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWVW_H__B72ECA65_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
