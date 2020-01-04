// colorsqu.h : header file
//
#ifndef _COLORSQU_H
#define _COLORSQU_H 

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////////////////////////////
// CSuperButton window 
class CSuperButton : public CButton
{
public:
CSuperButton(){};
	BOOL Create(CWnd* pOwnerWnd, CString strWndName,CRect rect,UINT nChildID);
~CSuperButton()
	{
		if(m_hWnd != NULL)	
		DestroyWindow();	
	};


	DECLARE_DYNCREATE(CSuperButton);


};

/////////////////////////////////////////////////////////////////////////////
// CCustomColor window 
class CCustomColor : public CWnd
{
// Construction
public:
	CCustomColor();

	CElemBar();


	DECLARE_DYNCREATE(CCustomColor);



// Attributes
public:

	CSuperButton		m_btnCustomFore;
	CSuperButton		m_btnCustomBack;

private:
   CString	m_strText;
// Operations
public:

// Implementation
public:
	virtual ~CCustomColor();

	
	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomColor)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonClickForeColor();
	afx_msg void OnButtonClickBackColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CColorSquare window



class CColorSquare : public CWnd
{
// Construction
public:
	CColorSquare();


	DECLARE_DYNCREATE(CColorSquare);



// Attributes
public:
	void 		SetColor(int index);
	COLORREF	GetColor() { return m_crColor;};
private:
   COLORREF m_crColor;
// Operations
public:

// Implementation
public:
	virtual ~CColorSquare();


	
	// Generated message map functions
protected:
	//{{AFX_MSG(CColorSquare)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#undef AFX_DATA
#define AFX_DATA

#endif
/////////////////////////////////////////////////////////////////////////////
