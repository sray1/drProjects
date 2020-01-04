
#ifndef _DRTREEVU_H
#define _DRTREEVU_H


#include <afxcview.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// DrTreeVu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrTreeVu view

class AFX_EXT_CLASS CDrTreeVu : public CTreeView
{
protected:
	CDrTreeVu();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDrTreeVu)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrTreeVu)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	int Init();
	CImageList* GetImageList(){return m_pImageList;}; 
	
protected:
	virtual ~CDrTreeVu();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:

	CImageList*	m_pImageList;
	BOOL		m_bViewChanged;

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrTreeVu)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif 
