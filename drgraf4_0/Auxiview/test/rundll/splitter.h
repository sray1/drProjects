#ifndef _SPLITTER_H
#define _SPLITTER_H

// splitter.h : custom splitter control and frame that contains it
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////
// CSplitterFrame frame with splitter/wipe

class CSplitterFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CSplitterFrame)
protected:
	CSplitterFrame();   // protected constructor used by dynamic creation

// Attributes
protected:
	CSplitterWnd m_wndSplitter;

// Implementation
public:
	virtual ~CSplitterFrame();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	// Generated message map functions
	//{{AFX_MSG(CSplitterFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// 

//	CWnd* GetActivePane(int* pRow = NULL, int* pCol = NULL);




#endif

