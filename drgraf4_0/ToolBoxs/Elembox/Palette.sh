// palette.h : interface of the CPaletteBar class
//
#ifndef _PALETTEBAR_H
#define _PALETTEBAR_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#ifndef __AFXEXT_H__
#include <afxext.h>         // for access to CToolBar
#endif


//#include "toolbar.h"         // for access to COldToolBar
//////////////////////
//16 class CPaletteBar : public CToolBar
//class AFX_EXT_CLASS CPaletteBar : public CToolBar
class CPaletteBar : public CToolBar
{
// Constructor
public:

	CPaletteBar();


	DECLARE_DYNAMIC(CPaletteBar);

/*
	// overridables
	virtual BOOL Create(CWnd* pOwnerWnd, int x, int y,UINT nChildID,UINT nIDCursor);
	virtual void SetSizes(SIZE sizeButton, SIZE sizeImage,BOOL bCaption);
	virtual	BOOL SetButtons(const UINT *lpIDArray,int nIDCount,UINT nColumns);
	virtual void RecalcLayout(UINT nButtonCount);
*/
	
// Attributes
public:

// Operations
public:
	void SetColumns(UINT nColumns);
	UINT GetColumns() { return m_nColumns; };
	virtual int 	HitTest(CPoint point);

protected:
	UINT    m_nColumns;

// Implementation
public:
	virtual ~CPaletteBar();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
/*
	// overridden from CToolBar implementation
	virtual void 	GetItemRect(int nIndex, LPRECT lpRect) const;

protected:
	void InvalidateButton(int nIndex);
	void UpdateButton(int nIndex);
	void CreateMask(int iImage, CPoint offset, 
		BOOL bHilite, BOOL bHiliteShadow);

	// for custom drawing
	struct DrawState
	{
		HBITMAP hbmMono;
		HBITMAP hbmMonoOld;
		HBITMAP hbmOldGlyphs;
	};
	BOOL PrepareDrawButton(DrawState& ds);
	BOOL DrawButton(CDC* pDC, int x, int y, int iImage, UINT nStyle);
	void EndDrawButton(DrawState& ds);
	// overridden from CToolBar implementation
	virtual void 	DoPaint(CDC* pDC);
			void	InvertTracker(CPoint point);

protected:
	BOOL    m_bTrackMove;
	CPoint  m_ptMouse, m_ptLast;
	UINT    m_nColumns;
	CWnd*   m_pOwnerWnd;
	UINT    m_cxRightBorder;
	UINT	m_cyCaption;


protected:

*/
	// Generated message map functions
protected:
	//{{AFX_MSG(CPaletteBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
/*
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
*/

};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////////////////////////////////////
#endif
