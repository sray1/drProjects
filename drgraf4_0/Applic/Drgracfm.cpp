// drgracfm.cpp : implementation file
//
#include "stdafx.h"
#include <afxpriv.h>	//HID_BASE_COMMAND

#include "resource.h"
#include "DrawView.h"
//#include "globals.h"
/////////////////////
#include "drgrafrm.h"
#include "drgracfm.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrGrafChildFrame

IMPLEMENT_DYNCREATE(CDrGrafChildFrame, CMDIChildWnd) 

int CDrGrafChildFrame::m_nDefCmdShow = SW_SHOWMAXIMIZED;
int CDrGrafChildFrame::m_nDefCmdShowOld = SW_SHOWMAXIMIZED;

static char BASED_CODE szSec[] = "Settings";
static char BASED_CODE szShowCmd[] = "ShowCmd";  


void CDrGrafChildFrame::ActivateFrame(int nCmdShow)
{
	if (nCmdShow == -1)
		nCmdShow = m_nDefCmdShow;   // use our default
//	CMDIChildWnd::ActivateFrame(nCmdShow);
	CMDIChildWnd::ActivateFrame(SW_SHOWNORMAL);
	
}

void CDrGrafChildFrame::Initialize()
{
	m_nDefCmdShow = AfxGetApp()->GetProfileInt(szSec, szShowCmd, m_nDefCmdShow);
	m_nDefCmdShowOld = m_nDefCmdShow;
}

void CDrGrafChildFrame::Terminate()
{
	if (m_nDefCmdShow != m_nDefCmdShowOld)
	{
		AfxGetApp()->WriteProfileInt(szSec, szShowCmd, m_nDefCmdShow);
		m_nDefCmdShowOld = m_nDefCmdShow;
	}
}



CDrGrafChildFrame::CDrGrafChildFrame()
{
}

CDrGrafChildFrame::~CDrGrafChildFrame()
{
}

BOOL CDrGrafChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	///////////////////////////////// Replace Back to MainFrame Menu  
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////////////////////// Menu	
	// By turning off the default MFC-defined FWS_ADDTOTITLE style,
	// the framework will use first string in the document template
	// STRINGTABLE resource instead of the document name.

	cs.style		&= ~(LONG)FWS_ADDTOTITLE;
	/////////////////////////////////////
	CRect BoxRect;
	int Boxwidth,Boxheight; 
	int Width12	= ::GetSystemMetrics(SM_CXSCREEN) - 2;	// for adjustment of View12 Size
	int Left12		= -1;
/*
	////////////////////////////////////////////////////////////// IGenBox 
	Boxwidth  = (int)(pWnd->GetIGenBox()->GetWidth());
	Boxheight = (int)(pWnd->GetIGenBox()->GetHeight()); 

   	BoxRect.left   = 0;
   	BoxRect.right  = BoxRect.left + Boxwidth; //
   	BoxRect.top    = 0;   //
   	BoxRect.bottom = BoxRect.top   + Boxheight;
//	ClientToScreen(&Rect);
	::AdjustWindowRect(&BoxRect,WS_BORDER|WS_CAPTION,FALSE);
	//////////////////////////////////////////// OutToOut
	Boxwidth  = BoxRect.Width();
	////////////////////////////// View12 Adjustment
	Width12		-= Boxwidth; 
	////////////////////////////////////////////////////////////// CntlBox 
	Boxwidth  = (int)(pWnd->GetCntlBox()->GetWidth());
	Boxheight = (int)(pWnd->GetCntlBox()->GetHeight()); 

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
*/
	//////////////////////////////////////////// StatusBars
	CRect STopRect,SBotRect;
	pWnd->GetSBarTop()->Init();
	pWnd->GetSBarTop()->ShowWindow(SW_SHOW);
	pWnd->RecalcLayout();
	pWnd->GetSBarBot()->Init();
	pWnd->GetSBarBot()->ShowWindow(SW_SHOW);
	pWnd->RecalcLayout();

	pWnd->GetSBarTop()->GetWindowRect(&STopRect); // screen Coords
	pWnd->GetSBarBot()->GetWindowRect(&SBotRect); // screen Coords
	////////////////////////////////////////////////////////////////////////////// 12View Adjust
	CRect Rect12;
	/////////////
   	Rect12.left		= Left12; //
   	Rect12.right	= Rect12.left + Width12;
   	Rect12.top		= STopRect.bottom; //
   	Rect12.bottom	= SBotRect.top; //
	//////////////////////////////////
	pWnd->ScreenToClient(&Rect12);
	///////////////////////////////////////////////////////////////////////
	pWnd->GetClientRect(&Rect12);
	pWnd->ScreenToClient(&SBotRect);
	SBotRect.NormalizeRect(); 
	////////////////////////////////////////
	cs.x		= Rect12.left;
	cs.cx		= Rect12.right - Rect12.left;
//	cs.y		= Rect12.top;
	cs.y		= 0;
	cs.cy		= Rect12.bottom - Rect12.top - 3*SBotRect.Height();
	//////////////////////////////////
	return CMDIChildWnd::PreCreateWindow(cs);
}


BEGIN_MESSAGE_MAP(CDrGrafChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CDrGrafChildFrame)
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_CREATE()
	ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_HELP, OnUpdateContextHelp)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_INDEX, CFrameWnd::OnHelpIndex)
	ON_COMMAND(ID_HELP_USING, CFrameWnd::OnHelpUsing)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpIndex)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrGrafChildFrame message handlers
/////////////////////////////////////////////////////////////////////////////

LRESULT CDrGrafChildFrame::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{

	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd); 
	//////////////////
	if (lParam == 0)
	{
		if(m_nIDTracking > 0xe001)
		{
			// frame's own Menu ( system Menu)
			lParam = HID_BASE_COMMAND+m_nIDTracking;
		}
		else
		{
			/////////////////////////////////////////////
			CDrawView* pActiveView = (CDrawView*)GetActiveView();
			if (pActiveView)
			{
				// handled by View
				pActiveView->SendMessage(WM_COMMANDHELP,wParam,0L);
			}
			else
			{
				// handle by MDIClient
				OPMODE OpMode = pWnd->GetOpMode();
				//////////////////////////////////
				if(OpMode == OP_INPUT)
					lParam = HID_BASE_COMMAND+IDR_INPUTMENU;
				else	  
				if(OpMode == OP_OUTPUT)
					lParam = HID_BASE_COMMAND+IDR_OUTPUTMENU;
				else	  
					lParam = HID_BASE_COMMAND+IDR_MAINFRAME;
			}
		}
	}
	if (lParam != 0)
	{
		AfxGetApp()->WinHelp(lParam);
		return TRUE;
	}
	return FALSE;
}

void CDrGrafChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	if (!IsWindowVisible())
		return;

	switch (nType)
	{
	case SIZE_MAXIMIZED:
		m_nDefCmdShow = SW_SHOWMAXIMIZED;
		break;
	case SIZE_RESTORED:
		m_nDefCmdShow = SW_SHOWNORMAL;
		break;
	}
}

void CDrGrafChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
///////////////////////////////////////////////////////////////////////// Change MENU	

	CDrGrafFrame* pWnd=(CDrGrafFrame*)(AfxGetApp()->m_pMainWnd); 
	///////////////////////////// Show ElementBar/Set Open Menu/Show DrawBox 
	if(bActivate) 
	{
		///////////////////////////////
//		pWnd->MDITile(MDITILE_SKIPDISABLED);
/*
		pWnd->MDISetMenu(pWnd->GetOpenMenu(),NULL);
		if(!(pWnd->GetElementBox()->GetStyle() & WS_VISIBLE) ) 
			pWnd->GetElementBox()->ShowWindow(TRUE);
		if(!(pWnd->GetDrawBox()->GetStyle() & WS_VISIBLE) )	
			pWnd->GetDrawBox()->ShowWindow(TRUE);
*/											
	}
	else
	{
		//////////////////////////////////////////// Only when ALL VIEWS deact. TOBEDONE
/*
		pWnd->MDISetMenu(&(pWnd->m_InitMenu),NULL);
		pWnd->m_wndElementBar.ShowWindow((m_wndElementBar.GetStyle() & WS_VISIBLE) == 0);
		pWnd->m_wndDrawBox.ShowWindow((m_wndDrawBox.GetStyle() & WS_VISIBLE) == 0);	
*/									
	}		
//	DrawMenuBar(); 
		
	// TODO: Add your message handler code here
	
}


//CMenu FAR CDrGrafChildFrame::menu;        // menu for all ChildFrame windows

int CDrGrafChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{ 

	///////////////////////////////// Replace Back to MainFrame Menu  
	CDrGrafFrame* pWnd = (CDrGrafFrame*)(AfxGetApp()->m_pMainWnd);
	//////////////////////////////////////////////////////////// Menu	
	// Setup the shared menu
//	if (menu.m_hMenu == NULL)
//		menu.LoadMenu(IDR_DRGRAFTYPE);
/*
	if(pWnd->GetOpMode() == OP_INPUT)
		m_hMenuShared = pWnd->GetInputMenu()->m_hMenu;
	else	
	if(pWnd->GetOpMode() == OP_OUTPUT)
		m_hMenuShared = pWnd->GetOutputMenu()->m_hMenu;
*/
    ////////////////////////////////////////////////////////////
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
//////////////////////////////////		
	// TODO: Add your specialized creation code here
///////////////////////
	return 0;
}
////////////////////////////////////////// end of module //////////////////////

void CDrGrafChildFrame::OnContextHelp() 
{
	m_bHelpMode = !m_bHelpMode;
	///////////////////////////
	CFrameWnd::OnContextHelp();
	// TODO: Add your command handler code here
	
}

void CDrGrafChildFrame::OnUpdateContextHelp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
