// Dlg_CurI.cpp : implementation file
//

#include "stdafx.h"
#include "MCurDll.h"
#include "UserMsg.h"

#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "Dlg_LQCI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_LQCI dialog


CDlg_LQCI::CDlg_LQCI(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_LQCI)
	m_bAdvanceOn	= FALSE;
	m_bClosed		= FALSE;
	m_dCoord		= 0.0;
	m_bUniform		= TRUE;
	//}}AFX_DATA_INIT
	m_pWnd 	= pWnd;
}


void CDlg_LQCI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_LQCI)
	DDX_CBString(pDX, IDC_CID, m_CID);
	DDX_CBString(pDX, IDC_NID, m_NID);
	DDX_Text(pDX, IDC_ELEMS, m_nElperSeg);
	DDX_Text(pDX, IDC_RATIO, m_dRatio);
	DDV_MinMaxDouble(pDX, m_dRatio, 0.1, 9999.);
	DDX_Check(pDX, IDC_ADVANCED, m_bAdvanceOn);
	DDX_Check(pDX, IDC_CLOSED, m_bClosed);
	DDX_Text(pDX, IDC_COORD, m_dCoord);
	DDX_Check(pDX, IDC_UNIFORM, m_bUniform);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_LQCI, CDialog)
	//{{AFX_MSG_MAP(CDlg_LQCI)
	ON_CBN_SELCHANGE(IDC_CID, OnSelchangeCid)
	ON_CBN_SELCHANGE(IDC_NID, OnSelchangeNid)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_CLOSED, OnClosed)
	ON_EN_KILLFOCUS(IDC_COORD, OnKillfocusCoord)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_DOUBLECLICKED(IDC_CLOSED, OnClosed)
	ON_BN_CLICKED(IDD_CANCEL, OnCancel)
	ON_BN_DOUBLECLICKED(IDD_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_UNIFORM, OnUniform)
	ON_BN_DOUBLECLICKED(IDC_UNIFORM, OnUniform)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMCur_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_LQCI message handlers

BOOL CDlg_LQCI::OnInitDialog()
{
	CDialog::OnInitDialog();
	////////////////////////////////////// Fill Up Sup & Load   TODO
	// TODO: Add extra initialization here
	//////////////////////////////////////////////////// Set Uniform Option
	m_bUniform	= TRUE;
//	((CButton*)GetDlgItem(IDC_UNIFORM))->SetCheck(TRUE);
//	GetDlgItem(IDC_RATIO)->EnableWindow(FALSE);	
	//////////	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_LQCI::Create ()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMCur_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	/////////////////////////////////////////////////////////////
	bOk = CDialog::Create(CDlg_LQCI::IDD);
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

void CDlg_LQCI::OnSelchangeCid() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	// TODO: Add your control notification handler code here
	
}

void CDlg_LQCI::OnSelchangeNid() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	// TODO: Add your control notification handler code here
	
}

void CDlg_LQCI::OnClosed() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	CWnd* pWndCtrl;
	///////////////////////
	if(m_bClosed)
	{
		m_bAdvanceOn	= FALSE;
		pWndCtrl = GetDlgItem(IDC_ADVANCED);
		pWndCtrl->EnableWindow(FALSE);
	}
	else
	{
		pWndCtrl = GetDlgItem(IDC_ADVANCED);
		pWndCtrl->EnableWindow(TRUE);
	}
	/////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_LQCIN,IDC_UPDATE);
}

void CDlg_LQCI::OnCancel() 
{
	////////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_CANCEL_LQCIN,IDD_CANCEL);
	////////////////////////////////////////////////////
}

void CDlg_LQCI::OnUpdate() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_LQCIN,IDC_UPDATE);
}

void CDlg_LQCI::OnKillfocusCoord() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_LQCIN,IDC_COORD);
}

void CDlg_LQCI::OnUniform() 
{
	// TODO: Add your control notification handler code here
	
}
/////////////////////////// end of module //////////////
