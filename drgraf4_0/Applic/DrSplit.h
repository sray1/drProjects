// splitter.h : custom splitter control and frame that contains it
//
//
#ifndef _DRSPLIT_H_
#define _DRSPLIT_H_       


/////////////////////////////////////////////////////////////////////////////
// CDrSplitFrm frame with splitter/wiper

class CDrSplitFrm : public CMDIChildWnd
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
class CDrSplitWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CDrSplitWnd)

// Implementation
public:
	CDrSplitWnd();
	~CDrSplitWnd();
	CWnd* GetActivePane(int* pRow = NULL, int* pCol = NULL);
};


/////////////////////////////////////////////////////////////////////////////
#endif
