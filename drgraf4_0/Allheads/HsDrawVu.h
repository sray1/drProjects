// 12View.h : interface of the CHsDrawVu class
//
#ifndef _HSDRAWVU_H 
#define _HSDRAWVU_H 


/////////////////////////////////////////////////////////////////////////////
#include "AxDrawVu.h"
/////////////////////
class CDrGrafCntrItem;

class CHsDrawVu : public CAxDrawVu
{
protected: // create from serialization only
	CHsDrawVu();
	DECLARE_DYNCREATE(CHsDrawVu)

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

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHsDrawVu)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

			UINT GetViewNumber(){return m_nView;}; 
	virtual void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL); 
	

public:
	virtual ~CHsDrawVu();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



// Generated message map functions
protected:
	//{{AFX_MSG(CHsDrawVu)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnCancelEditSrvr();
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
inline CDrGrafDoc* CHsDrawVu::GetDocument()
   { return (CDrGrafDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
#endif
