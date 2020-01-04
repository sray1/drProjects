// drgrafrm.h : interface of the CDrGrafFrame class
//
#include "elembox.h"
#include "drawbox.h"
#include "drstatus.h"
#include "globals.h"
///////////////////// 
#include "spdefine.h"   // for initialization of the specials
#include "MapFacto.h"
#include "Precison.h"
#include "ScaleFac.h"
#include "Unit.h"
/////////////////////////////////////////////////////////////////////////////

class CDrGrafFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CDrGrafFrame)
public:
	CDrGrafFrame();

// Attributes
public:

// Operations
public:  

	OPMODE			GetOpMode(){return m_OpMode;};
	void			SetOpMode(OPMODE om){m_OpMode = om;};
	////////////////////////////////////////////////////////////// Menu
	void 			SwitchMenu( UINT nMenuNum);
	CMenu*			GetInitMenu(){return &m_InitMenu;};
	CMenu*			GetInputMenu(){return &m_InputMenu;};
	CMenu*			GetOutputMenu(){return &m_OutputMenu;};
	////////////////////////////////////////////////////////////// Window Placement												
	void			InitialShowWindow(UINT nCmdShow);
	////////////////////////////////////////////////////////////// Create/Close Frame/View		
	void 			CreateOrActivateFrame(CDocTemplate* pTemplate,CRuntimeClass* pViewClass);
	void 			CloseView(CRuntimeClass* pViewClass);
	int				GetActiveViewNumber(){ return m_nActiveViewNumber;};
	void			SetActiveViewNumber(int VwNum){ m_nActiveViewNumber = VwNum;};
	////////////////////////////////////////////////////////////// ToolBoxes
    CElemBox* 		GetElemBox(){return &m_wndElemBox;};
    CSize			GetSizeElemBox(){return m_szElemBox;};
    void			SetSizeElemBox(CSize szBox){m_szElemBox = szBox;};

    CDrawBox* 		GetDrawBox(){return &m_wndDrawBox;};
    CSize			GetSizeDrawBox(){return m_szDrawBox;};
    void			SetSizeDrawBox(CSize szBox){m_szDrawBox = szBox;};
    /////////////////////////////////////////////////////////////// Status Bars
	CStatusBar*		GetStatusBar(){return &m_wndStatusBar;};
	CTopStatusBar*	GetSBarTop(){return &m_wndSBarTop;};
	CBotStatusBar*	GetSBarBot(){return &m_wndSBarBot;};;
	CWnd* 			GetMessageBar();  // returns our or default BOTTOM StatusBar
	////////////////////////////////////////////////////// Menu
	void 			Init();
	////////////////////////////////////////////////////// Specials
	void 			InitMapFactor();
	void 			InitPrecision();
	void 			InitScaleFactor();
	void 			InitUnit();
	
	virtual CMapFactor* 	GetMapFactor(){return &m_MapFactor;};
	virtual CPrecision* 	GetPrecision(){return &m_Precision;};
	virtual CScaleFactor* 	GetScaleFactor(){return &m_ScaleFactor;};
	virtual CUnit*		 	GetUnit(){return &m_Unit;};
	/////////////////////////////////////////////////
	virtual void 			SetMapFactorInfo();
    
    
    
    
// Implementation
public:
	virtual ~CDrGrafFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

	OPMODE			m_OpMode;
    //////////////////////////////// Menu
    CMenu			m_InitMenu;
    CMenu			m_InputMenu;
    CMenu			m_OutputMenu;
    //////////////////////////////// StatusBar
	CTopStatusBar	m_wndSBarTop;
	CBotStatusBar	m_wndSBarBot;
	CStatusBar  	m_wndStatusBar;
	CToolBar    	m_wndToolBar;
	//////////////////////////////// ToolBoxes
	CElemBox		m_wndElemBox;
	CSize			m_szElemBox;

	CDrawBox		m_wndDrawBox;
	CSize			m_szDrawBox;
 	//////////////////////////////// View
	int				m_nActiveViewNumber;
	///////////////////////////////////// Specials
	CMapFactor 		m_MapFactor;
	CPrecision 		m_Precision;
	CScaleFactor 	m_ScaleFactor;
	CUnit 			m_Unit;

    
// Generated message map functions
protected:
	//{{AFX_MSG(CDrGrafFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnDeckDreampipe();
	afx_msg void OnUpdateDeckDreampipe(CCmdUI* pCmdUI);
	afx_msg void OnDeckSap();
	afx_msg void OnUpdateDeckSap(CCmdUI* pCmdUI);
	afx_msg void OnDeckTab();
	afx_msg void OnUpdateDeckTab(CCmdUI* pCmdUI);
	afx_msg void OnOptionAxison();
	afx_msg void OnUpdateOptionAxison(CCmdUI* pCmdUI);
	afx_msg void OnOptionDialogon();
	afx_msg void OnUpdateOptionDialogon(CCmdUI* pCmdUI);
	afx_msg void OnOptionPenchange();
	afx_msg void OnUpdateOptionPenchange(CCmdUI* pCmdUI);
	afx_msg void OnOptionRefresh();
	afx_msg void OnUpdateOptionRefresh(CCmdUI* pCmdUI);
	afx_msg void OnOptionRubberband();
	afx_msg void OnUpdateOptionRubberband(CCmdUI* pCmdUI);
	afx_msg void OnView12view();
	afx_msg void OnUpdateView12view(CCmdUI* pCmdUI);
	afx_msg void OnView23view();
	afx_msg void OnUpdateView23view(CCmdUI* pCmdUI);
	afx_msg void OnView31view();
	afx_msg void OnUpdateView31view(CCmdUI* pCmdUI);
	afx_msg void OnView3dview();
	afx_msg void OnUpdateView3dview(CCmdUI* pCmdUI);
	afx_msg void OnViewDataview();
	afx_msg void OnUpdateViewDataview(CCmdUI* pCmdUI);
	afx_msg void OnViewDrawbox();
	afx_msg void OnUpdateViewDrawbox(CCmdUI* pCmdUI);
	afx_msg void OnViewElementbox();
	afx_msg void OnUpdateViewElementbox(CCmdUI* pCmdUI);
	afx_msg void OnViewSBarBot();
	afx_msg void OnUpdateViewSBarBot(CCmdUI* pCmdUI);
	afx_msg void OnViewSBarTop();
	afx_msg void OnUpdateViewSBarTop(CCmdUI* pCmdUI);
	afx_msg void OnSpecPaper();
	afx_msg void OnSpecPrecision();
	afx_msg void OnSpecScalefactor();
	afx_msg void OnSpecUnits();
	afx_msg void OnModeInput();
	afx_msg void OnModeOutput();
	afx_msg void OnUpdateModeInput(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModeOutput(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnWinIniChange(LPCSTR lpszSection);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
