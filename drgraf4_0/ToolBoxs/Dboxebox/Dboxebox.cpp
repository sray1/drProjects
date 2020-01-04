// dboxebox.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
///////////////////// Old ToolBar Utility from MFC (VC++ 1.5)
#include "globals.h"
#include "toolbar.h"
#include "statbar.h"
/////////////////////
#include "dboxebox.h"

#include "mainfrm.h"
#include "dboxedoc.h"
#include "dboxevw.h"
/////////////////////////////////////////////// toolbox dlls
#include "eboxdll.h"
#include "dboxdll.h"          

/////////////////////
#include "glb_Elem.h"
#include "dbglobal.h"
///////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxApp

BEGIN_MESSAGE_MAP(CDBoxEBoxApp, CWinApp)
	//{{AFX_MSG_MAP(CDBoxEBoxApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxApp construction

CDBoxEBoxApp::CDBoxEBoxApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDBoxEBoxApp object

CDBoxEBoxApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxApp initialization

BOOL CDBoxEBoxApp::InitInstance()
{
#ifdef _AFXDLL
	InitDBoxDLL();	// necessary for DLL resource access and IsKindOf
	InitEBoxDLL();	// necessary for DLL resource access and IsKindOf
#endif
	///////////////////////////////////////////////////////////END/////BANNER////////
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DBOXEBTYPE,
		RUNTIME_CLASS(CDBoxEBoxDoc),
		RUNTIME_CLASS(CMDIChildWnd),        // standard MDI child frame
		RUNTIME_CLASS(CDBoxEBoxView));
	AddDocTemplate(pDocTemplate);
    ////////////////////////////////////////////////////// register new class
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
					//·	class style : 0 [ reduces flash during resizing, no double clicks ]
					//·	no icon
					//·	arrow cursor
					//·	gray background color (COLOR_BTNFACE)
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
    /////////////////////////////////////////////////////////////////////
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// create a new (empty) document
	OnFileNew();

	if (m_lpCmdLine[0] != '\0')
	{
		// TODO: add command line processing here
	}

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDBoxEBoxApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDBoxEBoxApp commands
