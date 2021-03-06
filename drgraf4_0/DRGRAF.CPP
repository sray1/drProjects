// drgraf.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"

#include "afxext.h" 
#include "drgrafrm.h"  
#include "drgracfm.h"  
#include "drgradoc.h"

#include "drgraf.h"   

#include "12view.h"
#include "23view.h" 
#include "31view.h"
#include "isoview.h"
#include "dataview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrGrafApp

BEGIN_MESSAGE_MAP(CDrGrafApp, CWinApp)
	//{{AFX_MSG_MAP(CDrGrafApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
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
/////////////////////////////////////////// the Application

/////////////////////////////////////////////////////////////////////////////
// CDrGrafApp construction

CDrGrafApp::CDrGrafApp()
{
		
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDrGrafApp object

CDrGrafApp FAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CDrGrafApp initialization
#ifdef _DEBUG
	BOOL bTracking = AfxEnableMemoryTracking(TRUE);
	static CMemoryState	OldMemState,NewMemState,DiffMemState;
#endif 

BOOL CDrGrafApp::InitInstance()
{ 


#ifdef _DEBUG
	OldMemState.Checkpoint();
#endif

	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not n'�d. '�C0�C�C>LK&?&l@Z�C3!��  'C3! '�C3! '�C0�C�C>LK&?:&l@Z�C3!�t  'C3! '�C3! '�C0�C�C>LK&�8&l@Z Load standard INI file options (including MRU)
	EnableVBX();               // Initialize VBX support

	CDrGrafChildFrame::Initialize();  // Child Window Show Init..
	
	
	RegisterDocTemplates();		// Register Document Templates
	
	
///////////////////////////////////////////////////// create main MDI Frame window
	CDrGrafFrame* pMainFrame = new CDrGrafFrame;
	CreateMainFrame(pMainFrame);
	m_pMainWnd = pMainFrame;
/////////////////////////////////////////////////////////////// SplashWindow	
	UIN&�?&w@Z�C�CFL*w@�C OSOE&>.&w@Z�C3! '�C3! '�C0�C�C>LKOQ:x@OR:x@TOR)x@OG+w@TT O�  ��O OUO#
[�O#
�SS& @&z@Z�C�CFL*z@�C OSOW&@&z@Z�C0�C�C>LKOY&@&z@Z�C0�C�C>LKO\:{@TO\){@OG+z@TT O�  ��O O`O#
[�O#
�SS&�?&}@Z�C�CF-|@L*}@�C OSOa&�&}@Z�C3! '�C3! '�C0�C�C>&|@0CUCLKOc&@&�?&}@Z�C0�C�C>CL,C 2CKOd&�@&�?&}@Z�C0�C�C>CL,C 2CKOf&�@&�?&}@Z�C0�C�C>CL,C 2CKOg&�@&�?&}@Z�C0�C�C>CL,C 2CKOh&�@&�?&}@Z�C0�C�C>CL,C 2CKOi&�@&�?&}@Z�C0�C�C>CL,C 2CKOj&�@&�?&}@Z�C0�C�C>;
//////////////////////////////////////////////////////////////// CommandLine
/*
	if (m_lpCmdLine[0] == '\0')
		OnFileNew();
	else
		OpenDocumentFile(m_lpCmdLine);
*/
	m_nCmdShow = nCmdShow;
	m_pMainWnd->UpdateWindow();


	// enable file manager drag/drop and DDE Execute open
	m_pMainWnd->DragAcceptFiles();
	EnableShellOpen();
	RegisterShellFileTypes();
/*
		CString strDocPath = GetDocPathFromIniFile();
		if (!strDocPath.IsEmpty())
			OpenDocumentFile(strDocPath);
	}
	else
	{
		// open an existing document
		OpenDocumentFile(m_lpCmdLine);
	}
*/
	return TRUE;
}
/////////////////////////////////////////////////////////////////  
void CDrGrafApp::CreateMainFrame(CDrGrafFrame* pMainFrame)
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
	pMainFrame->Create (ClassName,
   				"DrGrafix",
   				WS_OVERLAPPEDWINDOW,
   				pMainFrame->rectDefault,
   				NULL,
   				MAKEINTRESOURCE(IDR_INITMENU)); 
   				
}
int CDrGrafApp::ExitInstance()
{
//	CPadView::Terminate();
//	CDrGrafChildFrame::Terminate();

	return CWinApp::ExitInstance();     
#ifdef _DEBUG
	NewMemState.Checkpoint(); 
	if( DiffMemState.Difference( OldMemState,NewMemState)  )
	{
		TRACE( "Memory LEAKED !\n" );
	}
		
#endif
	
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
	// that lists FOUR document types, all of which would be "DrGrafix".
	// We avoid this problem by removing the third string from 
	// the document template for the DrGraf frame/view. 
	//
	// Finding no GetDocString(CDocTemplate::fileNewName) for the
	// second to fourth document template, CWinApp concludes that there is only
	// one document type supported by the application (the "System Model"
	// document type specified in the first document template; and
	// therefore does not represent the user with a File New dialog.
	
	m_p12ViewTemplate = new CMultiDocTemplate(IDR_12TYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(C12View));
	AddDocTemplate(m_p12ViewTemplate);

	m_p23ViewTemplate = new CMultiDocTemplate(IDR_23TYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(C23View));
	AddDocTemplate(m_p23ViewTemplate);

	m_p31ViewTemplate = new CMultiDocTemplate(IDR_31TYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(C31View));
	AddDocTemplate(m_p31ViewTemplate);

	m_pIsoViewTemplate = new CMultiDocTemplate(IDR_ISOTYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(CIsoView));
	AddDocTemplate(m_pIsoViewTemplate);  

	m_pDataViewTemplate = new CMultiDocTemplate(IDR_DATATYPE,
			RUNTIME_CLASS(CDrGrafDoc),
			RUNTIME_CLASS(CDrGrafChildFrame),
			RUNTIME_CLASS(CDataView));
	AddDocTemplate(m_pDataViewTemplate);  

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

void CDrGrafApp::OnFileOpen()
{   
	CWinApp::OnFileOpen(); 

	//////////////////////////////
	CString strTitle;
	m_pMainWnd->GetWindowText(strTitle);
	CString strPath  = m_pDoc->GetPathName();
	strTitle += ": " + strPath;
	m_pMainWnd->SetWindowText(strTitle);
	return;
	///////////
	OnFileNew();// TODO: Add your command handler code here
	
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
    BOOL bNewFile = TRUE;
    CWinApp::OnFileNew(); 
    /////////////////////
	CMDIChildWnd* pMDIActive = ((CDrGrafFrame*)m_pMainWnd)->MDIGetActive();
	ASSERT(pMDIActive != NULL);
	/////////////////////////////////////////////////
//	CDrGrafDoc* pDoc = (CDrGrafDoc*)(theApp.m_pDoc );
	/////////////////////////////////////////////////  
	CDocument* pDoc = pMDIActive->GetActiveDocument();
	ASSERT(pDoc != NULL);
    ////////////////////////////
    m_pDoc = (CDrGrafDoc*) pDoc;
	//////////////////////////////
	CString strTitle;
	m_pMainWnd->GetWindowText(strTitle);
	strTitle += ": Untitled";
	m_pMainWnd->SetWindowText(strTitle);
    ////////////////////////////
	((CDrGrafFrame*)(m_pMainWnd))->GetStatusBar()->Init();
	((CDrGrafFrame*)(m_pMainWnd))->GetStatusBar()->ShowWindow(SW_SHOW);
	((CDrGrafFrame*)(m_pMainWnd))->RecalcLayout();
	((CDrGrafFrame*)(m_pMainWnd))->GetStatusBarTop()->Init();
	((CDrGrafFrame*)(m_pMainWnd))->GetStatusBarTop()->ShowWindow(SW_SHOW);
	((CDrGrafFrame*)(m_pMainWnd))->RecalcLayout();
    ////////////////////////////////////////////////// Element Box
	((CDrGrafFrame*)(m_pMainWnd))->GetElementBox()->ShowWindow(SW_SHOW);
	((CDrGrafFrame*)(m_pMainWnd))->RecalcLayout(); 
    ////////////////////////////////////////////////// Draw Box
	((CDrGrafFrame*)(m_pMainWnd))->GetDrawBox()->ShowWindow(SW_SHOW);
	((CDrGrafFrame*)(m_pMainWnd))->RecalcLayout();
	///////////////////////////////////////////////////////////////////// OpenMenu
	((CDrGrafFrame*)m_pMainWnd)->
			MDISetMenu( ((CDrGrafFrame*)m_pMainWnd)->GetOpenMenu(),NULL); 
	((CDrGrafFrame*)m_pMainWnd)->DrawMenuBar(); 
	///////////////////////////////////////////
    return;
    /////////////////////
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
}


CDocument* CDrGrafApp::OpenDocumentFile(LPCSTR lpszFileName)
{
	// CWinApp::OpenDocmentFile creates the first MDI child window
	// for the 12 view.  This override creates all other MDI child
	// window for the Model view.  Then it tiles the four MDI children
	// windows.

	CFrameWnd* pNewFrame;
	/////////////////////////// 

	// If file doesn't already exist, then create it.
	CFile file;
	CFileStatus status;
	CString str = lpszFileName;
	if (!file.GetStatus(str, status))
	{
		file.Open(str, CFile::modeCreate);
		file.Close();
	}

	CDrGrafDoc* pDoc = (CDrGrafDoc*)CWinApp::OpenDocumentFile(lpszFileName);

	if (pDoc == NULL)
	{
		AfxMessageBox("OpenDocumentFile failed.");
		return NULL;
	}

	m_pDoc=pDoc;	
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

/////////////////////////////////////////////////// Initialize Status Bars
	((CDrGrafFrame*)(m_pMainWnd))->GetStatusBar()->Init();
	((CDrGrafFrame*)(m_pMainWnd))->GetStatusBar()->ShowWindow(SW_SHOW);
	((CDrGrafFrame*)(m_pMainWnd))->RecalcLayout();
	((CDrGrafFrame*)(m_pMainWnd))->GetStatusBarTop()->Init();
	((CDrGrafFrame*)(m_pMainWnd))->GetStatusBarTop()->ShowWindow(SW_SHOW);
	((CDrGrafFrame*)(m_pMainWnd))->RecalcLayout();
    ////////////////////////////////////////////////// Element Box
	((CDrGrafFrame*)(m_pMainWnd))->GetElementBox()->ShowWindow(SW_SHOW);
	((CDrGrafFrame*)(m_pMainWnd))->RecalcLayout(); 
    ////////////////////////////////////////////////// Draw Box
	((CDrGrafFrame*)(m_pMainWnd))->GetDrawBox()->ShowWindow(SW_SHOW);
	((CDrGrafFrame*)(m_pMainWnd))->RecalcLayout();
	///////////////////////////////////////////////////////////////////// OpenMenu
	((CDrGrafFrame*)m_pMainWnd)->
			MDISetMenu( ((CDrGrafFrame*)m_pMainWnd)->GetOpenMenu(),NULL); 
	((CDrGrafFrame*)m_pMainWnd)->DrawMenuBar(); 
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
//	void 	UpdateIniFileWithDocPath(const char* pszPathName);
//	CString GetDocPathFromIniFile();
	
///////////////////////////////////////////////////////////////////	 
BOOL CDrGrafApp::OnIdle(LONG lCount)
{
	// call base class idle first
	BOOL bResult = CWinApp::OnIdle(lCount);

	// then do our work
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
	return bResult;
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

