// drgrafrm.h : interface of the CDrGrafFrame class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef	_DRGRAFFRAME
#define _DRGRAFFRAME 
                    
#include "globals.h"

#include "booleans.h"
#include "usermsg.h" 

#include <time.h>
#include "clock.h"
/////////////////
#include "toolbox.h"
#include "elembar.h"
#include "suppbar.h"
#include "drstatus.h"

////////////////////////////////////////
class CDrGrafFrame : public CMDIFrameWnd
	
{
	DECLARE_DYNAMIC(CDrGrafFrame)
public:
	CDrGrafFrame();

// Attributes

// Operations
public:
	//////////////////////////////////////////////// Create/Close Frame/View		
	void 			CreateOrActivateFrame(CDocTemplate* pTemplate,CRuntimeClass* pViewClass);
	void 			CloseView(CRuntimeClass* pViewClass);
	int				GetActiveViewNumber(){ return m_nActiveViewNumber;};
	void			SetActiveViewNumber(int VwNum){ m_nActiveViewNumber = VwNum;};
	////////////////////////////////////////////////////// ElementBar/SupportBar Location
	void 			SetElementLeft(UINT nleft){m_nElementLeft =nleft;};
	void 			SetElementTop (UINT ntop ){m_nElementTop  =ntop ;};
	UINT 			GetElementLeft(){return m_nElementLeft;};
	UINT 			GetElementTop (){return m_nElementTop;};
    ////////////////////////////////////////////////////// Boxes
	CElementBar* 	GetElementBox(){return &m_wndElementBar;}; 
	CSupportBar* 	GetSupportBar(){return &m_wndSupportBar;}; 
	CToolBox* 	 	GetDrawBox(){return &m_wndDrawBox;}; 
	CTopStatusBar*	GetStatusBarTop(){return &m_wndStatusBarTop;};
	CBotStatusBar*	GetStatusBar(){return &m_wndStatusBar;};;
	////////////////////////////////////////////////////// Menu
	CMenu*			GetInitMenu(){return &m_InitMenu;};	
	CMenu*			GetOpenMenu(){return &m_OpenMenu;};	
	//////////////////////////////////////////////												
	void			InitialShowWindow(UINT nCmdShow);
//	BOOL 			ReadWindowPlacement(LPWINDOWPLACEMENT pwp);
//	void 			WriteWindowPlacement(LPWINDOWPLACEMENT pwp); 

	void 			UpdateStatusBar(CClientDC* pDC);    
// Implementation

protected:    

	virtual ~CDrGrafFrame();  
	/////////////////////////
	void 	ReadDefaults();
	void 	Initialize();   
	                        
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif


protected:

	///////////////////////////////////////// control bar embedded members 
  	CElementBar		m_wndElementBar;
    UINT    		m_nElementCol; 
    
  	CSupportBar		m_wndSupportBar;
    UINT    		m_nSupportCol; 
    
	UINT			m_nElementLeft;
	UINT			m_nElementTop;
	UINT			m_nSupportLeft;
	UINT			m_nSupportTop;    
 	///////////////////////////////////////// View
	int				m_nActiveViewNumber;
  	////////////////////////////////////
	CToolBox		m_wndDrawBox;    
	CTopStatusBar	m_wndStatusBarTop;
	CBotStatusBar	m_wndStatusBar;
	CToolBar		m_wndToolBar;  
	///////////////////////////
	CMenu			m_InitMenu;
	CMenu			m_OpenMenu;

public:
	
	

// Generated message map functions
protected:
	//{{AFX_MSG(CDrGrafFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg LONG OnSupportBar(UINT wParam,LONG lParam);
	afx_msg void OnViewElementbox();
	afx_msg void OnUpdateViewElementbox(CCmdUI* pCmdUI);
	afx_msg void OnViewDrawbox();
	afx_msg void OnUpdateViewDrawbox(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionDialogOn(CCmdUI* pCmdUI);
	afx_msg void OnOptionDialogOn();
	afx_msg void OnOptionRubberband();
	afx_msg void OnUpdateOptionRubberband(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnWinIniChange(LPCSTR lpszSection);
	afx_msg void OnView12view();
	afx_msg void OnUpdateView12view(CCmdUI* pCmdUI);
	afx_msg void OnView23view();
	afx_msg void OnUpdateView23view(CCmdUI* pCmdUI);
	afx_msg void OnView31view();
	afx_msg void OnUpdateView31view(CCmdUI* pCmdUI);
	afx_msg void OnViewIsoview();
	afx_msg void OnUpdateViewIsoview(CCmdUI* pCmdUI);
	afx_msg void OnViewSBarBot();
	afx_msg void OnUpdateViewSBarBot(CCmdUI* pCmdUI);
	afx_msg void OnViewSBarTop();
	afx_msg void OnUpdateViewSBarTop(CCmdUI* pCmdUI);
	afx_msg void OnViewDataView();
	afx_msg void OnUpdateViewDataView(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
