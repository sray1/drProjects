// QuadtaBar.h : interface of the CQuadBar class
//
#ifndef _QUADBAR_H
#define _QUADBAR_H                               


#include "palette.h"
////////////////////////////
class CQuadBar : public CPaletteBar
{
// Constructor
public:

	CQuadBar();


	DECLARE_DYNAMIC(CQuadBar);


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

// Implementation
public:
	virtual ~CQuadBar();
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
	int		m_nActiveCurveObject;    // other objects 
	int		m_nActiveCurveObjectOld;
	int		m_nCheck[200];
	


	// Generated message map functions
protected:

	//{{AFX_MSG(CQuadBar)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif


