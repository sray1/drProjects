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
// CDrSplitFrm frame with splitter/wiper

class AFX_EXT_CLASS CDrSplitFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CDrSplitFrm)
protected:
	CDrSplitFrm();   // protected constructor used by dynamic creation

// Attributes
protected:
	CSplitterWnd m_wndSplitter;

// Implementation
public:
	virtual ~CDrSplitFrm();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	// Generated message map functions
	//{{AFX_MSG(CDrSplitFrm)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// 

//class CDrSplitWnd : public CSplitterWnd
class AFX_EXT_CLASS CDrSplitWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CDrSplitWnd)

// Implementation
public:
	CDrSplitWnd();
	~CDrSplitWnd();
	CWnd* GetActivePane(int* pRow = NULL, int* pCol = NULL);
};


/////////////////////////////////////////////////////////////////////////////
