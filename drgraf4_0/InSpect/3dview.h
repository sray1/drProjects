// 3DView.h : interface of the C3DView class
//
#ifndef _C3DVIEW 
#define _C3DVIEW 


/////////////////////////////////////////////////////////////////////////////
#include "drawview.h"
/////////////////////
class CDrGrafCntrItem;

class C3DView : public CDrawView
{
protected: // create from serialization only
	C3DView();
	DECLARE_DYNCREATE(C3DView)

// Attributes
public:
	CDrGrafDoc* GetDocument();
	// m_pSelection holds the selection to the current CDrGrafCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CDrGrafCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CDrGrafCntrItem* m_pSelection;

// Operations  // overrides of DrawView
public:
	int 	GetActiveObjectIndex();
	int 	GetObjectCount();
	void 	ChangeSelectionNextObjectIndex(BOOL bNext);
	void 	ChangeSelectionToObjectIndex(int nObjectIndex);  
	
	void 	OnDrawObject(CDC* pDC, int nObjIndex,int nObjectType, BOOL bSelected);


// Implementation
public:
public:

			UINT GetViewNumber(){return m_nView;}; 
	virtual void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL); 
	
	virtual ~C3DView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	virtual void OnInitialUpdate(); // called first time after construct

	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// OLE Container support
	virtual BOOL IsSelected(const CObject* pDocItem) const;


protected:



// Generated message map functions
protected:
	//{{AFX_MSG(C3DView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in drgravw.cpp
inline CDrGrafDoc* C3DView::GetDocument()
   { return (CDrGrafDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
#endif
