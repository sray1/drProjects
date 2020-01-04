// palette.h : interface of the CPaletteBarN class
//
#ifndef _PALETTEN_H
#define _PALETTEN_H

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA


#ifndef __AFXEXT_H__
#include <afxext.h>         // for access to CToolBar
#endif


//#include "Oldtool.h"         // for access to COldToolBar
//////////////////////
//16 class CPaletteBarN : public CToolBar
//class AFX_EXT_CLASS CPaletteBarN : public CToolBar
class CPaletteBarN : public CToolBar
{
// Constructor
public:

	CPaletteBarN();


	DECLARE_DYNAMIC(CPaletteBarN);

/*
	// overridables
	virtual BOOL Create(CWnd* pOwnerWnd, int x, int y,UINT nChildID,UINT nIDCursor);
	virtual void SetSizes(SIZE sizeButton, SIZE sizeImage,BOOL bCaption);
	virtual	BOOL SetButtons(const UINT *lpIDArray,int nIDCount,UINT nColumns);
*/
	virtual void RecalcLayout(UINT nButtonCount);
	
// Attributes
public:

// Operations
public:
	void SetColumns(UINT nColumns);
	UINT GetColumns() { return m_nColumns; };
	virtual int 	HitTest(CPoint point);


// Implementation
public:
	virtual ~CPaletteBarN();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

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



	// Generated message map functions
protected:
	//{{AFX_MSG(CPaletteBarN)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
/*
*/

};

//#undef AFX_DATA
//#define AFX_DATA
/////////////////////////////////////////////////////////////////////////////
#endif
