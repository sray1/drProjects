// drgracfm.cpp : implementation file
//
#include "stdafx.h"
//#include "resource.h" 

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
	// By turning off the default MFC-defined FWS_ADDTOTITLE style,
	// the framework will use first string in the document template
	// STRINGTABLE resource instead of the document name.

	cs.style &= ~(LONG)FWS_ADDTOTITLE;
	return CMDIChildWnd::PreCreateWindow(cs);
}


BEGIN_MESSAGE_MAP(CDrGrafChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CDrGrafChildFrame)
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrGrafChildFrame message handlers
/////////////////////////////////////////////////////////////////////////////

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
		pWnd->MDISetMenu(pWnd->GetOpenMenu(),NULL);
		if(!(pWnd->GetElementBox()->GetStyle() & WS_VISIBLE) ) 
			pWnd->GetElementBox()->ShowWindow(TRUE);
		if(!(pWnd->GetDrawBox()->GetStyle() & WS_VISIBLE) )	
			pWnd->GetDrawBox()->ShowWindow(TRUE);								
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
	DrawMenuBar(); 
		
	// TODO: Add your message handler code here
	
}


CMenu FAR CDrGrafChildFrame::menu;        // menu for all ChildFrame windows

int CDrGrafChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{ 
/*
	// Setup the shared menu
	if (menu.m_hMenu == NULL)
		menu.LoadMenu(IDR_OPENMENU);
	m_hMenuShared = menu.m_hMenu;
*/
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
//////////////////////////////////		
	// TODO: Add your specialized creation code here
///////////////////////
	return 0;
}

