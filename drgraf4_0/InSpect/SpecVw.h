// inputvw.h : header file
//
#ifndef _CSPECVIEW 
#define _CSPECVIEW 


/////////////////////////////////////////////////////////////////////////////
// CSpecView form view

class CSpecView : public CView
{
	DECLARE_DYNCREATE(CSpecView)
protected:
	CSpecView();           // protected constructor used by dynamic creation


// Attributes
public:
	CDrGrafDoc* GetDocument();
public:

// Implementation
protected:
	virtual ~CSpecView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	// Generated message map functions
	//{{AFX_MSG(CSpecView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in drgravw.cpp
inline CDrGrafDoc* CSpecView::GetDocument()
   { return (CDrGrafDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
#endif
