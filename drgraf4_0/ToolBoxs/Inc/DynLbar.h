// Elem.h : interface of the CDynLBar class
//
#ifndef _DYNLBAR_H
#define _DYNLBAR_H                               

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

#include "palette.h"
////////////////////////////
//class AFX_EXT_CLASS CDynLBar : public CPaletteBarN
class CDynLBar : public CPaletteBar
{
// Constructor
public:

	CDynLBar();


	DECLARE_DYNAMIC(CDynLBar);

	// overrides from paletteBar
//	virtual BOOL Create(CWnd* pOwnerWnd, int x, int y,UINT nChildID,UINT nIDCursor);
//	virtual void SetSizes(SIZE sizeButton, SIZE sizeImage,BOOL bCaption);
//	virtual	BOOL SetButtons(const UINT FAR* lpIDArray,int nIDCount,UINT nColumns);
//	virtual void RecalcLayout(UINT nButtonCount);

protected:

// Attributes
public:

// Operations
public:
	void PaintCustomBitmaps(CDC* pdc){ DoPaint(pdc);};
		
// Implementation
public:
	virtual ~CDynLBar();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	BOOL	m_bButtonDown;
	BOOL	m_bToolHit;	
	int		m_nButtCount;
	int		m_nActiveTool;          // edit and move
	int		m_nActiveToolOld;
	int		m_nActiveDynLObject;    // other objects 
	int		m_nActiveDynLObjectOld;
	int		m_nCheck[200];
	
	// Generated message map functions
protected:

	//{{AFX_MSG(CDynLBar)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////////////////////////////////////
#endif


