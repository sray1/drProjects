// mainview.h : header file
//
#ifndef _CMAINVIEW 
#define _CMAINVIEW
                 
#include "globals.h"
/////////////////////////////////////////////////////////////////////////////
// CMainView view

class CMainView : public CScrollView
{
	DECLARE_DYNCREATE(CMainView)
protected:
	CMainView();			// protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
// Implementation
			void PrepareDC(CDC* pDC);
			void PreparePrintDC(CDC* pDC, CPrintInfo* pInfo);

protected:
	virtual ~CMainView();
	virtual	BOOL PreCreateWindow(CREATESTRUCT& cs);
//    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	/////////////////////////////////////////////////////////////// Drawing support
	void 	TransformPoint3to2(double* Coord,double Tran[][3],
								double* dTranCoord);
	void 	GetWinOrigin(long* pWinH,long* pWinV,int nViewNumber);
//	long 	GetWinOrigin(LPOINT3 WIC,int nViewNumber
//								,int index);
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void 	DrawAll(CDC* pDC,int nViewNumber);
	/////////////////////////////////////////////////////////////// Printing support
			void GetDrawingCenter(LPOINT* pCenter);
			void PrintSignOn(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	void 	PrintAll(CDC* pDC, CPrintInfo* pInfo,int nViewNumber);
	void 	PrintTitlePage(CDC* pDC, CPrintInfo* pInfo);
	void 	PrintPageHeader(CDC* pDC, CPrintInfo* pInfo); 
	///////////////////////////////////////////////////// DocumentSize
	CSize 	GetDocSize(LPOINT3 WinExtWIC,int nViewNumber);  
	///////////////////////////////////////////////////// Zoom		
	int 	GetCurrentViewNumber();
	void 	ZoomtoFitFactor();

	
	// Generated message map functions
protected:
	//{{AFX_MSG(CMainView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnZoomFit();
	afx_msg void OnUpdateZoomFit(CCmdUI* pCmdUI);
	afx_msg void OnZoom();
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawAxis();
	afx_msg void OnUpdateDrawAxis(CCmdUI* pCmdUI);
	afx_msg void OnDrawEyeposition();
	afx_msg void OnUpdateDrawEyeposition(CCmdUI* pCmdUI);
	afx_msg void OnDrawUnits();
	afx_msg void OnUpdateDrawUnits(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
public:   

//	CMenuDraw			DrawMenuHandler;  
	////////////////////////////////////

protected:	
	CString	m_ClassName;
	int		m_nViewNumber;
	RECT	m_ViewRect;	
	int		m_nClientWidth;
	int 	m_nClientHeight;
	int		m_nTilt;
	int		m_nRotation;
	CPoint	m_ptAxisOrigin;
	CPoint	m_ptOrigin; 
	int 	m_nAxisLength;
	CPoint	m_ptScreenWinOrg;
	CPoint	m_ptPrintOffset;
	BOOL	m_bFromPrint;
	/////////////////////////////////////////// Document Size
	CSize	m_sizeDoc;
	CView*	m_pView;
	//////////////////////////////// Printing
	int		m_nBottomUsed;
	int		m_nTopUsed;
    int		m_nLeftBorder;   
    int		m_nTopBorder;    
    int		m_nRightBorder;
    int		m_nBottomBorder;
	////////////////////////////////
};
#endif
/////////////////////////////////////////////////////////////////////////////
