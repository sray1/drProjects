// drgraf.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

///////////////////// Old ToolBar Utility from MFC (VC++ 1.5)
#include "Oldglob.h"
#include "Oldtool.h"
#include "Oldstat.h"
/////////////////////
#include "Def_View.h"       // OpMode
/////////////////////////////////////
#include "resource.h"       // main symbols
#include "aboutbox.h"  
/////////////////////
#include "drgrafrm.h"
#include "drgracfm.h"
#include "drgradoc.h"
//#include "IpFrame.h"
///////////////////// view
#include "12View.h"
#include "23View.h"
#include "31View.h"
#include "3DView.h"
#include "DataView.h"
#include "MsDataVu.h"
#include "DeckView.h"
#include "SpDrawVu.h"		// Spectral:Auxilliary Draw View
#include "DrSplit.h"		// Splitter Child Frame (4 way Splitter for DrSpView etc)
#include "ColorPal.h"
#include "DrTreeVu.h"		// Form DataBase:Tree View
#include "Splitter.h"		// Splitter Child Frame (3 way Splitter for FormData etc)
/////////////////////////////////////////////// View     dlls
#include "Viewdll.h"
/////////////////////////////////////////////// ObjMgr   dlls
#include "OMgrdll.h"
/////////////////////////////////////////////// Draw3D   dlls
#include "Dr3Ddll.h"
/////////////////////////////////////////////// CreOpMgr dlls
#include "CMgrdll.h"
/////////////////////////////////////////////// CreOMMgr dlls
#include "CreMdll.h"
/////////////////////////////////////////////// EditMgr dlls
#include "EMgrdll.h"
/////////////////////////////////////////////// MeshEditMgr dlls
#include "Mditdll.h"
/////////////////////////////////////////////// DelMgr dlls
#include "DMgrdll.h"
/////////////////////////////////////////////// PostMgr dlls
#include "PMgrdll.h"
/////////////////////////////////////////////// DeckMgr dlls
#include "Deckdll.h"
/////////////////////////////////////////////// MouseMgr dlls
#include "MMgrdll.h"
#include "MNoddll.h"
#include "MCurdll.h"
#include "MPatdll.h"
#include "MSoldll.h"
#include "MO3Ddll.h"
#include "MSupdll.h"
#include "MStLdll.h"
/////////////////////////////////////////////// Special  dlls
#include "specdll.h"
#include "SDlgdll.h"
/////////////////////////////////////////////// MeshObj  dlls
#include "Mesh_dll.h"
#include "MMs0dll.h"
#include "MMs1dll.h"
#include "MMs2dll.h"
//#include "MMs3dll.h"
//#include "MM3Ddll.h"
/////////////////////////////////////////////// ElemObj  dlls
#include "Elemdll.h"
#include "OGen_dll.h"
#include "Suppdll.h"
#include "StaLdll.h"
#include "EDlgdll.h"
/////////////////////////////////////////////// Auxilliary Objects Dlls
#include "DBaseDll.h"
/////////////////////////////////////////////// Auxilliary Objects Dlls
#include "AuxiDll.h"
/////////////////////////////////////////////// DrawObj  dlls
#include "Drawdll.h"
#include "DDlgdll.h"
/////////////////////////////////////////////// toolbox  dlls
#include "EBoxdll.h"
#include "IGendll.h"
#include "DBoxdll.h"          
/////////////////////
#include "Glb_DBox.h"
#include "Glb_Elem.h"
#include "Glb_Cur.h"
#include "Glb_Pat.h"
#include "Glb_Sol.h"
#include "Glb_Supp.h"
#include "Glb_StaL.h"
//////////////////////
#include "mmsystem.h"
#include "drgraf.h"
#include "Splash.h"
//////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CDrGrafApp

BEGIN_MESSAGE_MAP(CDrGrafApp, CWinApp)
	//{{AFX_MSG_MAP(CDrGrafApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_HELP, OnUpdateContextHelp)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateFileClose)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	// Global help commands
	ON_COMMAND(ID_HELP_INDEX, CWinApp::OnHelpIndex)
	ON_COMMAND(ID_HELP_USING, CWinApp::OnHelpUsing)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CWinApp::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CWinApp::OnHelpIndex)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrGrafApp construction

CDrGrafApp::CDrGrafApp()
{
	m_p12ViewTemplate = NULL;
	m_p23ViewTemplate = NULL;
	m_p31ViewTemplate = NULL;  
	m_p3DViewTemplate = NULL;  
	m_pDataViewTemplate = NULL;
	/////////////////////////////
	 
}
CDrGrafApp::~CDrGrafApp()
{ 
/////////////////////////////////////// these are done in ~WinApp, so no need
/*
	if(m_p12ViewTemplate != NULL)
		delete m_p12ViewTemplate;
	if(m_p23ViewTemplate != NULL)
		delete m_p23ViewTemplate;
	if(m_p31ViewTemplate != NULL)
		delete m_p31ViewTemplate;  
	if(m_p3DViewTemplate != NULL)
		delete m_p3DViewTemplate;  
	if(m_pDataViewTemplate != NULL)
		delete m_pDataViewTemplate; 
*/	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDrGrafApp object

CDrGrafApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {0FDA4260-5F9D-11CF-9A11-88537EDAE885}
static const CLSID clsid =
{ 0xfda4260, 0x5f9d, 0x11cf, { 0x9a, 0x11, 0x88, 0x53, 0x7e, 0xda, 0xe8, 0x85 } };

/////////////////////////////////////////////////////////////////////////////
// CDrGrafApp initialization

BOOL CDrGrafApp::InitInstance()
{
	///////////////////////////////////////////////////////////////////// DLL Inits
#ifdef _AFXDLL
	InitDLLs();
#endif
	/////////////////////////////////////////////////////// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
	//////////////////////////////////////////////////////////////////BANNER////////
	BOOL 	bBanner = FALSE;
//	BOOL 	bBanner = TRUE;
	/////////////////////
	if(bBanner)
	{
#define BUF_LEN	256
		//Plays the specified multimedia file
		//via the multimedia interface.
		char ReplyStr[BUF_LEN];
		char ErrString[BUF_LEN];
		CString ComString = "play c:\\SB16\\Samples\\BALLADE.mid";		
//		CString message = "c:\\SB16\\Samples\\S_16_44.wav";		
		int mciError = mciSendString(ComString,ReplyStr, BUF_LEN, NULL);
		int dummy = mciGetErrorString(mciError,ErrString,BUF_LEN);
//		int dummy = sndPlaySound(message,SND_ASYNC|SND_LOOP);
		if(dummy == FALSE)
			AfxMessageBox("Problem playing sound");
		///////////////////
		if(!ShowBanner())
			return FALSE;
	}
	int dummy = sndPlaySound(NULL,SND_ASYNC);
	//////////////////////////////////////////////////////// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	//////////////////////////////////////////////////////////////////////////////
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	RegisterDocTemplates();		// Register Document Templates
    /////////////////////////////////////////////////////////// register new class
	if(!RegisterNewClasses())
		return FALSE;
    /////////////////////////////////////////////////////////// create main MDI Frame window
	CDrGrafFrame* pMainFrame = new CDrGrafFrame;
//	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
	if (!CreateMainFrame(pMainFrame) )
		return FALSE;
	m_pMainWnd = pMainFrame;
	/////////////////////////////////////////////////////////// Set Active ViewNumber
	((CDrGrafFrame*)m_pMainWnd)->SetActiveViewNumber(VIEW12);// correspond to Active Template
	////////////////////////////////////////
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();
	///////////////////////////////////////////////////////////////// .Ini File
	// enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
/*?
	// simple command line parsing
	if (m_lpCmdLine[0] == '\0')
	{
		// create a new (empty) document
		OnFileNew();
	}
	else
	{
		// open an existing document
		OpenDocumentFile(m_lpCmdLine);
	}
?*/
	//////////////////////////////////////////////////////
	UINT nCmdShow = m_nCmdShow;
	m_nCmdShow = SW_HIDE;
	((CDrGrafFrame*)m_pMainWnd)->InitialShowWindow(m_nCmdShow); 
	//////////////////////////////////
	m_pMainWnd->ShowWindow(nCmdShow);
	m_pMainWnd->UpdateWindow();
/*
	if (!m_pMainWnd->IsIconic() && m_lpCmdLine[0] == 0 &&
		m_splash.Create(m_pMainWnd))
	{
		m_splash.ShowWindow(SW_SHOW);
		m_splash.UpdateWindow();
	}
	m_dwSplashTime = ::GetCurrentTime();
*/
	//////////////////////////////////////////////////////
	// The main window has been initialized, so show and update it.
	m_nCmdShow = nCmdShow;                                         // restore m_nCmdShow
//	m_pMainWnd->UpdateWindow();

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
//?	m_server.UpdateRegistry(OAT_INPLACE_SERVER);
//?	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
//	if (!ProcessShellCommand(cmdInfo))
//		return FALSE;

	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED); 
	pMainFrame->UpdateWindow();
	/////////////////////////////////////////////////////////////// SplashWindow
/*	
	// CG: The following block was added by the Splash Screen component.
	{
		CCommandLineInfo cmdInfo;
		cmdInfo.m_bShowSplash = TRUE;
		ParseCommandLine(cmdInfo);

		CSplashCom::EnableSplashScreen(cmdInfo.m_bShowSplash);
	}
*/
	/////////////////////////////////////////////////////////// Turn Music off
	if(bBanner)
	{
#define BUF_LEN	256
		//Plays the specified multimedia file
		//via the multimedia interface.
		char ReplyStr[BUF_LEN];
		char ErrString[BUF_LEN];
		CString ComString = "close c:\\SB16\\Samples\\BALLADE.mid";		
		int mciError = mciSendString(ComString,ReplyStr, BUF_LEN, NULL);
	}
	////////////	
	return TRUE;
}
////////////////////////////////////////////////////////////////////// Helper
BOOL CDrGrafApp::RegisterNewClasses()
{

	// Control bar windows/modify for cursor  "AfxControlBar"
	WNDCLASS wc;
    // check if "SuperControlBar" doesn't already exist
    HCURSOR hCursor;
	if (!::GetClassInfo(m_hInstance, "SuperControlBar" , &wc) ) 
	{
		////////////////////////////////////////////////////////////////////////////////////////////
		// NOTE:	"AfxControlBar" is used for the standard control bar implementationin VC++1.5
		//			but NOT SUPPORTED anymore in VC++4.0
		//		AfxControlBar used to be:
					//�	class style : 0 [ reduces flash during resizing, no double clicks ]
					//�	no icon
					//�	arrow cursor
					//�	gray background color (COLOR_BTNFACE)
		//////////////////////////////////////////////////////////////////////////////////////
		CString strClassName = AfxRegisterWndClass(0,LoadStandardCursor(IDC_ARROW),
								(HBRUSH)COLOR_BTNFACE,(HICON)NULL);
//		if (!::GetClassInfo(m_hInstance, "AfxControlBar" , &wc) )
		if (!::GetClassInfo(m_hInstance, strClassName , &wc) )
		{
			AfxMessageBox("Couldnot get classInfo");
			return FALSE;
		} 
	
		wc.lpszClassName 	= "SuperControlBar";
	////////////////////////////////////////////////////
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
/*	
	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionEBox_DLL.hModule); // uses client's instance handle 
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle
*/	 
//////////////////////////////////////////////	
// IDC_BUTTON	
//		if ( (hCursor  = LoadStandardCursor(IDC_CROSS)) == NULL)
		if ( (hCursor  = LoadCursor(IDC_BUTTON)) == NULL)
		{
			AfxMessageBox("Couldn't load cursor");
			return FALSE;
		}	
		wc.hCursor 			= hCursor;
		wc.hInstance		= m_hInstance;
	
		if (!::RegisterClass(&wc))
			return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////
void CDrGrafApp::SetDocument()
{
	CMDIChildWnd* pMDIActive = ((CDrGrafFrame*)m_pMainWnd)->MDIGetActive();
	ASSERT(pMDIActive != NULL);
	/////////////////////////////////////////////////  
	CDocument* pDoc = pMDIActive->GetActiveDocument();
	ASSERT(pDoc != NULL);
	/////////////////////
	m_pDocument =  (CDrGrafDoc*)pDoc;
	/////////////////////////////////
	return;
}

void CDrGrafApp::InitDLLs()
{

	InitDr3DDLL();	// necessary for DLL resource access and IsKindOf
	InitSpecDLL();	// necessary for DLL resource access and IsKindOf
	InitDrawDLL();	// necessary for DLL resource access and IsKindOf
	InitOGenDLL();	// necessary for DLL resource access and IsKindOf
	InitMeshDLL();	// necessary for DLL resource access and IsKindOf
	InitElemDLL();	// necessary for DLL resource access and IsKindOf
	InitSuppDLL();	// necessary for DLL resource access and IsKindOf
	InitStaLDLL();	// necessary for DLL resource access and IsKindOf
	InitOMgrDLL();	// necessary for DLL resource access and IsKindOf
	InitSDlgDLL();	// necessary for DLL resource access and IsKindOf
	InitDDlgDLL();	// necessary for DLL resource access and IsKindOf 
	InitEDlgDLL();	// necessary for DLL resource access and IsKindOf
	InitIGenDLL();	// necessary for DLL resource access and IsKindOf
	InitEBoxDLL();	// necessary for DLL resource access and IsKindOf
	InitDBoxDLL();	// necessary for DLL resource access and IsKindOf
	InitMNodDLL();	// necessary for DLL resource access and IsKindOf
	InitMCurDLL();	// necessary for DLL resource access and IsKindOf
	InitMPatDLL();	// necessary for DLL resource access and IsKindOf
	InitMSolDLL();	// necessary for DLL resource access and IsKindOf
	InitMO3DDLL();	// necessary for DLL resource access and IsKindOf
	InitMSupDLL();	// necessary for DLL resource access and IsKindOf
	InitMStLDLL();	// necessary for DLL resource access and IsKindOf
	InitMMgrDLL();	// necessary for DLL resource access and IsKindOf
	InitCMgrDLL();	// necessary for DLL resource access and IsKindOf
	InitEMgrDLL();	// necessary for DLL resource access and IsKindOf
	InitDMgrDLL();	// necessary for DLL resource access and IsKindOf
	InitPMgrDLL();	// necessary for DLL resource access and IsKindOf
	InitMMs0DLL();	// necessary for DLL resource access and IsKindOf
	InitMMs1DLL();	// necessary for DLL resource access and IsKindOf
	InitMMs2DLL();	// necessary for DLL resource access and IsKindOf
//	InitMMs3DLL();	// necessary for DLL resource access and IsKindOf
//	InitMM3DDLL();	// necessary for DLL resource access and IsKindOf
	InitCreMDLL();	// necessary for DLL resource access and IsKindOf
	InitMditDLL();	// necessary for DLL resource access and IsKindOf
	InitDeckDLL();	// necessary for DLL resource access and IsKindOf
	InitViewDLL();	// necessary for DLL resource access and IsKindOf
	///
	InitAuxiDLL();	// necessary for DLL resource access and IsKindOf
	InitDBaseDLL();	// necessary for DLL resource access and IsKindOf

}

void CDrGrafApp::SetDocument(CDrGrafDoc* pDoc)
{

	m_pDocument = pDoc;
	
}
//////////////////////////////////////////////////////////////////////	
BOOL CDrGrafApp::CreateBannerWnd(CBanner* pBanWnd)
{
//	CRect rect(0,0,0,0);
// 	CString BanClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_BYTEALIGNWINDOW,
//   						0,(HBRUSH)(COLOR_WINDOW+1),NULL);        //NULL CURSOR 
   						
		
	if(!pBanWnd->Create())  							
   		return FALSE;
   	else
   		return TRUE;	 
   				
}

BOOL CDrGrafApp::ShowBanner()
{
	COLORREF BkColor = ::GetSysColor(COLOR_BACKGROUND);
	///////////////////////////////////////////////////
	int 	aiDspElements[1];
	DWORD 	aRGB[1];
//		CColorPal ColorPal;
//		if(ColorPal.Make256ColorPal(&ColorPal)<0)
//			return FALSE;
	///////////////////////////////////////////////////// change Back Color to Black
	COLORREF crBlack = RGB(255,0,255);
	aiDspElements[0] 	= COLOR_BACKGROUND;
	aRGB[0]				= crBlack;
	::SetSysColors(1,aiDspElements,aRGB);
	///////////////////////////////////////////////////////////////// Banner Window
	if(!CreateBannerWnd(&m_BannerWnd))
		return FALSE;
	// get desktop size

	int cxWidth 	= ::GetSystemMetrics(SM_CXSCREEN);
	int cyHeight 	= ::GetSystemMetrics(SM_CYSCREEN);
	CRect BanRect(0,0,cxWidth,cyHeight);
   	m_BannerWnd.SetWindowPos(NULL,BanRect.left,BanRect.top,BanRect.Width(),BanRect.Height(),
   						SWP_SHOWWINDOW);
	///////////////////////////////////////////////// Jasmin    					 
	m_BannerWnd.Init(1);
	m_BannerWnd.Invalidate(FALSE);    					
	m_BannerWnd.UpdateWindow();
	DWORD dwCafeStart = ::GetTickCount();
	while ((::GetTickCount() - dwCafeStart)<8000L)				// should be 8000L/2000L
		;
	m_BannerWnd.SetDestroy(TRUE);
	m_BannerWnd.Invalidate(FALSE);    					
	m_BannerWnd.UpdateWindow();
	///////////////////////////////////////////////// SeaShore    					 
	m_BannerWnd.SetDestroy(FALSE);
	dwCafeStart = ::GetTickCount();
	///////////////////////////////
	m_BannerWnd.Init(2);
	m_BannerWnd.Invalidate(FALSE);    					
	m_BannerWnd.UpdateWindow();    					
	while ((::GetTickCount() - dwCafeStart)<13000L)				// should be 13000L/2000L
		;
	m_BannerWnd.SetDestroy(TRUE);
	m_BannerWnd.Invalidate(FALSE);    					
	m_BannerWnd.UpdateWindow();
	///////////////////////////
//		ColorPal.DeleteObject(); 
	///////////////////////////////////////////////////////////////// DestroyBanner
	m_BannerWnd.DestroyWindow();
	/////////////////////////// put old color back   					
	aRGB[0]				= BkColor; 		// Restore Old Color
	::SetSysColors(1,aiDspElements,aRGB);
   	/////////////////////////////////////
	return TRUE;
}

BOOL CDrGrafApp::CreateMainFrame(CDrGrafFrame* pMainFrame)
{

//	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
//		return FALSE;
/*
	HCURSOR	hcursor;
    if ((hcursor = theApp.LoadStandardCursor(IDC_CROSS)) == NULL)
    	AfxMessageBox("LoadCursor failed."); 
*/    	
    HICON	hicon	= theApp.LoadIcon(IDR_MAINFRAME);

//  Create CmdiFrame Window   
   	CString ClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,
   						0,(HBRUSH)(COLOR_WINDOW+1),hicon);        //NULL CURSOR
	if(!pMainFrame->Create 	(
							ClassName,
   							"Soft Mesh CAFE",
   							WS_OVERLAPPEDWINDOW,
   							pMainFrame->rectDefault,
   							NULL,
   							MAKEINTRESOURCE(IDR_MAINFRAME))
   							)
   		return FALSE;
   	else
   		return TRUE;	 
   				
}
//////////////////////////////////////////////////////////////////////// 
void	CDrGrafApp::RegisterDocTemplates()
{
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	// We register FIVE doc templates with the CWinApp object, by calling
	// AddDocTemplate.  However, if we were to do this and nothing else, then
	// the framework would mistakenly believe that the application supports
	// FOUR document types.  The framework would display a File New dialog
	// that lists FIVE document types, all of which would be "DrGrafix".
	// We avoid this problem by removing the third string from 
	// the document template for the DrGraf frame/view. 
	//
	// Finding no GetDocString(CDocTemplate::fileNewName) for the
	// second to fourth document template, CWinApp concludes that there is only
	// one document type supported by the application (the "System Model"
	// document type specified in the first document template; and
	// therefore does not represent the user with a File New dialog.

	m_p3DViewTemplate = new CMultiDocTemplate(IDR_3DTYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(C3DView));
//?	m_p3DViewTemplate->SetContainerInfo(IDR_DRGRAFTYPE_CNTR_IP);
	AddDocTemplate(m_p3DViewTemplate);  

/*	
	m_p12ViewTemplate = new CMultiDocTemplate(IDR_DRGRAFTYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(C12View));
	m_p12ViewTemplate->SetContainerInfo(IDR_DRGRAFTYPE_CNTR_IP);
	AddDocTemplate(m_p12ViewTemplate);
*/	
	m_p12ViewTemplate = new CMultiDocTemplate(IDR_12TYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(C12View));
//?	m_p12ViewTemplate->SetContainerInfo(IDR_DRGRAFTYPE_CNTR_IP);
	AddDocTemplate(m_p12ViewTemplate);


	m_p23ViewTemplate = new CMultiDocTemplate(IDR_23TYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(C23View));
//?	m_p23ViewTemplate->SetContainerInfo(IDR_DRGRAFTYPE_CNTR_IP);
	AddDocTemplate(m_p23ViewTemplate);

	m_p31ViewTemplate = new CMultiDocTemplate(IDR_31TYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(C31View));
//?	m_p31ViewTemplate->SetContainerInfo(IDR_DRGRAFTYPE_CNTR_IP);
	AddDocTemplate(m_p31ViewTemplate);

	m_pDataViewTemplate = new CMultiDocTemplate(IDR_DATATYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(CDataView));
//?	m_pDataViewTemplate->SetContainerInfo(IDR_DRGRAFTYPE_CNTR_IP);
	AddDocTemplate(m_pDataViewTemplate);  

	m_pMeshDataViewTemplate = new CMultiDocTemplate(IDR_MESHDATATYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(CMsDataVu));
//?	m_pDataViewTemplate->SetContainerInfo(IDR_DRGRAFTYPE_CNTR_IP);
	AddDocTemplate(m_pMeshDataViewTemplate);  

	m_pDeckViewTemplate = new CMultiDocTemplate(IDR_DECKTYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(CDeckView));
//?	m_pDataViewTemplate->SetContainerInfo(IDR_DRGRAFTYPE_CNTR_IP);
	AddDocTemplate(m_pDeckViewTemplate);  

	// 3-way splitter frame with TreeVu/DataVu/ListVu  (3 panes)
	m_pFormViewTemplate = new CMultiDocTemplate(IDR_FORMDATATYPE,
		RUNTIME_CLASS(CDrGrafDoc),
		RUNTIME_CLASS(C3WaySplitterFrame), // 3-way splitter
		RUNTIME_CLASS(CDrTreeVu));

	AddDocTemplate(m_pFormViewTemplate);  
	// splitter frame with both Graphical output and Data Input/Output view (4 panes)
	m_pSpecViewTemplate = new CMultiDocTemplate(IDR_AUXINPUT,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrSplitFrm),
			RUNTIME_CLASS(CSpDrawVu));		// Spectral View as (0,0) default

	AddDocTemplate(m_pSpecViewTemplate);  
	////////////////////////////////////////////////////
	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
//?	m_server.ConnectTemplate(clsid, m_p12ViewTemplate, FALSE);				
//	m_server.ConnectTemplate(clsid, m_p23ViewTemplate, FALSE);				

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
//?	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

}
/////////////////////////////////////////////////////////////////////////////
// CAboutBox dialog used for App About

// App command to run the dialog
void CDrGrafApp::OnAppAbout()
{
	CAboutBox aboutBox;
	aboutBox.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// VB-Event registration
// (calls to AfxRegisterVBEvent will be placed here by ClassWizard)

//{{AFX_VBX_REGISTER_MAP()
//}}AFX_VBX_REGISTER_MAP

/////////////////////////////////////////////////////////////////////////////
// CDrGrafApp commands
///////////////////////////////////////////////////////////////////	 
 BOOL CDrGrafApp::OnIdle(LONG lCount)
{
	// call base class idle first
	BOOL bResult = CWinApp::OnIdle(lCount);

	// then do our work
/*
	if (m_DrCafeBM.m_hObject != NULL)
	{
		if (::GetCurrentTime() - m_dwDrCafeTime > 1000)
		{
			// timeout expired, Dissolve BitMap

			// disolve screen by ploting zillions of black pixels
			m_DrCafeDC.SelectObject(m_pOldBM);
			m_DrCafeBM.DeleteObject();
			m_pMainWnd->UpdateWindow();

			// NOTE: don't set bResult to FALSE,
			//  CWinApp::OnIdle may have returned TRUE
		}
		else
		{
			// check again later...
			bResult = TRUE;
		}
	}
	else 
	
	if (m_splash.m_hWnd != NULL)
	{
		if (::GetCurrentTime() - m_dwSplashTime > 1000)
		{
			// timeout expired, destroy the splash window
			m_splash.DestroyWindow();
			m_pMainWnd->UpdateWindow();

			// NOTE: don't set bResult to FALSE,
			//  CWinApp::OnIdle may have returned TRUE
		}
		else
		{
			// check again later...
			bResult = TRUE;
		}
	} 
*/	
	return bResult;
}

void CDrGrafApp::OnAppExit()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafApp::OnUpdateAppExit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafApp::OnContextHelp()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafApp::OnUpdateContextHelp(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafApp::OnFileClose()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafApp::OnUpdateFileClose(CCmdUI* pCmdUI)
{
	// TODO: Add your command handler code here

}

void CDrGrafApp::OnFileNew()
{

	// By default, the framework does not create an actual file for
	// a new document until the user does a File Save As.  But Model Drawing
	// requires a file as soon as the user does a File New, because
	// DrGraf updates the file on a per drawing basis.  Upon File
	// New, we prompt the user with a File Open dialog, in which the
	// user specifies a new file (or if she changes her mind, she
	// can specify an existing file).  We call the same
	// CWinApp::DoPromptFileName that CWinApp::OnFileOpen calls.
	// But we replace the OFN_FILEMUSTEXIST flag with
	// OFN_CREATEPROMPT.  
	/////////////////////
    CDrGrafFrame* pWnd = (CDrGrafFrame*)m_pMainWnd;
	/////////////////// force OpMode = Input
	pWnd->SetOpMode(OP_INPUT);
    ///////////////////////////////////////////////
    BOOL bNewFile = TRUE;
    CWinApp::OnFileNew(); 
    /////////////////////
/*
	CMDIChildWnd* pMDIActive = ((CDrGrafFrame*)m_pMainWnd)->MDIGetActive();
	ASSERT(pMDIActive != NULL);
	CDocument* pDoc = pMDIActive->GetActiveDocument();
	ASSERT(pDoc != NULL);
*/
//	pWnd->CreateOrActivateFrame(((CDrGrafApp*)AfxGetApp())->Get12ViewTemplate(), 
//				RUNTIME_CLASS(C12View));
	////////////////////////////////////////////////////////////////// Window Title
	CString strTitle;
	m_pMainWnd->GetWindowText(strTitle);
	strTitle += ": Untitled";
	m_pMainWnd->SetWindowText(strTitle);
    ////////////////////////////////////////////////////////////////// Init MainFrame
//    pWnd->Init();
    //////////////
    return;
    /////////////////////
/* 
	CString strNewFileName;

	if (!(DoPromptFileName(strNewFileName, IDS_NEW_DRGRAF,
			OFN_HIDEREADONLY | OFN_CREATEPROMPT, TRUE, NULL)))
		return;

/////////////////////////// 
//	strNewFileName = "Control.drg";
	// If file doesn't already exist, then create it.
	CFile file;
	CFileStatus status;
	if (!file.GetStatus(strNewFileName, status))
	{
		file.Open(strNewFileName, CFile::modeCreate);
		file.Close();
	}
	// Open the file now that it has been created.
		OpenDocumentFile(strNewFileName); 
	
*/	
}

void CDrGrafApp::OnUpdateFileNew(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafApp::OnFileOpen()
{

	CWinApp::OnFileOpen(); 
	//////////////////////////////
	CString strTitle;
	m_pMainWnd->GetWindowText(strTitle);
	CString strPath  = GetDocument()->GetPathName();
	strTitle += ": " + strPath;
	m_pMainWnd->SetWindowText(strTitle);
	return;
	///////////
	OnFileNew();// TODO: Add your command handler code here
	
}

void CDrGrafApp::OnUpdateFileOpen(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafApp::OnFilePrint()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafApp::OnUpdateFilePrint(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafApp::OnFilePrintPreview()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafApp::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafApp::OnFileSave()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafApp::OnUpdateFileSave(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}

void CDrGrafApp::OnFileSaveAs()
{
	// TODO: Add your command handler code here
	
}

void CDrGrafApp::OnUpdateFileSaveAs(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	
}
/////////////////////////////////////////////////////////////////////////////////// 

CDocument* CDrGrafApp::OpenDocumentFile(LPCSTR lpszFileName)
{
	// CWinApp::OpenDocmentFile creates the first MDI child window
	// for the 12 view.  This override creates all other MDI child
	// window for the Model view.  Then it tiles the four MDI children
	// windows.

	CFrameWnd* pNewFrame;
	/////////////////////////////////////////////////////////////////////// File Open/Create 
	// If file doesn't already exist, then create it.
	CFile file;
	CFileStatus status;
	CString str = lpszFileName;
	if (!file.GetStatus(str, status))
	{
		file.Open(str, CFile::modeCreate);
		file.Close();
	}
    //////////////////////////////////////////////////////////////////////// call base
	CDrGrafDoc* pDoc = (CDrGrafDoc*)CWinApp::OpenDocumentFile(lpszFileName);
    ////////////////////////////////////////////////////////////////////////
	if (pDoc == NULL)
	{
		AfxMessageBox("OpenDocumentFile failed.");
		return NULL;
	}
    //////////////////////////////////////////////////////////
    // Save Current Document File Name
//   	m_sDocFileName = (CString)lpszFileName;
/*
	pNewFrame = m_p12ViewTemplate->CreateNewFrame(pDoc, NULL);
	if (pNewFrame == NULL)
		return pDoc;
	m_p12ViewTemplate->InitialUpdateFrame(pNewFrame, pDoc);


	pNewFrame = m_p23ViewTemplate->CreateNewFrame(pDoc, NULL);
	if (pNewFrame == NULL)
		return pDoc;
	m_p23ViewTemplate->InitialUpdateFrame(pNewFrame, pDoc);

	pNewFrame = m_p31ViewTemplate->CreateNewFrame(pDoc, NULL);
	if (pNewFrame == NULL)
		return pDoc;
	m_p31ViewTemplate->InitialUpdateFrame(pNewFrame, pDoc);

	pNewFrame = m_pIsoViewTemplate->CreateNewFrame(pDoc, NULL);
	if (pNewFrame == NULL)
		return pDoc;
	m_pIsoViewTemplate->InitialUpdateFrame(pNewFrame, pDoc);

	// Tile the four MDI children windows within the MDI frame window.

	ASSERT(pNewFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)));
	CMDIFrameWnd* pMDIFrameWnd = ((CMDIChildWnd*)pNewFrame)->GetMDIFrame();
	ASSERT(pMDIFrameWnd != NULL);
	pMDIFrameWnd->MDITile(MDITILE_HORIZONTAL);
*/

	/////////////////////////////////////////////////// Initialize MainFrame
	((CDrGrafFrame*)(m_pMainWnd))->Init();
	///////////////////////////////////////////
	return pDoc;      
	
}
/////////////////////////////////////////////////////////////////////////////
// INI file implementation

static char BASED_CODE szIniFileSection[] = "Most Recent Piping Model";
static char BASED_CODE szIniFileEntry[] = "File";


void CDrGrafApp::UpdateIniFileWithDocPath(const char* pszPathName)
{
	WriteProfileString(szIniFileSection, szIniFileEntry, pszPathName);
}


CString CDrGrafApp::GetDocPathFromIniFile()
{
	return GetProfileString(szIniFileSection, szIniFileEntry, NULL);
}
//////////////////////////////////////// End of Module ///////////////////////////	 

BOOL CDrGrafApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following line was added by the Splash Screen component.
	CSplashCom::PreTranslateAppMessage(pMsg);

	return CWinApp::PreTranslateMessage(pMsg);
}
