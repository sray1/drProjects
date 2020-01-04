// drgracfm.h : header file
//
#ifndef _GRAFCHILD
#define _GRAFCHILD

/////////////////////////////////////////////////////////////////////////////
// CDrGrafChildFrame frame

class CDrGrafChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CDrGrafChildFrame)
protected:
	CDrGrafChildFrame();			// protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
// Implementation 
public:
	static void Initialize();
	static void Terminate(); 
protected:
	static CMenu FAR menu;     // menu for all ChildFrame windows

	virtual ~CDrGrafChildFrame(); 
	void	ActivateFrame(int nCmdShow);
public:
	
// We override CMDIChildWnd to customize the MDI child's title bar.
// By default the title bar shows the document name.  But we want
// it to instead show the text defined as the first string in
// the document template STRINGTABLE resource.  This string is
// "12" in the case of the MDI child window that embeds
// the view, and similarly for the other MDI child windows.  If
// we didn't customize the title bar, the two MDI child windows would
// show MYGraf:1 and MYGraf:2 if the document were named MYGraf. 

virtual	BOOL PreCreateWindow(CREATESTRUCT& cs); 
    
static	int m_nDefCmdShow;
static	int m_nDefCmdShowOld;
    

	// Generated message map functions
	//{{AFX_MSG(CDrGrafChildFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg	LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
	afx_msg void OnContextHelp();
	afx_msg void OnUpdateContextHelp(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
/////////////////////////////////////////////////////////////////////////////
