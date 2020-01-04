#ifndef _SPLITTER_H
#define _SPLITTER_H


class C3WaySplitterFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(C3WaySplitterFrame)
protected:
	C3WaySplitterFrame();   // protected constructor used by dynamic creation

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
	CSplitterWnd m_wndSplitter2;        // embedded in the first

// Implementation
public:
	virtual ~C3WaySplitterFrame();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	// Generated message map functions
	//{{AFX_MSG(C3WaySplitterFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif	// _SPLITTER_H



