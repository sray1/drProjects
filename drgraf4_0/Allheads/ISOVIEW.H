
// Isoview.h : header file
//
#ifndef _CIsoVIEW 
#define _CIsoVIEW 

#include "mainview.h"

//#include "elmouse.h"
//#include "dbmouse.h"
/////////////////////////////////////////////////////////////////////////////
// CIsoView view
/////////////////////////////////// Forward References
class CDrGrafDoc;                                     
//////////////////////////////////////////////////////
class CIsoView : public CMainView
{
	DECLARE_DYNCREATE(CIsoView)
protected:
	CIsoView();			// protected constructor used by dynamic creation
    virtual void OnActivateView(BOOL bActivate,CView* pActive,
    											 CView* pDeActive);

// Attributes
public:

// Operations
public:

// Implementation
public:
			UINT GetViewNumber(){return m_nView;}; 
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    virtual	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual	void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual		 ~CIsoView();
// Attributes
public:
	CDrGrafDoc* GetDocument();
protected:
	///////////////////////////////////////// View  
	CPoint	m_ptOriginIso;
	int		m_nView;
	///////////////////////////////////////// axis
	int 	m_nTilt;       
	int		m_nRotation;
	///////////////////////////////////////// mouse
//	CELMouse	m_ELMouse;
//	CDBMouse	m_DBMouse;
	///////////////////////////////////////////
// Operations
public:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

#ifndef _DEBUG	// debug version in IsoView.cpp
inline CDrGrafDoc* CDrGrafView::GetDocument()
   { return (CDrGrafDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

	// Generated message map functions
protected:
	//{{AFX_MSG(CIsoView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
