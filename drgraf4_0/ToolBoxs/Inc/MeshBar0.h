// Curve.h : interface of the CMeshBar0 class
//
#ifndef _MESHBAR0_H
#define _MESHBAR0_H                               


#include "palette.h"
////////////////////////////
class CMeshBar0 : public CPaletteBar
{
// Constructor
public:

	CMeshBar0();


	DECLARE_DYNAMIC(CMeshBar0);


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
	virtual ~CMeshBar0();
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
	int		m_nActiveNodeObject;    // other objects 
	int		m_nActiveNodeObjectOld;
	int		m_nCheck[200];
	


	// Generated message map functions
protected:

	//{{AFX_MSG(CMeshBar0)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point); 
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif


