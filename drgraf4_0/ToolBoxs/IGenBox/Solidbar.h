// Solid.h : interface of the CSolidBar class
//
#ifndef _SOLIDBAR_H
#define _SOLIDBAR_H                               


#include "palette.h"
////////////////////////////
class CSolidBar : public CPaletteBar
{
// Constructor
public:

	CSolidBar();
	DECLARE_DYNAMIC(CSolidBar);


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
	virtual ~CSolidBar();
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
	int		m_nActiveSolidObject;    // other objects 
	int		m_nActiveSolidObjectOld;
	int		m_nCheck[200];

	
	// Generated message map functions
protected:

	//{{AFX_MSG(CSolidBar)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif


