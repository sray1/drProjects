// AxisDraw.h : header file
//
#ifndef _AXISDRAW_H
#define _AXISDRAW_H

#undef AFX_DATA
#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////////////////////////////////////
// CAxisDraw dialog

class CAxisDraw : public CWnd
{
// Construction
public:
//	CAxisDraw(CView* pView);	// message filtered to View
	CAxisDraw();	// message filtered to View

    CView*	m_pView;

protected: 

	void 	DrawSampleAxes(CDC* PtrDC);
	POINT 	GetCenter(CRect* Rect);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAxisDraw)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#undef AFX_DATA
#define AFX_DATA
//////////////////////////////////////
#endif
