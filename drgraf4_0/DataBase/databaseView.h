// databaseView.h : interface of the CDatabaseView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASEVIEW_H__FF628E52_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_DATABASEVIEW_H__FF628E52_5915_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDatabaseView : public CView
{
protected: // create from serialization only
	CDatabaseView();
	DECLARE_DYNCREATE(CDatabaseView)

// Attributes
public:
	CDatabaseDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDatabaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDatabaseView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in databaseView.cpp
inline CDatabaseDoc* CDatabaseView::GetDocument()
   { return (CDatabaseDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASEVIEW_H__FF628E52_5915_11D2_8A0E_00A0CC30503B__INCLUDED_)
