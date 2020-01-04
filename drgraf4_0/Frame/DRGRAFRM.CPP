// drgrafrm.cpp : implementation of the CDrGrafFrame class
//
#include "stdafx.h" 
#include "stdio.h"
/////////////////////  
#include "drgraf.h"
#include "drgradoc.h" 
#include "drgrafrm.h"   

#include "12view.h"
#include "23view.h"
#include "31view.h"
#include "isoview.h"
#include "dataview.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
// CDrGrafFrame
IMPLEMENT_DYNAMIC(CDrGrafFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CDrGrafFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CDrGrafFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_MESSAGE(ELM_SUPPORT,OnSupportBar)
	ON_COMMAND(IDM_VIEW_ELEMENTBOX, OnViewElementbox)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_ELEMENTBOX, OnUpdateViewElementbox)
	ON_COMMAND(IDM_VIEW_DRAWBOX, OnViewDrawbox)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_DRAWBOX, OnUpdateViewDrawbox)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_DIALOGON, OnUpdateOptionDialogOn)
	ON_COMMAND(IDM_OPTION_DIALOGON, OnOptionDialogOn)
	ON_COMMAND(IDM_OPTION_RUBBERBAND, OnOptionRubberband)
	ON_UPDATE_COMMAND_UI(IDM_OPTION_RUBBERBAND, OnUpdateOptionRubberband)
	ON_WM_TIMER()
	ON_WM_WININICHANGE()
	ON_COMMAND(IDM_VIEW_12VIEW, OnView12view)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_12VIEW, OnUpdateView12view)
	ON_COMMAND(IDM_VIEW_23VIEW, OnView23view)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_23VIEW, OnUpdateView23view)
	ON_COMMAND(IDM_VIEW_31VIEW, OnView31view)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_31VIEW, OnUpdateView31view)
	ON_COMMAND(IDM_VIEW_ISOVIEW, OnViewIsoview)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_ISOVIEW, OnUpdateViewIsoview)
	ON_COMMAND(IDM_VIEW_S_BAR_BOT, OnViewSBarBot)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_S_BAR_BOT, OnUpdateViewSBarBot)
	ON_COMMAND(IDM_VIEW_S_BAR_TOP, OnViewSBarTop)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_S_BAR_TOP, OnUpdateViewSBarTop)
	ON_COMMAND(IDM_VIEW_DATAVIEW, OnViewDataView)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_DATAVIEW, OnUpdateViewDataView)
	//}}AFX_MSG_MAP
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
	ID_SEPARATOR			// status line indicator
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
//array ofIDs Used to Initialize ElementBar

static UINT BASED_CODE element[] =
{
	// same order as in the bitmap 'element.bmp'
	IDB_EL_NODE,
	IDB_EL_PIPE,
	IDB_EL_ELBOW,
	IDB_EL_BEAM,
	IDB_EL_SUPPORT,
	IDB_EL_TRUSS,
	IDB_EL_PLANE,
	IDB_EL_PLATE,
	IDB_EL_SHELL
};

//array ofIDs Used to Initialize SupportBar

static UINT BASED_CODE support[] =
{
	// same order as in the bitmap 'support.bmp'
	IDB_SUP_TRAN_SPRING,
	IDB_SUP_ROT_SPRING,
	IDB_SUP_FIXED_SUPPORT,
	IDB_SUP_TRAN_SNUBBER,
	IDB_SUP_ROT_SNUBBER,
	IDB_SUP_ANCHOR,
	IDB_SUP_ROLLER
};

/////////////////////////////////////////////////////////////////////////////
// CDrGrafFrame construction/destruction

CDrGrafFrame::CDrGrafFrame()
{
	/////////////////// Menu shared will be worked on later
	m_InitMenu.LoadMenu(IDR_INITMENU);                     // dont need to:preloaded
	m_OpenMenu.LoadMenu(IDR_OPENMENU);                     // done in childfrm creation
	////////////////////////////////////////////////////////
	m_nElementCol = 1;
	m_nSupportCol = sizeof(support)/sizeof(UINT);
	///////////////////                                Readin Defaults
	ReadDefaults();
	///////////////////                                Initialize Member Data
	Initialize();	     
	/////////////////////
	// TODO: add member initialization code here
}

CDrGrafFrame::~CDrGrafFrame()
{
}

int CDrGrafFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	/////////////////////// set LogFont/TextColor
	CDrGrafDoc* pDoc 	= (CDrGrafDoc*)(theApp.m_pDoc );
	CGrafObject* pObjectMgr = pDoc->GetObjectMgr();
	CDBoxMgr* pDBoxMgr    	= pObjectMgr->GetDBoxMgr();
	CDrFont* pDrFont	= pDBoxMgr->GetDrFont();
	////////////////////////////////////////////////////////// Frame Window
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	////////////////////////////////////////////////////////// Clock Timer
	if (!SetTimer(ID_CLOCK_TIMER, 1000 /*1000 msec = 1 sec*/, NULL))
	{
		MessageBox("Not enough timers available for this window.",
				"Frame:OnCreate", MB_ICONEXCLAMATION | MB_OK);

		// signal creation failure...
		return -1;
	} 
	////////////////////////////////////////////////////////// Top ToolBar
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE("Failed to create toolbar\n");
		return -1;		// fail to create
	}
	RecalcLayout();
	////////////////////////////////////////////////////////// Top StatusBar
	if (!m_wndStatusBarTop.Create(this,WS_CHILD|CBRS_TOP,
			IDS_TOP_STATUSBAR) ||
		!m_wndStatusBarTop.SetIndicators(top_indicators,
		  sizeof(top_indicators)/sizeof(UINT)))
	{
		TRACE("Failed to create Top status bar\n");
		return -1;		// fail to create
	}
	////////////////////////////////////////////////////////// Bottom StatusBar
	if (!m_wndStatusBar.Create(this,WS_CHILD|WS_VISIBLE|CBRS_BOTTOM,
			IDS_BOT_STATUSBAR) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("Failed to create status bar\n");
		return -1;		// fail to create
	}
	/////////////////// Get the 0 pane ready
	CString str;
	UINT nID, nStyle;
	int cxWidth;

	m_wndStatusBar.GetPaneInfo(0,nID,nStyle,cxWidth);
	m_wndStatusBar.SetPaneInfo(0,nID,SBPS_STRETCH,cxWidth);
	RecalcLayout();
	////////////////////////////////////////////////////////// DrawBox
	RECT Rect;
//  CreateExWrapper is a HACK to avoid assertion error w/ CWnd::Create
//	 and WS_POPUP style in wincore.cpp, line 349.

	Rect.left=Rect.top=Rect.right=Rect.bottom=0;
	m_wndDrawBox.CreateExWrapper(	"AfxWnd",
								NULL,
								WS_POPUP|WS_CAPTION,
								Rect,
								this,
								0);
	////////////////////////////
	CSize szButton,szImage;
	///////////////////////
	szButton.cx  = DB_BNSIZE_CX;
	szButton.cy  = DB_BNSIZE_CY; 
		
	szImage.cx   = DB_IMAGE_CX;
	szImage.cy   = DB_IMAGE_CY;
		
	m_wndDrawBox.m_wndPaletteBar.SetSizes(szButton,szImage);
    m_wndDrawBox.ShowWindow(SW_HIDE);
	////////////////////////////////////////////////////////// ElementBox
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	
	if (!m_wndElementBar.Create(this, rect.left, rect.top) ||
		!m_wndElementBar.LoadBitmap(IDB_ELEMENT) ||
		!m_wndElementBar.SetButtons(element,
		  sizeof(element)/sizeof(UINT),m_nElementCol,TRUE)) // NOTE: FALSE = NO CAPTION
	{	
		AfxMessageBox("Cannot Create ElementBar");
		return -1;
    }
	////////////////////////////
	szButton.cx  = EL_BNSIZE_CX;
	szButton.cy  = EL_BNSIZE_CY; 
		
	szImage.cx   = EL_IMAGE_CX;
	szImage.cy   = EL_IMAGE_CY;
		
	m_wndElementBar.SetSizes(szButton,szImage);
	m_wndElementBar.ShowWindow(SW_HIDE);
	////////////////////////////////////////////////////////// SupportBar
	if (!m_wndSupportBar.Create(this, rect.left, rect.top) ||
		!m_wndSupportBar.LoadBitmap(IDB_SUPPORT) ||
		!m_wndSupportBar.SetButtons(support,
		  sizeof(support)/sizeof(UINT),m_nSupportCol,FALSE)) // NOTE:FALSE= NO CAPTION
	{	
		AfxMessageBox("Cannot Create SupportBar");
		return -1;
    }
	////////////////////////////
	szButton.cx  = EL_BNSIZE_CX;
	szButton.cy  = EL_BNSIZE_CY; 
		
	szImage.cx   = EL_IMAGE_CX;
	szImage.cy   = EL_IMAGE_CY;
		
	m_wndSupportBar.SetSizes(szButton,szImage);
	m_wndSupportBar.ShowWindow(SW_HIDE);
	////////////////////////////////////////////////////////// end creation
	return 0;
	
} 
                                             
void CDrGrafFrame::CreateOrActivateFrame(CDocTemplate* pTemplate, 
				   CRuntimeClass* pViewClass)
{

	CMDIChildWnd* pMDIActive = MDIGetActive();
	ASSERT(pMDIActive != NULL);
	/////////////////////////////////////////////////
//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc );
	/////////////////////////////////////////////////  
	CDocument* pDoc = pMDIActive->GetActiveDocument();
	ASSERT(pDoc != NULL);
    /////////////////////////////////////////
//    BOOL bAnyViewOn = m_b12ViewActive_b12View;
//    if(bAnyViewOn)
//    {
	CView* pView;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(pViewClass))
		{
			pView->GetParentFrame()->ActivateFrame();
			return;
		}
	}
//    }
    ////////////////////////
	CMDIChildWnd* pNewFrame
		= (CMDIChildWnd*)(pTemplate->CreateNewFrame(pDoc, NULL));
	if (pNewFrame == NULL)
		return;     // not created
	ASSERT(pNewFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)));
	pTemplate->InitialUpdateFrame(pNewFrame, pDoc);  
/*	
	////////////////////////////////////////////////////////////  Menu Redraw
	MDISetMenu(&m_OpenMenu,NULL); 
	DrawMenuBar(); 
*/
	//////////////////////////////
	MDITile(MDITILE_SKIPDISABLED);
	//////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
// CDrGrafFrame message handlers     
/////////////////////////////////////////////////////////////////////////////
LONG CDrGrafFrame::OnSupportBar(UINT wParam, LONG lParam)
{

	POINT ptNew;
	if(lParam == 1)       //lParam = 1 SHOW AT NEW POSITION
	{ 
		CClientDC dc(this);
//		int nMapModeOld = dc.SetMapMode(MM_TEXT);
		////////////////////////////
		CSize sizeButton = m_wndElementBar.GetButtonSize();
		UINT  nCaptionHeight = m_wndElementBar.GetCaptionHeight();
		ptNew.x = m_nElementLeft + sizeButton.cx;
		ptNew.y = m_nElementTop  + wParam*(sizeButton.cy) + nCaptionHeight;//ELEMENT Buttonsize  
		m_wndSupportBar.SetWindowPos(NULL,ptNew.x,ptNew.y,0,0,
										SWP_NOZORDER|SWP_NOSIZE);
		m_wndSupportBar.ShowWindow(SW_SHOW); 
	}
	else if(!lParam)	// just toggle off
		m_wndSupportBar.ShowWindow((m_wndSupportBar.GetStyle()|WS_VISIBLE) == 0);  
	
	return 0;
	
}	
	
/////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////

void CDrGrafFrame::InitialShowWindow(UINT nCmdShow)
{
	WINDOWPLACEMENT wp;
	if (!ReadWindowPlacement(&wp))
	{
		ShowWindow(nCmdShow);
		return;
	}
	if (nCmdShow != SW_SHOWNORMAL)
		wp.showCmd = nCmdShow;
	SetWindowPlacement(&wp);
	ShowWindow(wp.showCmd);
}

void CDrGrafFrame::OnClose()
{  
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


void CDrGrafFrame::OnViewElementbox()
{
	// TODO: Add your command handler code here 
	if((m_wndSupportBar.GetStyle() & WS_VISIBLE) != 0)	// Turn Support OFF
			m_wndSupportBar.ShowWindow(SW_HIDE);  
			
	m_wndElementBar.ShowWindow((m_wndElementBar.GetStyle() & WS_VISIBLE) == 0);
}

void CDrGrafFrame::OnUpdateViewElementbox(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((m_wndElementBar.GetStyle() & WS_VISIBLE) != 0);
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnViewDrawbox()
{
	// TODO: Add your command handler code here
	m_wndDrawBox.ShowWindow((m_wndDrawBox.GetStyle() & WS_VISIBLE) == 0);
	
}

void CDrGrafFrame::OnUpdateViewDrawbox(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((m_wndDrawBox.GetStyle() & WS_VISIBLE) != 0);
	
}

void CDrGrafFrame::OnUpdateOptionDialogOn(CCmdUI* pCmdUI)
{
	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans();
	////////////////////////////////////////// 
	pCmdUI->SetCheck(pBool->IsDialogOn());
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafFrame::OnOptionDialogOn()
{

	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans();
	////////////////////////////////////////// 
	pBool->ToggleDialogOn();
	
}


void CDrGrafFrame::OnOptionRubberband()
{
	
	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans();
	////////////////////////////////////////// 
	pBool->ToggleDragOn();
	
}

void CDrGrafFrame::OnUpdateOptionRubberband(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans();
	////////////////////////////////////////// 
	pCmdUI->SetCheck(pBool->IsDragOn());
		
}
//////////////////////////////////////////////////////////////////////////////////
void CDrGrafFrame::UpdateStatusBar(CClientDC*  pDC)
{
	char buf[120];
	CString	str;    
   	CPen    Pen;
   	CPen*   PtrOldPen;
	
	CDrGrafDoc* pDoc 			= (CDrGrafDoc*)(theApp.m_pDoc );
	/////////////////////////////////////////////////////////////// 
    double dScaleFactor = pDoc->GetScaleFactor()->GetScaleFactor();
	/////////////////////////////// MapMode 
	char* MapModes[] ={"","MM_TEXT","MM_LOMETRIC","MM_HIMETRIC","MM_LOENGLISH",
					  "MM_HIENGLISH","MM_TWIPS","MM_ISOMETRIC","MM-ANISOMETRIC"};
	CString	Unit[] ={" in"," in"," ft"," ft"," mi"," mm"," cm"," m","km"};
	//////////////////////////////////////////
	int nUnitIndex = pDoc->GetUnit()->GetUnitIndex();				  
	int nMapMode       = pDC->GetMapMode();
	///////////////////////////////////////////
	sprintf(buf,"MapMode = %s      Scale = 1 in : %.2f %s",
				MapModes[nMapMode],dScaleFactor,Unit[nUnitIndex] );
	str = buf;
	m_wndStatusBar.SetPaneText(0,str,TRUE); 
	///////////////////////////////////////  
	UINT nID,nStyle;
	int cxWidth;
	m_wndStatusBar.GetPaneInfo(0,nID,nStyle,cxWidth);
	m_wndStatusBar.SetPaneInfo(0,nID,SBPS_STRETCH,cxWidth);
	m_wndStatusBar.SetPaneText(0,"Go Ahead! Make My Day!!!",TRUE);
	//////////////////////////////////////////////////////////////////// 
	int nViewNumber 	= GetActiveViewNumber();
	///////////////////////////////////////    
    LPOINT3 MouseWIC = pDoc->GetMouseMgr()->GetMouseLoc(nViewNumber)->GetMouseWIC();       
    //////////////////////////////////////////
	double dWorldBase   = (double)(pDoc->GetPrecision()->GetWorldBase());
	//////////////////////////////////////////
    double xWorld 		= ((double)MouseWIC.x/dWorldBase);
    double yWorld 		= ((double)MouseWIC.y/dWorldBase);
    double zWorld 		= ((double)MouseWIC.z/dWorldBase);
    ///////////////////////////////////////////
	double dMapFactor   = pDoc->GetMapFactor()->GetMapFactor();
	///////////////////////////////////////////
    xWorld 		*= dMapFactor;
    yWorld 		*= dMapFactor;
    zWorld 		*= dMapFactor;
    ////////////////////////// World Coord
    pDoc->GetScaleFactor()->DStoSC(&xWorld);
    pDoc->GetScaleFactor()->DStoSC(&yWorld);
    pDoc->GetScaleFactor()->DStoSC(&zWorld); 
    ////////////////////// for Iso
    double dCoord[3],Tran[2][3],dOrigin[2];
    dCoord[0] = xWorld;
    dCoord[1] = yWorld;
    dCoord[2] = zWorld;
	//////////////////////////////////////////////// Bottom Status Bar 
	
	CString strAxis[6] = {" X: "," Y: "," Z: "," Horz:","Vert:","    "};
	double dWorld[3];
	switch (nViewNumber)
	{
		case VIEW12:
		case VIEW23:
		case VIEW31:
			dWorld[0] = xWorld;
			dWorld[1] = yWorld;
			dWorld[2] = zWorld;
			break;
			 
		case VIEWISO:
			pDoc->GetObjectMgr()->GetXForm()->GetTranArray(Tran);
			pDoc->GetObjectMgr()->GetXForm()->TransformPoint3to2(dCoord, Tran, dOrigin);
			dWorld[1] = dOrigin[0];
			dWorld[2] = dOrigin[1];
			break;
			 
		default:
			break; 
}
	/////////////////////////////////////////////////
	if(nViewNumber == VIEWISO)
	{
		m_wndStatusBar.SetPaneText(1,strAxis[5],TRUE); 
		m_wndStatusBar.SetPaneText(3,strAxis[3],TRUE); 
		m_wndStatusBar.SetPaneText(5,strAxis[4],TRUE); 
	}	
	
	else
	{
		
		m_wndStatusBar.GetPaneInfo(1,nID,nStyle,cxWidth);
		m_wndStatusBar.SetPaneText(1,strAxis[0],TRUE); 

		 
		m_wndStatusBar.SetPaneInfo(3,nID,nStyle,cxWidth);
		m_wndStatusBar.SetPaneText(3,strAxis[1],TRUE);


		m_wndStatusBar.GetPaneInfo(5,nID,nStyle,cxWidth);
		m_wndStatusBar.SetPaneText(5,strAxis[2],TRUE);
	
	}
    //////////////////////////////////////////////////
	sprintf(buf,"%.2f %s",dWorld[1],Unit[nUnitIndex]);
	m_wndStatusBar.SetPaneText(4,str=buf,TRUE);
	sprintf(buf,"%.2f %s",dWorld[2],Unit[nUnitIndex]);
	m_wndStatusBar.SetPaneText(6,str=buf,TRUE);
	if(nViewNumber != VIEWISO)
	{ 
		sprintf(buf,"%.2f %s",dWorld[0],Unit[nUnitIndex]);
		m_wndStatusBar.SetPaneText(2,str=buf,TRUE);
	}	
	/////////////////////////////////////////////////////// Top Status Bar/Layer
   	Pen.CreatePen (PS_SOLID,1,RGB(255,0,0));
   	PtrOldPen = pDC->SelectObject(&Pen);
	/////////////////////////////////////////
	sprintf(buf,"%u",pDoc->GetLayer()->GetCurrentLayer());
	str = buf;
	m_wndStatusBarTop.SetPaneText(3,str,TRUE); 
	/////////////////////////////////////////////////////// Top Status Bar/Drawing Mode
	if(pDoc->GetObjectMgr()->GetEBoxMgr()->GetElementBoxStatus())
		str = pDoc->GetObjectMgr()->GetEBoxMgr()->
			GetElementName(pDoc->GetObjectMgr()->GetEBoxMgr()->GetElementType());
	else if (pDoc->GetObjectMgr()->GetDBoxMgr()->GetDrawBoxStatus())
		str = pDoc->GetObjectMgr()->GetDBoxMgr()->
			GetDrawName(pDoc->GetObjectMgr()->GetDBoxMgr()->GetActiveToolDrawType());
	m_wndStatusBarTop.SetPaneText(1,str,TRUE); 
	/////////////////////////////////////////////////////// Top Status Bar/Unit
	str = pDoc->GetUnit()->GetUnitName(pDoc->GetUnit()->GetUnitIndex());
	m_wndStatusBarTop.SetPaneText(5,str,TRUE);
	////////////////////////////////////////////// 
   	pDC->SelectObject(PtrOldPen);   
   	Pen.DeleteObject();
	
}


void CDrGrafFrame::OnTimer(UINT nIDEvent)
{   

	CClock clock; 
	CString strDate,strTime;
	
	clock.GetTimeDate(&strDate,&strTime);
 
	m_wndStatusBarTop.SetPaneText(8,strTime,TRUE);
	m_wndStatusBarTop.SetPaneText(10,strDate,TRUE);

}

void CDrGrafFrame::OnWinIniChange(LPCSTR lpszSection)
{
	CMDIFrameWnd::OnWinIniChange(lpszSection); 
	///////////////////
	CClock clock;
	clock.SetInternational();
	///////////////////
	// TODO: Add your message handler code here
	
}

void CDrGrafFrame::CloseView(CRuntimeClass* pViewClass)
{

	CMDIChildWnd* pMDIActive = MDIGetActive();
	ASSERT(pMDIActive != NULL);
	CDocument* pDoc = pMDIActive->GetActiveDocument();
	ASSERT(pDoc != NULL);

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

void CDrGrafFrame::OnView12view()
{ 

	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans();
	//////////////////////////////////////////  
	pBool->Toggle12ViewActive();
	if(pBool->Is12ViewActive() )
	{
		CreateOrActivateFrame(theApp.m_p12ViewTemplate, 
				RUNTIME_CLASS(C12View));
//	    m_Mouse.SetViewNumber(VIEW12);    // View12 = 1 etc.
    }
	else
	    CloseView(RUNTIME_CLASS(C12View));  
	    
			         
	// TODO: Add your command handler code here
	
}

void CDrGrafFrame::OnUpdateView12view(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans(); 
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->Is12ViewActive() );
	
}

void CDrGrafFrame::OnView23view()
{
	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans();
	////////////////////////////////////////// 
	pBool->Toggle23ViewActive();
	if(pBool->Is23ViewActive() )
	{
		CreateOrActivateFrame(theApp.m_p23ViewTemplate, 
			RUNTIME_CLASS(C23View));
//	    m_Mouse.SetViewNumber(VIEW23);    // View23 =2 etc.
    }
	else
	    CloseView(RUNTIME_CLASS(C23View));
	// TODO: Add your command handler code here
	
}

void CDrGrafFrame::OnUpdateView23view(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans(); 
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->Is23ViewActive() );
	
}

void CDrGrafFrame::OnView31view()
{

	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans();
	////////////////////////////////////////// 
	pBool->Toggle31ViewActive();
	if(pBool->Is31ViewActive() )
	{
		CreateOrActivateFrame(theApp.m_p31ViewTemplate, 
			RUNTIME_CLASS(C31View));
//	    m_Mouse.SetViewNumber(VIEW31);    // View31 = 3 etc.
    }
	else
	    CloseView(RUNTIME_CLASS(C31View));

	// TODO: Add your command handler code here
	
}

void CDrGrafFrame::OnUpdateView31view(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans(); 
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->Is31ViewActive() );

	
}

void CDrGrafFrame::OnViewIsoview()
{

	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans();
	////////////////////////////////////////// 
	pBool->ToggleIsoViewActive();
	if(pBool->IsIsoViewActive() )
	{
		CreateOrActivateFrame(theApp.m_pIsoViewTemplate, 
			RUNTIME_CLASS(CIsoView));
	}
	else
	    CloseView(RUNTIME_CLASS(CIsoView));
	
}

void CDrGrafFrame::OnUpdateViewIsoview(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans(); 
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->IsIsoViewActive() );
	
}


void CDrGrafFrame::OnViewDataView()
{

	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans();
	////////////////////////////////////////// 
	pBool->ToggleDataViewActive();
	if(pBool->IsDataViewActive() )
	{
		CreateOrActivateFrame(theApp.m_pDataViewTemplate, 
			RUNTIME_CLASS(CDataView));
	}
	else
	    CloseView(RUNTIME_CLASS(CDataView));
	
}

void CDrGrafFrame::OnUpdateViewDataView(CCmdUI* pCmdUI)
{

	CDrGrafDoc* pDoc	= (CDrGrafDoc*)(theApp.m_pDoc );
	CBooleans* pBool	= pDoc->GetBooleans(); 
	//////////////////////////////////
	pCmdUI->SetCheck(pBool->IsDataViewActive() );
	
}

void CDrGrafFrame::OnViewSBarBot()
{
	CWnd* pBar;
	if(pBar = GetDescendantWindow(IDS_BOT_STATUSBAR) )
	{
		pBar->ShowWindow( (pBar->GetStyle() & WS_VISIBLE) == 0);    // toggle
		RecalcLayout();
	}
		
}

void CDrGrafFrame::OnUpdateViewSBarBot(CCmdUI* pCmdUI)
{
	CWnd* pBar;	
	if(pBar = GetDescendantWindow(IDS_BOT_STATUSBAR) )
	{
		pCmdUI->SetCheck( (pBar->GetStyle() & WS_VISIBLE) != 0);
	}	
}

void CDrGrafFrame::OnViewSBarTop()
{
	CWnd* pBar;
	if(pBar = GetDescendantWindow(IDS_TOP_STATUSBAR) )
	{
		pBar->ShowWindow( (pBar->GetStyle() & WS_VISIBLE) == 0);    // toggle
		RecalcLayout();
	}
}

void CDrGrafFrame::OnUpdateViewSBarTop(CCmdUI* pCmdUI)
{
	CWnd* pBar;	
	if(pBar = GetDescendantWindow(IDS_TOP_STATUSBAR) )
	{
		pCmdUI->SetCheck( (pBar->GetStyle() & WS_VISIBLE) != 0);
	}	
}
////////////////////////////////////// end of module /////////////////// 
