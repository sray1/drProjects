// Dlg_CurI.cpp : implementation file
//

#include "stdafx.h"

#include "CMgrDll.h"
#include "UserMsg.h"
/////////////////////
#include "CommRsrc.h"
#include "Dlg_CrOI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CrOI dialog


CDlg_CrOI::CDlg_CrOI(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_CrOI)
	m_ObjID			= _T("");
	m_X				= 0.0;
	m_Y				= 0.0;
	m_Z				= 0.0;
	m_NID			= _T("");
	m_bDirect		= FALSE;
	m_bDirCos		= FALSE;
	m_bDominant		= FALSE;
	m_bAngleIn		= FALSE;
	m_bNegative		= FALSE;
	m_bAxis			= FALSE;
	//}}AFX_DATA_INIT
	m_pWnd 	= pWnd;
//	m_nAxis	= 0;	// No-Axis , default
}


void CDlg_CrOI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CrOI)
	DDX_Text(pDX, IDC_OBJID, m_ObjID);
	DDX_Text(pDX, IDC_ROT_X, m_X);
	DDX_Text(pDX, IDC_ROT_Y, m_Y);
	DDX_Text(pDX, IDC_ROT_Z, m_Z);
	DDX_Text(pDX, IDC_TRANPT, m_NID);
	DDX_Check(pDX, IDC_COORD_INPUT, m_bDirect);
	DDX_Check(pDX, IDC_DIRCOS, m_bDirCos);
	DDX_Check(pDX, IDC_DOMINANT, m_bDominant);
	DDX_Check(pDX, IDC_ANGLE_INPUT, m_bAngleIn);
	DDX_Check(pDX, IDC_NEGATIVE, m_bNegative);
	DDX_Check(pDX, IDC_AXIS, m_bAxis);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_CrOI, CDialog)
	//{{AFX_MSG_MAP(CDlg_CrOI)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_COORD_INPUT, OnCoordInput)
	ON_EN_CHANGE(IDC_OBJID, OnChangeObjID)
	ON_BN_CLICKED(IDC_ANGLE_INPUT, OnAngleInput)
	ON_BN_CLICKED(IDC_DIRCOS, OnDirCos)
	ON_BN_CLICKED(IDC_DOMINANT, OnDominant)
	ON_BN_CLICKED(IDC_NEGATIVE, OnNegative)
	ON_BN_CLICKED(IDC_AXIS_X, OnAxisX)
	ON_BN_CLICKED(IDC_AXIS_Y, OnAxisY)
	ON_BN_CLICKED(IDC_AXIS_Z, OnAxisZ)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_COORD_INPUT, OnCoordInput)
	ON_BN_DOUBLECLICKED(IDCANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDC_ANGLE_INPUT, OnAngleInput)
	ON_BN_DOUBLECLICKED(IDC_DIRCOS, OnDirCos)
	ON_BN_DOUBLECLICKED(IDC_DOMINANT, OnDominant)
	ON_BN_DOUBLECLICKED(IDC_NEGATIVE, OnNegative)
	ON_BN_DOUBLECLICKED(IDC_AXIS_X, OnAxisX)
	ON_BN_DOUBLECLICKED(IDC_AXIS_Y, OnAxisY)
	ON_BN_DOUBLECLICKED(IDC_AXIS_Z, OnAxisZ)
	ON_BN_CLICKED(IDC_AXIS, OnAxis)
	ON_BN_DOUBLECLICKED(IDC_AXIS, OnAxis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE extensionCMgr_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_CrOI message handlers

BOOL CDlg_CrOI::OnInitDialog()
{
	CDialog::OnInitDialog();
	////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_CrOI::Create ()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionCMgr_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	///////////////////////////////////////////////////////////// 
	bOk = CDialog::Create(CDlg_CrOI::IDD);
	///////////////////////////////////////
#ifdef _AFXDLL
//	CString strRes;
	AfxSetResourceHandle(hInstResourceClient); // restores client's instance handle

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif
#endif
	//////////////////
	return bOk;
}

void CDlg_CrOI::OnCancel() 
{
	////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_CREIN,IDD_CANCEL);
	////////////////////////////////////////////////////
}

void CDlg_CrOI::OnUpdate() 
{
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_CREIN,IDC_UPDATE);
}


BOOL CDlg_CrOI::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
/*
	BOOL WinHelp(
  

    HWND  hWndMain,	// handle of window requesting Help 
    LPCTSTR  lpszHelp,	// address of directory-path string 
    UINT  uCommand,	// type of Help 
    DWORD  dwData 	// additional data 
   );
*/ 

	AfxGetApp()->WinHelp(pHelpInfo->dwContextId,HELP_CONTEXTPOPUP);
	return TRUE;

//	return CDialog::OnHelpInfo(pHelpInfo);
}

void CDlg_CrOI::OnCoordInput()
{
	UpdateData(TRUE);
	/////////////////
	m_bDirect = !m_bDirect;
	///////////////////////
	// 12/29/97
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_CREIN,IDC_COORD_INPUT);
	// 12/29/97 end
}


void CDlg_CrOI::OnAngleInput() 
{
	UpdateData(TRUE);
	/////////////////
	m_bAngleIn = !m_bAngleIn;
	///////////////////////
	// 12/29/97
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_CREIN,IDC_ANGLE_INPUT);
	// 12/29/97 end
}

void CDlg_CrOI::OnDirCos() 
{
	UpdateData(TRUE);
	/////////////////
	m_bDirCos = !m_bDirCos;
	///////////////////////
	// 12/29/97
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_CREIN,IDC_DIRCOS);
	// 12/29/97 end
}

void CDlg_CrOI::OnDominant() 
{
	UpdateData(TRUE);
	/////////////////
	m_bDominant = !m_bDominant;
	///////////////////////
	if(m_bDominant)
	{
		GetDlgItem(IDC_AXIS)->SetWindowText("Axis");
		GetDlgItem(IDC_AXIS)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_AXIS)->SetWindowText("");
		GetDlgItem(IDC_AXIS)->EnableWindow(FALSE);
	}
	// 12/29/97
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_CREIN,IDC_DOMINANT);
	// 12/29/97 end
	/////////////////
}

void CDlg_CrOI::OnChangeObjID() 
{
	// 12/29/97
//	if(m_pWnd !=NULL)
//		m_pWnd->SendMessage(ID_UPDATE_CREIN,IDC_OBJID);
	// 12/29/97 end
}

void CDlg_CrOI::OnAxis() 
{
	UpdateData(TRUE);
	/////////////////
//	m_bAxis = !m_bAxis;
	///
	if(m_bAxis)
	{
		GetDlgItem(IDC_AXIS_X)->SetWindowText("X");
		GetDlgItem(IDC_AXIS_Y)->SetWindowText("Y");
		GetDlgItem(IDC_AXIS_Z)->SetWindowText("Z");
		GetDlgItem(IDC_NEGATIVE)->SetWindowText("Negative");
		GetDlgItem(IDC_AXIS_X)->EnableWindow(TRUE);
		GetDlgItem(IDC_AXIS_Y)->EnableWindow(TRUE);
		GetDlgItem(IDC_AXIS_Z)->EnableWindow(TRUE);
		GetDlgItem(IDC_NEGATIVE)->EnableWindow(TRUE);
		///
	}
	else
	{
		GetDlgItem(IDC_AXIS_X)->SetWindowText("");
		GetDlgItem(IDC_AXIS_Y)->SetWindowText("");
		GetDlgItem(IDC_AXIS_Z)->SetWindowText("");
		GetDlgItem(IDC_NEGATIVE)->SetWindowText("");
		GetDlgItem(IDC_AXIS_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_AXIS_Y)->EnableWindow(FALSE);
		GetDlgItem(IDC_AXIS_Z)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEGATIVE)->EnableWindow(FALSE);
		///
	}
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_CrOI::OnNegative() 
{
	UpdateData(TRUE);
	/////////////////
//	m_bNegative = !m_bNegative;
	/////////////////
	UpdateData(FALSE);
	/////////////////
}

void CDlg_CrOI::OnAxisX() 
{
	m_nAxis	= 1;	
}

void CDlg_CrOI::OnAxisY() 
{
	m_nAxis	= 2;	
}

void CDlg_CrOI::OnAxisZ() 
{
	m_nAxis	= 3;	
}
/////////////////////////// end of module //////////////
