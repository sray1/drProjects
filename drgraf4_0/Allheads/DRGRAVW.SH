// drgravw.h : interface of the CDrGrafView class
//
/////////////////////////////////////////////////////////////////////////////
#include "drgradoc.h"
/////////////////////
class CDrGrafView : public CScrollView
{
protected: // create from serialization only
	CDrGrafView();
	DECLARE_DYNCREATE(CDrGrafView)

// Attributes
public:
	CDrGrafDoc* GetDocument();

// Operations
public:

// Implementation
public: 
			void OnInitialUpdate();
	virtual ~CDrGrafView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Printing support
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CDrGrafView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in drgravw.cpp
inline CDrGrafDoc* CDrGrafView::GetDocument()
   { return (CDrGrafDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
