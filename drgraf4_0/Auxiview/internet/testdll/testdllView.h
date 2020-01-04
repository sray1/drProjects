// testdllView.h : interface of the CTestdllView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTDLLVIEW_H__A9539D19_6284_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_TESTDLLVIEW_H__A9539D19_6284_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTestdllView : public CView
{
protected: // create from serialization only
	CTestdllView();
	DECLARE_DYNCREATE(CTestdllView)

// Attributes
public:
	CTestdllDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestdllView)
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
	virtual ~CTestdllView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestdllView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in testdllView.cpp
inline CTestdllDoc* CTestdllView::GetDocument()
   { return (CTestdllDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLLVIEW_H__A9539D19_6284_11D2_8A0E_00A0CC30503B__INCLUDED_)
