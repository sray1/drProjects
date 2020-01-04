// Dlg_CurI.cpp : implementation file
//

#include "stdafx.h"
#include "MStLDll.h"
#include "UserMsg.h"
#include "CommRsrc.h"
#include "MNodRsrc.h"
#include "MCurRsrc.h"
#include "MStLRsrc.h"


#include "Dlg_PrsI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_PrsI dialog


CDlg_PrsI::CDlg_PrsI(CWnd* pWnd)
	: CDialog()                    // Modeless constructor
{
	//{{AFX_DATA_INIT(CDlg_PrsI)
	m_dFx	= 0.0;
	m_LoadID = _T("");
	//}}AFX_DATA_INIT
	m_pWnd 		= pWnd;
}


void CDlg_PrsI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_PrsI)
	DDX_Text(pDX, IDC_FX, m_dFx);
	DDX_CBString(pDX, IDC_LOADID, m_LoadID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_PrsI, CDialog)
	//{{AFX_MSG_MAP(CDlg_PrsI)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_CBN_SELCHANGE(IDC_LOADID, OnSelchangeLoadid)
	ON_BN_DOUBLECLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_DOUBLECLICKED(IDC_ADVANCED, OnAdvanced)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////// resource switch
extern AFX_EXTENSION_MODULE NEAR extensionMStL_DLL;

/////////////////////////////////////////////////////////////////////////////
// CDlg_PrsI message handlers

BOOL CDlg_PrsI::OnInitDialog()
{
	CDialog::OnInitDialog();
	////////////////////////////////////// Fill Up Sup
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BOOL CDlg_PrsI::Create ()
{
	BOOL bOk;	
#ifdef _AFXDLL
#ifdef _DEBUG
	CString strRes;
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes); 
#endif

	HINSTANCE hInstResourceClient = AfxGetResourceHandle();
	AfxSetResourceHandle(extensionMStL_DLL.hModule); // uses server's instance handle 

#ifdef _DEBUG
	strRes.LoadString(IDS_CHECK_RESOURCE);
	TRACE("resource string = %s\n", (const char*) strRes);
//	return hInstResourceClient;  
#endif
#endif
	/////////////////////////////////////////////////////////////
	bOk = CDialog::Create(CDlg_PrsI::IDD);
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


void CDlg_PrsI::OnUpdate() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	if(m_pWnd !=NULL)
		m_pWnd->SendMessage(ID_UPDATE_PRESSIN,IDC_UPDATE);
}

void CDlg_PrsI::OnSelchangeLoadid() 
{
	/////////////////
	UpdateData(TRUE);
	/////////////////
	// TODO: Add your control notification handler code here
	
}

void CDlg_PrsI::OnAdvanced() 
{
	// TODO: Open Dialog for  Addl. Info for skew/ NonLin support etc
	
}
/////////////////////////// end of module //////////////
