// drgrafrm.cpp : implementation of the CDrGrafFrame class
//

#include "stdafx.h"

#include "Def_Mous.h"
#include "Def_View.h"
/////////////////////
//#include "stdio.h"
#include "Banner.h"
#include <time.h>
#include "clock.h"
/////////////////////
#include "drgraf.h"
#include "drgracfm.h"
/////////////////////
#include "drgradoc.h"
#include "ObjMgr.h"
///////////////////// ElemObjects
#include "Def_Elem.h"
#include "Def_IGen.h"
#include "IGenBox.h"
#include "CntlBox.h"
#include "EDimBox.h"
/////////////////////////////////////////////// Dialogs
//#include "MDlgrsrc.h"
#include "UserMsg.h"                     // resource for GoodBy Id etc. NodIn etc
#include "ProbElemDim.h"				// Dlg for Prob/Elem Dimension Limits
/////////////////////
#include "12view.h"
#include "23view.h"
#include "31view.h"
#include "3Dview.h"
#include "dataview.h"
#include "MsDataVu.h"
#include "DeckView.h"
#include "SpDrawVu.h"
#include "drSplit.h"	// splitter frame for Auxilliary View (4 way)
#include "DrTreeVu.h"
#include "Splitter.h"	// splitter frame for FormData View (3 way)
///////////////////// SpecObjs
#include "Def_Spec.h" 
#include "SDlgMgr.h"
#include "Booleans.h"
#include "DrFont.h"
/////////////////////
#include "drgrafrm.h"
#include "Splash.h"
/////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
//////////////////////
enum TIMER
{
	TM_CLOCK,
	TM_BANNER,
	TM_MEMORY
};	
/////////////////////////////////////////////////////////////////////////////
// CDrGrafFrame
// NOTE:	ON_WM_WININICHANGE() is OBSOLETE from VC++ 5.0 Ver
//////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CDrGrafFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CDrGrafFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CDrGrafFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_DECK_DREAMPIPE, OnDeckDreampipe)
	ON_UPDATE_COMMAND_UI(IDM_DECK_DREAMPIPE, OnUpdateDeckDreampipe)
	ON_COMMAND(IDM_DECK_SAP, OnDeckSap)
	ON_UPDATE_COMMAND_UI(IDM_DECK_SAP, OnUpdateDeckSap)
	ON_COMMAND(IDM_DECK_TAB, OnDeckTab)
	ON_UPDATE_COMMAND_UI(IDM_DECK_TAB, OnUpdateDeckTab)
	ON_COMMAND(IDM_OPTION_AXISON, OnOptionAxison)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_AXISON, OnUpdateOptionAxison)
	ON_COMMAND(IDM_OPTION_DIALOGON, OnOptionDialogon)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_DIALOGON, OnUpdateOptionDialogon)
	ON_COMMAND(IDM_OPTION_PENCHANGE, OnOptionPenchange)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_PENCHANGE, OnUpdateOptionPenchange)
	ON_COMMAND(IDM_OPTION_REFRESH, OnOptionRefresh)
	ON_COMMAND(IDM_OPTION_RUBBERBAND, OnOptionRubberband)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_RUBBERBAND, OnUpdateOptionRubberband)
	ON_COMMAND(IDM_VIEW_12VIEW, OnView12view)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_12VIEW, OnUpdateView12view)
	ON_COMMAND(IDM_VIEW_23VIEW, OnView23view)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_23VIEW, OnUpdateView23view)
	ON_COMMAND(IDM_VIEW_31VIEW, OnView31view)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_31VIEW, OnUpdateView31view)
	ON_COMMAND(IDM_VIEW_3DVIEW, OnView3dview)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_3DVIEW, OnUpdateView3dview)
	ON_COMMAND(IDM_VIEW_DATAVIEW, OnViewDataview)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_DATAVIEW, OnUpdateViewDataview)
	ON_COMMAND(IDM_VIEW_MESHDATAVIEW, OnViewMeshDataview)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MESHDATAVIEW, OnUpdateViewMeshDataview)
	ON_COMMAND(IDM_VIEW_DECKVIEW, OnViewDeckview)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_DECKVIEW, OnUpdateViewDeckview)
	ON_COMMAND(IDM_VIEW_CNTLBOX, OnViewCntlbox)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_CNTLBOX, OnUpdateViewCntlbox)
	ON_COMMAND(IDM_VIEW_GENBOX, OnViewGenbox)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_GENBOX, OnUpdateViewGenbox)
	ON_COMMAND(IDM_VIEW_DRAWBOX, OnViewDrawbox)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_DRAWBOX, OnUpdateViewDrawbox)
	ON_COMMAND(IDM_VIEW_S_BAR_BOT, OnViewSBarBot)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_S_BAR_BOT, OnUpdateViewSBarBot)
	ON_COMMAND(IDM_VIEW_S_BAR_TOP, OnViewSBarTop)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_S_BAR_TOP, OnUpdateViewSBarTop)
	ON_COMMAND(IDM_SPEC_PAPER, OnSpecPaper)
	ON_COMMAND(IDM_SPEC_PRECISION, OnSpecPrecision)
	ON_COMMAND(IDM_SPEC_SCALEFACTOR, OnSpecScalefactor)
	ON_COMMAND(IDM_SPEC_UNITS, OnSpecUnits)
	ON_WM_TIMER()
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(IDM_OPTION_AUTOACCEPTON, OnOptionAutoacceptOn)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_AUTOACCEPTON, OnUpdateOptionAutoacceptOn)
	ON_COMMAND(IDM_OPTION_SPAWNON, OnOptionSpawnOn)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_SPAWNON, OnUpdateOptionSpawnOn)
	ON_COMMAND(IDM_OPTION_BLINEON, OnOptionBlineOn)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_BLINEON, OnUpdateOptionBlineOn)
	ON_COMMAND(IDM_OPTION_SINGLESEGON, OnOptionSingleSegOn)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_SINGLESEGON, OnUpdateOptionSingleSegOn)
	ON_COMMAND(IDM_VIEW_INPUTSTATUS_CONTROLS, OnViewInputstatusControls)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_INPUTSTATUS_CONTROLS, OnUpdateViewInputstatusControls)
	ON_COMMAND(IDM_VIEW_INPUTSTATUS_DECORATORS, OnViewInputstatusDecorators)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_INPUTSTATUS_DECORATORS, OnUpdateViewInputstatusDecorators)
	ON_COMMAND(IDM_VIEW_INPUTSTATUS_GENERATOR, OnViewInputstatusGenerator)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_INPUTSTATUS_GENERATOR, OnUpdateViewInputstatusGenerator)
	ON_COMMAND(IDM_VIEW_INPUTSTATUS_OPERATIONS, OnViewInputstatusOperations)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_INPUTSTATUS_OPERATIONS, OnUpdateViewInputstatusOperations)
	ON_COMMAND(IDM_VIEW_INPUTSTATUS_CURRENT, OnViewInputstatusCurrent)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_INPUTSTATUS_CURRENT, OnUpdateViewInputstatusCurrent)
	ON_COMMAND(IDM_VIEW_OPERBOX, OnViewOperbox)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_OPERBOX, OnUpdateViewOperbox)
	ON_COMMAND(IDM_WINDOW_NEW_3D_VIEW, OnWindowNew3dView)
	ON_UPDATE_COMMAND_UI(IDM_WINDOW_NEW_3D_VIEW, OnUpdateWindowNew3dView)
	ON_COMMAND(IDM_DEBUG_CALCTIME, OnDebugCalctime)
	ON_UPDATE_COMMAND_UI(IDM_DEBUG_CALCTIME, OnUpdateDebugCalctime)
	ON_COMMAND(IDM_VIEW_ALLVIEW, OnViewAllview)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_ALLVIEW, OnUpdateViewAllview)
	ON_COMMAND(IDM_VIEW_SPECTRA, OnViewSpectra)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_SPECTRA, OnUpdateViewSpectra)
	ON_UPDATE_COMMAND_UI(IDM_MODE_AUXILLIARY_SPATIAL, OnUpdateModeAuxilliarySpatial)
	ON_COMMAND(IDM_MODE_AUXILLIARY_SPECTRAL, OnModeAuxilliarySpectral)
	ON_UPDATE_COMMAND_UI(IDM_MODE_AUXILLIARY_SPECTRAL, OnUpdateModeAuxilliarySpectral)
	ON_COMMAND(IDM_MODE_AUXILLIARY_TEMPORAL, OnModeAuxilliaryTemporal)
	ON_UPDATE_COMMAND_UI(IDM_MODE_AUXILLIARY_TEMPORAL, OnUpdateModeAuxilliaryTemporal)
	ON_COMMAND(IDM_OPTION_SNAPON_OBJMERG, OnOptionSnaponObjmerg)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_SNAPON_OBJMERG, OnUpdateOptionSnaponObjmerg)
	ON_COMMAND(IDM_VIEW_DATABASE_FORMDATA, OnViewDatabaseFormdata)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_DATABASE_FORMDATA, OnUpdateViewDatabaseFormdata)
	ON_COMMAND(IDM_SPECS_TOLERANCES, OnSpecsTolerances)
	//}}AFX_MSG_MAP
	ON_MESSAGE(ID_OPTION_MODE,OnOptionMode)
	ON_MESSAGE(ID_RESET_VASKID,OnResetVaskID)
	ON_MESSAGE(ID_RESET_MASKID,OnResetMaskID)
	ON_MESSAGE(ID_RESET_TASKID,OnResetTaskID)
	ON_MESSAGE(ID_RESET_XASKID,OnResetXaskID)
	ON_MESSAGE(ID_UPDATE_STATCNTLS,OnUpdateStatCntls)
	ON_MESSAGE(ID_RESET_IGENOPEN,OnResetIGenOpen)
	ON_MESSAGE(ID_RESET_CNTLOPEN,OnResetCntlOpen)
	ON_MESSAGE(ID_RESET_IGENOPEN_MESH,OnResetIGenOpen_Mesh)
	ON_MESSAGE(ID_RESET_CNTLOPEN_MESH,OnResetCntlOpen_Mesh)
	ON_MESSAGE(ID_RESET_MODELESS,OnResetModeLess)
	ON_MESSAGE(ID_RESET_MODELESS_MESH,OnResetModeLess_Mesh)
	ON_MESSAGE(ID_RESET_IGENOPEN_AUXI,OnResetIGenOpen_Auxi)
	ON_MESSAGE(ID_RESET_CNTLOPEN_AUXI,OnResetCntlOpen_Auxi)
	ON_MESSAGE(ID_RESET_MODELESS_AUXI,OnResetModeLess_Auxi)
	ON_MESSAGE(ID_ACTIVE_FANDMIN,OnCreateorActivateF_MIn)
	ON_MESSAGE(ID_UPDATE_FANDMIN,OnUpdateF_MIn)
	ON_MESSAGE(ID_CANCEL_FANDMIN,OnCancelF_MIn)
	ON_MESSAGE(ID_GOODBYE_FANDMIN,OnGoodByeF_MIn)
	ON_MESSAGE(ID_ACTIVE_DANDRIN,OnCreateorActivateD_RIn)
	ON_MESSAGE(ID_UPDATE_DANDRIN,OnUpdateD_RIn)
	ON_MESSAGE(ID_CANCEL_DANDRIN,OnCancelD_RIn)
	ON_MESSAGE(ID_GOODBYE_DANDRIN,OnGoodByeD_RIn)
	ON_MESSAGE(ID_ACTIVE_PRESSIN,OnCreateorActivatePrsIn)
	ON_MESSAGE(ID_UPDATE_PRESSIN,OnUpdatePrsIn)
	ON_MESSAGE(ID_CANCEL_PRESSIN,OnCancelPrsIn)
	ON_MESSAGE(ID_GOODBYE_PRESSIN,OnGoodByePrsIn)
	ON_MESSAGE(ID_ACTIVE_THERMIN,OnCreateorActivateThrIn)
	ON_MESSAGE(ID_UPDATE_THERMIN,OnUpdateThrIn)
	ON_MESSAGE(ID_CANCEL_THERMIN,OnCancelThrIn)
	ON_MESSAGE(ID_GOODBYE_THERMIN,OnGoodByeThrIn)
	ON_MESSAGE(ID_ACTIVE_LUMPWTIN,OnCreateorActivateLWtIn)
	ON_MESSAGE(ID_UPDATE_LUMPWTIN,OnUpdateLWtIn)
	ON_MESSAGE(ID_CANCEL_LUMPWTIN,OnCancelLWtIn)
	ON_MESSAGE(ID_GOODBYE_LUMPWTIN,OnGoodByeLWtIn)
	ON_MESSAGE(ID_ACTIVE_SUPIN,OnCreateorActivateSupIn)
	ON_MESSAGE(ID_UPDATE_SUPIN,OnUpdateSupIn)
	ON_MESSAGE(ID_CANCEL_SUPIN,OnCancelSupIn)
	ON_MESSAGE(ID_GOODBYE_SUPIN,OnGoodByeSupIn)
	ON_MESSAGE(ID_ACTIVE_NODIN,OnCreateorActivateNodIn)
	ON_MESSAGE(ID_UPDATE_NODIN,OnUpdateNodIn)
	ON_MESSAGE(ID_CANCEL_NODIN,OnCancelNodIn)
	ON_MESSAGE(ID_GOODBYE_NODIN,OnGoodByeNodIn)
	ON_MESSAGE(ID_ACTIVE_LQCIN,OnCreateorActivateLQCIn)
	ON_MESSAGE(ID_UPDATE_LQCIN,OnUpdateLQCIn)
	ON_MESSAGE(ID_CANCEL_LQCIN,OnCancelLQCIn)
	ON_MESSAGE(ID_GOODBYE_LQCIN,OnGoodByeLQCIn)
	ON_MESSAGE(ID_ACTIVE_CRCIN,OnCreateorActivateCrcIn)
	ON_MESSAGE(ID_UPDATE_CRCIN,OnUpdateCrcIn)
	ON_MESSAGE(ID_CANCEL_CRCIN,OnCancelCrcIn)
	ON_MESSAGE(ID_GOODBYE_CRCIN,OnGoodByeCrcIn)
	ON_MESSAGE(ID_ACTIVE_PATIN,OnCreateorActivatePatIn)
	ON_MESSAGE(ID_UPDATE_PATIN,OnUpdatePatIn)
	ON_MESSAGE(ID_CANCEL_PATIN,OnCancelPatIn)
	ON_MESSAGE(ID_GOODBYE_PATIN,OnGoodByePatIn)
	ON_MESSAGE(ID_ACTIVE_SOLIN,OnCreateorActivateSolIn)
	ON_MESSAGE(ID_UPDATE_SOLIN,OnUpdateSolIn)
	ON_MESSAGE(ID_CANCEL_SOLIN,OnCancelSolIn)
	ON_MESSAGE(ID_GOODBYE_SOLIN,OnGoodByeSolIn)
	ON_MESSAGE(ID_ACTIVE_O3DIN,OnCreateorActivateO3DIn)
	ON_MESSAGE(ID_UPDATE_O3DIN,OnUpdateO3DIn)
	ON_MESSAGE(ID_CANCEL_O3DIN,OnCancelO3DIn)
	ON_MESSAGE(ID_GOODBYE_O3DIN,OnGoodByeO3DIn)
	ON_MESSAGE(ID_ACTIVE_CREIN,OnCreateorActivateCreIn)
	ON_MESSAGE(ID_UPDATE_CREIN,OnUpdateCreIn)
	ON_MESSAGE(ID_CANCEL_CREIN,OnCancelCreIn)
	ON_MESSAGE(ID_GOODBYE_CREIN,OnGoodByeCreIn)
	ON_MESSAGE(ID_ACTIVE_FE0IN,OnCreateorActivateFE0In)
	ON_MESSAGE(ID_UPDATE_FE0IN,OnUpdateFE0In)
	ON_MESSAGE(ID_CANCEL_FE0IN,OnCancelFE0In)
	ON_MESSAGE(ID_GOODBYE_FE0IN,OnGoodByeFE0In)
	ON_MESSAGE(ID_ACTIVE_FE1IN,OnCreateorActivateFE1In)
	ON_MESSAGE(ID_UPDATE_FE1IN,OnUpdateFE1In)
	ON_MESSAGE(ID_CANCEL_FE1IN,OnCancelFE1In)
	ON_MESSAGE(ID_GOODBYE_FE1IN,OnGoodByeFE1In)
	ON_MESSAGE(ID_ACTIVE_FE2IN,OnCreateorActivateFE2In)
	ON_MESSAGE(ID_UPDATE_FE2IN,OnUpdateFE2In)
	ON_MESSAGE(ID_CANCEL_FE2IN,OnCancelFE2In)
	ON_MESSAGE(ID_GOODBYE_FE2IN,OnGoodByeFE2In)
	ON_MESSAGE(ID_ACTIVE_FE3IN,OnCreateorActivateFE3In)
	ON_MESSAGE(ID_UPDATE_FE3IN,OnUpdateFE3In)
	ON_MESSAGE(ID_CANCEL_FE3IN,OnCancelFE3In)
	ON_MESSAGE(ID_GOODBYE_FE3IN,OnGoodByeFE3In)
	// Global help commands
	ON_COMMAND(ID_HELP_INDEX, CFrameWnd::OnHelpIndex)
	ON_COMMAND(ID_HELP_USING, CFrameWnd::OnHelpUsing)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpIndex)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
		ID_SEPARATOR,
	ID_FILE_PRINT,
	ID_APP_ABOUT,
	ID_CONTEXT_HELP,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
};

static UINT BASED_CODE top_indicators[] =
{

	ID_INDICATOR_TEXT_DRAWING,
	ID_SEPARATOR,			
	ID_INDICATOR_TEXT_LAYER,
	ID_SEPARATOR,			
	ID_INDICATOR_TEXT_UNIT,
	ID_SEPARATOR,			
	ID_SEPARATOR,			  // STRETCH
    ID_INDICATOR_TEXT_TIME,
	ID_SEPARATOR,			
    ID_INDICATOR_TEXT_DATE,
	ID_SEPARATOR

};

/////////////////////////////////////////////////////////////////////////////
// CDrGrafFrame construction/destruction

CDrGrafFrame::CDrGrafFrame()
{
#ifdef _DEBUG
	m_bDebugCTim	= FALSE;
	m_pDlg_CTim		= NULL;
#endif
	///////////////////////////////////////////// Menus
	if(!(GetInitMenu()->m_hMenu))
		GetInitMenu()->LoadMenu(IDR_MAINFRAME);
	if(!(GetInputMenu()->m_hMenu))
		GetInputMenu()->LoadMenu(IDR_INPUTMENU);
	if(!(GetOutputMenu()->m_hMenu))
		GetOutputMenu()->LoadMenu(IDR_OUTPUTMENU);
	///////////////////////////////
	m_OpMode		= OP_INPUT;	//default menu selection
	////////////////////////////////////////////// ToolBoxes
    m_bCntlBox		= TRUE;    // CntlBox Active
    m_nObjectType	= ELEMENT;
	m_bDrawBox		= FALSE;    // DrawBox InActive
	m_bIGenBox		= TRUE;     // IGenBox Active
	//////////////////////////
	m_bMeshMode		= FALSE;
	m_bMGenBox		= FALSE;    // MGenBox InActive
	m_bAuxiMode		= FALSE;
	m_CurrentModeID = MO_GENERATOR;
	m_strModeID		= "GENERATOR Mode";
	//////////////////////////////////////////////
	m_strCurrID		= "Go Ahead! Make My Day!!@CLICK Right Button ON START";
	///////////
/*
	m_CurrentOperID = COP_CREATE;
	m_strOperID		= "CREATE";
	m_CurrentCntlID = ELEMENT;
	m_strCntlID		= "ELEMENT";
	m_CurrentIGenID = NODE;
	m_strIGenID		= "NODE";
*/
	m_CurrentOperID = UNONE;
	m_strOperID		= "START";
	m_CurrentCntlID = UNONE;
	m_strCntlID		= "UNKNOWN";
	m_CurrentIGenID = UNONE;
	m_strIGenID		= "UNKNOWN";
	////////////////////////////
	m_pLastStatCntlHit = NULL;
	////////////////////////////
	int i;
	//////
	for(i=0;i<MAX_IGENITEMS;i++)
		ReSetIGenOpen(FALSE,i);
	///
	for(i=0;i<MAX_CNTLITEMS;i++)
		ReSetCntlOpen(FALSE,i);
	////////////////////////////
	m_nToolType		= m_CurrentIGenID;
	////////////////////////////////// NodeBox
	SetMouseBoxType(NODEBOX);
}

CDrGrafFrame::~CDrGrafFrame()
{
#ifdef _DEBUG
	/////////////////////////////////// Modeless Dialogs
	if(m_pDlg_CTim)
	{
		if(m_pDlg_CTim->m_hWnd)
			m_pDlg_CTim->DestroyWindow();
		///////////////////
		delete m_pDlg_CTim;
	}
#endif	
	/////////////////////////////////// Menu
	if(GetInitMenu()->m_hMenu)
		GetInitMenu()->DestroyMenu();
	if(GetInputMenu()->m_hMenu)
		GetInputMenu()->DestroyMenu();
	if(GetOutputMenu()->m_hMenu)
		GetOutputMenu()->DestroyMenu();
	/////////////////////////////////// StatusBars
	if(m_wndSBarTop.m_hWnd)
		m_wndSBarTop.DestroyWindow();
	if(m_wndSBarBot.m_hWnd)
		m_wndSBarBot.DestroyWindow();
	if(m_wndStatusBar.m_hWnd)
		m_wndStatusBar.DestroyWindow();
	if(m_wndToolBar.m_hWnd)
		m_wndToolBar.DestroyWindow();
	///////////////////
/*
	if(m_pCo3InDlg->m_hWnd)
		m_pCo3InDlg->DestroyWindow();
	delete m_pCo3InDlg; 
*/
		
}
void CDrGrafFrame::SwitchMenu( UINT nMenuNum)
{
/*
	HMENU hMenuBar	= GetInputMenu()->GetSafeHmenu( );
	HMENU hWinBar	= GetWindowMenuPopup( hMenuBar );
	CMenu WinPopUpMenu;
	WinPopUpMenu.FromHandle(hWinBar);
*/
	////////////////////////
	switch(nMenuNum)
	{
		case IDR_MAINFRAME:

//			MDISetMenu(GetInitMenu(),&WinPopUpMenu); // 
			MDISetMenu(GetInitMenu(),NULL); // 
//			SetMenu(GetInitMenu()); //
			m_CurMenuID = IDR_MAINFRAME; 
			break;
			
		case IDR_INPUTMENU:
		

//			MDISetMenu(GetInputMenu(),&WinPopUpMenu); // 
			MDISetMenu(GetInputMenu(),NULL); // 
//			SetMenu(GetInputMenu()); //
			m_CurMenuID = IDR_INPUTMENU; 
			break;
		
		case IDR_OUTPUTMENU:
		
//			MDISetMenu(GetOutputMenu(),&WinPopUpMenu); // 
			MDISetMenu(GetOutputMenu(),NULL); // 
//			SetMenu(GetOutputMenu()); //
			m_CurMenuID = IDR_OUTPUTMENU; 
			break;

		case IDR_AUXINPUT:		
		

//			MDISetMenu(GetInputMenu(),&WinPopUpMenu); // 
			MDISetMenu(GetAuxInputMenu(),NULL); // 
//			SetMenu(GetInputMenu()); //
			m_CurMenuID = IDR_AUXINPUTMENU; 
			break;
		
		default:
			break;
	}
	//////////////			
	DrawMenuBar();
	////////////// 
}

CWnd* CDrGrafFrame::GetMessageBar() 
{
	//overrides of CFrameWnd to redirect Message to our StatusBar
	CBotStatusBar* pBar = (CBotStatusBar*)GetDescendantWindow(IDS_BOT_STATUSBAR, TRUE);

//	if (pBar->GetStyle() && WS_VISIBLE)
	if (MDIGetActive())
		return GetDescendantWindow(IDS_BOT_STATUSBAR, TRUE);
	else
		return GetDescendantWindow(AFX_IDW_STATUS_BAR, TRUE);
		
}

int CDrGrafFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	////////////////////////////////////////////////////////// DefaultToolBar
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE("CDrGrafFrame::OnCreate\nFailed to create toolbar\n");
		return -1;      // fail to create
	}
	RecalcLayout();
	////////////////////////////////////////////////////////// Init StatusBar
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("CDrGrafFrame::OnCreate\nFailed to create status bar\n");
		return -1;      // fail to create
	}
	RecalcLayout();
	////////////////////////////////////////////////////////// Top StatusBar
	if (!m_wndSBarTop.Create(this,WS_CHILD|CBRS_TOP,
			IDS_TOP_STATUSBAR) ||
		!m_wndSBarTop.SetIndicators(top_indicators,
		  sizeof(top_indicators)/sizeof(UINT)))
	{
		TRACE("CDrGrafFrame::OnCreate\nFailed to create Top status bar\n");
		return -1;		// fail to create
	}
	////////////////////////////////////////////////////////// Bottom StatusBar
	if (!m_wndSBarBot.Create(this,WS_CHILD|CBRS_BOTTOM,
			IDS_BOT_STATUSBAR) ||
		!m_wndSBarBot.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("CDrGrafFrame::OnCreate\nFailed to create Bottom status bar\n");
		return -1;		// fail to create
	}
	/////////////////// Get the 0 pane ready
	CString str;
	UINT nID, nStyle;
	int cxWidth;

	m_wndSBarBot.GetPaneInfo(0,nID,nStyle,cxWidth);
	m_wndSBarBot.SetPaneInfo(0,nID,SBPS_STRETCH,cxWidth);
	////////////////////////////////////////////////////////// ToolBoxes
	CRect BoxRect;
	BoxRect.left = BoxRect.top = BoxRect.right = BoxRect.bottom = 0;
	///////////////////////////////////////
	if(!(GetOperBox()->Create((CWnd*)this,BoxRect))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create OperBox\n");
		return -1;       // fail to create
	}
	///////////////////////////////////////
	if(!(GetIGenBox()->Create((CWnd*)this,BoxRect))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create IGenBox\n");
		return -1;       // fail to create
	}
	///////////////////////////////////////
	if(!(GetMGenBox()->Create((CWnd*)this,BoxRect))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create MGenBox\n");
		return -1;       // fail to create
	}
	///////////////////////////////////////
	if(!(GetEDimBox()->Create((CWnd*)this,BoxRect))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create EDimBox\n");
		return -1;       // fail to create
	}
	///////////////////////////////////////
	if(!(GetCntlBox()->Create((CWnd*)this,BoxRect))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create CntlBox\n");
		return -1;       // fail to create
	}
	////////////////////////////
	if(!(GetDrawBox()->Create((CWnd*)this,BoxRect))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create DrawBox\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// Mode Static
	if(!(GetModeStat()->Create((CWnd*)this,BoxRect,IDS_MODESTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create ModeStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// Cntl Static
	if(!(GetCntlStat()->Create((CWnd*)this,BoxRect,IDS_CNTLSTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create CntlStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// IGen Static
	if(!(GetIGenStat()->Create((CWnd*)this,BoxRect,IDS_IGENSTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create IGenStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// Oper Static
	if(!(GetCurrStat()->Create((CWnd*)this,BoxRect,IDS_CURRSTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create CurrStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// Oper Static
	if(!(GetOperStat()->Create((CWnd*)this,BoxRect,IDS_OPERSTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create OperStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// Snap Static
	if(!(GetSnapStat()->Create((CWnd*)this,BoxRect,IDS_SNAPSTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create SnapStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// Spawn Static
	if(!(GetSpawnStat()->Create((CWnd*)this,BoxRect,IDS_SPAWNSTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create SpawnStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// BLine Static
	if(!(GetBLineStat()->Create((CWnd*)this,BoxRect,IDS_BLINESTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create BLineStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// BLine Static
	if(!(GetAutoAcceptStat()->Create((CWnd*)this,BoxRect,IDS_AUTOACCEPTSTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create AutoAcceptStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// BLine Static
	if(!(GetSingleSegStat()->Create((CWnd*)this,BoxRect,IDS_SINGLESEGSTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create SingleSegStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// Draw Static
	if(!(GetDrawStat()->Create((CWnd*)this,BoxRect,IDS_DRAWSTAT))  )
	{
		TRACE0("CDrGrafFrame::OnCreate\nFailed to create DrawStat\n");
		return -1;       // fail to create
	}
	////////////////////////////////////////////////////////////////////// Setup Timers	
	////////////////////////////////////////////////////////// Clock Timer
	if (!SetTimer(TM_CLOCK, 1000 /*1000 msec = 1 sec*/, NULL))
	{
		MessageBox("Not enough timers available for this window.",
				"Frame:OnCreate", MB_ICONEXCLAMATION | MB_OK);

		// signal creation failure...
		return -1;
	} 
	////////////////////////////////////////////////////////// Banner Timer
	if (!SetTimer(TM_BANNER, 5000 /*1000 msec = 1 sec*/, NULL))
	{
		MessageBox("Not enough timers available for this window.",
				"Frame:OnCreate", MB_ICONEXCLAMATION | MB_OK);

		// signal creation failure...
		return -1;
	} 
	////////////////////////////////////////////////////////// Memory Timer
	if (!SetTimer(TM_MEMORY, 1000 /*1000 msec = 1 sec*/, NULL))
	{
		MessageBox("Not enough timers available for this window.",
				"Frame:OnCreate", MB_ICONEXCLAMATION | MB_OK);

		// signal creation failure...
		return -1;
	} 
	////////////////////////////
	// CG: The following line was added by the Splash Screen component.
	CSplashCom::ShowSplashScreen(this);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CDrGrafFrame diagnostics

#ifdef _DEBUG
void CDrGrafFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CDrGrafFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG
/*
afx_msg LRESULT CDrGrafFrame::OnCommandHelp(WPARAM, LPARAM lParam)
{
	
		WM_COMMANDHELP is an MFC private Windows message that is received by the active window
		when Help is requested. When the window receives this message, it may call
		CWinApp::WinHelp with context that matches the window's internal state. 
		lParam   contains the currently available Help context. lParam is zero 
		if no Help context has been determined yet. An implementation of OnCommandHelp
		can use the context ID in lParam to determine a “better” context or can just
		pass it to CWinApp::WinHelp.
		wParam   is not used and will be zero.
		If the OnCommandHelp function calls CWinApp::WinHelp, 
		it should return TRUE. Returning TRUE stops the routing of this command
		to other classes (base classes
	
	switch(lParam)
	{
		case 
*/
/////////////////////////////////////////////////////////////////////////////
void CDrGrafFrame::Init()   // Called by Open Document.Init
{
//
#ifdef _DEBUG
	/////////////////////////////////////////////////////////////////// Object
	m_pDlg_CTim	= new CDlg_CTim(this);
	/////////////////////////////////////////////////////////////////// Create
	if(m_pDlg_CTim->GetSafeHwnd() ==0)	// not created already
	{
		m_pDlg_CTim->Create();
		CRect BoxRect;
		CWnd  wndTopMost;
		m_pDlg_CTim->GetWindowRect(&BoxRect);
		SizeRectDlgIn(BoxRect);
		//////////////////////////////////////////////////////////////
		m_pDlg_CTim->SetWindowPos(&wndTopMost,BoxRect.left,BoxRect.top,BoxRect.Width(),
                        BoxRect.Height(),SWP_NOZORDER|SWP_HIDEWINDOW);
		//////////////////////////////////////////////////////////////
	}
	else
		m_pDlg_CTim->SetActiveWindow();
#endif
//	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CDrFont* pDrFont = (CDrFont*)pObjectMgr->GetSpecObject(DRFONT);
	/////////////////////////////////////////////////////////////////// System Sizes
	int cxBorder	= ::GetSystemMetrics(SM_CXBORDER);
	int cyBorder	= ::GetSystemMetrics(SM_CYBORDER);
	int cxVScroll	= ::GetSystemMetrics(SM_CXVSCROLL);
	int cxHScroll	= ::GetSystemMetrics(SM_CXHSCROLL);
	int cyMenuSize	= ::GetSystemMetrics(SM_CYMENUSIZE);
	int cyEdge		= ::GetSystemMetrics(SM_CYEDGE);
	int cyFrame		= ::GetSystemMetrics(SM_CYSIZEFRAME);
	int cyCapSize	= ::GetSystemMetrics(SM_CYSIZE);
	int cxScreen	= ::GetSystemMetrics(SM_CXSCREEN);	
	int cyScreen	= ::GetSystemMetrics(SM_CYSCREEN);
	//////////////////////////////////////////////////
	UINT Width12	= cxScreen;	// for adjustment of View12 Size
	UINT Left12	= 1;
	////////////////////////////////////////////////////////////// ProbDimLim & ElemDimLim
	m_ProbDimLim	= PDL_TWO;	// Default
	m_ElemDimLim 	= EDL_TWO;	// Default
	//////////////////////////////////
	CProbElemDim Dlg;
	//
	Dlg.m_PDim = m_ProbDimLim;
	Dlg.m_EDim = m_ElemDimLim;
	////////////////////////////
	if(Dlg.DoModal() == IDOK)
	{
		m_ProbDimLim	= Dlg.m_PDim;
		m_ElemDimLim 	= Dlg.m_EDim;
	}
	/////////////////////////// MouseMgr: Init : AUXILLIARY
//	GetMouAXMgr()->InitDlgIn();	// ProbDimLim & ElemDimLim is Done
	/////////////////////////// MouseMgr: Init
	GetMouseMgr()->InitDlgIn();	// ProbDimLim & ElemDimLim is Done
	/////////////////////////// CreOpMgr: Init
	GetCreOpMgr()->InitDlgIn();	// ProbDimLim & ElemDimLim is Done
	/////////////////////////// CreOMMgr: Init
	GetCreOMMgr()->InitDlgIn();	// ProbDimLim & ElemDimLim is Done
	/////////////////////////// PostMgr: Init
	GetPostMgr()->InitDlgIn();	// ProbDimLim & ElemDimLim is Done
	/////////////////////////// EditMgr: Init
	GetEditMgr()->GetDLDMouse()->SetProbLim(GetProbDimLim());
	GetEditMgr()->GetDLDMouse()->SetElemLim(GetElemDimLim());
	/////////////////////////// MditMgr: Init
	GetMditMgr()->GetDLDMouse()->SetProbLim(GetProbDimLim());
	GetMditMgr()->GetDLDMouse()->SetElemLim(GetElemDimLim());
	/////////////////////////// DlitMgr: Init
	GetDelMgr()->GetDLDMouse()->SetProbLim(GetProbDimLim());
	GetDelMgr()->GetDLDMouse()->SetElemLim(GetElemDimLim());
	////////////////////////////////////////////////////////////////////// StatusBars 
	GetStatusBar()->ShowWindow(SW_HIDE);
	RecalcLayout();
	GetSBarTop()->Init();
	GetSBarTop()->ShowWindow(SW_SHOW);
	RecalcLayout();
	GetSBarBot()->Init();
	GetSBarBot()->ShowWindow(SW_SHOW);
	RecalcLayout();
	////////////////////////
	CRect STopRect,SBotRect;
	GetSBarTop()->GetWindowRect(&STopRect); // screen Coords
	GetSBarBot()->GetWindowRect(&SBotRect); // screen Coords
	////////////////////////////////////////////////////////////// Menu
	if(m_OpMode == OP_INPUT)
		SwitchMenu(IDR_INPUTMENU);
	else	  
	if(m_OpMode == OP_OUTPUT)
	{
		SwitchMenu(IDR_OUTPUTMENU);
		return;
	}
	///////////////////////////////
	CRect BoxRect;
	int Boxwidth,Boxheight; 
	///////////////////////////////////////////////////////// ToolBoxes Creation
	/////////////////////////////////////////////////////////////// DrawBox 
	Boxwidth  		= (int)GetDrawBox()->GetWidth();
	Boxheight 		= (int)GetDrawBox()->GetHeight();

   	BoxRect.left   = 0;
   	BoxRect.right  = BoxRect.left + Boxwidth; //
   	BoxRect.top    = 0;   //
   	BoxRect.bottom = BoxRect.top   + Boxheight;
//	ClientToScreen(&Rect);
	::AdjustWindowRect(&BoxRect,WS_BORDER|WS_CAPTION,FALSE);
	//////////////////////////////////////////// OutToOut
	Boxwidth  = BoxRect.Width();
	Boxheight = BoxRect.Height(); 
	////////////////////////////////////////////////////////
   	BoxRect.right  = STopRect.right - cxBorder; //
   	BoxRect.top    = STopRect.bottom + 1;   //
   	BoxRect.left   = STopRect.right - Boxwidth;
   	BoxRect.bottom = BoxRect.top   + Boxheight;
	//////////////////////////////////////////////////////////////
	GetDrawBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                     BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_HIDEWINDOW);
	////////////////////////////////////////////////////////////// IGenBox 
	Boxwidth  = (int)GetIGenBox()->GetWidth();
	Boxheight = (int)GetIGenBox()->GetHeight(); 

   	BoxRect.left   = 0;
   	BoxRect.right  = BoxRect.left + Boxwidth; //
   	BoxRect.top    = 0;   //
   	BoxRect.bottom = BoxRect.top   + Boxheight;
//	ClientToScreen(&Rect);
	::AdjustWindowRect(&BoxRect,WS_BORDER|WS_CAPTION,FALSE);
	//////////////////////////////////////////// OutToOut
	Boxwidth  = BoxRect.Width();
	Boxheight = BoxRect.Height();
	////////////////////////////// View12 Adjustment
	Width12	-= Boxwidth; 
	////////////////////////////////////////////////////////
   	BoxRect.right  = STopRect.right - cxBorder; //
   	BoxRect.top    = STopRect.bottom + 1;   //
   	BoxRect.left   = BoxRect.right - Boxwidth;
   	BoxRect.bottom = BoxRect.top   + Boxheight;
	//////////////////////////////////////////////////////////////
	if(m_OpMode == OP_INPUT)
	{
		GetIGenBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                     BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_HIDEWINDOW);
		if(IsMeshMode())
			GetMGenBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                     BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_HIDEWINDOW);
		else
			GetMGenBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                     BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_HIDEWINDOW);
	}
	else
	if(m_OpMode == OP_OUTPUT)
	{
		GetIGenBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                     BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_HIDEWINDOW);
	}
	////////////////////////////////////////////////////////////// CntlBox 
	Boxwidth  = (int)GetCntlBox()->GetWidth();
	Boxheight = (int)GetCntlBox()->GetHeight(); 

   	BoxRect.left   = 0;
   	BoxRect.right  = BoxRect.left + Boxwidth; //
   	BoxRect.top    = 0;   //
   	BoxRect.bottom = BoxRect.top   + Boxheight;
//	ClientToScreen(&Rect);
	::AdjustWindowRect(&BoxRect,WS_BORDER|WS_CAPTION,FALSE);
	//////////////////////////////////////////// OutToOut
	Boxwidth  = BoxRect.Width();
	Boxheight = BoxRect.Height(); 
	////////////////////////////// View12 Adjustment
	Width12	-= Boxwidth; 
	Left12	+= Boxwidth;
	////////////////////////////////////////////////////////
   	BoxRect.left   = cyBorder; //
   	BoxRect.right  = BoxRect.left + Boxwidth;
   	BoxRect.top    = STopRect.bottom + 1;  //
   	BoxRect.bottom = BoxRect.top  + Boxheight;
	//////////////////////////////////////////////////////////////
	if(m_OpMode == OP_INPUT)
	{
		GetCntlBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_HIDEWINDOW);
	}
	else
	if(m_OpMode == OP_OUTPUT)
	{
		GetCntlBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_HIDEWINDOW);
	}
	////////////////////////////////////////////////////////////// EDimBox 
	Boxwidth  = (int)GetEDimBox()->GetWidth();
	Boxheight = (int)GetEDimBox()->GetHeight(); 

   	BoxRect.left   = 0;
   	BoxRect.right  = BoxRect.left + Boxwidth; //
   	BoxRect.top    = 0;   //
   	BoxRect.bottom = BoxRect.top   + Boxheight;
//	ClientToScreen(&Rect);
	::AdjustWindowRect(&BoxRect,WS_BORDER|WS_CAPTION,FALSE);
	//////////////////////////////////////////// OutToOut
	Boxwidth  = BoxRect.Width();
	Boxheight = BoxRect.Height(); 
	////////////////////////////////////////////////////////
   	BoxRect.left   = cyBorder; //
   	BoxRect.right  = BoxRect.left + Boxwidth;
   	BoxRect.top    = STopRect.bottom + 1;  //
   	BoxRect.bottom = BoxRect.top  + Boxheight;
	//////////////////////////////////////////////////////////////
	GetEDimBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                       BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_HIDEWINDOW);
	////////////////////////////////////////////////////////////// MainBox(Operations) 
	Boxwidth  = (int)GetOperBox()->GetWidth();
	Boxheight = (int)GetOperBox()->GetHeight(); 
	
   	BoxRect.left   = 0;
   	BoxRect.right  = BoxRect.left + Boxwidth; //
   	BoxRect.top    = 0;   //
   	BoxRect.bottom = BoxRect.top   + Boxheight;
//	ClientToScreen(&Rect);
	::AdjustWindowRect(&BoxRect,WS_BORDER|WS_CAPTION,FALSE);
	//////////////////////////////////////////// OutToOut
	Boxwidth  = BoxRect.Width();
	Boxheight = BoxRect.Height(); 
	////////////////////////////////////////////////////////
   	BoxRect.left   = (cxScreen - Boxwidth)/2; //
   	BoxRect.right  = BoxRect.left + Boxwidth;
   	BoxRect.top    = SBotRect.top - cxHScroll - Boxheight - (SBotRect.top - STopRect.bottom)/10;  //
   	BoxRect.bottom = BoxRect.top  + Boxheight;
	//////////////////////////////////////////////////////////////
	GetOperBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                        BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_HIDEWINDOW);
	////////////////////////////////////////////////////////////////////////////// StatCntls
	LOGFONT lf = pDrFont->GetCurrentLogFont();
	//////////////////////////////////////////
	CPoint ptLeftTop;
	CRect clientRect,statRect;
	GetClientRect(&clientRect);
	ClientToScreen(&clientRect);
	/////////////////////////////////////////////////////////////
	CRect FrameRect;
	GetWindowRect(&FrameRect);
	///////////////////////////////////////// ModeStat
	ptLeftTop.x = clientRect.right - 130;  
	ptLeftTop.y = FrameRect.top + cyCapSize + 3;
//	ptLeftTop.x = clientRect.left + (clientRect.Width() - 102)/2;  
//	ptLeftTop.y = clientRect.bottom - 98 - 18;
	///////////////
	GetModeStat()->SetInfo(ptLeftTop,m_strModeID,PS_SOLID,0,RGB(0,0,0),RGB(255,0,255),
							130,20,lf,RGB(0,0,0));
	GetModeStat()->ReCalcLayOut();
	///////////////////////////////////////// CntlStat
	ptLeftTop.x = clientRect.left+4;  
	ptLeftTop.y = clientRect.bottom - 98 - 18;
	///////////////
	GetCntlStat()->SetInfo(ptLeftTop,m_strCntlID,PS_SOLID,0,RGB(0,0,0),RGB(255,0,0),
							102,96,lf,RGB(255,255,0));
	GetCntlStat()->ReCalcLayOut();
	///////////////////////////////////////// IGenStat
	ptLeftTop.x = clientRect.right - 102 - 4;  
	ptLeftTop.y = clientRect.bottom - 98 - 18;
	///////////////
	GetIGenStat()->SetInfo(ptLeftTop,m_strIGenID,PS_SOLID,0,RGB(0,0,0),RGB(0,0,255),
							102,96,lf,RGB(255,255,0));
	GetIGenStat()->ReCalcLayOut();
	//////////////////////////////////////////////////////////////////////////////////
	// OperStat: Again Repositioned in DrawView.cpp: OnInitialUpdate
	///////////////////////////////////////// OperStat
	ptLeftTop.x = clientRect.right - 400 - cyBorder;  
	ptLeftTop.y = clientRect.top - 38;
	///////////////
	GetOperStat()->SetInfo(ptLeftTop,m_strOperID,PS_SOLID,0,RGB(0,0,0),RGB(0,255,0),
							102,20,lf,RGB(0,0,0));
	GetOperStat()->ReCalcLayOut();
	///////////////////////////////////////// CurrStat		
	ptLeftTop.x = clientRect.left + (clientRect.Width() - 400)/2 - cyBorder;  
	ptLeftTop.y = FrameRect.top + cyCapSize + 20;
	///////////////
//	lf.lfHeight = 13;
//	lf.lfWeight = 400;
	GetCurrStat()->SetInfo(ptLeftTop,m_strCurrID,PS_SOLID,0,RGB(0,0,0),RGB(255,255,0),
							400,34,lf,RGB(0,0,0));
	GetCurrStat()->ReCalcLayOut();
	/////////////////////////////////////////
	UpdateStaticControls();
	///////////////////////////////////////// BLineStat
	ptLeftTop.x = clientRect.left + (clientRect.Width() - 102)/2 + 100;  
	ptLeftTop.y = FrameRect.top + 1;
	///////////////
	CString str;
	str = "BLine ON";
	GetBLineStat()->SetInfo(ptLeftTop,str,PS_SOLID,0,RGB(255,255,255),RGB(0,255,255),
//							102,60,
							102,20,
							lf,RGB(0,0,0));
	GetBLineStat()->ReCalcLayOut();
	///////////////////////////////////////// AutoAcceptStat
	ptLeftTop.x -= 110;  
	///////////////
	str = "AutoAccept OFF";
	GetAutoAcceptStat()->SetInfo(ptLeftTop,str,PS_SOLID,0,RGB(255,255,255),RGB(0,255,255),
							102,20,lf,RGB(0,0,0));
	GetAutoAcceptStat()->ReCalcLayOut();
	///////////////////////////////////////// SingleSegStat
	ptLeftTop.x += (110 + 102 + 8);  
	///////////////
	str = "SingleSeg ON";
	GetSingleSegStat()->SetInfo(ptLeftTop,str,PS_SOLID,0,RGB(255,255,255),RGB(0,255,255),
							102,20,lf,RGB(0,0,0));
	GetSingleSegStat()->ReCalcLayOut();
	///////////////////////////////////////// SpawnStat
	ptLeftTop.x -= (110 + 110 + 110);  
	///////////////
	str = "Copy ON";
	GetSpawnStat()->SetInfo(ptLeftTop,str,PS_SOLID,0,RGB(255,255,255),RGB(0,255,255),
							102,20,lf,RGB(0,0,0));
	GetSpawnStat()->ReCalcLayOut();
	///////////////////////////////////////// SnapStat
	ptLeftTop.x -= 110;  
	///////////////
	str = "Snap ON";
	GetSnapStat()->SetInfo(ptLeftTop,str,PS_SOLID,0,RGB(255,255,255),RGB(0,255,255),
							102,20,lf,RGB(0,0,0));
	GetSnapStat()->ReCalcLayOut();
	///////////////////////////////////////// 		
}
// /////////////////////////////////Helpers for saving/restoring window state

static char BASED_CODE szSection[] = "Settings";
static char BASED_CODE szWindowPos[] = "WindowPos";
static char szFormat[] = "%u,%u,%d,%d,%d,%d,%d,%d,%d,%d";

static BOOL PASCAL FAR ReadWindowPlacement(LPWINDOWPLACEMENT pwp)
//BOOL CDrGrafFrame::ReadWindowPlacement(LPWINDOWPLACEMENT pwp)
{
	CString strBuffer = AfxGetApp()->GetProfileString(szSection, szWindowPos);
	if (strBuffer.IsEmpty())
		return FALSE;

	WINDOWPLACEMENT wp;
	int nRead = sscanf(strBuffer, szFormat,
		&wp.flags, &wp.showCmd,
		&wp.ptMinPosition.x, &wp.ptMinPosition.y,
		&wp.ptMaxPosition.x, &wp.ptMaxPosition.y,
		&wp.rcNormalPosition.left, &wp.rcNormalPosition.top,
		&wp.rcNormalPosition.right, &wp.rcNormalPosition.bottom);

	if (nRead != 10)
		return FALSE;

	wp.length = sizeof wp;
	*pwp = wp;
	return TRUE;
}

static void PASCAL FAR WriteWindowPlacement(LPWINDOWPLACEMENT pwp)
//void CDrGrafFrame::WriteWindowPlacement(LPWINDOWPLACEMENT pwp)
	// write a window placement to settings section of app's ini file
{
	char szBuffer[sizeof("-32767")*8 + sizeof("65535")*2];

	sprintf(szBuffer, szFormat,
		pwp->flags, pwp->showCmd,
		pwp->ptMinPosition.x, pwp->ptMinPosition.y,
		pwp->ptMaxPosition.x, pwp->ptMaxPosition.y,
		pwp->rcNormalPosition.left, pwp->rcNormalPosition.top,
		pwp->rcNormalPosition.right, pwp->rcNormalPosition.bottom);

	AfxGetApp()->WriteProfileString(szSection, szWindowPos, szBuffer);
}

///////////////////////////////////////////////////////////////////////////// ModeLess Dialogs
void CDrGrafFrame::SizeRectDlgIn(CRect& BoxRect)
{
	
	/////////////////////////////////////////////////////////////////// System Sizes
	int cxBorder	= ::GetSystemMetrics(SM_CXBORDER);
	int cyBorder	= ::GetSystemMetrics(SM_CYBORDER);
	int cxVScroll	= ::GetSystemMetrics(SM_CXVSCROLL);
	int cyMenuSize	= ::GetSystemMetrics(SM_CYMENUSIZE);
	int cyEdge		= ::GetSystemMetrics(SM_CYEDGE);
	int cyFrame		= ::GetSystemMetrics(SM_CYSIZEFRAME);
	int cyCapSize	= ::GetSystemMetrics(SM_CYSIZE);
	///////////////////////////////
	CRect FrameRect;
	GetWindowRect(&FrameRect);
	/////////////////////////////////////////////////////////////// ...InBox 
	int Boxwidth  		= BoxRect.Width();
	int Boxheight 		= BoxRect.Height();
	///////////////////////////////////////
	BoxRect.top    = 1 + FrameRect.top + cyEdge + cyCapSize;   //		
	BoxRect.bottom = BoxRect.top	+ Boxheight; //
	BoxRect.right  = FrameRect.right - cxBorder;
	BoxRect.left   = BoxRect.right	- Boxwidth;
	////////////////////////////////
	return;
}
////////////////////////////////////////////////////////////////////////
long CDrGrafFrame::OnCreateorActivateF_MIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivateF_MIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeF_MIn(UINT wParam, long lParam)
{
	
	GetMouseMgr()->GetDLDMouse()->GoodByeF_MIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateF_MIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateF_MIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelF_MIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateF_MIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
////////////////////////////////////////////////////////////////////////
long CDrGrafFrame::OnCreateorActivateD_RIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivateD_RIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeD_RIn(UINT wParam, long lParam)
{
	
	GetMouseMgr()->GetDLDMouse()->GoodByeD_RIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateD_RIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateD_RIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelD_RIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateD_RIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
////////////////////////////////////////////////////////////////////////
long CDrGrafFrame::OnCreateorActivatePrsIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivatePrsIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByePrsIn(UINT wParam, long lParam)
{
	
	GetMouseMgr()->GetDLDMouse()->GoodByePrsIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdatePrsIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdatePrsIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelPrsIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdatePrsIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
////////////////////////////////////////////////////////////////////////
long CDrGrafFrame::OnCreateorActivateThrIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivateThrIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeThrIn(UINT wParam, long lParam)
{
	
	GetMouseMgr()->GetDLDMouse()->GoodByeThrIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateThrIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateThrIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelThrIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateThrIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
////////////////////////////////////////////////////////////////////////
long CDrGrafFrame::OnCreateorActivateLWtIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivateLWtIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeLWtIn(UINT wParam, long lParam)
{
	
	GetMouseMgr()->GetDLDMouse()->GoodByeLWtIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateLWtIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateLWtIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelLWtIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateLWtIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
////////////////////////////////////////////////////////////////////////
long CDrGrafFrame::OnCreateorActivateSupIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivateSupIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeSupIn(UINT wParam, long lParam)
{
	
	GetMouseMgr()->GetDLDMouse()->GoodByeSupIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateSupIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateSupIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelSupIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateSupIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
////////////////////////////////////////////////////////////////////////
long CDrGrafFrame::OnCreateorActivateNodIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivateNodIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeNodIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->GoodByeNodIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateNodIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateNodIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelNodIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CancelNodIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	
long CDrGrafFrame::OnCreateorActivateLQCIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivateLQCIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeLQCIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->GoodByeLQCIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateLQCIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateLQCIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelLQCIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CancelLQCIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	
long CDrGrafFrame::OnCreateorActivateCrcIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivateCrcIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeCrcIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->GoodByeCrcIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateCrcIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateCrcIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelCrcIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CancelCrcIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}

long CDrGrafFrame::OnCreateorActivatePatIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivatePatIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByePatIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->GoodByePatIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdatePatIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdatePatIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelPatIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CancelPatIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}

long CDrGrafFrame::OnCreateorActivateSolIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivateSolIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeSolIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->GoodByeSolIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateSolIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateSolIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelSolIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CancelSolIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}


long CDrGrafFrame::OnCreateorActivateO3DIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CreateorActivateO3DIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeO3DIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->GoodByeO3DIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateO3DIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->UpdateO3DIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelO3DIn(UINT wParam, long lParam)
{
	GetMouseMgr()->GetDLDMouse()->CancelO3DIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}

long CDrGrafFrame::OnCreateorActivateCreIn(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	if(IsMeshMode())
		GetCreOMMgr()->CreateorActivateCreIn(wParam, lParam);
	else
		GetCreOpMgr()->CreateorActivateCreIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeCreIn(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	if(IsMeshMode())
		GetCreOMMgr()->GoodByeCreIn(wParam, lParam);
	else
		GetCreOpMgr()->GoodByeCreIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateCreIn(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	if(IsMeshMode())
		GetCreOMMgr()->UpdateCreIn(wParam, lParam);
	else
		GetCreOpMgr()->UpdateCreIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelCreIn(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	if(IsMeshMode())
		GetCreOMMgr()->CancelCreIn(wParam, lParam);
	else
		GetCreOpMgr()->CancelCreIn(wParam, lParam);
	////////////////////////////////
	return 0L;
}
////////////////////////////////////////////////////////////////////
long CDrGrafFrame::OnCreateorActivateFE0In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->CreateorActivatePost_NOD(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeFE0In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->GoodByePost_NOD(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateFE0In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->UpdatePost_NOD(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelFE0In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->CancelPost_NOD(wParam, lParam);
	////////////////////////////////
	return 0L;
}

long CDrGrafFrame::OnCreateorActivateFE1In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->CreateorActivatePost_CUR(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeFE1In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->GoodByePost_CUR(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateFE1In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->UpdatePost_CUR(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelFE1In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->CancelPost_CUR(wParam, lParam);
	////////////////////////////////
	return 0L;
}

long CDrGrafFrame::OnCreateorActivateFE2In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->CreateorActivatePost_PAT(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeFE2In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->GoodByePost_PAT(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateFE2In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->UpdatePost_PAT(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelFE2In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
	GetPostMgr()->GetDLDMouse()->CancelPost_PAT(wParam, lParam);
	////////////////////////////////
	return 0L;
}

long CDrGrafFrame::OnCreateorActivateFE3In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
//	GetPostMgr()->GetDLDMouse()->CreateorActivatePost_SOL(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnGoodByeFE3In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
//	GetPostMgr()->GetDLDMouse()->GoodByePost_SOL(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnUpdateFE3In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
//	GetPostMgr()->GetDLDMouse()->UpdatePost_SOL(wParam, lParam);
	////////////////////////////////
	return 0L;
}
	 
long CDrGrafFrame::OnCancelFE3In(UINT wParam, long lParam)
{
	wParam = GetCurrentIGenID();
	/////////////////////
//	GetPostMgr()->GetDLDMouse()->CancelPost_SOL(wParam, lParam);
	////////////////////////////////
	return 0L;
}
/////////////////////////////////////////////////////////////////////////////////////	
void CDrGrafFrame::InitialShowWindow(UINT nCmdShow)
{
	WINDOWPLACEMENT wp;
	if (!ReadWindowPlacement(&wp))
	{
//		ShowWindow(nCmdShow);
		ShowWindow(SW_SHOWMAXIMIZED);
		return;
	}
	if (nCmdShow != SW_SHOWNORMAL)
		wp.showCmd = nCmdShow;
		
	SetWindowPlacement(&wp);
//	ShowWindow(wp.showCmd);
	ShowWindow(SW_SHOWMAXIMIZED);
}

/////////////////////////////////////////////////////////////////////////////
// CDrGrafFrame message handlers
/////////////////////////////////////////////////////////////////////////////
void CDrGrafFrame::OnClose()
{  
	// before it is destroyed, 
	////////////////////////////////////////////// Kill Timers	
	KillTimer(TM_CLOCK);
	KillTimer(TM_MEMORY);
	/////////////////////////////////// toolboxes	 
	if(GetEDimBox()->m_hWnd != NULL)
		GetEDimBox()->DestroyWindow();
	if(m_wndCntlBox.m_hWnd)
		m_wndCntlBox.DestroyWindow();
	if(m_wndIGenBox.m_hWnd)
		m_wndIGenBox.DestroyWindow();
	if(m_wndMGenBox.m_hWnd)
		m_wndMGenBox.DestroyWindow();
	if(m_wndDrawBox.m_hWnd)
		m_wndDrawBox.DestroyWindow(); 
		
	// before it is destroyed, save the position of the window
	WINDOWPLACEMENT wp;
	wp.length = sizeof wp;
	if (GetWindowPlacement(&wp))
	{
		wp.flags = 0;
		if (IsZoomed())
			wp.flags |= WPF_RESTORETOMAXIMIZED;
		// and write it to the .INI file
		WriteWindowPlacement(&wp);
	}
	///////////////////////////////////////////
    CMDIFrameWnd::OnClose();  
    
}

void CDrGrafFrame::CreateOrActivateFrame(CDocTemplate* pTemplate, 
				   CRuntimeClass* pViewClass)
{
	CDocument* pDoc;
	///////////////
	if(GetActiveViewNumber() == VIEWSPECTRA_IN)		// Auxilliary
	{
		CDrSplitFrm* pMDIActive = (CDrSplitFrm*)MDIGetActive();
		ASSERT(pMDIActive != NULL);
		/////////////////////////////////////////////////
		pDoc = pMDIActive->GetActiveDocument();
	}
	else
	if(GetActiveViewNumber() == VIEWFORMDATA)		// FormData
	{
		C3WaySplitterFrame* pMDIActive = (C3WaySplitterFrame*)MDIGetActive();
		ASSERT(pMDIActive != NULL);
		/////////////////////////////////////////////////
		pDoc = pMDIActive->GetActiveDocument();
	}
	else
	{
		CDrGrafChildFrame*	pMDIActive = (CDrGrafChildFrame*)MDIGetActive();
		ASSERT(pMDIActive != NULL);
		/////////////////////////////////////////////////
		pDoc = pMDIActive->GetActiveDocument();
	}
	/////////////////////
	ASSERT(pDoc != NULL);
    /////////////////////////////////////////
	CView* pView;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(pViewClass))
		{
			pView->GetParentFrame()->ActivateFrame();
			MDITile(MDITILE_SKIPDISABLED);
			return;
		}
	}
    ////////////////////////
	if(GetActiveViewNumber() == VIEWSPECTRA_IN)		// Auxilliary
	{
		CDrSplitFrm* pNewFrame
			= (CDrSplitFrm*)(pTemplate->CreateNewFrame(pDoc, NULL));
		if (pNewFrame == NULL)
			return;     // not created
		ASSERT(pNewFrame->IsKindOf(RUNTIME_CLASS(CDrSplitFrm)));
		pTemplate->InitialUpdateFrame(pNewFrame, pDoc); 
	}
	else
	if(GetActiveViewNumber() == VIEWFORMDATA)		// Auxilliary
	{
		C3WaySplitterFrame* pNewFrame
			= (C3WaySplitterFrame*)(pTemplate->CreateNewFrame(pDoc, NULL));
		if (pNewFrame == NULL)
			return;     // not created
		ASSERT(pNewFrame->IsKindOf(RUNTIME_CLASS(C3WaySplitterFrame)));
		pTemplate->InitialUpdateFrame(pNewFrame, pDoc); 
	}
	else
	{
		CDrGrafChildFrame* pNewFrame
			= (CDrGrafChildFrame*)(pTemplate->CreateNewFrame(pDoc, NULL));
		if (pNewFrame == NULL)
			return;     // not created
		ASSERT(pNewFrame->IsKindOf(RUNTIME_CLASS(CDrGrafChildFrame)));
		pTemplate->InitialUpdateFrame(pNewFrame, pDoc); 
	}
	//////////////////////////////
	MDITile(MDITILE_SKIPDISABLED);
	//////////////////////////////
}

void CDrGrafFrame::CloseView(CRuntimeClass* pViewClass)
{

	CDocument* pDoc;
	///////////////
	if(GetActiveViewNumber() == VIEWSPECTRA_IN)		// Auxilliary
	{
		CDrSplitFrm* pMDIActive = (CDrSplitFrm*)MDIGetActive();
		ASSERT(pMDIActive != NULL);
		/////////////////////////////////////////////////
		pDoc = pMDIActive->GetActiveDocument();
	}
	else
	if(GetActiveViewNumber() == VIEWFORMDATA)		// Auxilliary
	{
		C3WaySplitterFrame* pMDIActive = (C3WaySplitterFrame*)MDIGetActive();
		ASSERT(pMDIActive != NULL);
		/////////////////////////////////////////////////
		pDoc = pMDIActive->GetActiveDocument();
	}
	else
	{
		CDrGrafChildFrame*	pMDIActive = (CDrGrafChildFrame*)MDIGetActive();
		ASSERT(pMDIActive != NULL);
		/////////////////////////////////////////////////
		pDoc = pMDIActive->GetActiveDocument();
	}
	/////////////////////
	ASSERT(pDoc != NULL);
    /////////////////////////////////////////
	CView* pView;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(pViewClass))
		{
			pView->GetParentFrame()->ShowWindow(SW_HIDE);
			return;
		}
	}

}
////////////////////////////////////////////////////////////////////// TOOLBOXES: CREATIONS
BOOL CIGenBox::Create(CWnd* pParentWnd,CRect rect)
{
	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd_EB = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx( WS_EX_CONTEXTHELP,
	//					"AfxWnd",
						strAfxWnd_EB,
						"GENERATOR",
						WS_POPUP |WS_CLIPCHILDREN |WS_CAPTION,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_IGenBOX*/,
						NULL
					);
	return bOk;				
}

BOOL CMGenBox::Create(CWnd* pParentWnd,CRect rect)
{
	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd_EB = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx( WS_EX_CONTEXTHELP,
	//					"AfxWnd",
						strAfxWnd_EB,
						"MESH",
						WS_POPUP |WS_CLIPCHILDREN |WS_CAPTION,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_MGenBOX*/,
						NULL
					);
	return bOk;				
}

BOOL CMainBox::Create(CWnd* pParentWnd,CRect rect)
{
	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd_EB = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx( WS_EX_CONTEXTHELP,
	//					"AfxWnd",
						strAfxWnd_EB,
						"OPERATION",
						WS_POPUP |WS_CLIPCHILDREN |WS_CAPTION|WS_EX_CONTEXTHELP,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_CntlBOX*/,
						NULL
					);
	return bOk;				
}

BOOL CCntlBox::Create(CWnd* pParentWnd,CRect rect)
{
	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd_EB = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx( WS_EX_CONTEXTHELP,
	//					"AfxWnd",
						strAfxWnd_EB,
						"CONTROL",
						WS_POPUP |WS_CLIPCHILDREN |WS_CAPTION,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_CntlBOX*/,
						NULL
					);
	return bOk;				
}

BOOL CEDimBox::Create(CWnd* pParentWnd,CRect rect)
{
	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd_EB = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL );
	////////////////////////////
	BOOL bOk = CreateEx( WS_EX_CONTEXTHELP,
	//					"AfxWnd",
						strAfxWnd_EB,
						"ELEMENT",
						WS_POPUP |WS_CLIPCHILDREN |WS_CAPTION,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_CntlBOX*/,
						NULL
					);
	return bOk;				
}

BOOL CDrawBox::Create(CWnd* pParentWnd,CRect rect)
{

	/////////////////////////////////////////////////////////////////////////
	// TN001: following not supported in MFC4.0
		//·	"AfxWnd" is used for all child windows created with CWnd::Create.
		//·	class style : CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW
		//·	no icon
		//·	arrow cursor
		//·	no background color
	//////////////////////////////////////////////////////////////////////////
	CString strAfxWnd_DB = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
							AfxGetApp()->LoadStandardCursor(IDC_ARROW),(HBRUSH)NULL,(HICON)NULL);
	////////////////////////////
	BOOL bOk = CreateEx( WS_EX_CONTEXTHELP,
	//					"AfxWnd",
						strAfxWnd_DB,
						"DECORATOR",
						WS_POPUP |WS_CLIPCHILDREN |WS_CAPTION,
						rect.left,
						rect.top, 
						rect.right - rect.left, 
						rect.bottom - rect.top,
						pParentWnd->GetSafeHwnd(),
						(HMENU)NULL/*IDW_DrawBOX*/,
						NULL
					);
	return bOk;				
}

//////////////////////////////////////////////////////////// Message Handler
void CDrGrafFrame::OnDeckDreampipe()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafFrame::OnUpdateDeckDreampipe(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnDeckSap()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafFrame::OnUpdateDeckSap(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnDeckTab()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafFrame::OnUpdateDeckTab(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnOptionAxison()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafFrame::OnUpdateOptionAxison(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

long CDrGrafFrame::OnOptionMode(UINT wParam, long lParam) 
{
//	MAX_MODE = 5
//	Modes: (0)GENERATOR/(1)MESH/(2)SPECTRAL/(3)SPATIAL/(4)TEMPORAL
	CString str[] = {"GENERATOR","MESH","SPATIAL","SPECTRAL","TEMPORAL",""};
	/////////////////////////////////////////
	UpdateModeStat(str[wParam]);
	///
	return 0L;
}

void CDrGrafFrame::OnOptionAutoacceptOn() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleAutoAcceptOn();
	////////////////////////////
	CString str1 = "AutoAccept ON";
	CString str2 = "AutoAccept OFF";
	//
	if(pBool->IsAutoAcceptOn())
		UpdateAutoAcceptStat(str1);
	else
		UpdateAutoAcceptStat(str2);
	
}

void CDrGrafFrame::OnUpdateOptionAutoacceptOn(CCmdUI* pCmdUI) 
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pCmdUI->SetCheck(pBool->IsAutoAcceptOn());
}

void CDrGrafFrame::OnOptionSingleSegOn() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleSingleSegOn();
	////////////////////////////
	CString str1 = "SingleSeg ON";
	CString str2 = "SingleSeg OFF";
	//
	if(pBool->IsSingleSegOn())
		UpdateSingleSegStat(str1);
	else
		UpdateSingleSegStat(str2);
	
}

void CDrGrafFrame::OnUpdateOptionSingleSegOn(CCmdUI* pCmdUI) 
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pCmdUI->SetCheck(pBool->IsSingleSegOn());
}

void CDrGrafFrame::OnOptionSpawnOn() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleSpawnOn();
	////////////////////////////
	CString str1 = "Copy ON";
	CString str2 = "Copy OFF";
	////////////////////////////
	if( (m_CurrentOperID == GOP_EDIT) ||(m_CurrentOperID == GOP_MOVE) )
	{		
		str1 = "Rigid OFF";
		str2 = "Rigid ON";
	}
	//
	if(pBool->IsSpawnOn())
		UpdateSpawnStat(str1);
	else
		UpdateSpawnStat(str2);
}

void CDrGrafFrame::OnUpdateOptionSpawnOn(CCmdUI* pCmdUI) 
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pCmdUI->SetCheck(pBool->IsSpawnOn());
}

void CDrGrafFrame::OnOptionBlineOn() 
{
	if(
		GetCurrentIGenID() == NODE ||GetCurrentIGenID() == CNODE || 
		GetCurrentIGenID() == INODE ||GetCurrentIGenID() == MCNODE 
		)
		return;
	//////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleBLineOn();
	////////////////////////////
	CString str1 = "BLine ON";
	CString str2 = "BLine OFF";
	//
	if(pBool->IsBLineOn())
		UpdateBLineStat(str1);
	else
	{
		UpdateBLineStat(str2);
//		GetMouseMgr()->GetDLDMouse()->SetCurrentNodeID("");
//		GetMouseMgr()->GetDLDMouse()->SetAnchorNodeID("");
		if(GetMouseBoxType() != NODEBOX) 
			ModeLessOn();	// reset CurrentNodeID
	}
}

void CDrGrafFrame::OnUpdateOptionBlineOn(CCmdUI* pCmdUI) 
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pCmdUI->SetCheck(pBool->IsBLineOn());
}

void CDrGrafFrame::OnOptionDialogon()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleDialogOn();
	
}

void CDrGrafFrame::OnUpdateOptionDialogon(CCmdUI* pCmdUI)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pCmdUI->SetCheck(pBool->IsDialogOn());
}

void CDrGrafFrame::OnOptionPenchange()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafFrame::OnUpdateOptionPenchange(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnOptionRefresh()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	////////////////////////////////////////////////////////////////////
	if(pDoc->IsModified())
//	CDocument::SetModifiedFlag
		pDoc->UpdateAllViews(NULL);
	
}

void CDrGrafFrame::OnOptionRubberband()
{
	
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleDragOn();
	
}

void CDrGrafFrame::OnUpdateOptionRubberband(CCmdUI* pCmdUI)
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pCmdUI->SetCheck(pBool->IsDragOn());
		
}

void CDrGrafFrame::OnView12view()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////////////  
	pBool->Toggle12ViewActive();
	if(pBool->Is12ViewActive() )
	{
		SetActiveViewNumber(VIEW12);
		////////////////////////////
		CreateOrActivateFrame(((CDrGrafApp*)AfxGetApp())->Get12ViewTemplate(), 
				RUNTIME_CLASS(C12View));
		///////////////////////////////////////////// View Changed
		((CDrGrafDoc*)pDoc)->GetObjectMgr()->SetViewChanged(TRUE);
		////////////////////////////
//		ModeLessOn();
		/////////////////
		OnModeInput();
//		SetOpMode(OP_INPUT);
//		SwitchMenu(IDR_INPUTMENU);
		//////////////////////////

    }
	else
	{
		if(!AnyOtherInputViewVisible())
			ModeLessOff();
		//////////////////
	    CloseView(RUNTIME_CLASS(C12View));  
	}	    
}

void CDrGrafFrame::OnUpdateView12view(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->Is12ViewActive() );
	
}

void CDrGrafFrame::OnView23view()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->Toggle23ViewActive();
	if(pBool->Is23ViewActive() )
	{
		SetActiveViewNumber(VIEW23);
		////////////////////////////
		CreateOrActivateFrame(((CDrGrafApp*)AfxGetApp())->Get23ViewTemplate(), 
				RUNTIME_CLASS(C23View));
		////////////////////////////
//		ModeLessOn();
		/////////////////
		OnModeInput();
//		SetOpMode(OP_INPUT);
//		SwitchMenu(IDR_INPUTMENU);
		SwitchMenu(IDR_INPUTMENU);
		//////////////////////////
    }
	else
	{
		if(!AnyOtherInputViewVisible())
			ModeLessOff();
		//////////////////
	    CloseView(RUNTIME_CLASS(C23View));  
	}	    

}

void CDrGrafFrame::OnUpdateView23view(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->Is23ViewActive() );
	
}

void CDrGrafFrame::OnView31view()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->Toggle31ViewActive();
	if(pBool->Is31ViewActive() )
	{
		SetActiveViewNumber(VIEW31);
 		////////////////////////////
		CreateOrActivateFrame(((CDrGrafApp*)AfxGetApp())->Get31ViewTemplate(), 
				RUNTIME_CLASS(C31View));
 		////////////////////////////
//		ModeLessOn();
		/////////////////
		OnModeInput();
//		SetOpMode(OP_INPUT);
//		SwitchMenu(IDR_INPUTMENU);
		SwitchMenu(IDR_INPUTMENU);
		//////////////////////////
   }
	else
	{
		if(!AnyOtherInputViewVisible())
			ModeLessOff();
		//////////////////
	    CloseView(RUNTIME_CLASS(C31View));  
	}	    

}

void CDrGrafFrame::OnUpdateView31view(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->Is31ViewActive() );

}

void CDrGrafFrame::OnView3dview()
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleIsoViewActive();
	if(pBool->IsIsoViewActive() )
	{
		SetActiveViewNumber(VIEWISO);
		////////////////////////////
		CreateOrActivateFrame(((CDrGrafApp*)AfxGetApp())->Get3DViewTemplate(), 
				RUNTIME_CLASS(C3DView));
		///////////////////////////////////////////// View Changed
		((CDrGrafDoc*)pDoc)->GetObjectMgr()->SetViewChanged(TRUE);
 		////////////////////////////
//		ModeLessOn();
		/////////////////
		OnModeOutput();
//		SetOpMode(OP_INPUT);
		SwitchMenu(IDR_OUTPUTMENU);
		//////////////////////////
		if(!AnyOtherInputViewVisible())
			ModeLessOff();
		/////////////////////////////////////
		// also sets m_nView in CDrGrafFrame 
		////////////////////////////////////////// 
		CMDIChildWnd* pMDIActive = MDIGetActive();
		if(!pMDIActive)
			return;
		///////////////	
		CDocument* pDoc = pMDIActive->GetActiveDocument();
		if(pDoc)
		{
   			/////////////
			CView* pView;
			POSITION pos = pDoc->GetFirstViewPosition();
			while (pos)
			{
				pView = pDoc->GetNextView(pos);
				///////////////////////////////////////////// Scale Changed
				if( ((CDrawView*)pView)->GetViewNum() == VIEWISO)  // View3D
					((CDrawView*)pView)->SetScalevv3DToLP();
				///////////////////////////////////
				break;
			}
		}
	}
	else
	    CloseView(RUNTIME_CLASS(C3DView));
	//////////////////////////////////////
	
}

void CDrGrafFrame::OnUpdateView3dview(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->IsIsoViewActive() );
	
}

void CDrGrafFrame::OnAddl3dview()
{
	////////////////////////////////////////////////////////////////////
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	SetActiveViewNumber(VIEWISO);
	SetOpMode(OP_OUTPUT);
	///////////////////////////////////////////// View Changed
	((CDrGrafDoc*)pDoc)->GetObjectMgr()->SetViewChanged(TRUE);
	/////////////////
	SwitchMenu(IDR_OUTPUTMENU);
	//////////////////////////
	if(!AnyOtherInputViewVisible())
		ModeLessOff();
	/////////////////////////////////////
	// also sets m_nView in CDrGrafFrame 
	////////////////////////////////////////// 
	CMDIChildWnd* pMDIActive = MDIGetActive();
	if(!pMDIActive)
		return;
	///////////////
	CDrawView* pView		= (CDrawView*)(pMDIActive->GetActiveView());
	///////////////////////////////////////////// Scale Changed
	if(pView->GetViewNum() == VIEWISO)  // View3D
		pView->SetScalevv3DToLP();
	///////////////////////////////////
}

void CDrGrafFrame::OnViewDataview()
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleDataViewActive();
	if(pBool->IsDataViewActive() )
	{
		SetActiveViewNumber(VIEWDAT);
		////////////////////////////
		CreateOrActivateFrame(((CDrGrafApp*)AfxGetApp())->GetDataViewTemplate(), 
			RUNTIME_CLASS(CDataView));
	}
	else
	    CloseView(RUNTIME_CLASS(CDataView));
	
}

void CDrGrafFrame::OnUpdateViewDataview(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->IsDataViewActive() );
	
}

void CDrGrafFrame::OnViewMeshDataview()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleMeshDataViewActive();
	if(pBool->IsMeshDataViewActive() )
	{
		SetActiveViewNumber(VIEWMESH);
		////////////////////////////
		CreateOrActivateFrame(((CDrGrafApp*)AfxGetApp())->GetMeshDataViewTemplate(), 
			RUNTIME_CLASS(CMsDataVu));
	}
	else
	    CloseView(RUNTIME_CLASS(CMsDataVu));
	
}

void CDrGrafFrame::OnUpdateViewMeshDataview(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->IsMeshDataViewActive() );
	
}

void CDrGrafFrame::OnViewDeckview()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleDeckViewActive();
	if(pBool->IsDeckViewActive() )
	{
		SetActiveViewNumber(VIEWDECK);
		////////////////////////////
		CreateOrActivateFrame(((CDrGrafApp*)AfxGetApp())->GetDeckViewTemplate(), 
			RUNTIME_CLASS(CDeckView));
	}
	else
	    CloseView(RUNTIME_CLASS(CDeckView));
	
}

void CDrGrafFrame::OnUpdateViewDeckview(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->IsDeckViewActive() );
	
}

void CDrGrafFrame::OnViewInputstatusControls() 
{
	m_CntlStat.ShowWindow((m_CntlStat.GetStyle() & WS_VISIBLE) == 0);
}

void CDrGrafFrame::OnUpdateViewInputstatusControls(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_CntlStat.GetStyle() & WS_VISIBLE) != 0);
}

void CDrGrafFrame::OnViewInputstatusDecorators() 
{
	m_DrawStat.ShowWindow((m_DrawStat.GetStyle() & WS_VISIBLE) == 0);
}

void CDrGrafFrame::OnUpdateViewInputstatusDecorators(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_DrawStat.GetStyle() & WS_VISIBLE) != 0);
}

void CDrGrafFrame::OnViewInputstatusGenerator() 
{
	m_IGenStat.ShowWindow((m_IGenStat.GetStyle() & WS_VISIBLE) == 0);
}

void CDrGrafFrame::OnUpdateViewInputstatusGenerator(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_IGenStat.GetStyle() & WS_VISIBLE) != 0);
}

void CDrGrafFrame::OnViewInputstatusCurrent() 
{
	m_CurrStat.ShowWindow((m_CurrStat.GetStyle() & WS_VISIBLE) == 0);
}

void CDrGrafFrame::OnUpdateViewInputstatusCurrent(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_CurrStat.GetStyle() & WS_VISIBLE) != 0);
}

void CDrGrafFrame::OnViewInputstatusOperations() 
{
	m_OperStat.ShowWindow((m_OperStat.GetStyle() & WS_VISIBLE) == 0);
}

void CDrGrafFrame::OnUpdateViewInputstatusOperations(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_OperStat.GetStyle() & WS_VISIBLE) != 0);
}

void CDrGrafFrame::OnViewOperbox() 
{
	m_wndOperBox.ShowWindow((m_wndOperBox.GetStyle() & WS_VISIBLE) == 0);
}

void CDrGrafFrame::OnUpdateViewOperbox(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((m_wndOperBox.GetStyle() & WS_VISIBLE) != 0);
}

void CDrGrafFrame::OnViewDrawbox()
{

	m_wndDrawBox.ShowWindow((m_wndDrawBox.GetStyle() & WS_VISIBLE) == 0);
	
}

void CDrGrafFrame::OnUpdateViewDrawbox(CCmdUI* pCmdUI)
{

	pCmdUI->SetCheck((m_wndDrawBox.GetStyle() & WS_VISIBLE) != 0);
	
}

void CDrGrafFrame::OnModeChange()
{
/*
	OnViewCntlbox(); // Edit/Creop etc. depends on this
	OnViewGenbox(); // Edit/Creop etc. depends on this
*/
}

void CDrGrafFrame::OnViewCntlbox() 
{
	if(m_CurrentOperID == GOP_POST)
	{
//		if(m_wndCntlBox.GetStyle() & WS_VISIBLE)
			m_wndCntlBox.ShowWindow(FALSE);
		/////////////////////////////// Show
		CRect BoxRect;
		int Boxwidth,Boxheight; 
		int cyBorder	= ::GetSystemMetrics(SM_CYBORDER);
		///////////
		CRect STopRect;
		GetSBarTop()->GetWindowRect(&STopRect); // screen Coords
		////////////////////////////////////////////////////////////// EDimBox 
		Boxwidth  = (int)GetEDimBox()->GetWidth();
		Boxheight = (int)GetEDimBox()->GetHeight(); 

   		BoxRect.left   = 0;
   		BoxRect.right  = BoxRect.left + Boxwidth; //
   		BoxRect.top    = 0;   //
   		BoxRect.bottom = BoxRect.top   + Boxheight;
//	ClientToScreen(&Rect);
		::AdjustWindowRect(&BoxRect,WS_BORDER|WS_CAPTION,FALSE);
		//////////////////////////////////////////// OutToOut
		Boxwidth  = BoxRect.Width();
		Boxheight = BoxRect.Height(); 
		////////////////////////////////////////////////////////
	 	BoxRect.left   = cyBorder; //
	 	BoxRect.right  = BoxRect.left + Boxwidth;
	 	BoxRect.top    = STopRect.bottom + 1;  //
	 	BoxRect.bottom = BoxRect.top  + Boxheight;
		//////////////////////////////////////////////////////////////
		GetEDimBox()->SetWindowPos(NULL,BoxRect.left,BoxRect.top,BoxRect.right-BoxRect.left,
                       BoxRect.bottom-BoxRect.top,SWP_NOZORDER|SWP_SHOWWINDOW);
		///
		return;
	}
	else
	{
		////////////////////////////////////////////
//		if(m_wndEDimBox.GetStyle() & WS_VISIBLE)
			m_wndEDimBox.ShowWindow(FALSE);
		////////////////////////////////////////
		m_wndCntlBox.ShowWindow(TRUE);
	}
}

void CDrGrafFrame::OnUpdateViewCntlbox(CCmdUI* pCmdUI) 
{
	if(m_CurrentOperID == GOP_POST)
		pCmdUI->SetCheck((m_wndEDimBox.GetStyle() & WS_VISIBLE) != 0);
	else
		pCmdUI->SetCheck((m_wndCntlBox.GetStyle() & WS_VISIBLE) != 0);
}

void CDrGrafFrame::OnViewGenbox() 
{
	if(IsMeshMode())
	{
		m_wndIGenBox.ShowWindow(FALSE);
		m_wndMGenBox.ShowWindow(TRUE);
	}
	else
	{
		m_wndMGenBox.ShowWindow(FALSE);
		m_wndIGenBox.ShowWindow(TRUE);
	}
}

void CDrGrafFrame::OnUpdateViewGenbox(CCmdUI* pCmdUI) 
{
	if(IsMeshMode())
		pCmdUI->SetCheck((m_wndMGenBox.GetStyle() & WS_VISIBLE) != 0);
	else
		pCmdUI->SetCheck((m_wndIGenBox.GetStyle() & WS_VISIBLE) != 0);
}

void CDrGrafFrame::OnViewSBarBot()
{
	CWnd* pBar = GetDescendantWindow(IDS_BOT_STATUSBAR);
	if(pBar)
	{
		pBar->ShowWindow( (pBar->GetStyle() & WS_VISIBLE) == 0); // toggle
		RecalcLayout();
	}
}

void CDrGrafFrame::OnUpdateViewSBarBot(CCmdUI* pCmdUI)
{
	CWnd* pBar = GetDescendantWindow(IDS_BOT_STATUSBAR);
	if(pBar)
	{
		pCmdUI->SetCheck( (pBar->GetStyle() & WS_VISIBLE) != 0);
	}	
}

void CDrGrafFrame::OnViewSBarTop()
{
	CWnd* pBar = GetDescendantWindow(IDS_TOP_STATUSBAR);
	if(pBar)
	{
		pBar->ShowWindow( (pBar->GetStyle() & WS_VISIBLE) == 0);    // toggle
		RecalcLayout();
	}
}

void CDrGrafFrame::OnUpdateViewSBarTop(CCmdUI* pCmdUI)
{
	CWnd* pBar = GetDescendantWindow(IDS_TOP_STATUSBAR);
	if(pBar)
	{
		pCmdUI->SetCheck( (pBar->GetStyle() & WS_VISIBLE) != 0);
	}	
}

void CDrGrafFrame::OnSpecPaper()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafFrame::OnSpecsTolerances() 
{

	CSDlgMgr* pSDlgMgr;
	/////////////////////////
	pSDlgMgr->DoModal_SpecObjs(HITNET);
	
}

void CDrGrafFrame::OnSpecPrecision()
{

	CSDlgMgr* pSDlgMgr;
	/////////////////////////
	pSDlgMgr->DoModal_SpecObjs(PRECISION);
	
}

void CDrGrafFrame::OnSpecScalefactor()
{

	CSDlgMgr* pSDlgMgr;
	/////////////////////////
	pSDlgMgr->DoModal_SpecObjs(SCALEFACTOR);
	
}
void CDrGrafFrame::OnSpecUnits()
{

	CSDlgMgr* pSDlgMgr;
	/////////////////////////
	pSDlgMgr->DoModal_SpecObjs(UNIT);
	
}

CView* CDrGrafFrame::GetViewPointer(CRuntimeClass* pViewClass)
{
	/////////////////////////////////////////////////////////
	// also sets m_nView in CMouse and CDrGrafFrame 
	///////////////////////////////////////////////////////// 
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd ); 
	CMDIChildWnd* pMDIActive = pWnd->MDIGetActive();
	ASSERT(pMDIActive != NULL);
	CDocument* pDoc = pMDIActive->GetActiveDocument();
	ASSERT(pDoc != NULL);

	CView* pView;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos)
	{
		pView = pDoc->GetNextView(pos);
		///////////////////////////////
		if (pView->IsKindOf(pViewClass))
			return pView;
	}
    return (CView*)NULL;
}

BOOL CDrGrafFrame::AnyOtherInputViewVisible()
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////////////  
	if	(GetActiveViewNumber() != VIEW12 && pBool->Is12ViewActive())
		return TRUE;
	////////////////
	if	(GetActiveViewNumber() != VIEW23 && pBool->Is23ViewActive())
		return TRUE;
	////////////////
	if	(GetActiveViewNumber() != VIEW31 && pBool->Is31ViewActive())
		return TRUE;
	////////////////
	return FALSE;
}
	
void CDrGrafFrame::ModeLessOff()
{
	////////////////////////////////////////////////
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_CUR();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_PAT();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_SOL();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_SLD();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_SUP();
	////////////////////////////////////////////////
	GetCreOpMgr()->GetSolCreOp()->ModeLessOff();
	////////////////////////////////////////////////
	GetPostMgr()->GetDLDMouse()->ModeLessOff_NOD();
	GetPostMgr()->GetDLDMouse()->ModeLessOff_CUR();
	GetPostMgr()->GetDLDMouse()->ModeLessOff_PAT();
//	GetPostMgr()->GetDLDMouse()->ModeLessOff_SOL();
}
	
void CDrGrafFrame::ModeLessOff_Mesh()
{
/*
	////////////////////////////////////////////////
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_CUR();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_PAT();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_SOL();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_SLD();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_SUP();
	////////////////////////////////////////////////
	GetCreOpMgr()->GetSolCreOp()->ModeLessOff();
	////////////////////////////////////////////////
	GetPostMgr()->GetDLDMouse()->ModeLessOff_NOD();
	GetPostMgr()->GetDLDMouse()->ModeLessOff_CUR();
	GetPostMgr()->GetDLDMouse()->ModeLessOff_PAT();
//	GetPostMgr()->GetDLDMouse()->ModeLessOff_SOL();
*/
}
	
long CDrGrafFrame::OnResetCntlOpen(UINT wParam, long lParam)
{
	int i;
	//////
	for(i=0;i<MAX_EDIMITEMS;i++)
			ReSetEDimOpen(FALSE,i);
	///
	for(i=0;i<MAX_CNTLITEMS;i++)
		ReSetCntlOpen(FALSE,i);
	///////////////////////
	switch(m_CurrentOperID)
	{
		case CREATEOPS:
			return 0L;
		case COP_CREATE:
			///
			for(i=1;i<MAX_CNTLITEMS;i++)	//0= Mesh->Closed
											// others->Open
				ReSetCntlOpen(TRUE,i);
			///
			break;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		case COP_EXTRACT:
			break;						// ALL->Closed
		////////////////////////////////
		case GENOPS:       
			return 0L;
			
		case GOP_EDIT:// fall thro'	
		case GOP_MOVE:
		case GOP_UNPOST:
		case GOP_DELETE:
			break;
			
		case GOP_POST:
			///
			switch(m_CurrentIGenID)
			{
				case CURVE:
					///
					ReSetCntlOpen(TRUE,0);			//0= Mesh->Open
					///////////
					ReSetEDimOpen(TRUE,0);			//0= 0D->Open
					ReSetEDimOpen(TRUE,1);			//0= 1D->Open
					return 0L;
				case PATCH:
					///
					ReSetCntlOpen(TRUE,0);			//0= Mesh->Open
					///////////
					ReSetEDimOpen(TRUE,0);			//0= 0D->Open
					ReSetEDimOpen(TRUE,1);			//0= 1D->Open
					ReSetEDimOpen(TRUE,2);			//0= 2D->Open
					return 0L;
				case SOLID:
					///
					ReSetCntlOpen(TRUE,0);			//0= Mesh->Open
					///////////
					ReSetEDimOpen(TRUE,0);			//0= 0D->Open
					ReSetEDimOpen(TRUE,1);			//0= 1D->Open
					ReSetEDimOpen(TRUE,2);			//0= 2D->Open
					ReSetEDimOpen(TRUE,3);			//0= 3D->Open
					return 0L;
				default:
					return 0L;
			}
			///
			return 0L;

		/////////////////////////////////
		case FEMOPS:        
		case BULLOPS:
			return 0L;						// ALL->Closed
		default:
			return 0L;						// ALL->Closed

	}
	////////////////////
	if(m_CurrentOperID != GOP_POST)
		OnResetIGenOpen(wParam, lParam);
	////////////////////
	return 0L;
}
	
long CDrGrafFrame::OnResetIGenOpen(UINT wParam, long lParam)
{
	int i;
	//////
	for(i=0;i<MAX_IGENITEMS;i++)
		ReSetIGenOpen(FALSE,i);
	///////////////////////
	switch(m_CurrentOperID)
	{
		case CREATEOPS:
			return 0L;
		case COP_CREATE:
			switch(m_CurrentCntlID)
			{
				case ELEMENT:
/*
				case EDIM_0:
				case EDIM_1:
				case EDIM_2:
				case EDIM_3:
*/
				///
					for(i=0;i<MAX_IGENITEMS;i++)	// ALL->Open
						ReSetIGenOpen(TRUE,i);
					///
					return 0L;
				//////////////////////////////// Static ?
				case  STATICLOAD:
				case  FORCE:       
				case  DISPLACE:        
				case  PRESSURE:        
				case  THERMAL:
				case  LUMPWT:
				case  GRAVITY:			
					///
					return 0L;						// ALL->Closed
				//////////////////////////////// Support ?
				case SUPPORT:
				case SUPPORT_RIGID:
				case SUPPORT_LINSPRING:
				case SUPPORT_LINSNUBBER:
				case SUPPORT_NLSPRING:
				case SUPPORT_NLSNUBBER:
					///
					return 0L;						// ALL->Closed
				default:
					///
					return 0L;						// ALL->Closed
			}
			return 0L;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		case COP_EXTRACT:

			switch(m_CurrentCntlID)
			{
				case ELEMENT:
					///
					ReSetIGenOpen(TRUE,0);		//0= Node->Open
												// others->Closed
					///
					return 0L;
				//////////////////////////////// Static ?
				case  STATICLOAD:
				case  FORCE:       
				case  DISPLACE:        
				case  PRESSURE:        
				case  THERMAL:
				case  LUMPWT:
				case  GRAVITY:			
					///
					return 0L;						// ALL->Closed
				//////////////////////////////// Support ?
				case SUPPORT:
				case SUPPORT_RIGID:
				case SUPPORT_LINSPRING:
				case SUPPORT_LINSNUBBER:
				case SUPPORT_NLSPRING:
				case SUPPORT_NLSNUBBER:
					///
					return 0L;						// ALL->Closed
				default:
					///
					return 0L;						// ALL->Closed
			}
			return 0L;
		////////////////////////////////
		case GENOPS:       
			return 0L;
			
		case GOP_EDIT:// fall thro'	
		case GOP_MOVE:
		case GOP_UNPOST:
		case GOP_DELETE:
			switch(m_CurrentCntlID)
			{
				case ELEMENT:
					///
					ReSetIGenOpen(TRUE,0);		//0= Node->Open
												// others->Closed
					///
					return 0L;
				//////////////////////////////// Static ?
				case  STATICLOAD:
				case  FORCE:       
				case  DISPLACE:        
				case  PRESSURE:        
				case  THERMAL:
				case  LUMPWT:
				case  GRAVITY:			
					///
					return 0L;						// ALL->Closed
				//////////////////////////////// Support ?
				case SUPPORT:
				case SUPPORT_RIGID:
				case SUPPORT_LINSPRING:
				case SUPPORT_LINSNUBBER:
				case SUPPORT_NLSPRING:
				case SUPPORT_NLSNUBBER:
					///
					return 0L;						// ALL->Closed
				default:
					///
					return 0L;						// ALL->Closed
			}
			return 0L;

			
		case GOP_POST:
			//////
//			ReSetIGenOpen(TRUE,0);					// Node->Open
			////////////////////
//			OnResetCntlOpen(wParam, lParam);
			////////////////////
			break;

		/////////////////////////////////
		case FEMOPS:        
		case BULLOPS:
			return 0L;								// ALL->Closed
		default:
			return 0L;								// ALL->Closed

	}
	////////////////////
	if(m_CurrentOperID == GOP_POST)
		OnResetCntlOpen(wParam, lParam);
	////////////////////
	return 0L;
}

long CDrGrafFrame::OnResetCntlOpen_Mesh(UINT wParam, long lParam)
{
	int i;
	//////
	for(i=0;i<MAX_EDIMITEMS;i++)
			ReSetEDimOpen(FALSE,i);
	///
	for(i=0;i<MAX_CNTLITEMS;i++)
		ReSetCntlOpen(FALSE,i);
	///////////////////////
	switch(m_CurrentOperID)
	{
		case CREATEOPS:
			return 0L;
		case COP_CREATE:
			///
			for(i=1;i<MAX_CNTLITEMS;i++)	//0= Mesh->Closed
											// others->Open
				ReSetCntlOpen(TRUE,i);
			///
			break;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		case COP_EXTRACT:
			break;						// ALL->Closed
		////////////////////////////////
		case GENOPS:       
			return 0L;
			
		case GOP_EDIT:// fall thro'	
		case GOP_MOVE:
		case GOP_UNPOST:
		case GOP_DELETE:
			break;
/*			
		case GOP_POST:
			///
			switch(m_CurrentIGenID)
			{
				case CURVE:
					///
					ReSetCntlOpen(TRUE,0);			//0= Mesh->Open
					///////////
					ReSetEDimOpen(TRUE,0);			//0= 0D->Open
					ReSetEDimOpen(TRUE,1);			//0= 1D->Open
					return 0L;
				case PATCH:
					///
					ReSetCntlOpen(TRUE,0);			//0= Mesh->Open
					///////////
					ReSetEDimOpen(TRUE,0);			//0= 0D->Open
					ReSetEDimOpen(TRUE,1);			//0= 1D->Open
					ReSetEDimOpen(TRUE,2);			//0= 2D->Open
					return 0L;
				case SOLID:
					///
					ReSetCntlOpen(TRUE,0);			//0= Mesh->Open
					///////////
					ReSetEDimOpen(TRUE,0);			//0= 0D->Open
					ReSetEDimOpen(TRUE,1);			//0= 1D->Open
					ReSetEDimOpen(TRUE,2);			//0= 2D->Open
					ReSetEDimOpen(TRUE,3);			//0= 3D->Open
					return 0L;
				default:
					return 0L;
			}
			///
			return 0L;
*/
		/////////////////////////////////
		case FEMOPS:        
		case BULLOPS:
			return 0L;						// ALL->Closed
		default:
			return 0L;						// ALL->Closed

	}
	////////////////////
	if(m_CurrentOperID != GOP_POST)
		OnResetIGenOpen(wParam, lParam);
	////////////////////
	return 0L;
}

long CDrGrafFrame::OnResetIGenOpen_Mesh(UINT wParam, long lParam)
{
	int i;
	//////
	for(i=0;i<MAX_IGENITEMS;i++)
		ReSetIGenOpen(FALSE,i);
	///////////////////////
	switch(m_CurrentOperID)
	{
		case CREATEOPS:
			return 0L;
		case COP_CREATE:
			switch(m_CurrentCntlID)
			{
				case ELEMENT:
/*
				case EDIM_0:
				case EDIM_1:
				case EDIM_2:
				case EDIM_3:
*/
				///
					for(i=0;i<MAX_IGENITEMS;i++)	// ALL->Open
						ReSetIGenOpen(TRUE,i);
					///
					return 0L;
				//////////////////////////////// Static ?
				case  STATICLOAD:
				case  FORCE:       
				case  DISPLACE:        
				case  PRESSURE:        
				case  THERMAL:
				case  LUMPWT:
				case  GRAVITY:			
					///
					return 0L;						// ALL->Closed
				//////////////////////////////// Support ?
				case SUPPORT:
				case SUPPORT_RIGID:
				case SUPPORT_LINSPRING:
				case SUPPORT_LINSNUBBER:
				case SUPPORT_NLSPRING:
				case SUPPORT_NLSNUBBER:
					///
					return 0L;						// ALL->Closed
				default:
					///
					return 0L;						// ALL->Closed
			}
			return 0L;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		case COP_EXTRACT:

			switch(m_CurrentCntlID)
			{
				case ELEMENT:
					///
					ReSetIGenOpen(TRUE,0);		//0= Node->Open
												// others->Closed
					///
					return 0L;
				//////////////////////////////// Static ?
				case  STATICLOAD:
				case  FORCE:       
				case  DISPLACE:        
				case  PRESSURE:        
				case  THERMAL:
				case  LUMPWT:
				case  GRAVITY:			
					///
					return 0L;						// ALL->Closed
				//////////////////////////////// Support ?
				case SUPPORT:
				case SUPPORT_RIGID:
				case SUPPORT_LINSPRING:
				case SUPPORT_LINSNUBBER:
				case SUPPORT_NLSPRING:
				case SUPPORT_NLSNUBBER:
					///
					return 0L;						// ALL->Closed
				default:
					///
					return 0L;						// ALL->Closed
			}
			return 0L;
		////////////////////////////////
		case GENOPS:       
			return 0L;
			
		case GOP_EDIT:// fall thro'	
		case GOP_MOVE:
		case GOP_UNPOST:
		case GOP_DELETE:
			switch(m_CurrentCntlID)
			{
				case ELEMENT:
					///
					ReSetIGenOpen(TRUE,0);		//0= Node->Open
												// others->Closed
					///
					return 0L;
				//////////////////////////////// Static ?
				case  STATICLOAD:
				case  FORCE:       
				case  DISPLACE:        
				case  PRESSURE:        
				case  THERMAL:
				case  LUMPWT:
				case  GRAVITY:			
					///
					return 0L;						// ALL->Closed
				//////////////////////////////// Support ?
				case SUPPORT:
				case SUPPORT_RIGID:
				case SUPPORT_LINSPRING:
				case SUPPORT_LINSNUBBER:
				case SUPPORT_NLSPRING:
				case SUPPORT_NLSNUBBER:
					///
					return 0L;						// ALL->Closed
				default:
					///
					return 0L;						// ALL->Closed
			}
			return 0L;

			
		case GOP_POST:
			//////
//			ReSetIGenOpen(TRUE,0);					// Node->Open
			////////////////////
//			OnResetCntlOpen(wParam, lParam);
			////////////////////
			break;

		/////////////////////////////////
		case FEMOPS:        
		case BULLOPS:
			return 0L;								// ALL->Closed
		default:
			return 0L;								// ALL->Closed

	}
	////////////////////
	if(m_CurrentOperID == GOP_POST)
		OnResetCntlOpen(wParam, lParam);
	////////////////////
	return 0L;
}


long CDrGrafFrame::OnResetCntlOpen_Auxi(UINT wParam, long lParam)
{
	int i;
	//////
	for(i=0;i<MAX_EDIMITEMS;i++)
			ReSetEDimOpen(FALSE,i);
	///
	for(i=0;i<MAX_CNTLITEMS;i++)
		ReSetCntlOpen(FALSE,i);
	///////////////////////
	switch(m_CurrentOperID)
	{
		case CREATEOPS:
			return 0L;
		case COP_CREATE:
			///
			for(i=1;i<MAX_CNTLITEMS;i++)	//0= Mesh->Closed
											// others->Open
				ReSetCntlOpen(TRUE,i);
			///
			break;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		case COP_EXTRACT:
			break;						// ALL->Closed
		////////////////////////////////
		case GENOPS:       
			return 0L;
			
		case GOP_EDIT:// fall thro'	
		case GOP_MOVE:
		case GOP_UNPOST:
		case GOP_DELETE:
			break;
/*			
		case GOP_POST:
			///
			switch(m_CurrentIGenID)
			{
				case CURVE:
					///
					ReSetCntlOpen(TRUE,0);			//0= Mesh->Open
					///////////
					ReSetEDimOpen(TRUE,0);			//0= 0D->Open
					ReSetEDimOpen(TRUE,1);			//0= 1D->Open
					return 0L;
				case PATCH:
					///
					ReSetCntlOpen(TRUE,0);			//0= Mesh->Open
					///////////
					ReSetEDimOpen(TRUE,0);			//0= 0D->Open
					ReSetEDimOpen(TRUE,1);			//0= 1D->Open
					ReSetEDimOpen(TRUE,2);			//0= 2D->Open
					return 0L;
				case SOLID:
					///
					ReSetCntlOpen(TRUE,0);			//0= Mesh->Open
					///////////
					ReSetEDimOpen(TRUE,0);			//0= 0D->Open
					ReSetEDimOpen(TRUE,1);			//0= 1D->Open
					ReSetEDimOpen(TRUE,2);			//0= 2D->Open
					ReSetEDimOpen(TRUE,3);			//0= 3D->Open
					return 0L;
				default:
					return 0L;
			}
			///
			return 0L;
*/
		/////////////////////////////////
		case FEMOPS:        
		case BULLOPS:
			return 0L;						// ALL->Closed
		default:
			return 0L;						// ALL->Closed

	}
	////////////////////
	if(m_CurrentOperID != GOP_POST)
		OnResetIGenOpen(wParam, lParam);
	////////////////////
	return 0L;
}

long CDrGrafFrame::OnResetIGenOpen_Auxi(UINT wParam, long lParam)
{
	int i;
	//////
	for(i=0;i<MAX_IGENITEMS;i++)
		ReSetIGenOpen(FALSE,i);
	///////////////////////
	switch(m_CurrentOperID)
	{
		case CREATEOPS:
			return 0L;
		case COP_CREATE:
			switch(m_CurrentCntlID)
			{
				case ELEMENT:
/*
				case EDIM_0:
				case EDIM_1:
				case EDIM_2:
				case EDIM_3:
*/
				///
					for(i=0;i<MAX_IGENITEMS;i++)	// ALL->Open
						ReSetIGenOpen(TRUE,i);
					///
					return 0L;
				//////////////////////////////// Static ?
				case  STATICLOAD:
				case  FORCE:       
				case  DISPLACE:        
				case  PRESSURE:        
				case  THERMAL:
				case  LUMPWT:
				case  GRAVITY:			
					///
					return 0L;						// ALL->Closed
				//////////////////////////////// Support ?
				case SUPPORT:
				case SUPPORT_RIGID:
				case SUPPORT_LINSPRING:
				case SUPPORT_LINSNUBBER:
				case SUPPORT_NLSPRING:
				case SUPPORT_NLSNUBBER:
					///
					return 0L;						// ALL->Closed
				default:
					///
					return 0L;						// ALL->Closed
			}
			return 0L;

		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		case COP_EXTRACT:

			switch(m_CurrentCntlID)
			{
				case ELEMENT:
					///
					ReSetIGenOpen(TRUE,0);		//0= Node->Open
												// others->Closed
					///
					return 0L;
				//////////////////////////////// Static ?
				case  STATICLOAD:
				case  FORCE:       
				case  DISPLACE:        
				case  PRESSURE:        
				case  THERMAL:
				case  LUMPWT:
				case  GRAVITY:			
					///
					return 0L;						// ALL->Closed
				//////////////////////////////// Support ?
				case SUPPORT:
				case SUPPORT_RIGID:
				case SUPPORT_LINSPRING:
				case SUPPORT_LINSNUBBER:
				case SUPPORT_NLSPRING:
				case SUPPORT_NLSNUBBER:
					///
					return 0L;						// ALL->Closed
				default:
					///
					return 0L;						// ALL->Closed
			}
			return 0L;
		////////////////////////////////
		case GENOPS:       
			return 0L;
			
		case GOP_EDIT:// fall thro'	
		case GOP_MOVE:
		case GOP_UNPOST:
		case GOP_DELETE:
			switch(m_CurrentCntlID)
			{
				case ELEMENT:
					///
					ReSetIGenOpen(TRUE,0);		//0= Node->Open
												// others->Closed
					///
					return 0L;
				//////////////////////////////// Static ?
				case  STATICLOAD:
				case  FORCE:       
				case  DISPLACE:        
				case  PRESSURE:        
				case  THERMAL:
				case  LUMPWT:
				case  GRAVITY:			
					///
					return 0L;						// ALL->Closed
				//////////////////////////////// Support ?
				case SUPPORT:
				case SUPPORT_RIGID:
				case SUPPORT_LINSPRING:
				case SUPPORT_LINSNUBBER:
				case SUPPORT_NLSPRING:
				case SUPPORT_NLSNUBBER:
					///
					return 0L;						// ALL->Closed
				default:
					///
					return 0L;						// ALL->Closed
			}
			return 0L;

			
		case GOP_POST:
			//////
//			ReSetIGenOpen(TRUE,0);					// Node->Open
			////////////////////
//			OnResetCntlOpen(wParam, lParam);
			////////////////////
			break;

		/////////////////////////////////
		case FEMOPS:        
		case BULLOPS:
			return 0L;								// ALL->Closed
		default:
			return 0L;								// ALL->Closed

	}
	////////////////////
	if(m_CurrentOperID == GOP_POST)
		OnResetCntlOpen(wParam, lParam);
	////////////////////
	return 0L;
}

long CDrGrafFrame::OnResetVaskID(UINT wParam, long lParam)
{
/*
	UINT CurrentTaskID;
	/////////////////////////
	SetVOprBoxStatus(TRUE);
	//////////////////////////////////////// Reset
	switch(m_CurrentVOprID)
	{
		case VO_ROTATE:
		case VO_ZOOM:
		case VO_PAN:
		case VO_ANIMATE:
			CurrentTaskID = GetViewMgr()->ReSetToolID(m_CurrentVOprID);
			break;
		default:
			return 0L;
	}
	////////////////////////////////////// TaskID
	SetActiveToolType((int)CurrentTaskID);
	////////////////////////////////////// String
	UpdateStaticControls();
	//////////
*/
	return 0L;
}
	
long CDrGrafFrame::OnResetMaskID(UINT wParam, long lParam)	// for MeshMode
{
	UINT CurrentTaskID;
	/////////////////////////
	SetIGenBoxStatus(TRUE);
	//////////////////////////////////////// Reset
	switch(m_CurrentOperID)
	{
		case COP_CREATE:
			CurrentTaskID = GetMouseMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			OnOptionSpawnOn(); // change RIGID->COPY 
			break;
		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		case COP_EXTRACT:
			CurrentTaskID = GetCreOMMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			OnOptionSpawnOn(); // change RIGID->COPY 
			break;
		case GOP_DELETE:
			CurrentTaskID = GetDelMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			break;
		case GOP_EDIT:
		case GOP_MOVE:
			CurrentTaskID = GetMditMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			OnOptionSpawnOn(); // change COPY->RIGID 
			break;
//		case GOP_POST:
//			CurrentTaskID = GetPostMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
//			break;
		default:
			return 0L;
	}
	////////////////////////////////////// TaskID
//	if(CurrentTaskID == (UINT)NONE)
//	{
//		AfxMessageBox("INADMISSIBLE TASK!\nILLEGAL Combination of\nCONTROL, MESH & OPERATION!!");
//		return 0L;
//	}
	///////////////////////////////
	SetActiveToolType((int)CurrentTaskID);
	//////////////////////////////// Elements?
	switch(m_CurrentCntlID)
	{
		case ELEMENT:
		/////////////
			switch(m_CurrentIGenID)
			{

				case FE0D:
				case MNODE:
				case MCNODE:
				case MESH0D:
					SetMouseBoxType(NODEBOX);
					////////////////////////////////////// ModeLesses
					SendMessage(ID_RESET_MODELESS_MESH);
					break;

				case MESH1D:
					SetMouseBoxType(CURVEBOX);
					////////////////////////////////////// ModeLesses
					SendMessage(ID_RESET_MODELESS_MESH);
					break;

				case MESH2D:
					SetMouseBoxType(PATCHBOX);
					////////////////////////////////////// ModeLesses
					SendMessage(ID_RESET_MODELESS_MESH);
					break;

				case MESH3D:
					SetMouseBoxType(SOLIDBOX);
					////////////////////////////////////// ModeLesses
					SendMessage(ID_RESET_MODELESS_MESH);
					break;

				case MBJ3D:
					SetMouseBoxType(OBJ3DBOX);
					////////////////////////////////////// ModeLesses
					SendMessage(ID_RESET_MODELESS_MESH);
					break;
				default:
					break;
			}
			break;
		//////////////////////////////// Static ?
		case  STATICLOAD:
		case  FORCE:       
		case  DISPLACE:        
		case  PRESSURE:        
		case  THERMAL:
		case  LUMPWT:
		case  GRAVITY:			
			SetMouseBoxType(STATICLOADBOX);
			////////////////////////////////////// ModeLesses
			SendMessage(ID_RESET_MODELESS_MESH);
			break;
		//////////////////////////////// Support ?
		case SUPPORT:
			SetMouseBoxType(SUPPORTBOX);
			////////////////////////////////////// ModeLesses
			SendMessage(ID_RESET_MODELESS_MESH);
			break;
		default:
			break;
	}
	////////////////////////////////////// String
	UpdateStaticControls();
	//////////
	return 0L;
}

long CDrGrafFrame::OnResetXaskID(UINT wParam, long lParam)
{
	UINT CurrentTaskID;
	/////////////////////////
	SetIGenBoxStatus(TRUE);
	//////////////////////////////////////// Reset
	switch(m_CurrentOperID)
	{
		case COP_CREATE:
//todo			CurrentTaskID = GetMouAXMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			OnOptionSpawnOn(); // change COPY->RIGID 
			break;
		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		case COP_EXTRACT:
			if(IsMeshMode())
				CurrentTaskID = GetCreOMMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			else
				CurrentTaskID = GetCreOpMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			OnOptionSpawnOn(); // change COPY->RIGID 
			break;
		case GOP_DELETE:
			CurrentTaskID = GetDelMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			break;
		case GOP_EDIT:
		case GOP_MOVE:
			if(IsMeshMode())
				CurrentTaskID = GetMditMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			else
				CurrentTaskID = GetEditMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			OnOptionSpawnOn(); // change RIGID->Copy 
			break;
		case GOP_POST:
			CurrentTaskID = GetPostMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			break;
		default:
			return 0L;
	}
	////////////////////////////////////// TaskID
	SetActiveToolType((int)CurrentTaskID);
	//////////////////////////////// Elements?
	switch(m_CurrentCntlID)
	{
		case ELEMENT:
		case EDIM_0:
		case EDIM_1:
		case EDIM_2:
		case EDIM_3:
		/////////////
			switch(m_CurrentIGenID)
			{

				case NODE:
				case INODE:
				case CNODE:
					SetMouseBoxType(NODEBOX);
					////////////////////////////////////// ModeLesses
					SendMessage(ID_RESET_MODELESS_AUXI);
					break;

				case CURVE:
					SetMouseBoxType(CURVEBOX);
					////////////////////////////////////// ModeLesses
					SendMessage(ID_RESET_MODELESS_AUXI);
					break;

				case PATCH:
					SetMouseBoxType(PATCHBOX);
					////////////////////////////////////// ModeLesses
					SendMessage(ID_RESET_MODELESS_AUXI);
					break;

				case SOLID:
					SetMouseBoxType(SOLIDBOX);
					////////////////////////////////////// ModeLesses
					SendMessage(ID_RESET_MODELESS_AUXI);
					break;

				case OBJ3D:
					SetMouseBoxType(OBJ3DBOX);
					////////////////////////////////////// ModeLesses
					SendMessage(ID_RESET_MODELESS_AUXI);
					break;
				default:
					break;
			}
			break;
		//////////////////////////////// Static ?
		case  STATICLOAD:
		case  FORCE:       
		case  DISPLACE:        
		case  PRESSURE:        
		case  THERMAL:
		case  LUMPWT:
		case  GRAVITY:			
			SetMouseBoxType(STATICLOADBOX);
			////////////////////////////////////// ModeLesses
			SendMessage(ID_RESET_MODELESS_AUXI);
			break;
		//////////////////////////////// Support ?
		case SUPPORT:
			SetMouseBoxType(SUPPORTBOX);
			////////////////////////////////////// ModeLesses
			SendMessage(ID_RESET_MODELESS_AUXI);
			break;
		default:
			break;
	}
	////////////////////////////////////// String
	UpdateStaticControls();
	//////////
	return 0L;
}
	

long CDrGrafFrame::OnResetTaskID(UINT wParam, long lParam)
{
	UINT CurrentTaskID;
	/////////////////////////
	SetIGenBoxStatus(TRUE);
	//////////////////////////////////////// Reset
	switch(m_CurrentOperID)
	{
		case COP_CREATE:
			CurrentTaskID = GetMouseMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			OnOptionSpawnOn(); // change RIGID->COPY 
			break;
		case COP_TRANSLATE:
		case COP_ROTATE:
		case COP_SCALE:
		case COP_REFLECT:
		case COP_SHEAR:
		case COP_SPAWN:
		case COP_STITCH:
		case COP_BLEND:
		case COP_EXTRACT:
			if(IsMeshMode())
				CurrentTaskID = GetCreOMMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			else
				CurrentTaskID = GetCreOpMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			OnOptionSpawnOn(); // change RIGID->COPY 
			break;
		case GOP_DELETE:
			CurrentTaskID = GetDelMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			break;
		case GOP_EDIT:
		case GOP_MOVE:
			if(IsMeshMode())
				CurrentTaskID = GetMditMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			else
				CurrentTaskID = GetEditMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			OnOptionSpawnOn(); // change COPY->RIGID
			break;
		case GOP_POST:
			CurrentTaskID = GetPostMgr()->ReSetToolID(m_CurrentCntlID,m_CurrentIGenID, m_CurrentOperID);
			break;
		default:
			return 0L;
	}
	////////////////////////////////////// TaskID
	SetActiveToolType((int)CurrentTaskID);
	////////////////////////////////////// ModeLesses
	SendMessage(ID_RESET_MODELESS);
	////////////////////////////////////// String
	UpdateStaticControls();
	//////////
	return 0L;
}
	
void CDrGrafFrame::UpdateSpawnStat(CString& str)
{
	/////////////
	GetSpawnStat()->SetText(str);
	GetSpawnStat()->Invalidate();
	GetSpawnStat()->UpdateWindow();
	/////////////
}
	
void CDrGrafFrame::UpdateBLineStat(CString& str)
{
	/////////////
	GetBLineStat()->SetText(str);
	GetBLineStat()->Invalidate();
	GetBLineStat()->UpdateWindow();
	/////////////
}
	
void CDrGrafFrame::UpdateSnapStat(CString& str)
{
	/////////////
	GetSnapStat()->SetText(str);
	GetSnapStat()->Invalidate();
	GetSnapStat()->UpdateWindow();
	/////////////
}
	
void CDrGrafFrame::UpdateAutoAcceptStat(CString& str)
{
	/////////////
	GetAutoAcceptStat()->SetText(str);
	GetAutoAcceptStat()->Invalidate();
	GetAutoAcceptStat()->UpdateWindow();
	/////////////
}
	
void CDrGrafFrame::UpdateSingleSegStat(CString& str)
{
	/////////////
	GetSingleSegStat()->SetText(str);
	GetSingleSegStat()->Invalidate();
	GetSingleSegStat()->UpdateWindow();
	/////////////
}
	
void CDrGrafFrame::UpdateCntlStat(CString& str)
{
	/////////////
	GetCntlStat()->SetText(str);
	GetCntlStat()->Invalidate();
	GetCntlStat()->UpdateWindow();
	/////////////
}

void CDrGrafFrame::UpdateIGenStat(CString& str)
{
	/////////////
	GetIGenStat()->SetText(str);
	GetIGenStat()->Invalidate();
	GetIGenStat()->UpdateWindow();
	/////////////
}

void CDrGrafFrame::UpdateOperStat(CString& str)
{
	/////////////
	GetOperStat()->SetText(str);
	GetOperStat()->Invalidate();
	GetOperStat()->UpdateWindow();
	/////////////
}

void CDrGrafFrame::UpdateModeStat(CString& str)
{
	/////////////
	GetModeStat()->SetText(str);
	GetModeStat()->Invalidate();
	GetModeStat()->UpdateWindow();
	/////////////
}

long CDrGrafFrame::OnUpdateStatCntls(UINT wParam, long lParam)
{
	UpdateStaticControls();
	return 0L;
}
	
void CDrGrafFrame::UpdateStaticControls()
{
	////////////////////////////////////////// StatCntls
	UpdateModeStat(m_strModeID);
	UpdateCntlStat(m_strCntlID);
	UpdateIGenStat(m_strIGenID);
	UpdateCurrStat(m_strCurrID);
	UpdateOperStat(m_strOperID);
	////////////////////////////
}

long CDrGrafFrame::OnResetModeLess_Auxi(UINT wParam, long lParam)
{
	if(GetActiveToolType()<0)
		return 0L;
	/////////////
	ModeLessOn_Auxi();
	return 0L;
}

void CDrGrafFrame::ModeLessOn_Auxi()
{
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
//todo	GetMouAXMgr()->GetDLDMouse()->ModeLessOff_CUR();
/*
	GetMouAXMgr()->GetDLDMouse()->ModeLessOff_PAT();
	GetMouAXMgr()->GetDLDMouse()->ModeLessOff_SOL();
	GetMouAXMgr()->GetDLDMouse()->ModeLessOff_O3D();
	GetMouAXMgr()->GetDLDMouse()->ModeLessOff_SLD();
	GetMouAXMgr()->GetDLDMouse()->ModeLessOff_SUP();
*/
	////////////////////////////////////////////////
	switch(GetCurrentIGenID())
	{
		case MESH0D:
			GetCreOMMgr()->GetSolCreOp()->ModeLessOff();
			break;
		case MESH1D:
			GetCreOMMgr()->GetSolCreOp()->ModeLessOff();
			break;
		case MESH2D:
			GetCreOMMgr()->GetSolCreOp()->ModeLessOff();
			break;
		case MESH3D:
			GetCreOMMgr()->GetSolCreOp()->ModeLessOff();
			break;
//		case MBJ3D:
//			GetCreOpMgr()->GetSolCreOp()->ModeLessOff();
//			break;
		default:
			break;
	}
	////////////////////////////////////////////////// Turn off, if not Create
	if(m_CurrentOperID != COP_CREATE)
	{
		switch(m_CurrentOperID)	// Check for Creation by Spawning & Stitching
		{
			case COP_TRANSLATE:
			case COP_ROTATE:
			case COP_SCALE:
			case COP_REFLECT:
			case COP_SHEAR:
			case COP_SPAWN:
			case COP_STITCH:
			case COP_BLEND:
			case COP_EXTRACT:
				////////////////////////////////////////////////
				switch(GetCurrentIGenID())
				{
					case MESH0D:
						GetCreOMMgr()->GetSolCreOp()->ModeLessOn();
						break;
					case MESH1D:
						GetCreOMMgr()->GetSolCreOp()->ModeLessOn();
						break;
					case MESH2D:
						GetCreOMMgr()->GetSolCreOp()->ModeLessOn();
						break;
					case MESH3D:
						GetCreOMMgr()->GetSolCreOp()->ModeLessOn();
						break;
					case MBJ3D:
						GetCreOMMgr()->GetSolCreOp()->ModeLessOn();
						break;
					default:
						return;
				}
				///////
				return;

			default:
				return;
		}
	}
	//////////////////////////////////////////////////
	switch(GetMouseBoxType())
	{
		////////////////////////////////////////////////
		case ELEMDIMBOX:
		case NODEBOX:

//todo			GetMouAXMgr()->GetDLDMouse()->ModeLessOn_NOD();
			///////
			return;

		case CURVEBOX:

//			GetMouAXMgr()->GetDLDMouse()->ModeLessOn_CUR();
			///////
			return;

		case PATCHBOX:

//			GetMouAXMgr()->GetDLDMouse()->ModeLessOn_PAT();
			///////
			return;

		case SOLIDBOX:

//			GetMouAXMgr()->GetDLDMouse()->ModeLessOn_SOL();
			///////
			return;

		case OBJ3DBOX:

//			GetMouAXMgr()->GetDLDMouse()->ModeLessOn_O3D();
			///////
			return;

		case SUPPORTBOX:

//			GetMouAXMgr()->GetDLDMouse()->ModeLessOn_SUP();
			///////
			return;

		case STATICLOADBOX:

//			GetMouAXMgr()->GetDLDMouse()->ModeLessOn_SLD();
			///////
			return;

		default:
			return;
	}
	///////////////////////////////////////
}


long CDrGrafFrame::OnResetModeLess_Mesh(UINT wParam, long lParam)
{
	if(GetActiveToolType()<0)
		return 0L;
	/////////////
	ModeLessOn_Mesh();
	return 0L;
}

void CDrGrafFrame::ModeLessOn_Mesh()
{
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_CUR();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_PAT();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_SOL();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_O3D();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_SLD();
	GetMouseMgr()->GetDLDMouse()->ModeLessOff_SUP();
	////////////////////////////////////////////////
	switch(GetCurrentIGenID())
	{
		case MESH0D:
			GetCreOMMgr()->GetSolCreOp()->ModeLessOff();
			break;
		case MESH1D:
			GetCreOMMgr()->GetSolCreOp()->ModeLessOff();
			break;
		case MESH2D:
			GetCreOMMgr()->GetSolCreOp()->ModeLessOff();
			break;
		case MESH3D:
			GetCreOMMgr()->GetSolCreOp()->ModeLessOff();
			break;
//		case MBJ3D:
//			GetCreOpMgr()->GetSolCreOp()->ModeLessOff();
//			break;
		default:
			break;
	}
	////////////////////////////////////////////////// Turn off, if not Create
	if(m_CurrentOperID != COP_CREATE)
	{
		switch(m_CurrentOperID)	// Check for Creation by Spawning & Stitching
		{
			case COP_TRANSLATE:
			case COP_ROTATE:
			case COP_SCALE:
			case COP_REFLECT:
			case COP_SHEAR:
			case COP_SPAWN:
			case COP_STITCH:
			case COP_BLEND:
			case COP_EXTRACT:
				////////////////////////////////////////////////
				switch(GetCurrentIGenID())
				{
					case MESH0D:
						GetCreOMMgr()->GetSolCreOp()->ModeLessOn();
						break;
					case MESH1D:
						GetCreOMMgr()->GetSolCreOp()->ModeLessOn();
						break;
					case MESH2D:
						GetCreOMMgr()->GetSolCreOp()->ModeLessOn();
						break;
					case MESH3D:
						GetCreOMMgr()->GetSolCreOp()->ModeLessOn();
						break;
					case MBJ3D:
						GetCreOMMgr()->GetSolCreOp()->ModeLessOn();
						break;
					default:
						return;
				}
				///////
				return;

			default:
				return;
		}
	}
	//////////////////////////////////////////////////
	switch(GetMouseBoxType())
	{
		////////////////////////////////////////////////
		case ELEMDIMBOX:
		case NODEBOX:

			GetMouseMgr()->GetDLDMouse()->ModeLessOn_NOD();
			///////
			return;

		case CURVEBOX:

//			GetMouseMgr()->GetDLDMouse()->ModeLessOn_CUR();
			///////
			return;

		case PATCHBOX:

//			GetMouseMgr()->GetDLDMouse()->ModeLessOn_PAT();
			///////
			return;

		case SOLIDBOX:

//			GetMouseMgr()->GetDLDMouse()->ModeLessOn_SOL();
			///////
			return;

		case OBJ3DBOX:

//			GetMouseMgr()->GetDLDMouse()->ModeLessOn_O3D();
			///////
			return;

		case SUPPORTBOX:

			GetMouseMgr()->GetDLDMouse()->ModeLessOn_SUP();
			///////
			return;

		case STATICLOADBOX:

			GetMouseMgr()->GetDLDMouse()->ModeLessOn_SLD();
			///////
			return;

		default:
			return;
	}
	///////////////////////////////////////
}

long CDrGrafFrame::OnResetModeLess(UINT wParam, long lParam)
{
	if(GetActiveToolType()<0)
		return 0L;
	/////////////
	ModeLessOn();
	return 0L;
}

void CDrGrafFrame::ModeLessOn()
{
	GetCreOpMgr()->GetSolCreOp()->ModeLessOff();
	////////////////////////////////////////////////// Turn off, if not Create
	if(m_CurrentOperID != COP_CREATE)
	{
		switch(m_CurrentOperID)	// Check for Creation by Spawning & Stitching
		{
			case COP_TRANSLATE:
			case COP_ROTATE:
			case COP_SCALE:
			case COP_REFLECT:
			case COP_SHEAR:
//			case COP_SPAWN:
//			case COP_STITCH:
//			case COP_BLEND:
				GetCreOpMgr()->GetSolCreOp()->ModeLessOn();break;
				///////
				return;
			///////////////////////////////////////////////////// Post
			case GOP_POST:
				////////////////////////////////////////////////
				switch(GetCurrentIGenID())
				{
					case NODE:
					case INODE:
					case CNODE:GetPostMgr()->GetDLDMouse()->ModeLessOn_NOD();break;
					case CURVE:GetPostMgr()->GetDLDMouse()->ModeLessOn_CUR();break;
					case PATCH:GetPostMgr()->GetDLDMouse()->ModeLessOn_PAT();break;
					case SOLID:
//						GetPostMgr()->GetDLDMouse()->ModeLessOn_SOL();
						break;
					default:return;
				}
				///////
				return;


			default:
				return;
		}
	}
	else
	{
		//////////////////////////////////////////////////
		switch(GetMouseBoxType())
		{
			////////////////////////////////////////////////
			case ELEMDIMBOX:
			case NODEBOX:GetMouseMgr()->GetDLDMouse()->ModeLessOn_NOD();
//				GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_CUR();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_PAT();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SOL();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_O3D();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SLD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SUP();
				////////////////////////////////////////////////
				return;
			case CURVEBOX:GetMouseMgr()->GetDLDMouse()->ModeLessOn_CUR();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
//				GetMouseMgr()->GetDLDMouse()->ModeLessOff_CUR();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_PAT();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SOL();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_O3D();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SLD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SUP();
				////////////////////////////////////////////////
				return;
			case PATCHBOX:GetMouseMgr()->GetDLDMouse()->ModeLessOn_PAT();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_CUR();
//				GetMouseMgr()->GetDLDMouse()->ModeLessOff_PAT();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SOL();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_O3D();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SLD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SUP();
				////////////////////////////////////////////////
				return;
			case SOLIDBOX:GetMouseMgr()->GetDLDMouse()->ModeLessOn_SOL();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_CUR();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_PAT();
//				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SOL();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_O3D();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SLD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SUP();
				////////////////////////////////////////////////
				return;
			case OBJ3DBOX:GetMouseMgr()->GetDLDMouse()->ModeLessOn_O3D();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_CUR();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_PAT();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SOL();
//				GetMouseMgr()->GetDLDMouse()->ModeLessOff_O3D();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SLD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SUP();
				////////////////////////////////////////////////
				return;
			case SUPPORTBOX:GetMouseMgr()->GetDLDMouse()->ModeLessOn_SUP();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_CUR();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_PAT();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SOL();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_O3D();
//				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SUP();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SLD();
				////////////////////////////////////////////////
				return;
			case STATICLOADBOX:GetMouseMgr()->GetDLDMouse()->ModeLessOn_SLD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_NOD();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_CUR();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_PAT();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SOL();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_O3D();
				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SUP();
//				GetMouseMgr()->GetDLDMouse()->ModeLessOff_SLD();
				////////////////////////////////////////////////
				return;
			default:return;
		}
	}
	///////////////////////////////////////
}

void CDrGrafFrame::OnModeInput()
{
	if(GetOpMode() == OP_INPUT) // already
		return;
	/////////////////
	SetOpMode(OP_INPUT);
	SwitchMenu(IDR_INPUTMENU);
	////////////////////////////////////////// Activate Data Dialog, if Any
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///
	pDoc->GetObjectMgr()->SetViewChanged(TRUE);
	///////////////////////////////////////////////////////////////////////// sets m_nView in
/*																		   // CDrGrafFrame 

	////////////////////////////////////////// 
	CMDIChildWnd* pMDIActive = MDIGetActive();
	if(!pMDIActive)
		return;
	///////////////	
//	CDocument* pDoc = pMDIActive->GetActiveDocument();
	if(pDoc)
	{
   		/////////////
		CView* pView;
		POSITION pos = pDoc->GetFirstViewPosition();
		while (pos)
		{
			pView = pDoc->GetNextView(pos);
//			pView->GetParentFrame()->ShowWindow(SW_HIDE);
			///////////////////////////////////////////// Scale Changed
			((CDrawView*)pView)->SetOpMode(OP_INPUT);
			((CDrawView*)pView)->SetScalevv3DToLP();
			///////////////////////////////////
		}
		///////////////////////////////////////////// View Changed
		((CDrGrafDoc*)pDoc)->GetObjectMgr()->SetViewChanged(TRUE);
		/////////////////////////////////////////////
	}
*/
	////////////////
/*
	OnModeChange();
	////////////////////////////
	m_wndCntlBox.ShowWindow(SW_SHOW);
	if(IsMeshMode())
		m_wndMGenBox.ShowWindow(SW_SHOW);
	else
		m_wndIGenBox.ShowWindow(SW_SHOW);
	m_wndOperBox.ShowWindow(SW_SHOW);
*/
	GetCntlStat()->ShowWindow(SW_SHOW);
	GetIGenStat()->ShowWindow(SW_SHOW);
	GetOperStat()->ShowWindow(SW_SHOW);
	GetCurrStat()->ShowWindow(SW_SHOW);
//		m_wndDrawBox.ShowWindow
//			((m_wndDrawBox.GetStyle() & WS_VISIBLE) == 0);
        /////////////
	////////////////////////////
	ModeLessOn();
	/////////////
}

void CDrGrafFrame::OnModeOutput()
{
	if(GetOpMode() == OP_OUTPUT) // already
		return;
	/////////////////
	SetOpMode(OP_OUTPUT);
	SwitchMenu(IDR_OUTPUTMENU);
	////////////////////////////////////////// Activate Data Dialog, if Any
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///
	pDoc->GetObjectMgr()->SetViewChanged(TRUE);
	////////////////
/*
	OnModeChange();
	//////////////////////////// close IGenBox, CntlBox
	if(IsMeshMode())
		m_wndMGenBox.ShowWindow(SW_HIDE);
	else
		m_wndIGenBox.ShowWindow(SW_HIDE);
	/////////////////////////////////////
	m_wndEDimBox.ShowWindow(SW_HIDE);
	m_wndCntlBox.ShowWindow(SW_HIDE);
	m_wndOperBox.ShowWindow(SW_HIDE);
*/
	GetCntlStat()->ShowWindow(SW_HIDE);
	GetIGenStat()->ShowWindow(SW_HIDE);
	GetOperStat()->ShowWindow(SW_HIDE);
	GetCurrStat()->ShowWindow(SW_HIDE);
	///////////////////////	
	ModeLessOff();
	//////////////////
}

void CDrGrafFrame::OnTimer(UINT nIDEvent)
{
	if(nIDEvent == TM_CLOCK)
	{
		CClock clock; 
		CString strDate,strTime;
	
		clock.GetTimeDate(&strDate,&strTime);
 
		GetSBarTop()->SetPaneText(8,strTime,TRUE);
		GetSBarTop()->SetPaneText(10,strDate,TRUE);
	}
	else
	if(nIDEvent == TM_BANNER)
	{
/*
		CBanner* pBanWnd = ((CDrGrafApp*)AfxGetApp())->GetBannerWnd();
//		pBanWnd->DissolveRect();
		pBanWnd->DestroyWindow(); 
*/		
	    /////////////////////////////////////////	
	    KillTimer(TM_BANNER);
		/////////////////////
	}			   
	if(nIDEvent == TM_MEMORY)
	{
/*
	///////////////////////////////////////////////////////
	// MEMORY WILL BE SWITCHED TO DIALOG OPTION					todo june96
	///////////////////////////////////////////////////////
typedef struct _MEMORYSTATUS { // mst 
    DWORD dwLength;        // sizeof(MEMORYSTATUS) 
    DWORD dwMemoryLoad;    // percent of memory in use 
    DWORD dwTotalPhys;     // bytes of physical memory 
    DWORD dwAvailPhys;     // free physical memory bytes 
    DWORD dwTotalPageFile; // bytes of paging file 
    DWORD dwAvailPageFile; // free bytes of paging file 
    DWORD dwTotalVirtual;  // user bytes of address space 
    DWORD dwAvailVirtual;  // free user bytes 
} MEMORYSTATUS, *LPMEMORYSTATUS; 
 
  
The MEMORYSTATUS structure contains information about current memory availability. The GlobalMemoryStatus function uses this structure. 
Members
dwLength
Indicates the size of the structure. The calling process should set this member prior to calling GlobalMemoryStatus. 
dwMemoryLoad
Specifies a number between 0 and 100 that gives a general idea of current memory utilization, in which 0 indicates no memory use and 100 indicates full memory use. 
dwTotalPhys
Indicates the total number of bytes of physical memory. 
dwAvailPhys
Indicates the number of bytes of physical memory available. 
dwTotalPageFile
Indicates the total number of bytes that can be stored in the paging file. Note that this number does not represent the actual physical size of the paging file on disk. 
dwAvailPageFile
Indicates the number of bytes available in the paging file. 
dwTotalVirtual
Indicates the total number of bytes that can be described in the user mode portion of the virtual address space of the calling process. 
dwAvailVirtual
Indicates the number of bytes of unreserved and uncommitted memory in the user mode portion of the virtual address space of the calling process. 
See Also
GlobalMemoryStatus 
*/
 
//		DWORD dwFreeMem = GetFreeSpace(0);
		MEMORYSTATUS memStat;
		memStat.dwLength = sizeof(MEMORYSTATUS); 
		GlobalMemoryStatus(&memStat);
		/////////////////////////////
		CString str;
		char Buf[40];
		sprintf(Buf,"%.2f Free  %.2f Total(Megs)",
			memStat.dwAvailVirtual/1024./1024.,
			memStat.dwTotalVirtual/1024./1024.); 
 
		GetSBarTop()->SetPaneText(6,str = Buf,TRUE);
	}
}

//void CDrGrafFrame::OnWinIniChange(LPCSTR lpszSection)	OBSOLETE from VC++ 5.0 Ver
void CDrGrafFrame::OnSettingChange(UINT uFlags, LPCSTR lpszSection)
{
	CMDIFrameWnd::OnSettingChange(uFlags,lpszSection);  // in WinCore,Cpp of MFC source
	///////////////////
	CClock clock;
	clock.SetInternational();
	///////////////////
	
}

void CDrGrafFrame::OnWindowNew3dView() 
{

	CDrGrafChildFrame* pMDIActive = (CDrGrafChildFrame*)MDIGetActive();
	ASSERT(pMDIActive != NULL);
	/////////////////////////////////////////////////
	CDocument* pDoc = pMDIActive->GetActiveDocument();
	ASSERT(pDoc != NULL);
    /////////////////////////////////////////
	// otherwise we have a new frame !
	CDocTemplate* pTemplate = ((CDrGrafApp*)AfxGetApp())->Get3DViewTemplate();		//3D View
	ASSERT_VALID(pTemplate);
	CDrGrafChildFrame* pFrame
		= (CDrGrafChildFrame*)(pTemplate->CreateNewFrame(pDoc, NULL));
	if (pFrame == NULL)
	{
		TRACE0("Warning: failed to create new frame.\n");
		return;     // command failed
	}
	////////////////////
	pTemplate->InitialUpdateFrame(pFrame, pDoc);
	///////////////////////////////////////////////// Set Properties
	OnAddl3dview();
}

void CDrGrafFrame::OnUpdateWindowNew3dView(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnDebugCalctime() 
{
	m_bDebugCTim = !m_bDebugCTim;
	/////////////////////////////
	if(m_bDebugCTim)
		GetDlg_CTim()->ShowWindow(TRUE);
	else
		GetDlg_CTim()->ShowWindow(FALSE);
	/////////////////////////////////////
}

void CDrGrafFrame::OnUpdateDebugCalctime(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((GetDlg_CTim()->GetStyle() & WS_VISIBLE) != 0);
}

void CDrGrafFrame::OnViewAllview() 
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////////////  
	if(GetOpMode() == OP_INPUT)
	{
		if(!pBool->IsIsoViewActive() )
			OnView3dview();
		/////////////////////////////
		if(!pBool->Is12ViewActive() )
			OnView12view();	// do these last, so appropriate tools show
		if(!pBool->Is23ViewActive() )
			OnView23view();
		if(!pBool->Is31ViewActive() )
			OnView31view();
	}
	else
	if(GetOpMode() == OP_OUTPUT)
	{
		if(!pBool->Is12ViewActive() )
			OnView12view();	
		if(!pBool->Is23ViewActive() )
			OnView23view();
		if(!pBool->Is31ViewActive() )
			OnView31view();
		/////////////////////////////
		if(!pBool->IsIsoViewActive() )
			OnView3dview();// do these last, so appropriate tools show
	}
	//////////////////////////////
	MDITile(MDITILE_SKIPDISABLED);
	//////////////////////////////
}

void CDrGrafFrame::OnUpdateViewAllview(CCmdUI* pCmdUI) 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->IsIsoViewActive() );
	
}

void CDrGrafFrame::OnViewSpectra() 
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleSpViewActive();
	if(pBool->IsSpViewActive() )
	{
		SetActiveViewNumber(VIEWSPECTRA_IN);
		////////////////////////////
		CreateOrActivateFrame(((CDrGrafApp*)AfxGetApp())->GetSpecViewTemplate(), 
			RUNTIME_CLASS(CSpDrawVu));
	}
	else
	    CloseView(RUNTIME_CLASS(CSpDrawVu));
	
}

void CDrGrafFrame::OnUpdateViewSpectra(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnViewDatabaseFormdata() 
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CAxObjMgr* pObjectMgr 	= pDoc->GetAxObjMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleFormDataViewActive();
	if(pBool->IsFormDataViewActive() )
	{
		SetActiveViewNumber(VIEWFORMDATA);
		////////////////////////////
		CreateOrActivateFrame(((CDrGrafApp*)AfxGetApp())->GetFormViewTemplate(), 
			RUNTIME_CLASS(CDrTreeVu));
	}
	else
	    CloseView(RUNTIME_CLASS(CDrTreeVu));
	
}

void CDrGrafFrame::OnUpdateViewDatabaseFormdata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnUpdateModeAuxilliarySpatial(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnModeAuxilliarySpectral() 
{
	/////////////////
	SetOpMode(OP_SPECTRA_IN);
	SwitchMenu(IDR_AUXINPUT);
	////////////////////////////////////////// Activate Data Dialog, if Any
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	///////////////////////////////////////////////////////////////////////// sets m_nView in
																		   // CDrGrafFrame 
	////////////////////////////////////////// 
	CMDIChildWnd* pMDIActive = MDIGetActive();
	if(!pMDIActive)
		return;
	///////////////	
//	CDocument* pDoc = pMDIActive->GetActiveDocument();
	if(pDoc)
	{
   		/////////////
		CView* pView;
		POSITION pos = pDoc->GetFirstViewPosition();
		while (pos)
		{
			pView = pDoc->GetNextView(pos);
			pView->GetParentFrame()->ShowWindow(SW_HIDE);
			///////////////////////////////////////////// Scale Changed
//			((CSpDrawVu*)pView)->SetOpMode(OP_SPECTRA_IN);
//			((CSpDrawVu*)pView)->SetScalevv3DToLP();
			///////////////////////////////////
		}
		///////////////////////////////////////////// View Changed
		((CDrGrafDoc*)pDoc)->GetObjectMgr()->SetViewChanged(TRUE);
		/////////////////////////////////////////////
		CObjectMgr* pObjectMgr 	= ((CDrGrafDoc*)pDoc)->GetObjectMgr();
		CBooleans* pBool = 
			(CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
		pBool->ToggleSpViewActive();
		//////////////
		OnViewSpectra();
		SetActiveViewNumber(VIEWSPECTRA_IN);
		////////////////////////////
		m_wndCntlBox.ShowWindow(SW_SHOW);
		////////////////////
/*
		m_wndIGenBox.ShowWindow(SW_SHOW);
		m_wndOperBox.ShowWindow(SW_SHOW);
*/
		GetCntlStat()->ShowWindow(SW_SHOW);
		GetIGenStat()->ShowWindow(SW_SHOW);
		GetOperStat()->ShowWindow(SW_SHOW);
		GetCurrStat()->ShowWindow(SW_SHOW);
//		m_wndDrawBox.ShowWindow
//			((m_wndDrawBox.GetStyle() & WS_VISIBLE) == 0);
        /////////////
	}
	////////////////////////////
	ModeLessOn();
	/////////////
}

void CDrGrafFrame::OnUpdateModeAuxilliarySpectral(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnModeAuxilliaryTemporal() 
{
	// TODO: Add your command handler code here
	
}

void CDrGrafFrame::OnUpdateModeAuxilliaryTemporal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnOptionSnaponObjmerg() 
{

	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pBool->ToggleSnapOn();
	////////////////////////////
	CString str1 = "Merge ON";
	CString str2 = "Merge OFF";
	//
	if(pBool->IsSnapOn())
		UpdateSnapStat(str1);
	else
		UpdateSnapStat(str2);
	
}

void CDrGrafFrame::OnUpdateOptionSnaponObjmerg(CCmdUI* pCmdUI) 
{
	CDrGrafDoc* pDoc 		= ((CDrGrafApp*)AfxGetApp())->GetDocument();
	CObjectMgr* pObjectMgr 	= pDoc->GetObjectMgr();
	/////////////////////////////////////////////// 
	CBooleans* pBool = (CBooleans*)pObjectMgr->GetSpecObject(BOOLEANS);
	////////////////////////////////////////// 
	pCmdUI->SetCheck(pBool->IsSnapOn());
}
/////////////////////////////////////////// end of Module //////////////////////////////////
