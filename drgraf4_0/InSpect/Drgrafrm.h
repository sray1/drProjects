// drgrafrm.h : interface of the CDrGrafFrame class
//
#ifndef _CDRGRAFRM_H_ 
#define _CDRGRAFRM_H_ 

#include "Dlg_CTim.h"
#include "CalcTime.h"
/////////////////////
#include "Def_View.h"
#include "Def_Mo.h"	// AllMode
///////////////////// ToolBoxes
#include "Def_MoBox.h"
#include "VOprbox.h"
#include "Mainbox.h"
#include "IGenbox.h"
#include "Cntlbox.h"
#include "EDimbox.h"
#include "MGenbox.h"
#include "drawbox.h"
///////////////////// Status Controls
#include "StatCntl.h"
///////////////////// StatusBars
#include "drstatus.h"
/////////////////////
#include "UserMsg.h"
#include "MouseMgr.h"
#include "CreOpMgr.h"
#include "EditMgr.h"
#include "MditMgr.h"
#include "DelMgr.h"
//todo#include "MergMgr.h"
#include "PostMgr.h"
#include "CreOMMgr.h"
///////////////////// Auxilliary
//#include "MouAXMgr.h"
/////////////////////////////////////////////////////////////////////////////
#define	MAX_IGENITEMS	5		
#define	MAX_CNTLITEMS	5
#define	MAX_EDIMITEMS	4
////////////////////////////////////////		
class CDrGrafFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CDrGrafFrame)
public:
	CDrGrafFrame();

// Attributes
public:

// Operations
public:  


#ifdef _DEBUG
	BOOL			IsDebugCTim(){return m_bDebugCTim;};
	CDlg_CTim*		GetDlg_CTim(){return m_pDlg_CTim;};
//	CCalcTime*		GetCalTime(){return &m_CalcTime;};
#endif
	////////////////////////////////////////////////////
	BOOL			IsAuxiMode(){return m_bAuxiMode;};	// TRUE = Auxilliary Mode/ FALSE = Primary Mode
	void			SetAuxiMode(BOOL b){m_bAuxiMode = b;}; // Edit/Creop etc. depends on this
	BOOL			IsMeshMode(){return m_bMeshMode;};	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	void			SetMeshMode(BOOL b){m_bMeshMode = b;}; // Edit/Creop etc. depends on this
	void			OnModeChange();
	///////////////////////////////////////////////////
	void			OnAddl3dview();
	void			OnModeInput();
	void			OnModeOutput();
	/////////////////////////////////////////////////////////
	PROBDIMLIM		GetProbDimLim(){return m_ProbDimLim;};
	ELEMDIMLIM		GetElemDimLim(){return m_ElemDimLim;};
	void			SetProbDimLim(PROBDIMLIM p){m_ProbDimLim = p;};
	void			SetElemDimLim(ELEMDIMLIM e){m_ElemDimLim = e;};
	/////////////////////////////////////////////////////////
	BOOL		IsEDimOpen(UINT i){return m_bEDimOpen[i];};
	void		ReSetEDimOpen(BOOL b,int i)
				{
					m_bEDimOpen[i] = b;
//					SendMessage(ID_RESET_TASKID);
				};
	BOOL		IsIGenOpen(UINT i){return m_bIGenOpen[i];};
	void		ReSetIGenOpen(BOOL b,int i)
				{
					m_bIGenOpen[i] = b;
//					SendMessage(ID_RESET_TASKID);
				};
	BOOL		IsCntlOpen(UINT i){return m_bCntlOpen[i];};
	void		ReSetCntlOpen(BOOL b,int i)
				{
					m_bCntlOpen[i] = b;
//					SendMessage(ID_RESET_TASKID);
				};
	///////////////////////////////////////////////////////////////////////
	UINT		GetCurrentVOprID(){return m_CurrentVOprID;};
	UINT		GetCurrentOperID(){return m_CurrentOperID;};
	UINT		GetCurrentCntlID(){return m_CurrentCntlID;};
	UINT		GetCurrentIGenID(){return m_CurrentIGenID;};
	UINT		GetCurrentPostID(){return m_CurrentPostID;};
	/////////////////////////////////////////////////////////////////////// for MeshMode
	void		SetCurrentOperID_Mesh(UINT i)
				{
					m_CurrentOperID = i;
					SendMessage(ID_RESET_CNTLOPEN_MESH);
				};
	void		SetCurrentCntlID_Mesh(UINT i)
				{
					m_CurrentCntlID = i;
					SendMessage(ID_RESET_IGENOPEN_MESH);
				};
	void		SetCurrentIGenID_Mesh(UINT i)
				{
					m_CurrentIGenID = i;
					SendMessage(ID_RESET_MASKID);
				};
	/////////////////////////////////////////////////////////////////////// for GOP_POST etc
	void		SetCurrentOperID_Alternate(UINT i)
				{
					m_CurrentOperID = i;
					SendMessage(ID_RESET_IGENOPEN);
				};
	void		SetCurrentIGenID_Alternate(UINT i)
				{
					m_CurrentIGenID = i;
					SendMessage(ID_RESET_CNTLOPEN);
				};
	void		SetCurrentCntlID_Alternate(UINT i)
				{
					m_CurrentCntlID = i;
					SendMessage(ID_RESET_TASKID);
				};
	/////////////////////////////////////////////
	void		SetCurrentPostID(UINT i)
				{
					m_CurrentPostID = i;
					SendMessage(ID_RESET_TASKID);
				};
	////////////////////////////////////////////////////////////////////////
	void		SetCurrentVOprID(UINT i)
				{
					m_CurrentVOprID = i;
					SendMessage(ID_RESET_VASKID);
				};
	/////////////////////////////////////////////////////////////////////////
	void		SetCurrentOperID(UINT i)
				{
					m_CurrentOperID = i;
					m_bAuxiMode?
					SendMessage(ID_RESET_CNTLOPEN_AUXI):
					SendMessage(ID_RESET_CNTLOPEN);
				};
	void		SetCurrentCntlID(UINT i)
				{
					m_CurrentCntlID = i;
					m_bAuxiMode?
					SendMessage(ID_RESET_IGENOPEN_AUXI):
					SendMessage(ID_RESET_IGENOPEN);
				};
	void		SetCurrentIGenID(UINT i)
				{
					m_CurrentIGenID = i;
					m_bAuxiMode?
					SendMessage(ID_RESET_XASKID):
					SendMessage(ID_RESET_TASKID);
				};
	///////////////////////////////////////////////////// Merg Manager
//todo	CMergMgr*		GetMergMgr(){return &m_MergMgr;};
	///////////////////////////////////////////////////// Post Manager
	CPostMgr*		GetPostMgr(){return &m_PostMgr;};
	///////////////////////////////////////////////////// Delete Manager
	CDelMgr*		GetDelMgr(){return &m_DelMgr;};
	///////////////////////////////////////////////////// Edit Manager
	CEditMgr*		GetEditMgr(){return &m_EditMgr;};
	///////////////////////////////////////////////////// Mesh Edit Manager
	CMditMgr*		GetMditMgr(){return &m_MditMgr;};
	///////////////////////////////////////////////////// CreOp Manager
	CCreOpMgr*		GetCreOpMgr(){return &m_CreOpMgr;};
	///////////////////////////////////////////////////// CreOM Manager
	CCreOMMgr*		GetCreOMMgr(){return &m_CreOMMgr;};
	///////////////////////////////////////////////////// Mouse Manager
	CMouseMgr*		GetMouseMgr(){return &m_MouseMgr;};
	UINT			GetMouseBoxType(){return m_MoBoxType;};
	void			SetMouseBoxType(UINT b){m_MoBoxType = b;};
	///////////////////////////////////////////////////// Mouse Manager: Auxilliary
//	CMouAXMgr*		GetMouAXMgr(){return &m_MouAXMgr;};
//	UINT			GetMouseBoxType(){return m_MoBoxType;};
//	void			SetMouseBoxType(UINT b){m_MoBoxType = b;};
	///////////////////////////////////
	OPMODE			GetOpMode(){return m_OpMode;};
	void			SetOpMode(OPMODE om){m_OpMode = om;};
	////////////////////////////////////////////////////////////// Menu
	void 			SwitchMenu( UINT nMenuNum);
	CMenu*			GetInitMenu(){return &m_InitMenu;};
	CMenu*			GetInputMenu(){return &m_InputMenu;};
	CMenu*			GetAuxInputMenu(){return &m_AuxInputMenu;};
	CMenu*			GetOutputMenu(){return &m_OutputMenu;};
	UINT			GetCurMenuID(){return m_CurMenuID;};
	////////////////////////////////////////////////////////////// Window Placement												
	void			InitialShowWindow(UINT nCmdShow);
	////////////////////////////////////////////////////////////// Create/Close Frame/View		
	CRect&			GetRect12(){return m_Rect12;};;	// for adjustment of View12 Size
	CView*			GetViewPointer(CRuntimeClass* pViewClass);
	BOOL			AnyOtherInputViewVisible();
	void 			CreateOrActivateFrame(CDocTemplate* pTemplate,CRuntimeClass* pViewClass);
	void 			CloseView(CRuntimeClass* pViewClass);
	int				GetActiveViewNumber(){ return m_nActiveViewNumber;};
	void			SetActiveViewNumber(int VwNum){ m_nActiveViewNumber = VwNum;};
    ////////////////////////////////////////////////////////////////////// ToolBoxes
	BOOL			IsIGenBoxActive(){return m_bIGenBox;};
	void			SetIGenBoxStatus(BOOL bStatus){m_bIGenBox = bStatus;};
	BOOL			IsMGenBoxActive(){return m_bMGenBox;};
	void			SetMGenBoxStatus(BOOL bStatus){m_bMGenBox = bStatus;};
	int				GetActiveObjectType(){return m_nObjectType;};
	void			SetActiveObjectType(int nObjectType){m_nObjectType = nObjectType;};
	int				GetActiveToolType(){return m_nToolType;};
	void			SetActiveToolType(int nToolType){m_nToolType = nToolType;};
    ///////////////////////////////////////////////////////////// OperBox
	BOOL			IsOperBoxActive(){return m_bOperBox;};
	void			SetOperBoxStatus(BOOL bStatus){m_bOperBox = bStatus;};
    ///////////////////////////////////////////////////////////// CntlBox
	BOOL			IsCntlBoxActive(){return m_bCntlBox;};
	void			SetCntlBoxStatus(BOOL bStatus){m_bCntlBox = bStatus;};
	///////////////////////////////////////////////////////////// DrawBox
	BOOL			IsDrawBoxActive(){return m_bDrawBox;};
	void			SetDrawBoxStatus(BOOL bStatus){m_bDrawBox = bStatus;};
	COLORREF		GetActiveForeColor(){return m_crFore;};
	void			SetActiveForeColor(COLORREF nColor){m_crFore = nColor;};
	COLORREF		GetActiveBackColor(){return m_crBack;};
	void			SetActiveBackColor(COLORREF nColor){m_crBack = nColor;};
	///////////////////////////////////////////////////////////// MainBox/IGenBox etc
    CEDimBox* 		GetEDimBox(){return &m_wndEDimBox;};
    CSize			GetSizeEDimBox(){return m_szEDimBox;};
    void			SetSizeEDimBox(CSize szBox){m_szEDimBox = szBox;};

    CVOprBox* 		GetVOprBox(){return &m_wndVOprBox;};
    CSize			GetSizeVOprBox(){return m_szVOprBox;};
    void			SetSizeVOprBox(CSize szBox){m_szVOprBox = szBox;};

    CMainBox* 		GetOperBox(){return &m_wndOperBox;};
    CSize			GetSizeOperBox(){return m_szOperBox;};
    void			SetSizeOperBox(CSize szBox){m_szOperBox = szBox;};

    CIGenBox* 		GetIGenBox(){return &m_wndIGenBox;};
    CSize			GetSizeIGenBox(){return m_szIGenBox;};
    void			SetSizeIGenBox(CSize szBox){m_szIGenBox = szBox;};

    CCntlBox* 		GetCntlBox(){return &m_wndCntlBox;};
    CSize			GetSizeCntlBox(){return m_szCntlBox;};
    void			SetSizeCntlBox(CSize szBox){m_szCntlBox = szBox;};

    CMGenBox* 		GetMGenBox(){return &m_wndMGenBox;};
    CSize			GetSizeMGenBox(){return m_szMGenBox;};
    void			SetSizeMGenBox(CSize szBox){m_szMGenBox = szBox;};

    CDrawBox* 		GetDrawBox(){return &m_wndDrawBox;};
    CSize			GetSizeDrawBox(){return m_szDrawBox;};
    void			SetSizeDrawBox(CSize szBox){m_szDrawBox = szBox;};
	/////////////////////////////////////////////////////////////// Static Controls
	void			UpdateStaticControls();
	void			UpdateModeStat(CString& str);
	void			UpdateSnapStat(CString& str);
	void			UpdateSpawnStat(CString& str);
	void			UpdateBLineStat(CString& str);
	void			UpdateAutoAcceptStat(CString& str);
	void			UpdateSingleSegStat(CString& str);
	void			UpdateCntlStat(CString& str);
	void			UpdateIGenStat(CString& str);
	void			UpdateOperStat(CString& str);
	void			UpdateCurrStat(CString& str)
					{
						m_CurrStat.SetText(str);
						m_CurrStat.Invalidate();
						m_CurrStat.UpdateWindow();
					};
	///////////////////////////////////////
	ALLMODES		GetCurrentModeID(){return m_CurrentModeID;};
	void			SetCurrentModeID(ALLMODES a){m_CurrentModeID = a;};
	CString&		GetstrModeID(){return m_strModeID;};
	void			SetstrModeID(CString& str){m_strModeID = str;};
    CStatCntl* 		GetModeStat(){return &m_ModeStat;};
    CSize			GetSizeModeStat(){return m_szModeStat;};
    void			SetSizeModeStat(CSize szBox){m_szModeStat = szBox;};
	
	CString&		GetstrCntlID(){return m_strCntlID;};
	void			SetstrCntlID(CString& str){m_strCntlID = str;};
    CStatCntl* 		GetCntlStat(){return &m_CntlStat;};
    CSize			GetSizeCntlStat(){return m_szCntlStat;};
    void			SetSizeCntlStat(CSize szBox){m_szCntlStat = szBox;};
	
	CString&		GetstrIGenID(){return m_strIGenID;};
	void			SetstrIGenID(CString& str){m_strIGenID = str;};
    CStatCntl* 		GetIGenStat(){return &m_IGenStat;};
    CSize			GetSizeIGenStat(){return m_szIGenStat;};
    void			SetSizeIGenStat(CSize szBox){m_szIGenStat = szBox;};
	
	CString&		GetstrOperID(){return m_strOperID;};
	void			SetstrOperID(CString& str){m_strOperID = str;};
    CStatCntl* 		GetOperStat(){return &m_OperStat;};
    CSize			GetSizeOperStat(){return m_szOperStat;};
    void			SetSizeOperStat(CSize szBox){m_szOperStat = szBox;};

	CString&		GetstrCurrID(){return m_strCurrID;};
	void			SetstrCurrID(CString& str){m_strCurrID = str;};
    CStatCntl* 		GetCurrStat(){return &m_CurrStat;};
    CSize			GetSizeCurrStat(){return m_szCurrStat;};
    void			SetSizeCurrStat(CSize szBox){m_szCurrStat = szBox;};

	CString&		GetstrDrawID(){return m_strDrawID;};
	void			SetstrDrawID(CString& str){m_strDrawID = str;};
    CStatCntl* 		GetDrawStat(){return &m_DrawStat;};
    CSize			GetSizeDrawStat(){return m_szDrawStat;};
    void			SetSizeDrawStat(CSize szBox){m_szDrawStat = szBox;};
	////////////////////////////////////////////////////////////////////
    CStatCntl* 		GetAutoAcceptStat(){return &m_AutoAcceptStat;};
    CSize			GetSizeAutoAcceptStat(){return m_szAutoAcceptStat;};
    void			SetSizeAutoAcceptStat(CSize szBox){m_szAutoAcceptStat = szBox;};

    CStatCntl* 		GetSingleSegStat(){return &m_SingleSegStat;};
    CSize			GetSizeSingleSegStat(){return m_szSingleSegStat;};
    void			SetSizeSingleSegStat(CSize szBox){m_szSingleSegStat = szBox;};

    CStatCntl* 		GetBLineStat(){return &m_BLineStat;};
    CSize			GetSizeBLineStat(){return m_szBLineStat;};
    void			SetSizeBLineStat(CSize szBox){m_szBLineStat = szBox;};

    CStatCntl* 		GetSpawnStat(){return &m_SpawnStat;};
    CSize			GetSizeSpawnStat(){return m_szSpawnStat;};
    void			SetSizeSpawnStat(CSize szBox){m_szSpawnStat = szBox;};

    CStatCntl* 		GetSnapStat(){return &m_SnapStat;};
    CSize			GetSizeSnapStat(){return m_szSnapStat;};
    void			SetSizeSnapStat(CSize szBox){m_szSnapStat = szBox;};
	/////////
	CStatCntl*		GetLastStatCntlHit(){return m_pLastStatCntlHit;};
	void			SetLastStatCntlHit(CStatCntl* m){m_pLastStatCntlHit = m;};
	////////////////////////////////////////////////////////////////////////
	void			ModeLessOff();
	void			ModeLessOn();
	void			SizeRectDlgIn(CRect& BoxRect);

	void			ModeLessOff_Mesh();
	void			ModeLessOn_Mesh();

	void			ModeLessOff_Auxi();	// Auxilliary
	void			ModeLessOn_Auxi();
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


#ifdef _DEBUG
	CDlg_CTim*		m_pDlg_CTim;	//Modeless
	BOOL			m_bDebugCTim;	// Debug Message Dlg
//	CCalcTime		m_CalcTime;
#endif
	////////////////////////////////
	BOOL			m_bMeshMode;	// TRUE = MESH Mode/  FALSE = GENERATOR Mode
	BOOL			m_bAuxiMode;	// TRUE = Auxilliary Mode/  FALSE = Primary Mode
	//////////////////////////////////////////
	BOOL			m_bIGenOpen[MAX_IGENITEMS];//0=Node	/1=Curve	/2=Patch	/3=Solid	/4=Object
	BOOL			m_bCntlOpen[MAX_CNTLITEMS];//0=Mesh	/1=Suppo	/2=Stati	/3=Histo	/4=Spectr
	BOOL			m_bEDimOpen[MAX_EDIMITEMS];//0=0D	/1=1D		/2=2D		/3=3D
	///////////////////////////////////////////
	PROBDIMLIM		m_ProbDimLim;
	ELEMDIMLIM		m_ElemDimLim;
	//////////////////////////////// Special Status
	CStatCntl		m_SnapStat;	
	CSize			m_szSnapStat;
	///////
	CStatCntl		m_SpawnStat;	
	CSize			m_szSpawnStat;
	///////
	CStatCntl		m_BLineStat;	
	CSize			m_szBLineStat;
	///////
	CStatCntl		m_AutoAcceptStat;	
	CSize			m_szAutoAcceptStat;
	///////
	CStatCntl		m_SingleSegStat;	
	CSize			m_szSingleSegStat;
	///
	CStatCntl*		m_pLastStatCntlHit;
	//////////////////////////////// Active TooL
	ALLMODES		m_CurrentModeID;				//Def_Mo.h
	CString			m_strModeID;
	UINT			m_CurrentVOprID;
	CString			m_strVOprID;
	UINT			m_CurrentCntlID;
	CString			m_strCntlID;
	UINT			m_CurrentIGenID;
	CString			m_strIGenID;
	UINT			m_CurrentOperID;
	CString			m_strOperID;
	UINT			m_CurrentPostID;	// Current ElementType To be Posted
	CString			m_strPostID;
	////////////////////////////////
	CString			m_strCurrID;

	UINT			m_CurrentDrawID;
	CString			m_strDrawID;
	///////
	CStatCntl		m_VOprStat;	
	CSize			m_szVOprStat;

	CStatCntl		m_DrawStat;	
	CSize			m_szDrawStat;

	CStatCntl		m_CntlStat;	
	CSize			m_szCntlStat;

	CStatCntl		m_IGenStat;	
	CSize			m_szIGenStat;

	CStatCntl		m_OperStat;	
	CSize			m_szOperStat;

	CStatCntl		m_CurrStat;	
	CSize			m_szCurrStat;

	CStatCntl		m_ModeStat;	
	CSize			m_szModeStat;
	//////////////////////////////
	CRect			m_Rect12;	// for adjustment of View12 Size
	////////////////////////////////
	UINT			m_MoBoxType;
	OPMODE			m_OpMode;
    //////////////////////////////// Menu
    CMenu			m_InitMenu;
    CMenu			m_InputMenu;
    CMenu			m_AuxInputMenu;
    CMenu			m_OutputMenu;
   	UINT			m_CurMenuID;
	//////////////////////////////// StatusBar
	CTopStatusBar	m_wndSBarTop;
	CBotStatusBar	m_wndSBarBot;
	CStatusBar  	m_wndStatusBar;
	CToolBar    	m_wndToolBar;
	//////////////////////////////// MergMgr
//todo	CMergMgr		m_MergMgr;					
	//////////////////////////////// PostMgr
	CPostMgr		m_PostMgr;					
	//////////////////////////////// DeleteMgr
	CDelMgr			m_DelMgr;
	//////////////////////////////// EditMgr
	CEditMgr		m_EditMgr;
	//////////////////////////////// MeshEditMgr
	CMditMgr		m_MditMgr;
	//////////////////////////////// CreOpMgr
	CCreOpMgr		m_CreOpMgr;
	//////////////////////////////// CreOMMgr
	CCreOMMgr		m_CreOMMgr;
	//////////////////////////////// MouseMgr
	CMouseMgr		m_MouseMgr;
	//////////////////////////////// MouseMgr:Auxilliary
//	CMouAXMgr		m_MouAXMgr;
	//////////////////////////////// ToolBoxes
	CEDimBox		m_wndEDimBox;
	CSize			m_szEDimBox;

	CVOprBox		m_wndVOprBox;
	CSize			m_szVOprBox;

	CCntlBox		m_wndCntlBox;
	CSize			m_szCntlBox;

	CIGenBox		m_wndIGenBox;
	CSize			m_szIGenBox;

	CMGenBox		m_wndMGenBox;
	CSize			m_szMGenBox;

	CMainBox		m_wndOperBox;
	CSize			m_szOperBox;

	CDrawBox		m_wndDrawBox;
	CSize			m_szDrawBox;
	//////////////////////////////// CntlBox
    BOOL			m_bCntlBox;
    int				m_nObjectType;
	int				m_nToolType;
	//////////////////////////////// IGenBox
    BOOL			m_bIGenBox;
    BOOL			m_bMGenBox;
	//////////////////////////////// OperBox = MainBox same thing)
    BOOL			m_bOperBox;
	//////////////////////////////// DrawBox
    BOOL			m_bDrawBox;
	COLORREF		m_crFore;
	COLORREF		m_crBack;
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
	afx_msg void OnViewMeshDataview();
	afx_msg void OnUpdateViewMeshDataview(CCmdUI* pCmdUI);
	afx_msg void OnViewDeckview();
	afx_msg void OnUpdateViewDeckview(CCmdUI* pCmdUI);
	afx_msg void OnViewCntlbox();
	afx_msg void OnUpdateViewCntlbox(CCmdUI* pCmdUI);
	afx_msg void OnViewGenbox();
	afx_msg void OnUpdateViewGenbox(CCmdUI* pCmdUI);
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
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSettingChange(UINT uFlags, LPCSTR lpszSection);
	afx_msg void OnViewMeshBox();
	afx_msg void OnUpdateViewMeshBox(CCmdUI* pCmdUI);
	afx_msg void OnOptionAutoacceptOn();
	afx_msg void OnUpdateOptionAutoacceptOn(CCmdUI* pCmdUI);
	afx_msg void OnOptionSpawnOn();
	afx_msg void OnUpdateOptionSpawnOn(CCmdUI* pCmdUI);
	afx_msg void OnOptionBlineOn();
	afx_msg void OnUpdateOptionBlineOn(CCmdUI* pCmdUI);
	afx_msg void OnOptionSingleSegOn();
	afx_msg void OnUpdateOptionSingleSegOn(CCmdUI* pCmdUI);
	afx_msg void OnViewInputstatusControls();
	afx_msg void OnUpdateViewInputstatusControls(CCmdUI* pCmdUI);
	afx_msg void OnViewInputstatusDecorators();
	afx_msg void OnUpdateViewInputstatusDecorators(CCmdUI* pCmdUI);
	afx_msg void OnViewInputstatusGenerator();
	afx_msg void OnUpdateViewInputstatusGenerator(CCmdUI* pCmdUI);
	afx_msg void OnViewInputstatusOperations();
	afx_msg void OnUpdateViewInputstatusOperations(CCmdUI* pCmdUI);
	afx_msg void OnViewInputstatusCurrent();
	afx_msg void OnUpdateViewInputstatusCurrent(CCmdUI* pCmdUI);
	afx_msg void OnViewOperbox();
	afx_msg void OnUpdateViewOperbox(CCmdUI* pCmdUI);
	afx_msg void OnWindowNew3dView();
	afx_msg void OnUpdateWindowNew3dView(CCmdUI* pCmdUI);
	afx_msg void OnDebugCalctime();
	afx_msg void OnUpdateDebugCalctime(CCmdUI* pCmdUI);
	afx_msg void OnViewAllview();
	afx_msg void OnUpdateViewAllview(CCmdUI* pCmdUI);
	afx_msg void OnViewSpectra();
	afx_msg void OnUpdateViewSpectra(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModeAuxilliarySpatial(CCmdUI* pCmdUI);
	afx_msg void OnModeAuxilliarySpectral();
	afx_msg void OnUpdateModeAuxilliarySpectral(CCmdUI* pCmdUI);
	afx_msg void OnModeAuxilliaryTemporal();
	afx_msg void OnUpdateModeAuxilliaryTemporal(CCmdUI* pCmdUI);
	afx_msg void OnOptionSnaponObjmerg();
	afx_msg void OnUpdateOptionSnaponObjmerg(CCmdUI* pCmdUI);
	afx_msg void OnViewDatabaseFormdata();
	afx_msg void OnUpdateViewDatabaseFormdata(CCmdUI* pCmdUI);
	afx_msg void OnSpecsTolerances();
	//}}AFX_MSG
	afx_msg long OnOptionMode(UINT wParam, long lParam);
	afx_msg long OnResetVaskID(UINT wParam, long lParam);
	afx_msg long OnUpdateStatCntls(UINT wParam, long lParam);
	afx_msg long OnResetCntlOpen(UINT wParam, long lParam);
	afx_msg long OnResetIGenOpen(UINT wParam, long lParam);
	afx_msg long OnResetCntlOpen_Mesh(UINT wParam, long lParam);
	afx_msg long OnResetIGenOpen_Mesh(UINT wParam, long lParam);
	afx_msg long OnResetCntlOpen_Auxi(UINT wParam, long lParam);
	afx_msg long OnResetIGenOpen_Auxi(UINT wParam, long lParam);
	afx_msg long OnResetMaskID(UINT wParam, long lParam);
	afx_msg long OnResetTaskID(UINT wParam, long lParam);
	afx_msg long OnResetXaskID(UINT wParam, long lParam);
	afx_msg long OnResetModeLess(UINT wParam, long lParam);
	afx_msg long OnResetModeLess_Mesh(UINT wParam, long lParam);
	afx_msg long OnResetModeLess_Auxi(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateF_MIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeF_MIn(UINT wParam, long lParam);
	afx_msg long OnUpdateF_MIn(UINT wParam, long lParam);
	afx_msg long OnCancelF_MIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateD_RIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeD_RIn(UINT wParam, long lParam);
	afx_msg long OnUpdateD_RIn(UINT wParam, long lParam);
	afx_msg long OnCancelD_RIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivatePrsIn(UINT wParam, long lParam);
	afx_msg long OnGoodByePrsIn(UINT wParam, long lParam);
	afx_msg long OnUpdatePrsIn(UINT wParam, long lParam);
	afx_msg long OnCancelPrsIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateThrIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeThrIn(UINT wParam, long lParam);
	afx_msg long OnUpdateThrIn(UINT wParam, long lParam);
	afx_msg long OnCancelThrIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateLWtIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeLWtIn(UINT wParam, long lParam);
	afx_msg long OnUpdateLWtIn(UINT wParam, long lParam);
	afx_msg long OnCancelLWtIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateSupIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeSupIn(UINT wParam, long lParam);
	afx_msg long OnUpdateSupIn(UINT wParam, long lParam);
	afx_msg long OnCancelSupIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateNodIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeNodIn(UINT wParam, long lParam);
	afx_msg long OnUpdateNodIn(UINT wParam, long lParam);
	afx_msg long OnCancelNodIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateLQCIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeLQCIn(UINT wParam, long lParam);
	afx_msg long OnUpdateLQCIn(UINT wParam, long lParam);
	afx_msg long OnCancelLQCIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateCrcIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeCrcIn(UINT wParam, long lParam);
	afx_msg long OnUpdateCrcIn(UINT wParam, long lParam);
	afx_msg long OnCancelCrcIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateO3DIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeO3DIn(UINT wParam, long lParam);
	afx_msg long OnUpdateO3DIn(UINT wParam, long lParam);
	afx_msg long OnCancelO3DIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateSolIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeSolIn(UINT wParam, long lParam);
	afx_msg long OnUpdateSolIn(UINT wParam, long lParam);
	afx_msg long OnCancelSolIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivatePatIn(UINT wParam, long lParam);
	afx_msg long OnGoodByePatIn(UINT wParam, long lParam);
	afx_msg long OnUpdatePatIn(UINT wParam, long lParam);
	afx_msg long OnCancelPatIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateCreIn(UINT wParam, long lParam);
	afx_msg long OnGoodByeCreIn(UINT wParam, long lParam);
	afx_msg long OnUpdateCreIn(UINT wParam, long lParam);
	afx_msg long OnCancelCreIn(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateFE0In(UINT wParam, long lParam);
	afx_msg long OnGoodByeFE0In(UINT wParam, long lParam);
	afx_msg long OnUpdateFE0In(UINT wParam, long lParam);
	afx_msg long OnCancelFE0In(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateFE1In(UINT wParam, long lParam);
	afx_msg long OnGoodByeFE1In(UINT wParam, long lParam);
	afx_msg long OnUpdateFE1In(UINT wParam, long lParam);
	afx_msg long OnCancelFE1In(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateFE2In(UINT wParam, long lParam);
	afx_msg long OnGoodByeFE2In(UINT wParam, long lParam);
	afx_msg long OnUpdateFE2In(UINT wParam, long lParam);
	afx_msg long OnCancelFE2In(UINT wParam, long lParam);
	afx_msg long OnCreateorActivateFE3In(UINT wParam, long lParam);
	afx_msg long OnGoodByeFE3In(UINT wParam, long lParam);
	afx_msg long OnUpdateFE3In(UINT wParam, long lParam);
	afx_msg long OnCancelFE3In(UINT wParam, long lParam);
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
#endif
