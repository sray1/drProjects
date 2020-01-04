// testrgbDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testrgb.h"
#include "testrgbDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
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

/////////////////////////////////////////////////////////////////////////////
// CTestrgbDlg dialog

CTestrgbDlg::CTestrgbDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestrgbDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestrgbDlg)
	m_Blue = 0;
	m_Green = 0;
	m_Red = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestrgbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestrgbDlg)
	DDX_Text(pDX, IDC_BLUE, m_Blue);
	DDV_MinMaxUInt(pDX, m_Blue, 0, 255);
	DDX_Text(pDX, IDC_GREEN, m_Green);
	DDV_MinMaxUInt(pDX, m_Green, 0, 255);
	DDX_Text(pDX, IDC_RED, m_Red);
	DDV_MinMaxUInt(pDX, m_Red, 0, 255);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestrgbDlg, CDialog)
	//{{AFX_MSG_MAP(CTestrgbDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_DONE, OnDone)
	ON_BN_CLICKED(IDB_SHOW, OnShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestrgbDlg message handlers

BOOL CTestrgbDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	
	// Initialize edit controls & member variables.
	m_Red = 0;
	m_Green = 0;
	m_Blue = 0;
	UpdateData(FALSE);    // upload data

	int editID[3] = {IDC_RED, IDC_GREEN, IDC_BLUE};
	for (int i = 0; i < 3; i++)
	{	
		CEdit *pEdit = (CEdit *)GetDlgItem(editID[i]);
		pEdit->SetLimitText(3);
	}

	GetClientRect(&m_ColorRect);
	double width = m_ColorRect.Width();
	double height = m_ColorRect.Height();
	m_ColorRect.SetRect(0.7 * width, 0.6 * height,
						0.85 * width, 0.85 * height);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestrgbDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestrgbDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
//		CDialog::OnPaint();

		CPaintDC dc(this);

		CBrush brush(RGB(m_Red,m_Green,m_Blue));
		CBrush *pOldBrush = dc.SelectObject(&brush);

		dc.Rectangle(m_ColorRect);

		dc.SelectObject(pOldBrush);
		brush.DeleteObject();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestrgbDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestrgbDlg::OnShow() 
{
	// TODO: Add your control notification handler code here
	
	if (!UpdateData(TRUE))
		return;

	InvalidateRect(&m_ColorRect);

}


void CTestrgbDlg::OnDone() 
{
	// TODO: Add your control notification handler code here

	EndDialog(0);

}

