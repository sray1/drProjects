
// 12view.h : header file
//
#ifndef _C12VIEW 
#define _C12VIEW 


#include "drawview.h"
/////////////////////////////////////////////////////////////////////////////
// C12View view
/////////////////////////////////// Forward References
class CDrGrafDoc;                                     
//////////////////////////////////////////////////////
class C12View : public CDrawView
{
	DECLARE_DYNCREATE(C12View)
protected:
	C12View();			// protected constructor used by dynamic creation
    virtual void OnActivateView(BOOL bActivate,CView* pActive,
    											 CView* pDeActive);
// Attributes
public:

// Operations  // overrides of DrawView
public:
	int 	GetActiveObjectIndex();
	int 	GetObjectCount();
	void 	ChangeSelectionNextObjectIndex(BOOL bNext);
	void 	ChangeSelectionToObjectIndex(int nObjectIndex);  
	
	void 	OnDrawObject(CDC* pDC, int nObjIndex,int nObjectType, BOOL bSelected);

// Implementation
public:

	virtual void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
	virtual		 ~C12View();

// Attributes
public:
	CDrGrafDoc* GetDocument();
protected:

	///////////////////////////////////////// axis
	int 	m_nTilt;       
	int		m_nRotation;

// Operations
public:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

#ifndef _DEBUG	// debug version in 12View.cpp
inline CDrGrafDoc* C12View::GetDocument()
   { return (CDrGrafDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

	// Generated message map functions
protected:
	//{{AFX_MSG(C12View)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
