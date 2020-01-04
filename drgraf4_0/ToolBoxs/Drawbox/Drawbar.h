// Draw.h : interface of the CDrawBar class
//
#ifndef _DRAWBAR_H
#define _DRAWBAR_H                               

//#undef AFX_DATA
//#define AFX_DATA AFX_EXT_DATA

/////////////////////////////////////////////// 
#include "palette.h"
///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//class AFX_EXT_CLASS CDrawBar : public CPaletteBar
class CDrawBar : public CPaletteBar
{
// Constructor
public:
	CDrawBar();


	DECLARE_DYNCREATE(CDrawBar);

	// overrides from paletteBar
//	virtual BOOL Create(CWnd* pOwnerWnd, int x, int y,UINT nChildID);
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
	virtual ~CDrawBar();
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
	int		m_nActiveDrawObject;    // other objects 
	int		m_nActiveDrawObjectOld;
	int		m_nCheck[200];

	
	// Generated message map functions
protected:
//	void SwitchButton(UINT nButton);
	//{{AFX_MSG(CDrawBar)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//#undef AFX_DATA
//#define AFX_DATA

/////////////////////////////////////////////////////////////////////////////
#endif
/*	
	afx_msg void OnUpdate_Label_In(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Label_Edit(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Label_Move(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_FreeHand_In(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_FreeHand_Edit(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_FreeHand_Move(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_ZoomSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Dimension(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Font(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Grid(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Rect_Fill(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Rect_Hollow(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_RRect_Fill(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_RRect_Hollow(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Circle_Fill(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Circle_Hollow(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Line(CCmdUI* pCmdUI);
	afx_msg void OnUpdate_Brush(CCmdUI* pCmdUI);
*/	


