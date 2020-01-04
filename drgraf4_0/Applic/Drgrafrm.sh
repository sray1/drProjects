// drgrafrm.h : interface of the CDrGrafFrame class
//
#ifndef _CDRGRAFRM_H_ 
#define _CDRGRAFRM_H_ 

#include "glb_View.h"
///////////////////// ToolBoxes
#include "MoBoxDef.h"
#include "Meshbox.h"
#include "elembox.h"
#include "drawbox.h"
///////////////////// Data Dialogs
#include "Dlg_SupI.h"
#include "Dlg_NodI.h"
#include "Dlg_LQCI.h"
#include "Dlg_CrcI.h"
#include "Dlg_Co4I.h"
///////////////////// StatusBars
#include "drstatus.h"
/////////////////////
#include "mousemgr.h"
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

	UINT			GetMouseBoxType(){return m_MoBoxType;};
	void			SetMouseBoxType(UINT b){m_MoBoxType = b;};
	///////////////////////////////////
	OPMODE			GetOpMode(){return m_OpMode;};
	void			SetOpMode(OPMODE om){m_OpMode = om;};
	////////////////////////////////////////////////////////////// Menu
	void 			SwitchMenu( UINT nMenuNum);
	CMenu*			GetInitMenu(){return &m_InitMenu;};
	CMenu*			GetInputMenu(){return &m_InputMenu;};
	CMenu*			GetOutputMenu(){return &m_OutputMenu;};
	UINT			GetCurMenuID(){return m_CurMenuID;};
	////////////////////////////////////////////////////////////// Window Placement												
	void			InitialShowWindow(UINT nCmdShow);
	////////////////////////////////////////////////////////////// Create/Close Frame/View		
	CView*			GetViewPointer(CRuntimeClass* pViewClass);
	BOOL			AnyOtherInputViewVisible();
	void 			CreateOrActivateFrame(CDocTemplate* pTemplate,CRuntimeClass* pViewClass);
	void 			CloseView(CRuntimeClass* pViewClass);
	int				GetActiveViewNumber(){ return m_nActiveViewNumber;};
	void			SetActiveViewNumber(int VwNum){ m_nActiveViewNumber = VwNum;};
	///////////////////////////////////////////////////// Mouse Manager
	CMouseMgr*		GetMouseMgr(){return &m_MouseMgr;};
    ///////////////////////////////////////////////////////////// ToolBoxes
	BOOL			IsElemBoxActive(){return m_bElemBox;};
	void			SetElemBoxStatus(BOOL bStatus){m_bElemBox = bStatus;};
	int				GetActiveObjectType(){return m_nObjectType;};
	void			SetActiveObjectType(int nObjectType){m_nObjectType = nObjectType;};
	int				GetActiveToolType(){return m_nToolType;};
	void			SetActiveToolType(int nToolType){m_nToolType = nToolType;};
	////////////////////////////////////////////////////////////////////// DrawBox
	BOOL			IsDrawBoxActive(){return m_bDrawBox;};
	void			SetDrawBoxStatus(BOOL bStatus){m_bDrawBox = bStatus;};
	COLORREF		GetActiveForeColor(){return m_crFore;};
	void			SetActiveForeColor(COLORREF nColor){m_crFore = nColor;};
	COLORREF		GetActiveBackColor(){return m_crBack;};
	void			SetActiveBackColor(COLORREF nColor){m_crBack = nColor;};
	/////////////////////////////////////////////////////	
	///////////////////////////////////////////////////////
    CMeshBox* 		GetMeshBox(){return &m_wndMeshBox;};
    CSize			GetSizeMeshBox(){return m_szMeshBox;};
    void			SetSizeMeshBox(CSize szBox){m_szMeshBox = szBox;};

    CElemBox* 		GetElemBox(){return &m_wndElemBox;};
    CSize			GetSizeElemBox(){return m_szElemBox;};
    void			SetSizeElemBox(CSize szBox){m_szElemBox = szBox;};

    CDrawBox* 		GetDrawBox(){return &m_wndDrawBox;};
    CSize			GetSizeDrawBox(){return m_szDrawBox;};
    void			SetSizeDrawBox(CSize szBox){m_szDrawBox = szBox;};
	/////////////////////////////////////////////////////////////// Data Dialogs
	void			ModeLessOff();
	void			ModeLessOn();
	void			SizeRectDlgIn(CRect& BoxRect);
	CDlg_SupI*		GetSupInDlg(){return m_pSupInDlg;};                                                                                
	CDlg_NodI*		GetNodInDlg(){return m_pNodInDlg;};                                                                                
	CDlg_LQCI*		GetLQCInDlg(){return m_pLQCInDlg;};                                                                                
	CDlg_CrcI*		GetCrcInDlg(){return m_pCrcInDlg;};                                                                                
	CDlg_Co4I*		GetCo4InDlg(){return m_pCo4InDlg;};                                                                                
    /////////////////////////////////////////////////////////////// Status Bars
	CStatusBar*		GetStatusBar(){return &m_wndStatusBar;};
	CTopStatusBar*	GetSBarTop(){return &m_wndSBarTop;};
	CBotStatusBar*	GetSBarBot(){return &m_wndSBarBot;};;
	CWnd* 			GetMessageBar();  // returns our or default BOTTOM StatusBar
	////////////////////////////////////////////////////// Menu
	void 			Init();
	
    
    
    
    
// Implementation
public:
	virtual ~CDrGrafFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

	UINT			m_MoBoxType;
	OPMODE			m_OpMode;
    //////////////////////////////// Menu
    CMenu			m_InitMenu;
    CMenu			m_InputMenu;
    CMenu			m_OutputMenu;
   	UINT			m_CurMenuID;
	//////////////////////////////// StatusBar
	CTopStatusBar	m_wndSBarTop;
	CBotStatusBar	m_wndSBarBot;
	CStatusBar  	m_wndStatusBar;
	CToolBar    	m_wndToolBar;
	//////////////////////////////// MouseMgr
	CMouseMgr		m_MouseMgr;
	//////////////////////////////// ToolBoxes
	CMeshBox		m_wndMeshBox;
	CSize			m_szMeshBox;

	CElemBox		m_wndElemBox;
	CSize			m_szElemBox;

	CDrawBox		m_wndDrawBox;
	CSize			m_szDrawBox;
	//////////////////////////////// ToolBox
    BOOL			m_bElemBox;
    int				m_nObjectType;
	int				m_nToolType;
	//////////////////////////////// DrawBox
    BOOL			m_bDrawBox;
	COLORREF		m_crFore;
	COLORREF		m_crBack;
	//////////////////////////////// Data Dialogs
	CDlg_SupI*		m_pSupInDlg;                                                                                
	CDlg_NodI*		m_pNodInDlg;                                                                                
	CDlg_LQCI*		m_pLQCInDlg; 
	CDlg_CrcI*		m_pCrcInDlg; 
	CDlg_Co4I*		m_pCo4InDlg; 
 	//////////////////////////////// View
	int				m_nActiveViewNumber;

    
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
	afx_msg void OnViewMeshBox();
	afx_msg void OnUpdateViewMeshBox(CCmdUI* pCmdUI);
	afx_msg void OnOptionAutoacceptOn();
	afx_msg void OnUpdateOptionAutoacceptOn(CCmdUI* pCmdUI);
	afx_msg void OnOptionBlineOn();
	afx_msg void OnUpdateOptionBlineOn(CCmdUI* pCmdUI);
	afx_msg void OnOptionSingleSegOn();
	afx_msg void OnUpdateOptionSingleSegOn(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg long OnResetModeLess(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateF_MIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeF_MIn(UINT wParam, long lParam);
	afx_msg long OnUpdateF_MIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateD_RIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeD_RIn(UINT wParam, long lParam);
	afx_msg long OnUpdateD_RIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivatePrsIn(UINT wParam, long lParam);
	afx_msg long OnGoodByePrsIn(UINT wParam, long lParam);
	afx_msg long OnUpdatePrsIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateThrIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeThrIn(UINT wParam, long lParam);
	afx_msg long OnUpdateThrIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateLWtIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeLWtIn(UINT wParam, long lParam);
	afx_msg long OnUpdateLWtIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateSupIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeSupIn(UINT wParam, long lParam);
	afx_msg long OnUpdateSupIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateNodIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeNodIn(UINT wParam, long lParam);
	afx_msg long OnUpdateNodIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateLQCIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeLQCIn(UINT wParam, long lParam);
	afx_msg long OnUpdateLQCIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateCrcIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeCrcIn(UINT wParam, long lParam);
	afx_msg long OnUpdateCrcIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateCo4In(UINT wParam, long lParam);
	afx_msg long OnGoodByeCo4In(UINT wParam, long lParam);
	afx_msg long OnUpdateCo4In(UINT wParam, long lParam);
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif
