// Drawbox.h : header file
// 
#ifndef _DRAWBOX_H
#define _DRAWBOX_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#include "dboxButt.h"
#include "drawbar.h"   //access to CDrawBar

#include "colorsqu.h"
/////////////////////////////////////////////////////////////////////////////
// CDrawBox window

//class AFX_EXT_CLASS CDrawBox : public CWnd
class CDrawBox : public CWnd
{
// Construction
public:
	/////////////////////////////////////////////////////////////////// DLLs public
	CDrawBox();
	virtual ~CDrawBox(); 


	DECLARE_DYNCREATE(CDrawBox);



    UINT			GetWidth();
    UINT			GetHeight();
	int  			GetActiveTool();
	int  			GetActiveDrawObject();
	COLORREF		GetForeColor();
	COLORREF 		GetBackColor();
    /////////////////////////////////////////////////////////// Children,Popup etc
//	BOOL 			Create(CMDIFrameWnd* pParentWnd,CRect rect);
	BOOL 			Create(CWnd* pParentWnd,CRect rect);
	CDrawBar*		GetDrawBar(){return &m_wndDrawBar;};
	CColorSquare*	GetColorSquare(int nrow,int ncol)
						{return &m_wndColorSquare[nrow][ncol];};
	CCustomColor*	GetCustomColor(){return &m_wndCustomColor;};
	/////////////////////////////////////////////////////////// Task					
	void 			GoRespondtoMouse();
	///////////////////////////////////////////////////////////
	int 			GetToolNum(int index);
	void 			FillToolNumArray();
	BOOL 			IsDrawTool(UINT nID);
	BOOL 			IsEditMoveTool(UINT nID);
	BOOL 			IsDrawObject(UINT nID);
    ///////////////////////////////////////////////////////////////////
	void 			SetActiveTool(int nTool){m_nActiveTool = nTool;};
	void 			SetActiveDrawObject(int nObject){m_nActiveDrawObject = nObject;};
	void 			SetForeColor(COLORREF crColor){m_crForeColor = crColor;}; 
	void 			SetBackColor(COLORREF crColor){m_crBackColor = crColor;}; 
    void			SetWidth(UINT nWidth){m_nWidth = nWidth;};
    void			SetHeight(UINT nHeight){m_nHeight = nHeight;};
	int				GetDrawBarButtCount(){return m_nDrawBarButtCount;};
    ///////////////////////////////////////////////////////////
 	UINT			GetColorSquareColMax(){return m_nColorSquareColMax;};
 	UINT  			GetColorSquareRowMax(){return m_nColorSquareRowMax;};
	///////////////////////////////////////////////////////////								    					  
    void 			SetSqTop(UINT nChildSqTop){m_nChildSqTop= nChildSqTop;};
    UINT  			GetSqTop() { return m_nChildSqTop;} 
// Operations
public:

// Implementation

protected:
    
	///////////////////////////////////////////////////////// children
  	CDrawBar		m_wndDrawBar; 
    CColorSquare 	m_wndColorSquare[DB_MAX_SQ_ROW][DB_MAX_SQ_COL];
    CCustomColor	m_wndCustomColor;
    /////////////////////////////////// helper
	BOOL 			CreateDrawBar();
	BOOL 			CreateColorSquares();
	BOOL 			CreateZoomScreen();
	///////////////////////////////////
    void 			Draw_Fore_Back_Rect();
    void 			Draw_Bottom_Box();
  	
protected:
	
    UINT    	m_nDrawBarColMax;
    UINT		m_nDrawBarRowMax;
	int 		m_nActiveTool;         // tool(edit or move)
	int			m_nActiveDrawObject;   // other objects
	int			m_nDrawBarButtCount;
	int			m_nToolNumArray[100];
    /////////////////////////////////
    UINT		m_nColorSquareColMax;
    UINT		m_nColorSquareRowMax;
    UINT		m_nSquareTop;
	UINT 		m_nChildSqTop;
    COLORREF	m_crForeColor;
    COLORREF	m_crBackColor;
    /////////////////////////
    UINT		m_nWidth;
    UINT		m_nHeight;
    //////////////////////

	
	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint(); 
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#undef AFX_DATA
//#define AFX_DATA
#endif
/////////////////////////////////////////////////////////////////////////////
