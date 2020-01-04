// CDeckView.h : interface of the CScrollView class
//
#ifndef _CDECKVIEW 
#define _CDECKVIEW 

//#include <afxcview.h>		// :ListView
//#include <afxcmn.h>		// Common Controls
/////////////////////
#include "drgraf.h"
#include "drgradoc.h"
#include "DeckMgr.h"
/////////////////////////////////////////////////////////////////////////////

class CDeckView : public CScrollView
{
protected: // create from serialization only
	CDeckView();
	DECLARE_DYNCREATE(CDeckView)

// Attributes
public:
	CDrGrafDoc* GetDocument();

// Operations
public:


	///////////////////////////////////////////////////// Deck Manager
	CDeckMgr*		GetDeckMgr(){return &m_DeckMgr;};
	/////////////////////////////////////////////////
	UINT			GetViewNum(){return m_nView;};
	void			SetViewNum(UINT u){m_nView  = u;};



protected:

			void	GetCardWidthHeightCount(CDC* pDC, int& nCardWidth, int& nCardHeight,
													int& nCardCount);
			int		GetCardCount(){return m_nCardCount;};
	virtual void	CalculateCardMetrics(CDC* pDC)
						{ GetCardWidthHeightCount(pDC, m_nCardWidth, m_nCardHeight,m_nCardCount); }
	virtual void	UpdateScrollSizes();
	virtual int		LastViewableCard();

private:
    void			PrintPageHeader(CDC* pDC);
    void			PrintPageFooter(CDC* pDC);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeckView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDeckView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


	//////////////////////////////// DeckMgr
	CDeckMgr	m_DeckMgr;					
	CFont		m_Font;
	CFont*		m_pOldFont;
	LOGFONT		m_LF;
	UINT		m_nView;
	//////////////////////////////////////////////////////////////////////////////////
	int			m_nCardIndexBeg;			// Begin  CardIndex for CurrentPage Printing
	int			m_nCardIndexEnd;			// Ending CardIndex for CurrentPage Printing
	int			m_nCardCount;				// Deck Card Count	
	int			m_nCardWidth;				// width of Card in current device units
	int			m_nCardHeight;				// height of Card in current device untis
	int			m_nCardsPerPrintedPage;		// how many Cards fit on a printed page
	int			m_nLinesPerPrintedPage;		// how many Lines fit on a printed page
	int			m_nCurrentPage;
	int			m_nPageHeight;
	int			m_nPageWidth;
	////////////////////////
	int			m_nHeaderHeight;
	int			m_nHeaderBot;
	////////////////////////
	int			m_nFooterHeight;
	int			m_nFooterTop;


// Generated message map functions
protected:
	//{{AFX_MSG(CDeckView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDeckFormatFix();
	afx_msg void OnUpdateDeckFormatFix(CCmdUI* pCmdUI);
	afx_msg void OnDeckFormatFree();
	afx_msg void OnUpdateDeckFormatFree(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*
#ifndef _DEBUG  // debug version in samplvw.cpp
inline CSampleDoc* CDeckView::GetDocument()
   { return (CSampleDoc*)m_pDocument; }
#endif
*/
//////////////////////////////////////////////////////////////////
#endif
