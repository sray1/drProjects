// rundllView.h : interface of the CRundllView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RUNDLLVIEW_H__B72ECA3C_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
#define AFX_RUNDLLVIEW_H__B72ECA3C_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRundllView : public CView
{
protected: // create from serialization only
	CRundllView();
	DECLARE_DYNCREATE(CRundllView)

// Attributes
public:
	CRundllDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRundllView)
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
	virtual ~CRundllView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRundllView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in rundllView.cpp
inline CRundllDoc* CRundllView::GetDocument()
   { return (CRundllDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUNDLLVIEW_H__B72ECA3C_51F5_11D2_8A0E_00A0CC30503B__INCLUDED_)
